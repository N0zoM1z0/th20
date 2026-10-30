# CORE/RECON-968 — original complete 108B and 127B AnimationHandle child-query path strict exact

Locked Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Two original game-authored functions in the Renderer/AnimationHandle
lifecycle are now independently full **original strict exact**:

- **108B/37-i386 `0x0044C830`** — on a live `Animation`, call the
  already strict-exact original **241B `Animation::find_child`** with
  identifier and ordinal. If found, return the child's true
  `AnimationHandle`; otherwise construct an actual zero Handle and
  return it by value.
- **127B/45-i386 `0x0044C7B0`** — on an actual `AnimationHandle`,
  invoke `AnimationHandle::resolve()` (including its native stale-ID
  behavior), produce a zero Handle fallback, and if a live Animation
  resolves, call the separately exact 108B child-query above. The
  source-level **conditional expression returning a class by value**
  naturally induces exactly the original hidden return-object pointer
  and native branch/local-copy behavior.

## Complete original executable proof

[`scripts/verify-animation-child-handle-lookup108127-native.py`](../scripts/verify-animation-child-handle-lookup108127-native.py)
checks all 108/127 original PE bytes through their native `ret 0xC`,
full 37/45-i386 disassembly, the exact original **nine E8 site/target
pairs** (four inside 108B and five inside 127B), the original
security-cookie **HIGHLOW `+0x07 -> 0x005B25C0` on each**, and four
and one physically original `INT3` alignment bytes beyond the
respective function returns.

The actual child/parent source graph is:

| Physical original source | Real original E8 destinations |
| --- | --- |
| `0x0044C830` 108B | `+0x1E -> 0x0044C6B0` already exact `Animation::find_child`; `+0x42 -> 0x00425CC0` real Handle constructor; `+0x4C -> 0x004117A0` folded integer assignment; `+0x61 -> 0x005429EE` cookie verifier |
| `0x0044C7B0` 127B | `+0x16 -> 0x00425CC0` Handle ctor; `+0x1E -> 0x0044CED0` real handle resolve; `+0x2B -> 0x004117A0` zero assignment; `+0x46 -> 0x0044C830` exact 108B child query; `+0x74 -> 0x005429EE` cookie verifier |

[`src/NativeAnimationChildHandleLookup.hpp`](../src/NativeAnimationChildHandleLookup.hpp)
uses two zero-added-storage views of the real maintained `Animation`
and `AnimationHandle` classes, with original-sized class assertions,
and a **single shared declaration** for the two methods. The complete
[`src/AnimationChildHandleLookup108127.cpp`](../src/AnimationChildHandleLookup108127.cpp)
contains ordinary typed C++20 class-value results and legitimate
`find_child`/`resolve` calls, not synthetic hidden `void*` outputs,
manual stack manipulation, inline assembly or copied bytes.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` naturally emits the original 108B/37 and
127B/45 bodies, **88/88 and 103/103 identical nonrelocated bytes**, all
actual original relocations and correct native returns. Separate
canonical original-bound relocation-aware cold replay:

```text
animation_child_handle_lookup_108: exact (108/108 bytes)
animation_child_handle_forward_127: exact (127/127 bytes)
Exact replay: 2/2 units, 1 cold object
```

Adds **two distinct original game-authored whole-exact function heads
/+235 `.text` bytes**, without double-crediting the existing 241B
find-child, 51B handle-resolve or SDK-style folded helpers. This does
**not** imply entire RendererPool allocation, 2,884B particle Update,
39,470B Animation VM or a linked/playable whole game. No project-wide
cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-child-handle-lookup108127-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationChildHandleLookup108127.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
