# Current reconstruction handoff

The latest confirmed reconstruction batch closes the complete 134-byte
ProgressMetadata checksum, correcting its return ABI and signed pointer
comparison. Earlier CORE/EXACT-164 independently audited the complete Enemy
mesh deformation root and expanded its boundary tests. Start with this
page, [generated progress](PROGRESS.md) and the [evidence index](EVIDENCE_INDEX.md).
Do not restart completed validation merely to review the handoff.

## Verified reconstruction state

The sole target is Japanese v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Embedded title/replay strings say 1.00c in this same file. The Steam-original
backup is provenance evidence; see [target provenance](TARGET_PROVENANCE.md).

The graph contains 992 physical strict units, 164 canonical objects and 180,723
disjoint comparison bytes. All 1,001 mapped functions have source; nine whole
mapped functions remain nonexact. Authored exact coverage is separately
206 functions / 56,350 bytes, with 218 confirmed authored origins. The reference
retains 6,945 terminal implementation reviews and 113 reconciled parser-gap files.
Whole-game 95% byte exactness, complete compilation/linkage and a playable
reconstruction remain unproved.

CORE161 closes the complete 0x140-byte Dialogue storage and 1,738-byte constructor,
actual callbacks/ready getters, the genuine 0x58-byte Laser controller and its
179-byte constructor/context routing. Eleven new strict units add 2,230 comparison
bytes; full EH support separately passes 157 bytes. A 17-byte Context pointer
getter folds to an existing physical ScriptStack unit without duplicate credit.
See [Dialogue owner evidence](DIALOGUE_OWNER_RECONSTRUCTION.md). Earlier
[FrontInf](FRONT_OWNER_RECONSTRUCTION.md) and [AsciiInf](ASCII_OWNER_RECONSTRUCTION.md)
construction remain accepted; native resource retirement/frame execution stay open.

The private whole Enemy draft still covers 110 effective values / 81 primary
heads. It passes 36,232 O2/UBSan cases with actual Dialogue construction and ready
reads. Twelve old synthetic getter mutation/exception cases are retired because
the recovered getters are pure. Production dispatch remains undefined; no case
fragment receives source acceptance or partial exact credit.

CORE/EXACT-162 reconstructs the 228-byte Dialogue destructor and its complete
233-byte compiler contribution. It retires fifteen actual animation handles
in the native order and leaves handle +70 untouched. All 14 independent
relocations and seven existing same-provider units strictly pass from a new
cold-built DialogueText object; portable production-owner retirement order
and populated Cursor destruction pass 512 dirty constructions. The full resource/frame VM remains open; see [Dialogue evidence](DIALOGUE_OWNER_RECONSTRUCTION.md).

CORE/EXACT-163 closes the whole 387-byte Dialogue follow-box and 63-byte
AnimationHandle child-forwarding method, with 26 independently mapped relocations.
The native WindowState coordinate scale is proven at global +20C0, and the
Dialogue TU now uses exact `/fp:strict` for all nine previously accepted units
plus follow-box. The portable production-owner fixture exercises real intrusive
child traversal, missing/invalid handles, X/Y scaling, three placement modes,
retained Z and cross-FrontInf callback routing. These two functions add 450
physical comparison bytes. The affected include-closure providers, not the
whole graph, are the correct cold-build scope.

## Current verification and cleanup

CORE/EXACT-165 corrects `ProgressMetadata::calculate_integrity` at 0x463F20:
its return is a byte, not the previously declared uint32_t; the native signed
32-bit address comparison and actual array-first-element expression now emit the
whole 134-byte target. All six relocations are independently supported by prior
exact LockRegistry/Worker and compiler-security roles. The 161-byte Metadata
integrity update also remains exact with its corrected callee symbol. Actual
include closures select **8 providers and 22 old strict units**. All eight are
cold-built at reduced priority into `build/core164-canonical/`; all 22 old
units and the new complete unit strictly replay exactly (**23/23**). The
remaining 156 canonical providers reuse unchanged valid evidence. All five
focused progress test suites pass. The original eight object and eight receipt
hashes are protected in `core164-progress-scope.json`, while the new
`core165-progress-final-proof.json` records verification results. Source ABI,
exactness and portable fixture limitations are in
[focused evidence](PROGRESS_INTEGRITY_BYTE_EXACT.md). No whole-graph replay was run.

