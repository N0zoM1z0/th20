# CORE/RECON-1091 — complete native 439B D3D9 Renderer surface blit Boss, whole strict exact

Immutable original Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original game-owned `0x0044BB10` is a whole **439B/158-i386**
D3D9 sprite RECT texture transfer, physical SHA-256
`27b31b093609d78ab184c3b2894a380b9180404e726fd64202d946651451e860`.
It is now **WHOLE STRICT EXACT** under ordinary pinned MSVC 19.44
C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
using real game C++ in
[`AnimationSurfaceBlit439.cpp`](../src/AnimationSurfaceBlit439.cpp).
The previously documented [438B NONEXACT frontier](ANIMATION_SURFACE_BLIT439_NATIVE_FRONTIER.md)
is historical, superseded by a recovered genuine native C++
surface-lifetime scope.

## Whole original native D3D9 resource and rectangle behavior

The original function receives a non-owning Renderer receiver and
one 40B `NativeSurfaceBlitCommand` argument holding file and
texture indices plus source/destination rectangle origins and
extents. The true 42-entry `std::array<AnimationFile*,42>` file
table is at native Renderer receiver **`+0x06000730`**, and
texture records are 24B entries at `AnimationFile+0x58`. Three
distinct original array-index E8 calls look up selected texture
records, and the game first checks for an existing native texture
pointer. If absent, no D3D9 or other Renderer calls are made.

After a valid texture, the original **192B `flush_draws()`** drains
pending GPU draws. A distinct inner C++ scope then owns the
**level-zero `IDirect3DSurface9*`** lifetime. The method performs
D3D9 `GetSurfaceLevel(0)`, creates true source and destination
Win32 `RECT`s from positions and widths/heights, and invokes
`D3DXLoadSurfaceFromSurface` using the real original source-surface
global at **`0x005C4EE4`** and point sampling. Failed copies
release the acquired surface without dirtying the selected
texture; successful transfers call actual D3D9 texture
`AddDirtyRect(nullptr)` (the original virtual method at
vtable `+0x54`, not `UnlockRect`) and release the temporary
surface. The same actual game Renderer and AnimationFile owner
interfaces are reused; no shadow allocated Renderer is invented.

The entire original game method contains **six true E8**:

| Native E8 | Physical original target |
| --- | --- |
| `+0x27`, `+0x6C`, `+0x15D` | existing folded 22B `std::array::operator[]`, `0x00414580` |
| `+0x51` | existing whole-exact 192B `AnimationPoolOwner::flush_draws`, `0x004455C0` |
| `+0x12F` | actual D3DX9 surface copy `0x0054069C` |
| `+0x1AC` | real cookie check `0x005429EE` |

Two original physical PE HIGHLOW fields are `+0x07` security
cookie `0x005B25C0` and `+0x120` real D3D9 source-surface pointer
`0x005C4EE4`. The original ends at real `ret 4` after **439B**.

## A true C++ scope, not a hand-crafted extra NOP

The first game-specific source restored all of these genuine
operations but emitted only **438B/157-i386** with original six
E8/two HIGHLOW roles. The native original had an additional
**real `0x90` NOP immediately after `flush_draws()`, at `+0x56`**;
its preceding branch offset differed by one. Merely removing this
original NOP *for a diagnostic comparison* gave 437/438 matching
nonrelocated bytes, but that is **not** a valid exact acceptance.
This was recorded in historical CORE/RECON-1087.

Rechecking the actual resource lifetime showed that the original
D3D9 surface is acquired *after* draw flush and used only within
its own inner lexical scope. Expressing this **genuine lifetime
boundary** in C++:

```cpp
if (selected_texture == nullptr) return;
flush_draws();
{
    // Actual independently scoped acquired surface and RECT lifetime.
    IDirect3DSurface9* surface;
    // GetSurfaceLevel, D3DXLoadSurfaceFromSurface, AddDirtyRect,
    // Release, with native early-return branches.
}
```

makes the pinned MSVC source naturally emit that exact original
`0x90` **compiler instruction at the proper position**, including
the original branch displacement, **without inserting any empty
instruction, asm, padding, fake owner or unreachable statement**.
This controlled source change adds one real compiler-generated
instruction while preserving all real resource semantics. The
entire emitted C++20 body is now **439B/158 i386**, with **407/407
original nonrelocated code bytes** and eight relocations at the
original full physical positions.

The independent locked-PE verifier
[`verify-animation-surface-blit439-native.py`](../scripts/verify-animation-surface-blit439-native.py)
SHA-attests the whole original 439B, full 158 instructions and
native `NOP`, all original E8 and PE HIGHLOW physical destinations,
and checks natural compiler source and every independent COFF
relocation field. The accepted unit is not truncated or normalized:

```text
animation_renderer_surface_blit_439: exact (439/439 bytes)
Entire immutable original PE body: 439B /158 i386
Natural MSVC code / ordinary bytes: 439B /407 of 407
Original relocation roles: 6 REL32 E8 +2 DIR32 HIGHLOW
Exact replay: 1/1 strict unit, 1 cold object
```

**One new game-authored physical original head /439 distinct
original executable `.text` bytes** is credited. Previously
accepted 22B folded array-index method, 192B Renderer flush and
native D3DX library implementation are *not* re-credited. The
adjacent 581B random-color surface effect was separately
SOURCE-PRESENT/NONEXACT at the time of this checkpoint and is
subject to its own independent original-boundary proof.
The entire game still does not link/play; no whole-project cold
replay or target executable modification was used.

```sh
scripts/repo-python scripts/verify-animation-surface-blit439-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationSurfaceBlit439.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
