# `LaserCurveInf::cancel_circle()` — exact native Curve path cancellation

The Curve vtable at `0x00571214` dispatches circle cancellation through slot
`+0x30` to the 647-byte native method at `0x004CA830`. The original type-2
`create_laser` diagnostic identifies the class as `LaserCurveInf`; its native
factory allocates `0x1370` bytes. The natural C++ implementation lives in
`src/LaserCurveCancelCircle.cpp`.

## Recovered object and path boundaries

- `LaserCurveInf` is `0x1370` bytes, matching the native factory allocation.
- `LaserType2Parameters` begins at `+0x6F8`; its `count` and `color` lanes are
  consumed at `+0x718` and `+0x714`.
- The two real `Animation` subobjects begin at `+0x754` and `+0xD38`.
- The path pointer is at `+0x1328`; it advances in `0x20`-byte records. Each
  `LaserCurvePathPoint` begins with the three-float point used by the hit test.
- The separately constructed `0x40`-byte path-state object begins at `+0x1330`
  and has its own [strict exact constructor receipt](LASER_CURVE_PATH_STATE_CTOR_EXACT.md).

## Native behavior

1. Return zero only when the caller's fourth argument is nonzero and
   `Laser::field_6CC` is nonzero.
2. Initialize the hit count and point index, construct the working `Vector3`,
   preserve the native base-position snapshot, and zero the 512-byte segment mask.
3. Square the radius once. Iterate `parameters.count` path records from `+0x1328`,
   copying each record's leading `Vector3` and testing XY squared distance.
   The forward miss edge `if (squared_distance > radius) goto tail` preserves
   the native unordered-aware `COMISS` behavior and branch layout.
4. For each hit, set the corresponding mask byte, increment the game's global
   bullet-cancel counter, and every twentieth point spawn the `bullet` animation
   with script `parameters.color * 2 + 0xD4`. Advance the path pointer for every
   sample, including misses.
5. If all points hit, set the native Laser state bits. Otherwise, when at least
   one point hit, dispatch the actual virtual slot `+0x38` with the mask and
   number of sampled points. Return the hit count.

## Strict native replay

The natural C++ forward miss goto makes the locked MSVC x86 `/Od` compiler emit
the native `JBE` hit edge and both `JMP` edges, including the otherwise
unreachable second jump. The complete **647/647 bytes** now strictly replay,
with **607/607 ordinary bytes** and **10/10 original relocation destinations**
matching. The relocations cover the security cookie, `Vector3`, `_memset`, the
XY squared-distance helper, the real BulletController/AnimationFile accessor
chain, the original `bullet` literal, `AnimationFile::spawn`, and the security
check. No inline assembly, manual branch bytes, NOPs, or padding are present.

The original class name is supported by the type-2 diagnostic string, native
factory, vtable and slot ownership; the path-state type spelling remains a
maintained descriptive name.
