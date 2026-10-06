#!/usr/bin/env python3
"""Validate and report explicit function decisions, never file-scan completion."""
import csv
from collections import Counter
import json

from project import ROOT, load_manifest

TERMINAL = {"absorbed-exact", "library-exact", "support-reviewed", "reviewed-nonexact"}
STAGES = TERMINAL | {"source-reviewed", "target-reviewed", "compiler-tested"}


def read(name):
    with (ROOT / "config" / name).open(newline="") as stream:
        return list(csv.DictReader(stream))


def report():
    bodies = read("reference-function-index.csv")
    decisions = read("reference-function-reviews.csv")
    files = read("reference-source-files.csv")
    index = {row["id"]: row for row in bodies}
    if len(index) != len(bodies):
        raise ValueError("duplicate reference body identity")
    file_index = {row["reference_path"]: row for row in files}
    if len(file_index) != len(files) or sum(int(row["definitions"]) for row in files) != len(bodies):
        raise ValueError("reference source coverage is inconsistent")
    for row in bodies:
        if row["file_sha256"] != file_index[row["reference_path"]]["file_sha256"]:
            raise ValueError("reference function/file identity differs")
    units = load_manifest("match-units.toml")["units"]
    seen = set()
    for row in decisions:
        if row["id"] in seen or row["id"] not in index or row["stage"] not in STAGES:
            raise ValueError("duplicate, unknown or invalid function review")
        if row["body_sha256"] != index[row["id"]]["body_sha256"]:
            raise ValueError("function review binds a stale body")
        if not row["evidence"] or not row["notes"]:
            raise ValueError("function review lacks evidence or rationale")
        canonical = row["canonical_units"].split(";") if row["canonical_units"] else []
        if any(unit not in units for unit in canonical):
            raise ValueError("function review names an unknown canonical unit")
        if row["stage"] in {"absorbed-exact", "library-exact"} and not canonical:
            raise ValueError("exact absorption lacks a canonical replay unit")
        seen.add(row["id"])
    terminal = {row["id"] for row in decisions if row["stage"] in TERMINAL}
    roles = {}
    for role in sorted({row["role_hint"] for row in bodies}):
        selected = [row for row in bodies if row["role_hint"] == role]
        roles[role] = dict(indexed=len(selected), terminal=sum(row["id"] in terminal for row in selected))
    return dict(indexed_bodies=len(bodies), explicitly_reviewed=len(decisions), terminal=len(terminal),
                pending=len(bodies) - len(terminal), source_files=len(files),
                parse_gap_files=sum(int(row["parse_gap_count"]) > 0 for row in files),
                stages=dict(Counter(row["stage"] for row in decisions)), roles=roles)


if __name__ == "__main__":
    print(json.dumps(report(), indent=2))
