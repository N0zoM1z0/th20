# Whole Enemy defeat reconstruction

CORE/EXACT-155 accepts the complete Enemy::defeat source at 0x4A5640 in
`src/EnemySpawnApplication.cpp`, first maintained in CORE154. Thirteen complete
units strictly replay 1,886 disjoint ordinary bytes; the authored caller accounts
for 1,371 bytes. Complete independent EH code/data replay supports its acceptance.
Current totals remain in [the handoff](RE_HANDOFF.md).
The production Enemy opcode dispatcher remains undefined.

## Independently identified process owner

Native factory 0x514240 publishes the allocation from 0x5117E0 at process slot
0x5C6118. Its independent allocation diagnostic names `StoneEnemyCtrlInf` in
`src/game/stoneenemy.cpp:67`. The allocation is 0xB4 bytes. Constructor 0x511980
constructs the real intrusive list, two Timers, float/byte/float interpolations,
then clears byte +B0. Destructor 0x511A30 retires the actual list records;
release 0x513CC0 frees the allocation and clears the process slot.

The maintained StoneEnemyController uses the complete observed storage:

| Offset | Member |
| --- | --- |
| 0x00 | IntrusiveList<StoneEnemyRecord> |
| 0x18, 0x28 | Timer |
| 0x38 | FloatInterpolation |
| 0x64 | Interpolation<uint8_t> |
| 0x84 | FloatInterpolation |
| 0xB0 | Raw byte reward gate |

The original record type spelling and remaining member meanings are unknown.
The record is forward-declared, not replaced by a prefix. Controller destruction
and allocation remain undefined production interfaces. The getter at 0x485A40
returns the raw byte; no boolean field or TaskInfo/vtable base is inferred.

## Complete maintained caller

The caller recursively defeats each observed child, reloads its node through
the link before setting bit9, destroys the iterator, then detaches its parent
link. Sound precedes direction calculation and optional animation publication.
The near-distance comparison evaluates 0.2f * 0.2f; the fallback direction is
negative pi / 2. The effect owner is cached before file lookup, and the spawned
raw handle is cached before publishing it through that owner. Controller angle
publication and the real drop protocol follow.

The damage-marked branch updates PlayerFeedback, reads its live counter at +38, selects
one of ten multipliers and divides the wrapped signed low 32-bit product by 100.
The record updates also wrap before clamping. The first process gate controls
field5C, while a fresh gate read after WeaponStoneInfo publication independently
controls the selected reward. The special fifth kind consumes another random
sample. Record and configuration evaluation retain their observed call order.

An optional script terminates asynchronous work, resets, selects the live index
and ticks the actual EclManager with positive zero before clearing field27C.
Only that script path can return zero from bit27. Otherwise the real std::function
callback runs before returning one. Exceptions preserve earlier side effects.

## Complete accepted units

| Complete unit | Native entry | Ordinary bytes |
| --- | --- | ---: |
| Enemy::defeat | 0x4A5640 | 1,371 |
| StoneEnemyController construction | 0x511980 | 90 |
| StoneEnemyController::byte_b0_value | 0x485A40 | 21 |
| stone_enemy_controller | 0x513DD0 | 10 |
| Enemy::damage_marked | 0x4AB300 | 26 |
| Player::feedback_value | 0x4AAA60 | 19 |
| player | 0x460830 | 26 |
| geometry::direction_xy | 0x47A2E0 | 55 |
| PlayerRecord::add_field_44 | 0x4A9FB0 | 75 |
| PlayerRecord::add_field_5c | 0x477F60 | 75 |
| std::function nonempty predicate | 0x4145A0 | 48 |
| std::_Func_class empty predicate | 0x414A80 | 45 |
| std::_Func_class implementation getter | 0x414AD0 | 25 |

All thirteen complete units pass zero-difference canonical relocation replay.
The three SDK functions have independently established library origins and no
authored credit. The other nine owner helpers retain pending origin classification;
exact emission does not establish authorship. The feedback count getter folds
to an existing physical unit and receives no duplicate mapping or byte credit.

EnemySpawnApplication.cpp uses the local /fp:strict candidate profile: /fp:precise
folded the literal multiplication/division observed as native operations. This
does not establish global game flags. The previously accepted apply_spawn unit
still strictly passes under the updated profile. The GeometryMetrics namespace
correction has its own fresh object and seven passing existing units.

