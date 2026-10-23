# Current reconstruction handoff

This page records current acceptance, protected local products and next work.
Use [generated progress](PROGRESS.md), the ledgers and the status reporter for
live counts; focused findings are in the [evidence index](EVIDENCE_INDEX.md).

## Verified reconstruction state

The sole target is Japanese v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Its embedded title/replay label is 1.00c in the same executable. The Steam-original
backup is provenance evidence. See [target provenance](TARGET_PROVENANCE.md).

The accepted graph contains 977 physical strict units, 164 canonical objects and
177,676 disjoint comparison bytes. All 987 mapped functions have source; ten
whole mapped functions remain nonexact. Authored exact coverage is separately
200 functions / 53,621 bytes, with 213 confirmed authored origins. The pinned
reference has 6,945 terminal implementation reviews and 113 reconciled parser-gap
files. These counts establish neither whole-game 95% byte exactness nor a
playable reconstruction; whole-program compilation and linkage remain open.

CORE160 reconstructs the complete 0x1A360-byte AsciiInf storage and its
687-byte authored noexcept constructor, including three actual Animations,
320 TextLines, the real Worker/list and shared text-file selection. Four new
strict units add 839 comparison bytes; complete EH support separately passes
94 bytes. AsciiInf resource lifetime, formatting and drawing remain open.
See [AsciiInf owner evidence](ASCII_OWNER_RECONSTRUCTION.md). The complete
FrontInf owner and boss-marker protocol remain accepted; see
[FrontInf evidence](FRONT_OWNER_RECONSTRUCTION.md).

The private whole-dispatcher draft now covers 110 effective values / 81 primary
heads and passes 36,244 O2/UBSan scenarios, including three further HUD paths.
The public actual-owner fixture passes 1,706 cases. Production dispatch remains
undefined; no fragment receives source acceptance or exact credit. The native
527 denominator reads EnemyHealth.field04 through a folded offset-four getter,
not a Timer base. Prior [rank/control evidence](ENEMY_RANK_CONTROL_RECONSTRUCTION.md)
and genuine Runtime destination/time operations remain valid.

The accepted whole Enemy defeat and real Feedback/reward/indexed-script protocols
remain intact. Feedback is still 114/native115 with one unexplained post-call NOP;
its full 133-byte constructor stays exact. Reuse the passing CORE156 real-owner
and guarded storage fixtures for unchanged bodies. See
[state protocols](ENEMY_DEFEAT_STATE_RECONSTRUCTION.md) and
[whole defeat](ENEMY_DEFEAT_RECONSTRUCTION.md).

## Current verification and cleanup

TextLine.hpp/cpp select one provider / one previous unit. One diagnostic build
and one final canonical build run serially at reduced priority. The previous
219-byte TextLine unit and four new complete units strictly pass; the other
163 providers reuse valid evidence. Both complete emitted INT3 tails and every
relocation are compared. Two complete handlers and shared flags-5 metadata
separately replay 94 bytes. No full CI or unfiltered whole-graph replay runs.

Current private proofs are `core160-cold-proof.json`,
`core160-affected-results.json.gz`, `core160-new-exact-results.json.gz`,
`core160-independent-bindings.json`, `core160-ascii-native-identity.json`,
`core160-ascii-callable-identity.json`, `core160-ascii-semantics.log`,
`core160-public-test-proof.json` and `core160-gates.json`.
These filenames and other private filenames below are relative to `.analysis/`.
The actual-owner fixture passes 256 dirty constructions, 81,920 complete
TextLine images, 768 shared-file selections and a separate noexcept termination
path. The earlier FrontInf fixture's twelve inputs are unchanged; its passing
1,706 cases remain valid. The affected whole-dispatcher fixture also passes all
36,244 cases after its recorded TextLine.hpp input changes. Its candidate/cases
are unchanged; see
`core160-dispatch-host-recipe.json` and `core160-dispatch-host.log`.

`core160-retirement-plan.json` records retirement of the replaced TextLine
object/receipt, initial probe pair and successful regenerable host binary:
five files / 960,418 bytes, after preserving authentic receipts and SHA-bound
input texts. All 328 canonical files, twenty private products and 337 native
evidence/active inputs retain their protected hashes. `core160-cleanup.json`
records the removed paths' inventory and hash checks;
cleanup itself adds zero compiler builds and zero canonical replays.
The preceding documentation-only `handoff160-retirement-plan.json` locates three
losslessly archived historical replay logs and 67,481 bytes saved.
Reuse completed evidence when its inputs are unchanged; documentation and cleanup
do not restart verification.

