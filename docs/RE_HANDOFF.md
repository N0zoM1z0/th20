# TH20 reconstruction — current handoff

## Start here

1. Read [repository rules](../AGENTS.md) before changing code or deleting artifacts.
2. Use this file for the current state and immediate next action.
3. Use the [open Boss backlog](RE_OPEN_BOSS_BACKLOG.md) for the wider priority map.
4. Use the [Enemy dispatcher frontier](ENEMY_STATE_EXECUTE_OPCODE_41967_PARTIAL_SOURCE_FRONTIER.md) for the maintained 41,967B root.
5. Use the [evidence index](EVIDENCE_INDEX.md) to find detailed native investigations and exact proofs.
6. Target/compiler/oracle rules live in [target provenance](TARGET_PROVENANCE.md), [workflow](RE_WORKFLOW.md), [oracles](ORACLES.md) and [tools](TOOLS.md).

## Locked target and authoritative status

The target is resources/th20.exe, the Japanese TH20 1.00a Steamless executable:
- Size: **1,858,560 bytes**
- SHA-256: a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897
- Registry/package identity is v1.00a. Embedded title/replay strings say 1.00c in this same file; see [provenance](TARGET_PROVENANCE.md).
- A complete playable game has **not** yet been built, linked or runtime-validated.

The canonical status is in config/matches.csv, config/match-units.toml,
config/functions.csv and config/function-origins.csv. Read the current counts with
`scripts/repo-python scripts/report-reconstruction-status.py --summary`.
The README SVG is generated from those same ledgers by `scripts/progress.py`.

## Current work — exact Player movement

The complete 555B/135-instruction `Player::apply_move_delta` at `0x004FFA10`
now strictly matches, including all 17 REL32 and ten DIR32 fields. C++14
mode, direct upper-bound assignment and two real world-coordinate values
recover the native lifetimes. See [the complete proof and controls](PLAYER_MOVEMENT555_STRICT_EXACT.md).

**Replay scope: 92/92 units from 37 fresh providers.** Removing the unneeded
AnimationFile definition from Player.hpp expands the captured closure to
91 existing units; all pass. Two score units were routed to their existing
SessionScore.cpp owner after the cold build exposed obsolete routing.
Current products are in `build/gpt61-player-movement-canonical/`; preserve
all former objects/receipts and `.analysis/player-movement555-session/`.
The README SVG is regenerated from the updated canonical ledgers.

The 3,111B Player main frame remains NONEXACT at 3,114B/783 instructions.
Its [complete branch/frame/register audit](PLAYER_MAIN_3111_CFG_AND_REGISTER_CONTROLS.md)
remains the constraint for next work: test the newly established language-mode
hypothesis privately, retaining the verified Timer bool ABI. Reuse prior
expression/API/definition controls. The known nonexact Player/WeaponStone
consumers are checked against their complete retained objects.

The [294B text-submit cleanup](ASCII_TEXT_SUBMIT294_CLEANUP_CONTROLS.md)
remains at a 292B NONEXACT parent with two exact EH units under
`build/gpt61-submit294-canonical/`. The glyph queue/application and
movement/swap matches remain intact.

## Latest checkpoint — exact GDI glyph text core

The GDI core at `0x00415830` now strictly replays its full 2,316B
contribution: 2,227B/470 instructions, one NOP and 22 font pointers. The
99B owned EH code and 76B five-state metadata also match. Implicit function
conversion at the consuming queue call and one reused X-position local
recover the native lifetime and frame. See [the complete proof](GLYPH_TEXT_CORE2227_STRICT_EXACT.md).

**Replay scope: ten units from two fresh providers**, derived from the
changed queue header's captured include closures. Existing 132B/23B job
children and the 56B bridge remain exact. The current objects/receipts are
in `build/gpt61-glyph-text-canonical/`; preserve the old canonical products
and private controls in `.analysis/glyph-core2227-session/`.

The downstream insertion/allocator scope is now covered by the forwarding
checkpoint above. The 294B submit and 578B/586B formatting callers remain
open.

## Previous frontier — ASCII text conversion and verifier

The 578B ASCII renderer remains a 574B NONEXACT candidate. Four private
conversion controls distinguish the native double spill from direct XMM
conversion; a strict-FP natural conversion still differs at five SSE operand
bytes. The checker now rejects foreign call symbols after a reproduced
false pass redirected lock lookup to `strlen`. See [the bounded controls](ASCII_TEXT_RENDER578_CONVERSION_CONTROLS.md).

No native input changed: **public exact replay scope is zero**. The fresh
baseline retains six existing helper matches through private comparison;
all public providers and receipts are preserved. Next work needs evidence
for the original scalar lowering or compiler context. Reuse these controls
rather than repeating comma/assignment/double-cast variants.

## Latest checkpoint — exact Card spell start

The complete 1,896B `Card::start_spell` at `0x00487C30` now strictly matches
all 512 instructions, 62 call fields and 26 data fields. Its owned 66B EH
code and 52B two-state metadata also match. Natural source restores temporary
capture/list-assigned position lifetimes, direct getter expressions and
indexed three-word script descriptors. See [the complete proof](CARD_START1896_STRICT_EXACT.md).

**Replay scope: eight units from one fresh Card-start provider**, retaining
all four prior helper matches. No shared header changed. The new provider is
`build/gpt61-card-start-canonical/CardStartSpell1896.obj`; preserve the old
`core1009-canonical` object/receipt and private controls under
`.analysis/card-start1896-session/`. The README SVG has been regenerated.

The adjacent 602B Card finish was already accepted as `card_finish_spell_602`;
the remaining ASCII text render/submit frontiers are separate work.
The ANM parser's separate zero word remains unresolved: its 326B candidate
and rejected initialized-size/class-key controls are retained in
[the slot investigation](ANIMATION_FILE_GROUP336_NATIVE_FRONTIER.md).

## Latest checkpoint — Renderer narrow formatting ABI

The 30B text formatter and all three Renderer consumers now share a correct
`char*` declaration and use 0x500-byte buffers. Following the native CRT chain
to its byte terminator and comparing the SDK's character-specific bodies
resolves the previous wide-character label. Fresh strict replay passes the
30B wrapper, 417B Renderer method and two genuine 31B/77B SDK inline bodies.
The two new units are library support; authored exact coverage is unchanged.

Affected exact replay scope is **four units in two providers**. The 586B
centered and 574B ASCII candidates retain their complete code and owned EH
sections after correcting symbol types; both remain NONEXACT. Next centered
work is its original advance-before-strlen evaluation and scalar temporary
ownership. See [the native CRT and ABI proof](RENDERER_TEXT_NARROW_CRT_ABI.md).

