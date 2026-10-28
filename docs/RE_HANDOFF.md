# TH20 reconstruction: current handoff

**Updated 2026-10-29; CORE/EXACT-463 complete InputButtonState/InputDevice native constructors.** This file is the concise
entrypoint, **not** a running transcript. Previous 1,689-line historical
handoff is available with `git show e7fa30d:docs/RE_HANDOFF.md`.
Use the [focused evidence index](EVIDENCE_INDEX.md) for individual native
observations, receipts and exact proofs, and [AGENTS.md](../AGENTS.md)
for compulsory reconstruction, commit and tool rules. Historical counts in
old reports and probe filenames are **not** current status.

## Immutable target, current exact status and protected objects

| Property | Current value |
| --- | --- |
| Comparison target | Japanese TH20 v1.00a Steamless, `resources/th20.exe` (ignored) |
| Target size | 1,858,560 bytes |
| SHA-256 | `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` |
| Provisional target boundaries | 6,928 |
| Source-present mappings, all origins | **1,159** |
| Canonical strict native units | **1,160** |
| Unique canonical object providers | **230**, each with an exact `.obj` and `.receipt.json` |
| Exact game-authored whole functions | **385**, covering **118,328 native bytes** |

The **live ledgers, not this dated table**, are authoritative. Before
reconstruction work run:

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

`config/match-units.toml` selects the protected canonical objects and
per-source locked MSVC x86 profiles. The target is the agreed Steamless
variant; embedded 1.00c title strings do not change its verified v1.00a
package identity. Never swap the target with the Steam-original backup.
The 230 current canonical object/receipt pairs, native proof documents,
private Ghidra data and toolchains must be protected. **A native exact
function is not proof of whole-game linkage or runtime completeness.**

## Recently closed complete gameplay bosses (do not reopen as nonexact)

