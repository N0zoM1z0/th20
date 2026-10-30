# CORE/RECON-987 — original 30B graphics-mode viewport forwarding, shared 806B→280B ABI strict exact

Immutable Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The game-owned `0x0044F700` is the entire **30B/14-i386**
`NativeGraphicsModeAction::set_mode_44f700(int,int)` method. It
forwards both original input words in native x86 calling order to
`NativeGraphicsModeAction::set_mode_44f720` at **`0x0044F720`**, the
independently exact [280B Graphics viewport switch](ANIMATION_GRAPHICS_VIEWPORT_SWITCH280_STRICT_EXACT.md).

The physical original [806B Graphics classification Boss](ANIMATION_RENDERER_CLASSIFY_ACTION806_STRICT_EXACT.md)
calls this 30B method from **two** E8 sites: `0x0044F554` and
`0x0044F6A2`, when transitioning appropriate category modes. Its
single direct E8 target is genuine `0x0044F720` at original offset
`+0x12`. The 30B original code includes an MSVC-emitted `nop` after
that call before the true `ret 8`, with two authentic `INT3` bytes
*outside* its body; there are no PE HIGHLOW relocations.

[`scripts/verify-animation-graphics-viewport-forward30-native.py`](../scripts/verify-animation-graphics-viewport-forward30-native.py)
independently verifies the entire original 30B/14 instructions, true
source/target of all three observed original E8 sites across the two
functions, the postcall `nop`, return convention, zero PE HIGHLOW and
two real subsequent `INT3` alignment bytes. Natural maintained
[`src/AnimationGraphicsViewportForward30.cpp`](../src/AnimationGraphicsViewportForward30.cpp)
uses the same
[`src/NativeGraphicsModeAction.hpp`](../src/NativeGraphicsModeAction.hpp)
as the other accepted 806B/280B C++ sources. The first C++20 source
probe naturally emitted **all 30B/14-i386, 26/26 matching nonrelocated
bytes and the real native 280B callee symbol**, without an inserted
NOP, assembly or patched bytes.

Pinned MSVC 19.44 x86 `/std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` original-target-bound only affected
cold replay:

```text
animation_graphics_viewport_forward_30: exact (30/30 bytes)
animation_graphics_viewport_switch_280: exact (280/280 bytes)
animation_renderer_classification_action_806: exact (806/806 bytes)
Exact replay: 3/3 units, 3 cold objects
```

Adds **one distinct whole-exact game-authored original 30B head/+30
`.text` bytes**; previously accepted 280B/806B functions and their
separate graphics helpers are not counted twice. The remaining
original Graphics internals, 5,993B draw and Animation VM are not
inferred exact. No global cold replay/linked or playable game claim.

```bash
scripts/repo-python scripts/verify-animation-graphics-viewport-forward30-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationGraphicsViewportForward30.cpp --source src/AnimationGraphicsViewportSwitch280.cpp --source src/AnimationRendererClassificationAction806.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
