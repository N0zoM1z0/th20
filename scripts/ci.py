#!/usr/bin/env python3
"""Target-independent control-plane, synthetic oracle, and public-tree checks."""
import os
from pathlib import Path
import re
import subprocess
import sys
from project import ROOT


def main():
    files = subprocess.check_output(["git", "ls-files", "--cached", "--others", "--exclude-standard", "-z"], cwd=ROOT).decode().split("\0")
    private = (".tools/", ".analysis/", "ghidra-project/", "build/", ".venv/", "_reference/")
    suffixes = {".exe", ".bak", ".dll", ".dat", ".zip", ".7z", ".rar", ".gpr", ".i64", ".id0", ".id1", ".obj", ".pdb"}
    for relative in files:
        if relative and (relative.startswith(private) or Path(relative).suffix.lower() in suffixes):
            raise ValueError(f"private artifact is trackable: {relative}")
    for path in (ROOT / "src").rglob("*"):
        if path.is_file() and re.search(r"^\s*#\s*(?:if|ifdef|ifndef|elif)\b[^\n]*(?:TH20_MATCH_EXACT|DIFFBUILD)", path.read_text(), re.M):
            raise ValueError(f"profile-selected source is forbidden: {path}")
    commands = [[sys.executable, "-m", "py_compile", *sorted(f for f in files if f.endswith(".py"))],
                [sys.executable, "scripts/validate-tracking.py", "--skip-target-bytes"],
                [sys.executable, "scripts/build.py", "--check"],
                [sys.executable, "scripts/validate-reference-review.py"],
                [sys.executable, "scripts/report-reference-functions.py"],
                [sys.executable, "-m", "unittest", "discover", "-s", "tests", "-v"],
                [sys.executable, "scripts/progress.py", "--check"], ["git", "diff", "--check"]]
    commands += [["bash", "-n", f] for f in files if f.endswith(".sh") or f == "scripts/repo-python"]
    for command in commands:
        subprocess.run(command, cwd=ROOT, check=True)
    print("Public CI passed; no private target, compiler, or Ghidra project required.")


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError, subprocess.CalledProcessError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
