#!/usr/bin/env python3
"""Reproducible reference-wide evidence audit; never imports reference source.

Reads every tracked file at the pinned clean commit. Private per-file results
include hashes, lexical hazards, independently compared disassembly bytes and
JSON hash-binding checks. Counts are review coverage, not reconstruction credit.
"""
from __future__ import annotations

import argparse
import collections
import csv
import hashlib
import json
from pathlib import Path
import re
import subprocess

from project import ROOT, load_manifest, verified_target, integer

HAZARDS = {
    "inline_assembly": re.compile(r"\b(?:__asm|_asm|asm)\b"),
    "naked": re.compile(r"__declspec\s*\(\s*naked\s*\)"),
    "decompiler": re.compile(r"\b(?:undefined[1248]?|unaff_\w+|extraout_\w+|CONCAT\d+|SUB\d+)\b"),
    "executable_memory": re.compile(r"\b(?:VirtualAlloc|VirtualProtect|PAGE_EXECUTE\w*|WriteProcessMemory)\b"),
}
ASM_LINE = re.compile(r"^\s*([0-9a-fA-F]{8})\s+((?:[0-9a-fA-F]{2} )*[0-9a-fA-F]{2}|(?:[0-9a-fA-F]{2}){2,15})(?=\s{2,})")
HASH = re.compile(r"^[0-9a-fA-F]{64}$")


def sha(data):
    return hashlib.sha256(data).hexdigest()


def module_for(path):
    parts = Path(path).parts
    return parts[1] if parts[0] == "source_reconstruction" and len(parts) > 2 else parts[0]


def category(path):
    p = Path(path)
    if path.startswith("analysis/ghidra/pseudocode/") or "combined_pseudocode" in path:
        return "generated-pseudocode"
    if p.suffix == ".asm":
        return "disassembly-evidence"
    if path.startswith("incremental/"):
        return "retained-engine-history"
    if path.startswith("scripts/recovered/"):
        return "resource-script"
    if p.suffix in (".cpp", ".hpp", ".h", ".c", ".inl", ".inc"):
        return "source-or-test"
    if p.suffix in (".json", ".jsonl", ".csv", ".properties", ".log"):
        return "claims-or-analysis"
    if p.suffix == ".md":
        return "documentation"
    return "tooling-or-data"


