# CORE/RECON-992 — full original 56B expired Handle fallback and 39B Animation callback forwarding

Locked original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Two genuine original game-owned `AnimationHandle` functions are now
whole-exact with one maintained four-byte Handle ABI:

| Original address | Complete source semantics | Physical native body |
| --- | --- | --- |
| **`0x0044CF10`** | Resolve a Handle through the already exact 51B `AnimationHandle::resolve()` at `0x0044CED0`; if missing/stale, return the **resident Animation at `current_animation_pool + 0xDC`** rather than null | **56B/19-i386, 56/56 strict** |
| **`0x0044F100`** | Obtain an Animation via the new full 56B fallback then assign its entry callback with genuine `Animation::set_field_5dc(AnimationEntryCallback)` at `0x00438A50` | **39B/15-i386, 39/39 strict** |

The `+0xDC` fallback is not a fabricated constant from a provisional
Ghidra prototype. It is the same authentic resident
**`Animation` subobject** separately identified at owner offset
`+0xDC` and actually destroyed by the independently
[whole exact 138B AnimationPool owner destructor](ANIMATION_POOL_DESTRUCTOR138_STRICT_EXACT.md).
The independent original `AnimationHandle::resolve()` includes
stale-ID clearing, so the fallback preserves the source's actual
contract rather than bypassing stale-handle handling.

## Original-only PE evidence

[`scripts/verify-animation-handle-resolve-fallback56-callback39-native.py`](../scripts/verify-animation-handle-resolve-fallback56-callback39-native.py)
checks the **entire original PE bodies**, their frozen whole-body
SHA-256 hashes
`e306f62f32073a950a66b2a8fc1ce24830b951dc032b571a525d3b759855fea1`
(56B) and
`255e47a8b20bf6a5c952e6b43e4b71ec0cbd6748d2fb075cd0bd8ff395e59c6e`
(39B), native 19/15 complete x86 instructions and true `ret`/`ret 4`,
**all original physical E8 offsets and original destinations**,
one physical PE HIGHLOW in the 56B method, zero in the 39B method,
and eight real `INT3` bytes after each function:

| Original native relocation | Real destination |
| --- | --- |
| 56B E8 `+0x0C` | `0x0044CED0`, previously **51/51 strict exact** `AnimationHandle::resolve()` |
| 56B HIGHLOW `+0x24` | `0x005C0028`, authentic `current_animation_pool` global |
| 39B E8 `+0x0C` | **`0x0044CF10`**, newly complete 56B fallback resolver |
| 39B E8 `+0x1B` | `0x00438A50`, previously exact 25B Animation callback-field setter |

[`src/AnimationHandleFallback56.cpp`](../src/AnimationHandleFallback56.cpp)
and [`src/AnimationHandleEntryCallbackForward39.cpp`](../src/AnimationHandleEntryCallbackForward39.cpp)
share the maintained original [`AnimationHandle.hpp`](../src/AnimationHandle.hpp)
class; the header receives **only two nonvirtual method declarations**,
with no new storage, inheritance, virtual table or altered ABI.
Natural pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` emitted the complete original
56B/19 instructions (48/48 nonrelocation bytes, 2 real COFF roles)
and 39B/15 instructions (31/31 nonrelocation bytes, 2 real COFF
roles) on their **first compile probes**, with no manual assembly,
NOP insertion, object prefix copying or original byte patching.

Original-target-bound **affected-only strict cold replay** includes
both new source files, the accepted Handle methods in
`AnimationHandle.cpp`, and the real separately accepted 51B resolver
from `BulletCollisionHandle.cpp`:

```text
animation_handle_resolve_resident_56: exact (56/56 bytes)
animation_handle_entry_callback_forward_39: exact (39/39 bytes)
bullet_collision_handle_resolve: exact (51/51 bytes)
... all 7 other accepted Handle/resolve units exact
Exact replay: 10/10 units, 4 cold objects
```

These add **two distinct original game-authored heads/+95 unique native
`.text` bytes**. The existing 51B Handle resolver, callback setter
and 138B AnimationPool destruction are **not credited again**. The
remaining original 508B/511B Animation-update loops and 39,470B VM
are still independently NONEXACT. No full cold replay or claim of a
fully linked/playable executable.

```bash
scripts/repo-python scripts/verify-animation-handle-resolve-fallback56-callback39-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationHandleFallback56.cpp --source src/AnimationHandleEntryCallbackForward39.cpp --source src/BulletCollisionHandle.cpp --source src/AnimationHandle.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
