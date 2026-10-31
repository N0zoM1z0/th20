# 2026-10-31 — guarded generated-build cleanup and protected artifact audit

This is a dated storage audit. **Live counts** are in
[`RE_HANDOFF.md`](RE_HANDOFF.md), `config/match-units.toml` and
`config/matches.csv`, not any historical cleanup record.

The original Japanese TH20 1.00a Steamless target remains immutable:
`resources/th20.exe` SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The checked reconstruction ledger contained **6,928 provisional
candidates, 1,578 strict-source units and 769 game-authored whole exact
heads /264,067 original code bytes** before and after cleanup. No code,
manifest, native source or exact acceptance was changed during the
retirement, and no compilation or cold replay was needed.

## Audited safe deletion

Used the existing read-only/dry-run-first
[`scripts/prune-generated-artifacts.py`](../scripts/prune-generated-artifacts.py),
which constructs its own protected set from the **live** unit manifest,
source-proof references and a deliberately conservative current-active
probe directory allowlist. Then performed exactly one explicit apply:

```sh
scripts/repo-python scripts/prune-generated-artifacts.py
scripts/repo-python scripts/prune-generated-artifacts.py \
  --apply --inventory .analysis/gptweb-cleanup-2026-10-31-build-retirement.json
scripts/repo-python scripts/prune-generated-artifacts.py
```

| Audited original file selection | Result |
| --- | ---: |
| Disposable noncanonical compiler `.obj`/`.receipt.json` paths | **2,875 files** |
| Original bytes removed | **127,712,939 bytes /121.80 MiB** |
| `build/` on-disk size before and after | **228MB → 100MB** (`du -sh`, rounded) |
| Protected canonical `.obj` and matching `.receipt.json` pairs | **432 +432** |
| Other individually tracked native proof build artifacts | **164** |
| Protected files within active unresolved probe directories | **1,881** |
| Unique protected-file SHA-256 results after deletion | **923 unchanged** |
| Remaining automatically disposable files on second dry-run | **zero** |

A **unique private, ignored JSON audit** at
`.analysis/gptweb-cleanup-2026-10-31-build-retirement.json`
records the precise 2,875 deleted relative paths, original sizes and
SHA-256 values, exact original-target SHA and every protected path/hash.
It was written **before** deletion. The guarded tool re-attested the
original EXE and all 923 protected SHA-256 hashes **after** removal;
re-running dry-run reported `0 disposable files, 0 bytes`. This is
not a claim that inactive probes or historical bytes were unnecessary
at the time they were captured: only codegen products that are safely
regenerable and neither canonical nor protected were deleted.

## Deliberately preserved

- Original executable and provenance, `_reference/`/`game_exe/`,
  Ghidra project, Git history and maintained source.
- **Installed `.tools/` (about 4.2GB)**: MSVC, Windows SDK, Wine and
  installed D3DX headers/libs. This is the active compiler/SDK runtime,
  not disposable duplicate test output. Never remove it as a generic
  storage optimization.
- **Ignored `.analysis/` (about 307–308MB)**: original-native
  snapshots, archived `.json.gz` replay/source-freeze evidence, active
  hypotheses and exact physical proof inputs. Historical archives are
  referenced from dated reports; age alone does not make them safe to
  purge. Do not delete this directory indiscriminately.
- Every current canonical object/receipt and the documented individual
  original-native probe input, plus selected active Boss probe paths.
- The previously **untracked 417B formatted-text Renderer candidate**
  was explicitly preserved by SHA under
  `.analysis/gptweb-open-animation-formatted-text417.cpp` with its
  unresolved 418B compiler frontier in adjacent private notes. It is
  **not** accepted as exact or a new maintained source function.

## Future storage maintenance

Run the guarded script without arguments to see the *current* disposable
scope. Never reuse or overwrite this dated private audit filename. Use a
fresh unique inventory path for each future `--apply`, review the active
probe directory allowlist against current unresolved tasks, and retain
all canonical receipts and original-native evidence. A docs/cleanup-only
change has **zero affected exact units**: verify target hashes, local
links, `git diff --check` and tracking; do **not** run unfiltered cold
replay or recompilation merely to save storage.
