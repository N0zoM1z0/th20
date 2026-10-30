# CORE/RECON-880 — entire original 1,204B polygon outline TRIANGLESTRIP Boss native strict exact

The locked Japanese TH20 v1.00a Steamless original PE has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
A real, originally SOURCE-ABSENT large game renderer at
**`0x0043D370`** is now implemented by one natural C++ source method:
[`src/AnimationPolygonOutline1204.cpp`](../src/AnimationPolygonOutline1204.cpp).
The **complete 1,204B /354 actual native i386 instructions** compile
under pinned MSVC 19.44.35211 x86 C++20 into a **whole 1,204/1,204B
strict canonical zero-difference original match**. This is a genuine
complete polygon/line-stroke Boss, not a partial block or an assembly
trampoline. Its original receiver is an Animation renderer in ECX,
with six true stack arguments and native `sub esp,0xA8`/`ret 0x18`.

| Entire original-native property | Independently accepted result |
| --- | --- |
| Original full code | **1,204/1,204B strict** |
| Actual x86 instruction heads | **354/354** |
| Original physical E8 call site/target pairs | **20/20** |
| Actual PE HIGHLOW absolute data field site/target pairs | **8/8** |
| Original nonrelocation bytes | **1,092/1,092 identical** |
| Stack frame and return ABI | **`0xA8` and `ret 0x18`** |
| Original D3D9 primitive | `D3DPT_TRIANGLESTRIP=5` |

## Source-independent PE proof, actual callers and math leaves

[`scripts/verify-animation-polygon-outline1204-native.py`](../scripts/verify-animation-polygon-outline1204-native.py)
reads the locked original PE `.text` and **actual PE `.reloc`** before
using candidate object bytes. It disassembles the complete function
through the real return, asserts all **20 actual E8 offsets and original
callee heads**, and all **eight original HIGHLOW physical field offsets
and native absolute target values**. Its callee inventory includes:

| Original actual direct E8 role | Number |
| --- | ---: |
| `AnimationPoolOwner::flush_draws`, original `0x004455C0` | 1 |
| Two genuine `Vector2::Vector2` default constructors `0x004398A0` | 2 |
| `Vector2::operator-` original `0x00429520` | 7 |
| **77B by-value `Vector2::operator+=` original `0x00439960`** | 3 |
| `rotate_xy<Vector2>` actual game `0x00458FA0` | 1 |
| Original 155B `normalize_vector2` `0x0043E910` | 1 |
| **72B by-value `Vector2::operator*=` original `0x00439910`** | 1 |
| Renderer color mode `0x00446690` | 1 |
| Graphics device get `0x00412730` | 2 |
| Actual compiler security-cookie checker `0x005429EE` | 1 |

The genuine eight PE HIGHLOW fields are one cookie
`0x005B25C0`, two actual 2.0f at `0x0056C8D0`, one negative pi
`0x0056E0F8`, two 1.0f `0x0056C8CC`, and two Graphics owner globals
`0x005C4D40`. The original independently authenticates a game
**104B caller** at `0x0045FAA0` with an actual direct E8 at
`0x0045FAFB` into the 1,204B polygon Boss. That original caller now has a
[complete but still NONEXACT semantic source](ANIMATION_POLYGON_MOTION_CALLERS_76_104_FRONTIER.md);
it is not credited as native exact.

The genuine 72B and 77B original compound value-return operators were
first recovered independently as
[CORE/RECON-879](ANIMATION_VECTOR2_COMPOUND_VALUE_72_77_STRICT_EXACT.md).
They mutate `Vector2` in place **but return the eight-byte value, not a
reference**, preserving the required original hidden-result-pointer
thiscall stack protocol. Using the conventional reference-returning
compound signature would change native calls and the parent body.
Neither 72B nor 77B child code is counted in this new 1,204B physical
body credit.

## Authentic first/interior/last segment geometry and unusual buffer state

The native renderer uses the *existing* receiver-owned **65,536×20B**
`SpriteColoredVertex` array and actual mutable buffer cursor. It
first guards the native `count+1` boundary (unsigned `JB`) and
requires at least two points. It then flushes pending draws,
constructs two real `Vector2` source locals, and modifies the
**original mutable thickness parameter** by dividing by genuine
2.0f. For every input point, it chooses the original incoming/outgoing
edge direction using real `Vector2::operator-` calls:

