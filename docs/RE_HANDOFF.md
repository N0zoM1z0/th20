# Current reconstruction handoff

This page records current acceptance, protected local products and next work.
Use [generated progress](PROGRESS.md), the ledgers and the status reporter for
live counts; dated investigations are routed through the [evidence index](EVIDENCE_INDEX.md).

## Verified reconstruction state

The sole target is Japanese v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Its embedded title/replay label is 1.00c in the same executable. The Steam-original
backup is provenance evidence. See [target provenance](TARGET_PROVENANCE.md).

The graph contains 897 physical strict units, 164 canonical objects and 168,151
disjoint comparison bytes. All 905 mapped functions have source; eight whole
mapped functions remain nonexact. Authored exact coverage is separately 181
functions / 47,071 bytes, with 190 confirmed authored origins. The pinned
reference has 6,945 terminal implementation reviews and 113 reconciled parser-gap
files. These counts establish neither whole-game 95% byte exactness nor a
playable reconstruction; whole-program compilation and linkage remain open.

CORE/EXACT-145 accepts the complete 94-byte GameRandom::next_word at 0x497470.
It records the raw engine result and returns its low 16 bits under the real
slot-10 mutex, bypassing modulus division. Its origin remains pending. The whole
Enemy dispatcher also has a private movement candidate for 49 values / 24 case
heads, with 459 bounded O2/UBSan scenarios. This draft is not production source
or partial exact credit. See [movement source frontier](ENEMY_DISPATCH_MOVEMENT_RECONSTRUCTION.md).

## Current verification and cleanup

The handoff maintenance batch changes documentation and the commit convention;
production source, profiles, anchors and acceptance ledgers are unchanged.
Public CI completed before the affected-only policy correction: 84 tests passed.
It was not repeated for the subsequent documentation-only edits. The full
existing-object replay was stopped at the user's request; its partial log is
interrupted evidence, not a completed whole-graph verification. No reconstruction
unit changed, so this batch has zero affected replay units. Relevant records are
`.analysis/handoff146-ci.log`, `handoff146-cleanup.json` and
`handoff146-existing-replay.log.gz`; final gates are `handoff146-gates.json`.
`handoff146-protected-inventory.json.gz` records protected products and evidence;
`handoff146-retirement-plan.json` maps each archived historical report to its
verified lossless `.gz` copy. Current CORE145 acceptance reports stay uncompressed
where originally recorded. Older successful CI logs and inactive exact-result
snapshots may now require `gzip.open`; their original content hashes are retained.
Native evidence, original-input archives, installed tools, reference, Ghidra
database and supplied game files remain protected. No unchanged graph is cold
built for cleanup.

## Protected local products

| Canonical directory | Objects | Required companions |
| --- | ---: | --- |
| `build/core141-canonical/` | 89 | Every sibling `.receipt.json` |
| `build/core142-canonical/` | 24 | Every sibling `.receipt.json` |
| `build/core143-canonical/` | 16 | Every sibling `.receipt.json` |
| `build/core145-canonical/` | 35 | Every sibling `.receipt.json` |

The manifest owns these 164 objects / 328 product files. The current 279-path
source freeze is `.analysis/core145-final-frozen-source.json`. New acceptance and
affected replay are `core145-word-strict.json`, `core145-affected-results.json.gz`
and `core145-cold-proof.json`; current whole-graph contracts are
`core145-graph-audit.json`. Earlier independent identities and original acceptance
remain preserved in their focused evidence and private archives.
Private filenames in this section are relative to `.analysis/`.

Retain the nine investigation object/receipt pairs at the build root:
core103-QueryProtocol-v5 and the core109..core113 sound probes. Their original
closures support unresolved [damage-query](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md)
and [sound](SOUND_PROTOCOL_RECONSTRUCTION.md) work, not current canonical credit.
Hashes are in `core141-retained-private-products.json`. Also retain the current
`build/core144-probes/Alignment.obj` and receipt for the unfinished owner inquiry.
Also retain `build/core146-probes/Phase.obj` and its receipt with the original
private inputs under `.analysis/core146-phase/`. This is an unfinished producer
probe with an unproven record-construction assumption, not canonical source.

Preserve `core145-pre-header-inputs.json.gz`, `core145-retired-inputs.json.gz`,
`core145-host-original-inputs.json.gz` and all earlier original-input archives,
native exports and rejected probe sources.
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
   contribution ownership remains unresolved. Continue the same whole-root
   source construction beyond the private 400..448 movement draft. The 500..575
   owner/state family now has a private 75-value / 71-head catalog and a phase
   producer investigation. Resume at its unresolved record-construction chain;
   do not promote the private `life = time = -1` constructor guess. See
   [phase producer evidence](ENEMY_PHASE_PRODUCER_INVESTIGATION.md) for the
   complete current boundary and retained inputs. The movement draft, exact word dependency,
   independent operand-read order and remaining member-call boundaries are in
   [movement source frontier](ENEMY_DISPATCH_MOVEMENT_RECONSTRUCTION.md).
   Reuse actual owners and the accepted animation sub-dispatcher. Preserve the
   native default return and full tables/EH; private exercise factoring and its
   out-of-domain exception are not production replacements.

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
official Japanese title and commit prefix `gpt-6.1-sol:`. Keep claims header-only.
For documentation and cleanup of an unchanged graph, check diffs, links and
protected hashes; skip Ghidra, MSVC, full CI and replay. For reconstruction
changes, derive affected providers from actual include closures and manifest
dependencies, then build and replay only those units. Use explicit `--source`
filters or individual unit commands. Do not run an unfiltered replay for handoff.
