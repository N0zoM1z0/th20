# CORE/EXACT-246 — exact complete 637-byte Bullet command8 interpolation boss

Original target: immutable Japanese TH20 v1.00a Steamless, whole executable
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The real original 637-byte `0x004827E0..0x00482A5C` body comprises
**189 complete x86 instructions**, original interval SHA-256
`1944055e35bfdfcf47c9c08e70449b8d11203a56a13b674998d90ada849bcdfd`.
It is now maintained as a complete natural C++20 member method
`Bullet::advance_command8()` in `src/BulletCommand8.cpp`, not as an
isolated case arm, byte-embedded target output or partially matched prefix.
Original source naming remains inferred; all native member offsets, call
boundaries, physical code extent, branch shape and relocation destinations
were independently reconciled against the locked original PE.

## Full native gameplay behavior and typed interpolation

The original real `BulletExtendedCommands::at(8)` at `0x0047C680` selects
one 64-byte command slot. When its actual `Timer::at_least(word_30)`
completes, the method clears bit **17** (`0x20000`) of the low word of the
Bullet's 64-bit command flags at +`0x90`, sets actual Bullet `position`
to `commands.at(8).vector_24`, copies the command's `scalar_10` to Bullet
speed, and calls the real `polar(velocity, float(angle), speed)`, zeroes the
velocity's Z component, and returns integer one.

When the command is active, the original `Timer::equals(0)` at
`0x004785E0` conditionally copies the current Bullet position into the
actual `VectorInterpolation<Vector3>` at Bullet+`0x420` through its real
`set_start(const Vector3&)` at `0x004393F0`. The source captures the full
three-lane **old position** and calls the genuine 1,129-byte
`VectorInterpolation<Vector3>::sample()` at `0x0042AD80`, using the
**original hidden-result Vector3 ABI**. It subtracts old position and
assigns the complete returned vector to Bullet velocity; unlike an XY-only
subtraction, the temporary carries all three native lanes before Z is
explicitly set to 0.0f. The true `scalar_math::absolute()` at
`0x0047A630` tests first X and then Y against the original native positive
velocity threshold at `0x0056FD30`; if either exceeds it, the original
`scalar_math::arctangent(y,x)` at `0x00459280` updates the real Bullet
Angle through `Angle::operator=(float)` at `0x00452F20`. Finally the source
zeros velocity Z and advances the real command Timer using the native
`Timer::operator++` at `0x00423540`, returning integer zero. Native
conditional early exits and the security-cookie epilogue are preserved.

## Whole-body matching and original compiler branch structure

The first complete natural `/Od` C++20 hypothesis emitted **632 bytes**:
all original 188 emitted instruction mnemonics aligned, but it lacked an
**entire original unconditional jump** at `+0x116`. Wrapping the active
branch under a real `else` reproduced that original jump, but also emitted
one extra `NOP` after the terminal Timer increment, totaling **638B**.
The accurate natural source places the common `Timer++` **after** the
`if/else` block, since the expiration branch already returns one. That
matches the original compiler flow: **637/637 original native bytes**, all
**549/549 non-relocation bytes** and all **22 independently verified
native relocation offsets, types, and destinations**. Among these are the
actual typed command getter, both Timer operators, native
`VectorInterpolation<Vector3>` setters/sample, the game Vector3
subtraction, the X/Y absolute+threshold, scalar atan2 and actual Angle
assignment; the native 16-byte stack-clobber/security-cookie lifecycle is
also byte identical. No prefix-only comparison or fabricated NOP is used.

MSVC 19.44 C++20 x86 settings are the project's locked
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` profile.
The complete accepted canonical object replay is in
`.analysis/core246-bullet-command8-exact-replay.log`.

This one typed method declaration affects the exact `Bullet.hpp`
compiler-receipt include closure: **24 source-object providers, 62 strict
native units** including **61 older exact functions** and this new 637B
function. All 24 objects were freshly compiled; all **62/62 complete
strict native units** pass, including the previously admitted 898B
command3 whole switch/table contribution and 493B command7, 707B
rectangle cancellation, 339B firing and 832B boundary boss. Only
MSVC-private BulletController literal `$SG85510` changed to `$SG85511`
and four Dialogue literal labels `$SG117855..117858` changed to
`$SG117856..117859`. Original native relocation sites/types/data targets
were immutable; only private COFF identifiers were reconciled in the
manifest. Private scope logs:
`.analysis/core246-bullet-header-affected-replay-part-0.log`,
`.analysis/core246-bullet-header-affected-replay-part-1.log`, and
`.analysis/core246-bullet-header-affected-replay-part-2.log`.
No unfiltered whole-repository cold replay was run.

The **12,140-byte** original parent Bullet update root `0x0047DCF0`,
**3,735-byte** original single-shot Bullet emitter, **662-byte** original
Bullet cancellation core, and **41,967-byte** Enemy ECL opcode dispatcher
remain distinct nonexact whole functions. Exactness of this individual
whole 637B subroutine is not a link or runtime proof for those parents.
