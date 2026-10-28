# TH20 reconstruction agent rules

All maintained source comments, documentation, review records and commit
messages must be in English, as explicitly requested by the user.
Official Japanese names and original target evidence may retain their original
language, as the user explicitly clarified. Preserve the official title in
`config/target.toml`, following TH095's treatment of game metadata.
Use the commit prefix requested for the active session: `gpt-web:` for web
work and `gpt-6.1-sol:` for this Codex session. Do not rewrite historical commits.

Invoke Python through `scripts/repo-python` for repository work, including
one-off snippets and tests. It selects the local `.venv` and verifies pinned
optional decoder versions. Python subprocesses use `sys.executable` to keep
that selection. See `docs/TOOLS.md` for fresh-checkout and override behavior.

## Exact target and scope

This repository reconstructs the user-selected Japanese TH20 v1.00a
**Steamless** executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The user explicitly approved this selection on 2026-10-06 and requested
**Ghidra** as the analysis backend. Preserve that decision across sessions.
The Steam-original backup is provenance evidence. Do not substitute it,
non-Steam retail, a localization, a trial or an earlier/later executable.

Registry/package identification is v1.00a; embedded title/replay strings say
1.00c in this same locked file. Preserve both observations as documented in
`docs/TARGET_PROVENANCE.md`. Version labels alone do not identify a different
comparison target.

## Before changing reconstruction state

For documentation-only or artifact-cleanup work, inspect Git status and the
changed paths, check documentation/diffs and protected product hashes, and stop
there. Do not run Ghidra, MSVC, full CI or canonical replay for an unchanged
reconstruction graph. The reconstruction preflight below applies when changing
reconstruction code, analysis evidence or acceptance state.

Read `docs/RE_HANDOFF.md` and the relevant source/evidence. Consult architecture,
workflow, oracle and semantic documentation when needed for the selected unit.
Inspect `git status`, then run:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

Ghidra queries/decompilation/exports must go through `scripts/ghidra.py`,
which re-attests target and database on every call. Never use an unrelated
IDA/Ghidra database. Never patch target or mapped database bytes.
The user explicitly requested no REA skills or REA MCP tools. Use the existing
attested Ghidra workflow directly.

## Evidence, source and exactness

- `config/functions.csv` is a provisional boundary ledger. Reconcile complete
  control flow, shared code, tails, padding and tables before accepting sizes.
- `function-origins.csv` separately tracks authored/compiler/library origins.
  Auto-analysis does not establish authorship.
- Mapping, source presence, semantic acceptance, compilation, linkage,
  runtime behavior and exactness are separate facts.
- Exact credit requires a reproducible unit in `match-units.toml`, a fresh
  locked-compiler build and complete zero-difference canonical relocation
  replay. Structural-exact diagnostic output does not establish exactness.
- Resolve canonical relocations from independent evidence, never by solving
  the target field under comparison. Do not shorten extents to hide differences.
- Use natural maintained C/C++ with one shared semantic body and canonical
  owner. No copied decompiler source, target byte arrays, arbitrary padding,
  inert compiler-shaping locals, fake returns, ABI lies or assembly.
- Do not add `TH20_MATCH_EXACT`/`DIFFBUILD` branches below `src/`. TH095's
  historical debt and special user-authorized assembly exceptions do not apply.
- Preserve MSVC x86 calling conventions, widths, layout, vtable/RTTI/EH,
  initialization and translation-unit ownership. Compiler 19.44.35211 is an
  installed candidate; game build/flags/SDK/CRT are not globally proven.
- Record observations, compiler results, corroboration, inferences and unknowns
  separately. Durable evidence belongs in the knowledge base and ledgers;
  raw decompiler text and transient probes stay under `.analysis/`.

## Session discipline

Keep RE_HANDOFF.md limited to current status, protected products and next work.
Architecture, oracles and source navigation each have their own documentation
role. Put unique native findings in focused evidence documents and link them
through EVIDENCE_INDEX.md; do not duplicate cumulative checkpoint logs across
core documents. Historical batch totals must not masquerade as current status.

At the beginning of each continuation, inspect the entire live Git status
(staged, unstaged and untracked). Web and Codex work may coexist: understand
existing dirty changes, preserve the other session's files and commit only
the active session's bounded batch. Do not reset or absorb concurrent work.

Keep native reconstruction writes and MSVC builds serialized. Do not delegate
matching. Keep `config/claims.csv` header-only. Work on one
bounded address, coherent owner/protocol, or workflow-maintenance batch.
Replay only exact units actually affected by source, shared-header, profile,
layout, partition or anchor changes. Derive affected providers from captured
include closures and manifest dependencies; use explicit source filters or
individual units. Use the validation scope below. Commit
stable checkpoints before handoff.

## Validation focus

Prioritize exact reconstruction: locked-compiler builds and complete canonical
replay for changed native units, tracking/progress checks for changed metadata.
Public CI covers the exact oracle and control plane. Portable semantic fixtures
are optional; select one only for a concrete unresolved native behavior or ABI
question. Allocation-failure injection, null robustness, exception matrices,
sanitizer variants and scenario totals are not exact-checkpoint requirements.
Historical tests need not be preserved, extended or rerun. Preserve original
branches, EH and null handling in source and the complete native comparison.

Before validation, identify changed inputs and affected providers; state the
replay scope in the handoff (zero for an unchanged native graph). Reuse passing
evidence for unchanged inputs. Shared headers expand their captured include
closure. Use `replay-exact-units.py --source ...` or individual `build.py --unit`
and `compare-coff-function.py --unit` commands. Never use an unfiltered
whole-graph replay for routine checkpoints. These scope rules supersede broader
verification requirements in historical records.

Retire the batch's superseded probe builds after verifying replacements. Protect
canonical objects/receipts, native evidence and active inputs; record removed
paths/bytes privately and verify protected hashes. See `docs/RE_WORKFLOW.md`.

The user also requires controlled CPU and memory use. Run compiler, headless
Ghidra, cold replay and semantic checks at reduced scheduling priority (for
example `nice -n 15`), keep heavy jobs serial and reuse existing evidence.
Keep queries bounded to the reviewed scope. Do not repeat cold builds of an
unchanged graph solely for documentation or cleanup.

Never commit original executables/data, downloaded proprietary toolchains,
credentials, generated decompiler text, private Ghidra/IDA databases or build
products. Keep them in ignored `.tools/`, `.analysis/`, `ghidra-project/`,
`build/` and `resources/th20.exe`; preserve the supplied `../game_exe/` files.
