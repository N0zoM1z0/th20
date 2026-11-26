# CORE/RECON-975 — original complete 30B narrow-format wrapper strict exact, 417B text Boss child

Original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Native `0x00447940` is a complete **30B/13-i386** `char`
formatting wrapper called at original `0x0044AC89` from the
separate **417B Animation text-submission Boss at `0x0044AC20`**.
It forwards all three original stack arguments (output, format,
`va_list`) plus actual constant **`0x500`** into the native
`vsprintf_s` function `0x00439880`. The current callers each reserve a
0x500-byte buffer. The [native CRT character-width proof](RENDERER_TEXT_NARROW_CRT_ABI.md)
corrects the earlier Ghidra-derived wide declaration; the complete 30B code
and actual call target are unchanged.

[`scripts/verify-animation-text-format30-native.py`](../scripts/verify-animation-text-format30-native.py)
attests every original PE byte and instruction through `ret`, genuine
E8 `+0x14 -> 0x00439880`, actual `push 0x500`, zero in-body HIGHLOW and
the original 417B parent E8 to this exact address. Natural C++20 source
[`src/AnimationTextFormat30.cpp`](../src/AnimationTextFormat30.cpp)
uses a shared narrow declaration and the actual SDK CRT interface. Pinned
MSVC 19.44 x86 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` builds **30/30
strict exact**, **26/26 nonrelocation bytes**, and the authentic native
`_vsprintf_s` call relocation:

```text
animation_text_format_30: exact (30/30 bytes)
Exact replay: 1/1 unit, 1 cold object
```

Adds one full source-present native unit/30 bytes but **zero new credited
original game-authored code**, since its original utility/library
versus custom source ownership is unresolved (`origin=unknown/review`).
The 417B parent was still NONEXACT at the original checkpoint and is now
[whole strict exact](ANIMATION_RENDERER_FORMATTED_TEXT_417_STRICT_EXACT.md).
The deeper text-submission body remains NONEXACT. No global cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-text-format30-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationTextFormat30.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
