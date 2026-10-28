# CORE/EXACT-320 — complete Player option management and fixed-coordinate dependency chain

This checkpoint closes **six independently bounded, entire original game-owned
function contributions**, including a **165-byte complete two-array option
state broadcast**. The immutable comparison original remains the user-selected
Japanese TH20 v1.00a Steamless executable, whole-file SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
All six functions are direct native dependencies of the separately still-open
**1,518-byte `Player::rebuild_option_animations`** (`0x004FACA0`). These
natural C++20 sources are `src/PlayerOptionManagement.cpp` and
`src/PlayerFixedPoint.cpp`, with actual `Player`, `PlayerShotController`,
`PlayerValues<PlayerOption,N>`, `IntPoint`, `Vector2` and bitfield owners.

| Complete original function | Original entry | Native size | Original whole-interval SHA-256 |
| --- | --- | ---: | --- |
| `Player::active_option_count` | `0x004FF670` | **20** | `e401318a015e1c2441fa8037d47088a562599b60b7ee14d0d5bd402aecdce9ba` |
| `PlayerShotController::set_flag0` | `0x004FFD50` | **42** | `c432f54b2cd7df16ee4111918f13559279d57b706c60b779273b3e3d5cfc8df7` |
| `IntPoint::assign_scaled` | `0x004FEE50` | **63** | `d1e1400877b0f88990480323c1ed08762febb454060976fda6e4ecf2181fabd4` |
| `Player::set_option_field_fc` | `0x004FB290` | **165** | `92106cf2643103ab5ee993bc861ce2292812dc0356d65f1c1226028f7ac113e1` |
| `PlayerValues<PlayerOption,10>::end` | `0x004FCE60` | **19** | `431c07eb23bf6be0bffe443abe9d2a05ba3d5b9846d79934c9b5cd849a13f416` |
| `PlayerValues<PlayerOption,12>::end` | `0x004FCE80` | **19** | `f96e9fa0a4be5155a4153c82a943a53a880bf5313d6e1d1d3720b55c010f62f5` |

**328 exact native bytes across six physical original functions** are now
strictly accepted, without copying any original machine code or synthesizing
padding. The 10- and 12-slot `begin()` template specializations naturally
emit the exact same **14-byte physical native body** at `0x0040BDA0`, as
previously observed for 33-slot position history. Since the original has
only one such folded physical address, neither begin specialization is
credited as a new exact root: this avoids duplicate original bytes.

## Verified behavior and original native references

The 165-byte original `Player::set_option_field_fc` uses *two* real range-for
loops, one over ten 0x12C-byte `PlayerOption` values at Player+0x684 and the
other over twelve at Player+0x123C. It assigns the argument to each actual
option's +0xFC field, preserves every other member, and returns `void` after
both loops. It issues four original `REL32` calls:

| Native field offset | Original destination | Role |
| --- | --- | --- |
| `+0x18` | `0x0040BDA0` | 10-slot folded begin getter |
| `+0x23` | `0x004FCE60` | 10-slot end getter |
| `+0x63` | `0x0040BDA0` | 12-slot folded begin getter |
| `+0x6E` | `0x004FCE80` | 12-slot end getter |

These are independent original `call` displacements extracted from the
unmodified PE; the object has exactly these four ABI-matching relocations.
The original 165-byte/51-instruction body matches its natural maintained
C++ range-for implementation and all four original references. Both
`end()` methods are separately complete 19-byte bodies returning the
correct 0xBB8/0xE10 byte offsets.

`Player::active_option_count()` reads the real `Player+0x680` count.
`PlayerShotController::set_flag0` modifies only bit zero of the actual
`flags_1255c` word while preserving all other bits. Native MSVC codegen
proved the correct C++ spelling is an honest one-bit bitfield assignment:
computationally equivalent hand-written masking emitted a **different**
register/evaluation order and was rejected. The view is added as a genuine
same-storage `PlayerWordFlags` union member, not a fabricated byte overlay.

`IntPoint::assign_scaled(const Vector2&)` reads real float X and Y and
multiplies **each** by native 128.0f before independent x86
float-to-signed-int truncation. Its original two `DIR32` fields at
**`+0x12` and `+0x2B`** both point to the native constant at `0x0056CD98`.
These two real coordinates feed the complete option setup parent's actual
integer position and trail fields; no alternate fixed-coordinate packing
was invented. All six original function extents have been independently
checked against the original whole-target x86 instruction stream.

## Locked compiler and affected-only verification

The six canonical units use MSVC 19.44.35211 i386
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
All six *whole* original bodies compare **100% exact**, including the 8
independently grounded native relocation sites across the 63B/165B
functions. Existing `src/Player.hpp`, `src/PlayerStorage.hpp` and
`src/Rectangle.hpp` gained only genuine member interfaces and real bitfield
storage access, with no changes to observed sizes or offsets.

Their captured **previous build receipt include closures** identified
**24 existing exact source providers and 81 existing exact units**.
The two new providers add six units: **87/87 scoped strict units across 26
fresh locked MSVC source objects** passed in six serialized, reduced-priority
cold batches of **5 + 38 + 10 + 10 + 19 + 5** units. The separate exact
2,018B Bullet collision, 898B command3, 966B Player reset, and other
existing large roots all remain strictly exact. No unfiltered full-graph
cold replay was run.

Six *compiler-private* `$SG` identities in three older constructors were
renumbered by the additional declarations, and nothing else changed:
Player constructor's native original target remained `0x00572BB8`, four
Dialogue references remained `0x0056FE1C`, and ASCII constructor's target
remained `0x0056F5CC`. Each old/new symbol was reconciled **only** after
checking complete nonrelocated bytes, current locked object receipts and
identical native relocation offsets/types/unchanged independently observed
targets; every such unit passed the unmodified strict canonical comparator.
Private evidence: `.analysis/core320-reconciled-private-symbols.json`,
`.analysis/core320-affected-headers.json`, `.analysis/core320-replay-groups.json`,
and `.analysis/core320-replay-batch0.log` through `batch5.log`.

The full **1,518-byte** original `Player::rebuild_option_animations` remains
**nonexact**, as do its unresolved WeaponStone virtual dispatch and active
resource creation paths. Precise helpers and source declarations do not
establish whole-parent exactness, whole-executable link or runtime closure.
