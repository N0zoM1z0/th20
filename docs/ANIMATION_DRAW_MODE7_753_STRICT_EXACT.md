# CORE/RECON-839 — complete original 753B Animation mode7 projection/fog renderer strict exact

The locked Japanese TH20 v1.00a Steamless original executable (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
contains an entire game-owned `0x00441C00` draw mode7 method. The original
5,993-byte Animation Draw Boss calls this physical target at its main
mode7 E8 instruction `0x00443A5A`. The original mode7 parent itself is
**753B /178 native x86 instructions**, with `sub esp,0x6C` and a genuine
`ret 4` for its one Animation* argument.

The full method is now recreated as natural typed C++
[`src/AnimationDrawMode7.cpp`](../src/AnimationDrawMode7.cpp), not a
prefix, isolated handwritten machine-code fragment, fabricated trampoline,
manual table or dummy codegen padding. The pinned-MSVC x86 compilation
produces **753B/178 genuine x86, full native `0x6C` frame** with all
seven original native E8 calls and all 29 independently attested
original PE HIGHLOW fields at their **exact physical instruction/field
offsets**. Every genuine byte after independently established relocation
replay passes **753/753 strict canonical exact**. This adds one real
original game-authored exact function, **753 original `.text` bytes**.

The 5,993-byte whole Animation Draw Boss at `0x00443880` stays
**SOURCE-PRESENT, NONEXACT**: a strict child never makes its parent
exact. Its whole current source-generated 5,993B/1,501 x86 and switch
positions remain separately
[evidenced](ANIMATION_DRAW_BOSS_5993_NATIVE_LENGTH_AND_STACK_FRONTIER.md).

## Independent original PE whole-function census

The new [original-only mode7 verifier](../scripts/verify-animation-draw-mode7-native.py)
extracts the immutable original PE `.text` body, independently decodes
all 178 physical instruction heads and reads the original `.reloc`
HIGHLOW section. Neither original call destinations nor the 29 data
values are guessed by solving candidate relocation fields.

| Whole original native location | Real physical source role |
| --- | --- |
| E8 `+0x1A` -> `0x00441430` | Original renderer setup/geometry mode7 method (1,996B), still independently NONEXACT |
| E8 `+0x2C` -> `0x0040BC20` | Genuine `_eh vector constructor iterator` for four 16B zero-valued points, compiler/library—not game credit |
| E8 `+0x34` -> `0x00422E10` | Genuine `Vector3` 12B zero constructor, preexisting strict source |
| E8 `+0xCF` -> `0x00540672` | Real D3DX9 `D3DXVec3Transform` import thunk, not authored game bytes |
| E8 `+0x12A` -> `0x00445700` | Entire 25B `animation_depth` game method, strict exact in CORE/RECON-838 |
| E8 `+0x277` -> `0x0043F6A0` | Original whole 3,159B strict exact Animation quad-submit Boss |
| E8 `+0x2E6` -> `0x005429EE` | Real compiler security-cookie check |

All **29 physical PE HIGHLOW fields** are independently verified at
precise original offsets: **11 live Graphics viewport pointer fields**
(`0x005C5840`, true `Graphics+0xB00`), **five original `1.0f`
constants** (`0x0056C8CC`), **11 shared four-vertex packed color/alpha
and reciprocal-W fields** (`0x005AEF10` plus original offsets), **one
real security cookie** (`0x005B25C0`), and **one pointer to the original
four-float zero constructor** (`0x004398D0`). There are no omitted
original switch tables or after-RET data in this function.

The physical four-float constructor `0x004398D0` is already maintained
elsewhere as `EnemyBounds::EnemyBounds()`, with a true 16B, four-zero
float layout and full native body. The original historical type name is
**not independently known**. Its use here is as the *same original
16-byte zero-constructed value object* passed to the native D3DX
four-coordinate transformation. No new storage, duplicate original
constructor, fake ABI or additional authored exact credit is created
for that existing provisional constructor symbol.

## Native game behavior and source corrections

1. Original mode7 first invokes the real renderer setup, constructs four
   16B transformed points and one 12B relative-position Vector3, then
   reads original near and far fog distances. Each of four iterations
   transforms one true **20B-stride** renderer corner from receiver
   `+0x6000E20` through its 64B D3DX matrix at `+0x60007D8`, using the
   original imported `D3DXVec3Transform`. The resulting XYZ is made
   relative to the original live viewport origin, and the source calls
   the newly strict 25B depth helper to obtain Euclidean distance.
2. Original fog uses the live `ViewportState::fog` at `+0x150`: near,
   far, RGB float channels and packed fog color are separate original
   fields. The code stores either the chosen original animation packed
   color, the fog packed RGB with original alpha, or separately computed
   B/G/R interpolated bytes preserving that alpha. It selects original
   color490 or color494 via the native Animation flags bitfield.
3. The original first distance guard is `COMISS` with `JBE` and the
   second threshold uses `COMISS` with `JB`. Changing the initial C++
   from a forward written near-color branch to the genuine
   **distance-above-fog-first branch** restored the native x86 branch
   layout and **the original NaN/unordered behavior**.
4. The same real float local holds original distance and later the
   normalized fog ratio. Treating them as two separately live C++
   temporaries added an extra four-byte stack slot absent from the
   original. Real source variable reuse recovers native `0x6C` frame.
5. The three source color-channel operations must narrow the integer
   conversion to an actual **8-bit byte before subtraction**. Original
   `CVTTSS2SI` is followed by **`MOVZX` from the low 8-bit register**
   in all B/G/R paths. Merely casting the final 32-bit subtraction
   caused MSVC to omit those three real low-byte conversions, producing
   an incorrect code shape. The maintained C++ now performs the native
   float-to-int-to-uint8-to-pixel operation without invented side effects.
6. The function submits the resulting four shared 28B vertices through
   the already exact `render_quad(animation,2)` method, then restores
   reciprocal W=1.0f on vertices in the native order **3,2,1,0**, and
   returns the authentic quad-submit result.

The source shares one renderer receiver interface
[`src/AnimationDrawDetailedOwner.hpp`](../src/AnimationDrawDetailedOwner.hpp)
with the maintained, still-NONEXACT 5,993B Draw Boss, rather than
inventing two independent owner classes. That interface was extracted
without changing the latter parent's code or any original E8 role:
its complete **6,316-byte pinned noncanonical COFF candidate**, including
**235 actual relocation records**, was independently byte-for-byte
compared with its prior build and was identical.

## Strict canonical acceptance and scope

The one new `animation_draw_mode7_753` canonical unit in
[`config/match-units.toml`](../config/match-units.toml) uses the native
`?draw_simple_mode7@AnimationDrawDetailedOwner@th20@@QAEHPAVAnimation@2@@Z`
method symbol, one pinned MSVC 19.44.35211 C++20 x86 source object,
and **all 36 original roles**. Its seven REL32 physical call destinations
are *explicitly* the independent PE roles listed above. The 29 DIR32
symbols are grounded by the original `Graphics`, shared quad-vertex
owner, existing native scalar `1.0f`, original four-float constructor
and security cookie, with authentic original COFF addends. All 36
COFF symbol, type, addend, original field offset, target and final
relocated byte locations are compared, rather than omitting a
nonmatching branch or taking a convenient function prefix.

```text
animation_draw_mode7_753: exact (753/753 bytes)
Exact replay: 1/1 units, 1 cold objects
```

Only new exact source is `src/AnimationDrawMode7.cpp` with its shared
new receiver declaration. The existing 5,993B source `src/AnimationDrawBoss.cpp`
was refactored to include that same declaration, but remains noncanonical.
No previously accepted exact source, public shared header, compiler
profile, target executable or old match unit was modified. Only this
**one new exact source/unit** is cold-built/replayed; the source and
binary audits for the noncanonical Draw Boss run separately. **No
full-graph cold replay.**

| Verified live game/strict graph | Before | After | Delta |
| --- | ---: | ---: | ---: |
| Original authored strict exact functions | 595 | **596** | +1 |
| Original authored game `.text` bytes | 196,817 | **197,570** | **+753** |
| Source-present mappings | 1,241 | **1,242** | +1 |
| Strict canonical units | 1,242 | **1,243** | +1 |
| Distinct canonical pinned objects/receipts | 261 | **262** | +1 |

## Reproduction

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-draw-mode7-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawMode7.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
