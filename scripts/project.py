"""Shared identity, build-input, and toolchain attestation helpers."""
import hashlib
import json
import os
from pathlib import Path
import struct
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def load_manifest(name):
    with (ROOT / "config" / name).open("rb") as stream:
        return tomllib.load(stream)


def integer(value):
    return int(value, 0) if isinstance(value, str) else int(value)


def verified_target(path=None):
    manifest = load_manifest("target.toml")
    target, expected = manifest["target"], manifest["pe"]
    path = path or Path(os.environ.get("TH20_TARGET_PATH", ROOT / "resources" / target["filename"]))
    data = Path(path).read_bytes()
    if len(data) != target["size"] or hashlib.sha256(data).hexdigest() != target["sha256"]:
        raise ValueError("target size/SHA-256 differs from the locked Steamless target")
    if hashlib.md5(data, usedforsecurity=False).hexdigest() != target["md5"]:
        raise ValueError("target MD5 differs from manifest")
    if data[:2] != b"MZ":
        raise ValueError("missing DOS signature")
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe:pe + 4] != b"PE\0\0":
        raise ValueError("missing PE signature")
    machine, count = struct.unpack_from("<HH", data, pe + 4)
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    opt = pe + 24
    if machine != 0x14C or struct.unpack_from("<H", data, opt)[0] != 0x10B:
        raise ValueError("target must be PE32/i386")
    base = struct.unpack_from("<I", data, opt + 28)[0]
    fields = {
        "image_base": base,
        "entry_point": base + struct.unpack_from("<I", data, opt + 16)[0],
        "size_of_image": struct.unpack_from("<I", data, opt + 56)[0],
        "headers_raw_size": struct.unpack_from("<I", data, opt + 60)[0],
    }
    for key, observed in fields.items():
        if observed != integer(expected[key]):
            raise ValueError(f"PE manifest mismatch: {key}")
    linker = f"{data[opt + 2]}.{data[opt + 3]}"
    if linker != expected["linker_version"] or count != len(expected["sections"]):
        raise ValueError("PE linker/section count mismatch")
    for index, section in enumerate(expected["sections"]):
        name, virtual_size, rva, raw_size, raw_offset = struct.unpack_from(
            "<8sIIII", data, opt + optional_size + index * 40)
        actual = (name.rstrip(b"\0").decode(), virtual_size, rva, raw_size, raw_offset)
        wanted = (section["name"], section["virtual_size"], integer(section["rva"]),
                  section["raw_size"], integer(section["raw_offset"]))
        if actual != wanted:
            raise ValueError(f"PE section mismatch: {section['name']}")
        if hashlib.sha256(data[raw_offset:raw_offset + raw_size]).hexdigest() != section["sha256"]:
            raise ValueError(f"PE section hash mismatch: {section['name']}")
    return data, manifest


def source_fingerprint(source):
    """Conservative freshness: source plus every canonical source/header."""
    source = Path(source).resolve()
    paths = {source}
    for tree in (ROOT / "src", ROOT / "probes"):
        paths.update(p.resolve() for p in tree.rglob("*") if p.is_file())
    result = {}
    for path in sorted(paths):
        try:
            key = str(path.relative_to(ROOT))
        except ValueError:
            key = str(path)
        result[key] = digest(path)
    return result


def toolchain_paths():
    lock = load_manifest("tools.lock.toml")["msvc"]
    installation = ROOT / ".tools" / "msvc"
    vc = installation / "VC/Tools/MSVC" / lock["directory_version"]
    sdk = installation / "Windows Kits/10"
    return lock, vc, sdk


def attest_compiler():
    lock, vc, _ = toolchain_paths()
    if not lock.get("files"):
        raise ValueError("compiler lock has no pinned files")
    for name, expected in lock["files"].items():
        path = vc / name
        if digest(path) != expected:
            raise ValueError(f"locked MSVC file differs: {name}")
    return lock, vc


def verify_build_receipt(unit):
    output = (ROOT / unit["object"]).resolve()
    output.relative_to((ROOT / "build").resolve())
    receipt = json.loads(output.with_suffix(".receipt.json").read_text())
    lock, _ = attest_compiler()
    expected = {
        "object_sha256": digest(output),
        "inputs": source_fingerprint(ROOT / unit["source"]),
        "profile": unit["profile"],
        "compiler_sha256": lock["files"]["bin/HostX64/x86/cl.exe"],
        "target_sha256": load_manifest("target.toml")["target"]["sha256"],
    }
    for key, value in expected.items():
        if receipt.get(key) != value:
            raise ValueError(f"stale or incompatible build receipt: {key}; cold-build the unit")
    for header, expected_hash in receipt.get("headers", {}).items():
        if digest(header) != expected_hash:
            raise ValueError(f"included header changed: {header}; cold-build the unit")
    return receipt
