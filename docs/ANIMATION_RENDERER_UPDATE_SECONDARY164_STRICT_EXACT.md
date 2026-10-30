# CORE/RECON-979 — original 164B locked Renderer secondary animation-list update strict exact

Immutable original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original `0x00449A70` is a whole **164B/46-i386** game-owned
Renderer update bridge, paired with independently exact
[150B original primary update](ANIMATION_RENDERER_UPDATE150_STRICT_EXACT.md).
It accepts the real renderer pool via ECX, holds process mutex slot **9**,
sets native pool status word `+0xD8` to 0, selects first 0x48-stride
Renderer record from the pool's real `+0x6C8` array, invokes the
separate **511B/150+ instruction** secondary Animation list-update
at `0x00449B20`, destroys the mutex and returns integer 1.
**That 511B callee remains SOURCE ABSENT / NONEXACT**.

[`scripts/verify-animation-renderer-update-secondary164-native.py`](../scripts/verify-animation-renderer-update-secondary164-native.py)
reads the original PE and validates the **entire 164B/46-i386**, real
`ret`, original lock index, member offsets, **all six native E8
physical instructions and target addresses**, **all three actual PE
HIGHLOW fields**, and original seven `INT3` alignment bytes:

| Original field | Physical target and meaning |
| --- | --- |
| HIGHLOW `+0x06` | `0x0056808D`, real original x86 EH handler |
| HIGHLOW `+0x15` | `0x005B25C0`, native security cookie |
| HIGHLOW `+0x2E` | `0x005C0240`, process `LockRegistry` |
| E8 `+0x32/+0x3B/+0x83` | `0x0040C310/0x0040B730/0x0040B900`, real recursive lock9 and guard lifetime |
| E8 `+0x65` | `0x00449490`, already accepted native 20B Renderer slot selection/index |
| E8 `+0x6C` | `0x00449B20`, separate still nonexact native **511B** secondary list update |
| E8 `+0x9B` | `0x005429EE`, genuine native security check |

[`src/AnimationRendererUpdateSecondary164.cpp`](../src/AnimationRendererUpdateSecondary164.cpp)
uses the same existing `NativeRendererPoolSelector`, typed
`NativeSpawnRendererView` and `std::lock_guard<std::recursive_mutex>` as
the already accepted 150B Renderer update. Its declarations live in one
[`src/NativeAnimationRendererUpdate.hpp`](../src/NativeAnimationRendererUpdate.hpp).
A natural single pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` probe produced **164B/46 original
instructions**, all **128/128 nonrelocated bytes** and all nine
original physical relocation roles. No handmade instruction padding,
fake memory field or second incompatible Renderer view was needed.

Affected-source original-target-bound local replay:

```text
animation_renderer_update_secondary_164: exact (164/164 bytes)
animation_renderer_update_150: exact (150/150 bytes)
animation_renderer_update_gate_59: exact (59/59 bytes)
Exact replay: 3/3 units, 3 cold objects
```

This contributes **one original game-authored whole function /164
unique `.text` bytes**. Preexisting 59B/150B wrappers, the 20B folded
index and the unresolved 511B list-update callee are **not** credited
again. No full cold replay and no claim of a finished linked game.

```bash
scripts/repo-python scripts/verify-animation-renderer-update-secondary164-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRendererUpdateSecondary164.cpp --source src/AnimationRendererUpdate150.cpp --source src/AnimationRendererUpdateGate59.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
