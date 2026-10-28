# Current TH20 reconstruction handoff

**Checkpoint:** CORE/EXACT-235 adds complete 707B native rectangle/radial Bullet cancellation boss, 25 original relocation anchors, 54/54 scoped strict units; CORE/EXACT-232 adds complete original 419B Bullet cancellation-to-item boss and 136B edge predicate, 54/54 full impacted exact units; CORE/EXACT-231 adds full original 388B filtered Bullet cancellation and true by-value std::function callback, 52/52 affected strict units; CORE/EXACT-229 adds complete exact 401B capped Bullet radial cancellation and the real 2-bit flags layout with 51/51 affected strict units; CORE/EXACT-228 adds exact 122B Bullet radial distance predicate, preserves full 320B cancel-near (2/2 scoped); CORE/EXACT-227 admits full original 320B Bullet spatial cancellation with fourteen relocations, 50/50 exact affected-only units; CORE/EXACT-226 adds complete 242B Bullet cancel-all boss and 19B active-list owner, all 49/49 corrected scoped units including a previously missed 832B caller; CORE/EXACT-225 adds full 81B native Bullet six-group draw orchestration, unified one narrow external Renderer ABI, 46/46 strict affected-only units; CORE/EXACT-220 adds complete exact 832B Bullet boundary boss (31 relocations) and integrates exact 176B rectangle (47/47 affected strict units); CORE/EXACT-219 adds complete exact 176B Bullet four-edge rectangle with original SSE 224f center, seven relocations and two original 832B caller sites; CORE/EXACT-218 closes fourth complete 277B Bullet upper reflection, 36/36 affected native replay; CORE/EXACT-216 adds complete 329B/319B native Bullet horizontal reflection with all 30 relocations and 37/37 strict affected replay; CORE/EXACT-214 admits the whole 281B native Bullet reflection and 22B/17B typed helpers (38/38 strict affected replay); CORE/REVIEW-212 corrects real Bullet-list head insertion and the exact 291B caller’s symbol/semantics; CORE/EXACT-211 adds three fully exact Bullet lifecycle/emitter dependencies (291+54+19B), all 38/38 affected units; CORE/EXACT-210 adds the entire exact 339-byte Bullet firing boss with 11 relocations and 36/36 affected strict units; CORE/EXACT-209 strictly reconstructs both the 19-byte native Player position getter and the 157-byte direction method (32/32 affected-only strict replays). CORE208 adds the complete original 252-byte Enemy opcode 632 raw script-pointer branch to the same entire 41,967-byte root; CORE207 queue copying and all native exact proofs remain protected.
This is the **current** entrypoint for the next agent, not a cumulative session
log. Read [AGENTS.md](../AGENTS.md) first for exactness policy, source rules,
active-session commit subjects and **affected-only** replay requirements. This
handoff describes the live state on 2026-10-28; older batch counts in focused
evidence documents are historical, not competing current status.

## Validation maintenance (Codex, 2026-10-28)

The historical portable semantic suite is retired: 142 fixture/runner files,
including allocation/null/exception scenarios and sanitizer hosts. Five
exact-oracle/control-plane test files remain; see [retained tests](../tests/README.md).
This cleanup changes no reconstruction input: **zero affected replay units**.
Use affected native builds and complete strict replay for exact checkpoints;
old scenario totals and test paths below remain historical evidence. Concurrent
web reconstruction is a separate batch. Commit prefixes follow the active session.

## Repository, target and canonical status

- Worktree: `main`, with CORE/EXACT-185 saved as commit `2713b35`
  (`gpt-web: reconstruct exact Bullet file getter for Enemy opcode 555`).
  CORE186 555 integration is `126eb2a`; CORE187 shared 609–612 branch is
  `25935c1`; CORE188 ABI/COW is `0358825`. CORE/EXACT-190 adds one
  genuine complete 151-byte EnemyController resource selector and preserves
  the unchanged CORE188 full-root host. Inspect the live Git status and
  `git log -5 --oneline` for the newest checkpoint.
  Factory has no network/push. **Do not discard dirty or ignored work:** the
  user explicitly said the single worker owns all modifications.
- Target: Japanese TH20 **v1.00a Steamless**, `resources/th20.exe` (ignored),
  SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
  Do not switch to the Steam-original backup or any other release. See
  [target provenance](TARGET_PROVENANCE.md) and `config/target.toml`.
- Live ledgers: **6,928** target function candidates, **1,020** source-present
  mappings, **1,011** physical canonical strict units, **225** confirmed
  authored exact functions / **58,718** authored exact bytes. The 168 current
  canonical objects cover **183,109** comparison bytes. **Nine**
  source-present whole-function mappings remain nonexact. These are not a
  whole-game completion percentage; see generated [progress](PROGRESS.md).
- The **41,967-byte** native `EnemyState::execute_opcode()` at `0x0048C010`
  is still **not machine-code exact**. Its *single complete-root source draft*
  covers **141 effective opcode values / 109 primary heads** and passes
  **44,554 / 44,554** `-O2`/UBSan **and** ASan+UBSan whole-root host scenarios
  (ASan `vptr` excluded for unresolved fixture RTTI; leak checks enabled). Do not claim
  partial native root bytes as exact functions.

## Latest work to resume

CORE/EXACT-235 (web) admits whole native **707-byte BulletController
rectangle-cancel boss** `0x0047CC90` (209 instructions, **25 independently
anchored native relocations**). Two *real complete* original
`geometry::rectangle_circle` calls (original 669B callee) test the incoming
oriented rectangle and original **384.0f × 448.0f gameplay field** with
scaled Bullet radius; live typed active list/iterator/EH and two-bit cancel
flags plus 662B native child `Bullet::cancel` are preserved. Natural
short-circuit rejection and real `0.0f` SSE literals produce **707/707
canonical original bytes**; all **53 old Bullet.hpp-dependent exact units**
were freshly recompiled, **54/54 strict units across 17 cold objects**,
no whole-graph replay. Only compiler-private `$SG` names changed while
all original relocation destinations remained fixed. See
[complete 707B boss evidence](BULLET_RECTANGLE_CANCELLATION_EXACT_RECONSTRUCTION.md).
Current authored-exact ledger: **250 functions / 64,804 bytes**.
The 662B Bullet cancellation child, 3,735B Bullet single-shot emitter, and
41,967B Enemy root **remain nonexact**; private whole-body probes for each
must not be admitted by length or partial similarities.


CORE/AUDIT-234 (web): independently re-audited full native 273B
`BulletController::draw_group` and native 33B/103B Timer float member
wrapper/set methods called by the 662B Bullet cancel and 3,735B emitter.
Original x87 `add_angles` result is stored to a float local then SSE-reloaded;
private 272B/293B source versions still **nonexact**. Timer float set is
not the already exact `Timer::set(int)`; it stores an untruncated fraction.
Both Timer methods and 273B draw remain **nonexact**, with no maintained
source or exact-credit changes. See [Bullet cancel Timer frontier](BULLET_CANCEL_662_NATIVE_FRONTIER.md)
and [single-group draw frontier](BULLET_DRAW_GROUPS_EXACT_RECONSTRUCTION.md).
This documentation-only audit affected **zero exact source units**; no
replay or whole-graph cold build was performed. Current exact totals remain
**249 functions / 64,097 bytes**.


CORE/EXACT-232 (web) newly reconstructs **two entire original native
functions** in the real Bullet cancel-to-ItemInf path: `Bullet::cancel_drops`
`0x0047D3D0` **419/419 bytes** (121 instructions, 20 original relocation
anchors) and `bullet_position_outside_screen` `0x00485390` **136/136 bytes**
(5 original relocation anchors). Restores native signed modulo5, process
RNG next()%2/%3 short circuit, live Context ItemInf ownership and original
spawn/spawn_many, as well as four ordered SSE screen comparisons with
actual -384/384/448 and 32/2 float identities. The prior 662-byte
`Bullet::cancel` boss is **still source/COFF nonexact** but its two true
child functions now have exact maintained source. Full `Bullet.hpp` closure:
**52/52 prior strict units** plus 2 new, **54/54 units across 17 freshly
compiled objects**. Private `$SG` symbols renumbered with original data
relocations unchanged; no whole-graph replay. See
[full exact item-drop and bounds proof](BULLET_DROPS_AND_SCREEN_EXACT_RECONSTRUCTION.md).
Current maintained authored-exact totals **249 functions / 64,097 bytes**.
The original 3,735B Bullet emitter and 41,967B Enemy opcode root also remain
nonexact; no full-game link/runtime claim.


