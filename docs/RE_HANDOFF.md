# Current reconstruction handoff

This page records current acceptance, protected local products and next work.
Use [generated progress](PROGRESS.md), the ledgers and the status reporter for
live counts; focused findings are in the [evidence index](EVIDENCE_INDEX.md).

## Verified reconstruction state

The sole target is Japanese v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Its embedded title/replay label is 1.00c in the same executable. The Steam-original
backup is provenance evidence. See [target provenance](TARGET_PROVENANCE.md).

The accepted graph contains 947 physical strict units, 164 canonical objects and
174,342 disjoint comparison bytes. All 956 mapped functions have source; nine
whole mapped functions remain nonexact. Authored exact coverage is separately
192 functions / 51,558 bytes, with 204 confirmed authored origins. The pinned
reference has 6,945 terminal implementation reviews and 113 reconciled parser-gap
files. These counts establish neither whole-game 95% byte exactness nor a
playable reconstruction; whole-program compilation and linkage remain open.

CORE155 accepts the whole 1,371-byte Enemy::defeat, nine owner helpers and three
SDK callback helpers: thirteen strict units / 1,886 bytes, with separate authored
and library origins. The complete 55-byte EH code and 44-byte metadata also
replay independently. The actual PlayerFeedback counter getter is corrected to
+38 and folds to an existing physical unit without duplicate credit. The public
actual-owner fixture passes 10,240 combinations, twelve interface failures,
five recursive topology cases and an assertion with unequal counter words. Earlier
Enemy creation/clear and spawn/tick results are retained. See
[whole defeat acceptance and callee boundaries](ENEMY_DEFEAT_RECONSTRUCTION.md).
The production Enemy opcode dispatcher remains undefined. Its private 96-value /
67-head draft and last CORE153 19,350-case result are preserved, without new credit.

## Current verification and cleanup

Only PlayerStorage.cpp changes. Actual include closures select one provider /
seven existing strict units, all freshly built and replayed. The other 163
providers reuse valid evidence. Thirteen new units reuse unchanged CORE154
objects with valid immutable receipts and pass their own canonical replay.
Only the affected defeat fixture is rerun. No whole-graph replay or full CI runs.
The earlier CORE154 52-provider/364-unit and geometry correction results remain
preserved; unchanged verification is not repeated.

Current private proofs are `core155-independent-bindings.json`,
`core155-counter-exact-results.json.gz`, `core155-new-exact-results.json.gz`,
`core155-graph-audit.json`, `core155-defeat-semantics.log` and `core155-gates.json`.
These filenames and other private filenames below are relative to `.analysis/`.
Reuse passing evidence for unchanged inputs. Documentation and cleanup add
**zero compiler builds and zero canonical replays**; only protected hashes and
lightweight documentation/tracking checks run during that phase.

`core155-retirement-plan.json` records the two replaced PlayerStorage product
files / 50,630 bytes. Their authentic receipt and SHA-bound source versions are
preserved in `core155-pre-counter-inputs.json.gz`. `core155-cleanup.json` confirms
all protected hashes remain unchanged. No disposable probe builds are created.
Native evidence, original inputs, installed tools, reference source, Ghidra and
supplied game files remain protected.

Historical archive lookup remains in `handoff146-retirement-plan.json`,
`handoff149-retirement-plan.json`, `handoff152-retirement-plan.json` and
`handoff154-retirement-plan.json`. The last identifies the lossless
`core154-retired-probe-inputs.json.gz` archive.
Use `gzip.open` for their losslessly archived reports instead of old plain paths.

## Protected local products

| Canonical directory | Objects | Required companions |
| --- | ---: | --- |
| `build/core141-canonical/` | 79 | Every sibling `.receipt.json` |
| `build/core142-canonical/` | 12 | Every sibling `.receipt.json` |
| `build/core143-canonical/` | 10 | Every sibling `.receipt.json` |
| `build/core145-canonical/` | 6 | Every sibling `.receipt.json` |
| `build/core149-canonical/` | 1 | Every sibling `.receipt.json` |
| `build/core151-canonical/` | 1 | Every sibling `.receipt.json` |
| `build/core152-canonical/` | 3 | Every sibling `.receipt.json` |
| `build/core154-canonical/` | 50 | Every sibling `.receipt.json` |
| `build/core154-v2/` | 1 | Every sibling `.receipt.json` |
| `build/core155-canonical/` | 1 | Every sibling `.receipt.json` |

The manifest owns these 164 objects / 328 product files. The current 279-path
source freeze is `core155-final-frozen-source.json`. Protected hashes, including
280 native evidence files and twenty private investigation products, are in
`core155-retirement-plan.json`. Retain the nine root object/receipt pairs for
core103-QueryProtocol-v5 and the core109..core113 sound probes, plus
`build/core144-probes/Alignment.obj` and its receipt. Their unfinished
[damage-query](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md),
[sound](SOUND_PROTOCOL_RECONSTRUCTION.md) and
[Renderer-owner](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md) inquiries remain open.

