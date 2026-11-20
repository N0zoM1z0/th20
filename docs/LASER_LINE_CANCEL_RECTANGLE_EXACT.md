# LaserLineInf::cancel_rectangle() — exact native rectangle-cancellation boss

The Line-family vtable at 0x00571148 dispatches slot +0x2C to
LaserLineInf::cancel_rectangle() at 0x004CA380. The complete native body is
1,197 bytes. Its second integer argument and field_6CC preserve the native
early-out gate; the other integer argument is unused by this implementation.

The active path snapshots the native Laser base position, constructs the
512-byte segment mask, computes the screen-derived angular step, creates the
initial position and doubles the segment step. It walks with the inclusive
native boundary screen_top / screen_half + distance <= field_74. Every sample
is passed to the original geometry::rectangle_rectangle function together
with the supplied rectangle center, dimensions and direction, and the
sampled segment's center, doubled step dimensions and Laser angle.

A hit marks the current segment, increments the owning BulletController
cancel counter, and selects one of three bullet animation script families
using the signed Laser type and Type0 color. The original ranges are <= 0x11,
0x22 or 0x26 for script base 0xD4; <= 0x1E for base 0x104; and <= 0x21
for base 0x11C. At the end, a partial hit set is published through virtual
slot +0x38 with the full mask and segment count. When every segment hits,
the native flags transition is applied instead. The method returns the hit
count.

## Strict replay

The natural C++ implementation in src/LaserLineCancelRectangle.cpp strictly
replays 1,197/1,197 bytes under the pinned MSVC x86 /Od profile. All 1,077
ordinary bytes and all 30 original call/data relocations match, including
the 512-byte memset, rectangle-rectangle geometry test, Vector3 helpers,
Context/BulletController accounting, AnimationFile spawns, virtual
cancel_segments dispatch and security-cookie check. No assembly or padding
is used.
