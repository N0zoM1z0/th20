# CORE/RECON-1100 — original 562B D3D9 Renderer texture-file-memory upload Boss, whole strict exact

Immutable Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original game-owned `0x0044E8F0` is a complete **562B/177-i386**
Renderer texture file-memory upload method, original whole SHA-256
`1b0d6d08d535765761f1cfaf5f9140a7e0963f0b04b00daae23cac98cb182a19`.
Its authentic source is now
[`src/AnimationFileTextureLoad562.cpp`](../src/AnimationFileTextureLoad562.cpp),
which pinned MSVC19.44 C++20 x86 emits as **562/562 whole strict
exact**, with **486/486 nonrelocated native bytes, 6 E8 and 13 genuine
PE HIGHLOW fields** at every original physical location.

## Real original Renderer and D3D9 resource semantics

The native method is a game Renderer `__thiscall` with one borrowed
`TextureRecord*` argument and eight additional native 32-bit stack
arguments (final `ret 0x24`). One original stack input at `+0x10`
is intentionally named `original_parameter_10` because the whole
original does not read it; no speculative purpose is assigned.
The original clears `TextureRecord::flags` bits 0/1, maps the
incoming texture format using the separately exact original **77B**
`select_texture_format` at `0x0044CFB0`, and **updates the incoming
by-value native format parameter itself**. It computes a source
`RECT` using original source left/top plus
`min(original_width, clipped_width)` and equivalent height; an
independent destination `RECT` starts at `(0,0)` and spans the
potentially resized output width/height.

The original ANM group header pointer lives at `TextureRecord+0x10`.
It reads a native **single byte at group-header `+0x22`**, a distinct
observed texture flag from the previously verified `+0x20` flag.
When this byte is nonzero and process-global graphics scale
`0x005B8818` is strictly below original `0x0056C8D0`
(**2.0f**), the destination dimensions are converted to float,
multiplied by the live graphics scale and original constant
`0x0056E0EC` (**0.5f**), then truncated to signed 32-bit integers.
The source retains exact SSE2 `cvtsi2ss/mulss/cvttss2si` lowering,
not an invented floating-point approximation.

The original reads real D3D9 texture format table `0x0056E208`,
obtains the actual device from `Graphics` at global `0x005C4D40`
via previously whole exact `Graphics::get_device`, and calls
`D3DXCreateTexture` (actual IAT `0x005406A2`) with one mipmap
level, usage zero, selected format, `D3DPOOL_MANAGED`, and
`&TextureRecord::texture`. It then uses genuine texture COM
`GetSurfaceLevel(0)` with a temporary `IDirect3DSurface9*`,
including the native real compiler NOP after the COM virtual call.
It calls the real D3DX9 `D3DXLoadSurfaceFromFileInMemory`
`0x00540696` with original `external_bytes` at `TextureRecord+0x04`,
`external_size` at `+0x08`, and both actual source/destination RECTs.
The native filter is specifically **`D3DX_FILTER_NONE` = 1** without
scaling, or **`0x30004`** under the ANM flag/graphics-scale test;
using the superficially similar `D3DX_FILTER_POINT` = 2 would be
native incorrect. The surface is released through real COM
`Release()` in both failure and success paths, with correct clearing
of the temporary pointer. On D3DX failure the game returns `-1`.
On success it invokes the **independent original 2,745B** texture
finalization method at `0x00451910`, stores bytes-per-pixel from the
true original table `0x0056E22C` to `TextureRecord+0x0C`, and
returns original `width*height*bytes_per_pixel`.

## What changed to obtain true whole-native exact code

The first meaningful C++20 source was **569B/180 i386**, already
with all six native E8 and 13 data relocation types, but used a
separate `mapped_format` local, the wrong `D3DX_FILTER_POINT`
constant, reversed short-circuit/comparison evaluation, and an
extra staged `filtering` local before the D3DX call. These were
real native stack and filter-protocol differences, not alignment.
Controlled source probes first corrected the original source-vs-clip
comparison, the **`nominal_scale > current_scale`** float predicate,
and the early failure/COM release ordering. The generated body
narrowed to **567B/178** after removing the stale header pointer.

Two authentic source changes then restored the exact native ABI:

1. Reassign the **actual by-value `native_format` argument** from
   `select_texture_format` rather than creating a second format
   temporary. Original x86 stores back to the caller-frame parameter
   at relative `+0x1F` before using its index twice in the byte-size
   table.
