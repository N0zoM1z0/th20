# CORE/EXACT-268 — whole original 777-byte Player rectangle hit/graze boss

Immutable Japanese TH20 v1.00a Steamless target, whole PE SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The **entire original 777-byte** real Player collision and graze method
at **`0x004F8CE0..0x004F8FE8`** has now been reconstructed as natural
C++20 `Player::collision_rectangle(const Vector3&,const Vector2&,int)`
in `src/PlayerCollisionRectangle.cpp`. All **212 original x86 instructions**,
**777/777 original native bytes**, and **35 original relocation sites**
are strict exact. Original whole-body SHA-256:
`63133b1bb1056760b3124343119e68ab76ab46846d2eeadaf12e501c047236bf`.
No truncated function, padding, copied x86 bytes, fabricated struct offset,
convention misreport or build-specific code path is accepted.

## Real Player ownership and the whole hit/graze gameplay flow

The original `__thiscall` receiver is a full authentic `Player`, with
native `Player::position_ref()` at **`0x00460850`** returning the real
position at Player+`0x614`. The method constructs **two complete 8-byte
`Vector2` objects** for Bullet XY rectangle bounds and **two native
12-byte `Vector3` objects** for the Player's actual position envelope.
Native `Player::focused_mode()` at `0x004FF5E0` selects one of two
**real `PlayerCollisionBounds` fields**:

- Normal bounds `Player+0x209C`, actual `collision_bounds.normal_extent`.
- Focused bounds `Player+0x20A8`, actual `collision_bounds.focus_extent`.

The source uses the real Player position and natural
`Vector3::operator-(const Vector3&)` (`0x00429440`) and
`Vector3::operator+(const Vector3&)` (`0x00429570`), each through its
correct hidden-return object ABI. The original fully unrolled
four-edge comparison determines whether the Bullet XY axis-aligned
rectangle overlaps the Player envelope. An overlapping rectangle
then checks the authentic global `FrontInf*` at **`0x005C06A4`** and its
already exact 44B `has_dialogue()` at `0x00478160`: active dialogue
suppresses collision. When the original `mode != 0`, an otherwise valid
hit is reported with return code **2**; for normal mode the original
checks Player life states **2, 4 and 3** through the real
`Player::state_value` getter at `0x00411700`, then Player's actual
`Timer+0x2050` signed `greater_than(0)` at `0x00461070`. If this is
not already active, the original calls the separate full **336-byte**
Player hit/death callback at `0x004F86F0`. Real hit return is **1**;
ignored/blocked hits return **0**.

The non-overlap path performs a complete **second rectangle comparison**
using the native Bullet graze diameter **48.0f** at `0x0056FB7C`,
divided by real **2.0f** at `0x0056C8D0`, so the corresponding
XY graze margin is 24 world units. Four new boundaries are calculated
in the *existing* native `Vector2 minimum/maximum` objects. If this
expanded Bullet rectangle also misses, the original returns **0**;
otherwise it reports the graze code **2**. This is the real complete
original 0/1/2 result classifier consumed by the separate 2,018B Bullet
collision-processing boss `0x00484A20`, not a simple radial shortcut.

## Whole-body compiler convergence and independently attested relocations

Original PE Ghidra decompilation identified all full function paths;
Capstone independently verified the **entire 777B/212 instruction
range**, ABI register/stack use and original security-cookie epilogue.
A first complete typed C++ hypothesis compiled to **745 bytes / 206
instructions**, matching only **194/212** native instruction mnemonics.
The discrepancy centered on the second graze-border comparison: the
original **first rewrites the same four Vector2 boundary lanes**, then
performs a four-way short-circuit check. The provisional C++ instead
computed each enlarged boundary *inside* its individual `if` test,
causing different SSE evaluation and reducing the body by 32 bytes.
Restoring the genuine two-stage rectangle-update algorithm yielded
**the full original 777 bytes / 212/212 instruction order**, native
**`0x74` stack frame**, and **637/637 non-relocation bytes**. This
change is functional original gameplay semantics, not a compiler-shaping
unused local.

The 35 independently sourced relocation positions include the real
stack cookie and checker, two native Vector2 and two Vector3
constructors, actual `Player::focused_mode`, four authentic Player
position getters, four Vector3 arithmetic callees, eight native
`2.0f` references, four native **48.0f** references, two original
FrontInf global references, its real `has_dialogue` call, three
original Player state getter calls, Timer current-value predicate and
actual Player damage handler. For **each of the 35 original sites**
its target is determined by the *original Capstone-disassembled
semantic operand*, not by a COFF comparison-field solver. The full
native register and data evidence is retained privately at
`.analysis/core268-player-rectangle-original-attested-35-relocs.json`
and `.analysis/core268-player-rectangle-native-anchor-audit.log`.

The existing typed `src/Player.hpp` adds only the authentic external
method interfaces `state_value`, `apply_player_hit` and the new full
`collision_rectangle` body. `state_value` currently aliases the native
17B +0x10 getter also used in other TaskInfo-derived classes and is
**not awarded new independent exact coverage**; the 336B hit handler
remains its own unresolved original full function. There is **no
invented Player owner layout**. Locked compiler profile is MSVC 19.44
x86 `/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`, run with reduced priority. The source is
strictly accepted under `[units.player_collision_rectangle]` and
`.analysis/core268-player-rectangle-full-canonical-replay.log`:
**`player_collision_rectangle: exact (777/777 bytes)`**.

## Actual affected-header-only replay and remaining big roots

The changed true `src/Player.hpp` header impacts just **nine existing
source providers / 35 previous exact units**, as derived from captured
compiler receipt header-include dependencies. All **9/9 sources** were
freshly compiled and all **35/35 original native units strictly exact**,
including existing entire Bullet command3/7 and Bullet firing Player
callers. The compiler renumbered one private `$SG` diagnostic string
symbol in the Player constructor; its original relocation offset, type
and true target **`0x00572BB8`** remained fixed and the complete source
was recompiled and replayed after the safe label update.

Together with this new complete 777B native boss:
**36/36 strict exact units across 10 freshly built objects**.
The actual scoped native replay proof is
`.analysis/core268-player-affected-replay-part-0.log` plus the new
canonical unit log. **No unfiltered whole-repository cold replay** was
performed and the locked target PE is unchanged.

The separate **466-byte** original circular Player collision handler
`0x004F8FF0`, its **336-byte** hit callback at `0x004F86F0`, parent
**2,018-byte** Bullet collision at `0x00484A20`, and other original
**1,404B** command11, **273B** draw, **3,735B** emitter,
**12,140B** command sequencer and **41,967B** Enemy opcode bosses remain
nonexact independently. Whole-game linkage/runtime is not inferred
from this 777B function.
