# CORE/EXACT-314 — entire 966-byte Player initialization/reset gameplay boss

This checkpoint reconstructs **one entire original game-owned Player method**
`0x004FB450..0x004FB815` (inclusive): **966 native bytes, 208 x86 instructions**
and original interval SHA-256
`9bf7d059b85c4cede182813b8470e46b60669cb6e43704a3333468b6d2964904`.
The target is the immutable, agreed Japanese TH20 v1.00a Steamless executable,
whole-file SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
There is **no prefix comparison, arbitrary NOP, binary patch, decompiler code
blob or shortened function extent**. The whole maintained natural C++20 source
is `src/PlayerResetInitial.cpp`, `Player::reset_initial_state()`.

## Full native behavior (not extracted basic blocks)

Fresh target-attested Ghidra call/decompile evidence was independently checked
against the entire original instruction stream. The reset executes, in native
order:

1. Set the Player's actual state word `+0x10` to one; clear timers `+0x644`
   and `+0x654`, then clear separate Player entity flag bits 0 and 3,
   preserving the other bits. Retire and reset both original four-byte
   AnimationHandles at `+0x60C` and `+0x610` through their distinct native
   calls.
2. Reset the real `PlayerShotController` at `Player+0x22B4`, call the
   separately exact 237-byte `clear_option_animations` sweep, and call the
   separately open 1,518-byte `rebuild_option_animations(-1)` at `0x004FACA0`.
   Restore the `+0x20EC` float to 1.0f, clear flag bit 2 through the separately
   exact 26-byte member, stop the real float Interpolation, set both collision
   expansion and the clock-scale setter to native 1.0f.
3. Reset **all 33 actual eight-byte `IntPoint` position history records**
   `Player+0x20FC` from the Player's real fixed-position reference `+0x620`.
   The source uses the genuine `PlayerValues<IntPoint,33>::begin/end`
   traversal and a live iterator local; no raw memory block substitutes for
   the native typed copy.
4. Read the four **native IEEE-754 float** speed parameters at serialized
   `PlayerShotData+0x10/+0x14/+0x18/+0x1C`, multiply independently by
   original `128.0f` and truncate with x86 `cvttss2si` to the genuine Player
   integer speed fields `+0x20B4..+0x20C0`. This corrected an earlier
   unverified nine-integer-header hypothesis which created four extra
   `std::bit_cast` helper calls. The four float members and their actual
   offsets are now maintained in `src/ShotData.hpp`; their gameplay labels
   remain provisional.
5. Initialize the actual `PlayerMotionParameters` five floats using original
   5, 30, 70, 70 and 128; initialize normal/focused `PlayerCollisionBounds`
   from 3.0, half-extents and the original 10.0/2.0 Z extent. Set
   `field_2204=8` and write the real five script slots `0..4` in order.
6. Get `player_table()`, run the now exact 73-byte integer clamp of its
   mode field to 0..1, inspect the separately exact Session flag-0 accessor
   and the Player's real `view_index`. Call the original `enter_special_state`
   **only** when the clamped mode is zero, flag-0 is zero and view index is
   one; otherwise exit without the special-state side effect.

The returned `void` ABI, both original callers (`0x004BA940`, `0x004BBF90`),
16 distinct original callees, all branch paths and the complete original
frame and return are retained.

## Independent native relocation proof

The entire original 966-byte PE range contains **40 independently grounded
native relocation fields**: **19 direct `REL32` call sites** decoded from the
original E8 instructions, plus **21 `HIGHLOW` / `DIR32` fields** taken from
the *original PE's own `.reloc` table*, including the true `session` global
at `0x005BA568` (an immediate, not a memory operand). All 40 original
field offsets and types agree exactly with the 40 genuine COFF relocations.
The underlying targets follow original code, original base relocation and
already separately reviewed function/global identities, not a solution
computed from the bytes being compared. All **806 non-relocation bytes**
also match directly. The original complete interval, each original target,
its evidence class and compiler symbol are recorded privately in
`.analysis/core314-player-init-original-relocations.json`.

The canonical unit is `player_reset_initial_state` in
`config/match-units.toml`. Locked MSVC 19.44.35211 x86 with explicit
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
emits **966/966 complete original bytes, including every branch displacement,
stack-local slot, integer conversion and all 40 replayed reference fields**.
No compiler, target or native function bytes were patched.

One original call at `+0x10F` to `0x0040BDA0` uses a naturally compiled
14-byte `PlayerValues<IntPoint,33>::begin` instance. That entire emitted
body has independently been compared to the physical original 14-byte helper,
whose Ghidra library identity is provisional and may be linker folded.
No *second* exact credit was claimed for that shared physical address.
The separately existing `end` at `0x004FCE40` remains 19/19 strictly exact.

The matching C++ source groups the real clock initialization as its own
ordinary C++ block before position-history maintenance. MSVC naturally emits
the original one-byte `nop` at the block boundary in this `/Od` profile; it
is **not** manually injected or represented as inert compiler-shaping locals.
A distinct, previously captured whole-body private candidate without that
scope emitted 965B / 207 aligned kinds. Earlier guesses about the shot
header and iterator ownership are preserved in ignored experiment snapshots,
not allowed to overwrite the native findings.

## Actual affected-only strict replay

Three changed native headers (`src/Player.hpp`, `src/PlayerStorage.hpp`,
`src/ShotData.hpp`) impact **exactly 20 existing canonical source providers
and 60 previously strict units** according to the *actual previous build
receipt include closures*. The new `PlayerResetInitial.cpp` adds **one** new
provider/unit. All **61/61 original whole-function strict units across 21
fresh locked-MSVC objects** pass, serialized at reduced scheduling priority
in five batches (5, 32, 8, 15, 1 units). This includes the existing 2,018B
Bullet collision, 898B Bullet command-3, 661B Player rotated collision,
777B rectangle collision and 466B circle collision. No accepted relocation
needed symbol renumbering or relaxation in this batch.

Evidence logs: `.analysis/core315-player-init-replay-batch0.log` through
`batch4.log`, plus the source-by-header include graph in
`.analysis/core315-player-init-include-closure.json` and the exact replay
source list `.analysis/core315-player-init-replay-groups.json`. Original
target hash and source ledgers remain valid; no unfiltered cold replay ran.

**This native exact root is not proof of whole-executable linkage or runtime
completeness.** The separate 1,518B option rebuild, 269B shot-controller
reset, 41B special-state entry, full Player construction/game startup and
large Bullet/Enemy dispatchers remain distinct unfinished work.


## Subsequent CORE/EXACT-369 whole-parent closure

The *separate* complete **1,518-byte** Player option rebuild boss at
0x004FACA0 is now independently **1,518/1,518 native strict exact**,
with all 418 original instructions and 60 independently attested
E8/HIGHLOW references. Any earlier reference in this historical
checkpoint to that parent as still nonexact/open is **superseded**.
This proof's own helper or original function is not double counted.
Read the [new entire Player option rebuild exact proof](PLAYER_OPTION_REBUILD_1518_EXACT_RECONSTRUCTION.md).