2. Express the **actual filter decision directly as the
   `D3DXLoadSurfaceFromFileInMemory` argument**, rather than storing
   an extra intermediate DWORD. The pinned compiler naturally
   generates the original one actual filter local, genuine COM
   GetSurfaceLevel NOP, exact native jumps and the original result
   branches without a manufactured instruction.

These operations are meaningful texture/upload decisions, not an
unused compiler-shaping variable, target byte patch, hand-coded
assembly or truncated match. The exact whole result is **562B/177**.

## Independent original executable and canonical proof

The original function has six genuine native E8:

| Original E8 | Original destination |
| --- | --- |
| `+0x17` | game format selector `0x0044CFB0` (77B) |
| `+0x10A` | `Graphics::get_device` `0x00412730` |
| `+0x12C` | genuine `D3DXCreateTexture` IAT `0x005406A2` |
| `+0x1AE` | genuine `D3DXLoadSurfaceFromFileInMemory` IAT `0x00540696` |
| `+0x1FB` | separate game **2,745B** texture finalizer `0x00451910` |
| `+0x227` | native cookie check `0x005429EE` |

The full original immutable format table `0x0056E208` contains nine
32-bit D3DFORMAT words `(0,21,21,21,21,21,21,21,21)`; the matching
nine texture-byte-size words at `0x0056E22C` are all `4`. Both real
36-byte original tables are now locked by the independent verifier,
not assumed from prior source comments. The source definitions in
`Graphics.cpp` and `AnimationDynamicTexture155.cpp` agree with those
actual original data words.

The **13 PE HIGHLOW fields** include the real security cookie,
four live scale references to `0x005B8818`, two original native
2.0f comparisons at `0x0056C8D0`, two float 0.5f constants at
`0x0056E0EC`, the selected D3D9 format table `0x0056E208`,
actual Graphics global `0x005C4D40`, and both byte-size lookups
at `0x0056E22C`. The checker
[`verify-animation-texture-upload562-native.py`](../scripts/verify-animation-texture-upload562-native.py)
reads and SHA-pins the **entire original** 562B/177-i386, all
19 true native PE physical reference site/target pairs and the
real original native 2,745B finalizer extent, then compares the
complete canonical C++ object and its fresh strict receipt.

```text
animation_texture_upload_from_memory_562: exact (562/562 bytes)
Original whole function: 562B /177 i386
Nonrelocated original bytes: 486/486
Original reference fields: 6 E8 REL32 +13 PE HIGHLOW
Exact replay: 1/1 unit, ONE affected cold object
```

This contributes **one distinct game-authored exact function /
562 original executable `.text` bytes**. Previously credited
format selection, Graphics accessor, D3DX SDK calls, and the
independent **now SOURCE-PRESENT, NONEXACT 2,745B finalizer** are
not recredited by transitivity. The whole game still does not
build/link/play. No full-project cold replay was run.

```sh
scripts/repo-python scripts/verify-animation-texture-upload562-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationFileTextureLoad562.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1101 — native 2,745B finalizer now has its own game source

The original `0x00451910` texture-alpha finalizer invoked at this
exact 562B uploader's physical E8 `+0x1FB` is now
[source-present but still NONEXACT](ANIMATION_TEXTURE_FINALIZER2745_NATIVE_FRONTIER.md).
Its source reconstructs the full four-format D3D9 surface scan and
actual 16 RGB neighborhood helper calls, preserves genuine original
switch tables outside the 2,745B code extent, and shares one typed
Renderer borrow through `NativeRendererTextureMemoryView.hpp`.
The original 562B upload has been **source-scoped rebuilt and
revalidated 562/562 exact** after the header migration. No 2,745B
byte count is credited as exact or merged with the uploader.

## CORE/RECON-1102 — four existing exact texture-neighbor helpers now credited game-owned

The separately still-NONEXACT 2,745B original game texture finalizer
invoked by this WHOLE-EXACT 562B uploader calls four original
[format-specialized RGB/alpha neighbor kernels](ANIMATION_TEXEL_FOUR_GAME_ORIGIN_692_STRICT_EXACT.md)
exactly four times each. All four original kernels (139B/183B/183B/187B)
were already WHOLE strict exact under REF-042. Their original game
Renderer domain ownership is now independently attested with
medium provenance confidence, reclassifying the already exact
**692 native bytes as authored** but adding **zero new exact units**.
This 562B uploader remains independently exact without recrediting
its finalizer or any pixel-helper executable bytes.
