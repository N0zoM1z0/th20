#!/usr/bin/env python3
"""Strictly replay canonical units, with a cold build unless explicitly skipped."""
import argparse
import subprocess
import sys
from project import ROOT, load_manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", action="append", default=[])
    parser.add_argument("--existing-objects", action="store_true",
                        help="verify existing objects and receipts without compiling")
    args = parser.parse_args()
    subprocess.run([sys.executable, "scripts/build.py", "--check"], cwd=ROOT, check=True)
    units = load_manifest("match-units.toml")["units"]
    if args.source:
        unknown = set(args.source) - {u["source"] for u in units.values()}
        if unknown:
            raise ValueError(f"unconfigured replay sources: {sorted(unknown)}")
        units = {k: v for k, v in units.items() if v["source"] in args.source}
    objects = set()
    for name, unit in units.items():
        key = (unit["source"], unit["object"], tuple(unit["profile"]))
        if key not in objects:
            if not args.existing_objects:
                subprocess.run([sys.executable, "scripts/build.py", "--unit", name], cwd=ROOT, check=True)
            objects.add(key)
        subprocess.run([sys.executable, "scripts/compare-coff-function.py", "--unit", name], cwd=ROOT, check=True)
    mode = "existing" if args.existing_objects else "cold"
    print(f"Exact replay: {len(units)}/{len(units)} units, {len(objects)} {mode} objects")
    if not units:
        print("No configured units; this establishes no exact reconstruction credit.")


if __name__ == "__main__":
    try:
        main()
    except (OSError, KeyError, ValueError, subprocess.CalledProcessError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
