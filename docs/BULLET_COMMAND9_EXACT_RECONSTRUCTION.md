# CORE/EXACT-237 — exact complete native 226-byte Bullet command-9 update

Original input is Japanese TH20 v1.00a Steamless PE, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The independently audited **entire 226-byte native function**
`0x0047C800..0x0047C8E1` comprises **70 x86 instructions**, with full
native SHA-256 `b56e367e56cc464c4e42d68d9b05128a486d1bf646731a6b0ebaba4f1a43db28`.
The original C++ identifier is inferred; the native game-owned typed body
is maintained in `src/BulletCommand9.cpp` as `Bullet::advance_command9()`.
This is a whole function, not an extracted switch arm.

The original code accesses real Bullet `commands.at(9)` with the native
64-byte `ExtendedCommand` stride, checks its genuine `Timer::at_least` at
`0x004235C0` against `word_30`, and, if the countdown has finished,
clears precisely **bit 19 of the low 32-bit** native 64-bit
`BulletCommandFlags` at +0x90 before returning integer one.
If the command timer is not finished, it increments actual Bullet position
through `Vector3::operator*(float)` and `Vector3::operator+=` using
`commands.at(9).vector_24` multiplied by the real shared
`default_timer_clock` at `0x005AEFE4`. It then assigns native integer zero
to `commands.at(9).timer` and returns integer zero. Actual native methods
are `BulletExtendedCommands::at` `0x0047C680`, `ClockScalar::operator float`
`0x004292E0`, Vector3 multiply `0x004292F0`, Vector3 addition assignment
`0x004296E0`, and Timer integer assignment `0x00423520`.

A first natural C++ expression using a guard-return and normal fallthrough
emitted **224 bytes** and omitted one native unconditional jump at
`+0x6E`. The native 226B body has a genuine `if/else` branch shape, with
position update only under `else` and the shared Timer reset after the
branch. Preserving this natural C++ ownership yields the exact instruction
sequence (including its original compiler-emitted jump), not artificial
padding or assembly. The locked MSVC 19.44 C++20 x86 profile
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` gives **186/186
identical non-relocation bytes** and all **ten independent native relocation
fields**, strict canonical full-body **226/226 original bytes**.

Adding the real member declaration to shared `Bullet.hpp` changes its actual
compiler-receipt include closure: **17 older cold objects containing 54
previous exact native units**. All 54 were freshly compiled and strict
replayed without a regression. The compiler assigned BulletController's
private diagnostic literal `$SG85500` instead of `$SG85499`, and Dialogue
`$SG117845..117848` instead of `$SG117844..117847`. All original PE
relocation destinations, offsets/types and actual native bytes were fixed;
only COFF-private symbol spelling was updated in the manifest.
**55/55 affected strict units across 18 cold objects**, comprising 54 old
and one new. No all-repository cold replay or relaxed comparator.
Original/native private evidence:
`.analysis/core235-native-0047c800.asm`,
`.analysis/core237-bullet-command9-replay.log`, and
`.analysis/core237-bullet-header-closure-replay.log`.

The original **662-byte Bullet cancellation** function, original
**3,735-byte single-bullet emission** function, and **41,967-byte** Enemy
opcode root remain open. Successful strict replay for this one entire
subsystem method does not imply full game linking or those bosses' completion.
