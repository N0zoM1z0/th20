# CORE/RECON-1092 — original 581B D3D9 Renderer color-effect surface Boss, WHOLE strict exact

Immutable Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The game-owned original `0x0044BE40` is a complete **581B/201-i386**
Renderer D3D9 color-effect surface-transfer Boss with whole original
SHA-256
`b515085a0793cb68b558ccf8704a506c05e8fef7fd4abdefc5f99e648d619e77`.
The entire function, including its genuine `ret 0x18` and all
original call/data relocation fields, is now independently WHOLE
STRICT EXACT from real C++20 in
[`AnimationSurfaceEffect581.cpp`](../src/AnimationSurfaceEffect581.cpp).
The original [CORE/RECON-1088 580B compiler frontier](ANIMATION_SURFACE_EFFECT581_NATIVE_FRONTIER.md)
is superseded, not a reason to shorten the original native extent.

## Complete original Renderer file surface and RGB effect protocol

The method uses the same actual Renderer 42-slot
`std::array<AnimationFile*,42>` at `this+0x06000730` and original
24B `TextureRecord`s as the [independently WHOLE-EXACT 439B
D3D9 RECT blit Boss](ANIMATION_SURFACE_BLIT439_STRICT_EXACT.md).
Its genuine `__thiscall` ABI takes six additional arguments: file
index, texture index, source D3D9 surface pointer, destination
`RECT*`, source `RECT*`, and optional color effect selector. The
original selects a texture, flushes pending draw commands using the
exact 192B Renderer `flush_draws`, gets a level-zero surface via
the real D3D9 vtable method, then calls
`D3DXLoadSurfaceFromSurface` with point filtering and real source
and destination RECTs. It releases the acquired surface on errors.

For `effect == 1`, the method additionally locks the destination
surface, checks the real `HRESULT`, and updates each 32-bit pixel
inside the actual locked rectangle. It copies each pixel word into
a genuine four-byte original color staging value, then invokes the
**already accepted original 92B `NativeRendererRandomPulse::random_byte_449d20`**
three separate times, each through the **same actual game state
at `0x005BA4C4`**. The green and blue channels use the original
**signed 32-bit `(channel*random_byte())/0x300`**, red uses
`/0x500`, and alpha becomes `0xff`. There are no invented
64-bit-multiply CRT routines, hidden retries or other random
engines. The original walks each pixel in 4-byte units and advances
rows by the actual unsigned **`locked.Pitch >> 2`** count of
32-bit pixels, then calls `UnlockRect` and `Release` on its
acquired surface before the native cookie/return sequence.

## Nine original E8 and four PE HIGHLOW, exact whole physical body

The native original has nine real E8 at:

| Original E8 | Physical original target |
| --- | --- |
| `+0x27` and `+0x5C` | existing folded 22B `std::array::operator[]` `0x00414580` |
| `+0x43` | original 192B `flush_draws` `0x004455C0` |
| `+0xA9` | D3DX9 surface-to-surface copy `0x0054069C` |
| `+0x13E` | existing original folded 23B zero-value constructor `0x00425CC0` |
| `+0x180`, `+0x1AA`, `+0x1D1` | same game-owned exact 92B random pulse `0x00449D20` |
| `+0x23A` | genuine original cookie check `0x005429EE` |

There are four actual PE HIGHLOW: original `+0x07` cookie
`0x005B25C0`, and three physical references
`+0x17C/+0x1A6/+0x1CD` to the same native random-state global
`0x005BA4C4`. Every one of these original relocations is
independently verified by the locked original executable, not
predicted from generated COFF first.

## Recovered actual C++ local-surface lifetime, not fabricated padding

The first meaningful source was 709B with six inappropriate CRT
64-bit multiply/divide calls. Restoring signed native 32-bit
arithmetic, actual four-byte staging color, locked RECT and
unsigned `Pitch>>2` stride produced a complete C++20
**580B/200-i386** compiler body with all nine E8/four original data
roles, but missing the original **real `0x90` NOP immediately after
`flush_draws()` at native `+0x48`**. The byte difference was
initially documented as NONEXACT, without falsely claiming
normalized code as an exact accepted function.

Re-examining the physical D3D9 resource lifetime established that
**the acquired surface and its optional locked pixel data belong
to one inner lexical scope which starts after drawing is flushed**.
Representing that actual game lifetime in ordinary C++:

```cpp
if (selected_texture == nullptr) return;
flush_draws();
{
    // Original scoped level-zero D3D9 surface and optional locked pixels.
    IDirect3DSurface9* dest_surface;
    // GetSurfaceLevel, D3DX copy, optional LockRect/channel updates,
    // UnlockRect and Release within this same scope.
}
```

causes pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
to **naturally** generate the original post-flush NOP and restore
the original branch displacement. The entire authentic COFF
function becomes **581B/201 i386**, with **529/529 nonrelocated
original bytes**, all **13 real original relocation fields and
native destinations**. No `asm`, dead expression, source fake NOP,
custom generated bytes, truncated native target or compiler patch
was used. The adjacent 439B original texture blit was independently
recovered through the same meaningful D3D9 surface-lifetime scope
in CORE/RECON-1091; this is distinct second native game code.

[`verify-animation-surface-effect581-native.py`](../scripts/verify-animation-surface-effect581-native.py)
independently hashes the entire original native 581B, checks
all 201 instruction boundaries and the actual NOP/return, all
nine E8/four PE HIGHLOW targets, the original 23B/92B callee
bodies, then verifies the **whole** canonical object and original
physical relocation positions. Accepted scoped replay:

```text
animation_renderer_surface_effect_581: exact (581/581 bytes)
Entire original body and generated source: 581B/201-i386
Comparable native bytes: 529/529
Relocation roles: 9 E8 REL32 +4 data DIR32
Exact replay: 1/1 unit, 1 cold object
```

This adds **one distinct game-authored original physical head /
581 executable `.text` bytes**. The 439B game blit, 192B flush,
23B folded constructor, 22B folded array index, 92B random pulse
and D3DX implementation are all separately owned and **not
recredited**. The game remains not fully linked or playable.
No project-wide cold replay was executed.

```sh
scripts/repo-python scripts/verify-animation-surface-effect581-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationSurfaceEffect581.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
