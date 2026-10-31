# CORE/RECON-1103 — original entire 2,745B D3D9 Renderer alpha-fringe texture Boss WHOLE STRICT EXACT

Locked original: Japanese TH20 Steamless v1.00a, executable SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The game-owned original Renderer texture-alpha finalizer `0x00451910`
is **2,745B/759 x86 instructions**, complete original function SHA-256
`1b4a86d1336a36cd506b27e58c8e750b26874ec42a1a8da94e8e96fadfa58924`.
It is now **WHOLE STRICT EXACT** from ordinary C++20 in
[`src/AnimationTextureFinalize2745.cpp`](../src/AnimationTextureFinalize2745.cpp),
with independent full original PE and canonical whole native evidence.
This supersedes [CORE/RECON-1101's historical source-present/NONEXACT
frontier](ANIMATION_TEXTURE_FINALIZER2745_NATIVE_FRONTIER.md). The original
562B texture-from-memory upload Boss is a separately exact caller and
is not recredited by the finalizer.

## Original complete four-format D3D9 alpha-fringe protocol

The original accepts the real borrowed `IDirect3DTexture9*`, obtains a
level-0 `IDirect3DSurface9*` through the native COM vtable and, when
present, calls true surface `GetDesc`, `LockRect`, and ultimately
`UnlockRect`/`Release`. Its four separate format branches scan
locked pixels by actual signed row `Pitch` and native dimensions.
When a pixel's alpha is zero it accumulates the red, green and blue
components of *opaque* left, right, top and bottom neighbors. Each
neighbor has its own original conditional boundary and original
function call. For counts greater than one it divides the accumulated
RGB values by the count, writes the resulting component bits back to
the transparent pixel, and leaves its alpha channel unchanged.

| Original native format branch | Pixel layout and native four-neighbor helper | Original direct E8 offsets in 2,745B |
| --- | --- | --- |
| `D3DFMT_UNKNOWN` (0) and `D3DFMT_A8R8G8B8` (0x15) | Four-byte BGRA, whole exact game `accumulate_texel8888` **139B** at `0x00451880` | `+0x18C/+0x1B6/+0x1E4/+0x215` |
| `D3DFMT_A1R5G5B5` (0x19) | Two-byte 5:5:5 packed, whole exact game `accumulate_texel1555` **183B** at `0x00451640` | `+0x3C3/+0x3ED/+0x417/+0x444` |
| `D3DFMT_A4R4G4B4` (0x1A) | Two-byte 4:4:4 packed, whole exact game `accumulate_texel4444` **183B** at `0x00451700` | `+0x652/+0x67C/+0x6A6/+0x6D3` |
| `D3DFMT_A8R3G3B2` (0x1D) | Two-byte 3:3:2 packed, whole exact game `accumulate_texel8332` **187B** at `0x004517C0` | `+0x8E5/+0x90F/+0x939/+0x966` |

The native original has **17 E8**: those 16 genuine game calls and
one compiler cookie check `+0xAAE -> 0x005429EE`. The four existing
format-specialized helpers were already exact under REF-042 and are
[separately credited as game-owned original code](ANIMATION_TEXEL_FOUR_GAME_ORIGIN_692_STRICT_EXACT.md).
No 139B/183B/183B/187B helper code is counted inside this 2,745B
new code head. The original 562B uploader at `0x0044E8F0` has its
own true E8 `+0x1FB -> 0x00451910` into this now complete Boss.

## Source-derived resolution of 2,745B compiler code layout

The first natural C++20 attempt expressed all four formats correctly
but generated a **2,794B COFF contribution with a shorter function
body** from redundant independent RGB scalars and a copied RGB array.
Using a single `std::uint32_t rgb[3]` per original format restored
one real contiguous three-channel accumulator, reducing the source
contribution to 2,558B (although it still lacked original code).
Several source-only compiler probes were then checked against the
original *full* 759-instruction x86 body and its 17 original E8.

The final naturally exact code faithfully expresses five original
semantic/evaluation details, not inert compiler-shaping operations:

1. The D3D9 surface has a real early return if `GetSurfaceLevel`
   produces no surface. The borrowed surface and locked storage have
   their own proper lifetime and original COM release ordering.
2. A pixel is read and updated as **element zero of an actual
   format-specific texel array**, `pixel[0].alpha/red/green/blue`.
   The original compiler emits genuine indexed-address arithmetic,
   not the shorter pointer-field access that previous source used.
