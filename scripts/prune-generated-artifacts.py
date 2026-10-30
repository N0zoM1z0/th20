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
import re
import subprocess
import tomllib
from pathlib import Path

TARGET_SHA256 = "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"

# Active unresolved complete-game roots, not historical successful probes.
# Revisit this list against native source/frontier evidence at every cleanup.
ACTIVE_PROBE_DIRECTORIES = frozenset(
    {
        # Historical exact command-11/emitter probes retained as selected
        # original-CFG comparison inputs for unresolved Bullet draw/dispatch.
        "core255-probes", "core263-probes", "core264-probes",
        "core285-probes", "core287-probes", "core288-probes",
        "core290-probes", "core291-probes", "core292-probes",
        "core371-probes", "core372-probes", "core373-probes",
        "core374-probes", "core375-probes",
        # Large Player frame / movement and currently unresolved SSE spills.
        "core360-probes", "core363-pos", "core364-probes",
        "core418-probes", "core419-probes", "core428-probes",
        "core456-probes", "core457-probes", "core459-probes",
        # Still-open EnemyState mesh and historical archive codegen evidence.
        # The original archive LZSS compressor itself is now whole strict exact.
        "core384-probes", "core388-probes",
        # Selected original Bullet emitter codegen benchmarks. The 3,735B
        # emitter is now STRICT EXACT; these are dated private diagnostics,
        # not an indication that its own native body remains nonexact.
        "core601-probes", "core614-probes", "core616-probes",
        "core620-probes", "core621-probes", "core622-probes",
        "core626-probes",
        # The adjacent nonexact Player movement and 3,111B frame probes.
        "core541-probes", "core558-probes",
        # CORE/RECON-894 active still-NONEXACT source frontier: original
        # 5,993B Animation Draw, Player 555B, 1,486B rotated corner,
        # 104B polygon wrapper and 827B dynamics. Keep the actual working
        # candidate objects, not just their code/proof text. Historical
        # now-exact 120B/233B/296B/2,169B/4,347B variants can be retired.
        "core835-probe", "core872-probe", "core873-probe",
        "core877-probe", "core881-probe", "core894-probe",
        "core897-probe", "core898-probe",
    }
)


def digest(path: Path) -> str:
    result = hashlib.sha256()
    with path.open("rb") as source:
        for chunk in iter(lambda: source.read(1024 * 1024), b""):
            result.update(chunk)
    return result.hexdigest()


def documented_native_probes(root: Path) -> set[Path]:
    """Protect actual build objects directly named by tracked source/proof text.

    A Markdown/script citation to an exact private .obj path is stronger
    evidence of current provenance than a dated directory-number allowlist.
    This guard protects *individual* referenced artifacts without retaining
    thousands of unused variants in the same experimental directory.
    Missing historical paths cannot be deleted and require no fake entries.
    """
    paths = subprocess.check_output(
        ["git", "ls-files", "-z", "--", "README.md", "docs", "scripts"],
        cwd=root,
    ).decode().split("\0")
    # All artifacts remain confined to build/, never accept arbitrary file
    # paths from a Markdown comment as external deletion/protection requests.
    pattern = re.compile(
        r"(?<![\w/])build/[a-zA-Z0-9_.-]+/[a-zA-Z0-9_.-]+"
        r"(?:\.receipt\.json|\.obj)\b"
    )
    references: set[Path] = set()
    for name in paths:
        if not name:
            continue
        document = root / name
        if not document.is_file() or document.suffix not in {
            ".md", ".py", ".toml", ".json", ".txt",
        }:
            continue
        for raw in pattern.findall(document.read_text(errors="replace")):
            relative = Path(raw)
            if (root / relative).is_file() and not (root / relative).is_symlink():
                references.add(relative)
    return references


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--apply",
        action="store_true",
        help="Delete reviewed disposable build products and retain SHA-256 inventory.",
    )
    parser.add_argument(
        "--inventory",
        type=str,
        help=(
            "Unique new .analysis/*.json audit inventory for --apply; "
            "never overwrite a prior cleanup audit."
        ),
    )
    options = parser.parse_args()

    root = Path(__file__).resolve().parent.parent
    assert Path.cwd().resolve() == root, "Run from the TH20 repository root"
    assert (root / ".git").is_dir() and (root / "AGENTS.md").is_file()
    manifest = tomllib.loads((root / "config/match-units.toml").read_text())
    units = manifest["units"]
    canonical_objects = {Path(u["object"]) for u in units.values()}
    canonical_receipts = {p.with_suffix(".receipt.json") for p in canonical_objects}
    proof_references = documented_native_probes(root)
    protected = canonical_objects | canonical_receipts | proof_references
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
        f"{len(canonical_receipts)} receipts, "
        f"{len(proof_references)} referenced proof artifacts, "
        f"{len(active_files)} active probe files"
    )

    if options.apply and files:
        if not options.inventory:
            parser.error("--apply requires a unique --inventory .analysis/*.json path")
        relative_audit = Path(options.inventory)
        if (
            relative_audit.is_absolute()
            or len(relative_audit.parts) != 2
            or relative_audit.parts[0] != ".analysis"
            or relative_audit.suffix != ".json"
            or any(part in (".", "..") for part in relative_audit.parts)
        ):
            parser.error("inventory must be a new top-level .analysis/*.json file")
        audit = root / relative_audit
        assert audit.parent.is_dir() and not audit.parent.is_symlink()
        if audit.exists() or audit.is_symlink():
            parser.error(f"audit inventory already exists, refusing overwrite: {audit}")
        # Write durable private inventory *before* deleting any paths.
        audit.write_text(
            json.dumps(
                {
                    "immutable_target_sha256": TARGET_SHA256,
                    "canonical_objects": len(canonical_objects),
                    "canonical_receipts": len(canonical_receipts),
                    "protected_path_sha256": original_hashes,
                    "tracked_proof_artifacts": sorted(map(str, proof_references)),
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
