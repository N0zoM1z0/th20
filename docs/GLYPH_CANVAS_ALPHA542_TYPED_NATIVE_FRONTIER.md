**CORE/RECON-1058/1059 status correction:** The original 2,227B glyph text core previously called source-absent is now [SOURCE-PRESENT, NONEXACT](GLYPH_TEXT_CORE2227_TYPED_NATIVE_FRONTIER.md) with a complete 2,052B/481-instruction native-typed candidate. Its separate original 132B game-specific queued-job capture is [WHOLE STRICT EXACT](GLYPH_TEXT_JOB_CAPTURE132_STRICT_EXACT.md). Historical source-absent claims below are dated; the 2,227B parent is still not exact.

# CORE/RECON-1057 — original 542B glyph canvas Alpha-processing Boss, complete typed C++ source frontier

Locked target: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original native canvas Alpha processor at `0x00417AB0` is a **complete
542B/164-i386** game-owned method, SHA-256
`b510c0d99e2c1d40f1388c77952a55775dfd24617858922e56ed178e1fdf64df`.
The original entire **2,227B/470-i386 glyph text-rendering Boss**
`0x00415830` calls this native method via its genuine E8 `+0x6D6`.

## Real native game state and three pixel modes

[`src/GlyphCanvasAlphaInvert542.cpp`](../src/GlyphCanvasAlphaInvert542.cpp)
maintains a complete typed C++ implementation on the existing borrowed
[`NativeGlyphCanvasView`](../src/NativeGlyphCanvasView.hpp), not a
parallel GDI bitmap object. Native four stack arguments are preserved
in the method declaration, including the fourth caller-supplied `0`
whose use inside the native body is unobserved. Its actual `ret 0x10`
and one-byte boolean return are verified from the locked PE:

- `0x15`: iterate each of the requested image rows, starting at the
  original logical `canvas_width_415800()` and horizontal origin.
  Invert the **high alpha byte** of each BGRA32 pixel by XOR 0xFF,
  without overwriting its three color bytes.
- `0x19`: iterate the entire `pixel_stride_4156c0()*rows` byte buffer
  in 2-byte words, toggling the top **one-bit Alpha**. If the new top
  bit is clear, clear color channels through the original sequential
  **0x83FF**, **0xFC1F**, **0xFFE0** masks. All three masking steps
  are actual original per-pixel state changes.
- `0x1A`: iterate 16-bit ARGB4444 pixels within the original rows and
  horizontal region, invert the top 4-bit Alpha nibble by XOR 0xF,
  and retain the other packed RGB nibbles.
- Other pixel formats return false; the three recognized modes return
  true. No new range validation or fallback mode was invented.

Read-only [`verify-glyph-alpha-invert542-native.py`](../scripts/verify-glyph-alpha-invert542-native.py)
SHA-attests the complete original 542B body, 164 instructions, native
`ret 0x10`, three real format comparisons and exactly four genuine
original E8 instructions: `+0x0C -> 0x004156C0` stride, `+0x1B ->
0x004156A0` pixels, and `+0x6B/+0x198 -> 0x00415800` width. It
independently proves **zero original PE HIGHLOW** in this function and
the actual parent 2,227B E8 edge.

The first natural C++20 source candidate compiled **514B/157-i386**.
An explicit meaningful `std::uint16_t` local for the 1-bit Alpha
transition (rather than C++'s default promoted 32-bit arithmetic)
raised the result to **540B/164-i386**, with the same four original
function call roles. In this candidate, the first two original E8
relocation positions match exactly; the two width calls occur at
source `+0x71/+0x1AC` versus native `+0x6B/+0x198`, so the whole
body remains **NONEXACT**. Separate, controlled variants of the
4-bit color arithmetic and a consolidated success return did not
reproduce the whole original. No original code extent was shortened,
no raw machine instructions, no arbitrary padding, and no inert
compiler-shaping assignments were added.

**Status: SOURCE-PRESENT, NONEXACT**. The original 542B function has
no accepted strict unit, and the entire 2,227B parent is still
SOURCE-ABSENT. The existing 681B canvas creation, 104B fallback,
82B descriptor lookup, 182B cleanup and four 20B getters remain
independently whole exact. This new declaration touches only the
shared glyph view's affected canonical source owners; the existing
5-provider **17/17-unit** closure is rebuilt locally to guard those
previous exact results. No whole-graph replay is run.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/GlyphCanvasAlphaInvert542.cpp build/core1057-probes/GlyphCanvasAlphaInvert542.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-glyph-alpha-invert542-native.py \
  --candidate-object build/core1057-probes/GlyphCanvasAlphaInvert542.obj
scripts/repo-python scripts/validate-tracking.py --require-target
```