| Entire original function | Address | Native bytes | Focused proof |
| --- | --- | ---: | --- |
| `InputButtonState::InputButtonState` / `InputDevice::InputDevice` | `0x0041F9B0` / `0x0041FCB0` | **340 / 102** | [complete genuine input state/device constructor ABI and original PE references](INPUT_DEVICE_BUTTON_CTORS_442_EXACT_RECONSTRUCTION.md) |
| `InputInf::for_view` | `0x00498FB0` | **26 (existing)** | [immutable PE RTTI InputInf, 261B original constructor and real input owner](INPUT_INF_RTTI_OWNER_LAYOUT_CORRECTION.md) |
| `AnimationPoolOwner::interrupt_handle` / `AnimationHandle::interrupt` | `0x0044EE90` / `0x0044EF90` | **246 / 35** | [whole native pool/handle animation child-interrupt protocol](ANIMATION_POOL_INTERRUPT_246_EXACT_RECONSTRUCTION.md) |
| `SoundInf::request_effect` | `0x00426D70` | **320** | [whole sound request queue, channel cooldown, original PE volume table](SOUND_EFFECT_REQUEST_QUEUE_320_EXACT_RECONSTRUCTION.md) |
| `AnimationHandle::is_valid` / `set_position_forward` | `0x0047A340` / `0x004645E0` | **45 / 26** | [full native handle validity and position forwarders](ANIMATION_HANDLE_PLAYER_FRAME_71_EXACT_RECONSTRUCTION.md) |
| `Player::suspend_option_animations` | `0x004BD0C0` | **237** | [entire native mode-3 suspension, distinct from mode-2 clearer](PLAYER_OPTION_MODE3_SUSPEND_237_EXACT_RECONSTRUCTION.md) |
| `PlayerValues<IntPoint,33>::at` / `InputButtonState::replay_current_bits` | `0x0045D670` / `0x004973A0` | **22 / 25** | [complete original main-frame call graph and two exact ABI methods](PLAYER_MAIN_FRAME_3111_NATIVE_FRONTIER.md) |
| `PlayerValues<IntPoint,33>::size` | `0x004FFFE0` | **16** | [whole exact history-array capacity; real 3,111B frame calls](PLAYER_HISTORY_AND_MOVEMENT_555_FRONTIER.md) |
| `Player::movement_mode` / `set_movement_mode` / `set_secondary_option_field_fc` | `0x004FF870` / `0x004FFF10` / `0x004FB340` | **23 / 75 / 90** | [whole Player mode and secondary option native ABI](PLAYER_MOVEMENT_MODE_188_EXACT_RECONSTRUCTION.md) |
| `Player::update_option_frame` / `IntPoint::to_vector3` | `0x004FA860` / `0x004FEE00` | **1,081 / 70** | [entire Player option gameplay boss and true ECX callback ABI](PLAYER_OPTION_FRAME_1081_EXACT_RECONSTRUCTION.md) |
| `Five native IntPoint option-coordinate operations` | `0x004F5700` / `0x004F57C0` / `0x004F5890` / `0x004F5920` / `0x004F70F0` | **49 / 45 / 48 / 45 / 65** | [whole original signed/wrapping coordinate dependencies](INT_POINT_OPTION_MATH_252_EXACT_RECONSTRUCTION.md) |
| `DamageHandle::resolve` | `0x004C0E10` | **67** | [complete safe Identifier32 bit-cast and real Hit controller lookup](DAMAGE_HANDLE_LOOKUP_67_EXACT_RECONSTRUCTION.md) |
| `PlayerShot::retire` / `PlayerShotController::return_to_free` / `PlayerShot::heap_owned` | `0x00506AF0` / `0x00506AB0` / `0x00506540` | **166 / 55 / 41** | [complete original shot retirement and ownership lifecycle](PLAYER_SHOT_RETIRE_166_EXACT_RECONSTRUCTION.md) |
| `PlayerShotController::reset_all` / `reset_timer_12400` | `0x00504950` / `0x00506CD0` | **269 / 32** | [complete PlayerShot lifetime iterator and Timer reset](PLAYER_SHOT_CONTROLLER_RESET_269_EXACT_RECONSTRUCTION.md) |
| `create_bomb_controller` / `create_hit_controller` | `0x00478300` / `0x004C20D0` | **123 / 92** | [whole native Bomb and Hit factories](BOMB_HIT_FACTORY_COMPLETE_EXACT_RECONSTRUCTION.md) |
| `FunctionChainController::remove_unlocked` | `0x00412400` | **162** | [exact whole owned-node scheduler removal](FUNCTION_CHAIN_REMOVE_162_EXACT_RECONSTRUCTION.md) |
| `EnemyPattern::emit_items` | `0x004A5350` | **630** | [entire timed item scatter and native arithmetic](ENEMY_PATTERN_ITEM_EMITTER_630_EXACT_RECONSTRUCTION.md) |
| `ProgressSaveManager` ctor / `commit` / copy / merge | `0x0050E5D0` / `0x0050F660` / `0x0050EEB0` / `0x0050F5F0` | **199 / 70 / 75 / 107** | [full Worker/ProgressSnapshot original methods](PROGRESS_SAVE_MANAGER_LIFECYCLE_EXACT_RECONSTRUCTION.md) |
| `ProgressProfile::ProgressProfile` | `0x0050AF20` | **13,684** | [complete game-specific save Profile constructor](LARGE_GAMEPLAY_BOSSES_28350_EXACT_RECONSTRUCTION.md) |
| `Animation::update_geometry` | `0x00435C80` | **5,388** | [seven-selector geometry and attached tables](LARGE_GAMEPLAY_BOSSES_28350_EXACT_RECONSTRUCTION.md) |
| `easing` | `0x00454EF0` | **4,154** | [whole game easing dispatcher plus jump table](LARGE_GAMEPLAY_BOSSES_28350_EXACT_RECONSTRUCTION.md) |
| `EnemyMotionInterpolation::sample` | `0x004A8D70` | **2,433** | [full Enemy interpolation and axis modes](LARGE_GAMEPLAY_BOSSES_28350_EXACT_RECONSTRUCTION.md) |
| `EnemyState::update_movements` | `0x004A7710` | **1,675** | [complete original Enemy movement boss](LARGE_GAMEPLAY_BOSSES_28350_EXACT_RECONSTRUCTION.md) |
| `Angle normalization and Animation rotation/scale drawing dependency chain` | `0x00438540` / `0x00438600` / `0x00450590` / `0x004505C0` / `0x004864F0` / `0x004292E0` | **187 / 29 / 33 / 47 / 60 / 16** | [six complete original bodies; folded float getter credited once](ANGLE_ANIMATION_DRAW_ABI_EXACT_RECONSTRUCTION.md) |
| `Player::rebuild_option_animations` | `0x004FACA0` | **1,518** | [full original 418-instruction option rebuild boss](PLAYER_OPTION_REBUILD_1518_EXACT_RECONSTRUCTION.md) |
| `EffectInfo::spawn_effect_variant` / `AnimationFile::spawn_flag4` | `0x0049DCF0` / `0x0049E080` | **202 / 55** | [complete alternate spawn and native flag4 wrapper](EFFECT_SPAWN_FLAG4_VARIANT_EXACT_RECONSTRUCTION.md) |
| `EffectInfo::spawn_effect` | `0x0049DB70` | **227** | [whole original animation spawn and optional pointer protocol](EFFECT_SPAWN_227_EXACT_RECONSTRUCTION.md) |
| `EffectInfo::process_queued_effects` | `0x0049D4A0` | **271** | [entire two-queue lifecycle frame](EFFECT_REQUEST_FRAME_271_EXACT_RECONSTRUCTION.md) |
| `EnemyController::graze_reward_active` | `0x0049BE20` | **123** | [whole 16-handle reward predicate](ENEMY_GRAZE_REWARD_123_EXACT_RECONSTRUCTION.md) |
| `EffectInfo::queue_effect` | `0x0049DC60` | **143** | [whole request scheduling protocol](EFFECT_REQUEST_QUEUE_143_EXACT_RECONSTRUCTION.md) |
| `PlayerRecord::add_field_e4` | `0x004FE8D0` | **87** | [complete graze counter wrap and clamp](PLAYER_GRAZE_COUNTER_ADD_EXACT_RECONSTRUCTION.md) |
| `Player::record_bullet_graze` | `0x004F8B90` | **332** | [complete graze feedback and effects](PLAYER_BULLET_GRAZE_FEEDBACK_EXACT_RECONSTRUCTION.md) |
| `clear_animation_handle_value` | `0x0049DA50` | **20** | [whole native value clear](ANIMATION_HANDLE_VALUE_CLEAR_EXACT_RECONSTRUCTION.md) |
| `AnimationFile::spawn_flag2` / `Player::animation_file_ref` | `0x0049CBF0` / `0x00421810` | **57 / 17** | [whole native resource access](PLAYER_OPTION_RESOURCE_ABI_EXACT_RECONSTRUCTION.md) |
| `WeaponStoneInfo::option_script_variant` / `initialize_option_pair` | `0x00534130` / `0x00533180` | **77 / 90** | [complete virtual dispatches](WEAPON_STONE_OPTION_DISPATCH_EXACT_RECONSTRUCTION.md) |
| `PlayerRecord::available_option_count` | `0x004B81A0` | **38** | [native option count and WeaponStone offsets](PLAYER_OPTION_COUNT_AND_WEAPON_EXACT_RECONSTRUCTION.md) |
| `Player::set_option_field_fc` | `0x004FB290` | **165** | [option management protocol](PLAYER_OPTION_MANAGEMENT_EXACT_RECONSTRUCTION.md) |
| `PlayerFeedback::record_hit` | `0x004FB3A0` | **115** | [capped hit recorder](PLAYER_FEEDBACK_RECORD_HIT_EXACT_RECONSTRUCTION.md) |
| `Player::reset_initial_state` | `0x004FB450` | **966** | [whole reset state machine](PLAYER_INITIAL_RESET_966_EXACT_RECONSTRUCTION.md) |
| `PlayerTable::clamped_field_1e4` | `0x004C5DB0` | **73** | [mode clamp and state flags](PLAYER_RESET_MODE_EXACT_RECONSTRUCTION.md) |
| `Player::clear_option_animations` | `0x004FF8F0` | **237** | [full sweep and accessor chain](PLAYER_OPTION_RESET_EXACT_RECONSTRUCTION.md) |
| `Player::draw` | `0x004F8AF0` | **145** | [draw and flush](PLAYER_DRAW_EXACT_RECONSTRUCTION.md) |
| `player_draw_callback` | `0x004FEFB0` | **13** | [whole forwarded callback](PLAYER_DRAW_EXACT_RECONSTRUCTION.md) |
| `Player::collision_rectangle_circle` | `0x004F91D0` | **661** | [rotated hit/graze](PLAYER_ROTATED_COLLISION_661_EXACT_RECONSTRUCTION.md) |
| `BulletController::rebuild_active_bullets` | `0x0047D600` | **863** | [active frame, six draw groups](BULLET_ACTIVE_UPDATE_863_EXACT_RECONSTRUCTION.md) |
| Bullet aim direction-mode selector | `0x00485740` | **434** | [aim modes](BULLET_AIM_SELECTOR_EXACT_RECONSTRUCTION.md) |
| `Bullet::process_collision` | `0x00484A20` | **2,018** | [entire hit/graze lifecycle](BULLET_COLLISION_2018_EXACT_RECONSTRUCTION.md) |
| `Bullet::update_physics` | `0x00485B60` | **1,846** | [complete state machine and native table](BULLET_PHYSICS_1846_EXACT_RECONSTRUCTION.md) |
| `Bullet::cancel` | `0x0047C8F0` | **662** | [cancel and AnimationHandle lifecycle](BULLET_CANCEL_662_EXACT_RECONSTRUCTION.md) |
| Bullet four-way wrap | `0x00483270` | **781** | [whole screen-wrap](BULLET_WRAP_BOSS_EXACT_RECONSTRUCTION.md) |
| Bullet four-edge boundary handler | `0x00482A60` | **832** | [whole collision dispatcher](BULLET_BOUNDARY_BOSS_EXACT_RECONSTRUCTION.md) |
| `BulletController::fire` | `0x00481780` | **339** | [whole firing caller](BULLET_FIRE_EXACT_RECONSTRUCTION.md) |
| `Player::collision_rectangle` / `collision_circle` | `0x004F8CE0` / `0x004F8FF0` | **777 / 466** | [rectangle](PLAYER_COLLISION_RECTANGLE_EXACT_RECONSTRUCTION.md), [circle](PLAYER_COLLISION_CIRCLE_EXACT_RECONSTRUCTION.md) |

