#!/usr/bin/env python3
"""Serial, hash-attested x86 MSVC compilation with explicit flags and receipts."""
import fcntl
import json
import os
from pathlib import Path
import struct
import subprocess
import sys

from project import ROOT, attest_compiler, digest, load_manifest, source_fingerprint, toolchain_paths


def wine_path(path):
    return "Z:" + str(Path(path).resolve()).replace("/", "\\")


def native_include_path(windows_path):
    """Wine accepts case-insensitive paths; record the real Linux spelling."""
    if windows_path[:3].lower() != "z:\\":
        raise ValueError(f"include outside attested filesystem: {windows_path}")
    current = Path("/")
    for component in windows_path[3:].replace("\\", "/").split("/"):
        candidate = current / component
        if not candidate.exists():
            matches = [p for p in current.iterdir() if p.name.casefold() == component.casefold()]
            if len(matches) != 1:
                raise ValueError(f"cannot resolve Wine include path: {windows_path}")
            candidate = matches[0]
        current = candidate
    return current.resolve()


def compiler_environment():
    lock, vc, sdk = toolchain_paths()
    version = lock["sdk_version"]
    inc = [vc / "include", sdk / "Include" / version / "ucrt",
           sdk / "Include" / version / "shared", sdk / "Include" / version / "um",
           sdk / "Include" / version / "winrt", ROOT / ".tools/dxsdk-d3dx/build/native/include"]
    lib = [vc / "lib/x86", sdk / "Lib" / version / "ucrt/x86",
           sdk / "Lib" / version / "um/x86", ROOT / ".tools/dxsdk-d3dx/build/native/release/lib/x86"]
    for path in inc + lib:
        if not path.is_dir():
            raise ValueError(f"missing toolchain include/library directory: {path}")
    env = os.environ.copy()
    env.update(INCLUDE=";".join(map(wine_path, inc)), LIB=";".join(map(wine_path, lib)),
               WINEPATH=wine_path(vc / "bin/HostX64/x86") + ";" + wine_path(vc / "bin/HostX64/x64"),
               WINEDEBUG="-all", WINEPREFIX=str(ROOT / ".tools/wine"),
               WINEDLLOVERRIDES="winemenubuilder.exe=d;mscoree,mshtml=d")
    env["VSLANG"] = "1033"
    env.pop("CL", None)
    env.pop("_CL_", None)
    env.pop("LINK", None)
    return env


def compile_probe(source, output, profile):
    if not profile:
        raise ValueError("compiler flags are mandatory; no project-wide profile is assumed")
    source, output = Path(source).resolve(), Path(output).resolve()
    output.relative_to((ROOT / "build").resolve())
    if not source.is_file() or output.suffix.lower() != ".obj":
        raise ValueError("source must exist and output must be a build/**/*.obj path")
    # Inputs/outputs and exact compiler selection belong to the wrapper.
    forbidden = ("/fo", "/fd", "/fe", "/fa", "/yc", "/yu", "/mp", "/gl", "/link")
    for flag in profile:
        if not flag.startswith("/") or flag.lower().startswith(forbidden):
            raise ValueError(f"unsupported probe flag: {flag}; use ordinary COFF and explicit /Z7 debug info")
    lock, vc = attest_compiler()
    output.parent.mkdir(parents=True, exist_ok=True)
    receipt = output.with_suffix(".receipt.json")
    with (ROOT / ".tools/compiler.lock").open("a+") as gate:
        fcntl.flock(gate, fcntl.LOCK_EX | fcntl.LOCK_NB)
        output.unlink(missing_ok=True)
        receipt.unlink(missing_ok=True)
        inputs = source_fingerprint(source)
        command = ["wine", str(vc / "bin/HostX64/x86/cl.exe"), "/nologo", "/c", "/showIncludes",
                   *profile, "/I" + wine_path(ROOT / "src"), wine_path(source),
                   "/Fo" + wine_path(output), "/Fd" + wine_path(output.with_suffix(".pdb"))]
        completed = subprocess.run(command, cwd=ROOT, env=compiler_environment(),
                                   text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        headers = {}
        for line in completed.stdout.splitlines():
            if line.startswith("Note: including file:"):
                native = line.split("Note: including file:", 1)[1].strip()
                path = native_include_path(native)
                headers[str(path)] = digest(path)
            else:
                print(line)
        if completed.returncode:
            raise ValueError(f"compiler failed with exit status {completed.returncode}")
        if source_fingerprint(source) != inputs:
            raise ValueError("source changed during compilation")
        obj = output.read_bytes()
        if len(obj) < 20 or struct.unpack_from("<H", obj)[0] != 0x14C:
            raise ValueError("compiler did not emit ordinary i386 COFF")
        report = {"schema_version": 1, "command": command, "profile": profile,
                  "inputs": inputs, "object_sha256": digest(output),
                  "compiler_sha256": lock["files"]["bin/HostX64/x86/cl.exe"],
                  "compiler_version": lock["version"],
                  "headers": headers,
                  "target_sha256": load_manifest("target.toml")["target"]["sha256"]}
        receipt.write_text(json.dumps(report, indent=2) + "\n")
    print(f"i386 COFF OK: {output.relative_to(ROOT)}")


if __name__ == "__main__":
    try:
        if len(sys.argv) < 4:
            raise ValueError("usage: compile-probe.sh SOURCE OUTPUT.obj MSVC_FLAG...")
        compile_probe(sys.argv[1], sys.argv[2], sys.argv[3:])
    except (OSError, ValueError, KeyError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
