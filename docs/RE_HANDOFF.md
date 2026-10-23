# Current reconstruction handoff

This page records current acceptance, protected local products and next work.
Use [generated progress](PROGRESS.md), the ledgers and the status reporter for
live counts; dated investigations are routed through the [evidence index](EVIDENCE_INDEX.md).

## Verified reconstruction state

The sole target is Japanese v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Its embedded title/replay label is 1.00c in the same executable. The Steam-original
backup is provenance evidence. See [target provenance](TARGET_PROVENANCE.md).

The graph contains 928 physical strict units, 164 canonical objects and 172,008
disjoint comparison bytes. All 937 mapped functions have source; nine whole
mapped functions remain nonexact. Authored exact coverage is separately 189
functions / 49,912 bytes, with 201 confirmed authored origins. The pinned
reference has 6,945 terminal implementation reviews and 113 reconciled parser-gap
files. These counts establish neither whole-game 95% byte exactness nor a
playable reconstruction; whole-program compilation and linkage remain open.

CORE152 extends the same private whole-root draft to 96 values / 67 heads with
clear, selection and return paths. It passes 19,350 bounded O2/UBSan scenarios;
the production dispatcher remains undefined and receives no partial exact credit.
The public actual-owner fixture separately checks 4,636 clear protocol cases.
Five complete dependencies add 2,088 strict bytes; the four authored clear roots
account for 2,062 bytes, while the flag query origin remains pending. The genuine
whole Enemy::defeat at 0x4A5640 remains source-absent. See
[clear protocol](ENEMY_CLEAR_PROTOCOL_RECONSTRUCTION.md); retained
[Card callers](ENEMY_CARD_STATE_RECONSTRUCTION.md) and
[health/boss state](ENEMY_HEALTH_BOSS_STATE_RECONSTRUCTION.md) remain valid.

## Current verification and cleanup

Only 17 affected providers / 82 previous units are cold-built and strictly
replayed, followed by the five new units. The other 147 providers reuse existing
evidence. The focused public Enemy creation/clear test and expanded private
whole-root fixture pass. There is no unfiltered replay or full CI run.
Current proofs are `.analysis/core152-cold-proof.json`,
`core152-affected-results.json.gz`, `core152-new-exact-results.json.gz` and
`core152-graph-audit.json`; cleanup and final gates are `core152-cleanup.json`
and `core152-gates.json`. Cleanup only verifies protected hashes.
The 39 superseded product files total 2,248,403 bytes; their authentic probe and
fixture inputs/receipts are preserved in the 341,878-byte retirement archive.
The earlier handoff's archived successful reports remain mapped by
`handoff146-retirement-plan.json`; use `gzip.open` for their verified `.gz` copies.
Native evidence, original inputs, installed tools, reference, Ghidra and supplied
game files remain protected.

The earlier documentation-only archive lookup remains
`handoff149-retirement-plan.json`. Read `handoff144-protected-inventory.json.gz`
and `core131-admission-results.json.gz` with `gzip.open` instead of their old paths.

Historical source-hash snapshots are losslessly archived through
`handoff152-retirement-plan.json`. Current source freezes, original inputs and
active evidence remain protected; read the archived reports with `gzip.open`.

## Protected local products

| Canonical directory | Objects | Required companions |
| --- | ---: | --- |
| `build/core141-canonical/` | 84 | Every sibling `.receipt.json` |
| `build/core142-canonical/` | 16 | Every sibling `.receipt.json` |
| `build/core143-canonical/` | 12 | Every sibling `.receipt.json` |
| `build/core145-canonical/` | 17 | Every sibling `.receipt.json` |
| `build/core148-canonical/` | 14 | Every sibling `.receipt.json` |
| `build/core149-canonical/` | 2 | Every sibling `.receipt.json` |
| `build/core151-canonical/` | 2 | Every sibling `.receipt.json` |
| `build/core152-canonical/` | 17 | Every sibling `.receipt.json` |

The manifest owns these 164 objects / 328 product files. The current 279-path
source freeze is `.analysis/core152-final-frozen-source.json`. Current acceptance,
affected replay and graph contracts are the CORE152 records above. Earlier
independent identities and original acceptance
remain preserved in their focused evidence and private archives.
Private filenames in this section are relative to `.analysis/`.

