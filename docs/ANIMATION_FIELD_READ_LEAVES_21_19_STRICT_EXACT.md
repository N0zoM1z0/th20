# CORE/RECON-1116 — native Animation alpha and Vector3 read leaves, 21B + 19B whole exact

The locked Japanese TH20 Steamless v1.00a executable (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
contains two separate authored Animation methods that had remained
unclassified even though their callers are part of larger draw/animation
control flow. Both full original bodies are now reconstructed in
[`src/AnimationFieldReadLeaves.cpp`](../src/AnimationFieldReadLeaves.cpp).

## Original 21B: packed color alpha

`0x0044C650..0x0044C664` contains **21B/9 i386 instructions**, original
whole SHA-256
`0db22c6bec703e8f1bba18ced2635741d7bbfa4a3e6b82a80deaa446001f342d`.
The `__thiscall` method loads its existing Animation receiver and reads
`movzx eax,byte ptr [eax+0x493]`. This is the real alpha channel of
`AnimationBase::channels_490` (BGRA at +`0x490`), not an unrelated
flag word. Original **4,238B** caller `0x00461B80` calls it at native
`0x00461F7B`, `0x00461FB7` and `0x00462276`, each widening the byte
before an actual alpha multiplication.

The maintained `NativeAnimationReadView::color_alpha_44c650() const`
returns the genuine `std::uint8_t` member. Locked MSVC C++20 naturally
emits the entire original **21/21B, 9/9 instructions** with no original
E8 or PE HIGHLOW, and zero generated COFF relocations.

## Original 19B: the actual +0x484 Vector3

`0x0044CB00..0x0044CB12` contains **19B/9 i386 instructions**, original
whole SHA-256
`47d9a163f8e0cc4ba692c29d17e640400a0e7893ad7b454c95fc4658a48376ef`.
It obtains its real Animation receiver and returns the address of
`AnimationBase::vector_484`, using `add eax,0x484` before `ret`.
The original 26B wrapper `0x0044CAE0` calls it at `0x0044CAF1`.
The original **9,433B** controller at `0x004B0720` calls it many times,
including `0x004B18F2`, `0x004B1936`, `0x004B197A`,
`0x004B19BE` and `0x004B1F26`; at `0x004B18FF` it writes a genuine
float through the returned `EAX+4` pointer, establishing a real Vector3
component consumer. This is a game-authored shared animation field
accessor, not a guessed standalone object.

The maintained `NativeAnimationReadView::vector_484_44cb00()` returns
`Vector3&` and naturally compiles to the complete **19/19B, 9/9
instructions** with zero E8/PE HIGHLOW and zero COFF relocations.

## No new storage and bounded acceptance

`NativeAnimationReadView : Animation` is a **borrowed, non-instantiated
view** of the existing Animation receiver; `static_assert` confirms no
new field storage, and neither a shared layout header nor any existing
canonical source was changed. Its two methods preserve authentic native
`this` and return ABIs, original field offsets and direct callers.

The original-only/native/COFF checker
[`scripts/verify-animation-field-read-leaves-native.py`](../scripts/verify-animation-field-read-leaves-native.py)
attests both entire SHA-pinned bodies, instructions, physical callers,
absence of any E8/HIGHLOW and both complete compiler contributions.
Its **fresh canonical** receipt and strict replay establish:

```text
animation_color_alpha_21: exact (21/21 bytes)
animation_vector_484_19: exact (19/19 bytes)
Exact replay: 2/2 units, 1 cold objects
```

Only `src/AnimationFieldReadLeaves.cpp` was cold compiled, not an
unfiltered graph. This adds **two distinct authored original function
heads /40 original .text bytes**; it does **not** claim exactness of
either the 4,238B or the 9,433B original parent caller, nor duplicate
other unrelated folded library helpers. No entire-game link or runtime
playability claim is made.

```sh
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationFieldReadLeaves.cpp
scripts/repo-python scripts/verify-animation-field-read-leaves-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```
