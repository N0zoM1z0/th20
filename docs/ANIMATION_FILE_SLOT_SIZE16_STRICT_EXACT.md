# CORE/RECON-974 — complete original 16B `std::array<AnimationFile*,42>::size` strict exact

Immutable original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The native `0x00450870` is the entire **16B/8-i386**
`std::array<th20::AnimationFile*,42>::size()` template specialization,
returning original `42` (`0x2a`). It is physically called from the
independently whole-exact
[209B RendererPool file-slot retirement](ANIMATION_FILE_SLOT_RELEASE209_STRICT_EXACT.md)
at original E8 **`0x0044C448 -> 0x00450870`**.

[`scripts/verify-animation-file-slot-size16-native.py`](../scripts/verify-animation-file-slot-size16-native.py)
independently checks the immutable original full 16B function, all 8
x86 instructions through native `ret`, the real immediate `0x2a`,
zero PE HIGHLOW and the genuine original 209B parent E8 site/target.
A natural C++20 instantiation of the real maintained
`std::array<AnimationFile*,42>` from
[`src/AnimationFileSlotSize16.cpp`](../src/AnimationFileSlotSize16.cpp)
emits all 16 original bytes without padding, inline assembly or
manual object patching. Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS
/Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` original-bound replay:

```text
animation_file_slot_size_16: exact (16/16 bytes)
animation_file_slot_release_209: exact (209/209 bytes)
Exact replay: 2/2 units, 2 cold objects
```

This adds **one strict source-present native function/16 original
bytes**, but it is a compiler/STL template instantiation with
`library/exclude` provenance, **not an authored-game exact function**.
It therefore adds **zero** to the original game-authored head and
byte totals; the 209B existing game method is not credited again.
No full project cold replay or playable-game claim.

```bash
scripts/repo-python scripts/verify-animation-file-slot-size16-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationFileSlotSize16.cpp --source src/AnimationFileSlotRelease209.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
