# CORE/RECON-985 — complete original 806B Renderer classification/Graphics state Boss whole strict exact

Immutable original Japanese TH20 Steamless v1.00a executable SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Original `0x0044F3D0` is the entire **806B/211-i386 game-authored**
Renderer/Graphics category action invoked at genuine physical E8 sites
`0x00449EDE` and `0x00449F3D` by the previously strict-exact
[347B classification dispatcher](ANIMATION_RENDERER_CLASSIFY_DISPATCH347_STRICT_EXACT.md).
It handles original category values (including `0x29`, `0x2B/2C`,
`0..2`, `0x27..2A`, `3..5`, `6..11`, `12..19`, `20..23`, `24..25`,
`26..31`, special `0x20/21` and `0x31/32`) with ordered real
category/state branches. The actual game state word is at its
`AnimationPoolOwner` receiver **`+0x6C0`**; state updates are based
on category, Renderer view index and the previously applied state.
The source chooses real Graphics mode/clip actions and, on selected
transitions, performs six native vector-zero stores to the
current pool's float fields `+0xC8/+0xCC`.

## Immutable original PE, full 50 relocation roles

[`scripts/verify-animation-renderer-classification-action806-native.py`](../scripts/verify-animation-renderer-classification-action806-native.py)
independently checks the original complete body digest
`3163fb22930062a9c9f47de053878fd1a6da02af53ad5c8e393d6350e01f9019`,
**all 211 i386 instructions through the real `ret 8`**, eight following
original `INT3` alignment bytes, and **every single physical original
call field and actual native target**:

| Original native roles | Independently verified physical targets |
| --- | --- |
| **22 real E8 sites** | 0x0044F720 (four calls), 0x0044F700 (two calls), 0x0041DCE0 (three), 0x004DDA60 (five), 0x004DDF80 (four), 0x004D9DB0 (four), with original ordering and operand layout |
| **22 Graphics PE HIGHLOW** | Every individual source `Graphics` member call receiver is the direct original global at **`0x005C4D40`**, not a cached helper/function result |
| **6 AnimationPoolOwner PE HIGHLOW** | Genuine original pool pointer global **`0x005C0028`**; native two separate owner references around each of three selected float-zero update groups |
| Native category state | Compare actual original category literals and use original receiver word at **`+0x6C0`** |
| Native zero stores | Exactly six original `xorps xmm0,xmm0` followed by six original `movss`, writing actual float fields `+0xC8/+0xCC` |
| Parent calls | Original 347B dispatcher E8 at `0x00449EDE` and `0x00449F3D` both target complete **806B** method head |

Ghidra's generic function labels were treated as hypotheses, not
proof. The actual branches/offsets/call addresses are independently
checked against immutable PE bytes.

## Full natural C++20 source and compiler experiments

[`src/AnimationRendererClassificationAction806.cpp`](../src/AnimationRendererClassificationAction806.cpp)
uses the existing authentic [`Graphics`](../src/Graphics.hpp) owner,
`process_graphics` global, the single previously accepted
[`NativeRendererClassificationOwner`](../src/NativeRendererClassificationOwner.hpp)
class, and `current_animation_pool`. A non-owning
`NativeGraphicsModeAction : Graphics` local ABI view declares only
observed native external method symbols; it adds **no storage or
ownership claim**. Each `Graphics` call uses a direct reference to
`process_graphics` and each native state comparison/store recomputes
the genuine receiver's `+0x6C0` field. No fabricated dummy calls,
manual NOPs, inline assembly or patched original machine bytes.

The first semantic C++20 whole-function source produced **850B/249
instructions**, but cached Graphics through a non-inlined `/Od`
helper, adding 22 *non-original* E8 calls. Replacing those with direct
Graphics receivers produced **751B/214 instructions** and correct
**22 E8/28 HIGHLOW counts**, but an incorrect saved reference to
`state_6c0` still generated the wrong frame and code. Restoring each
real `this+0x6C0` member access removed the synthetic local and
naturally produced **806B/211 i386, 606/606 matching nonrelocated
bytes, all 22 native E8 and all 28 native HIGHLOW fields**. This
preserves the original source semantics and full linker symbol roles.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` original-target-bound replay includes all
local Renderer classification parents and the other newly completed
230B staged draw receiver:

```text
animation_renderer_classification_action_806: exact (806/806 bytes)
animation_renderer_classification_dispatch_347: exact (347/347 bytes)
animation_renderer_classify_primary_382: exact (382/382 bytes)
animation_renderer_classify_secondary_394: exact (394/394 bytes)
animation_renderer_staging_apply_230: exact (230/230 bytes)
Exact replay: 5/5 units, 4 cold objects
```

Credits **one distinct original game-authored whole exact head/+806
unique `.text` bytes**. Existing 347B/382B/394B/230B Renderer
functions and folded Graphics helpers are not counted twice.
The separate 280B Graphics mode setup, 5,993B Animation draw Boss,
508B/511B active-list update, 2,884B particle Update, and
39,470B Animation VM remain independently unfinished. No full
cold replay, whole-game link or playability claim.

```bash
scripts/repo-python scripts/verify-animation-renderer-classification-action806-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRendererClassificationAction806.cpp --source src/AnimationRendererClassifyDispatch347.cpp --source src/AnimationRendererClassification382394.cpp --source src/AnimationRendererStagingApply230.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
