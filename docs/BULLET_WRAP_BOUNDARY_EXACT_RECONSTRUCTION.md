# CORE/EXACT-243 — two complete Bullet wrap boundary checks and full 781B frontier

Original target: locked Japanese TH20 v1.00a Steamless PE SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Both complete native function bodies have independent native Ghidra and
Capstone evidence and are now maintained as ordinary C++20 in
`src/BulletWrapBounds.cpp`, with a separate narrow typed
`src/BulletWrapBounds.hpp` contract. Names remain inferred, and exact native
code does not establish full executable linkage.

| Entire original function | Entry | Native bytes | Native relocations | Strict result |
| --- | --- | ---: | ---: | ---: |
| `th20::bullet_wrap_outside` | `0x004854D0` | 176 | 9 | **176/176** |
| `th20::bullet_wrap_outside_with_floor` | `0x00485580` | 181 | 10 | **181/181** |

These two original 41-instruction functions test XY playfield exclusion
using the supplied `Vector3` position and two supplied full dimensions,
comparing against independently verified floating constants at the exact
original data addresses. The native left X boundary is **-384.0f / 2.0f**
(`0x0056FD6C`), the right X boundary is **384.0f / 2.0f**
(`0x0056CDA4`), Y upper is **448.0f** (`0x0056D7C0`), with common
**2.0f** at `0x0056C8D0`. The 176B function's lower Y boundary is literal
**0.0f**, using native `xorps`, whereas the distinct 181B function uses
original **-64.0f** at `0x0056FD68`. This original extra `DIR32`
relocation is real, not an invented semantic alias. Code maintains
original SSE comparison order and unordered/NaN flags, native full-EAX
integer return and the original common 0/1 return block.

The first natural diagnostic trial matched 134/140 non-relocation bytes
because its positive `if (outside)` form reversed the original final
branches and the two return-local stores. An equivalent natural original
`if (!(outside predicates)) value = 0; else value = 1;` recovers all
**140/140** non-relocation bytes in 176B and all **141/141** comparable
bytes in 181B. Locked MSVC 19.44 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` strict canonical replay confirms the two complete
functions **176/176 and 181/181**, with all **19 original independent
relocation offsets/types/data destinations**. Native intervals SHA-256:
`0x004854D0` `1cc6c8be12ca7fd9337c1234674cb6ad0f53139b4b05cbc1e630943a94cb5415`,
`0x00485580` `126f8fefd4314dc59401527bf4d3177d7a137ea7bc1b50dcd0ee4092b23e62ce`.
Focused proof: `.analysis/core243-wrap-bounds-exact-replay.log`.

## Whole 781-byte caller remains open — do not count a partial match

These helpers are actual dependencies of the original **781-byte** Bullet
wrap/teleport boss at `0x00483270`. Independently reading the complete
original **202-instruction** native function confirms this parent queries
Animation SpriteData extents at +0x48/+0x4C through native `0x00437CD0`,
uses the genuine Bullet `commands.at(6)` command flags to select four
playfield-edge position mirrors, increments `word_30`, optionally requests
its original sound effect, and clears original bit `0x1000` in the Bullet
command flags when its signed count threshold is reached. The parent full
native SHA-256 is
`55aad8459ac15ab485f06119d89dabe73e093c0c7ebc334ba7a45c548ed90f96`.

A **complete**, private natural C++20 781B source hypothesis was compiled
using the real typed `Bullet` and actual `SpriteData::extent_48/extent_4c`
owner, an **explicitly temporary** Animation method declaration, and
actual full incoming gameplay semantics. It emitted **759B / 197 instructions**
whose instruction mnemonics align with **197/202** original instructions.
The missing five original unconditional branches at native offsets `0xDE`,
`0x154`, `0x1D7`, `0x25E`, `0x260` are compiler control-flow differences
inside the 4-way edge dispatch, *not* independent original leaf functions.
Further natural `else` nesting, label and single-cycle `do` trials emitted
747, 759 and 771 bytes but no full match. Production `Animation.hpp`
was intentionally **not** modified or credited based on an unproven
private SpriteData retrieval method. Original 781B boss is therefore
**nonexact**, receives no native byte credit and remains a priority target.
Complete original native/working hypotheses are retained privately under
`.analysis/core243-native-00483270.asm` and
`.analysis/core243-BulletWrapBoss.cpp` / `.analysis/core243-wrap-*.cpp`.

The complete **3,735B** Bullet emitter `0x004818E0`, **662B** Bullet
cancellation body `0x0047C8F0`, **273B** single-group Bullet drawer and
**41,967B** Enemy ECL opcode root likewise remain nonexact. These two
new real standalone wrappers require only **one changed MSVC object /
two strict units**, no shared-header regressions and **no full cold replay**.

## CORE/EXACT-248 follow-on: original complete 781B parent now exact

The preceding "nonexact parent" statement records the state at
CORE/EXACT-243, **not the current reconstruction status**. A later
independent complete 781B C++20 probe was discovered and reconciled with
real `Animation::sprite_data`, `AnimationFile::sprite`, and the original
animation manager file identity method. The maintained entire
`Bullet::wrap_screen` at `0x00483270` now replays **781/781 native bytes**,
including all 25 original relocations and 202 original instructions.
The three actual SpriteData dependency methods (29/23/45B) are also
separately complete exact native units. All **315 prior shared-header
include-affected units** remain strict exact; **319/319 new plus old**
replay across **63 cold objects**, with no whole-graph replay.
See [full original screen-wrap boss and SpriteData owner exact proof](BULLET_WRAP_BOSS_EXACT_RECONSTRUCTION.md).
