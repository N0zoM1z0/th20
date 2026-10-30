# CORE/RECON-854 — complete 78B original game shape XY transform strict exact

The selected locked Japanese TH20 v1.00a Steamless executable, original
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
contains a native **78B /20-i386** game-owned 2D shape coordinate helper at
physical original head `0x00445AD0`. It has a real cdecl `ret`, with seven
actual stack arguments: `Vector2& output`, x, y, sine, cosine, offset-x,
offset-y. Unlike the nearby original whole 86B `thiscall` projected-XY
helper at `0x00445B20`, it has **no ECX receiver** and neither the
same source symbol nor the same native body.

The natural maintained [`src/AnimationShapeXY78.cpp`](../src/AnimationShapeXY78.cpp)
performs precisely:

```cpp
output.x = x * cosine - y * sine + tx;
output.y = x * sine + y * cosine + ty;
```

It emits **78/78 identical original bytes, with all 20 real i386
instruction heads**, including actual native SSE multiply/subtract/add
order and the two real `Vector2` float stores at output offsets 0 and 4.
There are **zero original native E8 and zero original PE HIGHLOW fields**,
so whole canonical byte matching is direct with no patchable relocation
fields. This is a complete game-authored function, not a prefix or
compiler/library thunk.

## Independently authenticated original game callers

The [locked PE-only native verifier](../scripts/verify-animation-shape-xy78-native.py)
independently disassembles the complete 78B body and reads the real
original PE relocation directory, then checks that **eleven physically
real original E8** incoming calls target exactly `0x00445AD0`:

| Actual game-owned original parent | Complete original length | Native E8 call offsets |
| --- | ---: | --- |
| Rectangle shape Boss `0x00439A00` | 1,980B | `+0x377`, `+0x3DE`, `+0x442`, `+0x4A9` |
| Triangle-fan shape Boss `0x0043B0E0` | 2,169B | `+0x377`, `+0x3DE`, `+0x443`, `+0x4A9` |
| Three-vertex shape Boss `0x0043E2C0` | 1,601B | `+0x2FA`, `+0x361`, `+0x3C5` |

These original parents create game-specific vertex coordinates from
angles, anchored dimensions and Animation renderer offsets. This
independently establishes actual authored game-geometry ownership,
not an automatic runtime helper classification. The historical original
C++ function name remains unknown; `animation_shape_xy` is a local
semantic spelling.

## Whole pinned native acceptance and bounded replay

One new `animation_shape_xy_78` canonical unit in
[`config/match-units.toml`](../config/match-units.toml) compiles only this
source into `build/core854-canonical/AnimationShapeXY78.obj` under the
standard pinned x86 MSVC C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`. Its relocation list is correctly empty.
The fresh build receipt and whole canonical replay produce:

```text
animation_shape_xy_78: exact (78/78 bytes)
Exact replay: 1/1 units, 1 cold objects
```

This adds **one unique original game-owned whole exact 78B function**,
not credit for its 1,980B/2,169B/1,601B parent bodies. The other three
large geometry parents remain **NONEXACT** until independently verified
whole code-body/relocation strict replays. This new C++ file has no
shared exact header dependencies, so **previously accepted canonical
replay scope is zero**, and no full-graph cold replay was performed.

| Current original-game credit | Before | After |
| --- | ---: | ---: |
| Distinct game-owned whole-native exact functions | 607 | **608** |
| Distinct original native `.text` code bytes | 213,061 | **213,139** |
| Source-present mappings | 1,253 | **1,254** |
| Strict canonical units | 1,254 | **1,255** |
| Accepted exact objects/receipts | 272 | **273** |

The enclosing 5,993B Animation Draw dispatcher and three calling
shape Bosses are not claimed exact by this isolated helper result.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-shape-xy78-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeXY78.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
