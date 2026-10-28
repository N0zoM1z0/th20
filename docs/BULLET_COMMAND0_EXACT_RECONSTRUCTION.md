# CORE/EXACT-240 — complete 267-byte Bullet command-0 speed/angle update

Original locked input: Japanese TH20 v1.00a Steamless, PE SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The entire original native **267-byte**, **73-instruction** method
`0x004840E0..0x004841EA`, SHA-256
`c5cba55150fab2ec9ec6dd7bcbfa44e2ce9bed9310f4078b5d8530c5147f4a33`,
now lives as a natural C++20 whole function `Bullet::advance_command0()`
in `src/BulletCommand0.cpp`. The original C++ name remains inferred;
original data ownership, ABI, complete body and call/data relocations
were separately confirmed against immutable native code.

The real `BulletExtendedCommands::at(0)` at `0x0047C680` selects the native
64-byte command slot zero. Its genuine sixteen-byte Timer is compared to
**16 frames** by original `Timer::at_most(16)` at `0x00423590`. On true,
`Timer::fraction()` at `0x00423BD0` supplies an x87 scalar float. The full
native x86 SSE speed curve is

`remaining = 5.0f - Timer.fraction() * 5.0f / 16.0f`

followed by `length = remaining + Bullet.speed`, the true
`Angle::operator float()` conversion and original `polar(Bullet.velocity,
angle, length)` at `0x00439330`. The original 5.0f and 16.0f literal
objects are independently anchored to `0x0056EDD4` and `0x0056CD90`;
other native relocations identify the actual Angle, slot accessor and
Timer methods. The command's original Timer is then advanced through
`Timer::operator++()` at `0x00423540` and integer zero is returned.

When the Timer is beyond the 16-frame window, the complete original path
instead clears only **low 32-bit bit 0** of the live Bullet's 64-bit
command flags at +`0x90` and returns integer one, without Timer advance.
This function is not the separate slot-nine Timer/position update or a
fragment of the still-unreconstructed main emitter. Natural C++ `if/else`
with separate `remaining`, `length` and `direction` float variables matches
the entire original 267B x86 control-flow, x87-to-SSE value transfers,
three constant-relocation sites, and all game-owned call ABIs.

Locked MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` strict replay verified **267/267 complete
original native bytes**, with all **11** independently anchored relocation
fields (including two native 5.0f references). All **223/223** original
non-relocation bytes matched before full strict admission.
One fresh object: `build/core240-canonical/BulletCommand0.obj`.

One real method declaration was added to shared `Bullet.hpp`. The complete
compiler-receipt include closure contains **18 old source providers with
55 previously exact native units**; all 55 were cold-recompiled and passed
strict replay. Adding the new unit yields **56/56 exact affected units
across 19 freshly compiled objects**. The only symbol changes were
compiler-private literal labels in the BulletController diagnostic
`$SG85504` to `$SG85505`, and four Dialogue literals
`$SG117849..117852` to `$SG117850..117853`; every original native data
relocation target and compared byte remained unchanged. No full/unfiltered
cold replay or relaxed comparator was used.

Focused private proofs: `.analysis/core240-original-004840e0.asm`,
`.analysis/core240-command0-canonical-replay.log`,
`.analysis/core240-bullet-affected-replay-part-0.log`, and
`.analysis/core240-bullet-affected-replay-part-1.log`.

Still not exact: complete original **662B** `Bullet::cancel`, **273B**
`BulletController::draw_group`, **3,735B** `BulletController::emit` and
**41,967B** Enemy ECL opcode root. A complete exact native gameplay leaf
or mid-size command method does not grant exactness to their callers or
to a runnable full-game build.