Retain the nine investigation object/receipt pairs at the build root:
core103-QueryProtocol-v5 and the core109..core113 sound probes. Their original
closures support unresolved [damage-query](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md)
and [sound](SOUND_PROTOCOL_RECONSTRUCTION.md) work, not current canonical credit.
Hashes are in `core141-retained-private-products.json`. Also retain the current
`build/core144-probes/Alignment.obj` and receipt for the unfinished owner inquiry.
The superseded CORE152 clear probes and completed host binary are retired.
Their original receipts and SHA-bound inputs are in `core152-retired-inputs.json.gz`;
native exports, rejected source and the active draft/fixture remain intact.
Preserve `core152-pre-clear-inputs.json.gz`, `core151-pre-card-inputs.json.gz`,
all CORE151, CORE150, CORE149 and CORE148 original-input archives,
both CORE147 original-input archives,
all CORE145 original-input archives and all earlier input/evidence archives.
Receipts retain their authentic original inputs and must never be rewritten.

Preserve private `.analysis/core149-pattern/`, `.analysis/core150-owner/` and `.analysis/core151-flags/`
sources and their native exports. Unfinished emission and ABI questions retain
their complete source/native evidence; do not repeat unchanged rejected trials.
Preserve `.analysis/core152-clear/`, its native exports and the integrated
`.analysis/core152-enemy-dispatch-candidate.cpp` / `core152-dispatch-host.cpp`.
The retired probe receipts remain authentic in the archive above; the whole
dispatcher draft still has no accepted source, mapping or exact credit.

## Next work and existing private leads

1. Resolve the genuine Renderer owner before declaring its members. Allocation is
   0x7D40E94 bytes; +6000DFC..+6000DFF remains unexplained. Negative direct-access
   searches do not prove padding. The current compiler probe and its limited
   exclusions are preserved in [pool/owner evidence](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md);
   reuse those results rather than repeating the unchanged trial.
   This boundary blocks authored, source-absent File::clear at 0x44AB00 (284 bytes),
   texture creators at 0x44C0B0 / 0x44C150 (155 / 139 bytes), and the full
   AnimationFile::spawn at 0x450CB0 (922 bytes). Follow
   [File lifetime](ANIMATION_FILE_LIFETIME_RECONSTRUCTION.md),
   [texture evidence](ANIMATION_TEXTURE_FORMAT_RECONSTRUCTION.md) and
   [mesh/ANM origins](MESH_RESOURCE_ORIGIN_AUDIT.md). Preserve real loaded-resource
   retirement, the opaque +6C buffer owner, early optional output publication,
   hidden handle return and complete VM registration. Convenience wrappers do not
   close the producer. File allocation keeps its existing profile without /EHsc;
   the 129/native67 trial does not justify changing child exception contracts.
2. Continue whole dispatch protocols, with complete control flow and tables.
   The Animation VM at 0x42B5D0 has a complete 40,752-byte extent; callback/lambda,
   Renderer, mutable ANM packet/buffer and startup owners remain open. See
   [dispatch evidence](CORE_ECL_DISPATCH_RECONSTRUCTION.md) and
   [callback contracts](ANIMATION_CALLBACK_RECONSTRUCTION.md).
   EnemyState::execute_opcode at 0x48C010 has 41,967 body bytes; whole compiler
   contribution ownership remains unresolved. Continue the same whole-root
   source construction beyond the private 400..448 movement draft. The 500..575
   owner/state family has a private 75-value / 71-head catalog, complete phase
   producers and phase, counter, drop, health, boss, Card, clear, selection and
   return paths in the integrated private draft. Continue its remaining genuine
   receiver ownership and state paths; reuse the closed record
   defaults, replacement gates, counters, drop/scatter, checked publication and
   the Card decoding/live-metadata sequence. The source-absent native Card start
   at 0x487C30 (1,896 ordinary bytes) and finish at 0x4878B0 (602 bytes) need real
   UI/record/Renderer closure; preserve full EH/resource effects before coding
   them. The whole 1,371-byte Enemy::defeat at 0x4A5640 also needs genuine
   recursive child/script/resource closure; its declaration and captured calls
   receive no source or exact credit. See [clear protocol](ENEMY_CLEAR_PROTOCOL_RECONSTRUCTION.md),
   [Card caller protocol](ENEMY_CARD_STATE_RECONSTRUCTION.md),
   [health and boss state](ENEMY_HEALTH_BOSS_STATE_RECONSTRUCTION.md),
   [drop protocol](ENEMY_DROP_PROTOCOL_RECONSTRUCTION.md),
   [state opcode frontier](ENEMY_DISPATCH_STATE_RECONSTRUCTION.md) and
   [phase protocol](ENEMY_PHASE_PRODUCER_INVESTIGATION.md). The movement draft, exact word dependency,
   independent operand-read order and remaining member-call boundaries are in
   [movement source frontier](ENEMY_DISPATCH_MOVEMENT_RECONSTRUCTION.md).
   Reuse actual owners and the accepted animation sub-dispatcher. Preserve the
   native default return and full tables/EH; private exercise factoring and its
   out-of-domain exception are not production replacements.

