# Current reconstruction handoff

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
python3 scripts/verify-target.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
python3 scripts/ghidra.py check
python3 scripts/ci.py
```

Read `AGENTS.md`, `RE_WORKFLOW.md`, `ARCHITECTURE.md`, `ORACLES.md`,
`SEMANTIC_RECONSTRUCTION.md` and `SOURCE_MAP.md` first. Next lane: one bounded
owner/ABI family from the provisional inventory, using independent target-local
evidence and clean compiler probes. Do not project TH095 roles/layouts/flags
onto TH20. Maintain one writable session and serial compiler/Ghidra access.
