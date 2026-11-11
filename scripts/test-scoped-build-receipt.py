#!/usr/bin/env python3
"""Scoped regression: unrelated source moves do not invalidate exact COFF receipts.

Uses a disposable copy of the one existing exact 26B selector's object and
receipt. Never modifies the canonical object, executable, or target manifest.
This checks metadata integrity only; compare-coff-function still verifies all
native bytes and separately attested original relocation destinations.
"""
import copy
import json
from pathlib import Path
import shutil
import sys
import tempfile

from project import ROOT, load_manifest, verify_build_receipt


def main():
    unit = load_manifest('match-units.toml')['units']['particle_effect_info_lookup_26']
    canonical = ROOT / unit['object']
    original_receipt = json.loads(canonical.with_suffix('.receipt.json').read_text())
    with tempfile.TemporaryDirectory(prefix='receipt-scope-', dir=ROOT / 'build') as scratch:
        dst = Path(scratch) / canonical.name
        shutil.copy2(canonical, dst)
        receipt_path = dst.with_suffix('.receipt.json')
        cloned = copy.deepcopy(unit)
        cloned['object'] = str(dst.relative_to(ROOT))

        def check(label, report, expected=True, changed_unit=None):
            receipt_path.write_text(json.dumps(report) + '\n')
            try:
                verify_build_receipt(changed_unit or cloned)
            except ValueError as exc:
                assert not expected, f'{label} wrongly rejected: {exc}'
                print(f'PASS rejected {label}: {exc}')
            else:
                assert expected, f'{label} wrongly accepted'
                print(f'PASS accepted {label}')

        check('unaltered canonical receipt', original_receipt)
        unrelated = copy.deepcopy(original_receipt)
        unrelated['inputs']['probes/NoRelationToEffectLookup.cpp'] = '0' * 64
        check('added unrelated source', unrelated)
        unrelated = copy.deepcopy(original_receipt)
        other = next((s for s in unrelated['inputs'] if s.endswith('/AnimationDrawBoss.cpp')))
        unrelated['inputs'].pop(other)
        check('removed unrelated source', unrelated)
        unrelated = copy.deepcopy(original_receipt)
        unrelated['inputs']['src/Session.hpp'] = '0' * 64
        check('new header shadowing captured include', unrelated, False)
        tampered = copy.deepcopy(original_receipt)
        tampered['inputs'][unit['source']] = '0' * 64
        check('changed owned source', tampered, False)
        tampered = copy.deepcopy(original_receipt)
        path = next(k for k in tampered['headers'] if k.endswith('/Session.hpp'))
        tampered['headers'][path] = '0' * 64
        check('changed captured header', tampered, False)
        tampered = copy.deepcopy(original_receipt)
        tampered['target_sha256'] = '0' * 64
        check('changed target digest', tampered, False)
        wrong_unit = copy.deepcopy(cloned)
        wrong_unit['profile'] = ['/Od']
        check('wrong compiler profile', original_receipt, False, wrong_unit)
        with dst.open('r+b') as f:
            f.seek(24)
            old = f.read(1)
            f.seek(24)
            f.write(bytes([old[0] ^ 1]))
        check('changed object bytes', original_receipt, False)
    print('Scoped receipt regression: 3 accepted / 6 rejected as intended')


if __name__ == '__main__':
    main()
