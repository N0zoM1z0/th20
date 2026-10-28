# CORE/EXACT-283 — exact complete original 2,018-byte Bullet collision and graze boss

Immutable original target: Japanese TH20 v1.00a Steamless PE, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The **whole original** `Bullet::process_collision(int mode)` at
**`0x00484A20..0x00485201`**, long listed as a nonexact gameplay root,
now has a reproducible natural C++20 implementation in
`src/BulletCollision.cpp`. The locked MSVC 19.44 x86 `/Od /Ob0 /GS /Gy
/Zl /arch:SSE2 /fp:precise /sdl /EHsc` build is **strict-exact
2,018/2,018 original bytes**, preserving all **532 x86 instructions**
and all **81 original relocation sites** (**68 REL32 calls and 13 DIR32
original globals/constants**). The original entire code SHA-256 is
`7b565186781d77f6a0120ff031b59a849def7798460ffc5d91278ae873688ee3`.
The original member name/source spelling is inferred; the complete
machine-code body, data ownership, argument passing and native targets
are checked from the immutable PE. No assembler, byte-array copy,
`TH20_MATCH_EXACT` alternate body, fake owner prefix, padding,
truncated basic block or partial-function credit is used.

## Complete native collision and graze gameplay

The function is a true game-owned `Bullet` instance member. It first
writes `AnimationFlags::color_mode` to zero through the independently
exact **45B** `Animation::set_collision_color_mode` at `0x004863C0`
and resets the real `AnimationBase::vector_2c` via the separately exact
**38B** `Animation::set_base_position` at `0x00470AF0`, using the
original zero `Vector3` at `0x0056FC08`.

Original BulletFlags bit 1 gates further hit tests, and nonpositive
`size.x` also short-circuits the entire gameplay path. A real float
assignment to `Timer+0x4D8` uses already exact 33B
`Timer::operator=(float)` at `0x0047C5F0` and native 1.0f at
`0x0056C8CC`. The original 2-by-2 collision decision selects actual
Player geometry by the genuine low BulletFlags bit 6 (scaled extents)
and bit 4 (circular collision):

| Bit 6 | Bit 4 | Real native collision route |
| --- | --- | --- |
| Clear | Clear | Whole exact **777B** `Player::collision_rectangle(position, size, mode)` at `0x004F8CE0` |
| Clear | Set | Whole exact **466B** `Player::collision_circle(position, size.x, mode)` at `0x004F8FF0` |
| Set | Clear | Scale the authentic 8B `Vector2` extents and call whole 777B rectangle classifier |
| Set | Set | Multiply the real X radius by `scale` and call whole 466B circular classifier |

The native Player classifier returns **0** (none), **1** (true hit),
or **2** (graze). The original `converted_graze` local starts at zero
and its original 0-to-2 conditional is preserved rather than optimized
away. Return code 0 increments the real `Timer+0x4C0`; a duration of
60 and the original `field_4d4` state arm a 3-stage graze effect and
reset `Timer+0x4A0`.

A result of 1 while `Bullet+0x18` is clear invokes the **entire original
hit-effect branch**: sets Bullet state at `+0x50` to 3, interrupts
Animation in mode 1 at the genuine `0x004388F0`, validates the real
four-byte `AnimationHandle` through independently exact
`bullet_animation_handle_valid` at `0x00485A10`, and interrupts its
original mode-1 handle. If `cancel_script` is nonnegative, the real
`Context::bullet_controller()->animation_file()` produces an original
`AnimationFile::spawn` hidden-result `AnimationHandle` which resolves
into an actual `Animation*`. Effect mode 1 interrupts this Animation
with the genuine `0x00486370` wrapper (mode 3). The position offset
uses real `Vector3` return-by-value multiplication, original
`default_timer_clock` at `0x005AEFE4` and **10.0f** at
`0x0056E734`, then animates the true position via
`Animation::interpolate_position(30, 6, original_zero_Vector3, offset)`.
Effect mode 2 initializes the real 56B `EffectParameters`, copies the
Bullet's 3D position and packed color, and dispatches the authentic
`Context::effect_info()->spawn_effect(4, parameters, 0)` with the true
hidden-result ABI.

Graze code 2 is not a small leaf path: an active graze reward tier
combines `Timer+0x4A0::every(field_4d0)`, the Player's original
`record_bullet_graze(position, color)` callback, 3-stage decrement,
`PlayerRecord::graze_enabled`, reward increment, a threshold greater
than 22, and real passive-weapon feedback. The original reward RNG
selects **two different 10-way options**: normal indices 0..9 or
7..16 depending on the live player flag, each using the actual
`process_bullet_random` at `0x005BA4A8`. On a special successful
reward it intentionally jumps to the *same* original hit-effect label,
not a duplicated or artificially extracted subfunction.

The ordinary graze fade advances original Timers at `+0x4A0/0x4B0`,
zeros `+0x4C0`, tests the genuine native command flag, and conditionally
calls mode-2 `cancel_animation_handle_mode2` at `0x00486310`.
The original fade opacity is the signed integer expression
`208 - Timer::operator*(2)` using the already strict-exact **23B**
Timer multiplication at `0x0045C2E0`, clamped to **96..255**. Actual
Animation `color_mode=1` and the four native RGBA byte channels are
published through the complete exact 45B and 62B Animation setters.
Two separate real `GameRandom::signed_range(1.0f)` returns construct
an authentic temporary `Vector3` for the frame-to-frame animation
position jitter. A nongraze result tests the real complete **46B**
`Timer::operator!=(0)` at `0x0047C620`, interrupts mode-3
AnimationHandle through `0x00486350` if necessary, resets the Timer,
and falls into the original shared return and security-cookie epilogue.