- At the first point, direction uses `points[1]-points[0]` and, if
  the `closed` byte is set, adds `points[0]-points[count-1]`.
- At the last point, direction uses the previous edge and, for a
  closed polygon, is replaced by the first edge plus closing edge.
- At interior points, it adds the incoming and outgoing edge vectors.

It rotates the resulting direction by the genuine **`-pi/2`** source
constant, invokes the already exact `normalize_vector2` and scales the
result with the newly exact **by-value compound multiply**. It writes
two real 20B vertices per input point, on the positive and negative
sides of the original path, with the actual world and renderer XY
offsets, Z=0, reciprocal-W=1 and the original advancing packed-color
stream. It submits D3D9 FVF `0x44`, color mode2 and
`DrawPrimitiveUP(TRIANGLESTRIP,2*count-2,vertices,20)`.

**The original buffer state contains a subtle but authentic anomaly:**
it reserves only **`count+1`** vertices, writes **`2*count`**
20B records, and advances the *persistent* renderer cursor by only
**`count*20` bytes** after submission, even though the local pointer
advances by `2*count*20` during vertex emission. This is directly
established by original `count+1` guard at `+0x16..0x3C`, the
`2*count-2` primitive calculation at `+0x469`, and the actual
`IMUL edx,[ebp+8],0x14` persistent advance at `+0x477`.
The source **preserves the original behavior exactly**; it does not
silently change the guard to `2*count` or advance the persistent
cursor by twice as many records.

## Meaningful source fixes that restored exactly 1,204B

The first C++ source used a separate cached renderer alias and a
separate `SpriteColoredVertex* second` cursor for the second side of
each point. This was semantically close but compiled to
**1,213B/356 x86** with an unwanted `0xB0` frame and E8 fields shifted
6–9 bytes. Removing the *redundant* receiver alias (the real method
already keeps `this`) produced **1,207B/354 x86**, but still had an
extra 4B stack slot. The final semantic change advanced **the one
real used local vertex cursor** after the first point and again after
the second, rather than allocating a separate `second` pointer.
This reproduces the real pointer mutation at native
`+0x348..0x34E` and `+0x3EA..0x3F0`. It eliminates the unneeded
local, restores the genuine `0xA8` frame and prevents an original
3-byte `LEA` at `+0x1BB` from becoming a six-byte long-disp address.

The final ordinary C++ emits **all 354 original instruction heads in
the original order, with all 20 E8 and eight PE HIGHLOW fields in
exactly their original positions**. The result is not achieved by
original-binary patching, manual assembly, NOP padding, inert local
variables or shortening the full native code extent.

## Strict canonical object, bounded regression and precise original credit

One new canonical unit, `animation_polygon_outline_1204`, in
[`config/match-units.toml`](../config/match-units.toml) owns a fresh
pinned i386 MSVC source object/receipt
`build/core880-canonical/AnimationPolygonOutline1204.obj` with true
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` compilation. It has **20 original native E8/REL32 +8
native PE HIGHLOW/DIR32** explicitly attested symbol/offset/type/target
roles. The complete replay and independent comparator report:

```text
animation_polygon_outline_1204: exact (1204/1204 bytes)
Exact replay: 1/1 units, 1 cold objects

animation_polygon_outline_1204: exact (1204/1204 bytes)
```

The new method declaration extends the shared
`AnimationDrawDetailedOwner.hpp`, so previously accepted exact
sources in the affected header include closure are recompiled and
strictly replayed individually. The separate **5,993B Animation Draw
parent remains NONEXACT** and gets only its focused role/switch
regression. The real 104B caller has a separate source-present NONEXACT
semantic reconstruction and does not earn exact credit. No unfiltered full-graph cold replay is run.

This credits **one unique whole original authored game function and
1,204 real `.text` bytes**, not the existing exact math/Graphics/
Vector2 children or its enclosing call graph. Live tracked coverage
becomes **631 game whole-native exact methods /232,890 original native
bytes**, **1,278 source-present mappings /1,278 strict canonical units /
295 accepted compiler source-object/receipt providers**.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-outline1204-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonOutline1204.cpp
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_outline_1204
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
