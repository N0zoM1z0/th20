# Whole Enemy defeat source checkpoint

CORE154 maintains the complete Enemy::defeat source at 0x4A5640 in
`src/EnemySpawnApplication.cpp`. This is a source and semantic checkpoint:
complete canonical relocation and exception-handler binding remain pending.
The ten new source candidates below receive no new mapping, origin or exact
credit. Current accepted totals remain in [the handoff](RE_HANDOFF.md).
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

The damage-marked branch updates PlayerFeedback, reads its live count, selects
one of ten multipliers and divides the wrapped signed low 32-bit product by 100.
The record updates also wrap before clamping. The first process gate controls
field5C, while a fresh gate read after WeaponStoneInfo publication independently
controls the selected reward. The special fifth kind consumes another random
sample. Record and configuration evaluation retain their observed call order.

An optional script terminates asynchronous work, resets, selects the live index
and ticks the actual EclManager with positive zero before clearing field27C.
Only that script path can return zero from bit27. Otherwise the real std::function
callback runs before returning one. Exceptions preserve earlier side effects.

## Compiler observation and acceptance boundary

| Complete source candidate | Native entry | Ordinary bytes |
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

All ten candidates have complete ordinary extents with zero differences outside
relocation fields in the pinned compiler output. This is diagnostic evidence,
not canonical exactness. The folded feedback count getter also has a maintained
body; its existing physical identity receives no duplicate credit.

EnemySpawnApplication.cpp uses the local /fp:strict candidate profile: /fp:precise
folded the literal multiplication/division observed as native operations. This
does not establish global game flags. The previously accepted apply_spawn unit
still strictly passes under the updated profile. The GeometryMetrics namespace
correction has its own fresh object and seven passing existing units.

Before accepting the new candidates, independently bind their complete callees,
SDK callback helpers, constant roles and the full defeat EH cleanup/handler,
unwind map and FuncInfo. Do not derive anchors from compared relocation fields.
PlayerFeedback::record_hit, PlayerRecord::add_reward, the indexed ECL selector,
weapon_stone_info and the Controller resource dispatcher remain undefined native
interfaces. Capturing them in a fixture does not reconstruct those bodies.

## Bounded verification and retained evidence

Captured includes select 52 providers / 364 previously accepted units. Their
fresh builds and strict replays pass; the 112 unchanged providers reuse existing
evidence. The subsequent GeometryMetrics correction rebuilds only its provider
and replays its seven units. No whole-graph replay or full CI is run.

The public O2/UBSan fixture passes 10,240 combinations, twelve interface failures
and five recursive topology cases. It uses maintained owner storage, actual
handle publication, record clamps and random advancement. It checks full actor,
Controller, record and feedback images, event prefixes, script returns, pending
child detachment, post-call node reload and iterator cleanup after exceptions.
Existing Enemy creation/clear and spawn/tick fixtures also pass against the
current declarations.

The test domain uses live owner pointers, nonnegative feedback counts, valid
effect cursors, finite positions and acyclic child lists. Resource-free startup,
unreconstructed VM execution, feedback/reward bodies and resource creation are
explicit captures. Portable fixture execution does not prove Windows resource
integration or a whole-program product.

Private evidence is retained under `.analysis/`: the `core154-*native.asm`
exports, `core154-production-diagnostic.json`, affected replay results and graph
audit. Authentic inputs/receipts are in `core154-pre-acceptance-inputs.json.gz`,
`core154-pre-geometry-namespace-inputs.json.gz`,
`core154-pre-publication-inputs.json.gz` and `core154-v4-original-inputs.json.gz`.
The handoff identifies the current freeze and retirement inventory. Cleanup
checks protected hashes and adds zero compiler or replay invocations.
