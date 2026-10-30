# CORE/RECON-978 — entire 59B GameController-gated Renderer update whole strict exact

Immutable original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original `0x00450880` is the complete **59B/18-i386** game-owned
Renderer animation update gate. It uses the real existing global
`current_game_controller` at original physical address `0x005BA828`,
checks its independently accepted `GameController::update_suppressed()`
and `GameController::animation_frozen()` accessors, and returns native
integer 1 when both gates are active. Otherwise it forwards its real
`AnimationPoolOwner*` stack argument to the independently
[150B exact Renderer update wrapper](ANIMATION_RENDERER_UPDATE150_STRICT_EXACT.md),
which in turn calls the still **NONEXACT** 508B Animation list-update
Boss `0x00449870`. A source-level wrapper never credits its unverified
transitive child.

The original-only
[`scripts/verify-animation-renderer-update-gate59-native.py`](../scripts/verify-animation-renderer-update-gate59-native.py)
verifies all 59 original PE bytes, 18 x86 instructions through the
actual `ret`, three genuine E8 site/destination pairs
`+0x12 -> 0x00424030`, `+0x21 -> 0x00424060` and
`+0x34 -> 0x004497D0`, and **all three real PE HIGHLOW**
`+0x05/+0x0E/+0x1D -> 0x005BA828`. The real `test/je` short
circuit and fixed return 1 are independently checked, not assumed
from earlier Ghidra pseudo-C signatures.

[`src/AnimationRendererUpdateGate59.cpp`](../src/AnimationRendererUpdateGate59.cpp)
uses the existing maintained `GameController` type and the same
[`NativeAnimationRendererUpdate`](../src/NativeAnimationRendererUpdate.hpp)
return/call ABI declaration as the 150B callee. Its *first*
ordinary C++20 probe emitted all **59B/18-i386 and 35/35
nonrelocated original bytes**, with the actual decorated symbols and
six original relocations; no raw PE copy, manual opcode or padding.
Pinned MSVC 19.44 x86 `/std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` local replay:

```text
animation_renderer_update_gate_59: exact (59/59 bytes)
animation_renderer_update_150: exact (150/150 bytes)
Exact replay: 2/2 units, 2 cold objects
```

This adds **one game-authored whole exact function /59 original `.text`
bytes**; preexisting GameController predicates, 150B Renderer wrapper
and still-NONEXACT 508B list-update receive no additional credit.
No full project cold replay and no claim of a fully linked/playable game.

```bash
scripts/repo-python scripts/verify-animation-renderer-update-gate59-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRendererUpdateGate59.cpp --source src/AnimationRendererUpdate150.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
