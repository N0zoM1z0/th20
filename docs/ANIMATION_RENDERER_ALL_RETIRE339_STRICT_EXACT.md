# CORE/RECON-988 — native whole 339B Renderer double-list complete Animation retirement strict exact

Locked TH20 Japanese Steamless v1.00a executable SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Original `0x0044A3A0` is the full **339B/106-i386** game-owned
Renderer-side Animation retirement of both live lists. The native
Renderer has **two 24B IntrusiveList<Animation>** objects at offsets
`+0x00` and `+0x18`, using the same preexisting
[`NativeSpawnRendererView`](../src/NativeSpawnRendererView.hpp) as the
accepted 691B Renderer detachment, 382B/394B classification and
150B/164B Renderer update wrappers. This method sequentially walks
both lists with actual `IntrusiveIterator` instances, obtains each
Animation through `IntrusiveLink::node_access()`, and calls the
separately whole exact **308B**
[`AnimationPoolOwner::release_animation`](ANIMATION_POOL_RELEASE_308_AND_HELPERS_STRICT_EXACT.md)
on the authentic global `current_animation_pool` at `0x005C0028`.

The [original PE-only validator](../scripts/verify-animation-renderer-all-retire339-native.py)
authenticates every original byte of the whole 339B body against SHA-256
`e09b297f6d6283afe82af02d6748e0d95449c3dd9f833d57c9979e2d31b6361a`,
all **106 i386 instructions** through the genuine `ret`, physical
following five `INT3` alignment bytes, all **19 actual direct E8
sites and native destinations**, all **four original PE HIGHLOW
fields**, and the two actual native `release_animation` E8 locations
`+0x99/+0x122 -> 0x0044C2F0`.

| Native field | Original physical meaning |
| --- | --- |
| E8 `+0x36/+0xBF` | `0x0040C080`, real iterator initializers for both lists |
| E8 `+0x42/+0xCB`, `+0x51/+0xDA` | `0x00412280` begin and `0x00412540` end |
| E8 `+0x5E/+0xE7`, `+0x6B/+0xF4`, `+0x7A/+0x103`, `+0x85/+0x10E` | Native iterator advance/differs/get/node-access, each duplicated for true second list |
| E8 `+0x99/+0x122` | Genuine **308B whole exact** AnimationPool animation retirement, not a fabricated helper |
| E8 `+0xAB/+0x134` | `0x00411B00`, two true iterator destructors; both scopes retain exception-cleanup state |
| E8 `+0x14A` | `0x005429EE`, actual security-cookie checker |
| PE HIGHLOW `+0x06/+0x15` | `0x00568415` actual original EH handler / `0x005B25C0` stack cookie |
| PE HIGHLOW `+0x95/+0x11E` | Two genuine live pool global references `0x005C0028` |

The native six original `nop` instructions at `+0x63/+0x9E/+0xB0` and
`+0xEC/+0x127/+0x139` emerge naturally from iterator lifetimes and
expression-call boundaries; there is no source-level byte patch or
hand-inserted NOP.

[`src/AnimationRendererAllRetire339.cpp`](../src/AnimationRendererAllRetire339.cpp)
uses maintained Renderer/Animation/Pool and STL-independent intrusive
list types with two distinct lexical loop scopes. Its **first pinned
MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` compilation** produced the entire original 339B/106
instructions, **247/247 matching nonrelocated bytes plus all 23
original physical relocation targets**, without changing any shared
class tag, inventing 96MiB pool storage, or assuming transitive code
is exact.

Original-target-bound, affected-only canonical cold replay:

```text
animation_renderer_all_retire_339: exact (339/339 bytes)
animation_pool_release_308: exact (308/308 bytes)
animation_geometry_release_82: exact (82/82 bytes)
animation_pool_membership_90: exact (90/90 bytes)
animation_pooled_record_index_23: exact (23/23 bytes)
Exact replay: 5/5 units, 3 cold objects
```

One new **original game-authored whole function/+339 `.text` bytes**
is credited. The previously counted 308B/82B/90B game functions and
23B compiler/STL index are regression checked, not double-counted.
This proves neither the full linked executable nor playability; the
separate 508B/511B Animation update loops, 5,993B draw and 39,470B
VM are still independently open. No global cold replay occurred.

```bash
scripts/repo-python scripts/verify-animation-renderer-all-retire339-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRendererAllRetire339.cpp --source src/AnimationPoolRelease308.cpp --source src/AnimationPoolReleaseHelpers.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
