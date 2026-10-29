# CORE/RECON-508 — entire original 3,111-byte Player main-frame typed C++ frontier

Comparison original: user-selected Japanese TH20 v1.00a Steamless,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**An entire game-authored Player main-frame C++ implementation now exists in
`src/PlayerMainFrame.cpp` as the typed method `Player::update_main_frame()`.
It remains NONEXACT, contributes zero original matching bytes and has no
canonical exact match unit.** Do not count this original 3,111-byte parent
from already exact callees. The separately exact 25-byte
`Player::frame_changed()` at `0x004C0CE0` is **another real function**;
its original signature must never be assigned to this parent.

## Immutable native extent and ownership

The complete original physical function spans
`0x004F9C30..0x004FA856`, **3,111 bytes / 783 i386 instructions**, full
native SHA-256
`7f0bff5c2e175ff3d223c9e958fd908e39016b136fd1ff0eb0e1ce0cf6672467`.
Original separate E8 displacement decoding yields **67 direct call sites**
to 36 unique native destinations. The original PE `.reloc` section
independently identifies **37 HIGHLOW absolute fields**, including real
static direction/audio/animation/clock references.

The function belongs to the actual 0x1485C Player owner and is called
from the independent original 4,043B Player state routine at
`0x004F7430`. The actual return is an integer zero, with ECX Player
receiver and no stack arguments. Native original callers and the object
layout prove a game-authored Player frame, rather than a standard-library
helper. The original `Player.hpp` now declares `update_main_frame()`;
this descriptive C++ name is **not a native original symbol claim**.

## Complete staged gameplay source

The whole typed maintained body contains the following original operations,
not merely isolated child helpers:

1. Resolve the **signed InputInf logical-to-process-view index** via
   original `0x00498FB0`, then independently test the separate native
   process input pointer array at `0x005B889C`. This corrects the older
   false interpretation of `InputInf+0x2E30` as two pointers. See the
   [independent three-caller ABI correction](INPUT_INF_VIEW_INDEX_ABI_CORRECTION.md).
2. Handle the original two-bit special movement state, `Timer+0x2070`
   transitions, exact animation-option suspension/clear/setter calls,
   and independently whole-exact `SoundInf::request_effect(0x50/0x51)`
   operations. The original may exit its special-mode calculation before
   normal input processing, retaining the resulting motion for this frame.
3. Perform ten separate live `InputButtonState::replay_current_bits`
   operations, preserving original diagonal precedence
   (`0x50/0x60/0x90/0xA0`), single direction bits
   (`0x20/0x10/0x40/0x80`) and two independently reread focus bits `8`.
   Use the true enemy Context/count and focus Timer when transitioning
   `Player+0x204C` and the prior fixed-position history.
4. Select one of **nine signed original direction pairs** from the
   independently decoded immutable table at `0x00572C48`:
   `(0,0)`, `(0,-1)`, `(0,1)`, `(-1,0)`, `(1,0)`, `(-1,-1)`,
   `(1,-1)`, `(-1,1)`, `(1,1)`; index is the live `Player+0x67C`.
   Apply the real focused/unfocused and diagonal speed fields
   `Player+0x20B4..0x20C0`, the real carry from the two motion vectors,
   clock scaling `+0x20EC` and defined wrapping 32-bit integer addition.
5. Create/retain the true effect AnimationHandle via Context/EffectInfo
   when focused; use the actual Player `AnimationFile*` member at
   `+0x1C`, the native effect resource and conditional sprite scale
   application. On unfocusing, interrupt the existing animation and
   assign the true four-byte handle through its existing setter.
6. Select the original four direction-change animation scripts using
   previous movement sign at `Player+0x674`; run the whole maintained
   `Player::apply_move_delta` (separate original 555B still NONEXACT),
   then update the actual AnimationHandle position when valid.
