# CORE/RECON-955 — original 124B Vector3 interpolation config whole strict exact

Locked Japanese TH20 v1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The native original `0x0045D190` is a complete **124B/45-i386**
game-specific six-argument `Vector3` interpolation state setter.
It is called at genuine original E8 `0x0045D17D` from the separate
57B Animation interpolation forwarding wrapper `0x0045D150`, which
in turn is called twice from the full original 2,884B particle Update
Boss. The 57B wrapper remains a separately scoped native method and
is **not inferred exact** from this accepted child.

## Original PE and real data layout

[`scripts/verify-animation-particle-interpolation124-native.py`](../scripts/verify-animation-particle-interpolation124-native.py)
reads original PE bytes and checks all 124B through `ret 0x18`, all
45 original x86 instructions, all **seven native E8 sites AND physical
target addresses**, **zero in-body HIGHLOW**, the original current-value
assignment at `+0x30`, original Timer at `+0x3C` and real parent E8:

| Native E8 | Destination | Actual role |
| --- | --- | --- |
| `+0x0E` | `0x00438E70` | `VectorInterpolation::set_duration` |
| `+0x1A` | `0x004394F0` | `VectorInterpolation::set_mode` |
| `+0x26` | `0x004393F0` | `set_start` with real `Vector3` (physical head folded with Motion's setter) |
| `+0x32` | `0x00438A90` | `set_end` |
| `+0x3E` | `0x00439480` | `set_tangent_start` |
| `+0x4A` | `0x00438B20` | `set_tangent_end` |
| `+0x70` | `0x00423520` | `Timer::operator=(0)` at `+0x3C` |

The genuine `VectorInterpolation` class in `src/Interpolation.hpp`
contains five 12-byte `Vector3` members followed by a 16-byte Timer,
duration and mode: its total size is 84 bytes. The local
`NativeVectorInterpolationConfigView` derives from it without adding
storage, so the tested original `+0x30` current and `+0x3C` Timer are
actual typed existing native offsets. This avoids inventing a second
interpolation runtime layout or changing the shared header.

## Canonical source and strict original-byte proof

[`src/AnimationParticleInterpolationConfig124.cpp`](../src/AnimationParticleInterpolationConfig124.cpp)
uses six ordinary setter/member expressions, one current Vector3 copy,
and a true Timer reset, not hand-emitted code. Pinned MSVC 19.44 x86
C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
produces complete original 124B/45 instructions, all seven authentic
relocation symbols/offsets/targets and **96/96 nonrelocated bytes**:

```text
animation_particle_interpolation_config_124: exact (124/124 bytes)
Exact replay: 1/1 unit, 1 cold object
```

This adds **one original game-authored exact function /124 `.text`
bytes** without double-crediting previously exact setter/Timer callees.
The original 2,884B virtual Update Boss remains source absent and
nonexact; this leaf does not imply its completion. No full cold replay.

```bash
scripts/repo-python scripts/verify-animation-particle-interpolation124-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationParticleInterpolationConfig124.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
