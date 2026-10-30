# CORE/RECON-926 — original one-segment ribbon 140B update Boss and 19B array-end whole strict exact

Locked original Japanese TH20 1.00a Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0045D6F0` is a **140B/46-i386** virtual update method
in a **distinct one-segment** ribbon group, not the previously exact
three-segment `0x0045E770` group. Its original polymorphic vtable is
at **`0x0056ECA4`**, with deleting wrapper `0x0045D6B0`, this update,
separate `0x0045DA40` draw and three inherited entries. Its one native
segment is `0x3C0` bytes at owner offset +8 and its Timer is at
`+0x3CC`. Native deleting wrapper and constructor suggest group size
`0x3E0`; those unaccepted parents require separate proofs.

## Independent original PE evidence

[`scripts/verify-animation-ribbon-solo-tick140-native.py`](../scripts/verify-animation-ribbon-solo-tick140-native.py)
authenticates the complete original 140B/46 native instructions, final
`ret`, all **six** physical E8 sites/targets, **zero** in-body HIGHLOW,
actual `0x3C0` loop stride/`0x3CC` Timer offset, original full six-slot
vtable with physical HIGHLOW, and both real call sites of the separate
19B array-end helper `0x0045DCE0`:

| Original E8 in 140B Boss | Physical target | Role |
| --- | --- | --- |
| `+0x12` | `0x0045D030` | Timer change gate |
| `+0x27` | `0x0040BDA0` | Genuine native begin/address helper |
| `+0x32` | `0x0045DCE0` | One-segment array one-past-end pointer |
| `+0x5C` | `0x004379C0` | Animation scale X |
| `+0x68` | `0x0045D780` | Original distinct **697B** per-segment dynamics Boss, still source-absent |
| `+0x81` | `0x00423540` | Original Timer increment |

The 19B/9-i386 `0x0045DCE0` helper has an actual `add eax,0x3C0`,
zero native E8/HIGHLOW and native caller E8 both in this 140B update
and the separate original 156B draw at `0x0045DA40`.

## Natural typed C++ and strict native replay

[`src/NativeRibbonSoloGroup.hpp`](../src/NativeRibbonSoloGroup.hpp)
uses the same established real `NativeRibbonSegment` element shape but
only **one** element. It preserves the distinct group layout and virtual
methods, without renaming or reusing the three-segment virtual table.
[`src/AnimationRibbonSoloGroupUpdate140.cpp`](../src/AnimationRibbonSoloGroupUpdate140.cpp)
expresses the timer-gated native loop and Animation scale update through
the real one-segment array. Its local `NativeRibbonSoloSegmentUpdateView`
only names the ABI to the **still-unreconstructed 697B callee**; it
neither creates duplicate storage nor asserts authorship of that callee.
[`src/AnimationRibbonSoloArrayEnd19.cpp`](../src/AnimationRibbonSoloArrayEnd19.cpp)
returns the actual one-past-end address using `sizeof(std::array<... ,1>)`.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` naturally produces the entire original native
bytes and real relocation sites:

```text
animation_ribbon_solo_tick_140: exact (140/140 bytes)
animation_ribbon_solo_end_19: exact (19/19 bytes)
Exact replay: 2/2 units, 2 cold objects
```

The **140B** polymorphic group update is one new original game-authored
strict exact function, **+140 `.text` bytes**. The independently exact
19B array end remains `origin=unknown/review`, likely generated/STL and
**uncredited** in authored totals. No old accepted sources or shared
headers were modified; no global cold replay ran. The original 697B
per-segment updater and 156B solo draw are **not** inferred exact from
these children.

```bash
scripts/repo-python scripts/verify-animation-ribbon-solo-tick140-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSoloGroupUpdate140.cpp --source src/AnimationRibbonSoloArrayEnd19.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
