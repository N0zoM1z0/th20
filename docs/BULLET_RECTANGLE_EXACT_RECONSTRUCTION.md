# CORE/EXACT-219 — complete original 176-byte Bullet field rectangle test

The immutable comparison target is Japanese TH20 Steamless v1.00a,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The real complete 176-byte function at `0x00485420` has 42 native
x86 instructions and original whole-body SHA-256
`e45982305e4b884c4a3f9e0568f71f3626fbf1b2e5e28ef4e8f57a6673296074`.
Original source spelling remains inferred. Maintained natural code is
`th20::bullet_outside_rectangle(const Vector3&,float,float,float,float)` in
`src/BulletRectangle.cpp`, with its small independent interface in
`src/BulletRectangle.hpp` (not an alteration of shared renderer/game headers).

Two independent original native calls at `0x00482AF6` and `0x00482B98`
connect this function to the original full **832-byte**
`0x00482A60` Bullet four-way bounce dispatcher. It returns integer one
when any of four rectangle-edge exclusion tests fires and zero otherwise.
The actual input point is the Bullet's live position at +0x64; the two
caller-supplied radius components are zero in this original caller, and
its width and height are selected from either real command index four or
current BulletController dimensions. The function retains its own general
radius parameters, rather than freezing those caller values.

The four ordered native SSE comparisons are:
`position.x + radius_x <= -width / 2`,
`position.x - radius_x >= width / 2`,
`position.y + radius_y <= 224 - height / 2`, and
`position.y - radius_y >= 224 + height / 2`.
The vertical frame center is the **original 224.0f** object at
`0x0056ED14`, with native 2.0f at `0x0056C8D0` and the x86 SSE sign-mask
at `0x0056D7D0`. The short-circuit order and original unordered/NaN
behavior are preserved exactly. Natural source spelling
`if (!(first || second || third || fourth)) outside=0; else outside=1;`
reproduces the native temporary integer and final direct branch. Superficially
equivalent `if (condition) return 1; return 0;` instead emitted 163 bytes;
the unsuccessful probes are retained privately, not treated as a prefix match.

The locked MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
compiler emitted **148/148** native non-relocation bytes and all seven
independently identified original data relocations. Fresh complete canonical
strict replay establishes **176/176 exact whole native bytes**. This new
source has no existing production include dependents: **one new exact unit,
one cold object**, no shared-header change and no unfiltered whole-graph
cold replay. Log: `.analysis/core219-bullet-rectangle-replay.log`,
original disassembly: `.analysis/core219-native-00485420.asm`.

The four complete native directional bounces are also exact, but this does
**not** make their enclosing 832-byte Bullet boundary dispatcher byte-exact.
Its private full-function trials compiled to 846, 848 and 865 bytes versus
the actual 832-byte native body. Neither that 832-byte caller, the 3,735-byte
single-shot Bullet emitter nor the 41,967-byte Enemy opcode dispatcher is
accepted as exact on the basis of this dependency closure.

## CORE/EXACT-220 follow-on: complete parent boss now exact

The source-correct entire **832-byte** native caller at `0x00482A60` has
since been independently reconstructed in `src/BulletBoundary.cpp`, with
the two calls now bound to the **real exact** `bullet_outside_rectangle`.
Its original 235 instructions and all 31 native relocation destinations
strictly match; the complete 832B/176B parent-and-callee replay and
45 previously exact include-dependent units all passed. The preceding
"nonexact caller" statement is historical to the original individual
rectangle admission, **not current status**. See
[complete boundary boss](BULLET_BOUNDARY_BOSS_EXACT_RECONSTRUCTION.md).
