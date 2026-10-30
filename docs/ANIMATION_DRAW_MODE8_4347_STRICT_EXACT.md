# CORE/RECON-850 — complete original 4,347B Animation Mode8 renderer, 4,372B whole strict native exact

The immutable Japanese TH20 v1.00a Steamless original executable is locked
by SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
At original physical address **`0x00441F00`** it contains a whole game-owned
**4,347B /1,063-x86** Animation Mode8 rendering Boss, with genuine
`sub esp,0x1BC`, original `ret 4`, and one Animation* input argument.
The original enclosing 5,993B Animation Draw dispatcher invokes this
physical head at original E8 addresses **`0x00443A8F` and `0x00443ACE`**.

One maintained, natural C++ method
[`src/AnimationDrawMode8.cpp`](../src/AnimationDrawMode8.cpp)
reproduces **every original 4,347B executable instruction byte** and its
**one genuine after-RET NOP plus six real 4-byte switch-pointer fields**.
The full physical original comparison extent is **4,372B**. The pinned
MSVC 19.44.35211 i386 C++20 compiler emits the entire native body,
original native stack/return contract and original after-body compiler
data **byte-for-byte after independent relocation replay**:

```text
animation_draw_mode8_boss_4347: exact (4347/4347 coverage bytes; 4372/4372 compared bytes)
Exact replay: 1/1 units, 1 cold objects
```

This is **whole-native strict exact** for one complete original Boss,
not a prefix, shape-only comparison, assembly alias, copied native bytes,
artificial NOP or hand-written jump table. The 5,993B main Draw
**enclosing** dispatcher is still separately **SOURCE-PRESENT/NONEXACT**
and receives no parent exact credit from this result.

## Immutable original PE census, independent of compiler output

The new
[`scripts/verify-animation-draw-mode8-native.py`](../scripts/verify-animation-draw-mode8-native.py)
reads the immutable original PE `.text` and actual relocation directory,
disassembles the complete 1,063 native instruction heads, and verifies:

| Independently attested native fact | Source/COFF strict result |
| --- | --- |
| Original 4,347B executable /1,063 actual i386 | **4,347/4,347B and 1,063/1,063 x86** |
| Original `0x1BC` frame and one-stack-argument `ret 4` | **Both identical** |
| 101 genuine original E8 call sites with actual destination heads | **101/101 physically identical site/target pairs** |
| 39 original in-body HIGHLOW data fields | **39/39 physically identical site/target pairs** |
| One compiler-generated after-RET `NOP` | **One actual byte `0x90` at the same offset** |
| Six original physically relocated 32-bit code pointers | **Six genuine compiler-generated COFF pointer relocations at exactly the native physical offsets** |
| All original relocations over code and table | **101 E8/REL32 +45 HIGHLOW/DIR32 =146 complete roles** |
| Whole body+NOP+native six-pointer mode table | **4,372/4,372 relocated original bytes, zero differences** |

The 101 original direct E8 roles include **41** calls to a *single*
physical 14B native folded matrix constructor/address getter at
`0x0040BDA0` (three genuine 64B local matrix constructions and 38 real
matrix-address member calls), **18** D3DXMatrixMultiply imported thunks,
**six each** of D3DXMatrixRotationX/Y/Z imported thunks, **seven** genuine
`Graphics::get_device` calls, **four** game-owned
`multiply_color_128_saturating` channel calls, **three** original pool
flush calls, original Animation draw-enabled/recursive rotation/position
transform/sprite lookup, original depth-write enable and disable, texture
binding/lookup and color-state selection, and the compiler cookie check.
All target heads are independently established original PE locations;
none is promoted to another duplicate source-owned function by a
provisional class spelling.

The **39 physical in-body** original PE HIGHLOW target roles are:
**18** actual native 64-bit zero (`0x0056CD50`) used for the 18 real
float-to-double X/Y/Z nonzero angle comparisons; **nine** live Graphics
pointer values (`0x005C4D40`); **four** real WindowState scale reads
(`0x005B8818`, actual global WindowState+`0x20C0`); **two** native half
constants (`0x0056E0EC`); **two** native zero float constants
(`0x0056E0E8`); **two** native one float constants (`0x0056C8CC`);
one true compiler security cookie (`0x005B25C0`) and the one main
case-table base reference (`0x00442FFC`, in-body field `+0x35D`).
The source's 45 actual COFF DIR32 fields include these 39 plus six
independent original after-RET jump-table pointers.

### Original physical six-case table and actual compiler labels

Original table base **`0x00442FFC`** is at method offset `+0x10FC`,
after the 4,347B body (`+0x10FB`) and one real compiler `NOP`.
It contains exactly six PE-relocated native code pointers in this
original source-mode order:

| Native mode | True original case instruction head | Source compiler local label |
| --- | --- | --- |
| 0 | `0x00442261` | `$LN16` (`+0x361`) |
| 1 | `0x0044239B` | `$LN20` (`+0x49B`) |
| 2 | `0x004424D5` | `$LN24` (`+0x5D5`) |
| 3 | `0x0044260F` | `$LN28` (`+0x70F`) |
| 4 | `0x00442749` | `$LN32` (`+0x849`) |
| 5 | `0x00442883` | `$LN36` (`+0x983`) |