CORE/EXACT-231 (web) newly admits the **complete original 388-byte**
`BulletController::cancel_near_if` `0x0047D240` with all **17 native
relocations**, real 122B radius predicate, 662B nonexact child cancel,
true live Bullet active list, flags and Controller cancel counter. An
independently established **by-value 40B std::function<int(const Vector3&)>
callback** (including full-EAX predicate return and real `0x00414400`
destructor) is required for the original `ret 0x30` ABI and exception
unwind. Original 116 instructions and 320/320 non-relocation bytes
converged only after a natural short-circuit distance/callback guard;
**388/388 entire original bytes** now strict exact. The expanded
`Bullet.hpp` `<functional>` closure is fully revalidated: **51/51 prior
exact units + 1 new, 52/52 strict units over 15 fresh cold objects**,
no full-graph replay. MSVC-private `$SG` numbering changed but native
data relocations did not. See
[complete filtered cancel evidence](BULLET_FILTERED_CANCELLATION_EXACT_RECONSTRUCTION.md).
Current authored-exact ledger totals: **247 functions / 63,542 bytes**.
The true 662B Bullet::cancel, 3,735B Bullet emit and 41,967B Enemy root
remain nonexact. Earlier CORE/AUDIT-230 662B frontier remains valid.


CORE/AUDIT-230 (web) independently re-attests the **entire nonexact
662-byte** original `Bullet::cancel` at `0x0047C8F0`: 199 native x86
instructions, 25 direct calls to 21 distinct addresses, full animation
handle/spawn/effects/drops/positional sound/Vector3 motion/Timer/manager
view protocol. Twelve full C++20 native probes compiled to 640..680B;
**a candidate with exactly 662B length still matches just 245/526
non-relocation bytes** due wrong local/result ABI and register allocation.
No source or exact-credit change. See
[complete Bullet cancel frontier](BULLET_CANCEL_662_NATIVE_FRONTIER.md).
The 3,735-byte Bullet single-shot emitter and 41,967-byte Enemy opcode
root also remain nonexact. Documentation-only scope: **zero affected units**,
no canonical or whole-graph replay. Exact totals remain **246 / 63,154B**.


CORE/EXACT-229 (web) admits complete original **401-byte** capped
`BulletController::cancel_near_limited` at `0x0047CF60`, all **16 native
relocations**, full SEH/iterator lifetime and bounded early return. The real
Bullet flags **bits 11..12** were recovered as a native 2-bit `effect_mode`
field: naturally assigning this field makes the compiler produce all the
original x86 register/branch shapes; original masked OR did not. Real
active list, exact 122B geometry predicate, signed cap and counter are
maintained. **401/401 strict original bytes**; actual include closure **50
previous exact units + 1 new = 51/51 across 14 cold objects** all exact,
compiler-private `$SG` renamed only, no whole-graph replay.
662B Bullet::cancel, 3,735B Bullet emit and 41,967B Enemy root still
nonexact. See [401B capped cancellation evidence](BULLET_LIMITED_CANCELLATION_EXACT_RECONSTRUCTION.md).
Current authored-exact totals **246 functions / 63,154 bytes**.


CORE/EXACT-228 (web) independently closes **all 122 bytes** of native
Bullet radial distance predicate `0x00485A60`, including original Vector3
construction/subtraction, XY-only squared norm, radius-square SSE comparison,
**full-EAX integer return** (confirmed by the original 320B caller),
and five independently anchored native relocations. The now typed
`src/BulletDistance.hpp/.cpp` is called from real maintained
`BulletSpatialCancellation.cpp`, and both **122/122 and 320/320B** remain
exact in **2/2 scoped strict units across two fresh cold objects**, no
whole-graph cold replay. Real 662B Bullet::cancel and 3,735B Bullet
single-shot emitter, 41,967B Enemy dispatcher still nonexact.
See [exact radial predicate](BULLET_DISTANCE_EXACT_RECONSTRUCTION.md).
Current authored-exact totals **245 functions / 62,753 bytes**.


CORE/EXACT-227 (web) reconstructs the entire original **320-byte
BulletController radial cancellation boss** at `0x0047D100`: real active
intrusive Bullet list, original 95 instructions/14 relocations, native
state 1/2 filter, `size.x / 2.0f + radius` and real geometry check
`0x00485A60`, original 662B `Bullet::cancel` ABI, cancel counter and
return count, all EH/iterator cleanup intact. Native complete 320/320
code exact, with 264/264 identical nonrelocation bytes and independently
anchored native relocations. True Bullet.hpp compiler-receipt include closure
**thirteen freshly built objects, 50/50 strict units** (49 old + 1 new),
including the 832B boundary, 242B cancel-all, 339B fire and four reflections.
Only MSVC-private `$SG` diagnostic names shifted with original relocation
targets unchanged. No full/unfiltered cold replay. See
[exact original spatial cancellation evidence](BULLET_SPATIAL_CANCELLATION_EXACT_RECONSTRUCTION.md).
Current confirmed authored exact: **244 functions / 62,631 bytes**.
The 122B native radius predicate, 662B individual cancel, 3,735B single
Bullet emitter and 41,967B Enemy root remain nonexact.


CORE/EXACT-226 (web) closes full native **242-byte**
`BulletController::cancel_all(int)` at `0x0047CB90` plus actual **19-byte**
`BulletController::active_list()` at `0x00485970`: all **13** original
cancel-all relocations, complete original iterator construction/advance/EH,
real active-list sentinel and state 0/3 exclusions, genuine 662B
`Bullet::cancel(int)` external call ABI, native full **261/261 new bytes**.
The 662B individual cancel remains **nonexact**. New declaration changes to
`src/Bullet.hpp` required **full actual compiler-receipt affected closure**:
**49/49 strict units across twelve freshly built MSVC source objects**, 47
prior plus 2 new, with zero byte regressions; NO whole-graph cold replay.
This **corrects** the CORE225 claim that its 45/45 old subset was exhaustive:
that earlier set missed the already exact 832B `src/BulletBoundary.cpp` boss.
The current 49/49 run *does* include it, plus BulletFire, BulletLifecycle,
all four reflections and 81B draw_groups; only COFF-private `$SG` labels
shifted while original data addresses and relocation sites stayed fixed.
See [exact cancellation and corrected full closure](BULLET_CANCELLATION_EXACT_RECONSTRUCTION.md).
Current authored exact: **243 functions / 62,311 bytes**. Original
3,735B Bullet emitter, 662B individual cancel and 41,967B Enemy root
remain source/COFF nonexact.


CORE/EXACT-225 (web) admits the full **81-byte** original
`BulletController::draw_groups` at `0x0047DC90` with all three original
relocations. The typed Controller selects native Renderer layer 12 with live
`view_index` and iterates **all six draw groups** through the real original
273-byte single-group method. Independent complete code and callee call sites
strict replay **81/81 bytes**, not a partial/one-arm match. A shared narrow
`AnimationRuntimeOwner.hpp` replaces the previous isolated Animation pool
class declaration in `BulletLifecycle.cpp`; its complete 291B retirement
remains byte exact. All **nine previously exact Bullet.hpp-dependent source
objects, 45 existing units**, were freshly compiled and all **45/45 strict
replayed**, including BulletFire and BulletReflection; only compiler-private
local `$SG` labels shifted with original data destinations unchanged.
**New plus old: 46/46 strict units, ten fresh MSVC objects**, no full cold
replay. The native 273B single-group Bullet drawer and 806B Renderer selector
remain nonexact, as do the 3,735B single-shot Bullet emitter and 41,967B
Enemy opcode boss. The 211B Bullet step source probe compiled to 212B,
**not accepted**, see [draw-group exact evidence](BULLET_DRAW_GROUPS_EXACT_RECONSTRUCTION.md).
Current confirmed authored exact ledger: **241 functions / 62,050 bytes**.