See the ledgers for all earlier accepted small/medium functions, including
Timer, Bullet command 0/1/2/3/7/8/9/10, reflection, drawing orchestration,
AnimationHandle and Player direction. Original compiler padding, data
jump tables and shared/folded helper aliases **must not be double counted**.

The new `Player::draw()` preserves all eight native Renderer references and
was revalidated with **57/57** scoped exact units across **22** cold objects,
including all 21 previously exact header consumers. Its separate 13-byte
`player_draw_callback` forwards the native EAX result and passes 1/1
additional scoped strict unit. See the focused proof.

The freshly closed Player option state sweep and four typed accessors add
**327 strict bytes**; all **49/49** units affected by new Player.hpp
declarations replayed across **18** source objects, with no full replay.
The complete **966-byte** Player initialization/reset root `0x004FB450`
is now **966/966 strict exact**, with **208 original instructions and 40
independently verified native relocation sites**. It closes the caller of
the 237B option-sweep, typed position-history and 73/20/26B mode/flag chain.
CORE/EXACT-314 recomputed the real affected closure and passed **61/61
strict units across 21 cold objects**, with no full-graph replay. Earlier
CORE/EXACT-308 independently corrected Ghidra's tentative 0x00471170
library-function label to a genuine `std::clamp<int>` call. The next
substantial Player frontier is the separate **1,518-byte**
`Player::rebuild_option_animations` at `0x004FACA0` (now CORE/EXACT-369 full strict exact).

CORE/EXACT-316 closed the distinct complete **115B**
`PlayerFeedback::record_hit` with three originally attested native calls.
The separate **332B Player bullet graze** at `0x004F8B90` is also now
**strict exact** in CORE/EXACT-347, with 20 independently grounded original
references and 307/307 strict affected units across 42 cold objects.

CORE/EXACT-320 now closes **six** independently original option-related
functions (328 bytes), including the complete 165-byte two-array broadcast,
42-byte typed ShotController bit-zero setter, and 63-byte float-to-fixed
conversion. The `Player.hpp`/`PlayerStorage.hpp`/`Rectangle.hpp` receipt
closure was **87/87 affected strict units across 26 cold objects**.
The 1,518-byte `Player::rebuild_option_animations` was still open at that historical checkpoint; its entire original is now
strict exact under CORE/EXACT-369, not a prefix or a mere
collection of these leaf methods.

CORE/EXACT-322 adds five previously unmapped complete native functions
and promotes the independently validated original 64-byte
`PlayerRecord::starting_power` method from the existing canonical unit
(**334 nonoverlapping original bytes**). The PlayerRecord clamps, signed
option division and two actual Weapon virtual offset forwarders are exact.
Only the `PlayerRecord.hpp`/`WeaponStoneInfo.hpp` receipt closure was cold
replayed, **267/267 strict units in 33 objects**. The 1,518-byte
`Player::rebuild_option_animations` was then awaiting whole-parent reconstruction; CORE/EXACT-369 has since closed it.

CORE/EXACT-326 closes both complete WeaponStone option script and option
initialization dispatchers, adding **167 exact native bytes** to the same
canonical provider; its actual include closure passed **39/39** strict units
across **8 cold rebuilt objects**. The large **1,518-byte** Player option
rebuild was still open at this checkpoint; CORE/EXACT-369 now closes it whole.

CORE/EXACT-330 also closes the 57-byte native AnimationFile flag-2
spawn wrapper and 17-byte real Player AnimationFile getter. The actual
`AnimationFile.hpp`/`Player.hpp` receipt include closure passed **232/232
strict units across 49 cold source objects**, retaining the previous
compiler profiles. The 1,518-byte parent was **nonexact at that checkpoint** (now strict exact in CORE/EXACT-369): these new
ABIs distinguish its native 5-arg resource creation from a speculative
direct 7-arg call.

At historical CORE/RECON-333, we maintained the **whole 1,518-byte**
`Player::rebuild_option_animations` at `src/PlayerOptionRebuild.cpp`
as a historical **NONEXACT** complete-function C++20 source frontier,
subsequently closed whole exact by CORE/EXACT-369. The locked
MSVC `/GS-` plus live 8-byte-aligned `IntPoint` result matches the native
stack prologue and full return, and emits **1,518B / 411 instructions**
with **410/418 original instruction kinds in order**. Independent original
reference audit: **57 E8 calls + 3 PE HIGHLOW fields**. At that prior checkpoint, full original relocation/instruction/lifetime
correspondence was still missing, so **zero canonical exact bytes** were
then claimed (since superseded by the entire 1,518B exact parent). The resource script fields at
PlayerShotData+0x88/+0xA8 and stack-slot ownership need further review.
Read [the full boss source frontier](PLAYER_OPTION_REBUILD_FULL_SOURCE_FRONTIER.md).

CORE/EXACT-335 closes the complete **20-byte** `AnimationHandle`
value-clear operation at `0x0049DA50`, then restores its original call in
the maintained full Player option rebuild parent. Only the owning existing
`BulletCollisionAnimationHelpers.cpp` canonical object was cold rebuilt:
**8/8** exact units remain accepted; the parent was separately compiled
and was **still nonexact at that time**, before CORE/EXACT-369.

CORE/RECON-343: a fresh whole-parent audit corrected an original-absent
late AnimationFile null guard, restored native script-table base-plus-byte-
displacement indexing, and used original `-999.0f` float literals.
The complete natural source now emits **1,518B / 411 i386 instructions**,
with **410/418 native instruction kinds aligned**, and the same 57 direct
call / three absolute relocation counts. **It was NONEXACT at that earlier checkpoint**: eight
native instructions are still absent, COFF second literal offset
`+0x49F` differs from native `+0x4AB`, and full byte/relo replay fails.
Only this nonexact source/evidence changed, so zero accepted exact units
needed cold replay. See the focused whole-source frontier.

CORE/EXACT-348 also closes the complete **87-byte**
`PlayerRecord::add_field_e4` callee used by the 332-byte Player graze
feedback root. The true `PlayerRecord.cpp` object and all **59/59**
scoped strict units pass; no shared header changes or full cold replay.
The previously open `EffectInfo::queue_effect` at `0x0049DC60` is now
independently strict exact. The Enemy graze predicate `0x0049BE20`
remains a separate unclosed original function.

CORE/EXACT-352 reconstructs the complete **143B** EffectInfo request
scheduler at `0x0049DC60`, including its real `void` ABI and exact two
original E8 call anchors. Re-evaluation of actual request consumers
initially **mistyped** `EffectRequest+8` as an integer creation
policy. CORE/EXACT-361 independently corrected it to a real optional
`Animation*`; `+0xC` remains the delay countdown. The two shared-header
include closures were replayed only for **30/30 strict units across nine
cold objects**; the existing 332B graze caller still replays exact after
correcting the callee's compiler symbol identity. The enemy graze reward
predicate was separately closed by CORE/EXACT-355; its STL helper is open.

