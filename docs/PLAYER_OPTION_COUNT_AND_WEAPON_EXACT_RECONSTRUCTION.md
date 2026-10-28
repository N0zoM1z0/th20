# CORE/EXACT-322 — PlayerRecord option-count roots and WeaponStone virtual forwarding

The immutable comparison target is the user-approved Japanese TH20 v1.00a
Steamless original, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint accepts **six distinct complete original game-owned bodies**
(**334 newly credited native bytes**), including the genuine signed option
count calculation, three different field clamps and the two real WeaponStone
virtual offset dispatchers. Five are newly source-present; the sixth is an
**already canonical, existing 64-byte implementation** whose authored origin
was independently established by this gameplay call chain. It is *not* a
second duplicate member body or a fake alias for the same original address.

| Whole original | Native entry | Bytes | Complete original interval SHA-256 |
| --- | --- | ---: | --- |
| `PlayerRecord::clamped_option_units` | `0x004993B0` | **64** | `00c47e36a0d7084fa4226adb2c35241736a2268046975b9acd807a25224373fd` |
| `PlayerRecord::clamped_option_cap` | `0x004B8210` | **64** | `54c24af1aefcccc13d24d72b925efa65ad4ec32f1009b20a2c2d1326ff84004a` |
| `PlayerRecord::starting_power` (existing, promoted) | `0x004B81D0` | **64** | `ba0c23375549ac6aa26e93784412e4ffe2a522ad114649d19adee5187a935257` |
| `PlayerRecord::available_option_count` | `0x004B81A0` | **38** | `126efe708c42d382a22adcad91a37e10b3138851d12f21431f2ee2529033393d` |
| `WeaponStoneInfo::focused_offset` | `0x004FF630` | **52** | `5c8c162823bd46cabf78125187c588e29e71522136fe7f4efcccfe619948a305` |
| `WeaponStoneInfo::unfocused_offset` | `0x004FF760` | **52** | `7cba0840865fe0df4717c77eae5dffdbdf5bd7b023e087df2ef344bad8d9e94a` |

## Complete native gameplay model

The entire original 38-byte option-count method invokes the independently
observed native 64-byte `field_30` clamp (`0..400`), then the *already
maintained* `PlayerRecord::starting_power()` at `0x004B81D0`, which clamps
the true `field_38` to `100..400`. The original signed `idiv` divides the
two observed values, preserving x86 truncation and denominator guarantees.
Native `PlayerRecord::clamped_option_cap` at `0x004B8210` separately clamps
`field_34` with **both bounds equal to 400**, storing the result. The
clamped fields and return values are not guessed from historical names:
all source expressions use actual `PlayerRecord` members and independently
attested native `std::clamp<int>` callee entry `0x00471170`.

The independent whole-function direct-call relocations are:

| Original body | Native field offsets | Original targets |
| --- | --- | --- |
| `clamped_option_units` | `+0x27` | `0x00471170`, `std::clamp<int>` |
| `clamped_option_cap` | `+0x27` | `0x00471170`, `std::clamp<int>` |
| `starting_power` | `+0x27` | `0x00471170`, `std::clamp<int>` |
| `available_option_count` | `+0x0C`, `+0x16` | `0x004993B0`, `0x004B81D0` |

The separate **52-byte** `WeaponStoneInfo` methods at `0x004FF630` and
`0x004FF760` forward their two integer option parameters through genuine
`Weapon*` members at **`WeaponStoneInfo+0x2C` / `+0x30`** and real
`Weapon` virtual table slots **`+0x14` / `+0x18`** respectively. They
preserve receiver evaluation, original argument order and the `Vector2*`
return in `EAX`. Both methods compile whole-byte exact through the actual
`Weapon` virtual interface in `src/Weapon.hpp`: no invented vtable copy,
unnamed raw callback offset or shortened function prefix. The inferred
method labels are kept distinct from the proven binary behavior.

## Correct handling of existing source and origin

The initial analysis discovered that `0x004B81D0` **already** had the
exact, 64-byte `PlayerRecord::starting_power()` body in `src/PlayerRecord.cpp`
and a strict canonical `player_record_starting_power` unit. Its origin ledger
still said `review` and its inventory status said `reconstructed` despite
100% canonical codegen. This checkpoint explicitly **reused that method**
as the original denominator callee, rejected a duplicate newly proposed
`clamped_option_divisor` identity, cold rebuilt the original physical unit
using its own locked profile, and promoted the existing game-authored
function to matching only after the original caller established the real
side-effect/return protocol. No second 64-byte body or overlapping match
row was admitted. The five new bodies live in
`src/PlayerRecordOptionCounts.cpp` and `src/WeaponStoneOptionOffsets.cpp`.

## Strict actual-input replay, no full cold replay

All six complete native bodies pass the locked MSVC 19.44.35211 i386
full-function canonical comparator. New units use `/std:c++20 /Od /Ob0
/GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`; the existing 64-byte
`starting_power()` retains its original separately validated `/GS-`
profile and source owner. Every original relocation type, offset and
independently grounded target is preserved.

Adding genuine methods to `src/PlayerRecord.hpp` and
`src/WeaponStoneInfo.hpp` affects exactly **31 existing canonical source
providers / 262 old strict units** by the *actual previous receipt include
closures*. The two new providers add five units. **267/267 strict whole
units across 33 freshly rebuilt canonical source objects** passed in seven
serialized, reduced-priority batches of **30+30+31+47+83+12+34** units.
This covers previously accepted 966-byte Player reset, 2,018-byte Bullet
collision and other large intact source objects; no unfiltered whole-graph
cold replay ran.

Fifteen MSVC compiler-private `$SG` numeric labels in fourteen previously
exact units changed because of newly declared members. Their original
relocation offsets/types and native string destinations were independently
unchanged. The private reconciler required a fresh receipt, identical
non-relocation bytes and an independently validated relocation target,
then updated only the local symbol identity; every affected unit passed the
unmodified strict comparator again. Full provenance is in ignored
`.analysis/core322-reconciled-private-symbols.json`, source selection in
`.analysis/core322-receipt-impact.json` and
`.analysis/core322-replay-groups.json`, and exact logs in
`.analysis/core322-replay-batch{0..6}.log`.

These now exact methods are **real dependencies** of the separate
**1,518-byte `Player::rebuild_option_animations` at `0x004FACA0`**, which
remains an independently open large gameplay root. Neither virtual
forwarders nor clamps establish that original parent's complete exactness,
resource ownership or whole-executable linkage/runtime completion.

## Later CORE/EXACT-326 update

The two complete WeaponStone option script selection/option pair initializers
at `0x00534130` (77B) and `0x00533180` (90B) are separately strict exact,
with explicit focused/unfocused virtual table slots and 39/39 affected-only
strict units. Read [the complete two-dispatch proof](WEAPON_STONE_OPTION_DISPATCH_EXACT_RECONSTRUCTION.md).
The entire 1,518-byte Player option rebuild root remains nonexact.
