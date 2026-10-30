# CORE/RECON-855 — whole original 1,980B Animation rectangle Boss strictly native exact

The immutable Japanese TH20 v1.00a Steamless original executable has
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
At original head **`0x00439A00`**, it contains an **entire game-owned
1,980B/486-x86 rectangle geometry renderer**, native frame `sub esp,0x68`,
original `ret 0x24` with nine stack parameters and an integer zero
return. The still-NONEXACT 5,993B Animation Draw dispatcher calls this
complete physical head at original E8 `0x00443E7E` and `0x00443FA6`.

One actual C++ method
[`src/AnimationShapeRect1980.cpp`](../src/AnimationShapeRect1980.cpp)
now compiles under the project pinned x86 MSVC 19.44.35211 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` into the
**whole exact original 1,980B**. This restores the complete native
codebody, **486/486 real x86 instructions**, the original `0x68` frame,
**12 exact E8 physical site/target roles**, and **16 exact PE HIGHLOW
physical site/target roles**. All **1,868/1,868 non-relocation bytes** are
identical before applying the 28 independently attested relocations; the
complete relocated canonical comparison is **1,980/1,980B zero differences**.

## Locked-PE source-independent proof

[`scripts/verify-animation-shape-rect1980-native.py`](../scripts/verify-animation-shape-rect1980-native.py)
independently disassembles the complete 1,980 original code bytes and
reads real PE `.reloc`. It attests all twelve original E8 offsets and
actual heads, all sixteen PE HIGHLOW offsets and actual absolute
reference values, 486 original complete i386 heads, true native
unsigned capacity `JB` and the original game Draw caller E8 sites.

The genuine E8 direct roles: one original `AnimationPoolOwner::flush_draws`
at `0x004455C0`, original scalar sine `0x00439820` and cosine
`0x004397C0`, **four calls to separately exact 78B authored XY transform
at `0x00445AD0`** (`+0x377/+0x3DE/+0x442/+0x4A9`), already exact
Graphics depth-disable `0x004DDF80`, color-mode selection
`0x00446690`, two real Graphics device getters at `0x00412730`,
and the compiler security cookie checker. The 78B callee already has
its [own strictly accepted source and physical credit](ANIMATION_SHAPE_XY78_STRICT_EXACT.md);
its bytes are **not** newly counted here.

The sixteen PE HIGHLOW physical data roles are:

| Original native physical owner | Genuine sites |
| --- | --- |
| Security cookie `0x005B25C0` | 1 |
| Four original 128-bit floating sign-XOR masks `0x0056D7D0` | 4 |
| Real half `0.5f` constant `0x0056E0EC` | 4 |
| Real one `1.0f` constant `0x0056C8CC` | 4 |
| Live `process_graphics` global `0x005C4D40` | 3 |

The original 128-bit mask is physically **four float sign bits**
`0x80000000` each, independently read as 16 immutable bytes from the
original executable. Under `/Od`, the ordinary source unary float
negation emits MSVC's natural COFF literal
`__xmm@80000000800000008000000080000000`, which the strict manifest
legitimately maps to this actual original PE constant owner. No
fabricated literal pool or guessed data address is used.

## Rejected original guesses and native source reconstruction

The first complete source candidate represented left/right/top/bottom
as four independent float locals, used a compact vertex-index loop and
cached extra pointers. It compiled to **1,207B/317 x86**, not the
1,980B/486 native parent, and lacked the original compiler security
cookie. Re-reading *original instruction operands* established the
actual typed semantic layout: two separate local arrays of four floats
`anchors_x[4]`, `anchors_y[4]`, at original frame locations
`[ebp−0x24..−0x18]` and `[ebp−0x14..−0x08]`. Their genuine initial zero
stores and three anchor cases per dimension are game-visible geometry
state, not compiler-padding locals. In original x86 `/Od`, indexing the
arrays intentionally emits native `MOV EAX,4;IMUL/SHL index`, including
the real local value comparisons and four independent XY calls.

The original anchor paths distinguish three horizontal and three
vertical interpretations: centered, from zero to width/height, and
negative width/height to zero. Six actually consumed float results
hold values reused across multiple coordinate stores: four meaningful
negative/scaled branch variants and two positive half-scale variants.
Writing those as genuine used scoped C++ temporaries restores the
original `0x68` stack and exact **four PE sign-mask fields**. Repeating
`-width*native_half` and `-height*native_half` directly in each
assignment would have emitted **eight** sign-mask data relocations,
not the genuine original four, and silently changed rounding/lifetime.

The original emits eight separate renderer XY translation updates on
its **four 20B SpriteColoredVertex objects**, and original reverse
Z=0/W=1 stores and two packed colors; a compact `for` loop was not
native-equivalent. The final typed C++ performs these real assignments
in their original order and then authentic D3D9 state/texture calls,
`SetFVF(0x44)` and `DrawPrimitiveUP(TRIANGLESTRIP,2,pointer,0x14)`.
It advances the true render-buffer cursor by four vertices and
increments the original renderer frame counter.

The original 4-vertex capacity check in particular performs
`MOV EAX,0x14; SHL EAX,2` to compute actual 4×20B occupied bytes and
`MOV EDX,0x14; SHL EDX,0x10` for the authentic **65,536×20B** pool end.
An innocuous `cursor+4` expression was compiled to `ADD reg,0x50` and
shifted all E8 fields by five bytes, despite equivalent arithmetic.
Using an actual **pointer into an indexed typed 65,536-element array**
for the cursor-end comparison regenerates the two original shift
instructions and restores **all E8 and data site positions**. This is
real code semantics and original array ownership, not an artificial
NOP or dummy local.

## Strict exact replay and bounded header-closure regression

The one actual original source `src/AnimationShapeRect1980.cpp` has
one pinned compiler object/receipt and one new canonical unit,
`animation_shape_rect_1980` in
[`config/match-units.toml`](../config/match-units.toml). Exactly
**12 authentic E8 REL32** and **16 authentic PE HIGHLOW/DIR32**
relocation records are specified with independently attested original
physical code/data destinations.

```text
animation_shape_rect_1980: exact (1980/1980 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The shared provisional method
`AnimationDrawDetailedOwner::draw_rect_439a00` signature was corrected
from `void` to its actual original integer-returning `ret 0x24` ABI.
This changed one shared renderer header, so **every affected previously
accepted provider** was cold-rebuilt and replayed individually:
mesh24/25, mode6, mode6 setup, mode7, mode7 setup, mode8, strip9,
strip11, projection math (two strict units) and the strict 1,468B
shape-ring Boss. All **11 previously accepted canonical units** stayed
zero-difference exact. The original 5,993B main Draw dispatcher was
also recompiled under its *focused noncanonical* original role verifier:
all its 123 real E8 target roles, 49+31 case pointers and genuine native
stack remained unchanged; **the 5,993B parent remains NONEXACT**.
No unrelated provider or unfiltered full-graph cold replay was run.

This credits one genuine game-authored physical 1,980B function only:

| Current game-native status | Before | After |
| --- | ---: | ---: |
| Exact authored physical original functions | 608 | **609** |
| Disjoint exact original game `.text` bytes | 213,139 | **215,119** |
| Source-present mapped functions | 1,254 | **1,255** |
| Strict canonical match units | 1,255 | **1,256** |
| Exact compiler source objects / receipts | 273 | **274** |

The related **2,169B triangle-fan** shape Boss at `0x0043B0E0`
and overall 5,993B Draw dispatcher remain nonexact separate functions,
regardless of this exact code and its exact 78B callee.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-shape-rect1980-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeRect1980.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
