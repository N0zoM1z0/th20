# CORE/RECON-977 — whole original 411B recursive Animation retirement queue strict exact

Original immutable Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Original `0x0044F840` is a **complete 411B/116-i386 game-authored**
`AnimationPoolOwner`-side recursive queueing method. Called twice by
the separate **508B/152-i386** Animation active-list update at original
E8 `0x00449969` and `0x004499B2`, it traverses the actual
`Animation::child_links[1]`, queues descendants before their parent,
marks `Animation+0x570` retired state `2`, clears actual parent
`+0x558/+0x55C`, pending `+0x554/+0x550`, and detaches first child
link `child_links[0]`. It retains a genuine exception-safe
`IntrusiveIterator<Animation>` lifetime including its native MSVC
handler and the self-recursive E8 call.

[`scripts/verify-animation-queue-retirement411-native.py`](../scripts/verify-animation-queue-retirement411-native.py)
reads the exact original PE, authenticates all original **411 bytes** by
body SHA-256
`d38cbce8caaee204e4c1e78bfba2f9023d89395535292d2828b6cabcaea0f94d`,
all 116 original x86 instruction boundaries through real `ret 8`, all
**18 direct E8 original physical sites and targets**, **two real PE
HIGHLOW fields** (`+0x06 -> 0x0056867D` EH; `+0x15 -> 0x005B25C0`
cookie), actual `Animation+0x570` and true **five `INT3`** after the
end of the function. All native E8 and PE relocation fields, including
the original MSVC exception cookie checker `+0x190 -> 0x005429EE`,
are individually pinned in the canonical native match manifest.

| Critical original E8 | Original address and independently established role |
| --- | --- |
| `+0x3B/+0x60` | `0x004494B0` actual `AnimationChildLinks::operator[]` |
| `+0x42/+0x67` | `0x0040FF90` native folded `IntrusiveLink::next_value` |
| `+0x74/+0x80/+0x8F` | `0x0040C080` iterator auto-initializer, `0x0044B9F0` link begin, `0x00412540` end |
| `+0x9C/+0xA9/+0xB8/+0xC7` | Native iterator advance/differs/get and node-access callees |
| `+0xD2` | **`0x0044F840`**, real whole self-recursion through each child |
| `+0xE4` | `0x00411B00` native iterator destructor |
| `+0x109` | `0x0044A670`, actual child pending-link initialize |
| `+0x11B` | **`0x00411EA0` 57B** native `IntrusiveList<Animation>::append` to retired staging list |
| `+0x173/+0x17A` | Native child-links index and `IntrusiveLink::detach` |

**Important physical-symbol correction:** The prior
[308B AnimationPool object retirement](ANIMATION_POOL_RELEASE_308_AND_HELPERS_STRICT_EXACT.md)
calls a different existing original **76B** physical head
`0x00411EE0` for insertion *at the free-list head*. The current
411B queue uses the native **57B** `IntrusiveList::append` at
`0x00411EA0` instead. Both were independently checked against actual
compiled COFF contributions, and the 57B helper naturally matched
**49/49 nonrelocated bytes plus both native E8 destinations**.
Neither existing folded subhelper is credited a second time.

The maintained [`src/NativeAnimationRetirePoolView.hpp`](../src/NativeAnimationRetirePoolView.hpp)
provides one non-owning original ABI receiver shared with prospective
508B caller reconstruction. The real full
[`src/AnimationQueueRetirement411.cpp`](../src/AnimationQueueRetirement411.cpp)
uses the existing `Animation`, `AnimationChildLinks`,
`IntrusiveIterator<Animation>`, and `IntrusiveList<Animation>` layouts,
not invented storage or handwritten assembly. It was compiled under
pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`, producing complete **411B/116-i386,
331/331 matching nonrelocated bytes plus all 20 original PE roles**:

```text
animation_queue_retirement_411: exact (411/411 bytes)
Exact replay: 1/1 unit, 1 cold object
```

This adds **one original game-authored whole function /411 unique
native `.text` bytes**. Existing iterator, 57B append, and 308B
retirement are not double-counted. The **508B Animation update caller,
2,884B particle Update, and 39,470B Animation VM** remain separate
NONEXACT work; whole executable build/link/playability is not claimed.
No full cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-queue-retirement411-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationQueueRetirement411.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
