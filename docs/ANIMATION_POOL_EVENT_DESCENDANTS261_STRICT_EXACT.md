# CORE/RECON-989 — original full 261B Animation child-event and VM update traversal strict exact

Locked Japanese TH20 Steamless v1.00a executable SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Original `0x0044EFC0` is the entire **261B/81-i386**
game-owned AnimationPool child-event traversal, taking the original
handle index and event integer with native x86 `__thiscall`-compatible
`ret 8`. It resolves the handle through the already exact
[`AnimationPoolOwner::resolve_handle` 456B](ANIMATION_POOL_RESOLVER_456_STRICT_EXACT_RECONSTRUCTION.md)
(original E8 `+0x32 -> 0x0044CD00`), then checks that the resulting
Animation exists. If nonnull it accesses the real
`Animation::child_links[1]` at `Animation+0x514`, creates a genuine
`IntrusiveIterator<Animation>` from the head, and visits all children.
Each child receives two distinct real calls in order:
`Animation::interrupt(event)` at `0x004388F0`, followed by
`Animation::update()` at **`0x0042B5D0`**, the enormous **39,470B
Animation VM**, which remains separate **NONEXACT** work.

[`scripts/verify-animation-pool-event-descendants261-native.py`](../scripts/verify-animation-pool-event-descendants261-native.py)
reads the actual unchanged executable and checks the complete original
261B body digest
`9f4ca0b447123a1a59cc1bd315b43de8e0fe096ec17ca48e0e5d7f6c07747836`,
all **81 x86 instructions** through native `ret 8`, all **14
physical E8 offsets and original target addresses**, both original
PE HIGHLOW locations `+0x06 -> 0x005685FD` (MSVC EH handler) and
`+0x15 -> 0x005B25C0` (stack cookie), and seven physical `INT3`
following the original function. The actual native child enumeration
uses original `AnimationChildLinks::operator[]`,
`IntrusiveLink::begin`, list-end, iterator advance/differs/get and two
separate link-to-Animation `node_access()` calls. The true original
security check and iterator cleanup are preserved.

The real
[`src/NativeEventDescendantPoolView.hpp`](../src/NativeEventDescendantPoolView.hpp)
declares a **zero-new-storage pool receiver** rather than inventing a
new Animation owner class or allocating original pool storage. Natural
[`src/AnimationPoolEventDescendants261.cpp`](../src/AnimationPoolEventDescendants261.cpp)
uses existing `Animation`, `AnimationPoolOwner`, `AnimationChildLinks`
and `IntrusiveIterator` source, and retains the original empty
null-animation branch. Its **first pinned MSVC 19.44 x86 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`**
compilation generated the complete original **261B/81 native code,
197/197 matching nonrelocated bytes and all 16 actual relocation
fields**, without fake NOP, byte patch or shortening the body.

Original-target-bound affected-only canonical replay:

```text
animation_pool_event_descendants_261: exact (261/261 bytes)
animation_pool_resolve_handle_whole_456: exact (456/456 bytes)
animation_link_find_predicate_159: exact (159/159 bytes)
animation_list_find_predicate_154: exact (154/154 bytes)
animation_pool_sprt_equal_lambda_43: exact (43/43 bytes)
Exact replay: 5/5 units, 2 cold objects
```

One distinct original game-authored whole-exact function and **+261
native `.text` bytes** are credited. The preexisting whole-exact
456B handle resolver and its folded children are not credited again.
The original 39,470B Animation VM is **not** assumed exact merely
because this 261B method calls it. The whole game still does not link
or play, and no full cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-pool-event-descendants261-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPoolEventDescendants261.cpp --source src/AnimationPoolHandleResolve.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
