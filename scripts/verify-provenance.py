#!/usr/bin/env python3
"""Reproduce local variant identification using the pinned independent registry."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import sys
import urllib.request
from project import ROOT, digest, load_manifest, verified_target, integer


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--fetch", action="store_true", help="fetch immutable registry snapshot")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    identities = load_manifest("version-identities.toml")
    registry = ROOT / ".analysis/bootstrap/versions.js"
    if args.fetch:
        data = urllib.request.urlopen(identities["registry_url"], timeout=60).read()
        if hashlib.sha256(data).hexdigest() != identities["registry_sha256"]:
            raise ValueError("registry snapshot hash mismatch")
        registry.parent.mkdir(parents=True, exist_ok=True)
        registry.write_bytes(data)
    if digest(registry) != identities["registry_sha256"]:
        raise ValueError("registry snapshot missing or changed; run with --fetch")
    text = registry.read_text()
    target_bytes, manifest = verified_target()
    embedded_labels = []
    for label in manifest["provenance"].get("embedded_labels", []):
        address = integer(label["address"])
        expected = (label["value"] + "\0").encode(label["encoding"])
        for section in manifest["pe"]["sections"]:
            start = integer(manifest["pe"]["image_base"]) + integer(section["rva"])
            if start <= address and address + len(expected) <= start + section["raw_size"]:
                offset = integer(section["raw_offset"]) + address - start
                if target_bytes[offset:offset + len(expected)] != expected:
                    raise ValueError(f"embedded version label differs at {address:#x}")
                embedded_labels.append(label)
                break
        else:
            raise ValueError(f"embedded version label is not file-backed: {address:#x}")
    files = {
        "steamless": ROOT / "resources/th20.exe",
        "steam_original": ROOT / manifest["provenance"]["steam_original_path"],
        "custom": ROOT.parent / "game_exe/custom.exe",
    }
    rows = []
    for variant, path in files.items():
        expected = identities[variant]
        observed = digest(path)
        if observed != expected["sha256"]:
            raise ValueError(f"local {variant} does not match the pinned identity")
        game = "th20_custom" if variant == "custom" else "th20"
        match = re.search('"' + observed + r'"\s*:\s*\[\s*"' + game +
                          r'"\s*,\s*"v([^\"]+)"\s*,\s*"\(([^\"]+)\)"', text)
        if not match or match.groups() != (expected["version"], expected["label"]):
            raise ValueError(f"pinned registry does not identify {variant}")
        rows.append({"variant": variant, "version": expected["version"],
                     "label": expected["label"], "sha256": observed, "size": path.stat().st_size})
    report = {"selected": "steamless", "files": rows,
              "embedded_labels": embedded_labels,
              "registry_url": identities["registry_url"],
              "official_checksums_available": False,
              "non_steam_original_sha256": identities["non_steam_original"]["sha256"]}
    output = ROOT / ".analysis/bootstrap/target-provenance.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n")
    if args.json:
        print(json.dumps(report, indent=2))
    else:
        for row in rows:
            print(f"{row['variant']}: Japanese v{row['version']} / {row['label']} / SHA-256 verified")
        if embedded_labels:
            print("Embedded title/replay label: 1.00c; registry/package identification: 1.00a. Same locked executable, separate evidence.")
        print("Exact oracle: user-selected Steamless; independent registry evidence, not publisher-issued checksums.")


if __name__ == "__main__":
    try:
        main()
    except (OSError, KeyError, ValueError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
