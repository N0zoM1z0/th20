# CORE/RECON-997 — complete 139B Renderer render-target creator strict exact

Target: locked Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original `0x0044C150..0x0044C1DA` is the **whole 139-byte /
48-instruction** game-owned D3D9 render-target creator, with one real
`__thiscall` receiver in ECX and three 32-bit stack parameters. The latter
are `TextureRecord*`, width, and height. The receiver's complete layout and
original C++ type spelling remain unknown, so
[`NativeRendererTextureOwner`](../src/NativeRendererTextureCreate.hpp)
is an *empty, non-owning ABI view*, not a fabricated owner layout or free
function in place of the native member function.

## Complete original semantics

The native function preserves flag bits outside `TextureRecord+0x14` low
two bits, setting those bits to 1; it obtains the genuine process Graphics
D3D9 device, and invokes the real COM `CreateTexture` vtable method at
`+0x5C`, passing width, height, one mip level, `D3DUSAGE_RENDERTARGET`,
`D3DFMT_A8R8G8B8`, `D3DPOOL_DEFAULT`, the `TextureRecord+0` pointer slot,
and null shared-handle output. Its nonzero `HRESULT` arm invokes the genuine
original diagnostic, without suppressing positive HRESULT results.
The final byte-size selection compares Graphics.presentation's true
`BackBufferFormat` at process Graphics `+0xEC` to D3D format `0x15`,
writes four or two into the record `+0x0C`, then returns zero.

[`verify-animation-texture-creator-native.py`](../scripts/verify-animation-texture-creator-native.py)
independently attests the entire original PE body SHA-256
`7af99aae8840f398d452b070ca18f65ebc943e650a715fcfb628487f5dd707dc`,
all 48 instruction boundaries, true `ret 12`, five adjacent native `INT3`
and every original relocation field before comparing a compiled object:

| Original field | Type | Native physical destination |
| --- | --- | --- |
| `+0x1C` | DIR32 | `0x005C4D40` process Graphics |
| `+0x21` | REL32 | `0x00412730` folded Graphics device getter |
| `+0x55` | DIR32 | `0x0056E250` actual diagnostic string |
| `+0x5A` | REL32 | `0x0040C6B0` folded diagnostic implementation |
| `+0x63` | DIR32 | `0x005C4D40+0xEC` presentation format member |

The source is natural
[`src/AnimationRenderTarget139.cpp`](../src/AnimationRenderTarget139.cpp),
using the actual SDK's `IDirect3DDevice9::CreateTexture`, not a handwritten
vtable dispatch or fabricated return. Locked MSVC 19.44 x86 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` produces the
entire **139B**, **119/119 nonrelocated bytes** and **all five independently
anchored relocation roles** exactly. Reproducible canonical replay:

```text
animation_render_target_139: exact (139/139 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The prior Graphics accessor and diagnostic function are folded/template
physical units with their own earlier exact credit; no duplicated
original byte intervals were introduced. This acceptance adds **one
complete original game-authored function /139 native `.text` bytes**.
The original adjacent 155B dynamic texture creator is still independent and
**NONEXACT** at this checkpoint, as are full Renderer ownership and whole-game
link/playability. No full-graph cold replay ran.

```bash
scripts/repo-python scripts/verify-animation-texture-creator-native.py \
  --variant target --candidate-object build/core997-canonical/AnimationRenderTarget139.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationRenderTarget139.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
