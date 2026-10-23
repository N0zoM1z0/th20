# Current reconstruction handoff

This page records current acceptance, protected local products and next work.
Use [generated progress](PROGRESS.md), the ledgers and the status reporter for
live counts; focused findings are in the [evidence index](EVIDENCE_INDEX.md).

## Verified reconstruction state

The sole target is Japanese v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Its embedded title/replay label is 1.00c in the same executable. The Steam-original
backup is provenance evidence. See [target provenance](TARGET_PROVENANCE.md).

The accepted graph contains 958 physical strict units, 164 canonical objects and
175,008 disjoint comparison bytes. All 968 mapped functions have source; ten
whole mapped functions remain nonexact. Authored exact coverage is separately
198 functions / 52,051 bytes, with 211 confirmed authored origins. The pinned
reference has 6,945 terminal implementation reviews and 113 reconciled parser-gap
files. These counts establish neither whole-game 95% byte exactness nor a
playable reconstruction; whole-program compilation and linkage remain open.

CORE156 maintains real Feedback, reward and indexed-script state protocols.
Eleven strict units add 666 comparison bytes and 493 authored code bytes. The complete
Feedback update remains 114/native115 and nonexact, with one unexplained post-call
NOP; it receives source/origin credit separately. The corrected Timer-base owner
retains its complete 133-byte constructor. The actual-owner fixture passes 38,400
Feedback, 8,064 reward, 84 selection and 10,240 defeat combinations, plus eight
remaining external-call failures and five topology cases. The guarded Player
storage/pool fixture also passes. See
[state protocols and emission boundary](ENEMY_DEFEAT_STATE_RECONSTRUCTION.md) and
[whole defeat acceptance](ENEMY_DEFEAT_RECONSTRUCTION.md).
The production Enemy opcode dispatcher remains undefined. Its private 96-value /
67-head draft and last CORE153 19,350-case result are preserved, without new credit.

## Current verification and cleanup

Three headers and three implementations change. Captured includes select 44
providers / 317 existing units; all fresh serial builds and strict replays pass.
The other 120 providers reuse valid evidence. Sixteen generated literal-name
changes preserve complete data and canonical roles. All 76 EH code/data sections
for 38 affected parents remain identical, including full relocation and function
label roles; their prior independent bindings are reused. Eleven new units pass
complete canonical replay. No full CI or unfiltered whole-graph replay runs.

Current private proofs are `core156-cold-proof.json`,
`core156-affected-results.json.gz`, `core156-new-exact-results.json.gz`,
`core156-independent-bindings.json`, `core156-eh-evidence-reuse.json`,
`core156-feedback-emission.json`, `core156-graph-audit.json`,
`core156-defeat-semantics-v1.log`, `core156-storage-semantics.log` and
`core156-gates.json`.
These filenames and other private filenames below are relative to `.analysis/`.
Reuse passing evidence for unchanged inputs. Documentation and cleanup add
**zero compiler builds and zero canonical replays**; only protected hashes and
lightweight documentation/tracking checks run during that phase.

`core156-retirement-plan.json` records 215 retired files / 3,817,017 bytes:
superseded canonical/probe products and copied private headers/source. Authentic
receipts and SHA-bound texts remain in the archives below. `core156-cleanup.json`
confirms all protected hashes remain unchanged. The maintained source/current
objects preserve the active Feedback emission question; replaced trials are
archived instead of kept as duplicate build trees.
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
| `build/core154-canonical/` | 7 | Every sibling `.receipt.json` |
| `build/core154-v2/` | 1 | Every sibling `.receipt.json` |
| `build/core156-canonical/` | 44 | Every sibling `.receipt.json` |

The manifest owns these 164 objects / 328 product files. The current 279-path
source freeze is `core156-final-frozen-source.json`. Protected hashes, including
284 native evidence files and twenty private investigation products, are in
`core156-retirement-plan.json`. Retain the nine root object/receipt pairs for
core103-QueryProtocol-v5 and the core109..core113 sound probes, plus
`build/core144-probes/Alignment.obj` and its receipt. Their unfinished
[damage-query](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md),
[sound](SOUND_PROTOCOL_RECONSTRUCTION.md) and
[Renderer-owner](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md) inquiries remain open.

Preserve `core156-pre-state-inputs.json.gz`,
`core156-pre-registration-ledgers.json.gz`,
`core156-probe-v1-original-inputs.json.gz`,
`core156-probe-v2-original-inputs.json.gz`,
`core156-probe-final-original-inputs.json.gz`,
`core156-member-call-original-inputs.json.gz`, `core155-pre-counter-inputs.json.gz`,
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

1. Continue the whole Enemy dispatcher with actual owners, complete control flow,
   tables and compiler contributions. The 0x48C010 root has 41,967 ordinary body
   bytes; no case fragment receives partial exact credit. Reuse the existing
   [state](ENEMY_DISPATCH_STATE_RECONSTRUCTION.md),
   [Card](ENEMY_CARD_STATE_RECONSTRUCTION.md),
   [clear](ENEMY_CLEAR_PROTOCOL_RECONSTRUCTION.md) and
   [movement](ENEMY_DISPATCH_MOVEMENT_RECONSTRUCTION.md) evidence.
2. Resolve the genuine Renderer owner and +6000DFC..+6000DFF before declaring
   members. Allocation is 0x7D40E94 bytes; negative searches do not prove padding.
   This blocks whole File::clear, texture creators and the 922-byte AnimationFile
   producer. The 40,752-byte Animation VM also remains open. Follow
   [pool/owner evidence](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md),
   [File lifetime](ANIMATION_FILE_LIFETIME_RECONSTRUCTION.md) and
   [whole dispatch evidence](CORE_ECL_DISPATCH_RECONSTRUCTION.md).
3. Preserve the Feedback 114/native115, generic list 31/native40 and callback
   invocation 69/native83 emission questions. Reuse the archived profile/isolation/
   explicit-call results; do not repeat unchanged trials or add inert operations.
   Original call/return/emission contracts require independent evidence.

The ten accepted source-present whole nonexact roots are:

| Root | Entry | Current boundary / evidence |
| --- | --- | --- |
| FunctionChainController::remove_unlocked | 0x412400 | 156/native162; [scheduler](FUNCTION_CHAIN_ALLOCATION_EXACT_RECONSTRUCTION.md) |
| ProgressMetadata::calculate_integrity | 0x463F20 | Whole native134; [progress storage](EXACT_PROGRESS_STORAGE_RECONSTRUCTION.md) |
| create_bomb_controller | 0x478300 | Whole native123; [Bomb owner](BOMB_OWNER_RECONSTRUCTION.md) |
| EnemyState::update_mesh | 0x4A4190 | 1548/native1649; [mesh lifetime](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md) |
| EnemyPattern::emit_items | 0x4A5350 | 628/native630; [drop protocol](ENEMY_DROP_PROTOCOL_RECONSTRUCTION.md) |
| PlayerFeedback::record_hit | 0x4FB3A0 | 114/native115; [state protocol](ENEMY_DEFEAT_STATE_RECONSTRUCTION.md) |
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