The nine source-present whole nonexact roots remain:

| Root | Entry | Current boundary / evidence |
| --- | --- | --- |
| FunctionChainController::remove_unlocked | 0x412400 | 156/native162; retain real class and observed reset behavior. [Scheduler](FUNCTION_CHAIN_ALLOCATION_EXACT_RECONSTRUCTION.md) |
| ProgressMetadata::calculate_integrity | 0x463F20 | Whole 134-byte native root; [Progress storage](EXACT_PROGRESS_STORAGE_RECONSTRUCTION.md) |
| create_bomb_controller | 0x478300 | Whole 123-byte native factory; [Bomb owner](BOMB_OWNER_RECONSTRUCTION.md) |
| EnemyState::update_mesh | 0x4A4190 | 1548/native1649; unused local conversion is not a source fix. [Mesh lifetime](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md) |
| EnemyPattern::emit_items | 0x4A5350 | 628/native630; extra native register copy remains unexplained. [Drop protocol](ENEMY_DROP_PROTOCOL_RECONSTRUCTION.md) |
| create_hit_controller | 0x4C20D0 | 82/native92; unobserved resets remain unresolved. [Hit lifecycle](HIT_CONTROLLER_LIFECYCLE_RECONSTRUCTION.md) |
| ProgressSaveManager construction | 0x50E5D0 | 198/native199; [lifetime/profile](PROGRESS_LOAD_LIFETIME_EXACT_RECONSTRUCTION.md) |
| ProgressSaveManager::commit | 0x50F660 | 68/native70; same lifetime/profile evidence |
| archive_compress | 0x539550 | Whole 1,036-byte native root; [write protocol](ARCHIVE_WRITE_RECONSTRUCTION.md) |

Do not repeat unchanged rejected profile trials or insert inert operations to
shape output. SaveManager's post-call NOPs remain unexplained; C++17 is
inapplicable because its real Worker contains std::jthread. Preserve actual void
and exception contracts. The compressor's unobserved sum is not a source fix.
The whole 1,707-byte damage query also remains unimplemented; its counter and
release-before-read ownership questions remain open. Focused documents retain
the corresponding rejected probes and semantic limits.

## Resume discipline

Follow [AGENTS.md](../AGENTS.md) and its preflight. Invoke Python through
`scripts/repo-python`, Ghidra through `scripts/ghidra.py`, and keep one writable
session. Run heavy work serial at nice 15 / CPU 3, with bounded Ghidra memory.
No REA or delegated reconstruction. Preserve English maintained prose, the
official Japanese title and commit prefix `gpt-6.1-sol:`. Keep claims header-only.
For documentation and cleanup of an unchanged graph, check diffs, links and
protected hashes; skip Ghidra, MSVC, full CI and replay. For reconstruction
changes, derive affected providers from actual include closures and manifest
dependencies, then build and replay only those units. Use explicit `--source`
filters or individual unit commands. Do not run an unfiltered replay for handoff.
