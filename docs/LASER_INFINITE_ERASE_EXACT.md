# LaserInfiniteInf::erase() — exact native segment erasure

The Infinite-family vtable at 0x005712E8 dispatches slot +0x44 to
LaserInfiniteInf::erase() at 0x004C9580. The complete native body is
683 bytes. Its two integer arguments preserve the original gate: when the
second argument is nonzero and field_6CC is also nonzero, it returns zero
without changing the Laser state.

The active path constructs two real Vector3 temporaries, computes the
screen-derived angular step (screen_top / screen_half), creates the initial
position from the Laser base position plus that step, and doubles the step for
subsequent samples. It walks the Laser length using the original strict
sample_distance < field_74 boundary. Samples outside the native screen
rectangle are skipped. Visible samples select one of three original bullet
script families using the signed type discriminator and the Type1 color, then
spawn a bullet animation through the active Context's BulletController
and AnimationFile. The native type ranges are <= 0x11, 0x22, or 0x26
for base 0xD4; <= 0x1F or 0x1B for base 0x104; and <= 0x21 for
base 0x11C. The Laser state becomes 1 after the sampling pass, and the
method returns the number of samples processed.

## Strict replay

The natural C++ implementation in src/LaserInfiniteErase.cpp strictly
replays 683/683 bytes under the pinned MSVC x86 /Od profile. All 563
ordinary bytes and all 29 original call/data relocations match, including the
Vector3 construction/operators, polar helper, screen-bound predicate,
Context/BulletController accessors, AnimationFile spawn and security-cookie
check. No assembly or padding is used.
