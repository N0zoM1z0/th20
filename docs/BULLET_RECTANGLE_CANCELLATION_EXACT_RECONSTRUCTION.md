# CORE/EXACT-235 — whole original 707-byte Bullet rectangle cancellation boss

Original target: immutable Japanese TH20 v1.00a Steamless PE, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The **complete** native `0x0047CC90..0x0047CF52` function has **707 bytes and
209 x86 instructions**, SHA-256
`e0251d1f35fb23b7d9cfcdc8e7024ec3a30cc4c9c4560a8d21796f095b2e9f68`.
Natural maintained C++20 now lives at `src/BulletRectangleCancellation.cpp`
as `BulletController::cancel_in_rectangle` (original spelling inferred).
Neither a truncated body nor a compiler-padded pseudofunction is credited.

## Original typed gameplay control flow

The function constructs two actual 12-byte `Vector3` temporaries and
performs original `dimensions / 2.0f`, `center - half`, and `center + half`
using complete native Vector3 operators. Despite the apparently unused
resulting local vectors, both original operations are present in the immutable
native function and cannot simply be optimized out of the `/Od` source.
The actual `BulletController::active_list()` at +`0x286D64` supplies
real intrusive Bullet link/iterator lifetime and SEH/unwind. State **1 or 2**
and `field_18 == 0` are the required native eligibility gates.

For each eligible Bullet, the original full **669-byte**
`th20::geometry::rectangle_circle` function at `0x00457610` is called
**twice**. The first test uses incoming rectangle center X/Y, width/height,
orientation, and the Bullet's real X/Y position plus radius
`Bullet.size.x * Bullet.scale`. The second uses the **true game viewport**:
X center **0.0f**, Y center **448.0f / 2.0f**, original width **384.0f**,
height **448.0f**, direction **0.0f**, and the same live Bullet position and
radius. Original independently attested constant addresses are 2.0f
`0x0056C8D0`, 384.0f `0x0056CDA4`, and 448.0f `0x0056D7C0`.
The underlying rectangle-circle primitive has independently reconstructed
source (`src/RectangleCollisions.cpp`); no fake abbreviated geometry routine
is used. Both actual calls are included within the original 707B body.

Only if **both** complete tests return true does the method increment the
returned count, increment the Controller's actual `cancel_counter` at
+`0x286D88`, assign the original incoming low two cancel effect bits to the
native `BulletFlags::fields.effect_mode` (bits 11..12), and invoke the
real `Bullet::cancel(mode)` at `0x0047C8F0`. That **662-byte** callee is
separately and correctly declared but remains *nonexact*. The full native
iterator destructor, security-cookie check, and `ret 0x14` are reproduced.

## Native instruction/codegen audit

The first entire natural prototype emitted **712B** versus target **707B**.
Replacing true `0.0f` operands with external variable reads was one cause of
the compiler emitting `movss` instead of the original `xorps` instructions.
More importantly, expressing the two collision tests as a conventional
combined positive `if` gave **702B**, and two explicit `continue`s gave
**708B**. The original is reproduced by one natural short-circuit rejection
`if (!(first_rectangle_circle && second_rectangle_circle)) continue;`.
This leads to the complete original native **707B/209-instruction** flow,
including SSE zero generation and the final iterator-advance branch, with
**607/607 non-relocation bytes identical** before replay.

The locked MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` canonical compile and strict replay produced
**707/707 complete original bytes** with **all 25 independently anchored
native relocation offsets/types/destinations**, including real Vector3
constructors/operators, 669B rectangle-circle twice, original Bullet
cancellation child, native List/Iterator/EH and all native float objects.
No native machine-code copying, arbitrary padding or relaxed comparison.
Focused log: `.analysis/core235-bullet-rectangle-cancel-replay.log`.

Adding one typed method to shared `src/Bullet.hpp` affects **16 older source
objects containing 53 earlier accepted exact units**. All 53 were freshly
compiled and full canonical strict replayed with zero byte or original-target
regressions. Only MSVC-private diagnostic literal local `$SG` numbers moved:
BulletController `$SG85493` -> `$SG85499`; four Dialogue locals
`$SG117838..117841` -> `$SG117844..117847`, with all native original
data relocation targets unchanged. Together with the new boss this scoped
replay passes **54/54 exact units, 17 fresh cold objects**. No unfiltered
whole-graph cold replay ran. Full include-affected log:
`.analysis/core235-bullet-header-closure-replay.log`.

The 662-byte native `Bullet::cancel` body, 3,735-byte native
`BulletController::emit`, and 41,967-byte Enemy opcode dispatcher remain
nonexact; neither this full caller nor its exact geometric and typed
iterator dependencies implies a complete game link/runtime.
