#!/usr/bin/env python3
"""Verify retained-source routing leads without importing names or exact credit.

Run Ghidra's attested architecture export first. Each row requires a matching
target string, current Ghidra string-reference pair, inventoried owner range,
and an independently decoded immediate at the claimed machine instruction.
"""
import argparse
import csv
import json
from pathlib import Path
import re

from project import ROOT, load_manifest, verified_target, integer


def verify(reference):
    from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_OP_IMM

    data, manifest = verified_target()
    base = integer(manifest["pe"]["image_base"])
    sections = manifest["pe"]["sections"]

    def read(address, length):
        for section in sections:
            start = base + integer(section["rva"])
            if start <= address and address + length <= start + section["raw_size"]:
                offset = integer(section["raw_offset"]) + address - start
                return data[offset:offset + length]
        raise ValueError(f"lead outside file-backed target: 0x{address:08X}")

    with (ROOT / "config/functions.csv").open(newline="") as stream:
        functions = {int(row["address"], 0): row for row in csv.DictReader(stream)}
    with (ROOT / ".analysis/architecture/string-refs.csv").open(newline="") as stream:
        xrefs = {(int(row["function"], 0), int(row["address"], 0)): row["value"]
                 for row in csv.DictReader(stream)}
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    result, rejected = [], []
    with (reference / "analysis/ghidra/source_location_functions.csv").open(newline="") as stream:
        for row in csv.DictReader(stream):
            if not row["function_entry"]:
                rejected.append(dict(row, rejection="reference has no containing function"))
                continue
            function = int(row["function_entry"], 0)
            string = int(row["string_va"], 0)
            site = int(row["reference_va"], 0)
            owner = functions.get(function)
            if owner is None or not function <= site <= int(owner["span_end"], 0):
                raise ValueError(f"lead has unverified containing function: {row}")
            actual = read(string, 1024).split(b"\0", 1)[0].decode("cp932")
            suffix = row["source_path"] + ":" + row["source_line"] + " " + row["type_or_context"]
            if not re.sub(r"\\+", "/", actual).endswith(suffix) or (function, string) not in xrefs:
                raise ValueError(f"retained diagnostic or Ghidra reference differs: {row}")
            instruction = next(decoder.disasm(read(site, 15), site, count=1), None)
            if instruction is None or not any(op.type == CS_OP_IMM and op.imm == string
                                              for op in instruction.operands):
                raise ValueError(f"claimed instruction does not reference diagnostic: {row}")
            result.append(dict(address=f"0x{function:08X}", source_path=row["source_path"],
                               source_line=row["source_line"], context=row["type_or_context"],
                               string_address=f"0x{string:08X}", instruction_address=f"0x{site:08X}",
                               evidence="REF-001; target string + decoded immediate + attested Ghidra xref"))
    private = ROOT / ".analysis/reference-review"
    private.mkdir(parents=True, exist_ok=True)
    (private / "rejected-diagnostics.json").write_text(json.dumps(rejected, indent=2) + "\n")
    return sorted(result, key=lambda row: (row["address"], row["instruction_address"]))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    reference = ROOT / load_manifest("reference.toml")["local_path"]
    # Reuse the full clean-commit audit before trusting even routing metadata.
    import importlib.util
    spec = importlib.util.spec_from_file_location("reference_review", ROOT / "scripts/review-reference.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    data, manifest = verified_target()
    summary, _, _ = module.audit(reference, data, manifest)
    if summary["totals"]["asm_rows_mismatch"]:
        raise ValueError("reference disassembly identity failed")
    rows = verify(reference)
    output = ROOT / "config/source-diagnostics.csv"
    if args.check:
        with output.open(newline="") as stream:
            if list(csv.DictReader(stream)) != rows:
                raise ValueError("source routing evidence is stale")
    else:
        with output.open("w", newline="") as stream:
            writer = csv.DictWriter(stream, fieldnames=list(rows[0]), lineterminator="\n")
            writer.writeheader()
            writer.writerows(rows)
    print(f"verified {len(rows)} diagnostic sites in {len({r['address'] for r in rows})} functions; no origin/source/exact credit")


if __name__ == "__main__":
    raise SystemExit(main())