## Whole-method C++ codegen convergence

The first complete private typed C++20 versions of this 2,018B boss
were not accepted: a plausible 2,014B version aligned **517/532**
native instruction kinds, used an external float for original 10.0f,
accessed a packed Bullet value directly instead of through its genuine
four-byte accessor, tested the player reward flag in the reversed
branch order, and omitted/added temporary calls in the graze path.
After the now exact 777B rectangle, 466B circle, seven Animation/handle
helpers, original 51B/44B handle resolver pair and 23B/46B Timer
methods were independently reconstructed, **entire-function** probes
could be compared against the full 532-instruction native range.

Eight dedicated complete-body variants separated actual differences
in `PlayerRecord` reward lookup, local Bullet color getter handling,
float literal and common return fallthrough. The final natural source:

- Calls true `BulletColor::get()` before the Player graze callback
  and retains the returned integer in a meaningful local;
- Uses **literal `10.0f`** for original native animation motion,
  rather than an unrelated external float definition;
- Calls `player_record(0)->graze_enabled()` directly, preserving the
  real original C++ call result and eliminating a spurious local;
- Places the two RNG reward branches in the native flag order and
  preserves `choice = next() % 10 (+ 7)` as a real gameplay value;
- Lets the nonhit Timer cleanup naturally fall through to the shared
  `return result`, rather than inserting a duplicate long return path.

The resulting **entire C++20 function** compiles to **2,018B with all
532 native instruction kinds in the original order**, the correct
native **0x118 stack frame**, **1,694/1,694 non-relocation bytes** and
**324 original relocated bytes at 81 native sites**. No arbitrary
compiler local, inert instruction or misplaced jump table is used.
The canonical strict replay is
`.analysis/core283-bullet-collision-full-canonical-replay.log`:
**`bullet_process_collision: exact (2018/2018 bytes)`**.

## Independently attested original native relocation and folded-owner caveat

The full executable original 2,018B range was independently decoded as
532 Capstone x86 instructions. For **every one of its 81 relocated
sites**, the true original PE instruction operand determines the
absolute data or direct-call target, *not* the MSVC candidate's
comparison-result solver. All 68 original call displacements are
matched to native call instructions and all 13 original absolute
relocations are checked from real native data operands. The original
4-byte encoded relocated value is then checked against that independent
target. See
`.analysis/core283-original-bullet-collision-81-relocations.json` and
`.analysis/core283-original-bullet-collision-relocation-audit.log`.
The complete manifest anchors are maintained under
`[units.bullet_process_collision]` in `config/match-units.toml`.

At one native call site the original target is `0x0040C300`, a **16B
shared four-byte getter** already represented in the repository as
`Identifier32::get()` (`src/Identifier32.cpp`, exact with original
source-family attribution pending). The new Bullet caller writes the
natural `BulletColor::get()` source declaration because the value comes
from the genuine `BulletColor` member at Bullet+0x88, but the PE
machine-code address alone does not prove that the original source
contained two separately emitted getter bodies. This checkpoint keeps
**the existing unique 16B native function mapping and origin unchanged**:
no second source definition, no duplicate exact unit and **zero new
credit** for this shared/folded getter. Caller ABI and target identity
are exact; original linker folding and source type names remain
independently unresolved. Other unimplemented original external helper
bodies (player graze feedback, complete Player damage and rewards) are
represented only as narrow typed method interfaces, not invented
receiver layouts or complete function claims.

## Strict changed-header closure only, not repository cold replay

Adding only narrow genuine declarations to three existing true owners
(`BulletColor::get` in `Bullet.hpp`, `Player::record_bullet_graze` in
`Player.hpp`, and four PlayerRecord reward interfaces in
`PlayerRecord.hpp`) affects **52 previous source providers / 298
previous exact native units**, derived from **actual previous MSVC
header include receipts**. Every one of the 52 source objects was
recompiled under its locked profile, and all **298/298 older whole
native units strictly replayed** without altered original executable
bytes or native targets. The compiler renumbered some *private* `$SG`
diagnostic string symbols; these were changed in the manifest only
with independently unchanged relocation offset, type, and original
native destination, and each affected source was fully rebuilt and
replayed. No external ABI symbol, original target or byte match was
waived. Focused source logs:
`.analysis/core283-bullet-collision-affected-replay-part-{0..4}.log`,
with private identical-target renumbering audit at
`.analysis/core283-bullet-collision-sg-corrections.jsonl`.

With one newly accepted **complete 2,018B boss**, the scoped batch is
**299/299 old/new strict native units across 53 freshly compiled
source objects**. **No unfiltered whole-repository cold replay** was
run. The Japanese v1.00a Steamless target hash remained locked.

The 1,404B command-11, 273B single-group draw, 3,735B single-shot
emitter, 12,140B Bullet command sequencer and 41,967B Enemy opcode
root remain independently nonexact. Passing this collision unit does
not imply complete linkage or runtime equivalence of the entire game.
