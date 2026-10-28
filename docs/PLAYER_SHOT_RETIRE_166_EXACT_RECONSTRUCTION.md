# CORE/EXACT-402 — complete original PlayerShot retirement and pool recycling chain

The immutable user-selected Japanese TH20 v1.00a Steamless PE is
`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**Three distinct whole game-authored native methods totaling 262
nonoverlapping original text bytes** are now strict exact C++ in
the existing canonical source `src/PlayerShotReset.cpp`:

| Physical original method | Native entry | Original bytes | Original x86 instructions | Original PE E8 / HIGHLOW |
| --- | --- | ---: | ---: | ---: |
| `PlayerShot::retire()` | `0x00506AF0` | **166/166** | **49** | **7 / 1** |
| `PlayerShotController::return_to_free(PlayerShot*)` | `0x00506AB0` | **55/55** | **20** | **2 / 0** |
| `PlayerShot::heap_owned() const` | `0x00506540` | **41/41** | **15** | **0 / 0** |

The three immutable original full-interval SHA-256 hashes, in the
same order, are
`c63be2e1cdb4597f306232134208152133733031401af42b23098e173a399636`,
`774e29eda3ae02064126f7631b6615ca0a2571fe598853ff307f1d6104c7311b`,
and
`eea526429cc63869e259608340816a2ba7efd3995ae10179b35e8c8fa0b10073`.

## Complete original game-owned lifetime behavior

The 166-byte source is a genuine full method on the real 0x124-byte
`PlayerShot`, not a helper fragment. It first clears `+0x9C`,
retires the real `AnimationHandle` at `+0x18`, and consults
the original `Context::hit_controller()` using the actual
`Context` pointer at `+0x120`. If that controller exists,
it tries resolving the real four-byte `DamageHandle` at
`+0xDC` and retires the resulting damage region if nonnull.
It then detaches the true `IntrusiveLink<PlayerShot>` at
offset zero, asks the owning `PlayerShotController` pointer
at `+0x11C` to return the shot to its free list, saves its
old `state_14` word and resets that state to zero. Finally,
only if prior native `state_14` bit 24 was set, it releases
the whole heap-owned shot through the actual process allocator.

The separately exact 55-byte `return_to_free` does **not**
recycle heap shots. It calls the 41-byte `heap_owned` predicate
and only if false prepends the real shot link to the native
controller free list at `+0x12448`. The 41-byte method tests
exactly native bitmask `0x01000000` in the shot's state
word at `+0x14`. The native 41-byte encoding specifically
uses a real `bool` value/conditional expression;
simplifying it to the alternative `!= 0` expression
was 47 bytes under the original `/Od` compiler, so was
**not** accepted as original.

The 166-byte retirement is reached by the **already exact
269-byte** `PlayerShotController::reset_all` at `0x00504950`,
directly called by the separate **already exact 966-byte**
`Player::reset_initial_state` boss. This source chain
establishes actual live player/game ownership and never
attributes compiler library functions as additional game bodies.

The separate **67-byte** original `DamageHandle::resolve`
at `0x004C0E10` is **still independently nonexact**;
it is a real typed external method declaration only, not
claimed reconstructed by the now exact 166-byte caller.
Likewise the native 66-byte intrusive `prepend` at
`0x0044A6B0` remains a separate original function.

## Fresh original PE direct-call and global-relocation proof

Original bytes and x86 instruction boundaries were read again
from the immutable original PE independently of the candidate.
Every native direct E8 call displacement and original PE
`.reloc` HIGHLOW field was compared with the actual locked
compiler COFF function reference offset, type and original
destination. The native 166-byte method has **eight** references:

| Original field | Type | Independently original native target |
| --- | --- | --- |
| `+0x1D` | REL32 | `0x0044FCD0` — AnimationHandle retirement |
| `+0x2C` | REL32 | `0x00412710` — Context Hit controller accessor |
| `+0x3E` | REL32 | `0x004C0E10` — unresolved DamageHandle lookup |
| `+0x4F` | REL32 | `0x004C1F30` — complete DamageRegion retirement |
| `+0x58` | REL32 | `0x00411CE0` — intrusive link detachment |
| `+0x70` | REL32 | `0x00506AB0` — entire 55B pool recycle |
| `+0x98` | DIR32 | `0x005B8894` — real process allocator pointer |
| `+0x9D` | REL32 | `0x00413B70` — true heap object release |

The entire 55-byte recycling method has native
`+0x0D REL32 -> 0x00506540` (`heap_owned`) and
`+0x2C REL32 -> 0x0044A6B0` (intrusive free-list prepend).
The 41-byte predicate has no external relocated fields.
Thus all **10/10 independently original E8/HIGHLOW targets**
and all **84 whole native instructions** match; the unchanged
strict canonical oracle accepts **166/166, 55/55 and 41/41**
without skipped blocks, manually padded NOPs, fake returns,
assembly or a shorter-than-original comparison range.

Complete original target SHA, physical method extents,
native x86 instruction counts and all ten PE reference
details are preserved privately in
`.analysis/core402-shot-retire-original-refs.json`.

## Protected native objects and strictly affected-only replay

Only the preexisting `src/PlayerStorage.hpp` public type
declarations and `src/PlayerShotReset.cpp` concrete source
were changed. Actual sizeof/offset constraints for both
the 0x124-byte shot and 0x12598-byte controller remain
unchanged. The **old pre-edit compiler receipt include
closure** selects exactly **26 source providers with
76 previous strict units**. The three new complete
game-owned units are integrated into the **existing single**
`build/core398-canonical/PlayerShotReset.obj` provider,
so the required set is **79/79 strict units in 26 cold
objects**, replayed in six serial reduced-priority batches
of **5 + 33 + 8 + 10 + 19 + 4**. All pass.
Private scope and complete native logs:
`.analysis/core402-shot-retire-preedit-scope.json`,
`.analysis/core402-shot-retire-replay-groups.json` and
`.analysis/core402-shot-retire-replay-batch0.log`
through `batch5.log`.

One actual MSVC-private string symbol `$SG82230` in
the Player constructor renumbered to `$SG82235`.
The immutable original string destination `0x00572BB8`,
native reference location/type and full nonrelocated bytes
were checked before only that compiler-private spelling
was reconciled and the unchanged strict oracle accepted
its full function. Private audit:
`.analysis/core402-reconciled-private-symbols.json`.
No unrelated source is cold replayed; no unfiltered
repository cold replay or whole-game runtime equivalence
is asserted.


## Subsequent CORE/EXACT-407 complete DamageHandle lookup callee

The separate native **67-byte** `DamageHandle::resolve` at
`0x004C0E10`, still open at this historical checkpoint,
is now **67/67 whole original strict exact**. It copies the
existing raw 4-byte DamageHandle word into the genuine
`Identifier32` by-value lookup using a defined compiler
bit-cast, retaining the original DamageHandle scalar
constructor ABI; no unsafe alias casting or false
member retyping is introduced. The original two E8
references target the separately exact 26B
`hit_controller(0)` and 264B `HitCtrlInf::find`.
The actual PlayerStorage.hpp compiler-receipt
closure passed **80/80 strict units in 27 cold source
objects**, no full replay. Earlier statements that
the 67B lookup remains unclosed are superseded.
Read the [complete independent 67B native method proof](DAMAGE_HANDLE_LOOKUP_67_EXACT_RECONSTRUCTION.md).
