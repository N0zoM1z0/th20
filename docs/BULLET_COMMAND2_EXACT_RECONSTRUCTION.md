# CORE/EXACT-241 — whole original 424-byte Bullet command-2 update

Immutable Japanese TH20 v1.00a Steamless target SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The entire original native function at `0x00483920..0x00483AC7` is
**424 bytes, 117 x86 instructions**, SHA-256
`5db4ede541395a58fbf913f2d81bf6878c374ddec9128fd2b04b96969026a1f4`.
The complete game-specific typed body now lives as natural C++20
`Bullet::advance_command2()` in `src/BulletCommand2.cpp` (native C++
spelling is inferred). It is not a partial opcode fragment or hand-authored
assembly artifact.

The real `BulletExtendedCommands::at(2)` at `0x0047C680` selects the native
64-byte command slot two and calls its actual `Timer::at_least(word_30)`
at `0x004235C0`. If the native Timer reaches this threshold, the function
clears precisely low-word bit 3 from Bullet's real 64-bit command flags at
+`0x90` and returns integer one. On the active path it uses the original
shared `default_timer_clock` at `0x005AEFE4` **twice**, once multiplied by
command `scalar_14` for the Angle increment and once by `scalar_10` for the
speed increment. The actual Angle getter and `add_angles` at `0x00438600`
are followed by original normalizing `Angle::operator=(float)` at
`0x00452F20`. The actual Bullet speed is updated; the current Angle and
speed are passed to native `polar(velocity,angle,speed)` at `0x00439330`.
The whole function then uses original `Timer::operator++(int)`
`0x00423540` on command slot 2, returning integer zero.

## Compiler/x87/branch convergence

The first complete natural method emitted **439 bytes**. Independently
inspecting the original code showed `BulletExtendedCommands::at(2)` is
resolved **before** the x87 `ClockScalar` getter and retained in ESI,
whereas the initial C++ multiplication evaluated the clock first.
Natural equivalent expressions `slot.scalar_14 * float(default_timer_clock)`
and `slot.scalar_10 * float(default_timer_clock)` reproduce the original
MSVC register-use and floating-dataflow order. This reduced the whole
function to **425 bytes** with all **117 original instruction mnemonics
in order**, but one extra NOP remained immediately after Timer increment.

The original native Timer increment happens **after the conditional
branch has joined**, not as the last expression inside the active `else`
block. Keeping the original semantic early return and placing the normal
Timer postfix increment after the `if/else` removes precisely that extra
compiler NOP. The maintained source is a normal single C++20 body, with no
compiler-only dummy work, copied opcodes, arbitrary padding or extra object
layout facades. Locked MSVC 19.44 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` now emits the **entire original 424/424 bytes**:
**360/360 original non-relocation bytes** plus **all 16 independently
anchored original relocation offsets/types/destinations**, including two
ClockScalar globals, native Angle and Timer members, and `polar`.

The single method declaration added to shared `Bullet.hpp` affects **19
previously accepted exact source objects/56 previous strict functions** by
actual compiler-receipt include closure. All 56 were freshly compiled and
passed strict canonical replay. Private MSVC BulletController diagnostic
`$SG85505` became `$SG85506`, while four Dialogue locals shifted
`$SG117850..117853` to `$SG117851..117854`; native original data targets
and relocation offsets/types remain unchanged. Together with the new 424B
unit the scope is **57/57 strict exact units across 20 cold objects**.
No all-repository cold replay or relaxed comparator was used.

Private proof: `.analysis/core240-original-00483920.asm`,
`.analysis/core241-command2-canonical-replay.log`,
`.analysis/core241-bullet-affected-replay-part-0.log`,
`.analysis/core241-bullet-affected-replay-part-1.log`, and alternative
whole-body `.analysis/core241-*.cpp` probes.

Open roots remain **662B** `Bullet::cancel`, **273B**
`BulletController::draw_group`, **3,735B** `BulletController::emit`, and
**41,967B** Enemy opcode dispatcher. A complete 424B exact gameplay method
is not an implicit exact-credit claim on these separate original bodies.
