# CORE/RECON-981 — full original 188B Direct3D9 texture-surface clear whole strict exact

Locked original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Original `0x00449D80` is a complete game-owned **188B/75-i386**
Direct3D9 texture surface zeroing method, receiving a genuine
`IDirect3DTexture9**` in ECX. It first gets mip level zero's
`IDirect3DSurface9*`. When the returned surface is nonnull, it
queries the real `D3DSURFACE_DESC` and uses a `D3DLOCKED_RECT`
to clear `Pitch * Height` bytes via `memset`, unlocks, calls COM
`Release()` and clears its local surface pointer. There is no invented
Renderer class allocation or substitute managed resource.

[`scripts/verify-animation-texture-surface-clear188-native.py`](../scripts/verify-animation-texture-surface-clear188-native.py)
reads the immutable original PE and checks all 188 original code
bytes, the 75 decoded instructions and genuine `ret`, full virtual
call slots and both original E8/one HIGHLOW role:

| Original operation | Physical instruction / destination |
| --- | --- |
| `Texture::GetSurfaceLevel` | actual vtable `+0x48`, level 0 |
| `Surface::GetDesc` | actual surface vtable `+0x30`, returned `D3DSURFACE_DESC` |
| `Surface::LockRect` | vtable `+0x34`, rect and zero flags |
| `std::memset` | E8 `+0x7C -> 0x00544760` with `locked.Pitch * desc.Height` |
| `Surface::UnlockRect` | actual vtable `+0x38` |
| `Surface::Release` | actual IUnknown vtable `+0x08` and original local surface=nullptr afterwards |
| security cookie | HIGHLOW `+0x07 -> 0x005B25C0`, E8 `+0xB3 -> 0x005429EE` |

Natural C++20
[`src/AnimationTextureSurfaceClear188.cpp`](../src/AnimationTextureSurfaceClear188.cpp)
uses the real Windows D3D9 SDK and `std::memset` API. The first source
omitted a native empty null-surface branch and the original
post-Release nulling of a local pointer; the compiler emitted an
incorrect **180B** instead. Preserving these actual source semantics
naturally generated **188B/75 i386, 176/176 matching nonrelocated
bytes plus all three original relocations**, with no manual NOPs,
handwritten machine code or target patches.

Pinned MSVC 19.44 x86 `/std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` strict original-target-bound
single-source replay:

```text
animation_texture_surface_clear_188: exact (188/188 bytes)
Exact replay: 1/1 unit, 1 cold object
```

This contributes **one distinct whole-exact original game-authored
head /188 `.text` bytes**. Existing graphics/CRT wrappers and any
not-yet-restored original callers are not recredited. Whole-game
build/link/playability, the 508B/511B Animation-list update bosses,
2,884B particle Update and 39,470B Animation VM remain unfinished.
No global cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-texture-surface-clear188-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationTextureSurfaceClear188.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