Preserve `core155-pre-counter-inputs.json.gz`,
`core155-pre-registration-ledgers.json.gz`, `core154-pre-acceptance-inputs.json.gz`,
`core154-pre-geometry-namespace-inputs.json.gz`,
`core154-pre-publication-inputs.json.gz`, `core154-v4-original-inputs.json.gz`,
`core154-retired-probe-inputs.json.gz` and all earlier original-input/evidence
archives. They retain authentic receipts and SHA-bound source versions; receipts
must never be rewritten. The earlier private whole-dispatcher candidate and
fixture remain `core152-enemy-dispatch-candidate.cpp` and
`core153-dispatch-host.cpp`. Preserve unfinished private owner/phase/protocol
sources and their native exports; reuse rejected-trial evidence.

## Next work

1. Close complete native feedback/reward and indexed ECL selector bodies on their
   genuine owners: record_hit at 0x4FB3A0 (115 bytes), add_reward at 0x4A9DE0
   (128-byte contribution), and selectors at 0x5401D0 / 0x540230 (40 / 66 bytes).
   Native record_hit increments +38 then copies it to +30;
   preserve signed comparisons and wrapping behavior when reviewing that whole
   protocol. The accepted defeat caller retains explicit resource interfaces.
   IntrusiveList construction remains31/native40 and SDK callback invocation
   remains69/native83; preserve these separate emission gaps and do not introduce
   shaping writes. Follow [whole defeat evidence](ENEMY_DEFEAT_RECONSTRUCTION.md).
2. Continue the whole Enemy dispatcher with actual owners, complete control flow,
   tables and compiler contributions. The 0x48C010 root has 41,967 ordinary body
   bytes; no case fragment receives partial exact credit. Reuse the existing
   [state](ENEMY_DISPATCH_STATE_RECONSTRUCTION.md),
   [Card](ENEMY_CARD_STATE_RECONSTRUCTION.md),
   [clear](ENEMY_CLEAR_PROTOCOL_RECONSTRUCTION.md) and
   [movement](ENEMY_DISPATCH_MOVEMENT_RECONSTRUCTION.md) evidence.
3. Resolve the genuine Renderer owner and +6000DFC..+6000DFF before declaring
   members. Allocation is 0x7D40E94 bytes; negative searches do not prove padding.
   This blocks whole File::clear, texture creators and the 922-byte AnimationFile
   producer. The 40,752-byte Animation VM also remains open. Follow
   [pool/owner evidence](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md),
   [File lifetime](ANIMATION_FILE_LIFETIME_RECONSTRUCTION.md) and
   [whole dispatch evidence](CORE_ECL_DISPATCH_RECONSTRUCTION.md).

The nine accepted source-present whole nonexact roots remain:

| Root | Entry | Current boundary / evidence |
| --- | --- | --- |
| FunctionChainController::remove_unlocked | 0x412400 | 156/native162; [scheduler](FUNCTION_CHAIN_ALLOCATION_EXACT_RECONSTRUCTION.md) |
| ProgressMetadata::calculate_integrity | 0x463F20 | Whole native134; [progress storage](EXACT_PROGRESS_STORAGE_RECONSTRUCTION.md) |
| create_bomb_controller | 0x478300 | Whole native123; [Bomb owner](BOMB_OWNER_RECONSTRUCTION.md) |
| EnemyState::update_mesh | 0x4A4190 | 1548/native1649; [mesh lifetime](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md) |
| EnemyPattern::emit_items | 0x4A5350 | 628/native630; [drop protocol](ENEMY_DROP_PROTOCOL_RECONSTRUCTION.md) |
| create_hit_controller | 0x4C20D0 | 82/native92; [Hit lifecycle](HIT_CONTROLLER_LIFECYCLE_RECONSTRUCTION.md) |
| ProgressSaveManager construction | 0x50E5D0 | 198/native199; [lifetime/profile](PROGRESS_LOAD_LIFETIME_EXACT_RECONSTRUCTION.md) |
| ProgressSaveManager::commit | 0x50F660 | 68/native70; same lifetime/profile evidence |
| archive_compress | 0x539550 | Whole native1036; [write protocol](ARCHIVE_WRITE_RECONSTRUCTION.md) |

Do not repeat unchanged rejected profile trials or insert inert operations to
shape output. Preserve actual void, lifetime and exception contracts. The whole
1,707-byte damage query remains unimplemented; its counter and release-before-read
ownership questions are in the focused evidence.

## Resume discipline

Follow [AGENTS.md](../AGENTS.md), [workflow](RE_WORKFLOW.md) and
[tool routing](TOOLS.md). Commit subjects use **`gpt-6.1-sol: <description>`**.
Use one writable session, no REA or delegated reconstruction, and serial heavy
work at nice 15 / CPU 3 with bounded Ghidra memory. Keep claims header-only and
maintained prose in English; preserve the official Japanese title.

Replay only units affected by actual source/include/profile/layout/partition or
anchor changes, using explicit source filters or individual units. Resume from
passing evidence above. An unchanged documentation/cleanup batch has zero
replay units; skip Ghidra, MSVC and full CI. Never run an unfiltered replay for
handoff, cleanup or reassurance.
