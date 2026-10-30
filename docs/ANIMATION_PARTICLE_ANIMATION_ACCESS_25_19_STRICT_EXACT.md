# CORE/RECON-967 — original 25B Timer and 19B color accessors whole strict exact

Original immutable Japanese TH20 Steamless v1.00a executable SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Two distinct game-specific `Animation` accessors used by the
original, still-nonexact [2,884B particle Update Boss](ANIMATION_PARTICLE_GRID_UPDATE_2884_TEMP_GHIDRA_AND_TYPED_FRONTIER.md)
are independently restored:

| Native original | Physical program roles | Exact bytes |
| --- | --- | --- |
| `0x0045D0A0`, **25B/10-i386** | Genuine `Animation+0x4D8` Timer member integer conversion, original E8 `+0x10 -> 0x0040FF90` (existing folded `Timer::operator int`), no HIGHLOW; direct original 2,884B caller E8 at **`0x0045CC7D`** | **25/25** |
| `0x0045D0E0`, **19B/9-i386** | Genuine four-byte `AnimationBase::color_490` reference at offset **`+0x490`**; zero E8/HIGHLOW; direct original 2,884B caller E8 at **`0x0045C713`** | **19/19** |

Ghidra inaccurately labeled the original 25B function as `void`, but
its actual code returns the Timer's integer value in EAX; the original
19B method returns a pointer/reference to a game-specific color word.
[`scripts/verify-animation-particle-animation-access-native.py`](../scripts/verify-animation-particle-animation-access-native.py)
checks both **whole original PE bodies**, actual x86 instructions/returns,
relocations, real owner field offsets and their distinct parent E8 sites.

The maintained
[`src/NativeParticleAnimationAccess.hpp`](../src/NativeParticleAnimationAccess.hpp)
uses the already independently verified `Animation` class, adds no
storage (size equality is asserted), and declares both actual
member-return ABIs. The natural
[`src/AnimationParticleAnimationAccess.cpp`](../src/AnimationParticleAnimationAccess.cpp)
uses the real typed `timer_4d8` and `base.color_490`; it introduces
neither a conflicting fake Animation class nor handwritten machine code.
Locked MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` reproduces complete code with authentic native
relocation roles. Original-target-bound replay:

```text
animation_particle_age_timer_25: exact (25/25 bytes)
animation_particle_color_ref_19: exact (19/19 bytes)
Exact replay: 2/2 units, 1 cold object
```

This adds **two distinct original authored game functions /44 `.text`
bytes** without double-counting the previously exact folded Timer
callee `0x0040FF90`. Their game-owned source identities are now
available for the 2,884B original Update C++ research probe; that
**enclosing Boss remains NONEXACT** and is not credited. No unfiltered
whole-graph cold replay ran.

```bash
scripts/repo-python scripts/verify-animation-particle-animation-access-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationParticleAnimationAccess.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
