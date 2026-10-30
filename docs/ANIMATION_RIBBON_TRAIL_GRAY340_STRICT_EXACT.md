# CORE/RECON-940 — whole original 340B gray trail ribbon configuration Boss strict exact

Immutable Japanese TH20 v1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original `0x0045E240` is a **340B/101-i386** author-specific gray
palette and geometry setup for the same 64-point `NativeRibbonTrailGroup`
whose [103B ctor](ANIMATION_RIBBON_TRAIL_GROUP_CTOR103_STRICT_EXACT.md),
[520B update](ANIMATION_RIBBON_TRAIL_UPDATE520_STRICT_EXACT.md) and
[165B draw](ANIMATION_RIBBON_TRAIL_DRAW165_STRICT_EXACT.md) are already
independently whole-exact. It is called by the separate original 47B
factory/configuration wrapper `0x0045E520` at E8 `0x0045E546`.

[`scripts/verify-animation-ribbon-trail-gray340-native.py`](../scripts/verify-animation-ribbon-trail-gray340-native.py)
fully validates original 340B /101 disassembled instructions, all
**10 E8 positions and actual physical destinations**, **two real PE
HIGHLOW fields/targets**, genuine final `ret 8`, and the original 47B
parent E8. The memory/behavior proof is:

- Set genuine `vertices_08[0]` x/y to zero using two separate native
  E8 calls to `0x0045D670`, then initialize angle using
  `GameRandom::range(pi)` and Timer to 1.
- Populate all 64 native four-byte packed-color records at `+0x208`
  with **`0xFF505050`**; for indices 0–7 modify byte 0 by
  `255-(index<<5)`, and indices 32–63 modify byte 3 with the
  independent alpha ramp `255-(tail_index<<4)`.
- Set Animation position from the argument, layer **19**, and invoke
  original `0x0045E590` to clear its flag byte.

A real ABI correction was needed: the first otherwise natural source
compiled to **340B/101-i386** with **291/292** nonrelocated bytes,
but emitted `ret 4`. Original `ret 8` proves an additional second
argument, even though this gray mode never reads that token. Restoring
`configure_gray_45e240(const Vector3&, int unused_token)` yields **all
292/292 nonrelocated bytes**, preserves natural gameplay code, and
correctly emits the original return cleanup. No machine-level patch,
fake padding, or fabricated return path was inserted.

[`src/AnimationRibbonTrailGroupGray340.cpp`](../src/AnimationRibbonTrailGroupGray340.cpp)
uses real native layout through the shared class and ordinary C++20
signed loop/byte-field accesses. Pinned MSVC x86 C++20 `/Od /Ob0 /GS
/Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` and the strict original
relocation oracle verify all **12 original fields** and complete code:

```text
animation_ribbon_trail_gray_340: exact (340/340 bytes)
Previous 103B ctor, 49B destructor, 520B update, 165B draw, 156B factory: exact
Exact replay: 6/6 units, 5 cold objects
```

The 340B game-specific function adds **one newly credited authored
original head /340 `.text` bytes**. The distinct original 382B pink
configuration path remains separate pending its own whole native proof.
No unfiltered graph-wide cold replay ran.

```bash
scripts/repo-python scripts/verify-animation-ribbon-trail-gray340-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonTrailGroupGray340.cpp --source src/AnimationRibbonTrailGroupUpdate520.cpp --source src/AnimationRibbonTrailGroupDraw165.cpp --source src/AnimationRibbonTrailGroupCtor103.cpp --source src/AnimationRibbonTrailGroupFactory156.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
