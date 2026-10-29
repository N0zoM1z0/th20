# CORE/MAINT-751 — current-state source/document correction and guarded native probe retirement

**Date:** 2026-10-29. This is documentation, source-navigation and ignored
generated-artifact housekeeping. There are **zero changes** to maintained
native C++ translation units, public headers, canonical native match-unit
definitions, compiler flags, physical original relocation targets, authored
function-origin classifications, original target bytes or game-credit ledgers.
No MSVC compile, Ghidra query, global cold replay or whole-game CI was run.

## Latest verified target and native-exact snapshot

| Fact | Current accepted state |
| --- | --- |
| Locked Japanese TH20 v1.00a Steamless original | SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897 |
| Source-present / mapped functions | **1,201** |
| Configured complete whole-native strict units | **1,203** |
| Canonical pinned MSVC source objects | **245** |
| Matching canonical compiler receipts | **245** |
| **Distinct authored-game complete native exact functions** | **556 /186,645 disjoint original .text bytes** |
| Whole TH20 game linked/playable | **No** |

These values come from the live native manifests/status tool and are a
dated snapshot, not a game-executable completion percentage. Old checkpoint
numbers **498/175,709**, **1,184 units/243 object pairs**, **236** or **212**
protected pairs are historical, not current.

### Documentation and source navigation corrected

- [Current agent handoff](RE_HANDOFF.md) has a single current status table,
  a compact list of *already exact* original big functions, and an explicit
  priority table for genuinely unfinished big game bosses. It replaces the
  long duplicate historical account, while retaining all focused proof links.
- [README](../README.md) now has a brief seven-row **current** area/status
  summary instead of reprinting a large succession of checkpoints. Exact
  Bullet emitter, ECL interpreter, input polling, LZSS compressor, Animation
  factory and Bullet command-11 are clearly distinguished from NONEXACT
  Player/Bullet/Enemy/Animation giant functions.
- [Roadmap](ROADMAP.md) no longer sends agents after an obsolete
  3,735B Bullet emitter compiler NOP frontier; the emitter is already
  whole strict exact. [Architecture](ARCHITECTURE.md) correctly states
  **39,470B Animation VM** (not dated 40,752B) and acknowledges the
  whole **1,036B LZSS compressor /706B decoder** already exact.
- [Evidence index](EVIDENCE_INDEX.md) links current next-agent reading
  order before the historical experiments and explains that dated exact
  totals are **not additive**. No unique original PE proof was removed.
- [Reconstruction workflow](RE_WORKFLOW.md) corrects its former claim that
  **243 canonical pairs and 1,184 units** were still live: those belonged to
  [CORE628](ARTIFACT_RETIREMENT_CORE628.md). The old retirement audit is
  explicitly marked dated. A previously superseded claim that the full
  3,735B Bullet emitter was NONEXACT is called out as historical; it is
  now whole-native exact, including the 3,832B compared compiler extent.
- Immediate big-Boss work is specific: [original 12,140B Bullet command
  source closure](BULLET_12140_E8_203_7_SOURCE_CLOSURE.md) has **203/210
  original E8s mapped** and precisely five unsourced *game-owned*
  Animation helper candidates plus two compiler helper calls. These seven
  targets are **not yet exact**. [Player main](PLAYER_MAIN_3111_SEMANTIC_OPERANDS_AND_REGISTER_FRONTIER.md),
  [Player movement](PLAYER_MOVEMENT_555_SHARED_NATIVE_128_RELOCATION.md)
  and [Bullet draw](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md) remain
  source-present but NONEXACT. The 41,967B Enemy opcode dispatcher and
  39,470B Animation VM remain separate NONEXACT game roots.
- No claim that library-only source matching increases the **game-authored**
  original code tally. The real 610B PMR vector and 100B shared_ptr STL
  contributions are already separately matched as **library/excluded**.

### Guarded build/ retirement, exact filesystem results

The existing guarded tool scripts/prune-generated-artifacts.py was tightened
to protect **individual generated native .obj or adjacent receipts explicitly
referenced by tracked README, docs and script text**, in addition to the
live match-units.toml canonical objects/receipts and the dated allowlist of
active native Player/Bullet/mesh benchmarks. The new reference guard is
path-specific: it does not retain an entire experiment directory merely
because one whole-method comparator object is cited.