CORE/EXACT-164 touches only the Enemy mesh host semantics test and focused
evidence/handoff prose. Its complete native 1,649-byte code audit confirms
three writes (and zero direct reads/address formations) of stack byte -31,
with independently identified 32.0/64.0/255.0 constants. The real mesh
production fixture passes 1,536 whole-owner deformation cases spanning those
thresholds, growing/equal/shrinking radius targets, independent geometry,
color, UV and strip checks. This **does not** grant whole-root exact credit;
`EnemyState::update_mesh` remains 1,548-source/1,649-native nonexact. The
CORE164 reconstruction graph is unchanged; its affected cold-build/strict
replay scope is **zero units**. Private evidence is
`core164-mesh-unused-byte-audit.json`; unrelated diagnostic drop/compression
probes remain ignored and unaccepted.

CORE163 changed the two source files `DialogueText.cpp` and
`AnimationHandle.cpp`, plus the existing handle declaration header. Actual
`/showIncludes` closures in original authenticated receipts select **53
providers / 351 strict units**; 51 previously accepted objects are rebuilt
serially at `nice 15` into `build/core163-canonical/` without overwriting the
original objects or receipts. The other two are already fresh in this
canonical directory. All **351/351** complete strict comparisons pass after
25 MSVC-generated literal labels were reconciled. Each old/new COFF literal
has identical complete bytes, and each native constant agrees through NUL;
2 native string-pool padded extents differ outside the original literal. No
target byte was solved to obtain any relocation. The other **111 unaffected
providers** reuse their previously validated original receipts; no unfiltered
whole-graph replay is performed.

Protected input hashes and the 53/351 affected closure are recorded privately in
`core163-affected-scope.json`. The self-contained result index is
`core163-affected-final-proof.json`: 351/351 full exact replays covering 63,053
affected comparison bytes, all 53 current canonical receipts, all 106 protected
old-object/receipt hashes, and 111 valid unaffected receipts. Three disjoint
comparison batches and `core163-literal-reconciliation.json` retain all native
literal identity evidence. Original object and receipt SHA-256 values
match the frozen scope after all builds. Native game target SHA-256 stays locked.

Prior CORE161 validated 59 providers / 392 previous units and eleven new
whole units. That historical evidence was not recompiled outside this turn's
actual affected closure. Complete INT3 tails, Cursor cleanup and shared
exception metadata are retained.

The actual-owner fixture passes 512 guarded dirty constructions, 24 exception
unwinds, 2,049 live callbacks and 3,072 full-width ready reads. The affected
FrontInf fixture passes 1,706 cases; AsciiInf passes 256 dirty constructions,
81,920 complete line images and 768 shared-file selections. The updated whole-root
fixture passes 36,232 cases. Source and fixture limitations are explicit in the
focused evidence; these are portable checks, not native game execution.

Historical CORE161 private proofs include `core161-cold-proof.json`,
`core161-affected-results.json.gz`, `core161-new-exact-results.json.gz`,
`core161-independent-bindings.json`, `core161-existing-role-reconciliation.json`,
`core161-protocol-native-identity.json`, `core161-public-test-proof.json`,
`core161-dispatch-host-recipe.json`, `core161-dispatch-host.log` and
`core161-gates.json`. Private filenames here are relative to `.analysis/`.
Registration/finalization scripts are not idempotent; consume their saved reports
rather than rerunning admission or cleanup.

`core161-retirement-plan.json` inventories 123 retired files / 5,306,440 bytes:
59 replaced object/receipt pairs, two superseded probe pairs and the successful
regenerable host binary. Authentic receipts and SHA-bound input texts are archived
before removal. `core161-cleanup.json` confirms all 328 current canonical files,
twenty private investigation products and 356 native evidence/active inputs
retain their protected hashes. The preceding CORE161 cleanup phase added zero compiler builds/replays; the
separate CORE163 phase above did rebuild exactly the affected 53 providers.

## Protected local products

| Canonical directory | Objects | Required companions |
| --- | ---: | --- |
| `build/core141-canonical/` | 68 | Every sibling `.receipt.json` |
| `build/core142-canonical/` | 7 | Every sibling `.receipt.json` |
| `build/core145-canonical/` | 3 | Every sibling `.receipt.json` |
| `build/core149-canonical/` | 1 | Every sibling `.receipt.json` |
| `build/core151-canonical/` | 1 | Every sibling `.receipt.json` |
| `build/core154-canonical/` | 5 | Every sibling `.receipt.json` |
| `build/core154-v2/` | 1 | Every sibling `.receipt.json` |
| `build/core156-canonical/` | 1 | Every sibling `.receipt.json` |
| `build/core158-canonical/` | 10 | Every sibling `.receipt.json` |
| `build/core161-canonical/` | 6 | Every sibling `.receipt.json` |
| `build/core163-canonical/` | 53 | Every sibling `.receipt.json` |
| `build/core164-canonical/` | 8 | Every sibling `.receipt.json` |

