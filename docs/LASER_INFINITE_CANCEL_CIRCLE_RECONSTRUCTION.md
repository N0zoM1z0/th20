# `LaserInfiniteInf::cancel_circle()` — native radial sampling

The Infinite-family vtable at `0x005712E8` dispatches circle cancellation
through slot `+0x30` to the 1,123-byte native method at `0x004CABF0`. The
maintained natural C++ reconstruction is `src/LaserInfiniteCancelCircle.cpp`;
it is tracked as `reconstructed`, not `matching`.

## Recovered owner layout

The concrete `LaserInfiniteInf` object is `0x1338` bytes, matching the
original factory allocation. Its Type1 parameter object begins at `+0x6F8`,
a scalar lane occupies `+0x76C`, and the two real `Animation` subobjects begin
at `+0x770` and `+0xD54`. The native base discriminator at `+0x6E4` is signed:
the original code uses signed `JLE`/`JG` comparisons, so the shared `Laser`
field is now represented as `std::int32_t` without changing its layout.

## Native behavior

1. Return zero when the fourth argument is nonzero and base `field_6CC` is
   nonzero. Initialize hit/sample counters, construct the working point and
   step vectors, retain the native base-position snapshot, and zero the
   512-byte segment mask.
2. Use the base angle to create an 8px half-step vector, compute the first
   point at `position + step`, clear its Z lane, then double the step to 16px.
   The loop continues while `8 + distance < field_74`, increasing distance
   by the original 16px data constant after each sample.
3. For each sample, test XY squared distance against the squared cancellation
   radius. A hit sets the sample mask, increments the global bullet-cancel
   counter, then checks the point against the original 32px screen margin.
4. Only on-screen hits spawn an effect. The signed `field_6E4` discriminator
   selects the three native script families: `color*2+0xD4` for values
   `<=0x11`, `0x22`, or `0x26`; `color*2+0x104` for values `<=0x1F` or
   `0x1B`; and `color*2+0x11C` for values `<=0x21`. Other types produce no
   animation. The actual Context/BulletController/AnimationFile call chain is
   retained separately in each branch.
5. Advance the point by 16px and increment the sample count on every iteration.
   After the loop, call the real virtual slot `+0x38` with the mask and sample
   count only when at least one point hit; return the hit count.

## Focused structural receipt — deliberately NONEXACT

The locked MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc` candidate contributes 1,117 bytes versus the 1,123-byte native body.
`scripts/verify-laser-infinite-cancel-circle-native.py` compiles only this
source, aligns the post-hit-branch code by the six-byte native branch-layout
difference, and confirms **967/967 ordinary non-relocation bytes** plus
**33/33 original relocation destinations**. The relocation set includes both
Vector3 constructors, `polar`, Vector3 add/compound-add, the squared-distance
helper, the original screen constants, `_memset`, the Context/BulletController
accessors, the 32px screen-bound helper, all three original `"bullet"` literal
references and the `AnimationFile::spawn` calls.

The six-byte difference is the native `JBE` hit edge followed by two jumps to
the sample-advance block; the natural candidate uses one unordered-aware `JA`
exit. The verifier checks both branch destinations and all relocations. No
unreachable jump, NOP, assembly, or padding is synthesized. No canonical match
unit or exact byte credit is claimed. The native class/source spelling is
corroborated by the original source diagnostic and vtable; authorship is
classified as medium-confidence game logic independently of byte equality.

The concrete `LaserInfiniteInf` constructor at `0x004C8880` is now also
restored as a natural C++ initializer list and strictly exact (87/87 bytes,
five original relocations). See
[the constructor receipt](LASER_INFINITE_CONSTRUCTOR_EXACT.md).