def audit(reference, target, manifest):
    def git(*args):
        return subprocess.check_output(["git", "-C", str(reference), *args])
    pin = load_manifest("reference.toml")
    if git("rev-parse", "HEAD").decode().strip() != pin["commit"]:
        raise ValueError("reference HEAD differs from pin")
    if git("status", "--porcelain", "--untracked-files=all").strip():
        raise ValueError("reference must be a clean pinned checkout")
    if pin["target_sha256"] != manifest["target"]["sha256"]:
        raise ValueError("reference audit target differs from locked target")
    paths = sorted(git("ls-files", "-z").decode().rstrip("\0").split("\0"))
    sections = manifest["pe"]["sections"]
    base = integer(manifest["pe"]["image_base"])

    def target_bytes(address, size):
        for s in sections:
            start = base + integer(s["rva"])
            if start <= address and address + size <= start + s["raw_size"]:
                off = integer(s["raw_offset"]) + address - start
                return target[off:off + size]
        return None

    records, summaries, texts = [], collections.defaultdict(collections.Counter), {}
    for path in paths:
        data = (reference / path).read_bytes()
        text = data.decode("utf-8", errors="replace")
        texts[path] = text
        kind, module = category(path), module_for(path)
        hazards = {name: len(rx.findall(text)) for name, rx in HAZARDS.items()}
        matches, mismatches, checked_bytes = 0, 0, 0
        if Path(path).suffix == ".asm":
            for line in text.splitlines():
                found = ASM_LINE.match(line)
                if not found:
                    continue
                address, code = int(found[1], 16), bytes.fromhex(found[2])
                checked_bytes += len(code)
                if target_bytes(address, len(code)) == code:
                    matches += 1
                else:
                    mismatches += 1
        record = dict(path=path, sha256=sha(data), bytes=len(data), lines=len(text.splitlines()),
                      module=module, category=kind, **hazards, asm_rows_match=matches,
                      asm_rows_mismatch=mismatches, asm_bytes_checked=checked_bytes)
        records.append(record)
        count = summaries[module]
        count.update(files=1, bytes=len(data), lines=record["lines"],
                     asm_rows_match=matches, asm_rows_mismatch=mismatches,
                     asm_bytes_checked=checked_bytes, **hazards)
        count[kind] += 1
        if Path(path).suffix in (".cpp", ".hpp", ".c", ".inc", ".inl"):
            count[Path(path).suffix] += 1
        if Path(path).name == "CMakeLists.txt":
            count["cmake_assembly_mentions"] += len(re.findall(r"\S+\.asm\b", text))
    known = {r["path"]: r["sha256"] for r in records}
    bindings, invalid_json = [], []

    def walk(value, report, pointer=""):
        if isinstance(value, dict):
            for key, val in value.items():
                normalized = key.replace("\\", "/").removeprefix("./")
                if normalized in known and isinstance(val, str) and HASH.fullmatch(val):
                    bindings.append(dict(report=report, pointer=pointer + "/" + key,
                                         source=normalized, claimed=val.lower(),
                                         observed=known[normalized], current=val.lower() == known[normalized]))
                walk(val, report, pointer + "/" + key)
        elif isinstance(value, list):
            for index, item in enumerate(value):
                walk(item, report, pointer + "/" + str(index))

    for path in paths:
        if Path(path).suffix == ".json":
            try:
                walk(json.loads(texts[path]), path)
            except json.JSONDecodeError:
                invalid_json.append(path)
    totals = collections.Counter()
    for counts in summaries.values():
        totals.update(counts)
    inventory_bytes = "".join(f"{r['path']}\0{r['sha256']}\n" for r in records).encode()
    summary = dict(repository=pin["repository"], commit=pin["commit"],
                   git_tree=git("rev-parse", "HEAD^{tree}").decode().strip(),
                   target_sha256=manifest["target"]["sha256"],
                   tracked_inventory_sha256=sha(inventory_bytes), totals=dict(totals),
                   modules={k: dict(v) for k, v in sorted(summaries.items())},
                   json_path_key_hash_bindings=len(bindings),
                   stale_bindings=[b for b in bindings if not b["current"]],
                   invalid_json=invalid_json,
                   asm_files_without_byte_rows=[r["path"] for r in records
                                               if r["category"] == "disassembly-evidence"
                                               and not r["asm_rows_match"] and not r["asm_rows_mismatch"]],
                   limitations=["Lexical hazard counts include comments and tests; inspect ownership before drawing conclusions.",
                                "Disassembly row byte equality validates evidence identity, not semantics, boundaries, ABI or C++ exactness.",
                                "Hash bindings cover JSON path-key/SHA256 maps, not every report's bespoke schema.",
                                "All tracked files scanned; no reference tests were run and no reconstruction credit inherited."])
    return summary, records, bindings


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reference", type=Path)
    parser.add_argument("--output", type=Path, default=ROOT / ".analysis/reference-review")
    args = parser.parse_args()
    try:
        target, manifest = verified_target()
        reference = args.reference or ROOT / load_manifest("reference.toml")["local_path"]
        output = args.output.resolve()
        output.relative_to((ROOT / ".analysis").resolve())
        summary, records, bindings = audit(reference.resolve(), target, manifest)
        output.mkdir(parents=True, exist_ok=True)
        (output / "summary.json").write_text(json.dumps(summary, indent=2) + "\n")
        (output / "bindings.json").write_text(json.dumps(bindings, indent=2) + "\n")
        with (output / "files.csv").open("w", newline="") as stream:
            writer = csv.DictWriter(stream, fieldnames=list(records[0]))
            writer.writeheader()
            writer.writerows(records)
        print(json.dumps({k: summary[k] for k in ("commit", "git_tree", "tracked_inventory_sha256", "totals", "json_path_key_hash_bindings")}))
        print(f"stale bindings: {len(summary['stale_bindings'])}; private detail: {output}")
        if summary["totals"]["asm_rows_mismatch"] or summary["invalid_json"]:
            return 1
        return 0
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        parser.exit(1, f"reference review failed: {error}\n")


if __name__ == "__main__":
    raise SystemExit(main())
