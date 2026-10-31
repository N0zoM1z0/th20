# CORE/RECON-1070 — whole native GDI canvas lifetime: 97B allocator, 16B destroy_at, 49B deleting destructor, 62B cleanup

Immutable original: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The now whole-strict-exact **360B D3D9 glyph texture uploader**
`0x004145D0` invokes native `0x00413BE0` via original E8 **`+0x124`**
after copying pixels and releasing its surface. The callee is not an
unknown one-off release function: it is the **97B/33-i386 TH20
`DiagnosticAllocator::release_object<NativeGlyphCanvasStorage>`**
instantiation. It calls a **16B/8-i386 `std::destroy_at`** helper, which
calls an actual **49B/18-i386 scalar-deleting destructor** with flag 0,
which calls the real **62B/22-i386 glyph canvas destructor**. That final
native destructor invokes the already independently whole-exact **182B
GDI surface resource cleanup** `0x00416360`.

## Independently complete physical original chain

| Original head | Whole code extent | Original physical callers and nested dependencies | Native-original SHA-256 |
| --- | ---: | --- | --- |
| `0x00413BE0` allocator release | **97B/33 i386** | Original 360B upload E8 `+0x124`; 6 native E8 to 16B destroy, lock-slot 1, lock_guard ctor, original scalar delete, guard dtor, cookie check; PE HIGHLOW cookie and real lock registry | `843797acd1750b9ccdc2b052dd523a64794fc3da1678e9f73f841c9d96dfded4` |
| `0x00413CD0` STL `std::destroy_at` | **16B/8 i386** | Allocator 97B E8 `+0x1F`; only E8 `+0x08` to 49B scalar-deleting destructor | `9fb315c8680ef95449989d6f70927d7d1fb25c306b2ac18f480eca7b0c65c5b4` |
| `0x004147E0` native scalar-deleting destructor | **49B/18 i386** | 16B destroy_at E8 `+0x08`; E8 `+0x0A` to 62B ordinary destructor and E8 `+0x20` to native sized-delete `0x0054278D` | `8840f29b61c1350c8d795d720a6d1811a26d33815cc99656e626f9c14fd0d50b` |
| `0x00414460` ordinary native destructor | **62B/22 i386** | 49B scalar dtor E8 `+0x0A`; E8 `+0x29` to real exact 182B GDI cleanup; authentic SEH handler and cookie PE HIGHLOW | `d9d5ef3df338f8174402f912e2bb04d827490be090fd184f85fefccce32e1709` |

All four physical heads are **distinct original code**, not shortened
prefixes or aliases. The original 62B destructor ends with an actual
`ret` at `+0x3D`. The native executable genuinely contains exactly
**five `0xCC` INT3 alignment bytes** immediately after that return
(`+0x3E..+0x42`). MSVC emits **67B total COFF contribution** for this
62B function, so the canonical strict unit uses **`size=62`,
`compare_size=67`** and checks the entire original 67B region including
all five real alignment bytes. It only **credits 62 bytes** of physical
TH20 function code; the five alignment bytes are not counted as an
extra function or padded source instructions. No target bytes were
modified.

## Real C++ owner, no false lifetime stand-in

The original canvas allocation and state owner is the existing real
[`NativeGlyphCanvasStorage`](../src/NativeGlyphCanvasStorage.hpp):
a **0x124-byte native object** with the observed format, pixel, HDC,
HGDIOBJ and bitmap fields. This class already has a whole-exact
**124B native constructor** `0x00414200` and a separate whole-exact
182B borrowed GDI cleanup. Adding its **genuine nonvirtual destructor**
and implementing it in
[`GlyphCanvasAllocatorLifetime.cpp`](../src/GlyphCanvasAllocatorLifetime.cpp)
with actual `NativeGlyphCanvasView::release_surface_416360()` naturally
recreates the entire original **62B destructor/49B deleting wrapper**,
including the real SEH stack frame and native code alignment.
The explicit game allocator template instantiation uses the already
established `DiagnosticAllocator::release_object<T>` with
`std::destroy_at`, native recursive lock slot **1**, and the original
scalar `operator delete` family.

A shadow/provisional `NativeCanvasReleaseOwner` originally reproduced
these four compiler shapes in private probes. Crucially, the accepted
source **does not use that parallel placeholder**: it uses the same
`NativeGlyphCanvasStorage` concrete type that the accepted 124B ctor
constructs and the accepted 360B D3D uploader destroys. The uploader
now calls `process_allocator->release_object(canvas)` naturally and
replays its entire **360/360** code with exact original E8 `+0x124`
to this 97B physical head. The previously borrowed and incorrectly
named `release_canvas_413be0` alias is no longer used by accepted
source. The 132B glyph job capture/23B destructor share the actual
0x58B `NativeGlyphRenderJob` class with the 360B uploader, so ownership
and typed layout agree across these originally separate artifacts.

The independently locked-PE checker
[`verify-glyph-canvas-allocator-lifetime-native.py`](../scripts/verify-glyph-canvas-allocator-lifetime-native.py)
SHA-attests all four entire original extents, **all** original E8 and
PE HIGHLOW destinations, native destructor `ret` width, the real five
`0xCC` bytes, the entire original 360B D3D9 parent and the previously
accepted physical 124B constructor and 182B cleanup. It separately
checks each canonical strict receipt and independently pinpoints its
physical original parent/callee relation.

Pinned MSVC 19.44 C++20 i386 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`, with **only five affected object providers
cold rebuilt**, accepts:

```text
glyph_canvas_allocator_release_97: exact (97/97 bytes)
glyph_canvas_destroy_at_16: exact (16/16 bytes)
glyph_canvas_scalar_deleting_dtor_49: exact (49/49 bytes)
glyph_canvas_destructor_62: exact (62/62 coverage bytes; 67/67 compared bytes)
glyph_canvas_constructor_124: exact (124/124 bytes)
glyph_canvas_release_182: exact (182/182 bytes)
glyph_texture_upload_360: exact (360/360 bytes)
glyph_upload_callback_invoke_59: exact (59/59 bytes)
glyph_text_job_capture_132: exact (132/132 bytes)
glyph_text_job_dtor_23: exact (23/23 bytes)
Exact replay: 10/10 units, 5 affected cold objects
```

This contributes **four newly distinct whole-native exact heads /224
original `.text` function bytes**, of which the **97B allocator
release, 49B native deleting wrapper and 62B GDI canvas destructor
are 208 game-authored native bytes**, while the **16B generic
`std::destroy_at`** retains `origin=unknown, disposition=review` and
adds **zero game-authored credit**. Previously exact folded/borrowed
lock guards, 124B construction, 182B release, 360B upload, glyph-job
closure and generic callback are not re-credited.
The original **2,227B GDI text producer remains SOURCE-PRESENT/NONEXACT**;
no runtime linkage or equivalent game playback is claimed. No entire
repository cold replay or byte patch was run.

```sh
scripts/repo-python scripts/verify-glyph-canvas-allocator-lifetime-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphCanvasAllocatorLifetime.cpp \
  --source src/GlyphCanvasConstruct124.cpp \
  --source src/GlyphCanvasRelease182.cpp \
  --source src/GlyphTextureUpload360.cpp \
  --source src/GlyphTextCore2227.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
