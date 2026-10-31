**CORE/RECON-1091 CURRENT CORRECTION:** Original Renderer 439B D3D9 surface blit at `0x0044BB10` is now [WHOLE STRICT EXACT 439/439](ANIMATION_SURFACE_BLIT439_STRICT_EXACT.md). A genuine nested C++ surface-lifetime scope after Renderer draw flush naturally makes MSVC emit the original one-byte `NOP`, 407/407 nonrelocated bytes and all six E8/two HIGHLOW. Earlier 438B/NONEXACT statements below are historical; no fake padding or truncated original boundary was used.

# CORE/RECON-1088 — whole original 581B D3D9 texture surface color-effect Boss, natural 580B source frontier

Locked Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original game-owned Renderer method `0x0044BE40` is a **complete
581B/201-i386 native function**, original whole SHA-256
`b515085a0793cb68b558ccf8704a506c05e8fef7fd4abdefc5f99e648d619e77`.
The function is not a generic standard-library method. It is the
second game-owned D3D9 texture-surface transfer method adjacent to
the independently restored **439B rectangle blit `0x0044BB10`**;
these two original native heads have distinct argument and pixel
lifetime protocols.

The original 581B receiver points at the Renderer file table at
**`this+0x06000730`**, a real `std::array<AnimationFile*,42>` with
native `AnimationFile+0x58` 24B texture record entries. The input
ABI has **six stack parameters**: file index, texture index, source
`IDirect3DSurface9*`, destination `RECT*`, source `RECT*`, and
optional color-effect enable integer. The method rejects absent
textures, flushes the queued Renderer draw primitives via the real
**192B `AnimationPoolOwner::flush_draws()`**, gets texture level-0
surface with D3D9 virtual `GetSurfaceLevel`, and invokes genuine
`D3DXLoadSurfaceFromSurface` with point sampling. It releases that
surface on error.

If the transfer succeeds and `effect==1`, the method calls surface
`LockRect`, checks the original returned HRESULT, then traverses
actual destination-RECT width and height on the locked 32-bit DIB.
A **4B original packed-color staging value** is initialized once
per column and receives each pixel word. For every pixel, the
original invokes the native **92B Renderer random-byte helper
`0x00449D20` three times**, through the same state owner at
**global `0x005BA4C4`**. It updates original green and blue
channels by subtracting their corresponding signed
`(channel*random_byte)/0x300`, red by `(red*random_byte)/0x500`,
sets alpha to 0xFF, and moves the pixel pointer. The original
row advance uses **`locked.Pitch >> 2` as an unsigned number of
32-bit pixels**, not a masked byte stride. The method ends with
surface `UnlockRect`, `Release`, and the real compiler security
cookie check. The observed game behavior is implemented by
[`src/AnimationSurfaceEffect581.cpp`](../src/AnimationSurfaceEffect581.cpp)
using genuine D3D9 SDK declarations, normal Win32 `RECT`, signed
integer color arithmetic, existing `PackedColor` staging and
[`NativeRendererRandomPulse`](../src/NativeRendererRandomPulse.hpp).
No fake 64-bit CRT multiply or invented random engine is used.

## Nine original E8 and four physical HIGHLOW

The immutable original has:

| Native original E8 | Real physical destination |
| --- | --- |
| `+0x27`, `+0x5C` | already-exact folded 22B array index `0x00414580` |
| `+0x43` | already-exact 192B Renderer draw flush `0x004455C0` |
| `+0xA9` | actual D3DX9 surface-to-surface copy `0x0054069C` |
| `+0x13E` | already-exact folded 23B four-byte value constructor `0x00425CC0` |
| `+0x180`, `+0x1AA`, `+0x1D1` | same 92B game random-byte method `0x00449D20` |
| `+0x23A` | real cookie check `0x005429EE` |

The four genuine PE HIGHLOW fields are cookie
`+0x07 -> 0x005B25C0` and three **independent** original references
`+0x17C/+0x1A6/+0x1CD -> 0x005BA4C4` to the *same* real game
random-state owner. There are no invented extra data globals.
The original complete function ends in actual `ret 0x18`.

## A meaningful native 580B source — not fabricated 581B exactness

The initial real C++20 candidate was 709B/255 instructions and
incorrectly produced **six additional CRT `__allmul` and
`__aulldiv` calls** because the channel product had been
erroneously promoted to a 64-bit multiplication before division.
The original 8-bit input product is bounded within a signed 32-bit
word; the native method uses signed `idiv` by the actual constants
0x300 and 0x500, not those CRT functions. Correcting the native
promotion, preserving each byte extraction directly from the
4B packed color staging object, keeping the `LockRect` HRESULT
as a meaningful local result, and expressing original 32-bit pixel
row strides naturally produced **580B/200-i386**, with **nine
REL32 and four DIR32** under pinned MSVC 19.44 C++20 x86
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.

The original complete native source is **581B/201-i386**. It
contains exactly **one genuine native `0x90` NOP at relative
`+0x48` immediately after `flush_draws()`** that modern installed
MSVC does not produce here. The original neighboring 439B
texture-blit method has a separate identical compiler frontier
at its original flush call. Read-only
[`verify-animation-surface-effect581-native.py`](../scripts/verify-animation-surface-effect581-native.py)
attests the **entire original 581B SHA/201-i386** and all nine
E8/four native HIGHLOW destinations, independently checks the
original 23B constructor and 92B random-byte whole native bodies,
and verifies the real 580B C++20 code/relocation graph. If one
*independently original* NOP is removed for a **diagnostic only**
comparison and all original relocation fields are masked, **579/580
ordinary bytes agree**. The sole remaining byte is a branch
distance `0xF3` vs `0xF2`, exactly reflecting that 1B NOP.

This comparison deliberately **does not register an exact unit**:
truncating the physical original, adding a fake `nop`, using assembly
or inventing inert compiler-shaping source would misrepresent the
original. **Status SOURCE-PRESENT/NONEXACT**. No newly credited
game-authored exact code is claimed for this original 581B parent.
The already strict 23B and 92B native child code is not credited
a second time, and the 439B original blit remains independently
source-present/NONEXACT. No full-project replay was run.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/AnimationSurfaceEffect581.cpp build/core1088-probes/AnimationSurfaceEffect581.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-animation-surface-effect581-native.py
scripts/repo-python scripts/verify-animation-surface-blit439-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```
