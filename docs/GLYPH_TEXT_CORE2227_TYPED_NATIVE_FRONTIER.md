**CORE/RECON-1060 CURRENT STATUS:** The real queue submission method `0x004162F0` is now [whole 56/56B strict exact](GLYPH_TEXT_QUEUE_SUBMIT56_STRICT_EXACT.md). Its original input is a borrowed `std::function<void()>&`; the main source now constructs a real lvalue before passing it to the native `std::_Unfancy`/queue bridge. The current 2,227B source candidate is **2,072B/484 i386, 25 E8/54 DIR32**, still NONEXACT. Earlier 2,052B/481/24-E8 statistics below are historical.

# CORE/RECON-1058 — complete original 2,227B glyph text rasterizer, typed game-source frontier

Target: original Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The native `0x00415830` glyph text/GDI renderer is a complete
**2,227B/470-i386** game-owned Boss, original whole-body SHA-256
`c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70`.
The original 294B text submission wrapper calls it at both native E8
`+0x6C/+0xD4`. The underlying original text builder has **25 E8
and 43 PE HIGHLOW**, including real GDI Win32 API imports, font tables,
font-size scale parameters, security/EH state and game globals.

## Maintained whole-stage C++20 source: not native exact

[`src/GlyphTextCore2227.cpp`](../src/GlyphTextCore2227.cpp)
implements a real **game-specific** font selection, GDI text drawing
and queued render submission protocol using the shared
[`NativeGlyphTextCore.hpp`](../src/NativeGlyphTextCore.hpp) declaration
also consumed by the existing 294B text-submit source.
The body preserves these independently observed original stages:

1. Lock the native process recursive mutex slot **0x12**, fetch
   the native HFONT array entry, acquire a fresh **0x124B GDI glyph
   canvas**, and select actual per-font outline radius/baseline
   across the original font indices. Preserve the real globally
   mutable native glyph scaling behavior.
2. Clear the original **0x202-byte** Unicode buffer portion,
   convert the source text via Windows `MultiByteToWideChar(932,
   ...,0x100)` and calculate the native allocated canvas width/height
   from the four real 32-bit geometry fields.
3. Call the separately whole-exact **104B canvas format fallback**
   (`0x004153D0`) with native requested bitmap mode `0x15`, read the
   exact **20B HDC getter** (`0x00415620`), select the actual font,
   set transparent background/converted GDI BGR text color and obtain
   Unicode length/true text extent through the Windows GDI APIs.
4. Support both original text paths: entire `TextOutW` when spacing
   is zero, or individual `wchar_t[2]` `TextOutW` calls with increasing
   requested advance. For shadow/outline mode, draw the source once,
   call the maintained **2,245B glyph compositor** (SOURCE-PRESENT
   but NONEXACT) on the actual canvas, then draw again.
5. Restore the prior selected font, invoke the separate maintained
   **542B three-format Alpha processor**, restore GDI state again,
   acquire native lock slot **0x13**, construct a real **0x58B glyph
   rendering job** from its canvas/color/two geometry words and the
   correct native `const std::function<void()>&` borrowed callback,
   then submit a new `std::function<void()>` to the original game
   job queue. Return the real GDI text width/height packed into the
   observed EDX:EAX 64-bit result ABI.

The exact source-level implementation/ownership of the native
**73B allocator**, original 102B callback-functor constructor,
**132B job constructor's caller cleanup**, and native queue
`0x004162F0` is not yet fully reconciled. The 132B job constructor
itself is separately [WHOLE STRICT EXACT](GLYPH_TEXT_JOB_CAPTURE132_STRICT_EXACT.md).
The native Win32/CRT/EH lowering, font table encoding, text queue
lifetime and resulting game-level rendering correctness remain
separate verification tasks, not established by compiling source.

## Immutable native proof and compiler comparison

[`verify-glyph-text-core2227-native.py`](../scripts/verify-glyph-text-core2227-native.py)
independently SHA-pins the **entire original 2,227B body** and all
470 instructions; confirms all **25 genuine original E8** and
**43 real PE HIGHLOW** roles with sampled exact original destinations;
verifies actual 294B parent E8 twice; and hashes the complete
original 2,245B compositor, 542B alpha processor and 104B
GDI fallback at their native original E8 positions.

The first natural pinned MSVC 19.44 i386 C++20 candidate was
**2,072B/486 instructions, 25 E8/54 DIR32**. Reconstructing the
original **132B captured glyph job constructor** corrected its
`std::function` ownership from by-value move to borrowed const-ref
copy, leaving the observed `+0x2C` field uninitialized. The current
unified C++ source now produces **2,052B/481 instructions, 24 E8/54
DIR32** versus original **2,227B/470, 25 E8/43 PE HIGHLOW**.
The surrounding native queue, std::function wrapper and MSVC EH
lowering still differ; the original file-format/raster font constants
have not been proven to link to the same data symbol owners.

**Status: SOURCE-PRESENT, NONEXACT**, with **zero credited original
2,227B parent exact bytes**. Its source is maintained and verified
as a complete gameplay-stage C++ candidate, but the entire original
physical extent does not match. The 132B real job capture, 681B
GDI creator and many nested glyph leaves remain separately exact
within their own canonical units. Original 578B formatter, 294B
submit, 542B Alpha processor and 2,245B compositor also remain
independent nonexact source owners.

No shared canonical exact provider is modified by this new parent
source or its header used only by the nonexact 294B submit wrapper.
The **only** accepted new source unit is the 132B capture in this
translation unit, with a scoped canonical cold replay and a
separately scoped refresh of its existing 93B std::function copy
callee. No full graph/cold replay was run.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/GlyphTextCore2227.cpp build/core1059-probes/GlyphTextCore2227.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-glyph-text-core2227-native.py \
  --candidate-object build/core1059-canonical/GlyphTextCore2227.obj
scripts/repo-python scripts/verify-glyph-text-job-capture132-native.py
scripts/repo-python scripts/verify-ascii-text-submit294-native.py \
  --candidate-object build/core1058-probes/AsciiTextSubmit294.obj
```

## CORE/RECON-1060 — real borrowed queue task bridge recovered

The source now uses the [whole-exact 56B
`NativeGlyphQueueView::submit_4162f0`](GLYPH_TEXT_QUEUE_SUBMIT56_STRICT_EXACT.md)
with a true `std::function<void()>&` lvalue instead of erroneously
passing a newly owned function by value. The original 56B E8
`+0x0D` calls the folded standard-library `_Unfancy` and E8 `+0x2C`
calls the original 151B queue backend. This raises the 2,227B C++
source candidate to **2,072B/484 i386** and **25 E8**, vs original
2,227B/470 and 25 E8/43 HIGHLOW. The native game queue backend,
function wrapper and main Boss remain independently nonexact.

## CORE/RECON-1062 — actual glyph render job destruction now exact

The native glyph render closure created by the previously exact 132B
constructor has a [whole exact 23B destruction method](GLYPH_TEXT_JOB_DTOR23_STRICT_EXACT.md)
called by original core E8 `+0x842`; its only E8 calls the already exact
20B std::function destructor on the +0x30 captured task member.
The custom glyph job ctor+dtor are both whole strict exact. This
2,227B game core itself remains SOURCE-PRESENT/NONEXACT and receives
no additional parent credit.
