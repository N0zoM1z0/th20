# CORE/RECON-911 — complete 140B ribbon-group update Boss strictly exact

Locked original: Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This is an **independent polymorphic ribbon/polygon AnimationCallback group**,
not an alias for the previously exact `0x0045F5E0` Motion-group updater.
The entire original `0x0045E770` is **140B /46 i386**, with a real
three-element **0x3C0-byte stride** and a timer at receiver `+0xB4C`.
The source reproduces the **entire 140/140 original relocated native bytes**.

## Original PE function and owned dispatch

[`scripts/verify-animation-ribbon-group140-native.py`](../scripts/verify-animation-ribbon-group140-native.py)
independently decodes all 46 original instructions, the complete return,
all six genuine original E8 sites and destinations, no in-body HIGHLOW,
and the exact six vtable entries with physical PE relocations:

| Original E8 offset | Actual target | Original role |
| --- | --- | --- |
| `+0x12` | `0x0045D030` | Timer change predicate |
| `+0x27` | `0x0040BDA0` | Folded native Motion begin/address helper |
| `+0x32` | `0x0045ECA0` | Genuine array one-past-end pointer, whole 19B exact |
| `+0x5C` | `0x004379C0` | Whole-exact Animation scale getter |
| `+0x68` | `0x0045E800` | Distinct **538B** per-segment updater, still source absent |
| `+0x81` | `0x00423540` | Original Timer increment |

The original **vtable `0x0056EDDC`** has physical slots for deleting
wrapper `0x0045E730`, this exact update `0x0045E770`, **156B draw
`0x0045EA20` (NONEXACT at this checkpoint)** and inherited methods
`0x00412540`, `0x00414B50`, `0x00414B50`. Native three-slot array
occupies offset `+0x08..+0xB47`. Its separately strict-exact
**19B `0x0045ECA0` helper** returns the array one-past-end at `+0xB40`
relative to that subobject, rather than an arbitrary opaque four-byte
field. The previous provisional field interpretation is explicitly
superseded by this independently observed 140B/156B loop relationship.

## Natural C++ source and whole canonical proof

[`src/NativeRibbonPolygonGroup.hpp`](../src/NativeRibbonPolygonGroup.hpp)
declares one distinct AnimationCallback-derived class with three authentic
0x3C0 records and a timer at +0xB4C, without inventing record fields or
a second ownership class for the earlier 0x3D4 polygon group. The
[`140B source`](../src/AnimationRibbonGroupUpdate140.cpp) uses genuine
Timer change/increment, Animation scale and a typed loop to update every
segment. The [`19B array-end helper`](../src/AnimationRibbonSegmentArrayEnd19.cpp)
uses true `sizeof(std::array<NativeRibbonSegment,3>)`. The 538B child body
and 156B draw remain separate reconstruction tasks.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` for the Boss, with the already proven C++17
profile for the 19B helper, generate *complete* canonical code and real
REL32 fields to all six original native targets:

```text
animation_ribbon_segment_array_end_19: exact (19/19 bytes)
animation_ribbon_group_update_140: exact (140/140 bytes)
Exact replay: 2/2 units, 2 cold objects
```

The **140B game-authored parent** adds **one genuinely new authored exact
original function /140 native `.text` bytes**; its exact child 19B
remains likely C++/STL/compiler-generated and `origin=unknown/review`, so
is **not** double-credited. The 140B parent is independently exact;
neither its 538B callee nor 156B draw is inferred exact from it.
All unrelated canonical source inputs and previous receipts are unchanged.

```bash
scripts/repo-python scripts/verify-animation-ribbon-group140-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonGroupUpdate140.cpp --source src/AnimationRibbonSegmentArrayEnd19.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
