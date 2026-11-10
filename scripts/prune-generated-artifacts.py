#!/usr/bin/env python3
"""Remove obsolete build objects and receipts; dry run unless --apply is set."""
from __future__ import annotations

import argparse
import hashlib
from pathlib import Path
import subprocess
import tomllib

ROOT = Path(__file__).resolve().parents[1]
TARGET_SHA256 = 'a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897'


def digest(path: Path) -> str:
    with path.open('rb') as source:
        return hashlib.file_digest(source, 'sha256').hexdigest()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--apply', action='store_true', help='Delete the selected build products.')
    parser.add_argument('--keep', action='append', type=Path, default=[], metavar='BUILD_PATH',
                        help='Retain a file or directory needed by an unresolved compiler question.')
    options = parser.parse_args()
    build = ROOT / 'build'
    if not build.is_dir() or build.is_symlink():
        raise ValueError('build/ must be a local directory')
    manifest = tomllib.loads((ROOT / 'config/match-units.toml').read_text())
    if manifest.get('target_sha256') != TARGET_SHA256 or not manifest.get('units'):
        raise ValueError('cleanup requires a nonempty manifest for the locked target')
    objects = {ROOT / unit['object'] for unit in manifest['units'].values()}
    protected = {ROOT / 'resources/th20.exe', *objects,
                 *(path.with_suffix('.receipt.json') for path in objects)}
    for path in protected - {ROOT / 'resources/th20.exe'}:
        path.resolve().relative_to(build.resolve())
    for relative in options.keep:
        path = (ROOT / relative).resolve()
        path.resolve().relative_to(build.resolve())
        if not path.exists() or path.is_symlink():
            raise ValueError(f'keep path is missing or a symlink: {relative}')
        if path.is_dir():
            protected.update(p for p in path.rglob('*') if p.is_file())
        else:
            protected.add(path)
    hashes = {path: digest(path) for path in protected}
    if hashes[ROOT / 'resources/th20.exe'] != TARGET_SHA256:
        raise ValueError('target SHA-256 differs from the locked executable')
    tracked = set(subprocess.check_output(
        ['git', 'ls-files', '-z', '--', 'build'], cwd=ROOT,
    ).decode().split('\0'))
    candidates = [path for path in sorted(build.rglob('*'))
                  if path.is_file() and not path.is_symlink() and path not in protected
                  and str(path.relative_to(ROOT)) not in tracked
                  and (path.suffix == '.obj' or path.name.endswith('.receipt.json'))]
    size = sum(path.stat().st_size for path in candidates)
    for path in candidates:
        print(path.relative_to(ROOT))
    print(f"{'APPLY' if options.apply else 'DRY RUN'}: {len(candidates)} files, {size:,} bytes; "
          f'{len(objects)} canonical object/receipt pairs protected')
    if options.apply:
        for path in candidates:
            path.unlink()
        for path, expected in hashes.items():
            if digest(path) != expected:
                raise ValueError(f'protected file changed: {path.relative_to(ROOT)}')
        print('Target and retained product hashes unchanged.')


if __name__ == '__main__':
    main()