CORE/EXACT-220 (web) closes the **entire original 832-byte Bullet
four-way boundary boss** `0x00482A60` (235 original x86 instructions,
**31 native relocations**, whole 832/832 canonical bytes). Natural
single-source short-circuit OR of the two actual rectangle paths fixes
previous 846/848/865B compiler control-flow differences. The complete
original 176-byte `bullet_outside_rectangle` at `0x00485420` is also
separately **176/176 strict exact** with seven relocations and is now the
actual direct callee at both native boss call sites. All four directional
Bounce methods remain exact. Original speed threshold is **-990f**, the
native flag-clear is lower 32-bit bit 6 of real 64-bit Bullet command flags.
Unlike previous scoped checkpoints, the full **nine** existing Bullet.hpp
include-dependent objects/**45** previous strict units (including BulletFire,
BulletLifecycle and BulletReflection) were **all** freshly compiled and
replayed exact after only COFF-private `$SG` name renumbering. Full new plus
old scope: **47/47 strict units across eleven cold objects**; NO unfiltered
cold replay. Original 3,735B Bullet single-shot emitter and 41,967B
Enemy root remain nonexact. See [full 832B boss evidence](BULLET_BOUNDARY_BOSS_EXACT_RECONSTRUCTION.md).
Current authored-exact ledger: **240 functions / 61,969 bytes**.


CORE/EXACT-219 (web) admits the entire original 176B native Bullet
rectangle boundary test at `0x00485420` (42 x86 instructions,
**176/176 full canonical bytes**, seven independent native relocations).
The original two direct call sites are `0x00482AF6` and `0x00482B98`
inside the still-nonexact **832B** native Bullet four-direction dispatcher.
The real 224f vertical origin is independently fixed at `0x0056ED14`,
with original 2f object and SSE sign mask. An ordinary C++ integer local and
negated four-condition test reproduce the complete native function;
shorter 163B and other nonmatching trials were rejected. New isolated
`src/BulletRectangle.hpp/.cpp` do **not** change any old source/header
closure: **one affected unit, one cold MSVC object, 1/1 strict exact**;
no whole-graph replay. All four separately original Bullet reflection
callees (1,206 distinct bytes) were already complete, but 832B caller,
3,735B Bullet emitter and 41,967B Enemy boss are still nonexact.
See [field rectangle original evidence](BULLET_RECTANGLE_EXACT_RECONSTRUCTION.md).
Current authored-exact totals: **239 functions / 61,137 bytes**.


CORE/EXACT-218 (web) admits complete **277/277 byte** original
`Bullet::reflect_at_upper_y` at `0x00483150`, all 13 native relocations,
using the real Bullet/Context and `448.0f / 2.0f` upper-Y native SSE
comparison (including unordered/NaN behavior) and Angle/position reflection.
This closes all **four independent horizontal/vertical bounce methods**
used by the still nonexact **832B** root `0x00482A60`. The existing five
same-object units still replay byte-exact. All 35 other affected units in six
`Bullet.hpp`-dependent old objects freshly compile and exact replay:
**36/36 new plus old affected units, seven cold objects**, no whole-graph
replay. Only compiler-private Dialogue `$SG` local symbol numbers changed;
relocation targets are unchanged. See
[upper-bounce exact evidence](BULLET_UPPER_REFLECTION_EXACT_RECONSTRUCTION.md).
Current authored-exact ledger: **238 functions / 60,961 bytes**. The 832B
Bullet boundary boss, 3,735B Bullet spawn and 41,967B Enemy root are still
**source/COFF nonexact**, not partial exact.


CORE/EXACT-216 (web) admits **two full original Bullet horizontal bounce
methods**: `Bullet::reflect_at_right_x` at `0x00483010` (**319/319B**,
14 relocations) and `Bullet::reflect_at_left_x` at `0x00482EC0`
(**329/329B**, 16 relocations), totaling **648** independently anchored
native bytes. Real typed Context/Controller/command slots, signed boundary
mirroring, actual Angle double-assignment and native SSE sign/pi/2 objects
were all reconciled from original complete control flow. They share the
existing `src/BulletReflection.cpp` owner; its old three units remain exact.
`Bullet.hpp` affects six other objects/35 accepted units: **35/35 fresh
cold-compilation strict replays** pass after COFF-private `$SG` label
renumbering only. **37/37 current-batch strict units / seven cold objects**,
no whole-graph replay. Original 832-byte bounce caller `0x00482A60`
was independently decompiled and a full private C++ probe compiled; it is
still **nonexact** (832B native versus 846/848B probes) and receives
no partial or false exact credit. The original 3,735B Bullet emitter and
41,967B Enemy opcode dispatcher remain nonexact. See
[horizontal bounce exact evidence](BULLET_HORIZONTAL_REFLECTION_EXACT_RECONSTRUCTION.md).
Current authored exact totals: **237 functions / 60,684 bytes**.


CORE/EXACT-214 (web): **fully exact 281-byte Bullet vertical reflection**
`0x00482DA0`, plus complete native 22-byte
`BulletExtendedCommands::at` `0x0047C680` and 17-byte
`BulletController::vector_4c_ref` `0x00485990`. All 13 original relocations
in the 281B function are independently anchored; SSE NaN branch and
`448.0f / 2.0f`, command index 4, Angle sign inversion and vertical
position reflection are preserved. **320/320 new native bytes**, 35/35
shared-Bullet.hpp existing units freshly cold-recompiled and strict replayed:
**38/38 units / seven objects**, no unfiltered cold replay. Local MSVC
`$SG` symbol labels renumbered; original data destinations did not change.
Full original 832B caller at `0x00482A60`, 3,735B single-bullet emit at
`0x004818E0`, and 41,967B Enemy opcode dispatcher **remain nonexact**.
See [Bullet reflection evidence](BULLET_REFLECTION_EXACT_RECONSTRUCTION.md).
Current authored exact ledger totals: **235 functions / 60,036 bytes**.


CORE/REVIEW-212 (web) independently corrected a **real source semantic error**:
native list method `0x0044A6B0` prepends to the sentinel, not appends.
`Bullet::deactivate` now invokes `free_list().prepend(&link)` with the correct
symbol at the same native relocation destination. Its complete **291/291B**
strict replay and the other two unchanged source units all pass (3/3, one
cold object). The 66B prepend callee itself is **not exact** (53/58
nonrelocation bytes) and receives no credit. The original 338B
AnimationFile script-begin method `0x004383A0` now has a private natural
compiler probe that structurally matches **306/306 nonrelocation bytes**,
but its global Renderer/Animation owner +0xB8 layout remains unproven:
**do not admit it as an exact unit or copy the private placeholder prefix**.
The original 73B Animation allocator at `0x00447800` contains explicit
zero-construction absent in the prior 60B template trial. Complete emitter
`0x004818E0` remains **3,735B and nonexact**. See
[focused original-callee audit](BULLET_EMIT_FRONTIER_AUDIT.md).
This correction affects only `src/BulletLifecycle.cpp` (3 strict units,
one cold object); **no whole-graph cold replay**. Current exact totals
remain **232 functions / 59,716 bytes**.


CORE/EXACT-211 (web) closes **all 291 original bytes** of real
`Bullet::deactivate` `0x0047DA40`, its **13 native relocations**,
`Bullet::select_context` `0x00486570` (**54/54 B, two relocations**),
and `BulletController::free_list` `0x00485900` (**19/19 B**). The deactivation
uses real active-link detach, live Context free-list return, five native Timer
resets, four preserved flag clears, AnimationHandle retirement and **real
shared_ptr metadata reset**. Complete 3,735B Bullet single-shot emitter
`0x004818E0` separately audited at 935 original instructions/60 calls but
**not exact**, nor is 41,967B Enemy root. Six shared-header objects/35 old
units fully revalidated after `$SG`-only compiler renumbering; **38/38
scoped exact units, seven cold objects, no whole-graph replay**. See
[complete lifecycle evidence](BULLET_LIFECYCLE_EMISSION_EXACT_RECONSTRUCTION.md).
Current maintained authored-exact totals: **232 functions / 59,716 bytes**.


CORE/EXACT-210 (web) admits **the full original 339-byte**
`BulletController::fire` at `0x00481780`: 103 original instructions,
11 independently anchored canonical relocations, natural C++20 signed nested
shot loops with by-value metadata ownership and early-stop/sound paths.
**339/339 original bytes exact** after canonical replay. Freshly recompiled
all **35 old Bullet.hpp-dependent units**, which remain exact after only
compiler-private `$SG` symbol labels shifted; total **36/36 exact across
seven affected cold objects** and no whole-graph replay.
The real **3,735B** `BulletController::emit` at `0x004818E0` and the
**41,967B** Enemy opcode boss at `0x0048C010` remain nonexact. Focused
[evidence](BULLET_FIRE_EXACT_RECONSTRUCTION.md). Current admitted authored
exact totals: **229 functions / 59,352 bytes**.


CORE/EXACT-209 (web) admits complete native `Player::position_ref` at
`0x00460850` (19B) and `Player::direction_to` at `0x004FF350` (157B).
The locked original PE and Ghidra agree on the XY/zero/pi/two/atan2 flow.
Two new exact units and **all 30 previously exact include-affected units**
were freshly rebuilt and strict-compared: 32/32 exact, six MSVC objects.
One compiler-generated Player diagnostic `$SG` label shifted, with original
relocation target unchanged. The original 339B Bullet firing caller and
41,967B Enemy root remain nonexact. See
[Player direction evidence](PLAYER_DIRECTION_EXACT_RECONSTRUCTION.md).
Affected-only validation; no full cold replay. Current admitted totals:
**228 authored exact functions / 59,013 bytes** (including this checkpoint).


CORE208 integrates the **entire native 252-byte / 62-instruction / 10-call**
opcode 632 at `0x00493831..0x0049392C` into the same full 41,967B
Enemy source draft. Unlike numeric-command cases 609–612, 632 reads ECL
integer index 0 then 1, runs the **real byte-exact 396B writable COW
selector**, grows the real `std::pmr::vector<BulletCommand>` if needed,
then stores the raw **borrowed `EclInstruction+0x1C` pointer** into
`BulletCommand::script` at +0x28. The pointer is not a string copy or a
VM argument read. New **324** scenarios (304 normal / 80 COW copies / 144
new metadata owners / 112 PMR resizes / 12 ECL failures / eight
632→609→632 pointer-preservation chains) bring both 86-TU GCC13
O2 UBSan and ASan+UBSan complete-root hosts to **44,554/44,554**.
The current four SHA-bound private inputs, original call-site audit,
both protected binaries and successful logs are in
`.analysis/core208-native-632-audit.json` and
`.analysis/core208-enemy-whole-root-proof.json`; explanation:
[whole original 632 script-pointer branch](ENEMY_WHOLE_ROOT_OPCODE_632_SCRIPT_POINTER.md).
CORE208 changed **zero maintained native compiler inputs**, so native
cold replay affected scope is **zero**. Original full 41,967B root
remains nonexact; conservative authored exact credit remains
**226 functions / 58,837 bytes**.


CORE207 adds the entire original **572-byte** Enemy opcode 614 branch at
`0x004925C7..0x00492802`, **129 actual x86 instructions and 19 native direct
calls**, to the **same complete 41,967-byte root**. The source reads ECL
integer index 0 (destination) then index 1 (source) before any mutation,
ensures the real PMR forward-list length first for destination then source,
and invokes native exact **119-byte `EnemyQueuedRecord::operator=`** for
`queued[destination]=queued[source]` — not swap/COW or flattened memcpy.
The **308** new whole-root cases include 288 real 76-byte record assignments,
56 self copies, ordered queue growths, 32 owner aliases, 64 replaced-owner
releases, 12 early ECL errors, and eight original 614→602→700 shared-owner
copy/COW chains. Both complete **86-source** GCC13 O2/UBSan and O2/ASan+UBSan
hosts pass **44,230/44,230** cases, including all 43,922 predecessors.
The independent original native case/call SHA audit, current source/recipe
SHA hashes and both passing host binaries/logs are protected in
`.analysis/core207-native-614-audit.json` and
`.analysis/core207-enemy-whole-root-proof.json`. See
[whole original 614 integration](ENEMY_WHOLE_ROOT_614_QUEUE_COPY.md).
CORE207 modifies **zero maintained production compiler inputs**, so native
cold replay scope is **zero**; the previous CORE206 whole exact 119B method
and its 113/113 original strict native unit replays remain accepted.
Current authored native exactness remains **226 functions / 58,837 bytes**.
The entire original 41,967B Enemy root still lacks native codegen exactness;
continue with other large missing heads (621/632) and original EH/switch.


CORE205 adds **three independently decoded complete original native
Enemy queued parameter heads** to the same single 41,967-byte source
draft: opcode **602** (181B/43 x86 instructions/8 calls), **603**
(189B/43/8) and **604** (213B/51/10). Each executes the previously
byte-exact **305B ensure-only `EnemyState::shared_shot`**, preserving
already shared metadata without writable COW. 602 stores two raw
integer type/color fields; 603 stores two raw `vector_34.x/y` floats
while preserving Z; 604 individually normalizes and stores `angle` and
`angle_step` through the genuine angle callee. **483 new whole-root
scenarios** cover 152 variants per opcode, **120** genuine surviving
shared aliases, **216** new owners, **96** real PMR forward-list growths,
and **27** ECL read exceptions preserving exact earlier stores.
All **43,922 / 43,922** complete **85-TU GCC13 O2/UBSan and
O2/ASan+UBSan** scenarios pass, including all 43,439 predecessors.
The complete independent native original intervals/call list, four active
private source/recipe hashes, both host binaries and logs are pinned at
`.analysis/core205-native-602-604-audit.json` and
`.analysis/core205-enemy-whole-root-proof.json`. See
[whole-root 602/603/604 integration](ENEMY_WHOLE_ROOT_602_604_QUEUED_PARAMETERS.md).
No maintained production input was modified in CORE205, so **zero new
native cold-build/replay units** and no full cold replay. The original
**41,967-byte Enemy root is still machine-code nonexact**; 572-byte
opcode 614 and the original 339-byte Bullet emitter remain open.


CORE204 integrates **the entire original 593-byte native opcode 601
primary head** at `0x00492803..0x00492A53` into the same complete
41,967-byte Enemy source-draft root. Original Capstone/locked PE and case
catalog independently confirm **136 original instructions / 16 direct
calls**, including `EnemyState::shared_shot` (exact 305B),
`BulletController::set_scalar_48(float)` (exact 26B, called **twice**),
the actual 0.9f position threshold, and original **339-byte** still-open
BulletController firing/metadata lifetime boundary at `0x00481780`.
This opcode uniquely uses **ensure-only, never COW** for shared metadata.
Its first field_48 setter runs before firing; the last setter resets
**the fresh, live Context owner** only on normal return, while a firing
exception leaves the preceding scalar value intact. The new **314**
scenarios test **266 real successful original shared record/position
paths**, **126** first-time owners, **70** unchanged shared aliases,
**56** actual queue expansions, **60** strict-relative vs **206** absolute
and NaN paths, **133** late Context retargets, **42** downstream throwing
producer cases with *no reset*, and six early VM operand errors.
Both full **85-TU** GCC13 O2/UBSan and ASan+UBSan fixtures pass all
**43,439/43,439** cases, retaining the preceding 43,125. Only unrelated
unlinked fixture vptr checks are disabled in the ASan run; leaks are on.
Protected active evidence: `.analysis/core204-enemy-dispatch-candidate.cpp`,
`.analysis/core204-dispatch-host.cpp`,
`.analysis/core204-op601-host-cases.inc`,
`.analysis/core204-dispatch-host-recipe.json`,
`.analysis/core204-dispatch-host.log`,
`.analysis/core204-dispatch-host-asan.log`,
`.analysis/core204-native-601-audit.json` and
`.analysis/core204-enemy-whole-root-proof.json` (four current source hashes,
two binary hashes and both original successful log hashes). Protect
`build/core204-dispatch-host*` and all older proof-bound objects.
Complete explanation:
[whole original opcode 601 Bullet caller](ENEMY_WHOLE_ROOT_OPCODE_601_BULLET_FIRE.md).
CORE204 changes **zero maintained production compiler inputs**. No extra
native cold-build/replay units, and no full cold replay, were needed after
CORE/EXACT-203's already passed 35/35 affected units. The full 41,967-byte
Enemy root and the 339B Bullet producer remain machine-code nonexact.


CORE/EXACT-203 independently recovered the entire native
**26-byte** `BulletController::set_scalar_48(float)` at `0x0049C740`.
Its `__thiscall` receiver writes the original `BulletController+0x48`
float field, with **26/26 original x86 bytes exact and zero relocations**.
The original large Enemy opcode 601 branch at
`0x00492803..0x00492A53` calls it twice (set Enemy's `field_274`, then
reset zero), while additionally calling the still-unaccepted 339-byte
BulletController shot creation function `0x00481780`. The genuine owner
is added to `src/BulletController.cpp` and real `src/Bullet.hpp`.
Canonical 11-function TU `build/core185-canonical/BulletController.obj`
was **replaced** by the 12-function
`build/core203-canonical/BulletController.obj`, preserving physical object
count. The header's real include closure is **six source providers / 35
complete native units**, all **35/35** passed after affected-only cold
compiles. Only five native-target-verified MSVC private `$SG` string names
changed in two existing constructor units. No old code-body or target
relocation differences remained. The private proof and scoped run log are
`.analysis/core203-bullet-scalar-exact-proof.json` and
`.analysis/core203-affected-replay.log`; detailed account:
[exact Bullet scalar dependency](ENEMY_BULLET_SCALAR_601_DEPENDENCY.md).
The still-current single Enemy root host is CORE202, with **43,125/43,125**
UBSan and ASan+UBSan scenarios. No whole-native cold replay was performed;
original 593B opcode 601/339B firing callee and the full 41,967B root
remain nonexact. Current authored exact credit increases only **26 bytes**.


CORE202 integrates the **entire original native opcode 600 primary branch**
(`0x00492434..0x004925C6`: **403 bytes / 90 instructions / ten direct
calls**) into the **same single 41,967-byte Enemy root source draft**.
It calls the real native-byte-exact `EnemyState::writable_shot` COW selector
before reconstructing the true 40B `ShotParameters` default, resetting the
actual `EtamaArgInf` through default construction and **PMR-aware move
assignment**, and writing precisely the original record offsets
`+0x34/+0x38/+0x40/+0x44/+0x48/+0x30`. The native
`record.vector_34.z` at `+0x3C` remains **bitwise preserved** (not a
blanket record memset), and default metadata `sound=21` and
`alternate_sound=38` with two default commands are retained.
**152 new whole-host scenarios** cover 114 typed/PMR reset matrices,
30 real shared-owner COW clones, 24 list extensions, 14 early/late
exceptions and 24 opcode 700/701 → reset → 701 state transitions.
Both 85-TU GCC13 full-host sanitizer configurations pass **43,125/43,125**
O2/UBSan and ASan+UBSan scenarios (leaks checked, only unrelated
`WeaponStoneInfo` vptr disabled). Source, original native calls and test
products are SHA-protected in `.analysis/core202-enemy-whole-root-proof.json`
with `.analysis/core202-native-600-audit.json`. Full findings:
[CORE202 original opcode 600 whole-root reset](ENEMY_WHOLE_ROOT_OPCODE_600_RESET.md).
Only *private semantic host inputs* changed, so **no new native cold
replays** were needed; authored exact remains **224 functions / 58,692
bytes**. The complete 41,967-byte original Enemy root is still nonexact.


CORE201 now links **the actual source/COFF-exact production methods**
`EnemyState::writable_shot` (`0x00498B80`, 396B, 22 original relocation
anchors) and `EnemyState::shared_shot` (`0x00498D10`, 305B, 16 anchors)
into the *same entire 41,967-byte Enemy opcode root host*, rather than
using its earlier duplicated private COW implementation. The 85-TU GCC13
host directly invokes both real methods and retains only an explicit
historical injected-failure adapter. **230 new tests** cover 152 direct
actual native owner selections (missing/unique/shared, PMR list growth,
deep copy, ensure-only no clone, raw pair identity), **60 full opcode
calls** across 609–612, 700–703 and 711/713, plus **18 downstream VM
exceptions** with previously committed COW ownership preserved. All prior
**42,743** scenarios also pass: **42,973/42,973** in both O2/UBSan and
ASan+UBSan (only unrelated unlinked WeaponStoneInfo vptr disabled; leaks
checked). Active source and binary/log hashes and the complete test fixture
are in `.analysis/core201-enemy-whole-root-proof.json` and
[CORE201 full-root real selector integration](ENEMY_WHOLE_ROOT_EXACT_QUEUED_SELECTOR_INTEGRATION.md).
**CORE201 changes no production compiler graph input**, hence **zero
additional native cold replays** since CORE200's already accepted
**112/112** affected unit strict results. Authored exact totals stay
**224 functions / 58,692 bytes**, and the original entire 41,967B native
root remains compiler-byte nonexact.


CORE/EXACT-200 reconstructs **both complete original native queued
metadata selectors** on the real game-owned `EnemyState`:
`writable_shot` at `0x00498B80` (396/396 bytes and 22 independently
original-PE-verified relocations) and `shared_shot` at `0x00498D10`
(305/305 bytes, 16 native relocations). Both return the authentic pair of
**raw pointers** to the indexed `EnemyQueuedRecord` and its owned
`EtamaArgInf`, using actual `std::pmr::forward_list`, `std::shared_ptr`,
`DebugAllocator`, real COW cloning and ensure-only reuse, rather than
fabricated selectors. The earlier wrong codegen assumption about a
conditional local allocator was experimentally corrected with a real
function-scope C++ object. The production source
`src/EnemyQueuedSelection.cpp` and declarations `src/EnemyState.hpp`
strictly emit all original 701 native instruction bytes. Actual compiler
receipts gave **19 preexisting provider TUs / 110 old strict units** plus
the one new TU / 2 new exact units. Only those **20 source objects** were
cold-built, and **all 112/112 complete affected native units** passed,
including every original relocation and complete MSVC source/object receipt.
Six old internal `$SG` debug-string symbol renumberings were checked against
original PE literal content, offsets and independently fixed target values.
See [CORE200 full 701-byte selector acceptance](ENEMY_QUEUED_SELECTORS_EXACT_RECONSTRUCTION.md)
and `.analysis/core200-selectors-full-proof.json`.

**Important provenance correction:** A copied private verification script
mistakenly overwrote the ignored historical CORE195 223-unit proof JSON.
CORE195's original code and full original unit scope were independently
re-attested as **223/223 native-exact**. The exact old JSON SHA could not
be regenerated because pinned MSVC emits variable COFF timestamps.
The original SHA and newly generated proof SHA are retained with the
transparent recovery record in `.analysis/core200-historical-proof-recovery.json`;
no claim that historical file bytes are unchanged is made. All production
source and native bytes remain verifiable. No full cold replay was run.

The **41,967-byte Enemy dispatcher is still nonexact**; the previously
protected CORE199 whole-root host remains a dated 42,743-case checkpoint.
CORE201 now executes the actual accepted COW and ensure-only production
methods, so do not use the historical CORE199 note about private selectors
as the current implementation. Further native heads, compiler EH/switch
layout and whole-image runtime remain open.


CORE199 adds the **entire original native opcode 711 and 713 Laser branches**
to the same full 41,967B Enemy source-draft root, not an isolated fake
opcode function. Original 711 is **619 bytes / 141 native instructions / 15
calls** with genuine `LaserType2Parameters` and factory type 2; 713 is
**611 bytes / 137 instructions / 16 calls** with `LaserType3Parameters`
and factory type 3. Independent locked-PE branch/call audits confirm real
`ShotMetadata` COW selection, typed PMR `BulletCommand` deep copies,
strict 0.9f position thresholds, the different parameter offsets and
713's late `integer_argument(1)` retarget window. **319** new scenarios
cover 144 type2 and 144 type3 calls, 288 real PMR copies, 96 COW clones,
48 late Context redirects, 15 staged exceptions and **16 calls through the
actual separately native-exact 474B LaserController creator**, eight of
which complete the real 75B intrusive-list registration. Both full 84-TU
O2/UBSan and ASan+UBSan hosts pass **42,743/42,743** cases with leak
detection enabled (only unrelated unlinked `WeaponStoneInfo` vptr check
excluded). Active source/binary/log hashes and complete original call sites
are in `.analysis/core199-enemy-whole-root-proof.json` and
`.analysis/core199-native-711-713-audit.json`.
Full evidence: [711/713 typed Laser branch integration](ENEMY_WHOLE_ROOT_711_713_LASER_TYPED_CREATION.md).
CORE199 changed **zero maintained native compiler graph inputs**, so
**no additional canonical cold builds or full cold replay** were run. Native
exact totals remain **222 functions / 57,991 bytes**. The original 41,967B
Enemy boss, concrete Laser allocators, COW selector and EH/switch layout
remain machine-code nonexact.


CORE198 **whole Enemy queued-parameter** integration has now
added two original primary heads **opcode 700 (269B/59 native instructions/10
calls)** and **701 (289B/67 instructions/11 calls)**, independently verified
from the locked PE and case-path catalogue. Both use the real 396B queued
record/metadata two-pointer COW selector semantics; 700 writes four floats
across the selected record's true ShotParameters position and metadata
`field_14`, and 701 writes five integer words to metadata `+0x24..+0x34`.
Original read order, full state images, COW isolation and earlier partial
writes on exceptions are checked. **337 added scenarios** include 80 actual
shared-owner COW copies, 144 first-time owner creation, 64 list growth cases
and 33 staged exceptions. All previous 42,087 cases remain passing, so the
active **84-TU entire-root** host passes **42,424/42,424** under both GCC13
O2/UBSan and O2/ASan+UBSan (only unrelated vptr unavailable, leaks on).
This new private draft is `.analysis/core198-enemy-dispatch-candidate.cpp`,
with `.analysis/core198-queued-parameters-host-cases.inc`, full logs and
SHA-bound `.analysis/core198-enemy-whole-root-proof.json`. Independent native
originals are `.analysis/core198-native-700-701-audit.json` and complete
.asm files. [Read opcode 700/701 whole-root evidence](ENEMY_WHOLE_ROOT_700_701_QUEUED_PARAMETERS.md).
It adds **zero native exact credit** and requires **zero new canonical cold
replay units**; the unchanged CORE195 **223/223** affected native strict
unit receipts remain valid. The original 41,967-byte Enemy root stays
nonexact. This CORE198 queued-opcode work and the earlier CORE197 concrete Laser
constructor audit are separate, individually SHA-bound investigations,
not competing reconstruction roots. Keep all CORE197 historical inputs.


CORE197 independently audits the **nine still-open complete native
functions** immediately below CORE195's now-exact Laser creator: four
**92-byte** concrete allocation wrappers (Line/Infinite/Beam/Curve),
their **88/87/159/122-byte** typed derived constructors and the common
**522-byte** Laser base constructor. Original allocated object sizes are
`0x18F8/0x1338/0x1370/0x1D30`. The native call chains establish true
`LaserTypeNParameters` at `+0x6F8`, real `Animation` subobjects,
concrete vtables, and two 0x800-byte Curve arrays (not guesswork padding).
Private typed MSVC probe for the 522B base constructor emitted 538B and
**did not match**: it is not accepted or made artificially exact. Complete
PE byte hashes, call sites and unresolved type layout are in
[concrete Laser allocation native frontier](LASER_CONCRETE_ALLOCATION_NATIVE_AUDIT.md)
and `.analysis/core197-laser-factory-constructor-frontier.json`.
No production inputs changed: **zero further cold replay units**; previous
CORE196 whole-root **42,087/42,087** dual-sanitizer scenarios and
CORE195 **223/223** native strict provider replays remain intact.


CORE196 continues the **one complete 41,967-byte Enemy root** using the
*actual* already accepted native-exact 474-byte `LaserController::create_laser`
from `src/LaserFactory.cpp` and complete 75-byte registration from
`src/LaserRegistration.cpp`. The previous CORE192 host still exists as
protected evidence, but the active private `core196` source/host/recipe
actually executes both production methods, with its four **92-byte concrete
native allocation factories still explicitly captured**. Test-only 34-slot
Laser classes provide correct signed virtual init ABI, without fabricating
native concrete subclasses or accepting their source. **1,146 new semantic
cases**, including **96 actual Enemy opcode-702/703 to production-creator
calls**, cover count limits, handle wrap and floor, all four types, allocation
failure, signed init rejection, real intrusive-list registration, and
exception short-circuiting. The full 84-TU GCC13 host now passes
**42,087 / 42,087** O2/UBSan and O2/ASan+UBSan tests (vptr excluded only
because unrelated `WeaponStoneInfo` RTTI is not linked, leaks enabled).
The five active source/recipe hashes, both binaries and full test logs are
protected in `.analysis/core196-enemy-whole-root-proof.json` with
`.analysis/core196-dispatch-host.log` and
`.analysis/core196-dispatch-host-asan.log`. Full evidence:
[actual byte-exact Laser factory in the entire Enemy root](ENEMY_WHOLE_ROOT_REAL_LASER_CREATOR_INTEGRATION.md).
**No production compiler graph input changed in CORE196**: zero further
native cold-build/replay units. The current total remains **222 authored
exact functions, 57,991 bytes**. The 41,967-byte main Enemy switch,
concrete allocators and derived Laser initialization remain nonexact.


CORE/EXACT-195 reconstructs the **entire 474-byte** original
`LaserController::create_laser` at `0x004D47F0`. Its real 4-entry native
switch table at `0x004D49CC`, original 2-byte `66 90` alignment, four
separate 92-byte allocator call targets, signed count/handle gates, true
vtable `+0x14` integer-returning initializer and previously exact 75-byte
LaserController registration now compile from natural maintained C++20
(`src/LaserFactory.cpp`, corrected `LaserParameters.hpp` and four unresolved
concrete allocator interfaces in `DiagnosticAllocator.hpp`). Canonical unit
`laser_controller_create_laser` strictly matches **474/474 native function
bytes** and **492/492 full compiler-contribution bytes** with **all 21
original native relocations**, *including all four table entries*, under
locked MSVC19.44 x86. The actual header closure selects **33 provider
sources / 223 canonical units**. Only these 33 objects were cold-compiled,
and every one of **223/223 complete prior/new units** strictly replayed
against the real PE with fresh source/object receipts. Independent complete
COFF audit found no other code-byte mismatch; 42 internal compiler `$SG`
source symbol renumbers were reconciled against the **unchanged original
relocation offsets, target addresses, types and literal bytes**, not invented
or waived. Complete evidence:
[474-byte factory and whole switch exact proof](LASER_CONTROLLER_CREATE_WHOLE_EXACT_RECONSTRUCTION.md),
`.analysis/core195-native-laser-creator-audit.json`,
`.analysis/core195-223-strict-attested.json` and
`.analysis/core195-all-42-sg-renames.json`.
**No full cold replay** was run. This adds **474 authored exact bytes** but
*does not accept* the four allocator factory bodies or the **41,967-byte**
Enemy boss root; the last CORE192 40,941-case entire-root private host still
captures this 474B method and must explicitly integrate the real source.


CORE/EXACT-194 reconstructs the **entire genuine native 75-byte**
`LaserController::register_laser(Laser*)` at `0x004C9300` from real
`Laser.link+0x8`, `LaserController.active+0x10` and `count+0x28` fields.
Both native direct calls (`IntrusiveLink::initialize` at `0x0044A670`
and `IntrusiveList::prepend` at `0x0044A6B0`) were independently
established; **75/75 original bytes with two relocations** replay exact
under locked MSVC 19.44 x86. The now independently byte-exact in CORE195 **474-byte**
LaserController creator at `0x004D47F0` calls this method at four verified
sites after allocation/virtual init. The only affected compiler-receipt
closure is **3 production TUs**, **22/22** complete strict units all passed
fresh cold build; other providers were not cold-built. Current source:
`src/LaserRegistration.cpp`, updated real member declaration in
`src/LaserParameters.hpp`, canonical
`build/core194-canonical/LaserRegistration.obj`. Private native bytes,
2 original targets, 4 caller sites, source/object hashes and replay log:
`.analysis/core194-native-laser-registration-audit.json` and
`.analysis/core194-affected-replay.log`; complete evidence at
[real laser registration exact reconstruction](LASER_REGISTRATION_NATIVE_EXACT_RECONSTRUCTION.md).
CORE194 added **one authored exact / 75 bytes**; CORE195 subsequently
accepted the entire separate 474-byte factory. Neither adds native byte
credit for the 41,967-byte Enemy boss. CORE192's 40,941 whole-root
scenarios remain protected; they were compiled before the new nonvirtual
member declaration and do not yet execute the real registration method.


CORE192 added **both complete original large Laser spawn opcode branches**
to the *same existing entire Enemy source-draft root*: native **702** has
682 bytes/153 instructions/15 calls at `0x004944C7..0x00494771`, and
**703** has 787 bytes/176 instructions/16 calls at
`0x00494771..0x00494A84`. Native independent instruction audit confirms
the original **0.9f strict/unordered XY relative-position threshold**,
record+metadata pair via writable queued COW, *actual* PMR
`BulletCommand` copies, type0/type1 distinct layouts, optional
`integer_argument(1)` on 703, angle normalization and late actual
`Context::laser_controller`. The original **474-byte** LaserController
creator at `0x004D47F0` was an explicit nonexact host boundary in CORE192;
CORE195 now accepts its **whole native body** separately, but the old host
still uses the capture until explicitly reintegrated. New **303** complete-root cases
include 96 COW copies, 96 missing-owner creations, 288 real PMR deep
copies, 48 operand-retargeted Contexts and 15 exceptions. Both full 82-TU
O2/UBSan and ASan+UBSan hosts pass **40,941/40,941** scenarios (only vptr
instrumentation excluded for unrelated unlinked RTTI, leaks checked).
Protected current native audits, four input SHA hashes, two host hashes and
full logs: `.analysis/core192-enemy-whole-root-proof.json` and
`.analysis/core192-native-702-703-audit.json`. Full evidence:
[CORE192 Laser 702/703 integration](ENEMY_WHOLE_ROOT_702_703_LASER_CREATION.md).
No maintained native compiler input changed, so **zero canonical cold
replay units** were required; native whole root remains **nonexact**.


CORE191 integrates the **actual accepted 151-byte**
`EnemyController::animation_file` from `src/EnemyResourceSelection.cpp`
into the *single complete-root* Enemy dispatcher host. The prior historical
selector-failure hook remains **private**, but the new 146 real-route cases
(36 direct / 110 full original opcode 555) execute the exact production
selector with native array bounds, separate inner/outer Contexts, live Stage
global, sound-before-VM order and Stage exceptions. The Stage getter remains
a test-only captured unimplemented boundary, not a guessed production body.
All **40,638 / 40,638** scenarios pass in **both GCC13 O2/UBSan and
O2/ASan+UBSan**, with `vptr` excluded solely due unlinked unrelated fixture
RTTI; leak detection enabled. New current proof and logs:
`.analysis/core191-enemy-whole-root-proof.json`,
`.analysis/core191-dispatch-host.log` and
`.analysis/core191-dispatch-host-asan.log`. Details:
[CORE191 exact selector in whole root](ENEMY_WHOLE_ROOT_REAL_FILE_SELECTOR_INTEGRATION.md).
CORE191 changes **no production compiler graph input**, so it requires
**zero additional native cold-build/strict replay units**; CORE190's
68/68 strict native units remain the validated baseline. The original
41,967-byte boss root **is still not machine-code exact**.


CORE/EXACT-190 independently recovered the **entire 151-byte**
`EnemyController::animation_file(int)` at `0x004AAE10`, a genuine complete
callee of the 41,967-byte Enemy Boss dispatcher (including opcode 555).
Index 7 calls the live Stage/Background global `0x005C069C` getter at
`0x004AADF0`, index 0 calls Context/BulletController (with the CORE185 20B
byte-exact getter), index 1 calls Context/EffectInfo, and other indices use
the genuine checked `std::array<AnimationFile*,8>::at` helper `0x004AA130`.
The original Stage owner tag/name is still **inferred** and its 20B getter
remains undefined. Three private natural MSVC probes produced 124, 145 and
finally **151** bytes; the accepted nested source emits **151/151 native
bytes**, with **seven independently established relocation anchors** and
zero differences under the locked compiler. Maintained source:
`src/EnemyResourceSelection.cpp`, `src/StageResource.hpp`, and true eight-slot
`EnemyController.hpp` array storage; canonical object is
`build/core190-canonical/EnemyResourceSelection.obj`. The `EnemyController.hpp`
header change expanded the receipt-derived affected closure to **12 provider
TUs / 68 strict native units** (including new selector); **68/68** complete
old/new units passed fresh cold build and canonical relocation-aware replay.
Six changed internal MSVC `$SG` string labels were reconciled to their same
independently verified target literals, with no shortened comparison or skipped
old unit. Further evidence: [full 151-byte resource selector](ENEMY_RESOURCE_SELECTOR_EXACT_RECONSTRUCTION.md).
**No full cold replay was run.** The 41,967-byte Enemy root remains
**machine-code nonexact**, with the CORE188 **40,492-case** private semantic
host and original proofs protected. Its old host captures the 151B routing
boundary; a later integration should switch to real new selector without
mistaking that host for native x86 codegen exactness.


CORE188 independently checked the original queued-selector return ABI.
The genuine **396-byte** `0x00498B80` writable selector and **305-byte**
`0x00498D10` ensure-only selector both call the separately decoded
**55-byte** `0x00467CC0` result constructor, which writes two raw pointer
words. The complete Enemy 609–612 caller consumes them as
`std::pair<EnemyQueuedRecord*, ShotMetadata*>`, **not** a by-value
`shared_ptr`. New private whole-root candidate and tests correct this prior
simplification and implement actual native COW/ensure-only ownership using
`std::pmr::forward_list`, `std::shared_ptr` and `DebugAllocator`.
**631** additional real-owner scenarios cover 144 deep COW copies, 288
initial allocations, 144 unique-owner reuses, 144 list expansions, 192
command-vector expansions, 19 ensure-only selections and 36 post-selection
operand exceptions. All **40,492 / 40,492** complete-host cases pass in
GCC13 O2/UBSan **and** ASan+UBSan (only vptr disabled because of unrelated
unlinked native RTTI; leak detection enabled). The original native functions
remain **compiler-byte nonexact**, as does the entire 41,967-byte Enemy root.
Proof-bound inputs, native call audit, limitations and next steps:
[CORE188 selector pair/COW](ENEMY_QUEUED_SELECTOR_PAIR_COW_RECONSTRUCTION.md).
CORE188 changes **zero canonical production replay units**, so no full or
partial native cold replay was run for this private semantic refinement.


CORE187 next attacked one **genuine large native case** rather than only
leaf setters: original Enemy opcodes **609/610/611/612 all share the single
1,457-byte, 314-instruction, 29-call primary branch** at
`0x004931DD..0x0049378D` (original SHA-256
`f129e860c6aaf09aa107aca146fc85abc1eb021721d052c6e2f7c2430dabb98b`).
The entire shared branch now runs inside the **same** native-root candidate,
using actual `ShotMetadata`/`BulletCommand` fields and PMR vector growth,
split on the native cursor/index and extended arguments, with cursor written
last. The original **396-byte queued owner selector** at `0x00498B80`
remains explicitly captured: its provisional COW interpretation is not
accepted source. The **888 new host cases** include **864 real selected
metadata accesses, 216 real PMR vector expansions and 22 expected exceptions**
(12 preserving partial writes). All **38,973** prior tests passed in both
GCC13 O2/UBSan and O2/ASan+UBSan (with the vptr/leak caveat above):
**39,861 / 39,861**. New production/compiler graph inputs = **zero**;
no new native cold replay or whole-root codegen exact credit. The active audit,
hashes, full member/write-order evidence and limitations are recorded at
[CORE187 609–612](ENEMY_WHOLE_ROOT_609_612_SHOT_COMMAND_INTEGRATION.md).


CORE/EXACT-185 added native `BulletController::animation_file() const` at
`0x004859B0`: **20/20** byte-exact native code, zero relocations. The actual
Bullet owner at +0x286D8C and distinct `EnemyController::animation_file`
selector at `0x004AAE10` independently establish the getter. The only five
canonical providers including `Bullet.hpp` were cold-built, and **33/33**
affected units strictly replayed. The Bullet TU now uses
`build/core203-canonical/BulletController.obj` as of CORE203, replacing
core185-canonical (which had itself replaced core180-canonical). Canonical object count increased to 165 only in CORE190.

CORE186 then integrated the **whole original 555 branch** into the **same**
41,967-byte Enemy root host. Native code at `0x0048C3F4..0x0048C577`
comprises **388 bytes / 81 instructions and ten direct calls**; an independent
Capstone/locked-PE audit discovered that its File-spawn **layer is 3**, *not*
the `-1` of the otherwise superficially similar Enemy defeat path. The full
candidate calls the real existing SoundInf pan adapter, Motion/Enemy position,
XY distance/direction and four-argument File wrapper; the real Bullet file
getter is executed in the index-0 selection test. The then-unaccepted 151B file dispatcher, Stage owner and seven-argument
VM producer were captured as explicit boundaries in CORE186; CORE190 now
accepts the **complete 151B selector** separately, while Stage/VM remain open. **540 new host scenarios** cover both independent gates,
strict 0.2 squared threshold, alternate Contexts, five routed indices, zero
VM operand reads, full owner images and **18 exception** cases. All prior
38,433 scenarios also pass, for **38,973/38,973** with GCC13 O2/UBSan.
Source/proof and limits: [opcode 555 native and whole-root evidence](ENEMY_OPCODE_555_EFFECT_RECONSTRUCTION.md).
No additional source graph changed in CORE186: **zero further native cold
replay units**, no full cold replay and no fresh root machine-byte credit.


The previously verified exact target is **Enemy opcode 539's real callee**,
`LaserController::reset_all_lasers` at `0x004D2430`. Full native body
**263/263 bytes**, **14/14** independent relocation anchors including EH and
cookie support, locked **MSVC 19.44.35211 x86**. It walks the native intrusive
list at `LaserController+0x10`, resets each `Laser+0x6AC` Timer, clears
`Laser+0x6CC` and makes the true vtable `+0x44` `erase(1,0)` call; it does
**not** skip state==1. Current source is `src/LaserParameters.cpp/.hpp`,
tracked unit is `laser_reset_all_lasers` in `config/match-units.toml`.
**Two affected** production TUs (`LaserParameters.cpp` `/fp:precise`,
`DialogueText.cpp` `/fp:strict`) were cold built and all **21/21** full
old/new units (**4,148 bytes**) replayed; the other **162** object receipts
were reused with verified hashes. The real typed Laser owner tests pass
**601/601** each under GCC/Clang ASan+UBSan. Related Dialogue ownership tests
also pass. Detailed evidence:
[opcode 539 complete callee](ENEMY_OPCODE_539_LASER_RESET_EXACT_RECONSTRUCTION.md).

The complete Enemy *caller* at `0x0049579E..0x004957BB` is 30 native bytes /
7 instructions: read the live state `Context` (`EnemyState+0x2EC`), call
`Context::laser_controller` at `0x0041CA90`, then invoke the exact callee.
**No VM operand reads**. CORE183 added this case to the **same entire root**,
not an isolated faux function. The additional **192** host cases include
**32** caught virtual exceptions, **208** actual erase calls, **64** context
retargets, current/next unlink handling and observer lifetime checks, while
preserving all **38,241** predecessor tests. See
[whole-root 539 integration](ENEMY_WHOLE_ROOT_539_LASER_RESET_INTEGRATION.md).

The most recent **active private** root work is:

- `.analysis/core208-enemy-dispatch-candidate.cpp` — same entire Enemy
  source-draft root with opcode 632 added to all previous families.
- `.analysis/core208-dispatch-host.cpp`,
  `.analysis/core208-op632-script-pointer-host-cases.inc`,
  `.analysis/core208-dispatch-host-recipe.json` — current whole 86-TU host,
  executing the maintained byte-exact writable COW selector.
- `.analysis/core208-dispatch-host.log`,
  `.analysis/core208-dispatch-host-asan.log`,
  `.analysis/core208-native-632-audit.json`,
  `.analysis/core208-enemy-whole-root-proof.json` — 44,554 passed cases,
  four SHA-bound private inputs, exact original 252B call targets and two
  proof-bound `build/core208-dispatch-host*` executables.
- All original CORE207/206 and older protected original PE, MSVC receipt,
  source, whole-root host and acceptance evidence remain intact.

For recent neighboring work see
[548 exact FrontInf](ENEMY_OPCODE_548_STAGE_TITLE_EXACT_RECONSTRUCTION.md),
[548 complete-root integration](ENEMY_WHOLE_ROOT_548_STAGE_TITLE_INTEGRATION.md),
[549 exact membership/551 color ABI](ENEMY_COLOR_CONTAINS_NATIVE_RECONSTRUCTION.md),
[549 whole-root integration](ENEMY_WHOLE_ROOT_549_AND_COLOR_CORRECTION.md),
[551 FogValue route](ENEMY_WHOLE_ROOT_551_FOG_INTEGRATION.md),
[554 BulletController caller](ENEMY_WHOLE_ROOT_554_BULLET_INTEGRATION.md),
[517/518 Screen/message](ENEMY_SCREEN_MESSAGE_517_518_RECONSTRUCTION.md),
[502/503 visibility](ENEMY_VISIBILITY_OPCODE_502_503_RECONSTRUCTION.md)
and the [whole switch layout](CORE_ENEMY_DISPATCH_LAYOUT.md).
Original 539, 555, 609–612, **700, 701, 702, 703, 711 and 713** are integrated in the one active
whole-root candidate (none implies whole-root native exactness). Original 548 was integrated as of CORE181.

## Next high-value research, including large functions

1. **Continue the same 41,967-byte Enemy Boss function**, preserving CORE183,
   CORE185, CORE187, CORE188, CORE191, CORE192, CORE196, CORE198,
   CORE199, CORE200, CORE201 and CORE202 proof-bound inputs, real
   Context owners and all **43,125** current dual-sanitizer tests. The original opcode **555** and larger
   shared **609–612** caller are now integrated. Next independently resolve
   the still-unreconstructed **41,967-byte native root compiler/EH/switch
   partition** and remaining missing primary opcode heads. The separately
   exact 396-byte COW and 305-byte ensure-only selectors now **both run in
   the real production-based CORE201 whole-root host**. Their exactness does
   not imply that the entire 41KB dispatcher is machine-code exact. The **474-byte native LaserController creator `0x004D47F0`**
   and its 75-byte registration callee are now **both exactly reconstructed**.
   The complete production creator is now **linked into the whole-root
   host**; next independently attack its **four unresolved 92-byte concrete
   Laser allocators / virtual initializer bodies**, with four
   concrete beam factory cases, virtual init and lifetime. The **151-byte**
   `EnemyController::animation_file` remains exact and already integrated;
   also attack the still undefined Stage getter `0x004AADF0` and
   Stage/Background owner `0x005C069C`, other missing primary heads and
   compiler/EH exactness. Nearby additional blockers: Renderer handle lookups for **502/503**, the actual ScreenInf
   factory and message cancellation for **517/518**, and the real Stage/Fog
   owner behind `0x005C069C` for **551**. Do not infer identities from old
   reference files or collapsed helper aliases. The full root's switch
   tables, EH and compiler partition remain unsolved.
2. **Attack other large Boss bodies and their real leaf dependencies**, not
   just short setters. Notable open work includes the ~40,752-byte Animation
   VM, 1,707-byte damage query, full Dialogue frame/message resources,
   Renderer ownership, and whole-game startup/lifetime. Follow
   [source map](SOURCE_MAP.md), [architecture](ARCHITECTURE.md),
   [roadmap](ROADMAP.md) and [evidence index](EVIDENCE_INDEX.md).
3. The **nine presently mapped nonexact whole roots** also deserve closure:
   `FunctionChainController::remove_unlocked` (`0x412400`),
   `create_bomb_controller` (`0x478300`),
   `EnemyState::update_mesh` (`0x4A4190`),
   `EnemyPattern::emit_items` (`0x4A5350`),
   `PlayerFeedback::record_hit` (`0x4FB3A0`),
   `create_hit_controller` (`0x4C20D0`),
   ProgressSaveManager construction (`0x50E5D0`),
   ProgressSaveManager::commit (`0x50F660`) and
   `archive_compress` (`0x539550`). Their unique native findings live in the
   corresponding documents from [EVIDENCE_INDEX](EVIDENCE_INDEX.md).

## Protected data and fast scoped verification

`config/match-units.toml` is the **only** current canonical object inventory,
not a static build-directory list copied from old handoffs. As of CORE195 it
selects **167** actual `build/**/*.obj` files with **167 sibling
`.receipt.json` files**. Their distribution is core141 66, core142 6,
core145 3, core149 1, core151 1, core154 5, core154-v2 1, core156 1,
core158 10, core163 19, core164 8, core166 2, core167 1, core174 2,
core178 9, core180 26, **core182 2, core185 1, core190 1, core194 1
core195 1, core200 1 and core203 1** (the latter replacing core185 1). Old probe objects/receipts may be
retained as historical evidence but are not current acceptance units. Also
preserve the twenty historical unfinished QueryProtocol/sound/Alignment
products documented in
[damage query](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md),
[sound protocol](SOUND_PROTOCOL_RECONSTRUCTION.md) and
[Animation pool](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md).

**For CORE203**, the real `Bullet.hpp` field method and canonical
BulletController TU change affect exactly **six receipt-derived provider
objects / 35 complete native units**; **35/35** strict exact replays
passed. No unfiltered cold replay. **For CORE200**, adding real
`EnemyState::shared_shot` and `writable_shot`
to `src/EnemyState.hpp` affects **19 existing source providers / 110 old
native units**, plus one new source provider / **two complete exact units**.
**112/112** native whole-unit strict receipt replays passed, with only **20
actual affected cold objects**; no unfiltered or full graph replay.
**For CORE195**, the changed `LaserParameters.hpp` virtual signature
and new `DiagnosticAllocator.hpp` concrete factory interfaces affect exactly
**33 receipt-derived canonical providers / 223 units**. Every one of those
33 sources was rebuilt under its own pinned flags and all **223/223** full
native strict unit comparisons passed. No unfiltered cold replay was run.
**For CORE194**, new real `LaserController::register_laser` and
`LaserParameters.hpp` affect **3 provider objects / 22 native units**;
**22/22** strict cold replays pass, other source providers not rebuilt.
**For CORE190**, changes to real `EnemyController.hpp` and new full selector
source affect exactly **12** receipt-derived canonical providers, all **68/68**
complete native strict units passed after **12** serial reduced-priority cold
compiles. **For CORE185**, changed `Bullet.hpp` inputs affected five canonical
providers: **33/33** prior units / **5** cold objects passed. **For CORE186/CORE187/CORE188/CORE191/CORE192/CORE196/CORE198/CORE199/CORE201/CORE202 private entire-root host integrations**, changed
production compiler inputs = **zero**; they rebuilt only separate GCC13
semantic hosts (and CORE187's additional AddressSanitizer variant), not any
native cold replay unit. Do **not** invoke whole-graph cold replay, Ghidra, MSVC or
full CI just for an evidence handoff. Verify `git status`, `git diff --check`,
protected product hashes and links; reuse the CORE185 native canonical
replay and the current CORE205 full-root semantic host receipts. The older CORE192
boundary remains historical; the new CORE196 unhooked caller executes the
actual exact Laser creator, though the concrete native allocation factories
remain explicit fixture boundaries. The CORE190
native-exact selector is linked into this host, but its Stage getter and
actual renderer/VM producer remain separate private boundaries. To resume actual RE, inspect all dirty work (the user owns
all modifications), review the specific native instructions with the attested
Ghidra/PE workflows, select the true affected include closure from compiler
receipts, then cold-build/replay **only those affected units**. Original
compiler/SDK/resource/target files are all ignored and must be preserved.

Useful commands from the repository root:

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/progress.py --check
# Only when a source unit actually changed:
scripts/build.py --unit laser_reset_all_lasers
scripts/repo-python scripts/compare-coff-function.py --unit laser_reset_all_lasers
```

