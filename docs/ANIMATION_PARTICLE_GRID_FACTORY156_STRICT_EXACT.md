# CORE/RECON-948 — original 156B/46-i386 0x1940-particle-grid factory strict exact

Original Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The genuine native `0x0045C090` is a **156B/46-i386** C++17
allocation instantiation for the real **0x1940-byte polymorphic
group** whose separately exact [172B constructor](ANIMATION_PARTICLE_GRID_GROUP_CTOR172_STRICT_EXACT.md)
allocates 200 color words, two arrays of 200 `Vector3`, 200 scalar
values, three additional vectors and a Timer. Its real 47B upper
factory/configuration wrapper calls it at original E8 `0x0045D013`.

## Independent original PE and complete relocated replay

[`scripts/verify-animation-particle-grid-factory156-native.py`](../scripts/verify-animation-particle-grid-factory156-native.py)
checks the complete immutable original function's 46 instructions through
`ret 8`, **all four original E8 instruction positions and destinations**,
**both original HIGHLOW positions and actual file-backed targets**, two
real `push 0x1940` operands and its genuine 47B parent E8:

| Original native field | Original destination | Meaning |
| --- | --- | --- |
| E8 `+0x2D` | `0x0054275D` | Native operator new of `0x1940` |
| E8 `+0x4D` | `0x0040C080` | Original MSVC `/sdl` automatic class initialization |
| E8 `+0x56` | `0x0040B280` | C++17 forwarded Animation receiver |
| E8 `+0x6A` | `0x0045C1F0` | Independently whole-exact 172B group constructor |
| DIR32 `+0x06`, `+0x15` | `0x00568897`, `0x005B25C0` | Native EH handler and security cookie |

A first natural `class` source with only scalar `float`/word fields
compiled to **143B**, omitting the original `__autoclassinit2`. A
private isolated C++17 test refined one genuine four-byte field at
`+0x192C` into a **float/pointer-compatible union**. Its float arm
continues to be zero-initialized with the *same original `xorps/movss`
instructions* by the 172B constructor, and the pointer-compatible arm
causes the compiler to classify the object for actual original `/sdl`
class initialization. The resulting factory was **156B/46-i386** and
the independently exact 172B ctor was unchanged. Both full native
relocation sets were checked. The historical pointer arm's runtime
use remains **provisional**, not a proven gameplay/resource ownership
claim; the union is a minimally sized source model of the verified
original four-byte storage and compiler ABI.

The maintained [`src/NativeParticleGridGroup.hpp`](../src/NativeParticleGridGroup.hpp)
keeps the original class size, all validated member offsets and one
consistent class declaration. The natural
[`src/AnimationParticleGridGroupFactory156.cpp`](../src/AnimationParticleGridGroupFactory156.cpp)
instantiates the existing ordinary diagnostic allocator C++17 template;
no explicit fake memset or raw x86 was inserted. Pinned MSVC 19.44 x86
C++17 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
reproduces the entire original relocated code:

```text
animation_particle_grid_factory_156: exact (156/156 bytes)
Previously accepted ctor172, deleting49, color-array78 and Vector3-array78: exact
Exact replay: 5/5 units, 3 cold objects
```

This function remains `origin=unknown/review`, likely a generated
C++ allocator template; it adds **zero authored-game code credit**.
The separate original 47B upper wrapper and virtual update/draw/
interrupt paths remain independent original source reconstruction tasks.
No unfiltered project-wide cold replay was performed.

```bash
scripts/repo-python scripts/verify-animation-particle-grid-factory156-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationParticleGridGroupFactory156.cpp --source src/AnimationParticleGridGroupCtor172.cpp --source src/AnimationParticleGridArrays200.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
