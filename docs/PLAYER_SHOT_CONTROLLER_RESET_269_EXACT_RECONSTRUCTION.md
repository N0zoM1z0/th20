# CORE/EXACT-398 — entire 269-byte PlayerShotController reset boss and 32-byte Timer wrapper

Immutable comparison original: user-approved Japanese TH20 v1.00a
Steamless executable, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Two physically distinct complete native game functions are now
**strictly exact**, both maintained as genuine C++20 in
`src/PlayerShotReset.cpp`, with real typed `PlayerShotController`,
`PlayerShot`, `IntrusiveList`, `IntrusiveIterator`, `Timer` and
`std::array` fields. The original 966-byte exact
`Player::reset_initial_state` at `0x004FB450` directly calls this
269-byte PlayerShotController reset, independently confirming its
true game-owned source and receiver ABI.

| Complete original game method | Physical original address | Native body | Original x86 instructions | Original E8 / PE HIGHLOW |
| --- | --- | ---: | ---: | ---: |
| `PlayerShotController::reset_all` | `0x00504950` | **269B** | **82** | **14 / 2** |
| `PlayerShotController::reset_timer_12400(int)` | `0x00506CD0` | **32B** | **13** | **1 / 0** |

These original native ranges total **301 newly accepted, nonoverlapping
game-authored exact bytes**. Their respective entire original SHA-256
values are
`33796b5a91ccfd593b8624eb666baf1549f456d5c4304b4ee47397e076cc15d4`
and
`bab22540cc70f7ea6954f77dcae9171915835b7920db9456b4e8f132d93ea79c`.

## Complete 269-byte gameplay lifetime state machine

The original receiver is `PlayerShotController`, with an actual
256-entry `PlayerShotPool` and its real intrusive active list
at offset `+0x12430`. It constructs a genuine 8-byte
`IntrusiveIterator<PlayerShot>` (including the native compiler
auto-initializer and actual list `begin`/`end` methods),
iterates until `differs(end)` becomes false, calls the real
`IntrusiveLink::node_access` on each entry, and invokes the
native `PlayerShot::retire` at `0x00506AF0`.

**The iterator's scope is significant.** The original's full
exception-aware iterator destructor runs at `+0xA4`,
*before* any Timer is changed. The maintained source therefore
puts the actual list iterator and its whole loop inside an
ordinary consumed C++ block, allowing genuine destructor,
exception-handler and stack security logic to be emitted
without artificial methods or fake branches.

After complete iterator retirement, the original resets the
three distinct 16-byte Timer objects at
`+0x12400`, `+0x12410` and `+0x12420` to **-1**, **-1**
and **0** respectively, using the real 32-byte wrapper for the
first and native `Timer::operator=(int)` twice for the others.
It then invokes actual
`std::array<uint32_t,30>::fill(0)` for the first counter array
at `+0x12468`, not an invented raw memset or a thirty-iteration
loop. The second 30-entry counter array at `+0x124E0`
remains untouched by this native method.

The real `PlayerStorage.hpp` class declaration now represents
both count arrays as `std::array<uint32_t,30>`, preserving
all independently established object offsets and the complete
`sizeof(PlayerShotController)==0x12598`. The separately observed
STL `std::array::fill` helper at `0x00506080` is a **different
physical native function** and receives no extra game-authored
credit here.

The original 32-byte wrapper, implemented as a real member of
`PlayerShotController`, simply writes
`timer_12400 = value` via the actual native Timer assignment.
The separate original 166-byte `PlayerShot::retire` at
`0x00506AF0` is **not yet a strict exact function**:
its declaration is a real typed call requirement, not a claim
that its full body is reconstructed.

## Independent native x86, PE references and exception handling

Both original functions were freshly decoded at their complete
physical boundaries from the immutable PE. All native direct
E8 operands and independent PE `.reloc` HIGHLOW fields were
collected *before* the new matching manifests were accepted,
and compared at the complete original byte offsets against
fresh MSVC 19.44 i386 compiler COFF relocations.

