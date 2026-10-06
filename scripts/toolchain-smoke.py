#!/usr/bin/env python3
"""Cold-compile, link, format-check, and execute an infrastructure probe."""
import importlib.util
import json
import shutil
import struct
import subprocess
import sys
from project import ROOT, attest_compiler, digest


def main():
    spec = importlib.util.spec_from_file_location("compile_probe", ROOT / "scripts/compile-probe.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    profile = ["/O2", "/Ob1", "/MT", "/EHsc", "/GR-", "/Gy", "/Z7"]
    source = ROOT / "probes/toolchain-smoke.cpp"
    obj = ROOT / "build/probes/toolchain-smoke.obj"
    exe = obj.with_suffix(".exe")
    module.compile_probe(source, obj, profile)
    lock, vc = attest_compiler()
    env = module.compiler_environment()
    command = ["wine", str(vc / "bin/HostX64/x86/link.exe"), "/NOLOGO", "/MACHINE:X86",
               "/SUBSYSTEM:CONSOLE", "/INCREMENTAL:NO", "/OPT:REF", "/OPT:ICF",
               "/OUT:" + module.wine_path(exe), module.wine_path(obj),
               "kernel32.lib", "user32.lib", "gdi32.lib", "ole32.lib", "oleaut32.lib",
               "dinput8.lib", "dsound.lib", "d3d9.lib", "d3dx9.lib", "winmm.lib",
               "xinput.lib", "gdiplus.lib", "dxguid.lib"]
    exe.unlink(missing_ok=True)
    result = subprocess.run(command, env=env, cwd=ROOT, capture_output=True, text=True, timeout=90)
    if result.returncode:
        raise ValueError(f"link failed: {result.stdout}\n{result.stderr}")
    data = exe.read_bytes()
    offset = struct.unpack_from("<I", data, 0x3c)[0]
    if (data[offset:offset + 4] != b"PE\0\0" or struct.unpack_from("<H", data, offset + 4)[0] != 0x14c
            or struct.unpack_from("<H", data, offset + 24)[0] != 0x10b):
        raise ValueError("linked probe is not PE32/i386")
    dll = ROOT / ".tools/dxsdk-d3dx/build/native/release/bin/x86/D3DX9_43.dll"
    shutil.copyfile(dll, exe.parent / "D3DX9_43.dll")
    env["WINEDLLOVERRIDES"] += ";d3dx9_43=n,b"
    run = subprocess.run(["wine", str(exe)], env=env, cwd=exe.parent,
                         capture_output=True, text=True, timeout=90)
    if run.returncode or "TH20 toolchain smoke: MSVC=194435211 pointers=4 result=1218640798" not in run.stdout:
        raise ValueError(f"probe runtime failed: {run.stdout}\n{run.stderr}")
    report = {"result": "passed", "compiler": lock["version"], "linker": lock["linker_version"],
              "profile": profile, "link_command": command, "pe_machine": "i386", "pe_format": "PE32",
              "source_sha256": digest(source), "object_sha256": digest(obj),
              "executable_sha256": digest(exe), "runtime_output": run.stdout.strip(),
              "reconstruction_credit": 0}
    output = ROOT / ".analysis/bootstrap/toolchain-smoke.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n")
    print(run.stdout.strip())
    print("Smoke passed: MSVC x86 C++/Win32/DirectX/UCRT compile, PE32 link, and Wine execution.")
    print("This probe is infrastructure validation; no TH20 function receives exact credit.")


if __name__ == "__main__":
    try:
        main()
    except (OSError, KeyError, ValueError, subprocess.TimeoutExpired) as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
