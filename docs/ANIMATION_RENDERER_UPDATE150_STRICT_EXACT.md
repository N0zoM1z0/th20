# CORE/RECON-976 — original complete 150B RendererPool locked animation-list update bridge strict exact

Immutable original Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x004497D0` is the complete **150B/44-i386**
game-owned RendererPool update wrapper, genuinely receiving its owner
via x86 ECX (`__fastcall`-compatible). It holds process recursive lock
slot **9**, chooses the original first Renderer list at owner `+0x6C8`
using the separately strict **20B/0x48-stride index**
`0x00449490`, calls native **508B/152-i386** Animation list update at
`0x00449870`, destroys the lock and returns original integer 1.
The 508B callee itself is **SOURCE ABSENT / NONEXACT** and receives
**no inferred exact credit** from this 150B wrapper.

## Immutable original PE and ABI evidence

[`scripts/verify-animation-renderer-update150-native.py`](../scripts/verify-animation-renderer-update150-native.py)
checks the entire original 150-byte body through true `ret`, 44 i386
instructions, actual `push 9` lock and `+0x6C8` typed receiver, real
`mov ecx,eax` passing the renderer list without an extra pointer
argument, **every six E8 site and physical original target** and all
**three real PE HIGHLOW site/targets**:

| Original field | Physical native target |
| --- | --- |
| DIR32 `+0x06` | `0x0056808D` genuine MSVC EH descriptor |
| DIR32 `+0x15` | `0x005B25C0` real security cookie |
| DIR32 `+0x2E` | `0x005C0240` process lock registry |
| E8 `+0x32/+0x3B/+0x75` | `0x0040C310/0x0040B730/0x0040B900` lock slot + guard ctor/dtor |
| E8 `+0x57` | `0x00449490`, actual first 0x48-stride Renderer slot lookup |
| E8 `+0x5E` | `0x00449870`, the **separate full 508B NONEXACT update Boss** |
| E8 `+0x8D` | `0x005429EE`, original security-cookie verifier |

[`src/NativeAnimationRendererUpdate.hpp`](../src/NativeAnimationRendererUpdate.hpp)
provides one shared declaration for this new exact wrapper and the
still-under-investigation 508B loop. The natural
[`src/AnimationRendererUpdate150.cpp`](../src/AnimationRendererUpdate150.cpp)
uses the already accepted `NativeRendererPoolSelector` view and the
actual `std::lock_guard<std::recursive_mutex>` source protocol.
No false padded owner class, custom x86, fake NOP or target edit.

The first full C++ candidate stored the native renderer-list pointer
in an extra local, causing an incorrect **154B** function despite the
right number of calls. Forwarding the real typed return expression
directly to the `__fastcall` 508B callee naturally uses ECX and emits
all original **150B/44 instructions**, 114/114 nonrelocated byte
matches, with genuine EH/cookie/lock physical roles. Pinned MSVC
19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc` and original-target-bound scoped replay:

```text
animation_renderer_update_150: exact (150/150 bytes)
Exact replay: 1/1 unit, 1 cold object
```

Credits **one original game-authored whole-exact native head/+150
`.text` bytes**. The 20B Renderer index is library-like and already
mapped; it is not recredited. The 508B update and its 411B recursive
queue callee, 39,470B Animation VM, and full linked executable remain
separate unfinished work. No project-wide cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-renderer-update150-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRendererUpdate150.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