CORE/EXACT-355 now also closes the complete **123-byte**
`EnemyController::graze_reward_active` called by the original 332-byte
Player graze root, using the real `EnemyData.handles` 16-slot
`std::any_of` predicate and original bool branching. Only its new
provider was cold replayed, **1/1 exact unit in one object**. The
separate 107-byte native STL `std::any_of` callee at `0x0048A990`
is not yet an exact helper and receives no new credit.

CORE/EXACT-358 closes the entire **271-byte** `EffectInfo` deferred-
effects frame at `0x0049D4A0`, with both complete 1024-entry native loops,
all 90 original instructions and eight independently attested PE call/
HIGHLOW targets. It shares the strict `src/EffectQueue.cpp` owner with the
143-byte queue producer, and **26/26** actual affected units across
**8 cold objects** were re-accepted. The separate original 227-byte
effect spawner at `0x0049DB70` was subsequently closed whole exact by
CORE/EXACT-361.

CORE/EXACT-361 now also closes the complete **227-byte**
`EffectInfo::spawn_effect` at `0x0049DB70`, including the original 32-byte
static effect-spec records, optional preexisting `Animation*`, native hidden
result, `Animation::set_flag0_recursively` and true callback. All eight
original relocation fields (7 E8 + 1 PE HIGHLOW) independently agree.
This discovery **corrects the old `EffectRequest+8` field from erroneous
integer policy to actual optional `Animation*`**. All three original
143/227/271-byte EffectInfo functions and the 332B Player graze,
662B Bullet cancel and 2,018B Bullet collision still match strictly:
**32/32 affected-only units across nine cold objects**. No unfiltered
whole-graph replay. [Focused full proof](EFFECT_SPAWN_227_EXACT_RECONSTRUCTION.md).

CORE/EXACT-362 independently closes the **202-byte** alternate
`EffectInfo::spawn_effect_variant` and genuine **55-byte**
`AnimationFile::spawn_flag4`. Both whole original native bodies are strict
exact, including six calls/one PE HIGHLOW in the 202B method and the
flag-4 wrapper's sole original E8 target. No other ANM or EffectInfo
lifecycle root inherits credit. The **actual shared-header compiler receipt
closure**, not a full cold replay, passed **239/239 strict units across 52
cold objects**; private MSVC `$SG` renumberings were independently verified.

CORE/EXACT-369 finally closes the **entire 1,518-byte**
`Player::rebuild_option_animations` at `0x004FACA0`: all **418 native x86
instructions** and **60 independently original PE E8/HIGHLOW reference
fields**, **1,518/1,518 strict bytes**. The source is now canonical
`src/PlayerOptionRebuild.cpp`, retaining only the real original
shot-data word accesses at +0x88/+0xA8 without inventing the larger
serialized schema. Sharing the one real option pointer/counter across
four loops, 8-byte-aligned active IntPoint move/copy and **whole**
AnimationHandle return assignments restored the actual original
`sub esp,0x9C` frame and the last 10 native bytes. The exact unit
passed its one-object **1/1 focused strict cold replay**. The separate
966-byte original Player reset caller also remains strict exact.
[Whole boss proof](PLAYER_OPTION_REBUILD_1518_EXACT_RECONSTRUCTION.md).
The old CORE/RECON-333/343 nonexact status is superseded, not credited
twice.

CORE/EXACT-376 additionally closes **six complete original drawing
dependencies totaling 372 unique original bytes**, including the entire
187-byte native angle normalization, 29-byte angle-add wrapper,
33/47-byte Animation rotation pair, 60-byte native scale setter and
one 16-byte physical float getter folded across `ClockScalar`/`Angle`
source spellings. **36/36 strict units in three existing cold objects**
pass using their original compiler profiles; none of these were counted
twice. The full 273-byte Bullet drawing parent remains independently
NONEXACT with two extra SSE argument spill/reloads. [Full
independent native ABI proof](ANGLE_ANIMATION_DRAW_ABI_EXACT_RECONSTRUCTION.md).

CORE/EXACT-381 independently rescanned the immutable original
PE, complete body instructions, E8/HIGHLOW references (including
real COFF symbol addends and attached tables), and TH20 class
callers for **ten previously undercredited game-owned original
functions, 28,350 unique native bytes**. Five are large bosses:
**13,684B Profile constructor**, **5,388B Animation geometry**,
**4,154B easing switch**, **2,433B EnemyMotionInterpolation sample**,
and **1,675B EnemyState movement update**, plus five smaller
Animation/ProgressScore/Enemy factor methods. These C++ source
implementations and strict canonical units *already existed*; the
new result is an evidence-grounded **authored-origin accounting
correction**, not freshly typed 28,350 bytes of source. All **16/16
original units across exactly five existing source objects** were
cold recompiled/replayed, with no public header changes and no
unfiltered full cold replay.
[Independent original provenance and table proof](LARGE_GAMEPLAY_BOSSES_28350_EXACT_RECONSTRUCTION.md).

CORE/EXACT-382/383 newly reconstructs the complete **199-byte**
`ProgressSaveManager` constructor and **70-byte** save submission,
with natural real Worker lexical scopes emitting the original one/two
post-call NOPs. The separately maintained **75-byte** copy and
**107-byte** merge methods were already canonical exact, and their
game-owned origin is now confirmed. Four nonoverlapping game-owned
original functions add **451 authored exact bytes**, of which **269B
are actually newly codegen-exact C++ this turn**. The previously
exact 299B destructor remains exact and receives no duplicate
credit. All **5/5 affected source-owner strict units in one cold
object** pass, with all 18 original E8/HIGHLOW anchors independently
audited. No unrelated source or full cold replay.
[Whole lifecycle native proof](PROGRESS_SAVE_MANAGER_LIFECYCLE_EXACT_RECONSTRUCTION.md).

CORE/EXACT-386 closes the full original **630-byte** EnemyPattern
timed scatter boss at `0x004A5350`: all **178 instructions** and
**18 original E8 + 12 native PE HIGHLOW** references are now
strict exact. Evaluating the positive extra count before
Timer naturally restores native `mov edx,esi` before signed
multiply/divide, with no artificial padding. The existing
complete 1,576B ItemInf producer and 239B EnemyPattern drop
caller remain exact: **3/3 truly affected strict units in one
cold original source object**. No unrelated replay, no
double-counted original native addresses.
[Whole original emitter proof](ENEMY_PATTERN_ITEM_EMITTER_630_EXACT_RECONSTRUCTION.md).

