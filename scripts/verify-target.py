#!/usr/bin/env python3
"""Fail closed on identity and PE mapping for the user-selected TH20 target."""
import argparse
import os
import sys
from pathlib import Path

from project import ROOT, verified_target


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", nargs="?", type=Path)
    args = parser.parse_args()
    try:
        path = args.executable or Path(os.environ.get("TH20_TARGET_PATH", ROOT / "resources/th20.exe"))
        data, manifest = verified_target(path)
        print(f"target OK: {path.resolve()} ({len(data)} bytes)")
        print(f"Japanese {manifest['target']['version']} / {manifest['target']['variant']}")
        print(f"sha256: {manifest['target']['sha256']}")
        return 0
    except (OSError, ValueError, KeyError) as exc:
        print(f"error: target rejected: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
