# TH20 reconstruction: current handoff

**Updated 2026-10-29; CORE/EXACT-386 complete 630-byte EnemyPattern item emitter.** This file is the concise
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
| Source-present mappings, all origins | **1,130** |
| Canonical strict native units | **1,129** |
| Unique canonical object providers | **226**, each with an exact `.obj` and `.receipt.json` |
| Exact game-authored whole functions | **354**, covering **114,290 native bytes** |

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
The 226 current canonical object/receipt pairs, native proof documents,
private Ghidra data and toolchains must be protected. **A native exact
function is not proof of whole-game linkage or runtime completeness.**

## Recently closed complete gameplay bosses (do not reopen as nonexact)

| Entire original function | Address | Native bytes | Focused proof |
| --- | --- | ---: | --- |
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