The latest [centered expression-order controls](ANIMATION_RENDERER_CENTERED_TEXT_586_NATIVE_FRONTIER.md#2026-11-26-expression-order-controls-after-the-narrow-abi-correction)
leave native inputs unchanged; exact replay scope is **zero**. A 582B typed
length candidate still evaluates sprite half early. A different 586B formula
aligns all calls but changes the division/subtraction sequence. Neither is
promoted. Preserve advance → strlen → length conversion → quarter span →
sprite half → subtraction in the next source hypothesis; reuse the rejected
literal, conversion, sign and inline controls.

## Latest checkpoint — whole Glyph mask compositor exact

The game-owned 2,245B `NativeGlyphCanvasView::composite_glyph_mask_416420`
at `0x00416420` now strictly replays all 612 instructions, 37 E8 calls and
five HIGHLOW fields. Its complete 63B EH code and 52B two-state metadata
also match. Source restores temporary offset insertion, original X/Y order,
per-format snapshot bases, guarded BGRA neighbor addresses, direct pixel
continues and the shared release-and-reset protocol.

Replay scope was only `src/GlyphMaskComposite2245.cpp`: **39/39 units from
one fresh locked-compiler object**, retaining all 35 prior matches. No shared
header changed. The C++17 allocator owner retains its seven passing units.
Focused verifiers, six malformed EH cases and an inverted-alpha branch case
pass. Authored exact coverage increases by one game function / 2,245B; the
supporting compiler code is uncredited. See the
[whole compositor proof](GLYPH_MASK_COMPOSITE2245_STRICT_EXACT.md).

The public 35B insertion wrapper remains 34B and NONEXACT; none of its missing
NOP is synthesized. Next Glyph work is that wrapper's native call/return
boundary or the separate 2,227B text core, using the now-exact compositor and
PMR backend as evidence.

## Latest checkpoint — Animation corner projection dispatcher

The original 244B `Animation::project_corners` dispatcher at `0x00445770` is
now strict exact. The canonical comparison covers its 244B/79-i386 body and
its original 16B switch table: all 260 relocated bytes, three E8 calls, four
body HIGHLOW fields and four table targets match. The 985B normal projector
and 1,486B rotated projector remain independently exact. Historical source
provenance for the 244B dispatcher remains unknown. See
[the dispatcher proof](ANIMATION_CORNER_PROJECTION_DISPATCH244_SOURCE_FRONTIER.md).

## Open Boss — Animation main Draw

The original 5,993B `AnimationPoolOwner::draw` at `0x00443880` remains
SOURCE-PRESENT, NONEXACT. The maintained source now evaluates mode35 width
while preparing renderer arguments and uses one shared zero-result return.
Compiled checks confirm the native 5/5/6/6 prepared pushes in modes35/36/45/46
and the final renderer-to-cookie tail. The previous source fails both checks.

The fresh candidate is **5,969B/1,497 instructions**, with a 0x200 frame
(native 0x204) and a complete **6,292B** code/table contribution (native
6,316B). All 123 E8 roles and both 49+31 switch-table alias partitions remain.
Physical metrics are 81/123 E8 sites, 22/32 HIGHLOW site/target pairs and
3,691/5,352 ordinary bytes. The earlier 5,989B candidate's higher score partly
offset missing instructions with eager width staging and a duplicate return.
The source now follows the native evaluation and return paths.

Four complete cases account for the entire 24B/four-instruction length gap:
mode35 is 8B short, mode36 8B, mode45 4B and mode46 4B. The two first-getter
m32 store forms and four register-source arithmetic reloads remain open,
along with their stack-slot ownership and receiver-load scheduling. Both
first getters still discard ST0; a second return now occupies `[ebp-0x160]`,
so a matching offset alone must not be called a first-result spill.

The latest native change touched only `src/AnimationDrawBoss.cpp`. It has no
canonical exact provider or source-including consumer; no shared header changed.
**Affected exact replay scope: zero.** Existing accepted children retain
their evidence, and the parent receives no exact credit.

See [the current source proof and complete case accounting](ANIMATION_DRAW_BOSS_5993_MODE45_MODE46_RETURN_FRONTIER.md#2026-11-26-native-width-preparation-and-one-zero-result-return).
The focused note also retains the rejected width-half swaps, inline helpers,
ABI/language and floating-environment controls. Do not repeat them. Next
investigate natural expression-temporary ownership for the two m32 stores
and four scalar reloads while preserving the newly verified argument/return
protocol. Keep the working getter declaration and locked compiler profile.

New reduced controls do not justify full-parent variants: value/reference
inline discards use separate branch temporaries, optimized scalar/vectorcall
helpers still use memory operands plus result copies, and assignment/comma
forms do not recover the register reload. Discarded comparisons, conversions,
negations and additions remain bare ST0 discards. The current native source
and accepted graph are unchanged; see the existing inline-ownership and
scalar-expression sections in the focused note before trying these again.

[Compiler/link-context controls](ANIMATION_DRAW_BOSS_5993_COMPILER_CONTEXT.md)
now retain the target's RSDS/feature metadata and confirm that `GCTL` plus an
empty `iltcg` can arise without code generation. The no-SSA option and shared
19.10 comparison do not recover the missing forms. Actual LTCG callers also
match ordinary COFF, including with the real 93B getter visible as IR.
Independent MAP replay covers every caller/getter byte and relocation in these
controls. Keep the current profile and focus on source temporary ownership;
the markers alone do not warrant a full Draw LTCG build.

The same note now records native volatile-access metadata: Draw is fully
covered, but only its two GS cookie accesses are marked. Linked positive
controls mark volatile x87 stores and saved-half accesses, arguing against
volatile storage for the missing native forms. Direct narrowed-wide arithmetic,
strict floating-environment narrowing and global `/O2` with local optimization
disabled also leave the reviewed callers unchanged. Reuse these results;
continue with expression-temporary ownership under the working float ABI.

## Latest checkpoint — StageResource selector and Enemy opcodes 622–626/631

The maintained partial Enemy root now executes opcodes 622–626/631 through
`src/EnemyStateResourceOpcode.cpp`. The 133-byte StageResource instruction selector
at `0x004773C0` strictly replays **133/133 bytes**, including its single Timer
assignment relocation. The six native case blocks total 337B/64 instruction
heads/9 ordered E8 calls. Root tests cover variable-size instruction scanning,
negative sentinels, miss preservation, Timer assignment, operand exceptions,
Context receiver capture, callback installation and the separate zero-table
views. See [the StageResource selector proof](STAGE_RESOURCE_RECORD_SELECTION_EXACT.md)
and [the maintained dispatcher frontier](ENEMY_STATE_EXECUTE_OPCODE_41967_PARTIAL_SOURCE_FRONTIER.md).
The 41,967-byte dispatcher remains NONEXACT; the StageResource leaf's original
source origin also remains unknown and receives no authored credit.

## Latest checkpoints — Enemy ECL opcodes 616, 617, 618, 619, 620, 627/628, 629/630, 632 and 633

Enemy ECL opcodes 616, 617, 618, 619, 620, 627, 628, 629, 630, 632 and 633 are now integrated into the
maintained root host and focused verifiers. Their production/test/verifier
changes are checkpointed and retained:

- `src/EnemyStatePlayerAngleOpcode.cpp`
- `src/EnemyStateLaserOpcode.cpp`
- `src/LaserCommandMethods.cpp`
- `src/LaserParameters.hpp`
- `src/LaserControllerFindLaser.cpp`
- `scripts/verify-laser-controller-find-laser-source.py`
- `scripts/verify-enemy-laser-lookup-opcode-source.py`
- `scripts/verify-enemy-laser-mutation-opcodes-source.py`
- `docs/ENEMY_41967_705_710_LASER_MUTATIONS_SOURCE_FRONTIER.md`
- `docs/LASER_MUTATION_SETTER_LEAVES_EXACT.md`
- `docs/ENEMY_41967_714_LASER_PARAMETER_FLAG_SOURCE_FRONTIER.md`
- `src/EnemyStateSharedQueuedParametersOpcode.cpp`
- `src/EnemyStateQueuedParametersOpcode.cpp`
- `src/EnemyStateScriptPointerOpcode.cpp`
- `src/EnemyStateBulletLaserCancelOpcode.cpp`
- `src/BulletLimitedCancellation.cpp`
- `src/EnemyStateBulletClearOpcode.cpp`
- `src/EnemyStateScorePopupOpcode.cpp`
- `src/BulletTimer4D8.cpp`
- `src/SessionScore.cpp`
- `tests/enemy_state_dispatch_root.cpp`
- `scripts/verify-enemy-bullet-laser-cancel-opcode-source.py`
- `scripts/verify-enemy-player-angle-opcode-source.py`
- `scripts/verify-enemy-shared-queued-opcode-source.py`
- `scripts/verify-enemy-shared-queued-polar-opcode-source.py`

Native opcode 616 is the **175-byte / 37-instruction / 7-E8** case at
`0x004954D1`, selector index 134. It reads radius operand 0, then executes
the real 320B BulletController::cancel_near Boss using the current Context
and live Enemy position reference. After that traversal it re-reads Context
and position and executes the real 288B LaserController::cancel_near Boss.
The root host verifies live position aliasing during Bullet traversal, Context
retargeting between phases, Bullet/Laser state filters, virtual circle-cancel
arguments and radius exception-before-side-effects. Bullet::cancel and the
concrete Laser::cancel_circle child remain explicit test capture boundaries.
See [the opcode-616 source frontier](ENEMY_41967_616_BULLET_LASER_RADIAL_CANCEL_SOURCE_FRONTIER.md).

Native opcode 617 is the **203-byte / 41-instruction / 8-E8** case at
`0x004958C3`, selector index 135. It reads the live Context Player position,
subtracts VM float operands 1/2 in X-then-Y order, calls the existing
`scalar_math::arctangent(dy, dx)`, and writes float destination 0. Context is
re-read between operands, and the root host tests retargeting with two real
Player objects, direct atan2(0,0)==0 semantics, and second-operand exception
preservation. See [the opcode-617 source frontier](ENEMY_41967_617_PLAYER_ANGLE_SOURCE_FRONTIER.md).

Native opcodes 605–608 now run through the production queued-shot property
helper. Their four original inline bodies total 705B/164 x86/31 E8 across
selectors 126–129. 605/606 use shared_shot for speed/count fields; 607/608 use
writable_shot and the pair-second ShotMetadata receiver for `field_38`, sound
and alternate sound. The root host covers narrowing, COW, owner preservation
and exception-visible partial writes. See [the 605–608 native/source frontier](ENEMY_41967_605_608_QUEUED_SHOT_PROPERTIES_SOURCE_FRONTIER.md).
The parent remains NONEXACT; no inline byte credit is claimed.

Native opcode 618 is the **243-byte / 55-instruction / 10-E8** case at
`0x00492BC6`, selector index 136. Its natural C++ source reads the integer
selector and both float operands before the real ensure-only `shared_shot`,
then extracts the pair, constructs a temporary `Vector3`, calls the existing
`polar` leaf and writes only queued-record vector_34 XY. The root host tests
second-float exception before queue growth, shared-owner stability, Z and
vector_40 preservation. See [the opcode-618 source frontier](ENEMY_41967_618_SHARED_QUEUED_POLAR_SOURCE_FRONTIER.md).

The shared `LaserController::find_laser` leaf at `0x00498FF0` is now
restored as natural C++ and linked into the maintained root host. Its native
body is 230B/70 instructions/11 E8 calls and is called by Enemy ECL opcodes
704–710. The implementation uses the real `active` intrusive list, compares
`Laser+0x8C`, preserves the second `node_value()` call on the match return,
and destroys the iterator on both paths. The root host tests empty/missing,
later-element, and duplicate-handle lookups. See
[the Laser find_laser source frontier](LASER_CONTROLLER_FIND_LASER_230_SOURCE_FRONTIER.md).

Enemy opcode 704 is now independently restored as a 176B/37-instruction
inline source fragment: Context owner capture, integer handle operand, real
`find_laser`, Vector3 construction, ordered float operands 1/2 and conditional
virtual `set_position`. Its native PE/COFF verifier and live Context-retarget /
missing-handle / operand-exception root tests pass. See
[the opcode-704 source frontier](ENEMY_41967_704_LASER_POSITION_LOOKUP_SOURCE_FRONTIER.md).
Sibling opcode fragments 705–710 and 714 now have natural C++ source and
focused root coverage. The six 705–710 setter leaves remain strict exact;
opcode 714's Beam flag override is semantic reconstruction (39/42), while
its three non-Beam vtables share an already-folded no-op body. See the
[705–710 Laser mutation frontier](ENEMY_41967_705_710_LASER_MUTATIONS_SOURCE_FRONTIER.md)
and [714 Laser flag frontier](ENEMY_41967_714_LASER_PARAMETER_FLAG_SOURCE_FRONTIER.md).
The 41,967B Enemy root remains NONEXACT.

Native opcode 620 is the **250-byte / 57-instruction / 8-E8** case at
`0x00492D4D`, selector index 138. Its natural C++ source uses the real
ensure-only `shared_shot` path and pair `std::get` extraction, writes the
queued record's `vector_40.x/y/z`, preserves the `-990.0f` threshold and
`1.0f` constant, and matches the original `COMISS/JBE` NaN behavior. The root
test checks shared metadata ownership, threshold boundary, NaN, and the
second-operand exception after the X write.

Native opcode 619 is the 148-byte / 35-instruction / 7-E8 writable queued
metadata update at 0x00492CB9, selector index 137. It calls the real
writable_shot COW selector, extracts both pair members in native order, then
reads float operand 1 and writes ShotMetadata::field_00, consumed as the
Bullet/Laser radial offset. The root host proves COW precedes the float read:
a float exception preserves the clone but leaves the metadata field unchanged.
See the opcode-619 source frontier
(ENEMY_41967_619_WRITABLE_METADATA_RADIAL_OFFSET_SOURCE_FRONTIER.md).

Native Enemy spawn opcodes 300/301/304/305/321 now route to the whole
653-byte `EnemyState::spawn_from_opcode()` Boss, strictly exact across all 577
ordinary bytes and all 19 relocation fields. The native float-argument stack
reservation order is recovered with an identity C++ cast, not assembly. The
309/310/311/312 selected-slot guard also routes an empty slot to this same
Boss. Original source origin remains unknown, and the 41,967-byte dispatcher
parent remains NONEXACT. See [the 653B spawn Boss proof](ENEMY_SPAWN_FROM_OPCODE_653_STRICT_EXACT.md).

Native opcode 629 is the **46-byte / 10-instruction** callback-table branch
at `0x00490B4D`, selector index 147. Its native table at `0x0056FE8C` selects
the 758B animation-rectangle Bullet callback or the 291B all-Bullet reset
callback. Both complete callbacks are now natural C++ `EnemyState` members,
with real AnimationHandle resolution, rotated `geometry::rectangle_circle`,
active Bullet iterator, Bullet Timer/color/field setters, Context/Player
position reads and Player movement-scale writeback. The original 6.0f and
10.0f globals are mapped; root tests exercise both callbacks, no state/field
filter, overlap/no-overlap and exception ordering. See
[the opcode-629 callback frontier](ENEMY_41967_629_BULLET_CLEAR_CALLBACK_SOURCE_FRONTIER.md).

Native opcode 630 is the **109-byte / 24-instruction / 5-E8** score-popup
branch at `0x0048C24A`, selector index 148. It uses real Session score
accounting, the Context +0x1C ItemRewardPopupQueue owner, live Enemy position
and the strict-exact 255B popup enqueue Boss. Root tests cover queue payload,
score, Context retargeting and operand exception-before-side-effects. See
[the opcode-630 source frontier](ENEMY_41967_630_SCORE_POPUP_SOURCE_FRONTIER.md).

`Bullet::set_timer_4d8` is now a separate **39-byte strict-exact** leaf at
`0x0049CAE0`: all 35 non-relocation bytes match and the single REL32 at
`+0x1C` targets exact `Timer::operator=(float)` at `0x0047C5F0`. See
[BULLET_TIMER_4D8_SETTER_EXACT.md](BULLET_TIMER_4D8_SETTER_EXACT.md).

Native opcode 633 is the 163-byte / 41-instruction / 6-E8 queued-record
decrement at 0x0049378E, selector index 151. It retains writable_shot and
both ordered pair extractions, performs wrapping uint32 decrement of record
field_30, then clamps a signed-negative result to zero. Boundary and
selector-exception tests cover both arithmetic and COW side effects.
See the opcode-633 source frontier
(ENEMY_41967_633_WRITABLE_QUEUED_RECORD_DECREMENT_SOURCE_FRONTIER.md).

Native opcode 632 is the **252-byte / 62-instruction / 10-E8** borrowed
BulletCommand script-pointer case at 0x00493831, selector index 150. Both
integer indexes are read before writable metadata COW, pair extraction and
PMR command-vector size/resize/index. The stored pointer is the original
EclInstruction + 0x1c trailing payload address; no string is copied. The
root host verifies COW, vector growth, pointer identity and second-index
exception-before-side-effects. See
[the opcode-632 source frontier](ENEMY_41967_632_BORROWED_SCRIPT_POINTER_SOURCE_FRONTIER.md).

Native opcodes 627 and 628 are each **182-byte / 39-instruction / 7-E8**
paired capped Bullet/Laser radial-cancellation cases at 0x00495580 and
0x00495636, selector indexes 145/146. They call the real 401B
BulletController::cancel_near_limited Boss with mode 0, limit 99,999 and
effects 0, then re-read Context/position and call the real 288B
LaserController::cancel_near Boss with mode 0 / argument 1. The root host
tests real intrusive traversal, state/field filters, effect-bit reset,
Context/position retargeting and radius exception ordering. See
[the opcode-627/628 source frontier](ENEMY_41967_627_628_CAPPED_RADIAL_CANCEL_SOURCE_FRONTIER.md).

The false-returning root-test stubs for the shared, writable queued-parameter
and script-pointer helpers are removed. The production helpers are included
in HOST_SOURCES and the locked-profile COFF compile list; their native opcode
verifiers are invoked by the maintained root verifier. The focused root host
passes under ASan/UBSan, and the root verifier compiles **67 locked-profile
i386 COFF source units** and 132 focused host sources. See the dedicated
[opcode-620 source frontier](ENEMY_41967_620_SHARED_QUEUED_VECTOR_SOURCE_FRONTIER.md).

This is still an inline fragment only. No standalone function unit or
strict exact-byte claim is created, and the 41,967-byte parent remains
**NONEXACT**. No full cold replay was run.

## Active Boss — EnemyState::execute_opcode

The main target is the original **41,967-byte** EnemyState::execute_opcode
at 0x0048C010. It now has a substantial partial natural-C++ root and
focused ASan/UBSan host, but the complete parent remains **NONEXACT**. No
whole-parent byte credit is claimed.

Recent committed case families exercised by the maintained root include:

- **609/610/611/612:** shared 1,457B shot-command branch; real writable-shot
  COW selector and PMR BulletCommand vector.
- **614:** 572B queued-record copy; real PMR forward-list and exact 119B record
  assignment.
- **616:** 175B paired Bullet/Laser radial cancellation; real 320B and
  288B controller cancellation Bosses, live Context/position retargeting,
  state filtering, virtual dispatch capture and radius exception ordering.
- **617:** 203B Player-relative angle; two live Context/Player position reads,
  existing atan2 leaf, destination writeback, Context-retarget semantics and
  second-operand exception coverage.
- **618:** 243B shared queued-polar update; real ensure-only shared record,
  pair extraction, temporary Vector3 and existing polar leaf; XY-only writes
  with Z/vector_40 preservation and second-float exception ordering.
- **620:** 250B shared queued-vector update; real ensure-only shared record,
  pair extraction, ordered X/Y writes, native `COMISS/JBE` NaN behavior and
  second-operand exception coverage.
- **619:** 148B writable queued-metadata radial-offset update; real COW selector,
  ordered pair extraction, COW-before-float and exception-after-clone coverage.
- **633:** 163B writable queued-record decrement; real COW selector, ordered pair
  extraction, uint32 wrap/signed high-bit clamp and selector-exception coverage.
- **632:** 252B borrowed script pointer; both indexes before COW, real PMR command
  growth and exact EclInstruction+0x1C pointer identity, plus second-index exception.
- **627/628:** two 182B capped Bullet/Laser cancellation branches; real 401B limited
  Bullet and 288B Laser Bosses, 99,999 cap/effects arguments and live Context retargeting.
- **629:** 46B callback-table case plus 758B and 291B native callback Bosses (10B INT3 alignment is separate);
  real AnimationHandle/geometry/Bullet iterator/Timer/color/Player paths and both
  callback modes execute under ASan/UBSan.
- **630:** 109B score-popup case; real Session score, Context +0x1C popup queue,
  live Enemy position and strict-exact 255B enqueue Boss.
- **621:** 346B mesh-owner lifecycle; real allocator templates and
  EnemyMeshOwner destructor. Renderer-dependent RenderMesh ctor/dtor and
  allocator startup remain host fixtures.
- **702/703/711/713:** four Laser parameter branches; real typed parameter
  lifetimes, COW and PMR command copies. LaserController::create_laser is a
  capture-only host boundary; its separate factory is strict exact.
- **712:** 196B rectangle-cancel branch; real 707B cancellation Boss and
  rectangle geometry. The 456B animation-pool resolver and 662B
  Bullet::cancel remain host boundaries.
- **800/801/802:** cross-Enemy script selection, selected-Enemy XY writeback
  and three-slot phase-script restarts through real EclManager/EclLoader and
  EnemyPhase owners.
- **553/554:** real EnemyData and BulletController setters, with Context
  retargeting and operand-order tests.
- Earlier routed families include movement, Pattern, bounds/health/controller,
  timer/mode, Card/health, animation spawn, membership, fog, bit flags,
  sound/gauge/title and selected-position cases.

The maintained root verifier currently compiles **67 locked-profile i386
COFF units** and runs 132 focused host source units under ASan/UBSan, including
opcodes 616, 617, 618, 619, 620, 627, 628, 629, 630, 632 and 633. The exact per-case boundaries and host limitations are documented in the
[dispatcher frontier](ENEMY_STATE_EXECUTE_OPCODE_41967_PARTIAL_SOURCE_FRONTIER.md)
and the focused case notes linked from the [evidence index](EVIDENCE_INDEX.md).

Other major open Bosses remain in the [backlog](RE_OPEN_BOSS_BACKLOG.md),
including the 12,140B Bullet extended-command dispatcher, 39,470B Animation VM update (source-present, NONEXACT), 5,993B Animation Draw Boss, 2,245B Glyph mask compositor,
2,227B Glyph text core, 1,896B Card Start and the 626B FrontInf command parent
(currently 622/626B). The 1,954B Window D3D9 reset-state Boss is also
source-present but NONEXACT.

## Continuation order

1. Continue only `AnimationPoolOwner::draw(Animation*)` at `0x00443880`
   until its complete 5,993B body and original relocations replay strict
   exact. The current source preserves native mode45/46 scale-half and
   post-adjustment width-half evaluation order and reaches **4,694/5,372**
   ordinary bytes, **109/123** physical E8 sites and **26/32** exact data
   site/target pairs. The former value-equivalent mode45 role swap reached
   4,840/5,376, 114/123 and 27/32, but did not preserve native source order.
   The open frontier is the mode35/36 first-getter x87 spill, their adjusted-scale
   XMM1 reloads and remaining call-site deltas, plus mode45/46 adjusted-scale
   XMM1 reloads and the four-byte contribution/dispatch-table displacement
   introduced by restoring mode45's original evaluation order. Mode45's
   half-height ownership is now source-correct; only its emitted memory-source
   addss differs from native register-register addss. The parent-angle bit-12 extraction now matches the
   original six-byte SHR/AND sequence. Modes37/38 and 39-41 now use
   offset-preserving `rounded_shape_radius`, `ring_center_radius` and
   `ring_thickness` aliases, with the 64B `AnmVariables` layout unchanged.
   The exact 5,388B Animation geometry boss now also names the shared geometry
   UV span and mode24/25 angular span, half-height, base radius and center angle,
   alongside mode47 ring thickness/center-radius and mode48 triangle radius;
   its 5,452B canonical relocated replay remains exact. Geometry UV offsets
   at AnimationBase+0x78/+0x7c are now named `texture_offset_u/v` without
   changing the 0x4c0 AnimationBase layout. The parent-only
   lexical semantic-debt scan is now zero (heuristic only). Five small
   AnimationBinding leaves are now independently native-attested and strictly
   exact, including the 34B `copy_base` wrapper and four callback/lifecycle
   helpers; original template/allocation callers are verified in
   `docs/ANIMATION_BINDING_LEAF_FUNCTIONS_EXACT.md`.
   The adjacent 42B `Animation::is_active` signed predicate now also strictly
   replays 42/42B; its original method identity and authored/accessor origin
   remain unknown. The 452B `matrix_identity` helper now also has a strict canonical replay
   including all four DIR32 references to the original `1.0f` constant; its
   natural C++ source uses the original explicit store order. Its generic
   utility origin remains unknown. The adjacent `Animation::clear_flag_02`
   helper also now strictly replays
   32/32B using the natural `AnimationFlagByte02::bit_10` C++ bitfield access;
   its original authored-versus-accessor origin remains explicitly unresolved.
   The callback family also gained five strict native leaf replays (230B):
   `Animation::interrupt`, `Animation::set_callback`, callback construction,
   base destruction and the eight-byte scalar deleting path. The original
   five-slot vtable and its `SprtFuncBaseInf` RTTI distinction are pinned by
   `scripts/verify-animation-callback-leaves-native.py`.
   Modes45/46 now both preserve original source evaluation order: scale
   half-height before the inherited-scale getter, then a separate width-half
   calculation after adjusted scale. This intentionally rejects the previous
   mode45 role swap, which improved byte/E8 metrics but computed width half
   before the getter and scale half after it. The native verifier now pins
   mode35/36 first-return spills and adjusted-scale register operands, plus
   mode35/36/45/46 width windows and mode45/46 adjusted-scale windows. The
   The former mode36_width label at +0x171C was corrected: that window is
   mode46; mode36 width is at +0x1155. Both focused verifiers pass.
   Mode28's raw Animation flags at +0x4A8/+0x4AC are now identified as the
   horizontal/vertical 0..2 anchor indices: the original parent loads +0x4AC
   first, then +0x4A8, and pushes vertical before horizontal for the cdecl
   draw_shape_43e2c0 call at +0x0D73. The exact 1,601B triangle child was
   replayed 1/1; its final parameters are named horizontal_anchor and
   vertical_anchor. The native verifier pins the parent loads, cdecl push
   order and child target; the source-role verifier checks the source args.
   AnimationFlags now exposes horizontal_anchor/vertical_anchor as
   layout-preserving union aliases for the original word_10/word_14 storage,
   with static offsets +0x10/+0x14 and the unchanged 0x20-byte structure.
   Mode6/7/8 setup/rendering, both 985B/1,486B corner projectors, the 0x5D
   script operand producer and both laser initializers use the semantic names.
   The five anchor-specific exact leaves were cold-replayed 1/1 each:
   985/985, 1,486/1,486, 1,378/1,378, 1,996/1,996 and 4,347/4,347 coverage
   bytes (4,372/4,372 compared bytes). The complete affected include-closure
   batch replayed 33/33 exact units across 11 source objects, including seven
   AnimationBinding units, nine AnimationCallback units, four DrawAccess
   leaves and the 5,388B AnimationGeometry boss. The 39,470B update source and
   both laser initializer sources also compile as i386 objects; those owners
   are not claimed exact. A typed __forceinline reference accessor was tested and
   rejected because it changed the exact 1,378B mode6 setup contribution to
   1,399B; direct union field aliases preserve the original codegen. The
   source-role verifier pins the alias names, offsets, layout and consumers.
   Mode35/36's second inherited-scale result is now named
   `inherited_scale` and feeds the real adjusted-scale argument. The first
   getter remains a separate discarded call in the decompilation, while the
   native body stores both first returns to the write-only `[ebp-0x160]` slot.
   A current-source-derived scalar probe recovers both spills and both
   register-register adjusted-scale operations, but drops to 89/123 E8 sites
   and is four bytes short at the mode36 renderer call because it reuses the
   earlier half-height for width. The native path recomputes the width half
   after adjusted-scale; preserving that order currently reverts to the
   memory-operand subtraction. No source change is promoted. A focused mode36 declaration
   battery (including case-top predeclarations with native assignment order),
   `/fp:fast`/`/fp:strict`/`/fp:precise`, `/Zi`/`/Z7` debug-info builds,
   scalar SSE-load intrinsics and bit-cast experiments did not recover the
   native XMM1 load without breaking the call
   census or natural source profile; see the appended mode36 probe report. The
   inherited-scale getter's exact 93B `float` ABI is closed;
   A new 16-way mode35 width-temporary placement battery found a 4-byte
   ordinary-byte score rise (4,844/5,376) at unchanged 114/123 E8 positions,
   but it moves the second mode35 getter +22 bytes and increases total E8
   displacement 44→62; it is rejected. Restoring native mode45 evaluation
   order is now the maintained source even though it drops to 109/123 E8,
   4,694/5,372 ordinary bytes and 26/32 data sites; do not reintroduce the
   value-equivalent role swap to inflate the byte score. A detailed
   source-only tradeoff ledger is in
   [mode35/36 width-order experiments](ANIMATION_DRAW_BOSS_5993_MODE35_MODE36_WIDTH_ORDER_EXPERIMENTS.md).
   The native verifier now also pins the post-adjustment mode35/36 width
   calculations and their XMM operand order; the source-role verifier checks
   the corresponding C++ evaluation order. Both focused verifiers pass.
   Direct renderer-argument and mixed mode35/36 ownership trials were worse
   (83–89/123 E8; 3,675–3,800 ordinary bytes); see the appended matrix in the
   width-order experiment ledger. No source variant is promoted.
   First-result locals kept with the existing case temporaries, reused width
   locals, and scalar `__forceinline`/`__vectorcall` helpers also failed to
   preserve the native frame and E8 graph. No parent source or exact credit
   changed.
   Candidate-only disassembly now confirms the exact split: the role-swapped
   `current_spill_direct` experiment emits both native-slot spills and both
   register-register adjusted-scale ops, but has 89/123 E8 and 140 bytes of
   total call displacement; the native-order spill candidate emits both
   spills but memory-source arithmetic, 84/123 E8 and 296 bytes of displacement.
   `scripts/report-animation-draw-boss-candidate.py` reports candidate-side
   instructions separately from native instructions; use it for future probes.
   Register/volatile qualifiers, predeclaration order, shared-half reuse and
   standard function-object wrappers did not close the gap. See the appended
   candidate-only audit in the width-order ledger.

   Additional first-return stack-slot scope batteries also failed: a single
   function/case local stores to [ebp-0x164] and yields 85/123 E8; hoisting
   all four shared temporaries can recover [ebp-0x160] but collapses the
   parent to 44/123 E8 and 14/32 data sites. Nested-switch scope behaves the
   same. The original source graph is retained; see the appended stack-slot
   lifetime section of the width-order ledger.
   A follow-up scope/reference/aggregate/array matrix and compact local
   struct/scale-pair battery also failed to recover the first-return spills
   without collapsing the E8 graph (84–86/123); reusing the actual width or
   adjusted-scale argument local was worse (45/123). Assignment-at-argument
   variants compiled back to the maintained candidate. See the appended
   scoped/aggregate lifetime section; no candidate is promoted.
   One new shared function-scope first-result local placed after common
   renderer setup does recover both mode35/36 fstp m32 stores to [ebp-0x160]
   (mode35 at +0x0FCD exactly; mode36 at +0x10B6, four bytes early), but its
   inline-width candidate is only 5,981B/1,499 instructions, 84/123 E8,
   3,726/5,364 ordinary bytes and 23/32 data sites. Restoring the current
   width local loses the native spill slot again. This is a useful stack-slot
   explanation, not a promoted candidate; the maintained parent remains
   5,989B/109 E8.
   The native-only verifier now proves [ebp-0x160] is write-only across the
   complete body: exactly two fstp writes at +0x0FCD/+0x10BA and no reads.
   Four additional nested-switch declaration placements all produce the same
   5,997B/85-E8 candidate with no store to that slot; see the appended lifetime
   probe. The maintained source is unchanged.
   A mode45 native-order expression battery (named/reversed addition,
   compound assignment and post-adjustment width temporaries) did not improve
   the 5,989B/109-E8 maintained candidate. A mode46 role swap can produce
   register-register subtraction only as `subss xmm1,xmm0`, not native
   `subss xmm0,xmm1`, while dropping to 113/123 E8; arithmetic identity forms
   and dual-half locals are also worse. The current mode45/46 source order is
   retained. Full metrics are in the appended mode45/46 sections of the width
   experiment ledger.

   Ghidra's `float10` does not justify MSVC `long double`. See
   [the focused mode45/46 frontier](ANIMATION_DRAW_BOSS_5993_MODE45_MODE46_RETURN_FRONTIER.md)
   and [the full-body convergence report](ANIMATION_DRAW_BOSS_5993_MODE35_MODE45_SITE_CONVERGENCE.md).
   Do not switch to another function before this Boss is exact.
2. Only after that exact replay, resume the remaining large Enemy dispatcher
   cases and the open FrontInf, Bullet and Animation Bosses. Preserve natural
   C++ control flow and real ownership; do not substitute trivial setters for
   Boss work.

For source changes, replay only affected units and changed shared-header
consumers. Do not run a full cold replay for routine progress. Preserve
original C/C++ control flow, ABI, exceptions and operand order. No ASM,
synthetic padding, fake returns or shortened extents.

## Protected products and local storage

Preserve the locked target, supplied game files, useful native evidence,
Ghidra project/runtime and canonical build objects:

- resources/th20.exe
- ../game_exe/ if present
- .analysis/ native evidence and active investigation inputs
- .analysis/factory-native-ghidra/, .analysis/factory-runtime/
- ghidra-project/ and .tools/
- every build/*-canonical/ object/receipt directory

Noncanonical build outputs may be pruned only when they are generated
.obj/receipt artifacts, are not referenced by current scripts/docs, and do
not preserve an unresolved investigation. Keep current Enemy/Bullet/Item/
WeaponStone/FrontInf and other open-Boss work products. Do not delete an
entire analysis or build tree to save space.

## Useful focused commands

- git status --short --branch
- scripts/repo-python scripts/report-reconstruction-status.py --summary
- scripts/repo-python scripts/verify-enemy-state-dispatch-frontier.py
- scripts/repo-python scripts/verify-enemy-shared-queued-opcode-source.py
- scripts/repo-python scripts/replay-exact-units.py --source src/ChangedSource.cpp
- scripts/repo-python scripts/build.py --check
- git diff --check

The root verifier is a focused dispatcher/host check, not a full cold replay
or whole-parent exactness test. Use replay-exact-units.py --source only for
actual source changes and their captured include-closure consumers. Commit
stable checkpoints with the required gpt-6.1-sol: prefix. Preserve and inspect
all dirty/untracked work before making changes.


## 2026-11-25 follow-up: native mode45/46 ownership and candidate-only mode map

The maintained `src/AnimationDrawBoss.cpp` now uses the original mode45
evaluation order instead of the earlier value-equivalent role swap:

- Compute `half_for_scale = height / 2` before the inherited-scale getter.
- Compute `adjusted_scale = getter + half_for_scale`.
- Recompute `height / 2` for the width argument only after adjusted scale.

Mode46 retains its original asymmetric subtraction order as well: scale half
before the getter, adjusted scale after the getter, width half recomputed after
adjusted scale. The source-role verifier checks both blocks independently.
The current candidate is **5,989B / 1,501 x86**, **4,694/5,372** ordinary
bytes, **109/123** E8 positions, **68B** total absolute E8 displacement and
**26/32** exact HIGHLOW sites. This is a deliberate semantic correction, not
a byte-score improvement. The previous mode45 role swap scored
4,840/5,376, 114/123, 44B and 27/32, but moved the width-half calculation
before the getter and recomputed the scale half afterwards. It is not the
maintained source anymore.

The native verifier now pins all relevant arithmetic windows by actual mode:

| Mode | Native scale window | Native width window |
| --- | --- | --- |
| 35 | `+0x1016` register `addss xmm0,xmm1` | `+0x1068` width add |
| 36 | `+0x1103` register `subss xmm0,xmm1` | `+0x1155` width `subss xmm1,xmm0` |
| 45 | `+0x15DD` register `addss xmm0,xmm1` | `+0x163D` width add |
| 46 | `+0x16BC` register `subss xmm0,xmm1` | `+0x171C` width `subss xmm1,xmm0` |

The former verifier called the `+0x171C` window `mode36_width`; it is
mode46. Mode36's width calculation is the distinct `+0x1155` window. The
focused native PE and source-role verifiers both pass after correcting this
mislabel and pinning the missing windows.

The candidate-only report was extended to decode the first actual `ret 4`,
score the same 6,316B COFF contribution for every probe (including longer
experiments), and separate mode35/36/45/46 adjusted-scale operations from
their width operations. It now distinguishes mode46 native-order
`subss xmm0,xmm1` from a reversed-destination `subss xmm1,xmm0`. The
maintained candidate currently has memory-source adjusted-scale arithmetic
in modes35/36/45/46; mode45's previous register-register add came only from
the rejected role swap.

A mode46 role-swap probe (width half before getter, scale half recomputed
after) did produce a register-register subtraction, but with reversed
destination `subss xmm1,xmm0` at `+0x16DC`, a 5,989B body, 113/123 E8,
4,786/5,372 ordinary bytes, 48B total E8 displacement and 27/32 HIGHLOW
sites. It is rejected because it changes
the native source order and loses a physical E8 position. Dual-half
predeclarations, post-getter reuse, direct-return, and `+0`, `*1`, `/1`,
negative-half and negated-reverse expression forms did not improve the
maintained candidate; their bodies ranged from 5,992B to 6,005B and had
109–113/123 E8 positions. No ASM, padding or production-only compiler
shaping was introduced.


## 2026-11-25 follow-up: isolated mode45 intrinsic rejection and exact draw leaves

A mode45-only _mm_load_ss/_mm_set_ss intrinsic battery expands the
contribution to 6,084–6,098B and loses the native E8 graph; these
compiler-shaping forms are rejected. The scalar source-order correction
remains production.

The four DrawAccess leaves (two 20B color getters, 26B enabled predicate,
93B inherited-scale getter) were rebuilt together after their include closure
changed and passed strict canonical replay 4/4. Their exact child status does
not imply parent exactness.

2026-11-25 follow-up: the recursive inherited auxiliary-scale leaf at
`0x00445880` was independently replayed again and remains exact at 93/93B.
A function-scope first-result local in the large parent emits both native
write-only `[ebp-0x160]` stores and preserves the first 89 E8 positions, but
mode36's post-getter adjusted-scale arithmetic remains a memory-source
`subss` instead of the native register-register form. The closest candidate
puts the next renderer call four bytes early; volatile/copy/compound local
forms and shared-half reuse do not close the gap. See
`ANIMATION_DRAW_BOSS_5993_MODE35_MODE36_WIDTH_ORDER_EXPERIMENTS.md`; production
remains the 5,989B/109-E8 candidate, NONEXACT.

The latest mode36 comparison isolates the first-result candidate's remaining
four-byte call drift: native code loads the stored half-height into XMM1 then
uses register-register `subss xmm0,xmm1`; the closest natural scalar C++ form
uses a single memory-source `subss xmm0,[local]`. Ordinary scalar/volatile
local forms keep the memory operand, while a one-operation SSE intrinsic
breaks the full parent call graph (0/123 E8) and is rejected. The current
5,989B/109-E8 production source remains unchanged. Exact instruction details
and scoped metrics are in the mode35/36 width-order experiment ledger.

2026-11-25 follow-up: a fresh mode35/36-only C++ probe, with mode45/46 source
left unchanged, now reaches 94/123 E8 positions and 27/32 HIGHLOW sites while
emitting both native `[ebp-0x160]` first-result stores at +0x0FCD/+0x10BA.
The candidate is 5,993B/1,501 x86 with 4,023/5,372 ordinary bytes and 116B
total absolute E8 displacement. All 123 REL32 target symbols remain in the
same sequence as the maintained parent. It still has a four-byte call drift
across modes36–44, and mode36 width is multiply-negative-plus-add rather than
the native reverse-destination subtract. Do not promote it: the maintained
5,989B/109-E8 parent remains unchanged. See the mode35/36 experiment ledger.

The 94-site mode35/36 probe has now been stress-tested against local declaration
placement, nested-switch scope boundaries, shared-half liveness and width
expression forms. Five common-setup declaration positions and four nested
switch declaration positions are codegen-identical; the first-result local's
slot placement is stable. Reusing the half local for scale and width collapses
the switch graph (45–77/123 E8), and a short-lived block local does not emit
the native spill. Only the multiply-by-negative-one width spelling retains
94/123 E8/5,993B, while direct subtraction returns to 89/123. The candidate
remains non-production because its width instruction sequence is not native.
See the appended local-scope/width-form ledger section.

Additional focused probes after the 94-site checkpoint did not improve the
production 109/123-E8 source. Mode36 arithmetic rewrites score 81–86/123 E8;
pointer aliases to force the half local into a second XMM register collapse
to 28/123 E8 or fail the pinned compile. On the 94-site candidate, moving the
first-result local across common setup and nested-switch declaration points,
predeclaring half/color/count locals, and short-lived block scopes do not
improve its stack-slot/call frontier. Sharing the half local for scale and
width loses the first-result stores and collapses the call graph. Keep the
current production source unchanged; detailed measurements are in the
mode35/36 experiment ledger.

2026-11-25 follow-up: isolated mode45/46 half-role swapping reaches
5,993B/1,501 x86, 114/123 E8 positions, 44B total E8 displacement and 27/32
HIGHLOW sites. All 123 REL32 target symbols remain in production order. It is
rejected: it precomputes the width half before the getter and recomputes the
scale half after it, while native source/dataflow computes scale half before
the getter and width half after. The source-role verifier intentionally
rejects this value-equivalent order swap. A bit-mask-only parent-flag rewrite
also reduces the maintained build to 1,500 heads, so it is not promoted.
`src/AnimationDrawBoss.cpp` remains unchanged at 5,989B/1,501, 109/123 E8,
68B displacement, 26/32 HIGHLOW and NONEXACT. See the mode35/36 experiment
ledger for exact mismatch offsets and candidate metrics.

2026-11-25 targeted replay checkpoint: reran
`scripts/verify-animation-draw-boss-native.py` and
`scripts/verify-animation-draw-boss-source-roles.py`; both pass on the
maintained parent. The native verifier reconfirmed 5,993B/1,501 x86, 123 E8,
43 callees, 32 body HIGHLOW, both original switch tables (49+31 pointers),
and the exact four child call targets. The source-role verifier reconfirmed
the 5,989B/1,501 production object, 109/123 E8 positions, 26/32 HIGHLOW,
and the source-ordered mode35/36/45/46 arithmetic. Then ran only
`scripts/replay-exact-units.py --source src/AnimationDrawAccess.cpp`: all four
leaf functions replayed exact (20B, 20B, 26B, 93B) from one rebuilt object.
No full cold replay was run; production sources and exact child sources are
unchanged.

2026-11-25 targeted renderer-child replay: independently replayed only the six
renderer child sources reached by the Boss's detailed shape calls:

- `AnimationShapeRotatedRing1001.cpp`: `draw_shape_43c780`, 1,001/1,001B exact
- `AnimationShapeAlternating899.cpp`: `draw_shape_43df30`, 899/899B exact
- `AnimationShapeRing1468.cpp`: `draw_shape_43ab20`, 1,468/1,468B exact
- `AnimationShapeTriangle1601.cpp`: `draw_shape_43e2c0`, 1,601/1,601B exact
- `AnimationShapeEllipticLine660.cpp`: `draw_shape_43c4e0`, 660/660B exact
- `AnimationShapeEllipticFan863.cpp`: `draw_shape_43c180`, 863/863B exact

Each source was replayed individually with `replay-exact-units.py --source`;
all six used one affected canonical object each and passed strict full-byte /
relocation replay (6/6). Together with the separately replayed four
`AnimationDrawAccess.cpp` accessors, the Boss's six detailed renderer children
and four accessors remain 10 exact leaf functions / 6,651 original bytes.
No full cold replay was run and no leaf source was changed. The 5,993B parent
remains SOURCE-PRESENT/NONEXACT; exact children do not transfer exactness to
its call dispatcher.
