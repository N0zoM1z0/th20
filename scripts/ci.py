#!/usr/bin/env python3
"""Basic public checks without a game executable, compiler or analysis tools."""
import argparse
import ast
import json
from pathlib import Path
import re
import subprocess
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--full', action='store_true',
                        help='Also run the synthetic exact-oracle tests.')
    options = parser.parse_args()
    # The whole public tree is cheap to inspect and includes earlier PR commits,
    # even in shallow checkouts. No branch/range detection or private inputs.
    names = set(subprocess.check_output(
        ['git', 'ls-files', '--cached', '--others', '--exclude-standard', '-z'],
        cwd=ROOT).decode().split('\0')) - {''}
    private = ('.tools/', '.analysis/', 'ghidra-project/', 'build/', '.venv/', '_reference/')
    suffixes = {'.exe', '.bak', '.dll', '.dat', '.zip', '.gz', '.7z', '.rar',
                '.gpr', '.i64', '.id0', '.id1', '.obj', '.pdb'}
    for name in sorted(names):
        path = ROOT / name
        if name.startswith(private) or path.suffix.lower() in suffixes:
            raise ValueError(f'private artifact is trackable: {name}')
        if not path.is_file() or path.is_symlink():
            continue
        if name.startswith('src/') and re.search(
            r'^\s*#\s*(?:if|ifdef|ifndef|elif)\b[^\n]*(?:TH20_MATCH_EXACT|DIFFBUILD)',
            path.read_text(), re.M,
        ):
            raise ValueError(f'profile-selected source is forbidden: {name}')
        if path.suffix == '.py':
            ast.parse(path.read_text(), filename=name)
        elif path.suffix == '.json':
            json.loads(path.read_text())
        elif path.suffix == '.toml':
            tomllib.loads(path.read_text())
        elif path.suffix == '.sh' or name == 'scripts/repo-python':
            subprocess.run(['bash', '-n', str(path)], check=True)
    for command in (
        [sys.executable, 'scripts/validate-tracking.py', '--skip-target-bytes'],
        [sys.executable, 'scripts/build.py', '--check'],
        ['git', 'diff', '--check'],
        ['git', 'diff', '--cached', '--check'],
    ):
        subprocess.run(command, cwd=ROOT, check=True)
    if options.full:
        subprocess.run([sys.executable, '-m', 'unittest', 'discover', '-s', 'tests',
                        '-p', 'test_exact_oracle.py'], cwd=ROOT, check=True)
    print('Basic CI passed: public-tree syntax, ledgers, build configuration and diff checks.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, ValueError, SyntaxError, subprocess.CalledProcessError) as exc:
        print(f'error: {exc}', file=sys.stderr)
        raise SystemExit(1)
