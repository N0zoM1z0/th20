#!/usr/bin/env python3
"""Reproduce the locked analysis tools and candidate x86 compiler locally."""
import argparse
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tarfile
import urllib.request
import zipfile

from project import ROOT, digest, load_manifest


def download(url, output, expected_hash):
    output.parent.mkdir(parents=True, exist_ok=True)
    if not output.exists():
        part = output.with_suffix(output.suffix + ".part")
        urllib.request.urlretrieve(url, part)
        if digest(part) != expected_hash:
            raise ValueError(f"download checksum mismatch: {url}")
        part.replace(output)
    if digest(output) != expected_hash:
        raise ValueError(f"cached download checksum mismatch: {output}")
    return output


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reference-tools", type=Path,
                        default=ROOT.parent.parent / "th095-reconstruction/th095/.tools")
    args = parser.parse_args()
    for command in ("wine", "uv", "git", "cabextract", "msiextract"):
        if shutil.which(command) is None:
            raise ValueError(f"missing prerequisite: {command}")
    lock = load_manifest("tools.lock.toml")
    tools = ROOT / ".tools"
    tools.mkdir(exist_ok=True)
    downloads = tools / "downloads"
    for name, section in (("ghidra", "ghidra"), ("jdk", "temurin_jdk")):
        destination = tools / name
        reference = args.reference_tools / name
        if destination.is_dir():
            continue
        if reference.is_dir():
            destination.symlink_to(reference.resolve(), target_is_directory=True)
            continue
        item = lock[section]
        archive = download(item["url"], downloads / item["asset"], item["sha256"])
        extracted = "ghidra_12.1.3_PUBLIC" if name == "ghidra" else "jdk-21.0.12.1+1"
        if not (tools / extracted).is_dir():
            if name == "ghidra":
                with zipfile.ZipFile(archive) as stream:
                    stream.extractall(tools)
                # Python zip extraction does not preserve executable modes.
                for path in (tools / extracted).rglob("*"):
                    if path.is_file() and (path.suffix in {".sh", ""}):
                        path.chmod(path.stat().st_mode | 0o111)
            else:
                with tarfile.open(archive) as stream:
                    stream.extractall(tools, filter="data")
        destination.symlink_to(extracted, target_is_directory=True)
    objdiff = tools / "objdiff"
    if not objdiff.is_dir():
        reference = args.reference_tools / "objdiff"
        if reference.is_dir():
            objdiff.symlink_to(reference.resolve(), target_is_directory=True)
        else:
            objdiff.mkdir()
            item = lock["objdiff"]
            exe = download(item["url"], objdiff / "objdiff-cli", item["sha256"])
            exe.chmod(0o755)
    repository = tools / "msvc-wine"
    item = lock["msvc_wine"]
    if not repository.is_dir():
        subprocess.run(["git", "clone", item["repository"], str(repository)], check=True)
    head = subprocess.check_output(["git", "-C", str(repository), "rev-parse", "HEAD"], text=True).strip()
    if head != item["commit"]:
        subprocess.run(["git", "-C", str(repository), "checkout", "--detach", item["commit"]], check=True)
    item = lock["msvc_manifest"]
    manifest = download(item["url"], tools / "vs2022-pinned.manifest", item["sha256"])
    cl = tools / "msvc/VC/Tools/MSVC" / lock["msvc"]["directory_version"] / "bin/HostX64/x86/cl.exe"
    if not cl.is_file():
        subprocess.run([sys.executable, str(repository / "vsdownload.py"),
                        "--manifest", str(manifest), "--accept-license",
                        "--msvc-version", "17.14", "--sdk-version", "10.0.26100",
                        "--architecture", "x86", "--host-arch", "x64",
                        "--with-workload", "no", "--with-asan", "no", "--with-atl", "no",
                        "--with-dia", "no", "--with-msbuild", "no", "--with-devcmd", "no",
                        "--skip-recommended", "--dest", str(tools / "msvc"),
                        "--cache", str(downloads / "msvc")], check=True, cwd=ROOT)
    item = lock["dxsdk_d3dx"]
    archive = download(item["url"], downloads / "microsoft.dxsdk.d3dx.9.29.952.8.nupkg", item["sha256"])
    if not (tools / "dxsdk-d3dx/build/native/include/d3dx9.h").is_file():
        with zipfile.ZipFile(archive) as stream:
            stream.extractall(tools / "dxsdk-d3dx")
    if not (ROOT / ".venv/bin/python").exists():
        subprocess.run(["uv", "venv", str(ROOT / ".venv")], check=True)
    subprocess.run(["uv", "pip", "install", "--python", str(ROOT / ".venv/bin/python"),
                    "-r", str(ROOT / "config/python-requirements.txt")], check=True)
    version = subprocess.run(["reccmp-project", "--version"], capture_output=True, text=True) if shutil.which("reccmp-project") else None
    if version is None or version.stdout.strip() != "reccmp-project 0.1.6":
        subprocess.run(["uv", "tool", "install", "reccmp==0.1.6"], check=True)
    subprocess.run([sys.executable, "scripts/doctor.py"], cwd=ROOT, check=True)
    print("TH20 bootstrap complete. MSVC/SDK/CRT remain candidates until target-local replay proves them.")


if __name__ == "__main__":
    try:
        main()
    except (OSError, KeyError, ValueError, subprocess.CalledProcessError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
