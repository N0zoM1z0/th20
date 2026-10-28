# CORE/CLEANUP-300 — scoped artifact retirement and exact-proof protection

**Date:** 2026-10-28. No native reconstruction source, profile, exactness
claim, canonical manifest or original comparison target was changed.
The cleanup was performed only after inspecting the dirty source tree,
reconciling the three provisional CORE298 public-header declarations,
and preserving the entire experimental patch and private source under
`.analysis/core298-*`. Those prototypes have not been admitted as
verified ABI declarations; source control returned to the last exact
state without losing the hypotheses.

## Measured retirement

| Ignored file category | Deleted files | Removed bytes | Approx. MiB |
| --- | ---: | ---: | ---: |
| Obsolete noncanonical `build/` objects, receipts, outdated sanitizer hosts and probe binaries | 2,113 | 206,482,917 | 196.92 |
| Uncited, historical `.analysis/*.gz` snapshots and logs | 383 | 7,059,351 | 6.73 |
| **Total** | **2,496** | **213,542,268** | **203.65** |

The `build/` directory decreased from approximately **227 MiB to 26
MiB**, and `.analysis/` from approximately **264 MiB to 257 MiB**.
The complete original path, original byte length and SHA-256 of **each
retired file** is retained in the ignored private audit
`.analysis/core300-retired-artifact-inventory.json`. The selection and
destructive confirmation were both run through the opt-in, default-dry-
run private script `.analysis/core300-safe-artifact-prune.py`.

## What was explicitly preserved

- All **212 unique canonical MSVC objects** currently referenced by
  `config/match-units.toml`, and **all 212 sibling receipt JSON files**.
  None was missing before or after cleanup. The entire target's
  `resources/th20.exe` original SHA-256 remains
  `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
- Unfinished active full-boss probe object sets and complete C++ source
  hypotheses for command-11, group drawing, emitter and graze-feedback
  functions. Private native assembly/decompilation, PE relocation
  attestations and focused evidence were **not** removed.
- Private `.analysis` snapshots explicitly cited in maintained
  documentation or relied upon by retained private source/scripts, and
  original evidence archives. Existing Git commits preserve previous
  maintained sources and the superseded long handoff.
- The installed ~4.2GB compiler/toolchain `.tools/`, original game
  provenance `_reference/` and `../game_exe/`, ignored Ghidra database,
  `.venv`, tracked sources, and generated progress diagrams.

## Safe repeat procedure

The private script is **dry-run by default** and must be inspected
before using `--apply`. It derives protected `.obj`/`.receipt.json`
paths from the **live** manifest, checks their existence, scans
maintained documents and private analysis source for archive
references, and excludes active root-probe directories and native
proof archives. It writes a per-file SHA-256 deletion inventory and
rechecks every protected object/receipt and the original executable
hash after deletion. It never deletes a complete `build/` or
`.analysis/` directory, toolchain, executable, database or Git history.

Do not run broad `git clean -fdx`, `rm -rf build`, indiscriminate
`.analysis` archival deletion, or a full cold replay merely to clean
storage. For documentation and ignored artifact cleanup, use Git
diffs, link verification, native hash, tracking and generated-progress
checks only; there are **zero replay-affected units** when the final
native-source/header/manifest inputs are unchanged.

The old retired ASan host binaries correspond to historical portable
semantic scenarios, **not current exactness gates**. If a previous
probe's disposable binary is needed, regenerate it from maintained
source and preserved `.analysis` experiment files under the actual
locked compiler profile. The exact `build/` cache is not a durable
research archive; native original evidence and source are.
