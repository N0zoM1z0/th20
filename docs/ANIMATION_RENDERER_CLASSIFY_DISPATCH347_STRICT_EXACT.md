# CORE/RECON-983 — original complete 347B RendererPool layer classification driver strict exact

Locked Japanese TH20 Steamless v1.00a executable SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x00449E40` is a complete game-owned **347B/105-i386**
RendererPool classification dispatch. Under real recursive lock slot
**9**, it traverses the original first Renderer group within pool
`+0x6C8` using a 0x48-stride Renderer slot lookup. It calls both
previously exact [382B primary/394B secondary category filters](ANIMATION_RENDERER_CLASSIFY382394_STRICT_EXACT.md).
When the filter returns a nonzero match count, it invokes the original
**806B** classification action `0x0044F3D0`, recomputes the Renderer
slot, then applies its staging list with the separate **230B** method
`0x00449FA0`. It repeats the same process for both primary and
secondary classifications and returns integer 1. These **806B/230B
callees are separately NONEXACT** until independently restored.

## Original executable facts and physical call roles

[`scripts/verify-animation-renderer-classification-dispatch347-native.py`](../scripts/verify-animation-renderer-classification-dispatch347-native.py)
verifies the entire immutable original **347B/105 instructions** using
native SHA-256
`387c4cb4d7aa4ff81fde9e8f3ff70453d12f104ad5449948e2b2b2e04fe74122`,
the full original `ret 4`, every **14 real E8 instruction site and
physical target address**, and all **three actual PE HIGHLOW** roles:
`+0x06 -> 0x0056834D` (MSVC EH), `+0x15 -> 0x005B25C0`
(cookie) and `+0x2E -> 0x005C0240` (process lock registry).

| Native E8 offset | Actual original callee |
| --- | --- |
| `+0x32/+0x3B/+0x138` | `0x0040C310`, `0x0040B730`, `0x0040B900`: real lock slot and scoped guard |
| `+0x76/+0xB5/+0xD5/+0x115` | `0x00449490`: true four separate 0x48-stride Renderer lookups |
| `+0x85` | `0x0044A090`: original complete **382B primary** classification |
| `+0xE4` | `0x0044A210`: original complete **394B secondary** classification |
| `+0x9E/+0xFD` | `0x0044F3D0`: original **806B** separate application operation (not yet exact) |
| `+0xBC/+0x11C` | `0x00449FA0`: original **230B** separate staged-link processing (not yet exact) |
| `+0x150` | `0x005429EE`: original security cookie check |

The maintained source
[`src/NativeRendererClassificationOwner.hpp`](../src/NativeRendererClassificationOwner.hpp)
is a zero-new-storage, non-owning view of the existing real
`AnimationPoolOwner`, sharing the already exact three-list
[`NativeRendererClassificationView.hpp`](../src/NativeRendererClassificationView.hpp)
receiver. The full natural
[`src/AnimationRendererClassifyDispatch347.cpp`](../src/AnimationRendererClassifyDispatch347.cpp)
uses the real `NativeRendererPoolSelector`, typed C++20
`std::lock_guard<std::recursive_mutex>` and native one-slot
`for (view=0; view<1; ++view)` control flow. It deliberately computes
four independent original Renderer index calls and keeps the
nonzero returned match count in an ordinary local, rather than
inferring all callee behavior from a decompiler pseudocode label.

The first pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` compilation produced the entire
**347B/105 original machine instructions, 279/279 matching
nonrelocated bytes and all 17 original physical relocation roles**.
No fake padding, manual NOP, PE patch or alternate incompatible
Renderer storage was needed. Actual original-target-bound scoped replay:

```text
animation_renderer_classification_dispatch_347: exact (347/347 bytes)
animation_renderer_classify_primary_382: exact (382/382 bytes)
animation_renderer_classify_secondary_394: exact (394/394 bytes)
Exact replay: 3/3 units, 2 cold objects
```

One new original game-authored whole exact head and **+347 unique
`.text` bytes** are credited, beyond the already separate 776B for
the two classification callees. The 806B/230B functions and any
still larger callers remain independently unfinished and not counted.
No global cold replay, whole-game build/link or playability claim.

```bash
scripts/repo-python scripts/verify-animation-renderer-classification-dispatch347-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRendererClassifyDispatch347.cpp --source src/AnimationRendererClassification382394.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
