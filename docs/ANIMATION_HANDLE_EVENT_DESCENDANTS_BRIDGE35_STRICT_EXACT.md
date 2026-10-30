# CORE/RECON-990 — original 35B descendant event Handle bridge and corrected 29B caller ABI

Target original Japanese TH20 Steamless v1.00a PE SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original **`0x0044F0D0`** is a complete distinct **35B/15-i386**
game-owned `AnimationHandle` member. It forwards its real four-byte
`AnimationHandle::value` and caller event to `current_animation_pool`
(global at **`0x005C0028`**), invokes the independently full exact
[261B child-event/VM traversal at `0x0044EFC0`](ANIMATION_POOL_EVENT_DESCENDANTS261_STRICT_EXACT.md),
and returns with original x86 `ret 4`. The original body contains
one genuine E8 `+0x17 -> 0x0044EFC0`, one actual PE HIGHLOW
`+0x13 -> 0x005C0028`, and the compiler's original postcall `nop`.

## Independently discovered historical source-symbol mismatch

There are **two distinct physical 35B Handle wrappers**, with
*different original callees*. The previously exact
[`AnimationHandle::interrupt`](../src/AnimationHandle.cpp)
at **`0x0044EF90`** calls the genuine **246B ordinary pool interrupt**
at `0x0044EE90`. The now-restored
[`AnimationHandle::update_descendants_event_44f0d0`](../src/AnimationHandleEventDescendantsBridge35.cpp)
at **`0x0044F0D0`** instead calls the **261B child interrupt + VM**.
They must not be silently merged just because their machine-code
shapes/lengths are almost identical.

Crucially, the prior whole exact
**29B `AnimationHandle::interrupt_offset_7`** at `0x00464510`
physically calls **the second function `0x0044F0D0`** at E8 site
`0x00464521`, **not** the older `0x0044EF90` one. The old maintained
[`src/AnimationHandle.cpp`](../src/AnimationHandle.cpp) had called
`interrupt(event+7)` under the previous 35B symbol despite the
canonical relocation target already being bound to `0x0044F0D0`.
This is a real ABI/semantic mismatch, not an arbitrary refactor.

The maintained code now declares the new member on the original
four-byte [`AnimationHandle`](../src/AnimationHandle.hpp), keeps the
older `interrupt` implementation intact for its own callers, and
changes `interrupt_offset_7` to call the **physically correct**
`update_descendants_event_44f0d0(event+7)`. Its existing canonical
29B unit's decorated REL32 symbol was corrected to this new method
while retaining the **same original PE target `0x0044F0D0`**.
No new fields/virtual members are added to AnimationHandle.

[`scripts/verify-animation-handle-event-descendants-bridge35-native.py`](../scripts/verify-animation-handle-event-descendants-bridge35-native.py)
checks all original 35 bytes, 15 decoded x86 instructions, native
`ret 4`, one real E8/one HIGHLOW and the physical 29B caller E8.
It **also independently checks the other 35B native wrapper** and
its separate 246B target to prevent the same confusion returning.
Normal pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` produces the whole original
35B with **27/27 matching nonrelocated bytes** plus both real COFF
fields. The modified 29B caller still reproduces its complete original
body and now uses a source symbol matching its real physical target.

Original-target-bound affected-only cold replay:

```text
animation_handle_event_descendants_bridge_35: exact (35/35 bytes)
animation_pool_event_descendants_261: exact (261/261 bytes)
animation_handle_interrupt_offset_7: exact (29/29 bytes)
animation_handle_interrupt: exact (35/35 bytes)
... four other accepted AnimationHandle units also exact
Exact replay: 8/8 units, 3 cold objects
```

This adds **one distinct 35B original game-authored function/+35
`.text` bytes**, while fixing the actual source role of a previously
credited 29B Handle caller. Neither the older 35B/246B path nor the
261B callee is counted again. The separate original 39,470B VM called
by the 261B path is still NONEXACT. No full cold replay or whole-game
link/playability claim.

```bash
scripts/repo-python scripts/verify-animation-handle-event-descendants-bridge35-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationHandleEventDescendantsBridge35.cpp --source src/AnimationHandle.cpp --source src/AnimationPoolEventDescendants261.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
