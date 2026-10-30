# CORE/RECON-956 — original complete 57B Animation Vector3 interpolation forwarder strict exact

Locked Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0045D150` is a complete game-owned **57B/24-i386**
Animation interpolation configuration forwarder. It is called twice
inside the original 2,884B particle-grid virtual Update Boss at
original E8 `0x0045CBA5` and `0x0045CE34`. The function operates on
**Animation+0x8C**, the genuine `VectorInterpolation` subobject in
`AnimationBase`, not a new allocation or independent interpolation
member. It is distinct from its previously exact
[124B six-parameter callee](ANIMATION_PARTICLE_INTERPOLATION_124_STRICT_EXACT.md).

## Original PE behavior and complete original call evidence

[`scripts/verify-animation-particle-interpolation-forward57-native.py`](../scripts/verify-animation-particle-interpolation-forward57-native.py)
independently verifies all 57 bytes /24 i386 instructions, native
`ret 0x14`, `Animation+0x8C`, `push 8`, the original single E8
**`+0x2D -> 0x0045D190`**, **zero HIGHLOW**, and the two physical
E8 parent sites in the full original 2,884B Update. It preserves the
five incoming arguments in real original order, inserting mode 8 as
the fixed second callee argument and forwarding the four `Vector3`
inputs with the original tangent/endpoint rearrangement.

[`src/NativeAnimationInterpolationConfig.hpp`](../src/NativeAnimationInterpolationConfig.hpp)
now supplies a **single ODR-consistent zero-extra-storage C++ declaration**
shared by this forwarder and the already exact 124B callee. Its
`static_assert(offsetof(AnimationBase,interpolation_8c)==0x8C)` ties
the original member address to the real `Animation` source layout;
there is no second vtable or allocator. The actual natural
[`src/AnimationParticleInterpolationForward57.cpp`](../src/AnimationParticleInterpolationForward57.cpp)
computes this byte offset directly without introducing an unnecessary
intermediate Animation pointer local. The first semantically similar
source using two local owner/pointer variables emitted **64B** and was
rejected, not credited.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` naturally emits all 24 original instructions,
one real 124B callee relocation, and **53/53 nonrelocated bytes**.
Scoped canonical original-target replay of both affected sources:

```text
animation_particle_interpolation_forward_57: exact (57/57 bytes)
animation_particle_interpolation_config_124: exact (124/124 bytes)
Exact replay: 2/2 units, 2 cold objects
```

This credits **one new original game-authored whole exact function /
57 `.text` bytes** without double-crediting the 124B child. The full
2,884B Update is still SOURCE ABSENT / NONEXACT. No graph-wide cold replay.

```bash
scripts/repo-python scripts/verify-animation-particle-interpolation-forward57-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationParticleInterpolationForward57.cpp --source src/AnimationParticleInterpolationConfig124.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
