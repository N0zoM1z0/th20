# CORE/EXACT-245 — complete original 493-byte Bullet player-homing velocity boss

Original target: immutable Japanese TH20 v1.00a Steamless, PE SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The independently audited **entire original 493-byte** function at
`0x00480DB0..0x00480F9C` has **146 x86 instructions**, whole native SHA-256
`afb97c18e3fc0e4ba66c998c701ab5aa36f6803685be1c2a30d514906d29475d`.
The maintained C++20 `Bullet::advance_command7()` in
`src/BulletCommand7.cpp` recovers the entire game-owned player-homing
Bullet velocity/interpolation path, not just a switch branch or preamble.
The original source spelling is inferred; instruction/ABI boundaries and
all native relocation destinations are independently checked.

The real Bullet's `commands.at(7)` uses the exact 64-byte
`ExtendedCommand` stride. If its actual `Timer::at_least(word_30)`
condition is true, the method clears **low-word command flag bit 31** and
returns integer one. Otherwise it obtains the active game Player via
`Context::player` at native `0x0040FF90` and calls the separately exact
157-byte `Player::direction_to` at `0x004FF350` using the Bullet's real
position. It combines that direction with `commands.at(7).scalar_14`
using genuine `add_angles` at `0x00438600`, creates a real `Vector3`
target velocity with `polar` at `0x00439330` and the command's
`scalar_10`, and adjusts the live Bullet velocity using the complete
natural vector expression:

`velocity += (target_velocity - velocity) * commands.at(7).vector_24.x`.

The normal vector subtraction, three-lane scalar multiplication and
`Vector3::operator+=` are original typed methods, with genuine local
12-byte Vector3 construction and original security-cookie frame. It then
forces velocity Z to **0.0f**, updates the live Bullet `speed` from the
independently exact XY-only `bullet_velocity_magnitude(velocity)` at
`0x0047A2A0`, updates its real `Angle` through
`vector_direction(velocity)` at `0x00456210`, advances the command's real
Timer, and returns integer zero. The original whole path has **21** direct
native relocations to real code/data; no guessed virtual dispatch or fake
helper ABI was introduced.

The initial entire C++ source probe emitted the right **493-byte length**,
but its `NOP` was emitted after the terminal Timer increment rather than
after the original Angle assignment. Moving `commands.at(7).timer++`
**outside** the actual conditional `else` block (the completed branch
already returns early) reproduces the genuine source-level control flow.
The natural locked MSVC 19.44 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` code then has **409/409 identical
non-relocation bytes** and all **21 independently grounded native
relocations**. The complete canonical replay yields **493/493 original
machine bytes**, with no arbitrary padding, native byte embedding or
prefix-only comparison. Proof: `.analysis/core245-bullet-command7-native-replay.log`.

Adding the real command7 member declaration to shared `Bullet.hpp` affects
**23 source-object providers / 61 strict native units**: 60 earlier exact
functions and the new whole 493B function. All 23 objects were freshly
cold compiled and **61/61 functions strictly replayed exact**. This
includes the original entire 898B command3 switch boss with its 928B
switch-table contribution, 707B rectangle cancellation, 832B boundary
logic, 339B BulletFire, and all previously admitted Bullet lifecycle
functions. Original data relocation targets were unchanged; the compiler
only renumbered BulletController private `$SG85509` to `$SG85510` and
Dialogue private `$SG117854..117857` to `$SG117855..117858`.
Focused complete include-closure logs:
`.analysis/core245-bullet-header-affected-replay-part-0.log`,
`.analysis/core245-bullet-header-affected-replay-part-1.log` and
`.analysis/core245-bullet-header-affected-replay-part-2.log`.
No unfiltered whole-repository cold replay was executed.

The full original **3,735-byte single-bullet emitter** at `0x004818E0`,
**662-byte** Bullet cancellation body, **781-byte** Bullet wrap boss,
**12,140-byte** Bullet update dispatcher, and **41,967-byte** Enemy ECL
opcode root remain *nonexact*. A correctly matched whole 493B method is
not a runnable-game or complete-parent proof.