CORE/EXACT-387 closes the original complete **162B**
`FunctionChainController::remove_unlocked` at `0x00412400`.
Its true owned-node release branch explicitly zeros the by-value
node parameter stack slot; the prior 156B source erroneously
omitted that native write. The corrected ordinary scoped C++
reproduces **162/162 native bytes, 52/52 instructions** with
five independently original E8 and one PE HIGHLOW field.
Only its real existing source owner was cold rebuilt:
**15/15 strict units in one object**, including native
611B update and 587B draw scheduler roots. No full replay.
[Complete native function proof](FUNCTION_CHAIN_REMOVE_162_EXACT_RECONSTRUCTION.md).

CORE/EXACT-394 closes both complete original game factories:
`create_bomb_controller` at `0x00478300` (**123B/41 instructions**)
and `create_hit_controller` at `0x004C20D0` (**92B/32 instructions**).
Both use a genuine initialization failure `goto cleanup` path
and invalidation of the retired local pointer. The entire native
original includes an otherwise Ghidra-omitted short jump inside
each function; neither original 123/92-byte interval is truncated.
All **15 independent E8/HIGHLOW reference fields** agree with the
real immutable original and locked COFF objects. Only the
actual two source providers and their six earlier exact units
were cold rebuilt, **8/8 strict units in two objects**,
with zero unrelated/all-graph replay. The Bomb diagnostic,
real Session/Context publisher and Hit allocator establish
the original TH20 gameplay object ownership.
[Two complete native factories](BOMB_HIT_FACTORY_COMPLETE_EXACT_RECONSTRUCTION.md).

CORE/EXACT-398 closes the complete **269B native
PlayerShotController reset boss** at `0x00504950`, and its separate
complete **32B Timer reset wrapper** at `0x00506CD0`. Both are
strict whole-original exact: **82+13 i386 instructions and
17 independent PE E8/HIGHLOW references**. The actual native
PlayerShot iterator is destroyed before three Timer resets;
the 30-counter native `std::array` fill uses actual field
`+0x12468`. The prior exact 966B Player initialization caller
and complete 1,518B Player option rebuild still pass strictly.
The genuine *previous* PlayerStorage.hpp compiler receipts
identify 25 existing source providers/74 strict units. Adding
one new provider with two exact units yields **76/76 actual
affected strict units across 26 serialized cold objects**, with
no full/unfiltered cold replay. One MSVC private `$SG` renumber
in the original Player constructor was reconciled only after
confirming native original string target `0x00572BB8`, field
offset/type and all nonrelocation bytes. Separately original
At the earlier CORE/EXACT-398 checkpoint, the separate
166B `PlayerShot::retire` remained unclosed; CORE/EXACT-402
has since reconstructed the complete original in its own
independent exact unit.
[Whole original shot reset and Timer proof](PLAYER_SHOT_CONTROLLER_RESET_269_EXACT_RECONSTRUCTION.md).

CORE/EXACT-402 separately closes all three entire original
PlayerShot retirement methods: **166B `PlayerShot::retire`** at
`0x00506AF0`, **55B owner return-to-free** at `0x00506AB0`,
and **41B heap-owned bit predicate** at `0x00506540`. Their
complete original **84 native instructions and ten independent
PE E8/HIGHLOW references** match strict game C++ without
stubs or dead locals. The 166B method tears down the real
AnimationHandle, conditionally resolves/retires DamageRegion,
detaches shot from the active intrusive list, returns non-heap
shot storage to `PlayerShotController::free` and conditionally
releases heap-owned PlayerShot through the native allocator.
The original 269B shot reset, 32B Timer wrapper, 966B Player
initializer and 1,518B Player options boss remain independently
exact. Existing true `PlayerStorage.hpp` compiler receipts
identify **26 old source providers, 76 earlier strict units**;
the three new units give **79/79 exact units in 26 serial
cold objects**, not a full cold replay. A single MSVC-private
`$SG` rename retained its original PE string destination
`0x00572BB8` and the strict original byte comparison.
At that earlier checkpoint, the separate 67B `DamageHandle::resolve`
at `0x004C0E10` remained open; CORE/EXACT-407 now closes it
separately, without inferring exactness from its caller.
[Whole original retirement proof](PLAYER_SHOT_RETIRE_166_EXACT_RECONSTRUCTION.md).

CORE/EXACT-407 independently closes the entire **67B
DamageHandle::resolve** native game method at `0x004C0E10`,
**24/24 original instructions** and two original native E8
references, resolving to the previously exact 26B
`hit_controller(0)` and 264B `HitCtrlInf::find`.
The correct source retains DamageHandle's original raw
4B member and exact folded 24B scalar constructor;
the defined MSVC `__builtin_bit_cast` copies the ID to
a genuine by-value Identifier32 without an unobserved
`/Od` helper or undefined pointer alias cast.
Only the real previous `PlayerStorage.hpp` receipt closure
of **26 old source providers / 79 old strict units**
plus one new source object is rebuilt:
**80/80 whole native strict units in 27 cold objects**
across six serialized batches. No global cold replay,
duplicated native byte credit or ABI-breaking header
retyping. The complete prior 166B shot retire, 269B
shot reset, 966B Player reset and 1,518B option boss
remain exact.
A separate existing `src/HitCtrlInf.cpp` provider was cold
rebuilt after its previous global-input receipt became stale:
**16/16 strict units in one additional object** passed,
including complete 26B/264B original callees. This is
outside the actual header-include closure and does
not expand the 80-unit changed-source scope.
[Whole original 67B PE/COFF proof](DAMAGE_HANDLE_LOOKUP_67_EXACT_RECONSTRUCTION.md).

CORE/EXACT-410 adds **five entire native C++ IntPoint
gameplay methods totaling 252 physically unique original
bytes**, discovered from the whole original **1,081-byte /
325-instruction Player option-frame** at `0x004FA860`
(which itself is **not yet strict exact**). The five
originals are 49B nonzero comparison, 45B scalar
multiplication, 48B subtraction, 45B signed division
and 65B in-place coordinate addition, where the last
method returns the *entire* eight-byte IntPoint value,
not IntPoint&. All original instruction bytes and the
three independently native original calls to the real
`IntPoint(int,int)` constructor at `0x0040DE00`
are strict exact. The **previous** `Rectangle.hpp`
compiler receipts selected 31 actual source objects
with 100 old strict units; the five new bodies in the
**existing** Rectangle object result in **105/105
strict units in 31 serial cold objects**, not a full
repository cold replay. Six MSVC-private `$SG` labels
were reconciled only with independent original PE
target verification. At CORE/EXACT-410 time, the larger 1,081B
option-frame and 3,111B Player frame bosses were
both open. The former is now fully exact in
CORE/EXACT-417, while the latter remains open.
[Whole independent IntPoint ABI proof](INT_POINT_OPTION_MATH_252_EXACT_RECONSTRUCTION.md).

