# LaserLineInf::erase() — exact native segment erasure

The Line-family vtable at 0x00571148 dispatches slot +0x44 to
LaserLineInf::erase() at 0x004C9830. The complete native body is 635 bytes.
Its two integer arguments preserve the original gate: when the second
argument is nonzero and field_6CC is also nonzero, it returns zero without
changing the Laser state.

The active path constructs two real Vector3 temporaries, computes the
screen-derived angular step (screen_top / screen_half), creates the initial
position from the Laser base position plus that step, and doubles the step for
subsequent samples. It walks the Laser length using the original strict
sample_distance < field_74 boundary. Unlike the Infinite variant, this Line
path spawns a bullet effect at every sample and does not run the separate
screen-edge predicate. The Type0 color and signed type discriminator select
the same three original bullet script families: <= 0x11, 0x22, or 0x26
for base 0xD4; <= 0x1F or 0x1B for base 0x104; and <= 0x21 for
base 0x11C. The Laser state becomes 1 after the sampling pass, and the
method returns the number of samples processed.

## Strict replay

The natural C++ implementation in src/LaserLineErase.cpp strictly replays
635/635 bytes under the pinned MSVC x86 /Od profile. All 527 ordinary bytes
and all 27 original call/data relocations match, including the Vector3
construction/operators, polar helper, Context/BulletController accessors,
AnimationFile spawn and security-cookie check. No assembly or padding is used.