The genuine compiler-generated main table base label `$LN50` has value
`+0x10FC`, with actual source `jmp [ecx*4 + table]` original body field
`+0x35D`. All seven source-object local label values/sections were
read **from its actual COFF symbol table**, independently corroborated
with original native instruction-head and original PE table addresses
**before** accepting the full relocated byte equality. There is no
handcrafted switch array or guessed after-RET length.

## Source-level semantics recovered by real original experiments

The original Code8 renderer checks the genuine Animation draw flag and
alpha byte `Animation+0x493`, flushes pending renderer draws, applies the
true Animation depth-write bit4 branch, and when necessary constructs
its 64B local matrix values and updates the Animation matrix. It uses
real WindowState scaled coordinates, original integer Animation flag
bits and six distinct X/Y/Z rotation **orders** under native
`Animation+0x4A2` bitfield values 0..5:

| Mode | Original rotation order |
| --- | --- |
| 0 | X → Y → Z |
| 1 | X → Z → Y |
| 2 | Y → X → Z |
| 3 | Y → Z → X |
| 4 | Z → X → Y |
| 5 | Z → Y → X |

Each of 18 conditional axis rotations performs the original double-zero
comparison with native `UCOMISD/LAHF`, actual D3DXMatrixRotation import,
**two** real original 14B matrix-view getter E8 calls, and actual
D3DXMatrixMultiply import. All branches and native float operands are
source-owned; the first-class 8-bit rotation mode C++ bitfield produces
the original `mov dl;shr dl,2;and dl,7;movzx eax,dl` protocol and
all six independent case heads rather than an incorrect sign-extending
32-bit shift.

After rotation, the method publishes the genuine world transform and
synchronizes true live Animation/renderer texture state, color tint,
original packed B/G/R/A multiplication, sprite cache and 64B texture
matrix update, D3D vertex stream/FVF/texture-state, then invokes the
actual DrawPrimitive index and primitive count. Source-level corrections
needed to recover the original x86, beyond merely matching behavior:

1. The original alpha guard is one direct byte read at `Animation+0x493`,
   not an indexed byte read from `color_490` that caused modern `/Od`
   to insert a 3×byte index multiplication and shift all subsequent E8.
2. The original 8-bit rotation-mode bitfield handles a three-bit index
   at bits2..4. A 32-bit shift expression emitted `SAR/MOVZX` with
   different opcode sizes. The natural byte bitfield restored all
   original six-case dispatch code and the genuine branch/JNE behavior.
3. The original `Animation::transform_position` writes the already
   constructed 64B world matrix's translation **row**. The natural
   typed `Vector3*` alias of `world.elements[3]` emits the native
   receiver/return-value pointer sequence; taking the address of the
   first scalar cell `&world.elements[3][0]` led to three redundant
   instructions and a nine-byte shift, despite equivalent address bits.
4. The renderer color choice is the genuine C++ natural ternary
   `color_mode != 0 ? color494 : color490`, and the live color/tint
   source is read at real renderer offsets. Changing it to two full
   statement branches shortened and retargeted later machine code.
5. The direct renderer texture/sprite/FVF cache lvalues retain the real
   source receiver field access at `+0x6000E04/E08/E18/E0E`; keeping
   extra reference aliases prolongs compiler stack lifetimes and shifts
   later original E8 roles. These are actual game-owned mutable fields,
   not fake compiler padding.
6. The real screen-primitive corner index is computed **before** the
   final Graphics device retrieval, then multiplied by four when
   passed as the DrawPrimitive argument. The original places actual
   IMUL/ADD, value storage, `get_device` and `SHL` instructions in this
   order; the direct large argument expression moved computation too
   late. A used named source-local `corner_index` restores the actual
   late E8 positions and all remaining original byte equality.

These changes were checked over the **entire** 4,347B original native
function, not a prefix or candidate-size coincidence. There are no
artificial no-op locals, C++ version feature flags, manual assembly,
compiler-patched bytes or fabricated ABI branches.

## Strict canonical replay, source ownership and present status

The one canonical `animation_draw_mode8_boss_4347` unit in
[`config/match-units.toml`](../config/match-units.toml) uses the standard
pinned x86 MSVC profile
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`,
original `size=4347`, required `compare_size=4372`, and exactly **146**
independently specified real source COFF relocation roles (101 E8,
39 body HIGHLOW and six table HIGHLOW). Its one pinned source provider
is `build/core850-canonical/AnimationDrawMode8.obj` with a fresh
compiler receipt.

Only one **new** source and canonical unit is cold compiled and replayed.
No other previously exact source/header/profile/match provider is changed;
**affected old canonical unit replay scope=0**. No unfiltered full-graph
cold replay is run. Original 4,347B is credited as **one distinct
whole-native game-authored function**; the one-byte NOP, 24B table,
existing exact D3DX/Graphics/Animation callees, compiler cookie and
folded 14B getters do not earn duplicate game-code credit.

| Verified live metric | Before | After | Delta |
| --- | ---: | ---: | ---: |
| Whole original game-authored strict exact functions | 603 | **604** | +1 |
| Original game exact `.text` bytes | 206,100 | **210,447** | **+4,347** |
| Source-present original mappings | 1,249 | **1,250** | +1 |
| Canonical strict match units | 1,250 | **1,251** | +1 |
| Pinned exact source object/receipt providers | 268 | **269** | +1 |

The *enclosing* original 5,993B Animation Draw dispatcher is still
**SOURCE-PRESENT, NONEXACT**. The reconstructed game as a whole is not
linked or playable from its maintained source yet.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-draw-mode8-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawMode8.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/progress.py --check
```
