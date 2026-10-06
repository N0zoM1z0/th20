#!/usr/bin/env python3
"""Attest installed analysis/compiler versions and locked critical binaries."""
import argparse
import importlib.util
import subprocess
import sys
from project import ROOT, attest_compiler, digest, load_manifest


def check_analysis():
    lock = load_manifest("tools.lock.toml")
    for path, expected in lock["analysis_files"].items():
        if digest(ROOT / ".tools" / path) != expected:
            raise ValueError(f"analysis tool fingerprint mismatch: {path}")
    props = (ROOT / ".tools/ghidra/Ghidra/application.properties").read_text()
    if "application.version=12.1.3" not in props:
        raise ValueError("Ghidra version mismatch")
    print("analysis OK: Ghidra 12.1.3, Temurin JDK 21.0.12.1+1, objdiff 3.8.0; locked binary fingerprints")


def check_compiler():
    lock, vc = attest_compiler()
    spec = importlib.util.spec_from_file_location("compile_probe", ROOT / "scripts/compile-probe.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    for tool, expected in (("cl.exe", lock["version"]), ("link.exe", lock["linker_version"])):
        command = ["wine", str(vc / "bin/HostX64/x86" / tool)]
        result = subprocess.run(command, env=module.compiler_environment(), text=True,
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=90)
        if f"Version {expected}" not in result.stdout:
            raise ValueError(f"{tool} did not report locked version {expected}: {result.stdout[:500]}")
        print(f"compiler OK: {tool} {expected} targeting x86")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--analysis", action="store_true")
    parser.add_argument("--compiler", action="store_true")
    args = parser.parse_args()
    try:
        if args.analysis or not args.compiler:
            check_analysis()
        if args.compiler or not args.analysis:
            check_compiler()
    except (OSError, KeyError, ValueError, subprocess.TimeoutExpired) as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