CORE/EXACT-417 closes the entire **1,081-byte Player
per-option frame gameplay boss** at `0x004FA860`,
**325/325 original i386 instructions and all
40 independent PE E8/HIGHLOW references**. The
true 4-byte `PlayerOption` callback fields are
**single-inheritance member-function pointers**,
giving the original ECX receiver and avoiding two
unobserved 5-byte function-pointer spills.
A chained actual IntPoint interpolation expression
retains the true aggregate hidden-result ABI and
signed frame gates, in addition to animation and
resource ownership. Its separate native **70-byte
IntPoint::to_vector3** at `0x004FEE00` is also
**70/70 exact**, with two independently original
128.0f PE HIGHLOW fields; the previous five full
IntPoint helpers remain exact and are not duplicated.
The previous `Player.hpp`/`PlayerStorage.hpp`/
`Rectangle.hpp` receipt union covers **31 old source
providers / 105 old strict units**; adding one
new actual provider and one method to an existing
owner gives **107/107 strict units in exactly
32 serialized cold objects**. Six compiler-private
Player/Dialogue/Ascii `$SG` identifiers were
accepted only against independently real native
string targets, reference offsets and full
nonrelocation bytes. The original **3,111-byte unnamed Player
main-frame** enclosing caller remains independently
NONEXACT. The historical `Player::frame_changed`
name was wrong (distinct exact native 25B at
`0x004C0CE0`). No unfiltered full cold
replay. [Independent entire Player option frame
proof](PLAYER_OPTION_FRAME_1081_EXACT_RECONSTRUCTION.md).

CORE/EXACT-420 closes **three complete Player
mode and secondary-option methods** called from the
still-open 3,111B Player frame boss: **23B**
`movement_mode` at `0x004FF870`, **75B**
`set_movement_mode` at `0x004FFF10`, and
**90B** `set_secondary_option_field_fc` at
`0x004FB340`. The true two-bit mode lives in
Player flags bits 6..7; the native setter resets
`timer_2070` then **returns the bit-field
assignment expression** (not a separate reload),
reproducing all 75 native bytes naturally.
The exact 90B method walks the real 12-entry
`secondary_options` only, using the native
begin/end pair (the original begin body is folded
with the existing 14B Motion accessor). All
65 original instructions and **three independent
native PE E8 call fields** are strict exact.
Real old `Player.hpp`/`PlayerStorage.hpp`
receipt closure selects 28 source providers with
81 exact units; adding three functions in the
**same existing canonical object** produces
**84/84 strictly original exact units across
28 serialized cold objects**. No full cold
replay, no duplicate physical original byte
credit, and the 3,111B parent remains nonexact.
[Complete 188-byte game native proof](PLAYER_MOVEMENT_MODE_188_EXACT_RECONSTRUCTION.md).

CORE/EXACT-429 independently closes the original
**16-byte `PlayerValues<IntPoint,33>::size()`**
at `0x004FFFE0` (8 native instructions, no
relocations). The physical 3,111B Player frame
calls it **three** times to bound 33 fixed
history records. CORE/RECON-429 additionally
maintains the **entire real 555-byte**
`Player::apply_move_delta(int,int)` at
`0x004FFA10` as complete typed C++20
(**561B / 136 instructions currently emitted;
all 135 original mnemonic kinds ordered; real
17 E8 plus 10 PE HIGHLOW original refs**).
**This 555B motion boss is NONEXACT**, with
one observed extra 6B SSE y-bound float spill,
and receives **0 game-exact bytes**. Its
original caller is the separate still-open
3,111B Player main frame. Only `Player.hpp`
was shared-header changed, so the old
canonical include receipts selected **25
source objects / 69 existing strict units**;
the new exact 16B template instantiation
within existing `PlayerAccessors.cpp` yields
**70/70 exact units in 25 scoped cold
objects**. The new nonexact full source
`src/PlayerMovement.cpp` was compiled
independently. No repository-wide cold replay,
duplicate physical byte or fake NOP padding.
[Whole native evidence and honest 555B
frontier](PLAYER_HISTORY_AND_MOVEMENT_555_FRONTIER.md).

CORE/RECON-432 independently audits the entire original
**3,111B / 783-instruction** *unnamed* Player main-frame
routine at `0x004F9C30`, including its **67
native E8 call fields, 37 PE HIGHLOW sites**
and original live Player/Input/Option fields.
**Do not call this original `Player::frame_changed`**:
that decorated source name already belongs to a
different **25B exact original member** at
`0x004C0CE0`. The original 3,111B body still
remains nonexact.
CORE/EXACT-433 closes two real native original
game callees: **22B** `PlayerValues<IntPoint,33>::at`
at `0x0045D670` (three direct original calls),
and **25B** `InputButtonState::replay_current_bits`
at `0x004973A0` (ten calls to real input word
`+0x29C`). Thus **58/67 original direct call sites**
now have independently canonical-exact callees;
the other nine still include the separate full
nonexact 555B Player movement boss. The only
affected existing source objects were
`src/PlayerAccessors.cpp` and `src/InputState.cpp`:
**17/17 actual scoped strict units in two
cold objects**, with no full-repository replay or
duplicate exact bytes.
[Complete original Player 3,111B call graph and
corrected identity](PLAYER_MAIN_FRAME_3111_NATIVE_FRONTIER.md).

CORE/EXACT-436 closes the **entire distinct 237-byte
Player option mode-3 suspension boss** at `0x004BD0C0`,
called by the **still nonexact** 3,111B original
Player main frame at `+0x75`. It **sets** bit 1,
unlike the *other* already exact 237B mode-2
`Player::clear_option_animations` at
`0x004FF8F0`. All 72 original instructions
and eight immutable PE E8 reference fields are
strict exact; four original calls invoke the
folded 23B PlayerOption array indexer, and four
the 22B mode-3 animation interrupt wrapper.
Actual Player.hpp preedit receipts identify
25 old source owners/71 strict units; one new
function in an existing owner gives **72/72
native strict units in 25 serialized cold objects**.
One compiler-private Player `$SG` rename was
independently checked against original string
target `0x00572BB8` and unchanged native bytes.
The 3,111B parent itself remains NONEXACT,
now **59/67 direct original E8 call sites**
have exact native callees; eight remain.
The separately existing source object for the 22B
mode-3 cancellation callee had a stale broad-input
receipt; one additional focused cold replay passed
**8/8 units in its own object**, separately from
the actual 72-unit header closure.
[Whole separate mode-3 original proof](PLAYER_OPTION_MODE3_SUSPEND_237_EXACT_RECONSTRUCTION.md).

CORE/EXACT-439 adds **two whole original
AnimationHandle game members totaling 71B**:
`is_valid` at `0x0047A340` (**45/45B**)
and `set_position_forward` at `0x004645E0`
(**26/26B**). The original independently
attested E8 calls target already strict
`AnimationHandle::resolve` `0x0044CED0`
and `set_position` `0x004502C0`.
All 27 complete original instruction heads
and both independent PE reference fields
are strict exact; no original HIGHLOW fields.
The still-open 3,111B Player main-frame
calls the first twice and the second once,
raising exact callee original call sites to
**62/67**, leaving five separately open.
The genuine `AnimationHandle.hpp` preedit
compiler receipts cover **106 old source
objects and 471 earlier exact units**;
with two new methods in the same canonical
owner, **473/473 strict units in exactly
106 serial cold source objects** passed
in 22 batches, with no full all-repository
replay. Compiler-private `$SG` symbols were
reconciled only against independent original
PE addresses, fields and full unchanged
nonrelocation bytes. Original gameplay
bosses retain their strict exact matches.
[71-byte original native ABI proof](ANIMATION_HANDLE_PLAYER_FRAME_71_EXACT_RECONSTRUCTION.md).

