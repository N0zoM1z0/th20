# CORE/EXACT-242 — whole native Bullet command-1/10 velocity bosses and XY magnitude

Immutable original Japanese TH20 v1.00a Steamless PE, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint independently reconstructs **three entire original x86
functions**, with game-specific naturally typed C++20 source, full exact
native function extents, and all original call/data relocations:

| Complete original native function | Entry | Size | Relocations | Exact replay |
| --- | --- | ---: | ---: | ---: |
| `Bullet::advance_command1` | `0x00483F00` | 471 B | 20 | 471/471 |
| `Bullet::advance_command10` | `0x00483D20` | 473 B | 20 | 473/473 |
| `bullet_velocity_magnitude` | `0x0047A2A0` | 25 B | 2 | 25/25 |

Original whole-body SHA-256, in that order:
`ad36abcfa8c83922d1c075492047c230f099e86c54d56d54d34dde5734980916`,
`a591cd9f5584c51be90918555c53ef7e76171b62825efc27eb6682f6fa816c63`,
and `a7b2a7576d6ccd093167aa8c78dc507b4d4aa47a7f2ff00c89af8065728d7f77`.
Original C++ spellings remain inferred; native ownership, call/return ABIs,
exact original bit/field layout, entire x86 body and relocation destinations
are independently attested.

The two distinct whole gameplay methods share a real typed protocol but are
**not** one function split into fragments. Their original `ExtendedCommand`
slot indices are **1** and **10**, respectively, with the same actual
64-byte stride. Each compares the slot's native Timer against its
`word_30` duration via exact `Timer::at_least()` at `0x004235C0`. On expiry,
slot 1 clears **low 32-bit bit 2** from the actual Bullet command flags;
slot 10 instead clears **bit 21**. Both return integer one immediately.

On the non-expired path, each performs the real clock-scaled speed increment
`speed += slot.scalar_10 * float(default_timer_clock)`, where the original
clock object is `0x005AEFE4`, and updates the full three-lane **velocity**
vector (not Bullet position) with
`velocity += slot.vector_24 * float(default_timer_clock)`.
The two independent original absolute-value operations on `velocity.x` and
`velocity.y` use `scalar_math::absolute` at `0x0047A630` (float-to-double
CRT wrapper), with the exact original threshold **about 0.0001f**
(`0x0056FD30`, bits `0x38D1B717`). If either exceeds that threshold, the
function sets the actual Angle from native `scalar_math::arctangent(y,x)`
at `0x00459280` and replaces the speed with the genuine game-specific
**XY-only** magnitude. Otherwise the previous angle and the new
clock-adjusted speed remain unchanged. Both original functions advance
the active command Timer through native `Timer::operator++(int)` at
`0x00423540` and return integer zero.

The separately completed **25-byte** `bullet_velocity_magnitude(const
Vector3&)` calls the existing exact original `th20::squared_norm_xy` at
`0x00456130` and `scalar_math::square_root` at `0x00446B30`, returning
the float via original x87 ST0. Ghidra's provisional decompilation called
this return `void`, which was **rejected** after checking the actual
471/473-byte original callers. This is **XY magnitude, not three-dimensional
Vector3 magnitude**. It is naturally authored in
`src/BulletVelocityMagnitude.hpp/.cpp`; both actual gameplay consumers
include that maintained typed declaration from
`src/BulletCommandVelocity.cpp` rather than private ABI placeholders.

## Original MSVC code and real affected-only scope

Locked MSVC 19.44 C++20 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` produces **391/391** and **393/393** native
non-relocation bytes in the complete 471B and 473B methods, and **17/17**
for the entire 25B magnitude helper. All **42** original native relocation
offsets/types/destinations replay exactly, including the independently
reconstructed `squared_norm_xy`, native CRT square root, actual ClockScalar,
Vector3, Angle, Timer, arctangent and Bullet owners. Full strict canonical
replay verifies **969/969 complete original bytes**. There is no artificial
compiler-padding, copied opcode data, truncated body or relaxed comparator.

The two method declarations added to shared `Bullet.hpp` affect **20 source
objects containing 57 exact previous units**. All **57/57 old units** were
freshly cold-compiled and compared using only their actual include closure.
The new two methods live in one additional object; the separately exact
25B magnitude lives in another. All scoped verification totals **60/60
strict exact units across 22 freshly compiled objects**, with no full or
unfiltered cold replay. The compiler's private BulletController debug
literal `$SG85506` moved to `$SG85508`, and four Dialogue literals
`$SG117851..117854` moved to `$SG117853..117856`; offsets/types and all
independently anchored PE data destinations were unchanged and strictly
rechecked, not exempted.

Private proof logs and native audits:
`.analysis/core242-velocity-command-canonical-replay.log`,
`.analysis/core242-bullet-affected-replay-part-0.log` through
`.analysis/core242-bullet-affected-replay-part-2.log`, and
`.analysis/core242-bullet-sg-corrections.jsonl`.

Whole original roots still **nonexact** are the 662B `Bullet::cancel`
implementation, 273B `BulletController::draw_group`, 3,735B
`BulletController::emit` and 41,967B Enemy opcode dispatcher. Completing
three full native functions does not grant any part of their separate
native extents as exact or prove whole-game link/runtime completion.
