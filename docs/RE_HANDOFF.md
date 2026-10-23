# Current reconstruction handoff

This page records current acceptance, protected local products and next work.
Use [generated progress](PROGRESS.md), the ledgers and the status reporter for
live counts; dated investigations are routed through the [evidence index](EVIDENCE_INDEX.md).

## Verified reconstruction state

The sole target is Japanese v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Its embedded title/replay label is 1.00c in the same executable. The Steam-original
backup is provenance evidence. See [target provenance](TARGET_PROVENANCE.md).

The graph contains 896 physical strict units, 164 canonical objects and 168,057
disjoint comparison bytes. All 904 mapped functions have source; eight whole
mapped functions remain nonexact. Authored exact coverage is separately 181
functions / 47,071 bytes, with 190 confirmed authored origins. The pinned
reference has 6,945 terminal implementation reviews and 113 reconciled parser-gap
files. These counts establish neither whole-game 95% byte exactness nor a
playable reconstruction; whole-program compilation and linkage remain open.

The latest source acceptance is CORE/EXACT-143, commit `cfd171b`: complete
PooledAnimation/AnimationPool construction and destruction, with 65,536 genuine
records, native stride 0x600 and extent 0x6000000. Four whole units add 243 body
bytes / 253 compared bytes; their origins remain pending. See
[pool lifetime](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md) for boundaries, EH,
24 affected cold builds and the complete dirty-storage owner fixture.

## Handoff verification and cleanup

This housekeeping batch changes workflow and documentation, with no production
source, header, profile, layout or canonical manifest changes. Existing-object
replay keeps full target, receipt, extent and relocation checks; it neither
compiles nor awards new exact credit. Missing or stale products fail directly.

Public CI and complete replay logs are `.analysis/handoff144-ci.log` and
`.analysis/handoff144-existing-replay.log`. Protected inventories, retired cache
paths/bytes and Git packing checks are recorded in
`.analysis/handoff144-protected-inventory.json`, `handoff144-cleanup.json` and
`handoff144-git-packing.json`. Packing preserves every Git object, reference and
reflog without pruning. Native evidence, original-input archives, installed tools,
reference, Ghidra database and supplied game files are retained.

## Protected local products

| Canonical directory | Objects | Required companions |
| --- | ---: | --- |
| `build/core141-canonical/` | 94 | Every sibling `.receipt.json` |
| `build/core142-canonical/` | 46 | Every sibling `.receipt.json` |
| `build/core143-canonical/` | 24 | Every sibling `.receipt.json` |

The manifest owns these 164 objects / 328 product files. The unchanged 279-path
source freeze is `.analysis/core143-final-frozen-source.json`. Complete acceptance,
independent identities and earlier protected retirement are preserved in
`core143-gates.json`, `core143-boundaries.json`, `core143-graph-audit.json`,
`core143-independent-slot-identities.json` and `core143-post-cleanup-results.json.gz`.
Private filenames in this section are relative to `.analysis/`.

Retain the nine investigation object/receipt pairs at the build root:
core103-QueryProtocol-v5 and the core109..core113 sound probes. Their original
closures support unresolved [damage-query](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md)
and [sound](SOUND_PROTOCOL_RECONSTRUCTION.md) work, not current canonical credit.
Hashes are in `core141-retained-private-products.json`. Also retain the current
`build/core144-probes/Alignment.obj` and receipt for the unfinished owner inquiry.

Preserve `core143-pre-header-inputs.json.gz`, `core143-retired-inputs.json.gz` and
all earlier original-input archives, native exports and rejected probe sources.
Receipts retain their authentic original inputs and must never be rewritten.

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
   contribution ownership remains unresolved. Its current bounded dependency
   audit is preserved in [complete Enemy layout](CORE_ENEMY_DISPATCH_LAYOUT.md).
   Reuse actual owners and the accepted animation sub-dispatcher; dependency
   coverage does not establish partial root credit.

The eight source-present whole nonexact roots remain:

| Root | Entry | Current boundary / evidence |
| --- | --- | --- |
| FunctionChainController::remove_unlocked | 0x412400 | 156/native162; retain real class and observed reset behavior. [Scheduler](FUNCTION_CHAIN_ALLOCATION_EXACT_RECONSTRUCTION.md) |
| ProgressMetadata::calculate_integrity | 0x463F20 | Whole 134-byte native root; [Progress storage](EXACT_PROGRESS_STORAGE_RECONSTRUCTION.md) |
| create_bomb_controller | 0x478300 | Whole 123-byte native factory; [Bomb owner](BOMB_OWNER_RECONSTRUCTION.md) |
| EnemyState::update_mesh | 0x4A4190 | 1548/native1649; unused local conversion is not a source fix. [Mesh lifetime](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md) |
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
official Japanese title and commit prefix `gpt-6-astra-medium:`. Keep claims
header-only. For cleanup of an unchanged graph, run
`nice -n 15 taskset -c 3 scripts/repo-python scripts/replay-exact-units.py --existing-objects`;
source/header/profile changes require fresh affected cold builds.
