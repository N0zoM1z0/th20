# LaserCurveInf::cancel_rectangle() — exact native curve-rectangle boss

The Curve-family vtable at 0x00571214 dispatches slot +0x2C to
LaserCurveInf::cancel_rectangle() at 0x004C9AB0. The complete native body is
740 bytes. Its second integer argument and field_6CC preserve the original
early-out gate; the other integer argument is unused.

The active path constructs the three native Vector3 temporaries and snapshots
the Laser base position. It allocates a byte mask whose length equals the
Type2 curve point count using DiagnosticAllocator::allocate_bytes and the
original diagnostic source label at 0x00571748, then clears the whole mask.
The native Vector3 division/subtraction/addition temporaries are retained even
though the subsequent point predicate consumes the original rectangle
arguments.

The point walk uses the native 0x20-byte LaserCurvePathPoint stride and the
original count boundary. Each point is tested by
geometry::rotated_rectangle_point against the caller's rectangle. Hits mark
the corresponding byte, increment the owning BulletController cancel counter,
and every twentieth point index spawns a bullet animation using the Type2
color and script base 0xD4. If every point hits, the native full-cancel flag
transition is applied; if only some points hit, the original virtual
cancel_segments slot +0x38 receives the complete mask and point count. The
allocated mask is then released through DiagnosticAllocator::release_bytes.

## Strict replay

The natural C++ implementation in src/LaserCurveCancelRectangle.cpp strictly
replays 740/740 bytes under the pinned MSVC x86 /Od profile. All 656 ordinary
bytes and all 21 original call/data relocations match, including the allocator
and original diagnostic label, memset, three Vector3 arithmetic helpers,
rotated-rectangle predicate, Context/BulletController accounting,
AnimationFile spawn, virtual segment publication, allocator release and
security-cookie check. No assembly or padding is used.
