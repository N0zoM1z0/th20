# CORE/RECON-1071 — complete original 73B game GDI glyph canvas factory, exact native `class`/`noexcept` owner

Pinned target: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original `0x00413C50` is a whole **73B/22-i386**
`DiagnosticAllocator::allocate_object<NativeGlyphCanvasStorage>`
member-template specialization, original SHA-256
`b82f916474d1365d308fa06635f6d8b54d7f305f8e6003f360d97879e7c9ee91`.
The real **2,227B/470-i386** GDI glyph text-raster Boss at `0x00415830`
physically invokes this 73B factory via original E8 **`+0x89`** to
allocate the same concrete **0x124B** glyph surface that its already
whole-exact **360B queued D3D9 upload** later releases.

## Three original native calls and the real compiler type contract

The entire native 73B function has **exactly three E8 and zero PE
HIGHLOW**, independently read from the locked original PE:

| Original E8 instruction | Real physical destination | Meaning |
| --- | --- | --- |
| `+0x0E`, COFF relocation field `+0x0F` | `0x0054275D` | Actual CRT scalar `operator new` for exactly `0x124` bytes |
| `+0x27`, field `+0x28` | `0x0040C080` | Compiler-generated **31B class-zeroing** `__autoclassinit2` helper, previously whole-exact under a folded original head |
| `+0x2F`, field `+0x30` | `0x00414200` | Actual game-owned **124B/28-i386** GDI canvas constructor, already whole-exact |

The original also checks the genuine null allocation result and
returns the constructed concrete pointer or null, ending with an
actual `ret 4`. It has no lock, allocation retry or invented fallback
inside its own 73B extent; these concepts remain separate runtime
owners.

The previously maintained
[`NativeGlyphCanvasStorage`](../src/NativeGlyphCanvasStorage.hpp)
had been provisionally declared as **`struct`** with a default
constructor that could throw. Both details were material:
ordinary `new NativeGlyphCanvasStorage()` originally generated a
**122B** C++20 candidate with additional exception-cleanup code.
Marking just its constructor `noexcept` reduced that candidate to
**60B**, but did not emit the native 31B class-zeroing call.
Correcting the source to the **real `class` with public observed
native fields** *and* a **`noexcept` default constructor** makes pinned
MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` naturally emit the complete original **73B/22 i386**
method and its true `__autoclassinit2` E8.

This is an observed compiler lowering and a meaningful native object
exception contract, not a fabricated `memset` added by hand. The
existing 124B source constructor still compiles **124/124** after
adding `noexcept` to its declaration/definition. The distinct
**97B allocator release, 16B `std::destroy_at`, 49B scalar-deleting
destructor and 62B real GDI canvas destructor** also continue to
replay exact under the corrected `class` type, after their C++ template
mangling is updated (`struct` U to `class` V). The 62B destructor's
five real trailing INT3 alignment bytes are separately checked, not
credited as source instructions.

## Actual 2,227B parent source and independent native proof

[`src/GlyphCanvasAllocate73.cpp`](../src/GlyphCanvasAllocate73.cpp)
explicitly instantiates the **existing real game
`DiagnosticAllocator::allocate_object<T>` implementation** in
[`DiagnosticObjectFactories.hpp`](../src/DiagnosticObjectFactories.hpp)
for this same 0x124B class. The surrounding 2,227B typed text-core
source now calls `process_allocator->allocate_object<NativeGlyphCanvasStorage>`
and uses `extern template` to avoid a duplicate canonical object
body. The parent remains **SOURCE-PRESENT/NONEXACT** at
**2,080B/486-i386, 25 E8/54 DIR32** versus original
**2,227B/470-i386, 25 E8/43 physical PE HIGHLOW**. No false
parent credit is claimed for repairing this factory edge.

The read-only independent original checker
[`verify-glyph-canvas-factory73-native.py`](../scripts/verify-glyph-canvas-factory73-native.py)
SHA-attests the whole 73B/22 original, actual native return and all
three E8 targets, the complete original 2,227B parent and its E8
`+0x89`, and the complete native 31B folded class-initialization
and 124B canvas-construction code. The independently native-anchored
canonical receipt verifies **73B/73B**, **61/61 nonrelocated bytes**
and all three original E8 field positions:

```text
glyph_canvas_allocator_allocate_73: exact (73/73 bytes)
glyph_canvas_constructor_124: exact (124/124 bytes)
glyph_canvas_allocator_release_97: exact (97/97 bytes)
glyph_canvas_destroy_at_16: exact (16/16 bytes)
glyph_canvas_scalar_deleting_dtor_49: exact (49/49 bytes)
glyph_canvas_destructor_62: exact (62/62 coverage; 67/67 including genuine INT3 alignment)
glyph_texture_upload_360: exact (360/360 bytes)
glyph_upload_callback_invoke_59: exact (59/59 bytes)
glyph_text_job_capture_132: exact (132/132 bytes)
glyph_text_job_dtor_23: exact (23/23 bytes)
Exact replay: 10/10 units, 5 affected object providers
```

This adds **one new game-authored exact physical function /73 distinct
original `.text` bytes**. The original folded 31B class-init helper,
previously credited game 124B ctor, all four exact downstream lifetime
heads, 360B upload and 132B/23B glyph job closure **are not**
re-credited. No original target code patch, fake no-op/padding,
compiler-emitted helper forgery or full-project cold replay was used.

```sh
scripts/repo-python scripts/verify-glyph-canvas-factory73-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphCanvasAllocate73.cpp \
  --source src/GlyphCanvasConstruct124.cpp \
  --source src/GlyphCanvasAllocatorLifetime.cpp \
  --source src/GlyphTextCore2227.cpp \
  --source src/GlyphTextureUpload360.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
