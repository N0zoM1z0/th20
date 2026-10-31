**CORE/RECON-1103 CURRENT CORRECTION:** The complete original 2,745B/759 i386 Renderer texture-alpha finalizer is now [WHOLE STRICT EXACT](ANIMATION_TEXTURE_FINALIZER2745_STRICT_EXACT.md). Real C++ `pixel[0]` texel access, signed `(-Pitch)/texel_width`, `std::uint32_t rgb[3]{}` with chained three-channel reset, unsigned x/y `>0`, and byte truncation into packed 16-bit color fields restore full original code. The strict comparison covers **ALL 2,798 original bytes including 53B of genuine post-ret tables**, all 17 E8 and eight true original PE HIGHLOW roles; only 2,745 real code bytes are credited. All older 2,558B/NONEXACT observations below are historical compiler probes, not current project status.

# CORE/RECON-1101 — original 2,745B Renderer texture alpha-fringe Boss: full source, nonexact native frontier

Immutable Japanese TH20 Steamless v1.00a original SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The real game-owned `0x00451910` texture finalizer is a **complete
2,745B/759-instruction i386** Renderer Boss, original whole SHA-256
`1b4a86d1336a36cd506b27e58c8e750b26874ec42a1a8da94e8e96fadfa58924`.
Its original parent is the separately [WHOLE STRICT EXACT 562B
D3D9 file-memory texture uploader](ANIMATION_TEXTURE_UPLOAD562_STRICT_EXACT.md),
which invokes this finalizer at genuine E8 `0x0044E8F0+0x1FB` after a
successful D3DX surface upload. The 2,745B finalizer had **no
maintained game source** before this checkpoint. It is now
`SOURCE-PRESENT, NONEXACT` with real C++20 in
[`src/AnimationTextureFinalize2745.cpp`](../src/AnimationTextureFinalize2745.cpp).
No original code bytes are credited for the still nonexact parent.

## The whole native four-format surface and alpha-fringe behavior

The original receives an existing `IDirect3DTexture9*` argument, calls
its true D3D9 `GetSurfaceLevel(0)` virtual method, and if a surface is
returned, obtains a genuine `D3DSURFACE_DESC` and
`D3DLOCKED_RECT` via surface `GetDesc`/`LockRect`. It switches on the
original format enum, preserving four independent pixel scan bodies:

| Original format | Pixel format and transparent-test semantics | Genuine four neighbor E8 |
| --- | --- | --- |
| `0` / `0x15` | `D3DFMT_UNKNOWN` / `D3DFMT_A8R8G8B8`, four-byte BGRA, alpha byte zero | `0x00451880` **139B**, original `+0x18C/+0x1B6/+0x1E4/+0x215` |
| `0x19` | `D3DFMT_A1R5G5B5`, two-byte unsigned texel, top alpha bit zero | `0x00451640` **183B**, original `+0x3C3/+0x3ED/+0x417/+0x444` |
| `0x1A` | `D3DFMT_A4R4G4B4`, two-byte texel, top alpha nibble zero | `0x00451700` **183B**, original `+0x652/+0x67C/+0x6A6/+0x6D3` |
| `0x1D` | `D3DFMT_A8R3G3B2`, two-byte texel, top alpha byte zero | `0x004517C0` **187B**, original `+0x8E5/+0x90F/+0x939/+0x966` |

Each real scan iterates native `D3DSURFACE_DESC::Height` rows and
`Width` pixels using the actual signed surface pitch. Transparent
texels accumulate RGB components from the **left, right, top and
bottom** neighbor *only when each neighbor exists and has nonzero
alpha*, via the corresponding original format-specific helper.
There is a real per-texel count; only counts greater than one cause
unsigned RGB division by count, as observed in all four original
format branches. The result is stored into the native packed
RGB fields **without inventing alpha changes**. After the format
switch the original calls real surface `UnlockRect` and `Release`,
without adding an unobserved mipmap, D3DX scaling or extra COM owner.

