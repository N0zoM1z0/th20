#!/usr/bin/env python3
"""Public consistency gates for reference decisions, without a private checkout."""
import csv
import json

from project import ROOT, load_manifest


def validate():
    pin = load_manifest("reference.toml")
    target = load_manifest("target.toml")["target"]
    audit = json.loads((ROOT / "config/reference-audit.json").read_text())
    for key in ("repository", "commit", "target_sha256"):
        if audit[key] != pin[key]:
            raise ValueError(f"reference audit/pin mismatch: {key}")
    if pin["target_sha256"] != target["sha256"]:
        raise ValueError("reference decision target differs from the exact target")
    if pin["local_path"] != "_reference/Touhou20":
        raise ValueError("reference checkout must use the ignored repository-local path")
    if audit["totals"]["asm_rows_mismatch"]:
        raise ValueError("reference disassembly mismatch cannot be accepted")
    with (ROOT / "config/reference-review.csv").open(newline="") as stream:
        decisions = list(csv.DictReader(stream))
    groups = {row["reference_module"] for row in decisions}
    if len(groups) != len(decisions) or len(decisions) != audit["module_dispositions"]:
        raise ValueError("reference group coverage is duplicate or incomplete")
    if sum(int(row["files"]) for row in decisions) != audit["totals"]["files"]:
        raise ValueError("reference dispositions do not account for every tracked file")
    if any(not row["disposition"] or not row["review_note"] for row in decisions):
        raise ValueError("reference group lacks a decision and review rationale")
    with (ROOT / "config/functions.csv").open(newline="") as stream:
        functions = {row["address"]: row for row in csv.DictReader(stream)}
    with (ROOT / "config/source-diagnostics.csv").open(newline="") as stream:
        diagnostics = list(csv.DictReader(stream))
    seen = set()
    for row in diagnostics:
        identity = (row["address"], row["instruction_address"], row["string_address"])
        function = functions.get(row["address"])
        if identity in seen or function is None:
            raise ValueError("duplicate or unowned source diagnostic")
        if not int(row["address"], 0) <= int(row["instruction_address"], 0) <= int(function["span_end"], 0):
            raise ValueError("source diagnostic instruction lies outside its reviewed routing range")
        if not row["source_path"] or not row["evidence"] or int(row["source_line"]) <= 0:
            raise ValueError("source diagnostic lacks evidence or source location")
        seen.add(identity)
    print(f"reference review consistent: {len(decisions)} groups, {audit['totals']['files']} files, {len(diagnostics)} routing sites")


if __name__ == "__main__":
    validate()
