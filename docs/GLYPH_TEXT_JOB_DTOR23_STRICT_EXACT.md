# CORE/RECON-1062 — whole native 23B glyph queued-text job destructor exact

Locked original Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Original `0x004142C0..0x004142D6` is a distinct **23B/11-i386**
game-authored queued GDI glyph render job destructor, original
SHA-256 `3aacecdb1b3170aea87b3cf029b04e1e4ddbba1e64fa05d9c05920c198fe9d28`.
The full **2,227B/470-i386** text-raster core at `0x00415830` calls
this physical head via genuine original E8 **`+0x842`**.

The original 23B destructor takes the true `NativeGlyphRenderJob`
receiver in ECX, adds **`+0x30`** to reach its existing 40B
`std::function<void()>` member, and invokes the complete original
**20B `std::function` destructor** `0x00414400` at its only E8
**`+0x0D`**. It ends in a bare `ret`, with **zero native PE
HIGHLOW**. No additional cleanup, virtual dispatch, hidden allocation
or harmless-looking destructor call is present in those original
23 machine-code bytes.

That custom closure is already naturally and meaningfully maintained
in [`src/GlyphTextCore2227.cpp`](../src/GlyphTextCore2227.cpp)
with the separately exact **132B glyph job constructor**. The
compiler-generated C++ destructor naturally emits the **whole
23B/11-i386** native function, all **19/19 nonrelocation code
bytes** and the one independently original PE E8 to the existing
20B destructor; it is not a user-authored pseudo-wrapper or a
shortened comparison prefix. The original generic 20B target is
already exact in a different C++ owner and is **not** credited twice.

[`verify-glyph-text-job-dtor23-native.py`](../scripts/verify-glyph-text-job-dtor23-native.py)
SHA-pins both complete original 23B and 20B bodies, validates every
physical native E8, the exact `this+0x30` receiver adjustment,
original `ret`, the original parent 2,227B/470 source caller, and
the full canonical unit receipt. Focused pinned MSVC 19.44 i386
C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
strict replay of this **one already-present glyph-job provider**:

```text
glyph_text_job_capture_132: exact (132/132 bytes)
glyph_text_job_dtor_23: exact (23/23 bytes)
Exact replay: 2/2 units, 1 cold object
```

This is **one new game-authored exact function /23 original `.text`
bytes**. The previous 132B constructor and 20B standard destructor
remain independent accepted physical code and are not counted again.
The original 2,227B GDI text core remains **SOURCE-PRESENT, NONEXACT**;
this 23B destructor does not imply successful task playback, linked
runtime success or whole-game equivalence. No project-wide cold
replay was run.

```sh
scripts/repo-python scripts/verify-glyph-text-job-dtor23-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextCore2227.cpp
```

## CORE/RECON-1069 — canonical job ABI now shared with D3D upload

The real +0x30 function member destructor is now maintained on
[the single 0x58B `NativeGlyphRenderJob` class](GLYPH_RENDER_JOB_58_NATIVE_UNIFIED.md)
together with the exact 132B D3D-texture/geometry/flag constructor and
its exact 360B D3D9 `operator() const`. The original 23B destructor
remains unchanged, 23/23 exact; no duplicate native code credit.
