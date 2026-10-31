# CORE/RECON-1087 — entire original 439B D3D9 sprite texture surface-copy Boss, 438B source frontier

Original immutable Japanese TH20 Steamless v1.00a target SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The game-owned Renderer method `0x0044BB10` is a complete
**439B/158-i386** D3D9 texture-to-texture rectangular copy method,
original native SHA-256
`27b31b093609d78ab184c3b2894a380b9180404e726fd64202d946651451e860`.
The source is now maintained as the actual C++20 method
[`NativeRendererSurfaceBlitView::blit_surface_rect_44bb10`](../src/AnimationSurfaceBlit439.cpp),
**SOURCE-PRESENT, NONEXACT**, not a fake exact target prefix.

The native receiver is the same renderer whose 192B native
`AnimationPoolOwner::flush_draws()` is already whole-exact. Its
huge file-slot table lives at receiver `+0x06000730`, a true
**42-entry `std::array<AnimationFile*,42>`**. The original calls
existing folded **22B** `std::array::operator[]` three times, at
native E8 `+0x27`, `+0x6C`, `+0x15D`, to resolve the file and
24B `TextureRecord` at `AnimationFile+0x58` using the 0x18 stride.
The argument is a true **40B** rectangular blit command:
file index, texture index, source left/top/width/height and
destination left/top/width/height, not an opaque hardware string.

The full native method tests the selected `IDirect3DTexture9*`,
flushes pending Renderer draw commands at **E8 `+0x51`**, obtains
a level-0 `IDirect3DSurface9*` via actual virtual `GetSurfaceLevel`
(vtable `+0x48`), builds two genuine Win32 `RECT`s using their
width/height deltas, and calls the original D3DX9
`D3DXLoadSurfaceFromSurface` at native **E8 `+0x12F`**. Its source
surface is the actual process-global pointer `0x005C4EE4`, the
only non-cookie native HIGHLOW field (`+0x120`). On successful
D3DX loading, the native method uses actual texture `AddDirtyRect`
(vtable `+0x54`) with null rectangle, then releases the acquired
level surface. On unsuccessful loading it releases the surface
without dirtying the texture. It does not treat `+0x54` as
`UnlockRect`, which is a *different* texture vtable method at
`+0x50`. Texture and surface lifetimes and branch boundaries
are faithfully expressed in ordinary C++20 and SDK D3D9 calls.

The original has **six physical E8/two PE HIGHLOW**:

| Original E8 | Real destination |
| --- | --- |
| `+0x27/+0x6C/+0x15D` | existing 22B folded array index `0x00414580` |
| `+0x51` | existing 192B game draw flush `0x004455C0` |
| `+0x12F` | native D3DX9 surface-to-surface copy `0x0054069C` |
| `+0x1AC` | native cookie check `0x005429EE` |

The PE HIGHLOW fields are cookie `+0x07 -> 0x005B25C0`
and source surface global `+0x120 -> 0x005C4EE4`. Its full native
function ends in `ret 4` at the original 439B boundary. This is
an authentic **D3D9 Renderer gameplay path**, not a generic STL
method and not an extracted short leaf.

## One genuine old compiler NOP still prevents whole exact acceptance

Pinned MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` naturally builds this entire C++ body to
**438B/157 i386**, containing the same **6 REL32/two DIR32 roles**,
all true `GetSurfaceLevel`/`D3DXLoadSurfaceFromSurface`/`AddDirtyRect`
and `Release` branches. This was independently compared against
original **439B/158 i386**. The entire physical original contains
**one genuine `0x90` NOP** immediately after its Renderer
`flush_draws()` call, at relative offset **`+0x56`**. The current
compiler does not emit that byte. After *diagnostically* removing
only that independently attested native NOP and blanking the
original relocation fields at their true physical sites,
the complete candidate has **437/438 equal ordinary bytes**:
the only differing byte is the preceding branch displacement
`0x59` vs `0x58`, precisely due to the one original NOP. Native
relocation fields then align physically after the missing NOP.
This comparison is **diagnostic only**, not an exact oracle
match and not a request to truncate original function length.

The original NOP is part of the function's legitimate compiled
extent. Inserting a fake empty statement, `asm`, synthetic padding,
changed native byte, false return or shortened target extent
would violate source-authenticity requirements. This method is
therefore **SOURCE-PRESENT, NONEXACT** with **zero new credited
original game code**, despite the extraordinarily close natural
code shape. The already exact 22B folded array index and 192B
game draw queue flush are not recredited.

The independent locked-original verifier
[`verify-animation-surface-blit439-native.py`](../scripts/verify-animation-surface-blit439-native.py)
checks the entire 439B SHA and every native E8 and HIGHLOW
position/target, the actual 158 decoded instructions and native
NOP, real natural C++ 438B/157 candidate, and the solely
**diagnostic** normalized byte difference. No exact match unit is
registered, and no whole-project replay is necessary for this
new source-only NONEXACT parent.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/AnimationSurfaceBlit439.cpp build/core1086-probes/AnimationSurfaceBlit439.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-animation-surface-blit439-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```
