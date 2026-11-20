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


def source_tree_paths():
    return {p.resolve() for tree in (ROOT / "src", ROOT / "probes")
            for p in tree.rglob("*") if p.is_file()}


def snapshot_name(path):
    return str(path.relative_to(ROOT) if path.is_relative_to(ROOT) else path)


def source_fingerprint(source):
    """Capture the source and repository input snapshot for a build."""
    return {snapshot_name(path): digest(path)
            for path in sorted(source_tree_paths() | {Path(source).resolve()})}


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


def verify_build_receipt(unit, *, compiler_hash=None, target_hash=None, source_paths=None):
    output = (ROOT / unit["object"]).resolve()
    output.relative_to((ROOT / "build").resolve())
    receipt = json.loads(output.with_suffix(".receipt.json").read_text())
    if compiler_hash is None:
        lock, _ = attest_compiler()
        compiler_hash = lock["files"]["bin/HostX64/x86/cl.exe"]
    if target_hash is None:
        target_hash = load_manifest("target.toml")["target"]["sha256"]
    expected = {
        "object_sha256": digest(output),
        "profile": unit["profile"],
        "compiler_sha256": compiler_hash,
        "target_sha256": target_hash,
    }
    for key, value in expected.items():
        if receipt.get(key) != value:
            raise ValueError(f"stale or incompatible build receipt: {key}; cold-build the unit")
    recorded = receipt.get("inputs")
    if not isinstance(recorded, dict):
        raise ValueError("stale or incompatible build receipt: inputs; cold-build the unit")
    headers = receipt.get("headers")
    if not isinstance(headers, dict):
        raise ValueError("stale or incompatible build receipt: headers; cold-build the unit")
    source = (ROOT / unit["source"]).resolve()
    command = receipt.get("command")
    source_argument = "Z:" + str(source).replace("/", "\\")
    if not isinstance(command, list) or len(command) < 3 or command[-3] != source_argument:
        raise ValueError("stale or incompatible build receipt: compiled source; cold-build the unit")
    included = {Path(path).resolve() for path in headers}
    # Adding or moving an unrelated translation unit does not stale every
    # original object. A newly introduced name that can shadow a captured
    # include (or the owned source) still forces a cold rebuild.
    captured_names = {path.name.casefold() for path in included | {source}}
    path_snapshot = source_tree_paths() if source_paths is None else source_paths
    current = {snapshot_name(path) for path in path_snapshot | {source}
               if path.name.casefold() in captured_names}
    recorded_names = {name for name in recorded if Path(name).name.casefold() in captured_names}
    if current != recorded_names:
        raise ValueError("stale or incompatible build receipt: inputs; cold-build the unit")
    if recorded.get(snapshot_name(source)) != digest(source):
        raise ValueError("stale or incompatible build receipt: inputs; cold-build the unit")
    for header, expected_hash in headers.items():
        header_name = snapshot_name(Path(header))
        if header_name in current and recorded.get(header_name) != expected_hash:
            raise ValueError("stale or incompatible build receipt: inputs; cold-build the unit")
        if digest(header) != expected_hash:
            raise ValueError(f"included header changed: {header}; cold-build the unit")
    return receipt