CORE/EXACT-445 closes the **whole 320-byte
SoundInf::request_effect** at `0x00426D70`,
**320/320 native exact** with all **102 original
i386 instructions** and **seven independently
original E8 + one PE HIGHLOW** references.
The actual 12-slot requests with 0x208 stride,
signed ID sentinel, at most 60 pan samples
and original 90-channel cooldown are preserved.
The original volume word `0x005AE6F2` equals
base `0x005AE6EA` plus real +8 COFF
addend. The separate 22B cooldown setter
folds to previously exact `EnemyPattern::set_base_kind`
at `0x00411570` and gets no duplicate
physical byte credit. The only changed source
interfaces were `SoundEffects.hpp` and its
existing `SoundEffects.cpp` owner: prior
compiler receipts identify **12 actual source
providers with 24 old units**, and the new
complete boss gives **25/25 strict native
units in 12 low-priority cold objects**.
Original 3,111B Player main-frame called
this twice; **64/67 original direct E8
call sites now have independently exact
callees**, three remain. The parent
remains NONEXACT. No unfiltered full replay.
[Whole 320B original sound request proof](SOUND_EFFECT_REQUEST_QUEUE_320_EXACT_RECONSTRUCTION.md).

CORE/EXACT-449 independently closes the
**246-byte/77-instruction original
AnimationPoolOwner::interrupt_handle** at
`0x0044EE90` and distinct **35-byte/15-instruction
AnimationHandle::interrupt` at `0x0044EF90`.
**Corrected ABI**: 246B belongs to the large
pool receiver, takes two stack args and walks
exception-safe child links; 35B bridges the
four-byte handle value and event through
global pool `0x005C0028`. All **13
original E8 and 3 original HIGHLOW**
fields, including native EH/cookie and
actual child-animation targets, are
independently original-attested exact.
The separately original 456B
`AnimationPoolOwner::resolve_handle` at
`0x0044CD00` stays NONEXACT. Real prior
`AnimationRuntimeOwner.hpp` receipt closure
had ten sources/20 strict units; adding the
preexisting five-unit `AnimationHandle.cpp`
provider and two new complete methods yields
**27/27 strict units in 11 low-priority
cold objects**. One compiler-private Bullet
`$SG` renumber independently re-attested its
original native string. The 3,111B Player
main-frame now has **65/67** exact callee
call sites, two remaining; parent remains
NONEXACT. No global cold replay.
[Whole animation pool/handle 281B original proof](ANIMATION_POOL_INTERRUPT_246_EXACT_RECONSTRUCTION.md).

CORE/EXACT-454 independently closes the
**26-byte/10-instruction complete original
InputController::for_view(int)** at `0x00498FB0`.
The original Player frame uses the genuine
input manager global pointer `0x005B8898`,
Player index `+0x14854`, and controller
input pointer table `+0x2E30 + index*4`;
the typed result is `InputButtonState*`
and the original member has no E8 or PE
HIGHLOW fields. At CORE/EXACT-454 time, the manager
prefix layout was not yet known, and the
source deliberately avoided fake padding.
CORE/EXACT-455 subsequently recovered its
original RTTI `InputInf` name and constructor-
observed device/slot/bindings prefix; the
old partial owner is superseded. Prior real `InputState.hpp`
compiler receipt closure had **one old
source object / 12 strict units**; the
new entire native method yields **13/13
strict units in that one cold source**
with all old Replay and input routines
still exact. The **3,111-byte original
Player main-frame** now has **66/67
native direct E8 call sites** pointing
to independently exact game callees.
The remaining original 555B
`Player::apply_move_delta` body is still
NONEXACT (561B current source);
the enclosing 3,111B parent is also
NONEXACT. No whole-repository replay.
[Whole native Player InputController proof](INPUT_CONTROLLER_PLAYER_VIEW_26_EXACT_RECONSTRUCTION.md).

CORE/EXACT-455 **corrects the owner, not the
physical native match**, for the already strict
original 26B input lookup at `0x00498FB0`.
Independent original RTTI at `0x005B41F8`
is **`.?AVInputInf@@`**; the original complete
261B `InputInf` constructor at `0x0041F8A0`
builds a real 16B TaskInfo base, 12×0x3D4
InputDevices at +0x20, real state arrays
and two `InputButtonState*` view slots at
+0x2E30, plus four 0x30 InputBindings at
+0x2E38. The previous partial and raw-pointer
cast `InputController::for_view` source was
retired in favor of real
`InputInf::for_view`, whose 26/26 original
bytes remain unchanged. **Do not add 26
game exact bytes again.** The existing
InputState owner is now 12/12 strict,
the new InputInf owner 1/1, for **13/13
changed-source strict units in two cold
objects**. The 1,081B PlayerOptionFrame
boss was additionally individually replayed
1/1 after its old broad-input receipt
became stale. Canonical provider count
is **230**; authored exact function count
**383** and original exact bytes **117,886**
are unchanged. The 261B InputInf ctor,
555B Player motion and 3,111B enclosing
Player main frame remain **NONEXACT**;
the enclosing frame still has **66/67**
exact original direct-call targets. No
whole-repository cold replay.
[Immutable RTTI/InputInf layout proof](INPUT_INF_RTTI_OWNER_LAYOUT_CORRECTION.md).

CORE/EXACT-463 independently closes **two whole
game-owned original native input constructors**
in the true `InputInf` construction chain:
**340B/81-instruction**
`InputButtonState::InputButtonState` at
`0x0041F9B0`, and **102B/28-instruction**
`InputDevice::InputDevice` at
`0x0041FCB0`. Both are complete source-owned
i386 exact functions with **all eight original
PE E8 fields** targeting actual CRT memset
and the 340B child ctor. The 340B method
value-initializes five separate 128B arrays
and performs the genuine final four-byte
state reset; 102B initializes the real
0x3D4-byte device and its 256B raw input
region, then clears its tail state.
The original **261B `InputInf::InputInf`**
at `0x0041F8A0` actually builds twelve
of these devices at +0x20, but the entire
manager ctor itself remains **NONEXACT**.
Previous actual `InputState.hpp` compiler
receipt closure had only **two source owners
and 13 strict native units**. Adding two
complete constructors in the same existing
`InputState.cpp` object gives **15/15 strict
native units in two cold objects**,
without any global cold replay. The exact
26B `InputInf::for_view` and existing
583B input update/475B replay update
remain full strict exact. Authored total
is **385 complete native functions /
118,328 original bytes**, canonical
units **1,160** in 230 physical providers.
[Both entire original native input constructors](INPUT_DEVICE_BUTTON_CTORS_442_EXACT_RECONSTRUCTION.md).

## Open complete-function roots — next agent's priorities

1. **Bullet command 11 `0x00481200`: 1,404 bytes / 357 native
   instructions.** The entire boss now has maintained nonexact
   `src/BulletCommand11.cpp`; read the [whole source frontier](BULLET_COMMAND11_FULL_SOURCE_FRONTIER.md). Its entire real 50B cross, 50B dot and 155B
   normalization helpers are exact. Full private candidates live at
   `.analysis/core255-BulletCommand11-splitarrays.cpp` and
   `.analysis/core263-command11-polar-one-literal.cpp` (older experiments). Real original
   `1.0f` for polar radius produces **353/357 original instruction kinds**
   in one full-body candidate; the remaining four original stores of
   384.0/448.0 may reflect real locals, but do **not** insert inert locals
   merely for bytes. Read
   [complete command11 geometry frontier](BULLET_COMMAND11_GEOMETRY_EXACT_RECONSTRUCTION.md).
2. **BulletController single-group draw `0x0047DB70`: 273 bytes.**
   Maintained entire function source now lives at `src/BulletDrawGroup.cpp`;
   read [the whole typed source frontier](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md).
   Original parent `draw_groups` at `0x0047DC90` is separately exact (81B).
   CORE/RECON-375 restored genuine **Animation+0x4A2 high-three-bit**
   mode access in maintained `Animation.hpp` while preserving the original
   raw alias; complete typed source now emits **283B / 84 instructions**
   and aligns **82/82 original mnemonic kinds**, but still contains two
   extra SSE float-offset spill/reloads (+10B) against original
   **273B / 82 instructions**. The genuine Animation.hpp receipt
   closure replayed **263/263 exact units across 56 cold objects**.
   The entire original draw-group parent is still NONEXACT; seek its
   actual pi/2 and Angle return ABI without manual padding.
   See [complete updated draw frontier](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md).
3. **Whole Bullet single-shot emitter `0x004818E0`: 3,735 native
   code bytes plus one NOP and two native switch tables (13+11 entries),
   **3,832B whole compiler contribution** and eight linker `CC` bytes.
   Complete C++20 private source candidates:
   `.analysis/core288-BulletEmitterFull.cpp`,
   `.analysis/core290-BulletEmitterFull-RealMetadataLifetime.cpp` and
   `.analysis/core292-emit-*.cpp`. The best ordered mnemonic alignment
   is **789/935**, still *not exact*. Real
   `std::shared_ptr<EtamaArgInf>` move ownership at `0x0047C530`
   differs from the installed STL (native 63B versus probe 54B);
   Renderer Animation allocation (298B), file script binding (338B),
   and 66B Bullet intrusive prepend need exact ABI closure. See
   [full emitter C++ frontier](BULLET_EMITTER_FULL_CXX_FRONTIER.md).
4. **Entire Bullet command/update dispatcher `0x0047DCF0` (12,140B)**
   and **Enemy ECL opcode dispatcher `0x0048C010` (41,967B)** remain
   separate nonexact large roots. The Enemy whole-root source and
   historical host investigations are documented by
   [dispatch layout](CORE_ENEMY_DISPATCH_LAYOUT.md) and
   [source map](SOURCE_MAP.md). Old dual-sanitizer host scenario counts
   are *historical only*, not a current CI or exactness gate. Animation
   VM, Renderer resource owners and Player damage lifecycle also remain
   substantial open work.
5. **Player bullet graze feedback `0x004F8B90` (332B) is now strict
   exact**, with maintained `src/PlayerGrazeFeedback.cpp` and
   [independent full proof](PLAYER_BULLET_GRAZE_FEEDBACK_EXACT_RECONSTRUCTION.md).
   Its three formerly speculative callee member interfaces were re-reviewed
   against original Ghidra/PE evidence, and the 307-unit genuine include
   closure passed. Their *separate callee implementations* and EffectInfo
   lifecycle remain open and must not inherit the caller's exact credit.

## Closed complete Player reset and option-animation rebuild chain

The separately complete **966-byte** `Player::reset_initial_state` at
`0x004FB450` and its genuine complete **1,518-byte** callee
`Player::rebuild_option_animations` at `0x004FACA0` are now **both
independently strictly exact**. The rebuilt options function is
**418/418 original instructions** with all 57 native direct-call and
three original PE HIGHLOW fields. Its maintained source and entire
original proof are [here](PLAYER_OPTION_REBUILD_1518_EXACT_RECONSTRUCTION.md);
the earlier 966-byte caller proof is
[here](PLAYER_INITIAL_RESET_966_EXACT_RECONSTRUCTION.md). The original
embedded shot-data schema beyond consumed words and other large gameplay
functions remain open, not the entire option rebuild boundary.

## Resume workflow and bounded verification

The locked compiler profile for most accepted x86 objects is
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc`. Some canonical sources use other separately verified
profiles: **always read each unit's `profile`**. Use `nice -n 15` for
MSVC/Ghidra/replay. The actual source include closures are captured in
canonical `.receipt.json` files; never estimate the impact of a shared
header from a static old handoff. Example:

