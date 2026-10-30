# CORE/RECON-950 — complete 92B 200-handle particle-grid virtual stop method strict exact

Locked original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original `0x0045CEB0` is a complete game-authored **92B/32-i386**
virtual method in the real **0x1940-byte 200-particle polymorphic group**,
pointed to by slot 3 of its genuine PE-relocated vtable `0x0056EC14`.
The already independently exact
[172B constructor](ANIMATION_PARTICLE_GRID_GROUP_CTOR172_STRICT_EXACT.md)
initializes its 200 four-byte `AnimationHandle` cells at `+0x08`.

## Original-only physical native proof

[`scripts/verify-animation-particle-grid-stop92-native.py`](../scripts/verify-animation-particle-grid-stop92-native.py)
reads only the original target PE and authenticates the full 92B return
boundary, all 32 x86 instructions, the actual 200-element signed loop,
**three original E8 site/target pairs**, **zero in-body HIGHLOW**,
and the physical vtable slot:

| Original E8 | Real destination | Semantics |
| --- | --- | --- |
| `+0x34` | `0x00414580` | Folded native indexed four-byte cell accessor, same physical Vector3::operator[] head |
| `+0x3B` | `0x0044CED0` | Native `AnimationHandle::resolve()` for current cell |
| `+0x4E` | `0x0044FD00` | Original `Animation::stop()` for non-null resolved instance |

The native method skips an unresolved handle and continues through all
200 entries, returning zero when finished. The body has a real `NOP`
after the stop call, naturally emitted by MSVC without source padding.

## Actual natural MSVC bytes and important relocation-identity correction

The first typed expression stored a temporary `AnimationHandle*` before
calling `resolve()`. It compiled to **96B/33 i386**, adding an
unnecessary four-byte pointer local. The genuine expression in
[`src/AnimationParticleGridStop92.cpp`](../src/AnimationParticleGridStop92.cpp)
combines native indexed cell addressing and `resolve()` directly;
pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` naturally emits **92B/32 i386**.

A first strict manifest draft mistakenly used `QAEPAUAnimation` in the
`AnimationHandle::resolve()` symbol, although the real declared type
returns an `Animation*` **class pointer**, whose actual MSVC symbol is
`?resolve@AnimationHandle@th20@@QAEPAVAnimation@2@XZ`. The error
caused relocation validation to reject the otherwise correct object;
it was corrected by inspecting the real COFF symbol and the existing
`AnimationHandle.hpp` declaration, **not** by re-labeling a different
physical original address. All three original E8 targets are maintained:

```text
animation_particle_grid_stop_92: exact (92/92 bytes)
Affected 172B ctor, 49B deleting wrapper, 156B factory and 47B creation: all exact
Exact replay: 5/5 units, 4 cold objects
```

This contributes **one new original game-authored strict function /92
native `.text` bytes**. The original 51B virtual event handler and the
large virtual update remain separate unresolved original bodies; the
exact stop method does not imply exactness for those functions or a
working linked game. No full cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-particle-grid-stop92-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationParticleGridStop92.cpp --source src/AnimationParticleGridGroupCtor172.cpp --source src/AnimationParticleGridGroupFactory156.cpp --source src/AnimationParticleGridCreate47.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
