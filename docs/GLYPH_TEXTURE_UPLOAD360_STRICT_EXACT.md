# CORE/RECON-1068 — complete original 360B queued D3D9 glyph texture-upload Boss, strict exact

Pinned original Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The actual game-owned `0x004145D0` glyph-render job executor occupies an
entire **360B/128-i386** native function, original SHA-256
`76223b12344a822e9f79546f3b197ce349d9b3467ebbbe2f3b65f73c411b0dcc`.
It is the downstream executable action of the separately accepted 132B
glyph-text render-job capture; it is **not** a 360B arbitrary GDI
texture stub, nor a folded standard-library function.

## True upload job fields, native Direct3D9 and pixel flow

The source [`GlyphTextureUpload360.cpp`](../src/GlyphTextureUpload360.cpp)
uses the [single canonical 0x58-byte `NativeGlyphRenderJob`](../src/NativeGlyphRenderJob.hpp) type, shared with the native-exact 132B constructor and 23B destructor. [CORE/RECON-1069](GLYPH_RENDER_JOB_58_NATIVE_UNIFIED.md) corrected the earlier parallel borrowed view without changing the uploaded native bytes:

| Native job offset | Independently demonstrated role |
| --- | --- |
| `+0x00` | `NativeGlyphCanvasStorage*` producing source glyph pixels |
| `+0x04` | captured `IDirect3DBaseTexture9*`, invoked as real `IDirect3DTexture9*` destination COM object (**not** an opaque color word) |
| `+0x08 .. +0x17` | 16B destination `RECT` for the locked D3D9 surface |
| `+0x18 .. +0x27` | 16B source/region `RECT` with row/column source offsets |
| `+0x28` | Optional `uint8_t*` completion flag, set to 1 after cleanup |
| `+0x2C` | Unobserved 32-bit member; **not** initialized by the exact 132B constructor |
| `+0x30 .. +0x57` | 40B `std::function<void()>` post-upload callback |

The entire original method obtains D3D9 surface level 0 from the
texture (`GetSurfaceLevel` vtable offset `0x48`); locks the destination
`RECT` via `LockRect` (`+0x34`), then copies each real glyph scanline
from the native canvas using `std::memcpy`, source pixel stride and
D3D9 destination pitch. The source byte origin uses `pixel_region.left`
while copy width is `(right-left)*4` bytes. After the scanlines,
it genuinely `UnlockRect`s, `Release`s the COM surface and clears
that temporary pointer. It calls the original independently exact
**182B GDI canvas release**, invokes the distinct original **97B
allocator-owned canvas release** `0x00413BE0`, signals the optional
completion pointer, and conditionally executes the task's real
`std::function<void()>`. No extra `ReleaseDC`, unexpected null
fallback or artificial cleanup handler has been added.

The initial legitimate `NativeGlyphCanvasView* glyph` local was an
extra cached alias of the real canvas field. Pinned MSVC emitted a
360B candidate with incorrect stack frame and getter receiver
lifetime, not the native instructions. Removing that redundant local
and using each live source canvas field access restored the original
32-byte/frame stack ownership. The final code naturally compiles to
**360B/128 instructions and all 316/316 nonrelocation bytes**, with
**nine original E8 and two native PE HIGHLOW** fields:

| Original instruction offset | Physical target |
| --- | --- |
| `+0x61` | `0x004156A0` whole-exact 20B bitmap pixels getter |
| `+0x6E`, `+0xD7` | `0x004156C0` whole-exact 20B canvas stride getter |
| `+0xC1` | `0x00543E20` original CRT memcpy |
| `+0x113` | `0x00416360` whole-exact 182B native canvas GDI release |
| `+0x124` | `0x00413BE0` separate 97B original allocator release |
| `+0x142` | `0x004145A0` already exact 48B `std::function` nonempty check |
| `+0x154` | `0x00414740` newly whole exact 59B `std::function` invocation |
| `+0x15F` | `0x005429EE` actual security-cookie check |

Original PE HIGHLOW fields `+0x07 -> 0x005B25C0` (security cookie) and
`+0x120 -> 0x005B8894` (genuine allocator-global pointer) are
independently verified. D3D9 COM vtable calls are *indirect*, not
counted as E8. The same source naturally emits the native complete
**59B/23-i386 standard-library callback operator** at `0x00414740`,
with three genuine nested E8 to original `_Empty` 45B
`0x00414A80`, CRT bad function call `0x00540E98` and
`_Getimpl` `0x00414AD0`. Its 47/47 comparable bytes are exact.
All previously exact callback helpers are not counted again.

Read-only independent original verification
[`verify-glyph-texture-upload360-native.py`](../scripts/verify-glyph-texture-upload360-native.py)
SHA-attests the entire 360B original body and 59B callback helper,
all 128 and 23 x86 instruction boundaries, native COM slot offsets,
physical original E8 and PE HIGHLOW sites/targets, and the separate
original 132B task-capture and 182B GDI release physical bodies.
Pinnned MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` generates both authentic entire methods:

```text
glyph_texture_upload_360: exact (360/360 bytes)
glyph_upload_callback_invoke_59: exact (59/59 bytes)
Exact replay: 2/2 units, 1 cold object
```

This adds **one game-authored entire original function/360 distinct
`.text` bytes**, plus **one generic STL whole-native 59B unit**
(`origin=unknown/review`, zero game-authored credit). The already exact
132B game job capture, 23B destructor, folded 48B bool helper, 182B
canvas release and 20B getters are **not** re-credited. Earlier
source-internal names calling `+0x04` a color and `+0x28` a mode
were incorrect: this independent native body establishes their
actual *consumer* roles. The full source-present 2,227B glyph text
rasterization parent remains **NONEXACT** pending complete producer
layout/queue ABI reconciliation; source-level member names do not
imply the original 2,227B physical code was exact.

No original target was patched, no machine-code literals substituted
for real D3D COM APIs, no shortened original extent was compared,
and no full-project cold replay was run.

```sh
scripts/repo-python scripts/verify-glyph-texture-upload360-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextureUpload360.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1069 — canonical shared glyph render job type

The earlier parallel `NativeGlyphUploadJobView` is now superseded by
[one true 0x58B native glyph render job](GLYPH_RENDER_JOB_58_NATIVE_UNIFIED.md)
with a correct D3D texture at +0x04 and completion-byte pointer +0x28.
The actual original 360B method is directly compiled as
`NativeGlyphRenderJob::operator() const` on the **same class** whose
132B constructor and 23B destructor are already whole exact.
All three unique game-authored native extents remain exact, with no
new head/byte credit and no invented forwarding method.

## CORE/RECON-1070 — original 97B allocator release now real typed source

This whole-exact 360B uploader's original E8 `+0x124` now has a
[complete separate strict 97B `DiagnosticAllocator::release_object`
implementation](GLYPH_CANVAS_ALLOCATOR_LIFETIME_97_16_49_62_STRICT_EXACT.md)
for the actual 0x124B `NativeGlyphCanvasStorage`. Its genuine 16B
`std::destroy_at`, 49B deleting destructor and 62B GDI cleanup are
also independently exact. The uploader no longer uses a borrowed
untyped `release_canvas` alias; its exact 360B and 11 native relocation
roles remain unchanged, and the 97/16/49/62 code heads are only
counted once at their original physical addresses.
