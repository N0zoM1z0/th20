# CORE/RECON-951 — complete original 202B Vector3 normalization whole strict exact

Immutable Japanese TH20 v1.00a Steamless executable SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The native original `0x0045CF10` is a complete **202B/58-i386**
three-coordinate vector normalization/copy operation, taking a real
`Vector3&` result and `const Vector3&` source. This is a custom
in-game epsilon-aware vector policy, not an automatically generated
constructor. The independent game-local callers belong to the Bullet/
Enemy geometry and animation program, but whole-parent exactness is not
inferred from this accepted helper.

## Independent original PE validation

[`scripts/verify-animation-particle-normalize202-native.py`](../scripts/verify-animation-particle-normalize202-native.py)
reads the original binary and authenticates the full 202B function
through `ret`, all **58 i386 instructions**, the genuine original
**two E8 fields/targets**, one actual PE HIGHLOW field/target, the
real original threshold value and the source-level normalization
versus copy branch:

| Original field | Native target | Meaning |
| --- | --- | --- |
| E8 `+0x42` | `0x00446B30` | Independently exact native `scalar_math::square_root(float)` |
| E8 `+0x58` | `0x00445680` | Independently exact native `geometry::absolute(float)` |
| DIR32 `+0x67` | `0x0056E1A0` | Game's real file-backed `0.01f` epsilon (IEEE754 original) |

The original computes three single-precision SSE squares and their
sum, takes its square root and comparison absolute value, then uses
`comiss/jbe` for the native epsilon rule. A magnitude smaller than
0.01f copies all 12 bytes of the input `Vector3` unchanged; otherwise
all three output coordinates are individually divided by the original
magnitude. There are exactly **three SSE `divss` instructions**. The
original low-level threshold and branch are not inferred from a generic
math library implementation.

## Natural maintained source and native strict oracle

[`src/AnimationParticleGridNormalize202.cpp`](../src/AnimationParticleGridNormalize202.cpp)
uses the same original game `Vector3` class, the already accepted
scalar square root and `geometry::absolute` functions, and the
existing true `native_0_01` global. The entire function is natural
ordinary C++20, without padded code, inline assembly, shortened
comparison, or fabricated constants. The first correct source
compiled under locked MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` already produced **202B/58 x86**,
all original **190/190 nonrelocated bytes** and three true COFF fields.
Original-target-bound relocation replay then certified:

```text
animation_particle_grid_normalize_202: exact (202/202 bytes)
Exact replay: 1/1 units, 1 cold objects
```

This adds **one original game-authored exact function /202 native
`.text` bytes**; it does not double-credit either already exact math
callee. The separate virtual 51B event/Timer wrapper in the particle
group and its larger 0x45C360 update remain open, as does complete
whole-game build/link/playability. No full-graph cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-particle-normalize202-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationParticleGridNormalize202.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
