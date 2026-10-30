# CORE/RECON-986 — original entire 280B Graphics viewport switch whole strict exact, shared 806B category ABI

Original immutable Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The actual game-owned `0x0044F720` is the entire **280B/66-i386**
Graphics viewport selection method. It takes a mode index and an
original second argument, selects the actual
`Graphics::viewports[index]` (native **0x16C** stride beginning at
Graphics `+0x278`), writes the real `Graphics::current_viewport`
member at **`+0xB00`**, forces the original second parameter word to
zero, invokes two original viewport setup methods and calls the
Direct3D9 device's **real `SetViewport` vtable entry `+0xBC`** with
the actual selected `adjusted_viewport` member at **`+0x104`**.
It then publishes the original selected X/Y origin and first 8-byte
point components to four current AnimationPool state words at
`+0xD0/+0xD4/+0xC8/+0xCC`. The source uses real typed viewport
and pool members; no dynamic owner allocation is inferred.

## Independent original PE and correct 806B caller symbol

[`scripts/verify-animation-graphics-viewport-switch280-native.py`](../scripts/verify-animation-graphics-viewport-switch280-native.py)
authenticates all 280 original PE bytes with native body SHA-256
`a1b8abddc5be4d6aa2f0745d27bb8f1752f47c2644eafd364e0154aecbfa4d18`,
all 66 instructions through actual `ret 8`, the 0x16C index
multiplication, native `+0xB00` current pointer, real D3D9 virtual
call slot, signed int-to-float `cvtsi2ss/movss` for X/Y, and two
separate original eight-byte indexed point accesses. It verifies
**every actual E8/HIGHLOW original field and physical destination**:

| Native original role | Actual original destination |
| --- | --- |
| E8 `+0x47` | **`0x004DA1F0`**, native viewport preparation with two original pointer parameters |
| E8 `+0x59` | **`0x004DA120`**, native Graphics device/viewport preparation |
| 4 HIGHLOW `+0xA1/+0xBF/+0xDD/+0x101` | Actual `current_animation_pool` global at **`0x005C0028`**, used independently for all four pool-view writes |
| Four original parent E8 | `0x0044F3E8`, `0x0044F485`, `0x0044F4CA` and `0x0044F50F` in the independently exact **806B** category Boss, all physically targeting `0x0044F720` |

The maintained [`src/NativeGraphicsModeAction.hpp`](../src/NativeGraphicsModeAction.hpp)
consolidates **one Graphics ABI class view** shared by
[`src/AnimationGraphicsViewportSwitch280.cpp`](../src/AnimationGraphicsViewportSwitch280.cpp)
and the previously whole exact
[`src/AnimationRendererClassificationAction806.cpp`](../src/AnimationRendererClassificationAction806.cpp).
This is important for linking: a private first 280B prototype used
the alternate decorated symbol `NativeGraphicsViewportSwitch`,
which cannot be silently substituted for the 806B caller's real
`NativeGraphicsModeAction::set_mode_44f720` C++ symbol. The actual
maintained source instead uses **one identical decorated callee
symbol for both caller and callee** and adds no new Graphics fields.

The first C++20 source already naturally compiled the complete
**280B/66 instructions, 256/256 original nonrelocated bytes plus all
six physical relocation roles**. The shared-header refactoring
recompiled both the maintained 280B callee and 806B game parent and
preserved their whole original results. Pinned MSVC 19.44 x86
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
original-target-bound affected-only strict replay:

```text
animation_graphics_viewport_switch_280: exact (280/280 bytes)
animation_renderer_classification_action_806: exact (806/806 bytes)
animation_renderer_classification_dispatch_347: exact (347/347 bytes)
animation_renderer_classify_primary_382: exact (382/382 bytes)
animation_renderer_classify_secondary_394: exact (394/394 bytes)
animation_renderer_staging_apply_230: exact (230/230 bytes)
Exact replay: 6/6 units, 5 cold objects
```

This adds **one distinct original game-authored head/+280 unique
`.text` bytes**. Existing 806B/347B/382B/394B/230B owners and
separate original Graphics helper subcalls are not counted again;
other original Graphics mode setup methods and the 5,993B draw Boss
remain separate unfinished work. No global cold replay or claim of
a linked/playable whole game.

```bash
scripts/repo-python scripts/verify-animation-graphics-viewport-switch280-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationGraphicsViewportSwitch280.cpp --source src/AnimationRendererClassificationAction806.cpp --source src/AnimationRendererClassifyDispatch347.cpp --source src/AnimationRendererClassification382394.cpp --source src/AnimationRendererStagingApply230.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
