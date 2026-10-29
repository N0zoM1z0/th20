#!/usr/bin/env python3
"""Dry-run-first retirement of reproducible, noncanonical TH20 build products.

Never purge the entire build tree. Immutable target, canonical MSVC .obj and
matching .receipt.json, active unclosed boss probes, and original evidence
are protected. Audited deletions require explicit --apply.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import subprocess
import tomllib
from pathlib import Path

TARGET_SHA256 = "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"

# Active unresolved complete-game roots, not historical successful probes.
# Revisit this list against native source/frontier evidence at every cleanup.
ACTIVE_PROBE_DIRECTORIES = frozenset(
    {
        # Bullet command-11 / emitter / drawing / intrusive resource ABI.
        "core255-probes", "core263-probes", "core264-probes",
        "core285-probes", "core287-probes", "core288-probes",
        "core290-probes", "core291-probes", "core292-probes",
        "core371-probes", "core372-probes", "core373-probes",
        "core374-probes", "core375-probes",
        # Large Player frame / movement and currently unresolved SSE spills.
        "core360-probes", "core363-pos", "core364-probes",
        "core418-probes", "core419-probes", "core428-probes",
        "core456-probes", "core457-probes", "core459-probes",
        # Still-open EnemyState mesh and archive compression.
        "core384-probes", "core388-probes",
    }
)


def digest(path: Path) -> str:
    result = hashlib.sha256()
    with path.open("rb") as source:
        for chunk in iter(lambda: source.read(1024 * 1024), b""):
            result.update(chunk)
    return result.hexdigest()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--apply",
        action="store_true",
        help="Delete reviewed disposable build products and retain SHA-256 inventory.",
    )
    options = parser.parse_args()

    root = Path(__file__).resolve().parent.parent
    assert Path.cwd().resolve() == root, "Run from the TH20 repository root"
    assert (root / ".git").is_dir() and (root / "AGENTS.md").is_file()
    manifest = tomllib.loads((root / "config/match-units.toml").read_text())
    units = manifest["units"]
    canonical_objects = {Path(u["object"]) for u in units.values()}
    canonical_receipts = {p.with_suffix(".receipt.json") for p in canonical_objects}
    protected = canonical_objects | canonical_receipts
    assert len(units) > 1000 and len(canonical_objects) > 200
    assert all((root / path).is_file() for path in protected)
    assert digest(root / "resources/th20.exe") == TARGET_SHA256

    # Never allow tracked files to enter any deletion set.
    tracked = subprocess.check_output(["git", "ls-files", "--", "build"], text=True)
    assert not tracked.strip(), "Unexpected tracked paths beneath build/"

    original_hashes = {str(path): digest(root / path) for path in sorted(protected)}
    build = root / "build"
    assert build.is_dir() and not build.is_symlink()
    candidates = []
    active_files = []
    for path in sorted(build.rglob("*")):
        if path.is_symlink() or not path.is_file():
            continue
        relative = path.relative_to(root)
        if relative in protected:
            continue
        assert relative.parts[0] == "build"
        if relative.parts[1] in ACTIVE_PROBE_DIRECTORIES:
            active_files.append(relative)
            continue
        # Other file types may be hand-maintained analysis inputs, not
        # independently disposable MSVC codegen artifacts.
        if path.suffix != ".obj" and not path.name.endswith(".receipt.json"):
            continue
        candidates.append(relative)

    files = []
    for relative in candidates:
        path = root / relative
        files.append(
            {"path": relative.as_posix(), "bytes": path.stat().st_size, "sha256": digest(path)}
        )

    bytes_retired = sum(item["bytes"] for item in files)
    print(
        f"{'APPLY' if options.apply else 'DRY RUN'}: {len(files)} disposable files, "
        f"{bytes_retired:,} bytes ({bytes_retired / 1048576:.2f} MiB)"
    )
    print(
        f"PROTECTED: {len(canonical_objects)} canonical objects, "
        f"{len(canonical_receipts)} receipts, {len(active_files)} active probe files"
    )

    if options.apply and files:
        audit = root / ".analysis/core497-build-retirement-inventory.json"
        assert audit.parent.is_dir()
        # Write durable private inventory *before* deleting any paths.
        audit.write_text(
            json.dumps(
                {
                    "immutable_target_sha256": TARGET_SHA256,
                    "canonical_objects": len(canonical_objects),
                    "canonical_receipts": len(canonical_receipts),
                    "protected_path_sha256": original_hashes,
                    "active_probe_directories": sorted(ACTIVE_PROBE_DIRECTORIES),
                    "deleted_files": len(files),
                    "deleted_bytes": bytes_retired,
                    "removed": files,
                },
                indent=2,
            )
            + "\n"
        )
        for item in files:
            path = root / item["path"]
            assert path.is_file() and not path.is_symlink()
            path.unlink()
        # Remove empty noncanonical build subdirectories, not entire build/.
        for directory in sorted(
            (p for p in build.rglob("*") if p.is_dir() and not p.is_symlink()),
            key=lambda p: len(p.parts),
            reverse=True,
        ):
            if not any(directory.iterdir()):
                directory.rmdir()

        assert digest(root / "resources/th20.exe") == TARGET_SHA256
        assert all(digest(root / path) == sha for path, sha in original_hashes.items())
        assert all(not (root / item["path"]).exists() for item in files)
        print(f"POST-CHECK: original target and all {len(protected)} protected SHA256 hashes unchanged")
        print(f"PRIVATE AUDIT: {audit.relative_to(root)}")


if __name__ == "__main__":
    main()