3. Each format's RGB state is one aggregate initialized with
   `std::uint32_t rgb[3]{}`. On transparent pixels the original
   evaluation order is the meaningful chained assignment
   `rgb[0] = rgb[1] = rgb[2] = 0`; unlike three independent ordered
   resets, this generates the native original RGB zero/store order.
4. The left and right actual neighbor pointers use array indexing,
   `&pixel[-1]` and `&pixel[1]`, while the signed top offset
   explicitly computes `pixel + (-locked.Pitch)/bytes_per_texel`.
   This reproduces original signed negative-pitch division semantics
   and the real native scaled pointer arithmetic, not arbitrary
   padding.
5. The true unsigned boundary comparisons use `x > 0` and `y > 0`,
   producing native **`jbe`** rather than the `je` emitted for
   `x != 0` and `y != 0`. The three packed 16-bit texel formats
   **truncate RGB to `std::uint8_t` before bitfield assignment**,
   matching original byte-extraction instructions (`movzx`, one
   extra byte per channel) rather than passing 16-bit RGB.

After these meaningful changes the compiler emits the **entire
2,745B/759-instruction original function exactly**, including the
original 17 E8 at all 17 original offsets, all native loop controls,
RGB averaging and real D3D9 COM vtable calls. Neither assembly, a
synthetic unused local, inserted NOP nor an altered executable was
needed.

## Exact complete 2,798B object contribution: code AND real native tables

The original game function ends at physical `0x004523C9`, exactly
2,745 bytes from `0x00451910`, with native `ret 4`. It is followed
by **53B of actual separately owned original PE data**:

- **3B** authentic alignment `0F 1F 00`.
- **20B** relocated five-case branch target table at physical
  `0x004523CC`: original destinations `0x004519C2`, `0x00451BEF`,
  `0x00451E7E`, `0x0045210D`, `0x0045239B`.
- **30B** original physical format selector table beginning at
  `0x004523E0` (actual original 28B format indices plus two
  trailing selector/data bytes). Neither table is part of the
  function's 2,745B game-code coverage.

Pinned MSVC i386 naturally puts these appended tables into the same
**2,798B complete COFF contribution** as the 2,745B function. The
existing strict comparison engine *already supports* two deliberately
separate lengths, so no tool workaround was needed:

```toml
size = 2745             # exactly all genuine original game code
compare_size = 2798     # genuine original code PLUS all real PE tables
```

The strict comparison replays and verifies **all 25 independently
original relocations across the complete 2,798B**:
**17 native E8 REL32**, **3 PE HIGHLOW inside original game code**
(cookie + two switch-table references), and **5 PE HIGHLOW fields
in the actual appended jump-target table**. The native 30B
selector-map bytes are also compared rather than ignored. After
normalizing just these 25 genuine physical relocation fields,
**all 2,698/2,698 remaining bytes are identical**. Replaying the
original exact relocated destinations yields **2,798/2,798 total
byte-for-byte equality**, not a structurally similar diagnostic
prefix. The 53B data contributes **zero** to game-function code
credit; no original function was truncated to hide differences.

[`scripts/verify-animation-texture-finalizer2745-native.py`](../scripts/verify-animation-texture-finalizer2745-native.py)
independently SHA-attests original entire 2,745B and the adjacent
53B region, all 759 native instructions/17 direct E8, all eight
physical HIGHLOW data sites including five *outside* the code,
and the original four 139B/183B/183B/187B child boundaries. It
also verifies the original 562B uploader's E8 into this Boss,
then the complete pinned compiler contribution and strict unit.

```text
animation_texture_finalize_alpha_2745: exact
2745/2745 original game code bytes
2798/2798 compared original code plus post-return data bytes
2698/2698 original nonrelocated code/data bytes
17 E8 REL32 + 8 real PE HIGHLOW relocation fields
759 original decoded native instructions
Exact replay: 1/1 unit, 1 affected cold object
```

This newly closes **one distinct game-authored original 2,745B
function head**, increasing genuine game code coverage by 2,745
bytes, with no additional credit for its attached 53B native data
or already accepted texel accumulators/562B caller. The whole game
still does not yet build/link/play. No unfiltered cold replay was
run.

```sh
scripts/repo-python scripts/verify-animation-texture-finalizer2745-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationTextureFinalize2745.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
