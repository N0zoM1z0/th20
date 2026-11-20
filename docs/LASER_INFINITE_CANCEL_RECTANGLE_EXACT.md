# LaserInfiniteInf::cancel_rectangle() — exact native rectangle-cancellation boss

The Infinite-family vtable at 0x005712E8 dispatches slot +0x2C to
LaserInfiniteInf::cancel_rectangle() at 0x004C9F10. The complete native body
is 1,131 bytes. Its second integer argument and field_6CC preserve the native
early-out gate; the other integer argument is not consumed by this path.

The active path constructs the native 512-byte segment mask and two Vector3
temporaries. It computes the screen-derived angular spacing, creates the first
sample from the Laser position and polar step, explicitly zeros the planar
z lanes, and doubles the step. The inclusive loop boundary is
screen_top / screen_half + distance <= field_74. Each sampled segment is
tested by the original geometry::rectangle_rectangle routine using the
caller-supplied rotated rectangle and the segment's position, step dimensions,
and Laser angle.

A hit sets the corresponding mask byte, increments the owning
BulletController cancellation counter, and spawns the matching bullet
animation selected from the signed Laser type and Type1 color. The three
script bases are 0xD4, 0x104, and 0x11C with the original type ranges. After
sampling, a nonzero hit count dispatches the native virtual cancel_segments
slot with the complete mask and segment count. The return value is the number
of hit segments.

## Strict replay

The natural C++ implementation in src/LaserInfiniteCancelRectangle.cpp
strictly replays 1,131/1,131 bytes under the pinned MSVC x86 /Od profile.
All 1,011 ordinary bytes and all 30 original call/data relocations match,
including the 512-byte memset, rectangle-rectangle geometry test, Vector3
helpers, BulletController accounting, AnimationFile spawns, virtual
cancel_segments dispatch and security-cookie check. No assembly or padding
is used.