Before deletion, a separate dry run and **four negative apply tests**
successfully proved that missing audit names, existing inventory filenames,
paths escaping .analysis and nested inventory names are all refused **before**
any deletion. The candidate set was independently cross-checked against the
manifest and the original PE SHA-256.

| Actual affected storage | Audited result |
| --- | ---: |
| Files selected after **documented proof** protection | **1,042** |
| Exact data deleted | **48,417,387 bytes** |
| Reclaimed storage | **46.17 MiB** |
| build/ before / after, displayed disk usage | approximately **123MB -> 74MB** |
| Protected native canonical objects | **245/245**, original SHA-256 unchanged |
| Protected canonical .receipt.json files | **245/245**, original SHA-256 unchanged |
| Explicit tracked native-evidence references detected | **64** (some overlap canonical/active files) |
| **Distinct original SHA-protected files** | **511**, all unchanged after apply |
| Additional active probe files retained by directory allowlist | **1,694** |
| Original game PE protected | Exact original SHA-256 unchanged |
| Second dry run after deletion | **0 files / 0 bytes** still eligible |
| Native code, acceptance, compiler profiles or game-credit changes | **None** |

Only **noncanonical reproducible generated .obj/.receipt.json** products
outside explicit native-source/receipt/documentation protection were removed.
No original executable, native data table, decompiler transcript, C++ source,
proof script, frozen input snapshot, ordinary analysis JSON or Git history was
deleted. Empty generated build subdirectories were removed only after their
disposable files were deleted.

**Private full SHA/path evidence** remains in ignored files:
- .analysis/core751-probe-retirement-inventory.json — written BEFORE
  deletion, records every removed file's path, exact byte count and
  SHA-256, all 511 original protected file hashes, native target digest,
  manifest-owned object count, and retained active probe directories.
- .analysis/core751-probe-retirement-dry-run.log — original reviewed
  candidate, byte and protection counts.
- .analysis/core751-probe-retirement-apply.log — actual completed apply,
  protected post-check and inventory location.

The cleanup is repeatable without overwriting older histories: the
tool refuses an existing or non-top-level .analysis audit name. A current
dry run finds nothing else eligible under the unchanged native graph.

### Intentionally retained substantial private storage

| Private storage | Why it stays |
| --- | --- |
| **.tools/ ~4.2GB** | Real pinned MSVC/Windows SDK, Wine and D3DX required to reproduce x86 original compiler behavior; not a disposable cache |
| **.analysis/ ~290MB** | Original PE/ABI/native disassembly proofs, private C++ hypotheses, original build/input freeze and about **386 compressed .json.gz snapshots** (~132MB). Many are uniquely referenced by earlier research; do **not** bulk-delete |
| **_reference/ ~157MB** | Locally pinned source/reference original identity and comparison evidence |
| **ghidra-project/ ~44MB** | Attested original Steamless game analysis database |
| **.venv/ ~17MB** | Pinned optional Python native decoder/verification dependencies |
| **build/ ~74MB after retirement** | All 245 current canonical object/receipt pairs, explicit original proof objects and actively protected native probes |
| **resources/th20.exe and original provenance** | Hash-attested immutable game target and original assets |

We did **not** delete historical .analysis/*.json.gz files merely to
inflate the reclaimed figure. In particular, a prior pre-admission ABI
snapshot may be the only complete source-state record of a now superseded
compiler experiment. Archive/retirement claims must not substitute for a
native source or strict exact unit proof.

## Scope and validation

No accepted compiler input or native match manifest changed. Therefore
**zero strict native units needed replay**; running all 1,203 cold units
would be both slower and uninformative. Instead this batch verifies the
original PE SHA, the current source ledger, all documentation entrypoint
links, the changed cleanup script's positive/negative guard behavior,
git diff --check and the exact **511-file protected hash inventory**.

Read the [current handoff](RE_HANDOFF.md) to continue actual
reconstruction. When new C++ or headers change, compute and replay only
their true affected native source closure; do not reuse this documentation
cleanup's zero-replay scope.
