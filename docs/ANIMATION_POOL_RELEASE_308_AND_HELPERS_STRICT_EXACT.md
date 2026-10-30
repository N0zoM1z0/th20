# CORE/RECON-976 — complete original 308B AnimationPool release Boss, 82B geometry, 90B membership and 23B array index

Original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

This is the complete **308B/80-i386 original game-owned `AnimationPoolOwner::release_animation`** at `0x0044C2F0`, plus three independently full native original callees:

| Original physical function | Strict code result | Native purpose |
| --- | --- | --- |
| `0x0044C2F0` | **308/308B, 80 i386** | Game-owned Animation release: retire callback and geometry, detach two intrusive links, sever parents, test pool membership, return pooled animation to free list or free separately allocated animation |
| `0x0044C5F0` | **82/82B, 22 i386** | Game-owned geometry memory free/reset through the original process DiagnosticAllocator |
| `0x0044D970` | **90/90B, 27 i386** | Game-owned membership bounds against original pool of 65,536 `PooledAnimation` records, each `0x600` bytes |
| `0x004494D0` | **23/23B, 9 i386** | Standard-library `std::array<PooledAnimation,65536>::operator[]`, genuine `0x600` stride, source owned by STL and not credited as game-authored |

[`scripts/verify-animation-pool-release308-native.py`](../scripts/verify-animation-pool-release308-native.py) reads only the immutable original PE, verifies the entire original SHA-256 of every one of these four bodies, their actual instruction/return boundaries, all original E8 site/destination pairs, every physical PE HIGHLOW field and original INT3 boundaries. The native 308B parent contains **11 genuine E8 and 2 HIGHLOW** (both process allocator). Its E8 targets include genuine callback/geometry retirement, two intrusive detach methods, the 90B membership helper, two 23B array indexing calls, original `insert_after`, `Animation::release_resources`, Handle assignment and final allocator release.

The original **308B** native function is physically called by other game functions at addresses including `0x00449A3B`, `0x00449CEE`, `0x0044A439` and `0x0044A4C2`. These are independently verified original E8 sites; this admission does **not** assert that those larger callers are whole-exact.

The natural maintained source is [`src/AnimationPoolRelease308.cpp`](../src/AnimationPoolRelease308.cpp) plus [`src/AnimationPoolReleaseHelpers.cpp`](../src/AnimationPoolReleaseHelpers.cpp), sharing [`src/NativeAnimationPoolReleaseViews.hpp`](../src/NativeAnimationPoolReleaseViews.hpp) and the existing real `AnimationPoolOwner`, `Animation`, `PooledAnimation`, `AnimationCallback`, `IntrusiveLink` and `DiagnosticAllocator` types. The pool is referenced through a **non-owning pointer view at `+0x710`**, and the original free-list sentinel at `+0x06000718`; no 100MB owner allocation is invented. The source intentionally computes the pooled-record array address twice as the original does, and the free-list insertion is `insert_after`, **not** a semantically different append.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` emits complete original whole-code contributions of **308B/80**, **82B/22**, **90B/27** and **23B/9 i386**. All native E8, data/allocator relocations and the STL index bytes match without inline assembler or artificial padding. Source-affected-only, original-bound canonical replay:

```text
animation_pool_release_308: exact (308/308 bytes)
animation_geometry_release_82: exact (82/82 bytes)
animation_pool_membership_90: exact (90/90 bytes)
animation_pooled_record_index_23: exact (23/23 bytes)
Exact replay: 4/4 units, 2 cold objects
```

**Accounting:** Three new authored-game distinct whole exact functions contribute **480 original native `.text` bytes** (`308+82+90`). The 23B STL array index contributes one strict source mapping but **zero authored game bytes**. This does not double-credit its existing compiler/folded child methods or imply complete game startup, linkage, playability, 2,884B particle Update exactness or 39,470B Animation VM exactness. No full cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-pool-release308-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPoolRelease308.cpp --source src/AnimationPoolReleaseHelpers.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
