# CORE/RECON-1099 — entire original 562B D3D9 texture-from-memory game Boss WHOLE strict exact

Immutable Japanese TH20 Steamless v1.00a executable SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original game-owned Renderer `0x0044E8F0` is a complete
**562B/177-i386** native texture-record file-image upload method, original
full SHA-256 `1b0d6d08d535765761f1cfaf5f9140a7e0963f0b04b00daae23cac98cb182a19`.
It has genuine C++20 source in
[`src/AnimationFileTextureLoad562.cpp`](../src/AnimationFileTextureLoad562.cpp)
which now emits the **whole exact native 562/562**, including **486/486
nonrelocated bytes** and all **six physical original E8 /13 PE HIGHLOW**
fields. Original return ABI is `ret 0x24`: the full nine-stack-word
argument contract is preserved, including one original input at stack
`+0x10` not read by this complete native body. Its game-specific role
is not invented by the reconstruction.

## True D3D9 texture creation, clipping and surface copy

The original takes a `TextureRecord*` pointing at the genuine native
24B owner. It updates original `TextureRecord::flags.bits` at offset
`+0x14` by clearing low two bits and selects its texture pixel format
via the separately accepted **77B** native `select_texture_format`
`0x0044CFB0` (native E8 `+0x17`). It computes clipped region
width/height as `min(region,requested)` and sets a source Win32 `RECT`
from the input source x/y and clipped dimensions. Its native texture
header pointer is at record `+0x10`; the actual one-byte flag at
header `+0x22` controls whether a scaled bitmap should be created.

The original compares the graphics scaling float at global
`0x005B8818` against the reference float at `0x0056C8D0`. When
scaling is enabled and below reference, the source uses genuine
SSE float `cvtsi2ss`, multiplication by the live scale and source
constant `0x0056E0EC`, and native signed truncation back to the
width/height arguments. The D3D destination `RECT` is zero-origin
and uses the resulting output dimensions. Original D3D9 format
values are read from `texture_api_formats[9]` at `0x0056E208`; the
actual Graphics instance `0x005C4D40` supplies its device through
the original folded 17B getter `0x00412730`.

The method then uses native D3DX9 **`D3DXCreateTexture`** (not a
synthetic direct `Device::CreateTexture`) with one mip level, managed
pool, chosen native D3DFORMAT, and the actual `record->texture`
pointer. It acquires a level-zero `IDirect3DSurface9*` through the
real texture vtable and calls
**`D3DXLoadSurfaceFromFileInMemory`** with the DIB bytes at
`record+0x04/+0x08` and source/destination RECTs. A nonzero HRESULT
releases the acquired surface and returns original `-1`; success
releases the surface, invokes a **separate original 2,745B**
texture finalize method `0x00451910`, stores the actual original
byte-per-pixel table `0x0056E22C` at `record+0x0C`, and returns the
original signed `width * height * byte_size`.

## Why the natural compiler now matches exactly

Several plausible C++ spellings yielded 567–572B compiler bodies,
with exactly the correct physical E8/data roles but wrong local
stack and branch lowering. Rechecking the entire original proved:

- The native format selection updates the actual original stack
  parameter, rather than an invented separate local format variable.
- The source/destination clip selection uses the original signed
  order `requested > region ? region : requested`, preserving the
  original `jle` compare operation.
- The scaled-output condition compares the native original reference
  float *against* the live graphics scale, preserving original
  `comiss` and `jbe` semantics.
- The original D3DX filter constant **`1` is
  `D3DX_FILTER_NONE`**, not `D3DX_FILTER_POINT` (whose SDK value is
  `2`). Its alternative scaled filter is exactly `0x30004`.
- A real, **explicit `if/else`** assigning the filter to a live DWORD
  produces the original evaluation and argument-push order. A
  seemingly equivalent `const DWORD filtering = condition ? ...`
  generated extra stack moves and missed the native body. This is a
  genuine change in D3D filter semantics and scope, not padding.
- The failure path evaluates the real D3DX HRESULT and releases the
  surface before returning `-1`; the successful finalizer and
  byte-count computation are independent of that failure return.

With pinned MSVC19.44 x86 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`, these
actual semantic expressions emit the whole **562B/177 instructions**
including the genuine post-COM compiler NOP. No handwritten assembly,
synthetic dead locals, `nop` source patch, fake native DLL shim or
shortened target extent was used.

## Original physical PE and strict-unit verification

Read-only
[`verify-animation-texture-upload562-native.py`](../scripts/verify-animation-texture-upload562-native.py)
independently SHA-attests the entire original 562B, checks complete
native x86 instruction boundaries and the actual `ret 0x24`, and
verifies all six original physical E8 destinations:

| Native E8 offset | Immutable original target |
| --- | --- |
| `+0x17` | game 77B texture-format selector `0x0044CFB0` |
| `+0x10A` | folded Graphics device getter `0x00412730` |
| `+0x12C` | D3DX9 `D3DXCreateTexture` `0x005406A2` |
| `+0x1AE` | D3DX9 `D3DXLoadSurfaceFromFileInMemory` `0x00540696` |
| `+0x1FB` | separate original 2,745B texture finalizer `0x00451910` |
| `+0x227` | native security cookie check `0x005429EE` |

The thirteen physical original PE HIGHLOW fields include true
security cookie, live scaling reference variables, 9-entry texture
format and byte-count tables, and the original process Graphics
device owner. The verifier checks each actual HIGHLOW site/target
and then compares all nineteen generated COFF field roles to the
physical PE evidence, **not merely the number of references**.

```text
animation_texture_upload_from_memory_562: exact (562/562 bytes)
Original complete game method: 562B /177 i386
Nonrelocated original bytes: 486/486
Original relocations: 6 E8 REL32 /13 PE HIGHLOW
Exact replay: 1/1 unit, ONE affected cold object
```

This adds **one distinct game-authored original function /562 native
`.text` bytes**. The earlier 77B format selector, folded Graphics
accessor, D3DX system libraries, and original **2,745B** texture
finalizer are separately owned and are **not** credited again.
The game still does not build/link/run as a whole, and **no
project-wide cold replay** was executed.

```sh
scripts/repo-python scripts/verify-animation-texture-upload562-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationFileTextureLoad562.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
