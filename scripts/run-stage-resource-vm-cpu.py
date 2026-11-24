#!/usr/bin/env python3
"""Compare the maintained StageResource VM state machine with original TH20 code."""
from __future__ import annotations

import hashlib
import importlib.util
import json
import subprocess
import shutil
import sys
from pathlib import Path

from project import ROOT, attest_compiler


def digest_bundle(paths: list[Path]) -> str:
    digest = hashlib.sha256()
    for path in paths:
        relative = path.relative_to(ROOT).as_posix().encode("utf-8")
        content = path.read_bytes()
        digest.update(len(relative).to_bytes(4, "little"))
        digest.update(relative)
        digest.update(len(content).to_bytes(8, "little"))
        digest.update(content)
    return digest.hexdigest()


def main() -> int:
    spec = importlib.util.spec_from_file_location("compile_probe", ROOT / "scripts/compile-probe.py")
    if spec is None or spec.loader is None:
        raise RuntimeError("cannot load the attested compiler driver")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)

    profile = [
        "/std:c++20", "/EHsc", "/Od", "/Ob0", "/GS-", "/Gy",
        "/arch:SSE2", "/fp:strict", "/W3",
        "/DTH20_NATIVE_CORE_SHA256=\"unused\"",
        "/I" + module.wine_path(ROOT / "_reference/Touhou20/include"),
        "/I" + module.wine_path(ROOT / "_reference/Touhou20/native_recovered"),
        "/I" + module.wine_path(ROOT / ".tools/dxsdk-d3dx/include"),
    ]
    sources = [
        ROOT / "tests/stage_resource_vm_cpu_compare.cpp",
        ROOT / "src/StageResourceScript.cpp",
        ROOT / "src/StageResourceFog.cpp",
        ROOT / "src/StageResourceInterruptAnimations.cpp",
        ROOT / "src/StageResourcePrimaryRotationFlag.cpp",
        ROOT / "src/StageResourceGlobals.cpp",
        ROOT / "src/StageResourceMeshUpdate.cpp",
        ROOT / "src/StageResourceObjectUpdate.cpp",
        ROOT / "src/AnimationPoolUpdate.cpp",
        ROOT / "src/RendererDeviceResetHooks108.cpp",
        ROOT / "src/RendererStageDrawReset.cpp",
        ROOT / "src/AnimationIsActive.cpp",
        ROOT / "src/AnimationObjectDrawLeaves.cpp",
        ROOT / "src/StageResourceObjectVisibility.cpp",
        ROOT / "src/StageResourceObjectDraw.cpp",
        ROOT / "src/AnimationClearFlag02.cpp",
        ROOT / "src/Matrix4Identity.cpp",
        ROOT / "src/StageResourceUpdate.cpp",
        ROOT / "src/AnimationParticleGridNormalize202.cpp",
        ROOT / "src/Interpolation.cpp",
        ROOT / "src/FogValue.cpp",
        ROOT / "src/Easing.cpp",
        ROOT / "src/ScalarMath.cpp",
        ROOT / "src/Angle.cpp",
        ROOT / "src/Vector2.cpp",
        ROOT / "src/Matrix4.cpp",
        ROOT / "src/AnmVariables.cpp",
        ROOT / "src/IntegerTriple.cpp",
        ROOT / "_reference/Touhou20/src/binary.cpp",
        ROOT / "_reference/Touhou20/src/pe.cpp",
        ROOT / "src/Timer.cpp",
        ROOT / "src/ClockScalar.cpp",
        ROOT / "src/NativeFloatGlobals.cpp",
        ROOT / "src/Vector3.cpp",
        ROOT / "src/MotionMath.cpp",
        ROOT / "src/CollisionGeometry.cpp",
    ]
    output_dir = ROOT / "build/gpt-web-stage-resource/cpu-compare"
    output_dir.mkdir(parents=True, exist_ok=True)
    objects = []
    for index, source in enumerate(sources):
        output = output_dir / f"{index:02d}-{source.stem}.obj"
        module.compile_probe(source, output, profile)
        objects.append(output)

    lock, vc = attest_compiler()
    env = module.compiler_environment()
    executable = output_dir / "stage-resource-vm-cpu-compare.exe"
    report = output_dir / "stage-resource-vm-cpu-report.json"
    shutil.copy2(ROOT / ".tools/dxsdk-d3dx/build/native/release/bin/x86/D3DX9_43.dll",
                 output_dir / "D3DX9_43.dll")
    wine = module.shared_command("wine")
    link = [
        *wine, str(vc / "bin/HostX64/x86/link.exe"), "/NOLOGO", "/MACHINE:X86",
        "/SUBSYSTEM:CONSOLE", "/INCREMENTAL:NO", "/OPT:REF", "/OPT:ICF",
        "/BASE:0x10000000", "/DYNAMICBASE:NO", "/OUT:" + module.wine_path(executable),
        *[module.wine_path(path) for path in objects], "kernel32.lib", "bcrypt.lib",
        module.wine_path(ROOT / ".tools/dxsdk-d3dx/build/native/release/lib/x86/d3dx9.lib"),
    ]
    result = subprocess.run(link, env=env, cwd=ROOT, capture_output=True, text=True, timeout=180)
    if result.returncode:
        raise ValueError(f"StageResource VM oracle link failed:\n{result.stdout}\n{result.stderr}")

    run = subprocess.run(
        [*wine, module.wine_path(executable), module.wine_path(ROOT / "resources/th20.exe"),
         module.wine_path(report)],
        env=env, cwd=ROOT, capture_output=True, text=True, timeout=300,
    )
    if run.stdout:
        print(run.stdout.strip())
    if run.stderr:
        print(run.stderr.strip(), file=sys.stderr)
    if "Unhandled page fault" in run.stderr or "Unhandled exception" in run.stderr:
        raise ValueError("StageResource VM oracle process faulted after producing its report")
    if run.returncode:
        raise ValueError(f"StageResource VM CPU oracle failed with exit status {run.returncode}")
    data = json.loads(report.read_text(encoding="utf-8"))
    if data.get("status") != "passed" or data.get("failed") != 0:
        raise ValueError(f"StageResource VM CPU oracle reported mismatches: {data}")
    source_inputs = [path for path in sources if path != ROOT / "tests/stage_resource_vm_cpu_compare.cpp"] + [
        ROOT / "src/StageResource.hpp",
        ROOT / "src/Animation.hpp",
        ROOT / "src/Matrix4.hpp",
        ROOT / "src/RenderMesh.hpp",
        ROOT / "src/Viewport.hpp",
        ROOT / "src/Graphics.hpp",
        ROOT / "src/StageResourceUpdateAdapters.hpp",
        ROOT / "src/StageResourceUpdateAdapters.cpp",
        ROOT / "src/AnimationRuntimeOwner.hpp",
        ROOT / "src/NativeAnimationResetHooksView.hpp",
        ROOT / "src/NativeGraphicsModeAction.hpp",
        ROOT / "src/Graphics.hpp",
        ROOT / "src/StageResourceDrawAdapters.hpp",
        ROOT / "src/StageResourceObjectVisibility.hpp",
        ROOT / "src/Angle.hpp",
        ROOT / "src/Vector3.hpp",
        ROOT / "src/Timer.hpp",
        ROOT / "src/ClockScalar.hpp",
        ROOT / "src/ScalarMath.hpp",
        ROOT / "src/Interpolation.hpp",
        ROOT / "src/FogValue.hpp",
    ]
    summary = {
        "status": "passed",
        "checks": data["checks"],
        "failed": data["failed"],
        "source_sha256": digest_bundle(source_inputs),
        "source_files": [path.relative_to(ROOT).as_posix() for path in source_inputs],
        "header_sha256": module.digest(ROOT / "src/StageResource.hpp"),
        "test_sha256": module.digest(ROOT / "tests/stage_resource_vm_cpu_compare.cpp"),
        "compiler": lock["version"],
        "linker": lock["linker_version"],
        "scope": data["scope"],
        "report": str(report.relative_to(ROOT)),
        "reconstruction_credit": 0,
    }
    receipt = ROOT / ".analysis/stage-resource-vm-cpu-compare.json"
    receipt.parent.mkdir(parents=True, exist_ok=True)
    receipt.write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print(f"PASS original PE vs maintained StageResource VM: {data['checks']} checks, 0 failures")
    print("Semantic CPU-oracle evidence only; no byte-exactness claim is implied.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, ValueError, KeyError, RuntimeError, subprocess.TimeoutExpired) as error:
        print(f"error: {error}", file=sys.stderr)
        raise SystemExit(1)
