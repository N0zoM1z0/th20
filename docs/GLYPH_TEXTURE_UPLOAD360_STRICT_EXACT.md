# CORE/RECON-1068 — complete original 360B D3D9 glyph texture upload Boss, whole strict exact

Locked original Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The native game-owned `0x004145D0` is a **complete 360B/128-i386**
queued GDI-to-D3D9 glyph texture upload Boss, original SHA-256
`76223b12344a822e9f79546f3b197ce349d9b3467ebbbe2f3b65f73c411b0dcc`.
It is the actual task invoked by the 40B `std::function<void()>` at
`+0x30` of the previously whole-exact **132B glyph render-job capture**.
The source reconstructs real D3D9/COM calls and the complete game
pixel-copy, cleanup, completion and callback sequence; this is not an
inline surrogate of the original 2,227B text producer.

## Correcting the original 0x58B job receiver hypothesis

Original native code proves the following physical job fields:

| Native receiver field | Actual operation/evidence |
| --- | --- |
| `+0x00` | borrowed genuine `NativeGlyphCanvasStorage*`, 0x124B font bitmap owner |
| **`+0x04`** | **`IDirect3DTexture9*`**, loaded and invoked via true COM vtable `+0x48` for `GetSurfaceLevel` (**not** the earlier guessed color word) |
| `+0x08..+0x17` | 16B Win32 `RECT` used in actual D3D9 surface `LockRect` |
| `+0x18..+0x27` | 16B source pixel rectangle, originally byte-start/row offsets and four-byte copy width |
| **`+0x28`** | **optional `uint8_t*` completion flag**, conditionally written with `1` (**not** an arbitrary integer mode) |
| `+0x2C` | genuine 32-bit job storage, not initialized by the original 132B constructor |
| `+0x30..+0x57` | real 40B `std::function<void()>` completion callback |

The maintained
[`NativeGlyphUploadJobView.hpp`](../src/NativeGlyphUploadJobView.hpp)
uses a **borrowed** full-size 0x58B typed layout with offset and size
assertions. The separately accepted original 132B glyph-job constructor
has an identical physical byte layout but still has provisional
color/mode field names in its producer source, now contradicted by
**direct native D3D usage**. This is explicitly an outstanding type
reconciliation, **not** proof that a color word is a texture pointer;
the original code bytes and both callback lifetimes remain separate.

The full maintained
[`GlyphTextureUpload360.cpp`](../src/GlyphTextureUpload360.cpp)
uses the real `IDirect3DTexture9::GetSurfaceLevel(0,...)` COM method,
`IDirect3DSurface9::LockRect`, native `D3DLOCKED_RECT::Pitch/pBits`
and a real Win32 rectangle. It copies a rectangular region from the
already exact native GDI bitmap's pixel pointer, stepping the source
rows by the actual canvas stride, stepping destination rows by the
locked surface pitch, and copying genuine `(right-left)*4` bytes per
row via CRT `memcpy`. Its source pixel left offset is applied in
**actual native byte units**; the source does not secretly normalize
it to four-byte pixels or add a defensive bounds check that is absent
from the original. It then unlocks the surface, releases the COM
surface, calls the separately exact 182B canvas GDI cleanup,
uses the genuine game allocator's separate 97B release method,
sets the observed optional completion flag and invokes the real
`std::function` callback only when nonempty.

## Native source exactness and originally attested relocations

A private first C++ source cached an extra `NativeGlyphCanvasView*`
alias in a local pointer, adding a stack slot and moving true native
getter calls. Its full extent happened to remain **360B**, but its
ordinary machine-code/relocation fields did not match. Removing the
redundant alias, so that each real getter is called directly on the
job's `canvas` field, naturally compiles the entire original
**360B/128 instructions**, all **316/316 ordinary bytes** and all
**nine physical native E8/two PE HIGHLOW** relocation roles.
No manually patched instruction, byte array, fake COM call, raw NOP,
artificial allocation or shortened comparison is used.

Independent original PE attestation
[`verify-glyph-texture-upload360-native.py`](../scripts/verify-glyph-texture-upload360-native.py)
checks the entire immutable 360B body, original 128 instruction
boundaries through its bare `ret`, genuine D3D9 vtable methods
`+0x48`/`+0x34`/`+0x38`/IUnknown `+0x08`, the native completion-byte
store, and all the independently original call/data sites:

| Native original field/site | Original true target |
| --- | --- |
| HIGHLOW `+0x07` | security cookie `0x005B25C0` |
| E8 `+0x61` (REL32 `+0x62`) | exact 20B glyph pixels getter `0x004156A0` |
| E8 `+0x6E` (REL32 `+0x6F`) | exact 20B glyph stride getter `0x004156C0` |
| E8 `+0xC1` (REL32 `+0xC2`) | CRT `memcpy` `0x00543E20` |
| E8 `+0xD7` (REL32 `+0xD8`) | glyph stride getter again `0x004156C0` |
| E8 `+0x113` (REL32 `+0x114`) | exact 182B native GDI release `0x00416360` |
| HIGHLOW `+0x120` | global game allocator `0x005B8894` |
| E8 `+0x124` (REL32 `+0x125`) | separate 97B native allocator release `0x00413BE0` |
| E8 `+0x142` (REL32 `+0x143`) | already exact folded 48B callable-nonempty check `0x004145A0` |
| E8 `+0x154` (REL32 `+0x155`) | distinct 59B `std::_Func_class<void()>::operator()` `0x00414740` |
| E8 `+0x15F` (REL32 `+0x160`) | security cookie verification `0x005429EE` |

The nested original **59B/23-i386** generic standard-library callback
operator has SHA-256
`046e82dc1916704a61693bbbdce1a6efd5bb769dc093e70b82fbda342ba7f8ca`,
**three real original E8** to `0x00414A80`, `0x00540E98`, `0x00414AD0`,
and zero native HIGHLOW. The source naturally generates that
complete **59/59B** at its own distinct physical original head.
Its preexisting empty/nonempty and `_Getimpl` folded lower functions
are *not* credited again. The callback operator itself is generic
STL (`origin=unknown/review`) and earns **zero game-authored bytes**.

Pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
canonical replay only recompiles the new source owner:

```text
glyph_texture_upload_360: exact (360/360 bytes)
glyph_upload_callback_invoke_59: exact (59/59 bytes)
Exact replay: 2/2 units, 1 cold object
```

This adds **one game-authored exact head /360 original `.text` bytes**
and one distinct **generic exact head /59 original bytes**.
The independently exact 132B job constructor, 23B job destructor,
182B GDI cleanup and all original canvas accessors are not counted
twice. The 2,227B text core, 294B submit wrapper and allocator's
97B deallocation method remain independently unresolved original
functions. No whole-repository cold replay was performed.

```sh
scripts/repo-python scripts/verify-glyph-texture-upload360-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphTextureUpload360.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