The manifest owns these 164 objects / 328 product files. Earlier authentic
object/receipt pairs remain in their original directories without alteration;
private CORE161 hashes and the new CORE163 scope both protect the old products.
The previous 279-path source freeze is `core161-final-frozen-source.json`.
Protected historical product, source, native-evidence and test hashes remain
in `core161-retirement-plan.json`.
Retain the nine root object/receipt pairs for core103-QueryProtocol-v5 and the
core109..core113 sound probes, plus `build/core144-probes/Alignment.obj` and its
receipt. These twenty files are historical unfinished-investigation snapshots;
their original receipts/inputs must not be rewritten as current builds. See
[damage query](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md),
[sound](SOUND_PROTOCOL_RECONSTRUCTION.md) and
[Renderer ownership](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md).

Preserve `core161-pre-dialogue-inputs.json.gz`,
`core161-pre-registration-ledgers.json.gz`,
`core161-probe-v1-original-inputs.json.gz`,
`core161-probe-v2-original-inputs.json.gz`,
`core161-prior-dispatch-inputs.json.gz` and all earlier original-input/evidence
archives. Current private root inputs are `core159-enemy-dispatch-candidate.cpp`,
`core161-dispatch-host.cpp`, `core161-front-host-cases.inc` and the core161 recipe;
earlier candidates and incomplete protocols remain protected.

Historical archive lookup remains in the handoff146/149/152/154/157/160 and
core156/158/159/160 retirement plans. They preserve archived logs, snapshots and
original inputs. Read `.json.gz` / `.log.gz` through `gzip.open`; old plain paths
may have been retired losslessly. Preserve installed tools, reference source,
Ghidra, native exports and supplied `../game_exe/` files.

## Next work

1. Continue the whole Dialogue frame/message VM, native resource retirement,
   and Cursor constructor emission. Follow-box and its real child lookup are
   now closed; the Renderer and Animation pool integration remain open.
2. Continue the complete Enemy dispatcher at 0x48C010, including its 41,967-byte
   ordinary body, tables and compiler contributions. Fourteen nondefault state
   paths remain unresolved. Reuse [FrontInf callers](FRONT_OWNER_RECONSTRUCTION.md),
   [rank/control](ENEMY_RANK_CONTROL_RECONSTRUCTION.md),
   [state](ENEMY_DISPATCH_STATE_RECONSTRUCTION.md),
   [Card](ENEMY_CARD_STATE_RECONSTRUCTION.md),
   [clear](ENEMY_CLEAR_PROTOCOL_RECONSTRUCTION.md) and
   [movement](ENEMY_DISPATCH_MOVEMENT_RECONSTRUCTION.md) evidence. Preserve native
   stale-handle behavior and complete extents; no partial-root credit.
3. Resolve the genuine Renderer allocation 0x7D40E94 and +6000DFC..+6000DFF before
   declaring fields. Negative searches do not prove padding. This blocks whole
   File::clear, texture creators and the 922-byte File spawn producer. The
   40,752-byte Animation VM also remains open; see
   [pool/owner evidence](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md),
   [File lifetime](ANIMATION_FILE_LIFETIME_RECONSTRUCTION.md) and
   [whole dispatch](CORE_ECL_DISPATCH_RECONSTRUCTION.md).

The nine source-present whole nonexact roots are:

| Root | Entry | Current boundary / evidence |
| --- | --- | --- |
| FunctionChainController::remove_unlocked | 0x412400 | 156/native162; [scheduler](FUNCTION_CHAIN_ALLOCATION_EXACT_RECONSTRUCTION.md) |
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
[tool routing](TOOLS.md). Commit subjects use **`gpt-web: <description>`**.
Use one writable session, no REA or delegated reconstruction, and serial heavy
work at nice 15 / CPU 3 with bounded Ghidra memory. Use scripts/repo-python;
keep claims header-only and maintained prose in English, preserving the official
Japanese target title.

Reuse passing evidence for unchanged inputs. Before new validation, identify
changed inputs and actual affected providers from captured includes/manifest
roles; use explicit source filters or individual units. Documentation and cleanup
alone select zero replay units: skip Ghidra, MSVC and full CI. Never run an
unfiltered replay for handoff or reassurance. Preserve authentic original inputs
before edits/retirement and check protected hashes after cleanup.
