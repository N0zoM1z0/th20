#!/usr/bin/env python3
"""Serial unmodified reference TU diagnostics; compilation confers no credit."""
import argparse
import csv
import hashlib
import json
from pathlib import Path
import subprocess
import sys

from project import ROOT, attest_compiler, digest, load_manifest, verified_target, verify_build_receipt

PROFILE = ["/nologo", "/c", "/std:c++20", "/Od", "/Ob0", "/GS-", "/Gy",
           "/Zl", "/arch:SSE2", "/fp:precise", "/EHsc", "/utf-8", "/MT"]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--module", action="append", default=[])
    parser.add_argument("--resume", action="store_true")
    args = parser.parse_args()
    pin = load_manifest("reference.toml")
    reference = ROOT / pin["local_path"]
    # runtime_core exports the scheduler include directory through its CMake
    # dependency. Record the corresponding include in this diagnostic recipe.
    scheduler_include = reference / "source_reconstruction/core_scheduler"
    include_profile = PROFILE + ["/IZ:" + str(scheduler_include.resolve()).replace("/", "\\")]
    if subprocess.check_output(["git", "-C", str(reference), "rev-parse", "HEAD"], text=True).strip() != pin["commit"]:
        raise ValueError("reference commit differs")
    if subprocess.check_output(["git", "-C", str(reference), "status", "--porcelain"], text=True):
        raise ValueError("reference checkout is dirty")
    verified_target()
    compiler, _ = attest_compiler()
    with (ROOT / "config/reference-source-files.csv").open(newline="") as stream:
        files = [row for row in csv.DictReader(stream)
                 if row["role_hint"] == "reconstruction-candidate"
                 and Path(row["reference_path"]).suffix == ".cpp"]
    if args.module:
        files = [row for row in files if (row["reference_path"].split("/")[1]
                 if row["reference_path"].startswith("source_reconstruction/")
                 else row["reference_path"].split("/")[0]) in args.module]
    output = ROOT / ".analysis/reference-functions/compilations"
    output.mkdir(parents=True, exist_ok=True)
    for index, row in enumerate(files, 1):
        relative = row["reference_path"]
        source = reference / relative
        if digest(source) != row["file_sha256"]:
            raise ValueError(f"reference source inventory is stale: {relative}")
        profile = list(include_profile)
        if relative == "source_reconstruction/archive/verify.cpp":
            # These string macros are declared by archive/CMakeLists.txt;
            # preserve the recipe instead of editing unmodified reference code.
            for extension in ("cpp", "hpp"):
                fingerprint = digest(source.parent / f"archive.{extension}")
                profile.append(f'/DTH20_ARCHIVE_{extension.upper()}_SHA256="{fingerprint}"')
        key = hashlib.sha256(relative.encode()).hexdigest()[:20]
        report = output / f"{key}.json"
        identity = dict(reference_commit=pin["commit"], reference_path=relative,
                        file_sha256=row["file_sha256"], profile=profile,
                        compiler_sha256=compiler["files"]["bin/HostX64/x86/cl.exe"],
                        target_sha256=pin["target_sha256"])
        object_path = ROOT / "build/reference-probes" / f"{key}.obj"
        if args.resume and report.exists():
            old = json.loads(report.read_text())
            if old.get("result") == "compiled" and all(old.get(field) == value for field, value in identity.items()):
                try:
                    if digest(object_path) != old.get("object_sha256") or digest(object_path.with_suffix(".receipt.json")) != old.get("receipt_sha256"):
                        raise ValueError("cached object/receipt digest differs")
                    verify_build_receipt(dict(object=str(object_path.relative_to(ROOT)),
                                              source=str(source.relative_to(ROOT)), profile=profile))
                except (OSError, ValueError, KeyError):
                    pass  # Retry missing/stale objects, headers and receipts.
                else:
                    print(f"[{index}/{len(files)}] cached compiled: {relative}", flush=True)
                    continue
        command = [str(ROOT / "scripts/compile-probe.sh"), str(source), str(object_path), *profile]
        with (output / f"{key}.log").open("w") as log:
            process = subprocess.run(command, cwd=ROOT, stdout=log, stderr=subprocess.STDOUT)
        result = dict(identity, result="compiled" if process.returncode == 0 else "compile-error",
                      exit_code=process.returncode, object=str(object_path.relative_to(ROOT)),
                      log=f".analysis/reference-functions/compilations/{key}.log")
        if process.returncode == 0:
            result["object_sha256"] = digest(object_path)
            result["receipt_sha256"] = digest(object_path.with_suffix(".receipt.json"))
        report.write_text(json.dumps(result, indent=2) + "\n")
        print(f"[{index}/{len(files)}] {result['result']}: {relative}", flush=True)
    print("Reference compiler diagnostics complete for selected TUs; no semantic review or exact credit inferred.")


if __name__ == "__main__":
    main()
