# CORE/RECON-915 — whole 538B ribbon segment dynamics Boss strict native exact

Original target is the user-selected Japanese TH20 1.00a Steamless executable,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0045E800` is a game-authored **538B /149-i386** ribbon
segment dynamics method, physically called by the independently exact
[140B ribbon-group update](ANIMATION_RIBBON_GROUP_UPDATE_140_STRICT_EXACT.md)
at E8 `0x0045E7D8`. Its own native code, relocations, and C++ source are
now independently whole strict exact, not merely semantically similar.

## Original PE complete proof

[`scripts/verify-animation-ribbon-dynamics538-native.py`](../scripts/verify-animation-ribbon-dynamics538-native.py)
reads only the locked original PE and independently verifies **all 538B**,
the exact 149 disassembled i386 instructions and final `ret 4`, **all
13 original E8 site/destination pairs**, **all 10 original HIGHLOW
field/destination pairs**, real `+0x115` NOP, native 4B radius/8B point
strides, closing index 59 and the original parent call. No candidate
COFF bytes, Ghidra labels or local hypothesis can redefine those checks.

| Real physical original role | Original call / data target |
| --- | --- |
| E8 `+0x034`, `+0x11F` | `0x0040BDA0`: folded address/begin primitive |
| E8 `+0x03F`, `+0x12A` | `0x0045DCA0` and `0x0045DCC0`: separately exact 19B float/point array ends |
| E8 `+0x069` | `0x004298E0`: game signed random scalar |
| E8 `+0x110`, `+0x173`, `+0x1BE` | `0x00429210`, `0x004292E0`, `0x004530C0`: native Angle constructor, conversion, increment |
| E8 `+0x162` | `0x00414580`: float array indexing (physically folded) |
| E8 `+0x195` | `0x00439330`: polar position generation |
| E8 `+0x1DC`, `+0x1F7` | `0x0045D670` twice: 8-byte indexed geometry copy, physically folded |
| E8 `+0x20C` | `0x005429EE`: native stack-cookie check |
| HIGHLOW `+0x01A`, `+0x065` | `0x005B25C0` cookie, `0x005BA4C4` RNG instance |
| HIGHLOW `+0x07A`, `+0x1A9` | `0x0056C8D0` = 2.0f |
| HIGHLOW `+0x0A9`, `+0x0C2`, `+0x0D8`, `+0x0ED` | `0x0056C8E0` = 4.0f radius bound |
| HIGHLOW `+0x1A1`, `+0x1B1` | `0x0056E0F0` = pi (float), `0x0056EE48` = 59.0f |

These **23 distinct original physical relocation fields** are independently
mapped to the same 23 whole-function COFF fields, with complete code bytes;
no shortened extent or guessed relocation target is accepted.

## Natural C++ and compiler lowering

The genuine segment has **60 `Vector2` points /60 four-byte colors /60
float radii**, total `0x3C0`, as recorded in
[`NativeRibbonPolygonGroup.hpp`](../src/NativeRibbonPolygonGroup.hpp).
The two actual 19B end helpers are [independently exact](ANIMATION_RIBBON_ARRAY_END_HELPERS_19_STRICT_EXACT.md).
The whole new [`src/AnimationRibbonSegmentDynamics538.cpp`](../src/AnimationRibbonSegmentDynamics538.cpp)
models the complete original control flow:

1. Iterate all 60 radii, adding real signed random displacement scaled by
   2.0f; clamp each radius around caller-provided limit +/-4.0f.
2. Initialize an `Angle(0.0f)` and traverse all 60 genuine two-float
   vertices in a separately scoped loop; write polar coordinates from the
   current radius and advance by 2*pi/59.
3. Copy actual vertex 0 into vertex 59 to close the original shape.

The necessary single NOP after Angle construction at physical `+0x115`
is emitted **naturally** by a real block lifetime for the vertex loop.
The initially tested unscoped natural source generated 537B/148 instructions
and was rejected. A real lexical scope changed it to the exact 538B/149
while preserving the natural parameter/array semantics; no explicit assembly,
fake return, synthetic local, byte padding, or exactness-specific conditional
is present.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` and the original-target-bound canonical
relocation-aware oracle independently certify:

```text
PASS complete original 538B/149 i386, 13 E8 +10 HIGHLOW, authentic +0x115 NOP
animation_ribbon_segment_dynamics_538: exact (538/538 bytes)
Exact replay: 1/1 units, 1 cold objects
```

This credits **one new original authored game function /538 whole native
`.text` bytes**. With the earlier 140B group update, 156B group draw,
76B LINESTRIP segment renderer, and 19B array ends, this closes the
previously unfinished ribbon update/draw/segment dynamics pipeline at
function level. The distinct allocator/constructor/destructor and whole
program are still not proven linked, playable, or exact.

### Affected-only reproduction

```bash
scripts/repo-python scripts/verify-animation-ribbon-dynamics538-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSegmentDynamics538.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

Only the new 538B source/provider is a changed compiler input; the
accepted 140B/156B/76B/19B providers and their receipts remain unchanged.
