# CORE/EXACT-251/252 — complete Bullet physics/collision step and AnimationHandle position chain

The immutable Japanese TH20 v1.00a Steamless executable is the native
source of truth; whole-file SHA-256 is
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Four complete, independent native game bodies are now maintained as normal
typed C++20 and accepted by strict original-byte comparison. Method names
and external owner spellings are source inferences; their real call ABIs,
object offsets, full native extents and original relocation targets are
reviewed separately. The source contains no copied game byte arrays,
inline assembly, compiler padding or fake Renderer allocation layout.

| Complete game-owned source method | Native entry | Original bytes | Original relocations | Strict canonical result |
| --- | --- | ---: | ---: | ---: |
| `Bullet::step_update()` | `0x0047D960` | **211** | **6** | **211/211** |
| `AnimationHandle::operator!=(std::uint32_t) const` | `0x0047C650` | 45 | 0 | 45/45 |
| `AnimationHandle::set_position(const Vector3&)` | `0x004502C0` | 35 | 2 | 35/35 |
| `AnimationPoolOwner::set_handle_position(std::uint32_t, const Vector3&)` | `0x00450270` | 66 | 1 | 66/66 |

**Four complete functions, 357 original native bytes and nine independently
verified original relocation fields.** Their original body SHA-256 values
in the same order are
`6d46080b1c511285c889b85b719bb8697f6cccf03e02d110c49d4632fd489e72`,
`265da2cd9d6f36a7efaef3e7f56d03cc303c1e383bc5ecede5f96f4daf22e62b`,
`2bc04027386f98022b2fce13d9c1c1352a3eaf833e0c865d24a65d7a4b73b202`,
and `c8e9ce6adb77a63c29b213f4f92ac76dae8531e06d374b21041f5918d2e67281`.

## Complete original 211-byte Bullet physics/collision state boss

The entire `0x0047D960..0x0047DA32` body contains **73 real x86
instructions**. The normal member `Bullet::step_update()` first checks
true `BulletFlags` bit 10 and, if clear, runs the separate full **1,846B**
native `Bullet::update_physics` child at `0x00485B60`, returning -1 if
that child reports failure. It then tests the real 4-byte
`AnimationHandle::operator!=(0u)` at `0x0047C650` and conditionally
writes the Bullet's complete position `Vector3` to that handle through
native `0x004502C0`.

The original branch on integer Bullet state tests state **2** first.
For state 2 it uses the real `Timer::at_least(8)` on the Timer at
Bullet+`0x4F8` (`0x004235C0`), then calls the original native
**2,018-byte** `Bullet::process_collision(0)` at `0x00484A20`, breaking
out of the collision dispatch only if the returned integer is one.
State **1** and the incomplete state-2 case share the low-word bit-9
collision permission check; when bit 9 is clear, the same real 2,018B
collision method is called again. At the end the method clears exactly
Bullet flags bit 10 (`~0x400u`) and returns 0.

The original 211B member was repeatedly compiled in historical
CORE/REVIEW-221 full-body probes but the closest natural `switch` source
emitted **212 bytes**, with exactly one surplus compiler NOP after the
second collision call. New whole-body compiler tests of actual C++
short-circuit semantics (not a copied opcode or a synthetic padding
statement) establish that the original call can appear as the
conditional subexpression `eligible && process_collision(0)`, whose
boolean result is unused but whose **conditional side effect** is real.
The final whole source in `src/BulletStep.cpp` generates exactly **211B**,
all **73/73 original instruction mnemonics** and all **187/187
non-relocation bytes**, with six original relocation sites matching:

- `+0x1B` to native 1,846B Bullet physics at `0x00485B60`;
- `+0x3A` to real 45B handle comparison at `0x0047C650`;
- `+0x59` to real 35B handle position update at `0x004502C0`;
- `+0x87` to actual Timer age test at `0x004235C0`;
- `+0x98` and `+0xB7` to the **same whole** 2,018B collision boss at
  `0x00484A20`, with the second result deliberately unused.