```bash
# Only when the source or an included header was actually modified:
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/ChangedSource.cpp
# Always run for any admitted exact code/tracking changes:
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/progress.py --check
git diff --check
```

For a shared header edit, inspect prior receipts for every canonical
provider that includes that header and replay **only those** sources.
If MSVC renumbers a private `$SG` string symbol, adjust *only* the
compiler-local symbol after confirming the original relocation offset,
type and target remain independently unchanged, then rerun its complete
unit. All accepted claims require **complete function native equality**
plus independently grounded original relocation targets; a provisional
`structural-exact` diagnostic alone does not earn credit. Never run
unfiltered whole-repository cold replay for a routine checkpoint.

For documentation-only or ignored artifact cleanup, do **not** invoke
MSVC, Ghidra, full CI or native replay on an unchanged reconstruction
graph. Run the target hash, Git diff/link checks and tracking/progress
checks instead. Commit substantive work promptly with subjects starting
**`gpt-web:`**. Maintain all comments/docs/commit messages in English;
answer the user in Chinese.

## Protected storage, artifact retirement and history

CORE/CLEANUP-300 retired **2,496 unused ignored files / 203.65 MiB**:
2,113 obsolete noncanonical build outputs and 383 unreferenced historical
compressed snapshots. The exact retired paths, sizes and SHA-256 values
are in ignored `.analysis/core300-retired-artifact-inventory.json`.
**All 212 canonical `.obj`/receipt pairs remain intact**; the target,
Ghidra database, 4.2GB Wine/MSVC toolchain, active unresolved-boss probes
and referenced private native evidence were not changed. The safe dry-run
and protected-retirement criteria are in
`.analysis/core300-safe-artifact-prune.py` and
[reconstruction workflow](RE_WORKFLOW.md). Retired build-only products
can be regenerated from retained private `.analysis` source scripts or
maintained sources. Historical proof documents and old dated handoffs
remain recoverable from Git, e.g.
`git show e7fa30d:docs/RE_HANDOFF.md`.

**Do not `git clean -fdx`, remove entire `build/` or `.analysis/`, or
reclaim `.tools/`, `ghidra-project/`, `_reference/` or executable files.**
Treat every dirty source edit as owned work: investigate it and preserve
nonexact hypotheses privately before cleaning maintained declarations.