Before changing build products, read [workflow](RE_WORKFLOW.md) and
[oracle definitions](ORACLES.md). Use `scripts/repo-python` for all Python
invocations, serial `nice -n 15` for heavy jobs, never patch the target PE
or Ghidra database bytes, and distinguish **real x86 canonical exactness**
from isolated O2/UBSan scenario counts. Keep source/docs/commit messages in
English (preserving official Japanese target metadata). Commit substantive
progress promptly with the active session's requested commit prefix.

## Cleanup and history lookup

CORE184 retires **eight** unreferenced, regenerable temporary files totaling
**15,391,114 bytes**, including a synthetic 12.5 MB compiler-output stress
log, an intermediate host-only object, the superseded CORE182 probe pair and
two disposable factory test output directories. The exact SHA-256/path/size
inventory and protected-before/after file hashes are stored in the ignored
`.analysis/core184-handoff-cleanup-audit.json`. This cleanup does not alter
maintained source, canonical manifest, original target, exact-credit ledger,
current root inputs, evidence archives or active compiler products.

For historical checkpoint narrative and old retirement inventories, use
`git show f709625:docs/RE_HANDOFF.md` and the focused evidence documents;
those dated paragraphs are intentionally **not** duplicated in this current
handoff. Private legacy original-input archives remain available under
`.analysis/`, and all CORE183/CORE185/CORE187/CORE188/CORE191/CORE192 root candidates/proofs listed above remain intact.
