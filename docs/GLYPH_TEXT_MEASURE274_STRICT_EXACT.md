# CORE/RECON-1067 — complete original 274B CP932/GDI font text measurement Boss, strict exact

Locked target: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original physical text-measurement Boss `0x004156E0` is a **whole
274B/71-i386** game-authored function, original SHA-256
`33e732ed92238aa3a5e4175ac0714abc7f427cf23e03c4ad1ae1b4b3260e23be`.
Its genuine return ABI is a **packed 8-byte Win32 `SIZE`** in EDX:EAX,
not a fabricated `SIZE*` argument or a high-level return proxy.
The method receives an encoded text pointer and native font table index.

## Complete native gameplay and Win32 GDI call protocol

[`src/GlyphTextMeasure274.cpp`](../src/GlyphTextMeasure274.cpp)
maintains the full observed native text-measurement source on the same
actual [22-entry font table](GLYPH_FONT_ARRAY22_RELEASE79_STRICT_EXACT.md)
at original data VA `0x005B66F0`. The full sequence is:

1. Read the selected `HFONT` using the already independent whole-exact
   `std::array<HFONT,22>::operator[]` folded physical head `0x00414580`.
2. Clear exactly **0x202 bytes** of a real local UTF-16 buffer and
   convert original CP932 code page **932** via Win32
   `MultiByteToWideChar(932,0,encoded,-1,unicode,0x100)`. The 0x100
   source conversion limit is the genuine original argument; no
   speculative extra Unicode buffer safety policy is attributed to
   the executable.
3. Read the current HWND through the existing native 16B folded
   `current_window_40c300` call at original data-global receiver
   `0x005B6758` and **pass its result directly to `GetDC`**. The
   original has **no extra local HWND stack copy** between these calls.
4. Select the actual font into the device context, compute the genuine
   Unicode length through CRT `wcslen`, ask Win32
   `GetTextExtentPoint32W` to fill the caller-local `SIZE`, then add
   exactly **4 pixels** to *both* native width and height.
5. Restore the prior font via the native second `SelectObject` call
   and return the two original 32-bit `SIZE` words packed as a 64-bit
   EDX:EAX result. There is **no original `ReleaseDC` call** in this
   function, and the maintained source does not insert one or assert
   complete external-window resource safety.

The genuine native window getter is declared only on the nonowning
[`NativeGlyphWindowHostView`](../src/NativeGlyphWindowHostView.hpp).
Its 16B original code head and the 22B folded font index are already
separately accepted, **not counted again**; this source owns exactly
one newly generated game-authored code body.

## Corrected lifetime hypothesis, full original proof

A plausible initial C++20 implementation cached the HWND in a local
variable before calling `GetDC(hwnd)`. It generated a **286B/73-i386**
candidate with the otherwise correct **five E8/eight DIR32** roles,
but had a false six-byte stack write and six-byte reload and thus
moved the original frame ownership. Removing that real but unnecessary
local and calling the Win32 API directly as
`GetDC(native_window_host_5b6758.current_window_40c300())` generated
precisely the original **274B/71 instructions**, including the native
`0x220`-byte function frame and all original local widths.
The source is not padded or patched, and there are no invented direct
function calls, assembly, copied native data or shortened comparisons.

[`verify-glyph-text-measure274-native.py`](../scripts/verify-glyph-text-measure274-native.py)
SHA-pins the **whole 274B original body**, all **71 instruction
boundaries**, and all **13 genuine physical PE relocation roles**:

| Original physical site | Original native target |
| --- | --- |
| PE HIGHLOW `+0x0A` | security cookie `0x005B25C0` |
| PE HIGHLOW `+0x18` | 22-HFONT font table `0x005B66F0` |
| E8 `+0x1C` / field `+0x1D` | already exact folded native 22B font index `0x00414580` |
| E8 `+0x37` / field `+0x38` | original CRT memset `0x00544760` |
| PE HIGHLOW `+0x5A` | `MultiByteToWideChar` IAT `0x0056C124` |
| PE HIGHLOW `+0x5F` | true native window global `0x005B6758` |
| E8 `+0x63` / field `+0x64` | original 16B window getter `0x0040C300` |
| PE HIGHLOW `+0x6B` | `GetDC` IAT `0x0056C2AC` |
| PE HIGHLOW `+0x85` | `SelectObject` IAT `0x0056C02C` |
| E8 `+0x96` / field `+0x97` | native CRT wide length `0x00548300` |
| PE HIGHLOW `+0xC2` | `GetTextExtentPoint32W` IAT `0x0056C030` |
| PE HIGHLOW `+0xF4` | original font-restore `SelectObject` IAT `0x0056C02C` |
| E8 `+0x109` / field `+0x10A` | actual security-cookie check `0x005429EE` |

The verifier independently reads and hashes the whole original folded
font index/window getter methods and the original native font-array
end's `this+0x58` (22 pointer elements). It does **not** solve
original target addresses from the compiled candidate. Pinned MSVC
19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` naturally emits the complete original **274B/71 i386**,
with **222/222 nonrelocated bytes** and **all 5 genuine E8/eight PE
HIGHLOW fields** in their independently native-confirmed positions.

```text
glyph_text_measure_274: exact (274/274 bytes)
Exact replay: 1/1 units, 1 cold object
```

This is **one new game-authored exact physical function /274 original
`.text` bytes**. The earlier [79B font resource release and 17B
array-end](GLYPH_FONT_ARRAY22_RELEASE79_STRICT_EXACT.md) remain separate,
with no duplicate native code credit; the same original 2,227B game
text raster core remains SOURCE-PRESENT/NONEXACT in its own body.
The original 542B Alpha Boss and 681B GDI surface creation Boss are
already independently whole-exact and are not re-credited. No
whole-repository cold replay was used.

```sh
scripts/repo-python scripts/verify-glyph-text-measure274-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextMeasure274.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
