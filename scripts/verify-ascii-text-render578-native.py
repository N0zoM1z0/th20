#!/usr/bin/env python3
"""Compatibility entry point for the original PE and current C++ source proof."""
import importlib.util
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "ascii_text_render578_source_candidate",
    ROOT / "scripts/verify-ascii-text-render578-source-candidate.py")
assert SPEC and SPEC.loader
MODULE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(MODULE)

if __name__ == "__main__":
    MODULE.main()