The 269B original has exactly **16** external reference fields:
**14 E8/REL32 and 2 HIGHLOW/DIR32**. Independently observed
native anchors include:

| Original displacement | Type | Original target | Role |
| --- | --- | --- | --- |
| `+0x06` | DIR32 | `0x0056863D` | original exception handler |
| `+0x15` | DIR32 | `0x005B25C0` | compiler security cookie |
| `+0x3C` | REL32 | `0x0040C080` | true iterator auto-initialization |
| `+0x48` | REL32 | `0x00412280` | real intrusive list begin |
| `+0x57` | REL32 | `0x00412540` | real intrusive list end |
| `+0x64` | REL32 | `0x00411C30` | real iterator advance |
| `+0x71` | REL32 | `0x00411BB0` | real iterator comparison |
| `+0x80` | REL32 | `0x0040C300` | iterator current link |
| `+0x8B` | REL32 | `0x0040F160` | link's PlayerShot receiver |
| `+0x92` | REL32 | `0x00506AF0` | actual shot retirement |
| `+0xA4` | REL32 | `0x00411B00` | iterator destructor |
| `+0xAF` | REL32 | `0x00506CD0` | whole exact Timer wrapper |
| `+0xBF` / `+0xCF` | REL32 | `0x00423520` | actual Timer assignment |
| `+0xEF` | REL32 | `0x00506080` | 30-entry std::array fill |
| `+0x105` | REL32 | `0x005429EE` | compiler cookie check |

The 32B wrapper has its one independently original native
E8/REL32 field `+0x15` to `0x00423520`. All **17/17
native reference field offsets, types, and original target
addresses** match the new canonical COFF objects, with no
fabricated address symbol or inferred relocation target.
The complete original audit is preserved privately in
`.analysis/core398-original-player-shot-reset-refs.json`.

Pinned profile: MSVC 19.44.35211 i386
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc`, with the original
exception handling and stack cookie on the 269B function.
The ordinary typeful C++ emits **269/269 + 32/32 strictly
exact original bytes**, 82+13 complete native instructions,
including the exact 17 original reference destinations. No
artificial locals, padding, hand-written assembly or shortened
function-prefix comparison is used.

## Exact impacted-source-only cold replay

The two real functions are in **one new canonical object**
`build/core398-canonical/PlayerShotReset.obj` with its fresh
locked compiler receipt and **two new exact units**. The sole
public declaration/header change is `src/PlayerStorage.hpp`,
which adds genuine member methods, corrects the arrays to
actual `std::array` and preserves the original live layout.

**Before editing**, the previous compiler receipts for that
header were independently collected: exactly **25 older source
providers, 74 strict native units**. The two new whole-method
units add one real source provider, yielding **76/76 strict
units across 26 freshly rebuilt source objects**, in six
serialized low-priority batches of **5+33+8+10+16+4**.
Both the complete 966-byte `Player::reset_initial_state`
and the separate 1,518-byte `Player::rebuild_option_animations`
passed complete strict native comparison after this header change.
No unfiltered whole-repository cold replay was run.

One MSVC compiler-private `$SG` counter in the existing Player
constructor renumbered from `$SG82145` to `$SG82230`. Before
reacceptance the original PE string destination remained exactly
`0x00572BB8`, with identical original relocation offset/type
and complete non-relocation bytes. Only the compiler-private
symbol identity was reconciled in its matching manifest, and
the unchanged strict comparator then passed the entire
Player constructor again.

Private proof: `.analysis/core398-shot-reset-preedit-scope.json`,
`.analysis/core398-shot-reset-replay-groups.json`,
`.analysis/core398-shot-reset-replay-batch0.log` through
`batch5.log`, and
`.analysis/core398-reconciled-private-symbols.json`.
No other native original game-owned function or linked
whole executable is claimed exact by the new source.