The C++ source reuses the existing packed pixel structures and
functions in [`TextureTexels.hpp`](../src/TextureTexels.hpp) /
[`TextureTexels.cpp`](../src/TextureTexels.cpp):
`accumulate_texel8888`, `accumulate_texel1555`,
`accumulate_texel4444`, and `accumulate_texel8332`.
These original **139B/183B/183B/187B** physical heads have separate
natural source and were already **WHOLE STRICT EXACT** under historical
REF-042 (4/4 native units), not NONEXACT as incorrectly asserted
in the original CORE/RECON-1101 frontier. CORE/RECON-1102 now
[independently re-attests their complete original code and corrects
custom game-origin classification](ANIMATION_TEXEL_FOUR_GAME_ORIGIN_692_STRICT_EXACT.md).
They remain separate original function heads and their prior exact
bytes are never added again by transitive reachability from this
still-NONEXACT 2,745B parent. The finalizer
shares the sole non-allocating Renderer method declaration
[`NativeRendererTextureMemoryView.hpp`](../src/NativeRendererTextureMemoryView.hpp)
with the already exact 562B uploader, not two conflicting definitions
of its class. Rebuilding only the affected 562B source after the new
shared header still passes **562/562 whole strict exact**.

## Original switch tables are physically outside the 2,745B code

The original in-function **17 E8** comprise exactly the 16 listed
four-neighbor calls plus one native compiler-cookie check
`+0xAAE -> 0x005429EE`. Its three physically original PE HIGHLOW
**within the 2,745B method** are the security-cookie field
`+0x0A -> 0x005B25C0` and two real switch-table pointers
`+0xA7 -> 0x004523E0`, `+0xAE -> 0x004523CC`.

The native method ends exactly at **`0x004523C9`** with genuine
`ret 4`. After three alignment bytes, the original has a physically
**distinct 20B/5-entry relocated jump-target table at
`0x004523CC`**, entries:

```text
0x004519C2
0x00451BEF
0x00451E7E
0x0045210D
0x0045239B
```

The second actual **28B mapping table at `0x004523E0`** uses the
original format indices to select that five-target table and has no
PE HIGHLOW of its own. Neither table is part of the 2,745B native
function body. Counting their bytes as game instructions or simply
cutting off generated compiler data to force an exact size would be
false evidence.

## Natural C++20 result and unresolved compiler frontier

The initial ordinary C++20 source expressed the four full scan
branches and correctly emitted all **17 original call roles**, but
used redundant temporary RGB copies (three separate color scalars
and an additional array), producing a **2,794B/750-decoded-instruction**
COFF contribution. This was semantically unnecessary and did not
faithfully model the original three contiguous 32-bit accumulator
values. Replacing it with one natural
`std::uint32_t rgb[3]` per format and resetting those three values
on transparent texels keeps the original neighbor/averaging behavior
and emits **2,558B** of current compiler function contribution.
The complete contribution includes genuine generated jump-table data
at its end and decodes to **718 instructions including data**.

The emitted COFF contains **17 REL32 and eight DIR32**: security
cookie, two switch-table addresses, and five distinct jump-target
table entries at its after-`ret` offsets `+0x9CC/+0x9D0/+0x9D4/
+0x9D8/+0x9DC`. Its actual last generated `ret 4` ends at
`+0x9C9`, rather than the original `+0xAB9`. This is a significant
**240-byte code-region gap** with different local RGB/loop lowering,
not a harmless padding byte or a candidate for a prefix-only exact
claim. The source is therefore **SOURCE-PRESENT, NONEXACT** and has
**zero credited game-authored bytes**.

Read-only independent
[`verify-animation-texture-finalizer2745-native.py`](../scripts/verify-animation-texture-finalizer2745-native.py)
SHA-pins the entire original 2,745B, all 759 instructions, each
physical native E8/HIGHLOW, the complete four distinct original
helper extents, both independent jump tables *outside* the function,
and the natural modern C++20 2,558B/17-E8/8-DIR32 compiler
contribution. It also requires the separate exact 562B original
parent's fresh strict receipt. No global cold replay, target patch,
truncated native function, handwritten assembly or synthetic NOP
was used.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/AnimationTextureFinalize2745.cpp build/core1101-probes/AnimationTextureFinalize2745.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-animation-texture-finalizer2745-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationFileTextureLoad562.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
