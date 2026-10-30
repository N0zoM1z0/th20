# CORE/RECON-946 — original two 78B C++ constructors for 200-element color and Vector3 arrays

Locked Japanese TH20 v1.00a Steamless SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Two real original C++20 `std::array` construction helpers in the
`0x0045C130..0x0045C1DD` region have **78B/27-i386** function bodies
followed by **five real `INT3` alignment bytes each**. Native original
`0x0045C190` constructs **200 four-byte AnimationHandle/color words**;
original `0x0045C130` constructs **200 twelve-byte Vector3 elements**.
Their original 172B group constructor physically invokes the first
once at `0x0045C212` and the second twice at `0x0045C220/0x0045C22E`.

[`scripts/verify-animation-particle-grid-arrays200-native.py`](../scripts/verify-animation-particle-grid-arrays200-native.py)
reads the original executable directly, checks all three parent call
locations, authentic 200 count and 4/12-byte stride, all original bytes
through the actual native returns, five true INT3 each, and both
real four-field relocation tables:

| Original body | Real original data/call roles |
| --- | --- |
| `0x0045C190`, color words | HIGHLOW `+0x06 -> 0x00567600` EH, `+0x13 -> 0x005B25C0` cookie, `+0x27 -> 0x00425CC0` 4-byte constructor; E8 `+0x36 -> 0x0040BC20` EH vector construction |
| `0x0045C130`, Vector3 | Same original EH/cookie fields, HIGHLOW `+0x27 -> 0x00422E10` real Vector3 constructor, E8 `+0x36 -> 0x0040BC20` |

The newly typed [`src/NativeParticleGridGroup.hpp`](../src/NativeParticleGridGroup.hpp)
is a single C++ class with independently observed base/vtable and
layout offsets from the original 172B group constructor: colors at
`+0x08`, two Vector3 arrays at `+0x328/+0xC88`, float array at
`+0x15E8`, three extra Vector3 values at `+0x1908/+0x1914/+0x1920`,
float at `+0x192C` and Timer at `+0x1930`, total **0x1940 bytes**.
The natural [`src/AnimationParticleGridArrays200.cpp`](../src/AnimationParticleGridArrays200.cpp)
instantiates both genuine 200-element array default constructors using
`std::construct_at`; there is no fake native code, manual INT3 or
independently conflicting class owner.

Pinned MSVC x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` and original-target-bound strict replay independently verify:

```text
animation_particle_grid_color_array200_78: exact (78/78 coverage bytes; 83/83 compared bytes)
animation_particle_grid_vector_array200_78: exact (78/78 coverage bytes; 83/83 compared bytes)
Exact replay: 2/2 units, 1 cold objects
```

Both likely library-generated bodies remain `origin=unknown/review` and
add **zero original authored-game code bytes**, despite full native
strict exactness. The 172B constructor and 156B allocation factory
need separate independent acceptance. No existing canonical source or
shared header was changed and no global replay was run.

```bash
scripts/repo-python scripts/verify-animation-particle-grid-arrays200-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationParticleGridArrays200.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
