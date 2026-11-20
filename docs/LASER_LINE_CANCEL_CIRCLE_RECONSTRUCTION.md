# `LaserLineInf::cancel_circle()` reconstruction

The native function at `0x004CB060` is the `+0x30` circle-cancellation
implementation in the Line Laser vtable at `0x00571148`. Its native boundary
is 1,170 bytes. `src/LaserLineInf.hpp` records the concrete derived layout
from the factory/constructor audit: the `Laser` base, `LaserType0Parameters`
at `+0x6F8`, and three real `Animation` subobjects at `+0x74C`, `+0xD30`,
and `+0x1314`, for a total size of `0x18F8`.

## Reconstructed behavior

1. If the final argument is nonzero while the Laser's `field_6cc` is active,
   return zero. Otherwise initialize hit/segment counts, two active Vector3
   locals, the native base-position snapshot, and a 512-byte zeroed segment mask.
2. Generate the half-step direction from the Laser angle using the native
   `16 / 2` spacing, form the first sample at the Laser's position plus that
   direction, zero Z, and double the direction for the 16-unit step.
3. Walk the line while the next half-step remains within `field_74`. For each
   sample, compare the XY squared distance to the supplied center against the
   squared radius. Record hits by sample index in the segment mask.
4. For each hit, increment the owning BulletController's cancellation counter.
   Every fourth hit may spawn a `bullet` animation, with script family selected
   from `field_6e4` and `LaserType0Parameters::color`; the three branches retain
   their distinct native `AnimationFile::spawn` calls.
5. If some but not all segments hit, publish the mask and sample count through
   the native virtual slot `+0x38`. If every sampled segment hits, update the
   Laser's `field_24` cancellation bits directly. Return the hit count.

## Current candidate and open work

The natural `/Od /Ob0 /GS /sdl` i386 COFF candidate is now 1,164 bytes versus
the complete 1,170-byte native code body. The following `INT3` alignment bytes
begin after the native function boundary and are not part of its size. The
remaining six-byte difference comes from the native `JBE`/`JMP` branch layout
and a second unreachable five-byte jump at `0x004CB221`; the natural source
uses the equivalent unordered-aware `JA` exit instead of synthesizing dead
code. No source padding or assembly is added. The hit test is written as
`!(squared_distance > radius)` to preserve the native ordered/unordered
`COMISS` branch behavior, rather than relying on the decompiler's superficially
equivalent `<=` spelling. The candidate uses the real
`Context::bullet_controller()` /
`BulletController::animation_file()` / `AnimationFile::spawn()` accessor chain,
Vector3 math, the XY squared-distance helper, and the native virtual publication
slot. `Context::bullet_controller()` is a verified 16-byte physical alias of
`Identifier32::get`; its source-level name is documented without a second
reccmp mapping or duplicate byte credit. The full class vtable, constructor/destructor,
and the other three `cancel_circle` implementations remain separate boundaries.

The shared base `field_6E4` is now typed as signed `std::int32_t`; the
Infinite handler's native `JLE`/`JG` type-family comparisons independently
confirm signed interpretation. This changes no object offsets or sizes.
