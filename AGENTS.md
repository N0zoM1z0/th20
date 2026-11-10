# TH20 reconstruction agent rules

## Highest priority: lightweight exact reconstruction and useful knowledge

These are the user's current workflow requirements. They override older
instructions that mandate broad CI, repeated preflights, document/source-pin
refreshes, per-checkpoint audits or extra workflow machinery. Preserve the
actual exactness, target identity, natural-source and state-isolation rules.

- Prioritize exact reconstruction and reusable knowledge. Use the shortest
  useful loop: inspect relevant state, analyze/edit, compile and compare the
  affected scope, retain useful learning, and create a coherent checkpoint.
- Use existing repository scripts and composable Bash. Add only the smallest
  change needed for an observed problem. Do not introduce a framework, schema,
  registry, state machine, generalized validator, test family or reporting
  process merely to make a local reconstruction task look more engineered.
- Documentation, knowledge and handoff edits require no compiler, analyzer,
  full CI, cold replay or receipt refresh. Inspect the diff. Check syntax only
  for machine-readable inputs actually changed.
- Source changes need the complete affected exact comparison, including its
  owned extents and relocations. Recheck known consumers of changed shared
  inputs. Tool changes need relevant positive/negative cases and a bounded
  real smoke. Run a broad suite only for an explicit request or a demonstrated
  impact that cannot be narrowed; state that reason first.
- Do not add tests or live freshness gates for prose hashes, prompt wording,
  progress totals, handoff source-SHA tables or ordinary source spelling.
  Bind exact evidence to executable inputs and relevant verification settings.
  Keep Git metadata as provenance. A document genuinely consumed by a build
  remains a build input. Never edit historical receipts to manufacture a pass.
- Plain Markdown is sufficient for knowledge: record the finding, applicable
  target/compiler/scope, evidence links, useful failed attempts and open
  questions. No mandatory JSON conversion, promotion workflow or test per note.
  Search relevant sections; do not read an entire large knowledge journal.
- Write documentation and knowledge in natural, fluent English. Lead with the
  concrete finding and connect the evidence and next action clearly. Remove
  filler, circular restatements, repeated conclusions and unnecessary jargon.
  Do not add defensive-claim boilerplate. State a real uncertainty or scope
  limit once when it changes a decision; do not repeat disclaimers about what
  a note does not prove, certify or authorize. Prefer a small useful note over
  an exhaustive report that is difficult to read.
- Keep handoff focused on current work, evidence references, blockers and the
  next useful action. Generate progress from canonical ledgers; avoid manual
  duplicate counts, recurring full reports and unrelated documentation chores.
- Preserve dirty/untracked work, targets, useful evidence, game-specific Wine
  prefixes and analyzer projects. Exactness still requires a complete strict
  comparison; knowledge and successful commands alone confer no exact credit.


All maintained source comments, documentation, review records and commit
messages must be in English, as explicitly requested by the user.
Official Japanese names and original target evidence may retain their original
language, as the user explicitly clarified. Preserve the official title in
`config/target.toml`, following TH095's treatment of game metadata.
Use the user's current commit prefix **`gpt-web:`** for every new checkpoint.
Do not rewrite historical commits or use a different prefix for cleanup work.

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
workflow and oracle documentation when needed for the selected unit.
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
(staged, unstaged and untracked). Do not assume dirty work belongs to another
worker: inspect and continue its investigation, without resetting, hiding or
silently discarding any meaningful changes. For an unfinished ABI hypothesis,
retain its exact diff and private source before restoring validated public
headers; keep exact claims separate from unverified hypotheses.

Keep native reconstruction writes and MSVC builds serialized. Do not delegate
matching. Keep `config/claims.csv` header-only. Work on one
bounded address, coherent owner/protocol, or workflow-maintenance batch.
Replay only exact units actually affected by source, shared-header, profile,
layout, partition or anchor changes. Derive affected providers from captured
include closures and manifest dependencies; use explicit source filters or
individual units. Use the validation scope below. Commit
stable checkpoints before handoff.

## Validation focus

Validate changed native units with locked-compiler builds and complete canonical
replay; check tracking/progress only when their inputs change. Public CI covers
the exact oracle and control plane when those tools change. The historical
portable semantic suite is retired; do not restore allocation-failure, null
robustness, exception or sanitizer matrices as checkpoint gates. Use a temporary
probe under `.analysis/` only for a specific unresolved native behavior or ABI
question. Preserve original branches, EH and null handling in the native source.

Before validation, identify changed inputs and affected providers; state the
replay scope in the handoff (zero for an unchanged native graph). Reuse passing
evidence for unchanged inputs. Shared headers expand their captured include
closure. Use `replay-exact-units.py --source ...` or individual `build.py --unit`
and `compare-coff-function.py --unit` commands. Never use an unfiltered
whole-graph replay for routine checkpoints. These scope rules supersede broader
verification requirements in historical records.

Keep required inputs, current reconstruction products and useful knowledge.
Delete obsolete archives, duplicate evidence, old outputs and cleanup reports;
a document citation alone is not a retention reason. Keep an old compiler
context only when an unresolved question depends on hard-to-reproduce inputs.
Do not create replacement archives, cleanup reports or mandatory inventories.
Protect canonical objects/receipts, useful native evidence and active inputs;
verify retained hashes. See `docs/RE_WORKFLOW.md`.

The user also requires controlled CPU and memory use. Run compiler, headless
Ghidra, cold replay and focused probes at reduced scheduling priority (for
example `nice -n 15`), keep heavy jobs serial and reuse existing evidence.
Keep queries bounded to the reviewed scope. Do not repeat cold builds of an
unchanged graph solely for documentation or cleanup.

Never commit original executables/data, downloaded proprietary toolchains,
credentials, generated decompiler text, private Ghidra/IDA databases or build
products. Keep them in ignored `.tools/`, `.analysis/`, `ghidra-project/`,
`build/` and `resources/th20.exe`; preserve the supplied `../game_exe/` files.

## Shared Factory runtime

Follow [the shared tools instructions](docs/SHARED_TOOLS.md). Ghidra/JDK and
Wine executables are shared through Factory; repository scripts also work
without MCP. Use `scripts/shared_runtime.py` and the existing compiler/analysis
frontends. Keep this game's prefix, analyzer project, Java home/cache, target
and compiler profile isolated. Do not install duplicate tools or inherit
another game's `WINEPREFIX`. This shared-runtime procedure supersedes older
per-repository installation instructions; pinned versions/hashes still apply.
