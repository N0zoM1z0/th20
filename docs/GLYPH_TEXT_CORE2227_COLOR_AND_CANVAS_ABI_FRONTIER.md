# Glyph Text 2,227B Boss: native GDI color roles and single-canvas lifetime

The pinned Japanese TH20 v1.00a Steamless glyph text core at `0x00415830`
has **2,227B/470 i386** of original executable code and a further
**1B NOP +22 direct font-switch pointers**, totaling **2,316B** in the
original PE. This update preserves the previously recovered 22-case
switch, all 17 pointer-alias groups, original allocator diagnostic path,
25 native E8 call roles and 43 in-body HIGHLOW roles. The original target
SHA-256 is `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

## New original-source and ABI corrections

The first previous full-extent candidate compiled from a separate `canvas`
owner and a `glyph` borrow alias. Original native code saves the allocator's
return in one pool-owned canvas pointer and passes that same value to the
real `ensure_format_4153d0`, HDC getter, 2,245B composite, and 542B Alpha
methods. The maintained source now uses **one real allocation result** and
borrows `NativeGlyphCanvasView` at the actual method calls. The old extra
alias generated unnecessary MSVC stack moves, not separate game storage.

The original GDI text color comes from **stack `[ebp+0x10]`**: original
`+0x392` loads that input, splits R/G/B into three byte locals (including
real `&0xff` masks) and assembles the `COLORREF`. The native two separate
composite calls instead pass **`[ebp+0x14]`** as the *outline color*,
at original `+0x492` and `+0x5CD`. The old source mislabeled these
words `layer` and `color` and used them in the wrong roles. The maintained
`native_text_core_415830` signature now calls them `text_color_word` and
`outline_color`, preserving their unchanged i386 types and argument positions.
`NativeGlyphTextCore.hpp` matches the new semantic names; its 294B submit
caller still compiles to the existing 292B **NONEXACT** frontier with all
real source call roles intact. The original nonspaced text branch also
advances the actual `horizontal_offset` input by two **once** before
both TextOut calls; the source preserves that input lifetime rather than
recalculating separate `+2` expressions. The GDI `SIZE` is filled by
`GetTextExtentPoint32W`; there is no original independent zero-initialization
of this output object.

## Whole original/native comparison and affected accepted consumers

Pinned MSVC 19.44 C++20 i386 (`/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`) produces the complete *current* candidate
**2,316B** contribution: **2,226B/469 i386 code** through `ret`, a
real 2B compiler NOP and all 22 native-role compiler-generated pointer
fields. The original is **2,227B/470 i386 code**, 1B original NOP and
22 pointer fields. Both tables start at the original `+0x8B4` address.
The candidate is **still NONEXACT**; equal contribution lengths,
call roles and table alias groups do not establish exact code.

In the zero-spacing draw path, the native code modifies its actual
`horizontal_offset` argument **once** (`+0x43A: mov/add/mov [ebp+0xC]`)
before the first GDI color update. The previous source recomputed `offset+2`
on each TextOut call, changing register lifetimes and branch instruction
positions. The corrected source now increments the live argument once and
reuses it, preserving both TextOut positions and their observable inputs.
The native two-wide-character temporary uses a single 32-bit zero store;
C++ value-initialization `wchar_t single_character[2]{}` reproduces that
natural aggregate initialization instead of the earlier separate
per-element initialization. These are real source semantics, not invented
compiler-shaping locals.

The corrected source and narrowed verification now establish:

| Whole-candidate metric | Previous switch checkpoint | Current source | Original |
| --- | ---: | ---: | ---: |
| Entire COFF/PE contribution | 2,316B | **2,316B** | 2,316B |
| Executable code through `ret` | 2,228B /472 instructions | **2,226B /469 instructions** | 2,227B /470 instructions |
| Original E8 physical sites | 4/25 | **15/25** | 25/25 |
| Original body HIGHLOW locations | 7/43 | **41/43** | 43/43 |
| In-code call/data role counts | 25/43 | **25/43** | 25/43 |
| Actual trailing switch table | 22, native aliases | **22, native aliases** | 22 |
| Equal ordinary positional bytes with candidate fields masked | 192 | **1,566** | 1,956 evaluated positions |

The final line is a bounded positional diagnostic, not strict credit:
real candidate relocations are masked and the code/RET and some instruction
bytes still differ despite the equal full contribution. **The first 15
E8 physical call sites align**, through original `+0x703` (second
lock acquisition), while the next native E8 is `+0x7BC` versus the
candidate `+0x7EC` in queued task construction. The two original in-body
HIGHLOW sites still misplaced are `+0x502` (candidate `+0x4F9`) and
`+0x820` (candidate `+0x813`). The full original code/table boundary and
all native relocation roles remain independently checked.

The original SHA, code/ret and 22 PE pointer boundaries, both independent
color argument offsets, all source relocation roles and the table alias
partition are checked in [`verify-glyph-text-core2227-native.py`](../scripts/verify-glyph-text-core2227-native.py).
The former switch-only 2,316B candidate is rejected by the new
physical-site and byte-equality verifier; matching only total length and
switch partition is insufficient. A cold build of **only** `src/GlyphTextCore2227.cpp` preserved
the original whole exact **132B glyph job constructor and 23B destructor
(2/2 units, one object)**. The sole header consumer
`src/AsciiTextSubmit294.cpp` was separately compiled and passed its own
native frontier checker with unchanged 292B/104 instructions and true
original call roles. The 56B queue bridge retains its independent strict
receipt. No broad cold replay was run.

Isolating the source changes separately shows that both the meaningful
in-place `horizontal_offset += 2` (as original `+0x43A`) and the natural
`wchar_t single_character[2]{}` initializer matter. Reverting only the
in-place adjustment returns a 2,312B/469-instruction candidate, while
reverting only the two-character initializer yields a 2,324B candidate.
Both preserve valid glyph behavior but misalign more original call sites.
The current combined source is the best, with all 15 native E8 positions
preserved before queue-task construction.

Next: reconcile the native queue-task `+0x7BC` invocation and the two
remaining in-body data-site shifts without sacrificing the recovered true
font switch, colors or in-place horizontal offset.
