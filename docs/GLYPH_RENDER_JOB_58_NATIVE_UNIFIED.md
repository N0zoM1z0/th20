# CORE/RECON-1069 — unify the real 0x58B glyph job constructor, destructor and D3D9 upload operator

Original target: immutable Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original game uses **one physical 0x58-byte queued glyph-render job**.
Three previously separate source reconstructions are truly methods of
this one object and are each **whole-native strict exact**:

| Genuine original method | Original physical body | Canonical source / real meaning |
| --- | ---: | --- |
| Constructor at `0x00413EC0` | **132B/49 i386** | Capture canvas pointer, D3D9 target, destination/source rectangles, completion pointer, and borrowed `std::function` callback |
| Destructor at `0x004142C0` | **23B/11 i386** | Destroy the true `std::function<void()>` member at `this+0x30` |
| `operator() const` at `0x004145D0` | **360B/128 i386** | Execute complete GDI bitmap-to-D3D9 surface upload, native canvas cleanup, completion flag and callback |

The source is now unified under the actual
[`NativeGlyphRenderJob`](../src/NativeGlyphRenderJob.hpp) type,
not two inconsistent constructors/views. The true original i386
object has the following physical offsets:

| Offset | Current source owner and independent native evidence |
| --- | --- |
| `+0x00` | real `NativeGlyphCanvasStorage*` to the original 0x124-byte GDI glyph canvas |
| **`+0x04`** | `IDirect3DBaseTexture9*` captured; the upload invokes this as an actual `IDirect3DTexture9*` COM object at vtable `+0x48` |
| `+0x08` | 16-byte `NativeTextTransform4` destination/lock rectangle |
| `+0x18` | 16-byte `NativeTextTransform4` source-image rectangle |
| **`+0x28`** | `uint8_t*` native completion flag, written with one byte after the upload |
| `+0x2C` | genuine 4-byte storage **not written by the original constructor** |
| `+0x30` | native **40B `std::function<void()>`** owned callback |

The earlier source field names `color` for `+0x04` and integer `mode`
for `+0x28` were **semantically wrong**: they appeared to match the
132B constructor because those fields are copied as opaque 32-bit
words, but only the actual whole-exact **360B D3D9 upload** proves their
correct pointer roles. The original native 132B constructor at
`0x00413EC0` does not use the values beyond copying them; preserving
its exact code does **not** vindicate its earlier C++ types.

The user-visible producer source
[`GlyphTextCore2227.cpp`](../src/GlyphTextCore2227.cpp) now instantiates
this same class, storing the genuine incoming D3D base texture
pointer, and treats the original raw 32-bit completion argument word
as an i386 callback pointer. **The external submit/render caller's
original parameter spelling and valid completion-pointer provenance
remain unresolved**; its 2,227B text core is still SOURCE-PRESENT,
NONEXACT. The current naturally compiled C++20 source is
**2,080B/486 i386 (25 E8/54 DIR32)** against original
**2,227B/470 (25 E8/43 native HIGHLOW)**. No success claim for the
parent's complete callback/error path or for runnable linked output
is made.

The original `NativeGlyphRenderJob::operator() const` body is now
compiled directly in
[`GlyphTextureUpload360.cpp`](../src/GlyphTextureUpload360.cpp),
not forwarded to an extra generated `upload_4145d0` wrapper with an
unobserved E8. It still calls the true D3D9 texture/surface vtables,
uses the whole-exact GDI canvas accessors and cleanup, and executes
the previously exact generic 59B `std::_Func_class<void()>::operator()`
callback. The native allocator's 97B release method remains a distinct
unresolved callee, as before.

## Canonical whole-body validation and code identity

This is a **semantic type and translation-unit ownership correction**,
not a new machine-code acceptance. Under pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`, two and only
two affected canonical object providers were recompiled:

```text
glyph_text_job_capture_132: exact (132/132 bytes)
glyph_text_job_dtor_23: exact (23/23 bytes)
glyph_texture_upload_360: exact (360/360 bytes)
glyph_upload_callback_invoke_59: exact (59/59 bytes)
Exact replay: 4/4 native physical units, 2 cold source objects
```

The constructor retains **128/128 ordinary original bytes and its one
real E8**; the destructor retains **19/19 ordinary original bytes and
its one E8**; the upload retains **316/316 ordinary original bytes,
nine original E8/two HIGHLOW**. No prior source bytes are patched,
no fake ABI or extra forwarding wrapper is introduced, and the prior
whole exact 79B font cleanup, 274B text measurement and 542B Alpha
processor remain independent native code heads.

**No new game-authored or generic exact head/byte credit** is accrued
by this corrected structure: those three game methods and the one
generic callback had been accepted in earlier checkpoints. Updating
their original function signatures and source-owner identity keeps
that same physical native identity, instead of falsely creating new
functions. No full-graph cold replay was run.

```sh
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextCore2227.cpp \
  --source src/GlyphTextureUpload360.cpp
scripts/repo-python scripts/verify-glyph-texture-upload360-native.py
scripts/repo-python scripts/verify-glyph-text-job-dtor23-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1070 — 97B allocator release is now actually whole exact

The earlier source-absent note in this document is superseded. The
genuine native 360B uploader now directly invokes
`process_allocator->release_object(canvas)` with the real concrete
`NativeGlyphCanvasStorage` owner. That [entire 97B allocator release,
16B STL destroy_at, 49B scalar-deleting destructor and 62B real GDI
canvas destructor](GLYPH_CANVAS_ALLOCATOR_LIFETIME_97_16_49_62_STRICT_EXACT.md)
are all separately whole strict exact in the original physical native
chain, including genuine 62B+5 INT3 compiler-contribution accounting.
No original game upload, job-capture or destructor code is credited twice.

## CORE/RECON-1071 — real 73B canvas class factory now whole strict exact

The same concrete GDI canvas is now produced by an
[independently whole-exact original 73B allocator factory](GLYPH_CANVAS_ALLOCATE73_CLASS_NOEXCEPT_STRICT_EXACT.md)
called from the real 2,227B text Boss E8 `+0x89`. The canonical C++
owner is a `class` with real observed public 0x124B fields and a
`noexcept` constructor. The source naturally reproduces original
scalar `operator new`, folded 31B class-zeroing E8 and already exact
124B constructor; its entire 97B/16B/49B/62B release chain remains
whole-exact under the corrected C++ `class` mangling. The original
2,227B text producer remains SOURCE-PRESENT/NONEXACT; no previous
constructor, destructor or generic helper code is counted twice.
