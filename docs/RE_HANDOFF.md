# Current reconstruction handoff

## REF-002 — 2026-10-06 — exhaustive review remains active

The user clarified that every existing reference implementation must receive
an individual review. Easy exact recoveries should be absorbed immediately;
difficult cases should record evidence and remaining work, then continue.
Do not treat REF-001's file/module scan as satisfying this requirement.

- Index: 916 nongenerated C/C++ files; 6,708 definitions, including 4,193
  reconstruction candidates. Role/address hints are provisional, not mappings.
- Parser gaps in 104 files require manual reconciliation. Deleted declarations
  and generated Ghidra exports are excluded; defaulted bodies and lambdas remain.
- Explicit decisions currently cover 24 native-core/export bodies. The other
  6,684 indexed bodies are pending, as are parse-gap reconciliations.
- Timer mode now matches through its natural two-bit field representation.
- Timer add/tick restore original receiver/global-clock/helper-call ABI and
  match all 295/324 bytes, including eight/ten independent relocations.
- Two float receiver helpers match 16/35 bytes. Their enclosing owner/origin
  remains pending, so they receive no authored progress credit.
- Cold replay: nine units, three objects, 1,007 bytes. Authored exact: five
  Timer functions, 788 bytes; source-present mappings: nine.
- Private original-reference TU probes cover scheduler/archive/runtime; build
  include dependencies and verifier hash macros need distinct recipe handling.

Read `REFERENCE_FUNCTION_REVIEW.md`. Use `index-reference-functions.py --check`
and `report-reference-functions.py` through `scripts/repo-python`; explicit
review outcomes bind to body hashes. Reference compiler probes stay serial and
never confer semantic or exact credit. Continue scheduler constructors/setters,
link/iterator repair and dispatch, then runtime/archive and every remaining
implementation. No approval or new task is needed to keep progressing.

Private evidence: `.analysis/ref002-*`, `.analysis/reference-functions/`.
The following records are historical checkpoints.

## REF-001 — 2026-10-06

The reference-wide review and first independently verified absorption are
recorded in `REFERENCE_REVIEW.md`. The pinned local checkout is
`_reference/Touhou20`, explicitly ignored and blocked from public CI's tracked
tree. The public repository is https://github.com/N0zoM1z0/th20, with TH095-style
README/progress, About and topics. Maintained prose is English; official names
and original evidence retain their language. Commit subjects use
`gpt-6.1-sol: <description>`.

All Python invocations now go through `scripts/repo-python`, modeled on TH10.
Shell launchers and public CI use the same entry point; it prefers the pinned
local environment and supports standard-library-only fresh public checkouts.

- All 10,822 reference files audited; 55 group dispositions account for them.
- Same target hash: registry/package identification is 1.00a, embedded
  title/replay labels are 1.00c. Both are verified in target provenance.
- 153 diagnostic sites in 124 functions independently accepted as routing
  evidence, with no mapping/source/exact credit inherited.
- Maintained source: `src/Random.*` and `src/Timer.*`; five source-present mappings.
- Four canonical units replay complete contributions from two cold objects.
- Authored exact credit: two Timer functions, 131 bytes. RNG's two exact
  equivalents are excluded as MSVC STL; __aullshr is excluded as CRT.
- Timer mode: natural source, behavior checked, three differing bytes; no credit.
- Current origin review: three authored, three exclusions, 6,922 pending.
- Public semantic/synthetic CI, private target/tracking/Ghidra checks, reference
  byte/freshness audit and independent source-diagnostic checks pass.
- Portable reference binary-parser and archive CTests pass. Linux cannot link
  its Windows-wmain archive verifier; no game/runtime credit follows.
- No whole-game build/runtime or reference implementation bulk import.

Next coherent family: Timer delta/tick and global clock/rounding, or enclosing
RNG seed/distribution/storage ownership. Other candidate families are indexed
in the reference review; avoid inheriting its service-suffixed layouts or
historical behavior counts. Replay existing units after any shared-source change.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/ghidra.py check
scripts/repo-python scripts/review-reference.py
scripts/repo-python scripts/ghidra.py architecture
scripts/repo-python scripts/import-reference-leads.py --check
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python scripts/ci.py
```

Private evidence: `.analysis/reference-review/`, `.analysis/reference-core*`,
`.analysis/reference-rng-anchor*`; receipts are beside `build/Random.obj` and
`build/Timer.obj`. The bootstrap record below is historical.

## BOOT-001 — 2026-10-06

The TH20 control plane and local build/analysis environment are initialized.
The user selected existing **Japanese v1.00a Steamless** as the sole exact
oracle. The Steam-original backup remains provenance evidence. This decision
is persistent; do not ask again or silently substitute the non-Steam variant.

- Target SHA-256: `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
- Repository: `/home/pentester/coding/codex_ida/th20-reconstruction/th20`.
- Supplied files: `../game_exe/`; ignored target symlink `resources/th20.exe`.
- Analysis: independent Ghidra 12.1.3 `TH20` project, fully target-attested.
- Inventory: 6,928 provisional functions, all origins/boundaries awaiting review.
  Architecture export has 22,731 direct call edges, 11,307 global-reference rows
  and 711 string-reference rows; these are routing evidence only.
- Mapping/source/exact: **0 / 0 / 0**; canonical manifest and claims are empty.
- Candidate compiler: MSVC 19.44.35211 x86, linker 14.44.35211.0,
  toolset directory 14.44.35207, SDK 10.0.26100.0, D3DX 9.29.952.8.
  Game compiler build and flags remain unproved; see `ORACLES.md`.
- Shared analysis-tool symlinks point at TH095's `.tools/`. Compiler/SDK/Wine
  and private Ghidra state are local to TH20. TH095 source, ledgers, database,
  environment and protected untracked files were not changed.
- Optional project-agnostic web bridge is prepared with a TH20 env template
  and launcher. No listener, user service or external endpoint was published.

## Validation evidence

Passed target/provenance verification, locked tool fingerprints/version banners,
Ghidra check plus bounded entry disassembly/decompilation and architecture
export, tracking/build-graph/progress gates, synthetic exact-oracle tests and
public CI. The target verifier rejects the Steam-original backup as a substitute;
the Ghidra attestation rejects a deliberately wrong expected target hash without
mutating the database or executing a query. Exact replay reports zero configured
units and does not manufacture matching credit.

The cold compiler probe passed x86 COFF, Win32/DirectX C++ headers, PE32 linker
and Wine/D3DX runtime checks. Infrastructure probe hashes at this checkpoint:

- Source: `f043a7f400b12088efe5cab8ca30e67c8a7803070fa6e0be022f340a2f5cce0a`.
- Object: `3053df6b6a59a90c3514c2445542530581691acec2058e550851e6227e87d27d`.
- PE32 executable: `9e8c92f9d647ac954ebf1fe3234087a7de81bd3004b6454029cc200277b53c02`.

Objects, debug records, raw decompilation, downloaded registry/manifests and
full command receipts stay in ignored `build/` and `.analysis/bootstrap/`.
The smoke executable is a console infrastructure probe, not a game build.

## Resume

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/ghidra.py check
scripts/repo-python scripts/ci.py
```

Read `AGENTS.md`, `RE_WORKFLOW.md`, `ARCHITECTURE.md`, `ORACLES.md`,
`SEMANTIC_RECONSTRUCTION.md` and `SOURCE_MAP.md` first. Next lane: one bounded
owner/ABI family from the provisional inventory, using independent target-local
evidence and clean compiler probes. Do not project TH095 roles/layouts/flags
onto TH20. Maintain one writable session and serial compiler/Ghidra access.
