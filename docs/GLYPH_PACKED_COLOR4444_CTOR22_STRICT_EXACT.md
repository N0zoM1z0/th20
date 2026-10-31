# CORE/RECON-1053 — complete original 22B ARGB4444 glyph color default constructor, strict exact

Locked original: Japanese TH20 v1.00a Steamless SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original `0x00414280` is a whole **22B/11-i386** native glyph
packed-color default constructor, original SHA-256
`b7fd8b74d2296f36938c0067299f46916f23a7f60c178579e2b2db4d478a0cc7`.
It zeros an actual **16-bit packed color value** in its receiver and
returns that same receiver pointer. There are no E8 instructions or
PE HIGHLOW data relocations in this complete native body.

The original source context is the **2,245B/612-instruction** GDI
glyph mask compositor at `0x00416420`, which has two separate BGRA32
and ARGB4444 alpha fill modes. In the ARGB4444 arm, it physically
calls the already exact **24B `PackedColor` copy/construct method** at
E8 `+0x4FD -> 0x004142A0`, then *separately* invokes the 22B default
constructor at E8 **`+0x505 -> 0x00414280`** before assigning the
bitwise converted alpha/RGB nibbles to its 16-bit color storage.
The 22B local's initialization is native meaningful state, not a
fabricated padding write or a folded alias of the 24B constructor.

The maintained
[`GlyphMaskComposite2245.cpp`](../src/GlyphMaskComposite2245.cpp)
now defines the genuine `NativeGlyphColor4444` value containing a
`std::uint16_t packed` and naturally default constructs it with
`packed(0)` before publishing the converted nibble pattern. This
correction restores the missing constructor call to the real
2,245B source and naturally emits the **entire 22B/11 original
machine instructions**, 22/22 ordinary bytes and zero native relocations.
The whole containing Boss advances from a 1,961B/536-i386 source
candidate to a **1,987B/538-i386** candidate with **27 E8/5 DIR32**;
the immutable original is still **2,245B/612**, 37 E8/5 native PE
HIGHLOW and remains SOURCE-PRESENT/NONEXACT.

Independent original proof
[`verify-glyph-packed-color4444-native.py`](../scripts/verify-glyph-packed-color4444-native.py)
SHA-attests the entire 22B original, the physical zeroing semantics
and absence of E8/HIGHLOW; it also independently checks the entire
2,245B/612 original compositor and its two real adjacent color
constructor calls. Pinned MSVC 19.44 x86 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
replays this original 22B physical unit and all four pre-existing
PMR-vector helper units from the **same** canonical source object:

```text
glyph_mask_offsets_vector_ctor_63: exact (63/63 bytes)
glyph_mask_offsets_vector_dtor_20: exact (20/20 bytes)
glyph_mask_offsets_vector_begin_26: exact (26/26 bytes)
glyph_mask_offsets_vector_end_26: exact (26/26 bytes)
glyph_packed_color4444_ctor_22: exact (22/22 bytes)
Exact replay: 5/5 units, 1 cold objects
```

This adds **one new game-authored native exact head /22 distinct original
`.text` bytes**. The previously exact 24B packed-color constructor,
all four standard PMR-vector template methods and the still-nonexact
2,245B parent are **not** re-credited. No shared GDI view, resource
layout or canonical owner is changed; no full cold replay was run.

```sh
scripts/repo-python scripts/verify-glyph-packed-color4444-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphMaskComposite2245.cpp
```
