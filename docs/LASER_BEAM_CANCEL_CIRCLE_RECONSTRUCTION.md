# `LaserBeamInf::cancel_circle()` — native Beam path cancellation

The Beam vtable at `0x00571214` dispatches circle cancellation through slot
`+0x30` to the 647-byte native method at `0x004CA830`. The maintained source
is a natural C++ reconstruction in `src/LaserBeamCancelCircle.cpp`; it is
tracked as `reconstructed`, not `matching`.

## Recovered object and path boundaries

- `LaserBeamInf` is `0x1370` bytes, matching the native Beam factory allocation.
- `LaserType2Parameters` begins at `+0x6F8`; its `count` and `color` lanes are
  consumed at `+0x718` and `+0x714`.
- The two real `Animation` subobjects begin at `+0x754` and `+0xD38`.
- The path pointer is at `+0x1328`; it advances in `0x20`-byte records. Each
  `LaserBeamPathPoint` begins with the three-float point used by the hit test;
  the remaining five words retain neutral names.
- The separately constructed `0x40`-byte path-state object begins at `+0x1330`
  and has its own [strict exact constructor receipt](LASER_BEAM_PATH_STATE_CTOR_EXACT.md).

## Native behavior

1. Return zero only when the caller's fourth argument is nonzero and
   `Laser::field_6CC` is nonzero.
2. Initialize the hit count and point index, construct the working `Vector3`,
   preserve the native base-position snapshot, and zero the 512-byte segment mask.
3. Square the radius once. Iterate `parameters.count` path records from `+0x1328`,
   copying each record's leading `Vector3` and testing XY squared distance. The
   `!(distance > radius_squared)` spelling preserves the native unordered
   `COMISS` behavior as well as the ordinary finite comparison.
4. For each hit, set the corresponding mask byte, increment the game's global
   bullet-cancel counter, and every twentieth point spawn the `"bullet"` animation
   with script `parameters.color * 2 + 0xD4`. The path pointer advances by `0x20`
   on every sample, including misses.
5. If all points hit, set the native Laser state bits. Otherwise, when at least
   one point hit, dispatch the actual virtual slot `+0x38` with the mask and
   number of sampled points. Return the hit count.

## Focused structural receipt — deliberately NONEXACT

The locked MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc` candidate contributes 641 bytes against the 647-byte native body. The
focused verifier `scripts/verify-laser-beam-cancel-circle-native.py` compiles
only this source, aligns the post-branch code by the six-byte native branch
layout difference, and confirms **583/583 ordinary non-relocation bytes** plus
**10/10 original relocation destinations**. Those relocations cover the
security cookie, `Vector3` constructor, `_memset`, squared-distance helper,
`Context::bullet_controller()` (twice), `BulletController::animation_file()`,
the original `"bullet"` literal at `0x0056FD14`, `AnimationFile::spawn()`, and
the security-cookie check.

The remaining six bytes are the native conditional layout: `JBE` to the hit
block followed by two jumps to the loop tail, versus the natural candidate's
single unordered-aware `JA` exit. The branch destinations and unordered
semantics are independently checked. No unreachable jump, NOP, assembly, or
padding is synthesized. No canonical match unit or exact byte credit is claimed.

The class name and original source spelling are inferred from the native Beam
vtable, factory allocation, constructor layout and slot ownership. The origin
classification is medium-confidence game-authored behavior, independent of
byte equality.