Independent binding uses full native callees, existing canonical owner roles and
the unique immutable 0.2f value at 0x56FBF8. The complete 55-byte cleanup/handler
section at 0x569780 and 44-byte unwind-map/FuncInfo section at 0x5AA9A4 have one
joint identity. Both replay completely, including the cleanup tail jump and its
five compiler-generated alignment bytes. Ghidra's existing listing omits those
first thirteen bytes; a bounded locked-PE decode corroborates the whole section.
The root's compared relocation field supplies no destination.

The actual std::bad_function_call helper is independently identified through its
native ThrowInfo and two catchable type descriptors. PlayerRecord::add_reward's
native boundary retains all 95 code bytes, one NOP and its eight-entry/32-byte
table. No table or padding is shortened to match a caller.

## Counter correction and remaining callee boundaries

The original candidate count getter read +30. The independently accepted physical
getter at 0x438520 reads +38; native record_hit increments that word and copies it
to +30. Their ordinary post-update equality hid the wrong getter in the first
fixture. The maintained body now reads +38, strictly matches the complete 17-byte
physical alias and has an unequal-word test. Only PlayerStorage.cpp is rebuilt.

Two independently identified callee roles retain nonexact emitted bodies:

| Callee | Current / native bytes | Preserved observation |
| --- | ---: | --- |
| IntrusiveList construction at 0x418A50 | 31 / 40 | Native code publishes tail +14 twice after the real link constructor; maintained source publishes it once. |
| std::_Func_class invocation at 0x4A3F20 | 69 / 83 | Native code calls the out-of-line identity-forward helper before virtual slot +8; current code passes the argument address directly. |

Their complete native roles, receiver storage and calling conventions independently
anchor the accepted callers; neither callee receives standalone exact credit.
SDK/emission provenance remains unresolved. The actual function storage is 40
bytes on x86 and its implementation pointer is slot9 at +0x24.

CORE156 maintains the full Feedback, reward and indexed-selection bodies in
[the state protocol](ENEMY_DEFEAT_STATE_RECONSTRUCTION.md). The Feedback update
remains 114/native115 and nonexact. weapon_stone_info, SoundInf::request_effect_at
and the Controller resource dispatcher remain undefined production interfaces;
resource creation and VM execution remain separate integration boundaries.

## Bounded verification and retained evidence

CORE155 changes only PlayerStorage.cpp. Captured include closures select one
provider / seven existing units, all freshly built and strictly replayed. The
other 163 providers reuse valid receipts. Thirteen new canonical units reuse the
unchanged CORE154 objects and pass their own complete replay. The earlier
52-provider/364-unit CORE154 proof remains preserved; it is not repeated.
No whole-graph replay or full CI is run.

The public O2/UBSan fixture passes 10,240 combinations, eight remaining external
interface failures and five recursive topology cases. It uses maintained owner storage, actual
handle publication, record clamps and random advancement. It checks full actor,
Controller, record and feedback images, event prefixes, script returns, pending
child detachment, post-call node reload and iterator cleanup after exceptions.
The corrected getter is tested with unequal +30/+38 words. CORE156 replaces the
Feedback/reward/reset/index captures with actual maintained bodies and adds their
independent state models; see [state verification](ENEMY_DEFEAT_STATE_RECONSTRUCTION.md).
Earlier Enemy creation/clear and spawn/tick results are retained.

The test domain uses live owner pointers, nonnegative feedback counts, valid
effect cursors, finite positions and acyclic child lists. Resource-free startup,
unreconstructed VM execution, feedback/reward bodies and resource creation are
explicit captures. Portable fixture execution does not prove Windows resource
integration or a whole-program product.

Private evidence is retained under `.analysis/`: the `core153..155-*native.asm`
exports, `core155-independent-bindings.json`, `core155-new-exact-results.json.gz`,
`core155-counter-exact-results.json.gz`, graph audit and semantic log. Authentic
inputs/receipts are in `core155-pre-counter-inputs.json.gz`,
`core155-pre-registration-ledgers.json.gz`, `core154-pre-acceptance-inputs.json.gz`,
`core154-pre-geometry-namespace-inputs.json.gz`,
`core154-pre-publication-inputs.json.gz` and `core154-v4-original-inputs.json.gz`.
The handoff identifies the current freeze and retirement inventory. Cleanup
checks protected hashes and adds zero compiler or replay invocations.