7. Shift the original 33-element `PlayerValues<IntPoint,33>` fixed-point
   position history backwards when movement is nonzero, preserving the
   previously exact original 16B size and 22B indexed access methods.
   Then walk the true **10 primary and 12 secondary 300-byte**
   PlayerOption records with two calls into the already exact 1,081B
   `Player::update_option_frame`, while preserving the native 30-frame
   option-expiry state update.

The original input lookup, sound, option, Animation, Timer, movement,
EnemyController and typed handle/position dependencies are real,
existing game-owner methods, not invented host shims. The source contains
ordinary C++ and no copied decompiler implementation, fabricated stack
padding, inline assembler, hardcoded executable byte arrays or partial
comparison extent.

## Whole parent compiler results — NOT strict exact

The first complete typed C++20 source compiled to **2,412B / 645
instructions**; its indirect lambda for repeated input checks was not
present in the original game, so the genuine ten individual read paths
were expanded and its `InputInf::for_view` ABI corrected. That revision
emitted **3,099B / 770 instructions** and 633/783 original mnemonic kinds
aligned. Further whole-function experiments used the directly observed
`AnimationFile*` member at `Player+0x1C` rather than extra accessors,
separate original X/Y speed reads, the two distinct native conditional
scale-call paths and genuine `AnimationHandle` comparison and assignment
methods. Their current natural typed source produces:

| Entire native measure | Original executable | Current maintained candidate |
| --- | ---: | ---: |
| Whole game function bytes | **3,111** | **3,235** |
| Complete x86 instruction heads | **783** | **807** |
| Ordered original mnemonic kinds aligned | 783 | **672 / 783** |
| Native directly decoded E8 calls | **67** | **67 emitted COFF REL32** (not yet original-field aligned) |
| Native PE HIGHLOW fields | **37** | **35 emitted COFF DIR32** (not yet original-field aligned) |
| Total canonical relocation fields | **104** original | **102** candidate; **not exact** |

The compiler profile is pinned MSVC 19.44.35211 x86 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
The last 67 direct call *count* agrees, but symbol targets, exact
positions, original all-byte code shape, condition register lifetimes,
C++ library/handle alias origins and two remaining absolute relocation
fields are not proven equivalent. The current difference is
**124 bytes and 24 instructions**, and 111 original mnemonic kinds
lack full ordered alignment. The source is a **whole semantic frontier**,
not strict original equivalence or a native acceptance claim. Preserve it
as an actual source-present reconstruction while continuing the original
operand/field and EH/ABI review.

Private original/candidate and compiler variant evidence:
`.analysis/core432-player-main-native-original-callgraph.json`,
`.analysis/core430-player-main-frame-decompile.txt` (read-only Ghidra
hypothesis, not oracle), `.analysis/core508-player-main-native-codegen.json`,
`.analysis/core508-player-main-direct-input-score.json`,
`.analysis/core509-player-main-body-variants.json`,
`.analysis/core509-player-main-maintained-score.json` and
`build/core508-probes/PlayerMainFrame.obj`.

## Affected-only regression and open parent/child work

`src/Player.hpp` gained exactly one real main-frame method declaration.
The independently established view-index ABI correction changed only
`InputInf.hpp`, its two implementation owners and the exact getter
symbol name. *Pre-edit canonical MSVC receipt headers* selected the
union of exactly **33 source objects and 89 strict units** for these
public-header changes. They were rebuilt serially at low priority,
then all **89/89 previously exact whole original bodies strictly
replayed**. The sole compiler-private string renumbering in the original
Player constructor was independently validated against the original PE,
not taken from candidate byte-field subtraction. There was **no
unfiltered all-graph cold replay**.

The independently authentic `Player::apply_move_delta` at
`0x004FFA10` is a complete 555B original and remains NONEXACT under
natural maintained C++ (561B/136 vs 555B/135; one extra SSE spill).
The enclosing Player state root at `0x004F7430`, main frame at
`0x004F9C30`, and whole-game linker/runtime are still open. The present
checkpoint adds **one newly source-present whole Player function**,
**corrects an important physical ABI error**, preserves all 437
existing authored exact roots, and makes no new original exact-byte claim.