The machine code spans the complete original native return/epilogue.
No individual case arm is counted as a function. The exact unit is
`[units.bullet_step_update]`, with reproducible proof in
`.analysis/core251-step-canonical-replay.log`.

## Three separately exact authentic animation-handle methods

The genuine `AnimationHandle` remains exactly **four bytes**. Its native
`operator!=(std::uint32_t)` compares the live `value` with the supplied
integer and emits the native full bool return protocol; the complete
45B function has zero relocations. The 35B wrapper reads that real handle
value and forwards it, plus the full incoming `Vector3`, through the
actual `current_animation_pool` pointer at **`0x005C0028`** to the
native Renderer method `0x00450270`. Both original relocations match.

The original 66B `AnimationPoolOwner::set_handle_position` then calls the
real **456-byte** owner handle resolver `0x0044CD00`. The latter's return
pointer is an actual `Animation*`, but its complete Renderer owner
implementation is not claimed as exact. On null the 66B method performs
an early return; on a non-null result it copies **all three 32-bit lanes**
of the position to the actual `Animation::vector_5bc` at `+0x5BC`.
The first natural `if (animation != nullptr)` attempt emitted 64B;
restoring the semantically equivalent and compiler-original normal
guard `if (animation == nullptr) return;` generated exactly **66/66
bytes**, including the original 2-byte short jump and the real call
relocation to `0x0044CD00`. The source is one normal translation unit,
`src/AnimationHandlePosition.cpp`; the two manager methods are narrow
external ABI declarations in the existing shared
`src/AnimationRuntimeOwner.hpp`, with no invented giant owner structure.
The three strict objects reside under `[units.animation_handle_ne]`,
`[units.animation_handle_set_position]`, and
`[units.animation_pool_set_handle_position]`; their complete new-object
strict proof is
`.analysis/core252-animation-handle-position-canonical-replay.log`.

## Actual changed-header closure, strict replay and remaining bosses

The new `Bullet.hpp` and `AnimationHandle.hpp` declarations require the
**true compiler-receipt include-closure union of 80 old source objects and
399 previously exact native units**, all replayed source-by-source with
locked MSVC 19.44 x86 `/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` and `nice -n 15`.
**399/399 old units** retain complete strict native equality. Private
MSVC `$SG` diagnostic labels were adjusted only after verifying that
all original relocation offsets, types and native destination addresses
were unchanged; source-specific replays then passed. Separate 35/66B
Renderer method declarations touch `AnimationRuntimeOwner.hpp`, whose
actual receipt closure is **four of those already listed source objects
and eight exact units**. These four were recompiled once more after the
last header change and **all 8/8 remained exact**, including the recently
admitted complete **662-byte** `Bullet::cancel` boss. The original one
private Bullet cancel string `0x0056FD14` retained its relocation site
and destination and was checked after its compiler-private `$SG` symbol
changed.

Including the new **211+45+35+66** complete functions, this batch
strictly validates **403/403 old and new exact native units across 82
distinct freshly compiled source-object providers**, with four of the
80 old providers additionally recompiled for the Renderer declaration.
There is **no unfiltered full-repository cold replay**. Original
locked-executable SHA is unchanged. Scoped logs:
`.analysis/core251-bullet-step-affected-replay-part-{0..6}.log`,
`.analysis/core251-step-canonical-replay.log`, and
`.analysis/core252-runtimeowner-scoped-replay.log`.

The original **1,846-byte** physics (`0x00485B60`), **2,018-byte**
collision (`0x00484A20`), **273-byte** group draw, **3,735-byte**
Bullet emitter, **12,140-byte** Bullet update, and **41,967-byte**
Enemy opcode dispatcher remain **separate nonexact complete bodies**.
These new exact methods are real dependencies, not a claim that any of
those larger roots has become exact or that the whole game links/runs.