Historical archive lookup remains in `handoff146-retirement-plan.json`,
`handoff149-retirement-plan.json`, `handoff152-retirement-plan.json` and
`handoff154-retirement-plan.json`, `core156-retirement-plan.json`,
`core158-retirement-plan.json` and `handoff157-retirement-plan.json`.
The handoff157 record identifies lossless archival of 101
historical logs/hash snapshots; handoff154 identifies
`core154-retired-probe-inputs.json.gz`.
The handoff160 record locates the archived core098, core099 and core141 replay
logs. Their `.log.gz` files preserve the complete original evidence.
Use `gzip.open` for their losslessly archived reports instead of old plain paths.

## Protected local products

| Canonical directory | Objects | Required companions |
| --- | ---: | --- |
| `build/core141-canonical/` | 77 | Every sibling `.receipt.json` |
| `build/core142-canonical/` | 12 | Every sibling `.receipt.json` |
| `build/core143-canonical/` | 10 | Every sibling `.receipt.json` |
| `build/core145-canonical/` | 6 | Every sibling `.receipt.json` |
| `build/core149-canonical/` | 1 | Every sibling `.receipt.json` |
| `build/core151-canonical/` | 1 | Every sibling `.receipt.json` |
| `build/core154-canonical/` | 7 | Every sibling `.receipt.json` |
| `build/core154-v2/` | 1 | Every sibling `.receipt.json` |
| `build/core156-canonical/` | 18 | Every sibling `.receipt.json` |
| `build/core158-canonical/` | 29 | Every sibling `.receipt.json` |
| `build/core159-v2/` | 1 | Every sibling `.receipt.json` |
| `build/core160-canonical/` | 1 | Every sibling `.receipt.json` |

The manifest owns these 164 objects / 328 product files. The current 279-path
source freeze is `core160-final-frozen-source.json`. Protected hashes for current
products, native evidence/active inputs and twenty private investigation products
are in `core160-retirement-plan.json`. Retain the nine root object/receipt pairs for
core103-QueryProtocol-v5 and the core109..core113 sound probes, plus
`build/core144-probes/Alignment.obj` and its receipt. Their unfinished
[damage-query](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md),
[sound](SOUND_PROTOCOL_RECONSTRUCTION.md) and
[Renderer-owner](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md) inquiries remain open.

Preserve `core160-pre-ascii-inputs.json.gz`,
`core160-pre-registration-ledgers.json.gz`,
`core160-probe-v1-original-inputs.json.gz`,
`core160-prior-dispatch-inputs.json.gz` and all earlier original-input/evidence
archives identified by the retirement plans. These retain authentic receipts
and SHA-bound source versions; receipts must never be rewritten. The current
private whole-dispatcher source remains `core159-enemy-dispatch-candidate.cpp`,
`core159-dispatch-host.cpp` and `core159-front-host-cases.inc`; its refreshed
recipe is `core160-dispatch-host-recipe.json`. Earlier candidates/fixtures and
unfinished owner/phase/protocol inputs remain protected; reuse their evidence
rather than repeating rejected trials.

## Next work

1. Continue the whole Enemy dispatcher with actual owners, complete control flow,
   tables and compiler contributions. The 0x48C010 root has 41,967 ordinary body
   bytes; no case fragment receives partial exact credit. Reuse the existing
   [state](ENEMY_DISPATCH_STATE_RECONSTRUCTION.md),
   [Card](ENEMY_CARD_STATE_RECONSTRUCTION.md),
   [clear](ENEMY_CLEAR_PROTOCOL_RECONSTRUCTION.md) and
   [movement](ENEMY_DISPATCH_MOVEMENT_RECONSTRUCTION.md) evidence. The new
   [rank/control](ENEMY_RANK_CONTROL_RECONSTRUCTION.md) and
   [FrontInf](FRONT_OWNER_RECONSTRUCTION.md) frontiers identify the fourteen
   remaining nondefault state paths and the handle-preservation requirement.
   AsciiInf now supplies the real shared-file receiver. Continue the complete
   0x140-byte Dialogue owner and 1,738-byte constructor at 0x4AF310, actual Cursor
   lifetime, animation/cancellation calls and ready-state protocol; see
   [text-resource evidence](ASCII_OWNER_RECONSTRUCTION.md).
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
