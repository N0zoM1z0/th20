# CORE/RECON-954 — full original 20B 200×Vector3 array index strict exact

Original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0045C2C0` is a complete **20B/9-i386** `std::array<Vector3,200>::operator[]`
with 12-byte stride, original `ret 4`, and **zero in-body relocations**.
It is physically called four distinct times by the real 2,884B particle
Update Boss at `0x0045CBDF`, `0x0045CC32`, `0x0045CDD3` and `0x0045CDF6`.

[`scripts/verify-animation-particle-vector-index20-native.py`](../scripts/verify-animation-particle-vector-index20-native.py)
reads the immutable original PE, verifies the full native instruction body,
no original PE HIGHLOW fields and all four parent E8 physical sites and
target destinations. Those parent calls are independently verified; their
presence **does not prove the parent whole source exact**.

[`src/AnimationParticleGridVectorIndex20.cpp`](../src/AnimationParticleGridVectorIndex20.cpp)
instantiates the genuine C++20 `std::array<Vector3,200>::operator[]`.
A separate first probe using a nominal custom `NativeGridVectorSpan200`
produced an indistinguishable native 20B body, but was **not selected**
because it would guess a separate source owner. Using the actual established
200-element array gives a single consistent original C++ STL method.
Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` and full strict original-bound replay:

```text
animation_particle_grid_vector_index_20: exact (20/20 bytes)
Exact replay: 1/1 strict unit, 1 cold object
```

This adds one source-present matching unit and object but **zero
new game-authored function/byte credit**, because the original C++
STL/template source provenance is `unknown/review`. The 2,884B native
particle Update parent remains SOURCE ABSENT / NONEXACT and no global
cold replay was performed.

```bash
scripts/repo-python scripts/verify-animation-particle-vector-index20-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationParticleGridVectorIndex20.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
