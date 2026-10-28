# CORE/EXACT-436 — complete original 237-byte Player option mode-3 suspension boss

Immutable comparison original: Japanese TH20 v1.00a Steamless
`resources/th20.exe`, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The entire original game-owned function at `0x004BD0C0`, 237
bytes and 72 native i386 instructions, is now **237/237 strict
exact** as `Player::suspend_option_animations()` in the
existing `src/PlayerOptionClear.cpp` source owner.
Original whole interval SHA-256:
`cfc2a084bac512a3e53d3d106d8f8c0943070fc57184b54ef9f89eebc69c668f`.

## Real game state and distinct native mode-2 / mode-3 functions

The separately exact `Player::clear_option_animations()` at
`0x004FF8F0` is **also 237 bytes**, but has **different
original behavior and a disjoint physical original interval**.
That function *clears* Player entity bit 1 and invokes
mode-2 handle cancellation. In contrast, the new mode-3
suspension *sets* Player entity bit 1 and iterates **all
ten primary `PlayerOption` objects at Player+0x684**
and **all twelve secondary option objects at +0x123C**,
each of the actual native 0x12C-byte stride. In both
loops, it invokes the real `PlayerValues<PlayerOption,N>::at(i)`
*separately* for the two `AnimationHandle` members
at option offsets +0xDC and +0xE0, calls the real
`cancel_animation_handle_mode3` on each handle,
and resets the native Player option frame counter
at `Player+0x20E8` to zero.

The entire native code naturally emits the original
after-pair loop NOPs. All branch boundaries, frame
state changes, return path and original call sites
are included. Neither source was shortened; no
synthetic dummy variable, manual assembly or hand
NOP was used. The original still-open 3,111B
unnamed Player main-frame at `0x004F9C30` invokes
this mode-3 suspension exactly once (original\ncallsite +0x75, independently decoded from PE).
The two real native functions never share a
physical credited interval.

## Independent original executable relocation and call proof

Full original PE Capstone decode produces **72 complete native
x86 instruction heads**. Independently read original PE E8
operands yield eight REL32 call fields and the immutable PE
`.reloc` table gives **zero HIGHLOW** fields.

| Original native E8 byte fields | Independent original target | Independently already exact callee |
| --- | --- | --- |
| `+0x44, +0x67, +0xA5, +0xC9` | `0x004BA3E0` | whole 23B folded `PlayerValues<PlayerOption,10/12>::at` |
| `+0x50, +0x73, +0xB1, +0xD5` | `0x00486350` | whole 22B `cancel_animation_handle_mode3` |

All **eight** original offset/type/target fields agree with
the emitted actual MSVC COFF symbols. The two different
typed source template instantiations fold to the **one**
original game physical 23B index body and are counted once.
The unchanged strict original comparator accepts
**205/205 nonrelocation +32/32 relocation bytes =
237/237 complete native bytes**. The immutable SHA,
all eight independent fields/targets, old separate
mode-2 native boundary and natural source diagnostic
are in
`.analysis/core436-original-player-suspend-option-237-proof.json`.

## Only the true changed-source receipt closure was replayed

The only maintained changes are the real
`Player::suspend_option_animations` method declaration
in `src/Player.hpp` and its natural source body in
`src/PlayerOptionClear.cpp`, using the same original
canonical MSVC i386 C++20 profile and object provider.
The previous actually locked `Player.hpp` header
compiler receipts select **25 old source providers /
71 old strict units**. The one newly admitted full
original body in the **same** PlayerOptionClear
source raises this to **72/72 strict native original
units in 25 freshly rebuilt source objects**,
replayed in five reduced-priority serial groups of
**5+35+8+14+10**. The unchanged 237B mode-2
clearer, 1,081B per-option Player frame,
1,518B option-animation rebuild and 966B
initial reset still pass the complete native oracle.

A single MSVC compiler-private Player ctor
`$SG` ID renumbered; only its spelling was
reconciled after independently attesting
the unchanged original PE string target
`0x00572BB8`, original relocation offset/type
and the entire function's nonrelocation bytes.
See the old native receipt scope at
`.analysis/core436-suspend-options-preedit-source-closure.json`,
actual replay groups at
`.analysis/core436-suspend-options-replay-groups.json`,
full strict batches
`.analysis/core436-suspend-options-replay-batch0.log`
through `batch4.log`, and private original
field audit
`.analysis/core436-reconciled-private-symbols.json`.

Only **one genuinely new 237-byte original game-owned
function** is credited. The still-open 3,111B
Player enclosing controller, nonexact 555B
Player movement and whole executable linkage
remain independent. No unfiltered global cold
replay was run.


## Separate exact mode-3 callee receipt refresh

The previously exact mode-3 wrapper owner
`src/BulletCollisionAnimationHelpers.cpp` had an old receipt
whose broad `inputs` inventory was stale. After the new 237B
unit and its actual 25-source receipt closure passed, this
separate previously exact native callee was independently
cold recompiled under its original locked MSVC profile.
**8/8 native strict units in one further cold object**
passed, including the entire 22B mode-3 wrapper and
the existing mode-1/mode-2, Animation/handle forwarding
and clear-value methods. Full bounded evidence is
`.analysis/core436-mode3-callee-extra-scoped-replay.log`.
This additional verification is disjoint from
the new method's **72/72 actually affected strict units
across 25 cold source objects**. No duplicate exact bytes
or global cold replay are involved.
