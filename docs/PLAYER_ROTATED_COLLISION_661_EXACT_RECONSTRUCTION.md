# CORE/EXACT-297 — original entire 661-byte Player rotated rectangle/circle collision boss

Immutable target: Japanese TH20 v1.00a Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The **entire native `0x004F91D0..0x004F9464`** method now compiles from
normal C++20 as `Player::collision_rectangle_circle(const Vector3&,
float width, float height, float angle, int mode)` in
`src/PlayerRotatedCollision.cpp`. Method spelling is inferred, but the
whole original code/ABI/data layout is independently established.

**Full 661/661 original machine bytes strict exact**, **181/181 x86
instruction mnemonics and order** preserved, **565/565 original
non-relocation bytes**, and all **24 original relocation positions/
types/targets** independently checked from real PE instruction operands.
Original whole-function SHA-256:
`95097d091144937f0cdd64a9675ebc16fdef575cdd219566e016f026bd859539`.
No assembly, copied native bytes, artificially truncated body, fake
Player layout, hidden alternate implementation or inert padding is used.

## Entire native two-stage rotated collision, graze and hit protocol

The source constructs the actual three-lane `Vector3` value through
native `Vector3::Vector3()` at `0x00422E10`, then copies all three
incoming position lanes. The true `Player::focused_mode()` at
`0x004FF5E0` first chooses the live `PlayerCollisionBounds` focus
radius at `+0x2098` or normal radius at `+0x2094`. The native original
stores the focus-selected float separately, **then copies it into the
live scaled-hit-radius float**, allowing the actual
`context->player_record()->collision_radius_multiplier()` (73B
at `0x004FF490`) to multiply it and divide by native **100.0f** at
`0x0056E04C`. This real intermediate radius copy is essential: omitting
it emitted 651B/179 x86 instructions rather than original 661B/181.

The method independently repeats the real focused-mode test to compute
the graze radius (`focus_radius` or `normal_radius` plus original
**30.0f** at `0x0056F280`). It then performs the **entire 669B**
`geometry::rectangle_circle` at `0x00457610` twice with the actual
8-float original native ABI and unmodified argument order: rotated
rectangle target `position.x`, `position.y`, `angle`, `height`, `width`,
then the real Player center `position_ref().x/y`, and selected collision
radius. The initial test uses **graze radius**, and no intersection
returns 0; the second test uses the smaller scaled **hit radius**, and
no intersection returns **2 (graze)**. Both calls independently invoke
the real `Player::position_ref()` *twice* in the original native argument
evaluation order (Player Y first, then Player X). The function does
not cache these getters or substitute a simplified circle-point test.

On a real hit intersection, the native method tests original borrowed
`FrontInf* process_front` at `0x005C06A4`; an active dialogue suppresses
hit handling through exact 44B `FrontInf::has_dialogue()` at
`0x00478160`. Nonzero collision mode returns 2 instead of inflicting
player damage. The genuine three Player state checks for 2, 4, and 3
then return 0, as does `Player::timer_2050.greater_than(0)` for active
invulnerability. Otherwise the method calls real
`Player::apply_player_hit()` at `0x004F86F0` and returns 1. This
complete ending is different from some previously accepted Player
circle/axis-aligned rectangle methods' invulnerability return protocol;
we preserve the actual native result rather than reuse an assumption.

## Native instructions, relocations and locked compiler proof

All **24** PE relocated offsets were independently derived from original
Capstone-decoded instructions and DWORD displacements, rather than
assuming earlier notes or the comparison solver had the correct targets.
The original calls include two focused-mode queries, exact PlayerRecord
multiplier and context getter, four position-ref calls, both 669B
`geometry::rectangle_circle` children, the FrontInf dialogue check,
three `Player::state_value` tests, original Timer comparison, native
`Player::apply_player_hit` and genuine MSVC security-cookie check.
Native constants are original 100.0f and 30.0f, and native global
FrontInf is checked twice. The original PE attestation is retained in
`.analysis/core297-player-rotated-native-24-relocations.json` and
`.analysis/core297-player-rotated-pe-attestation.log`.

The true C++ owner, under the locked MSVC 19.44 x86 `/nologo /c
/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc` profile at reduced priority, freshly strict-replays as
`player_rotated_rectangle_circle: exact (661/661 bytes)` in
`.analysis/core297-player-rotated-canonical-replay.log`. This is the
**entire 181-instruction native method**, not a prefix or one branch.

## Actual bounded changed-header include closure

One real member declaration was added to existing `Player.hpp`; no
layout, calling-convention profile or original target bytes were
changed. From authentic previous compiler receipts, this header's
exact dependency closure comprises **13 old source providers and 41
existing whole exact native units**. All 13 were cold compiled under
the locked profile, **41/41 prior strict units preserved**, including
previous full 777B rectangle, 466B circle, 2,018B Bullet collision and
434B Bullet aim selector callers. The sole private MSVC `$SG`
constructor-string identifier changed in `src/Player.cpp`; its
native original relocation offset, type and target address were
verified unchanged before that source was rerun strict-exact.

With the newly accepted complete 661B method this batch is
**42/42 scoped exact native units across 14 freshly compiled source
objects**, as proven in
`.analysis/core297-player-rotated-affected-replay-part-{0..1}.log`.
**No unfiltered whole-repository cold replay** was run.

Other independent complete nonexact roots still include the 1,404B
Bullet command-11, 273B Bullet drawing group, 3,735B emitter, 12,140B
Bullet command sequencer and 41,967B Enemy opcode dispatcher. This
method's strict equality does not imply complete game runtime/linkage.
