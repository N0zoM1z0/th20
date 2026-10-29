# CORE/RECON-665 — all 67 original Player main-frame E8 callee roles corroborated

**The complete 3,111-byte game-owned Player::update_main_frame
at 0x004F9C30 remains NONEXACT.** The original Japanese TH20 v1.00a
Steamless target is SHA-256
a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.
This investigation concerns independent complete original function
identities and their call roles, not exactness of the enclosing
Player dispatcher.

## Why existing native symbol names were not sufficient

The locked original method contains exactly **67 physical native E8
calls**. The latest whole C++ candidate also has 67 COFF REL32 call
fields in corresponding ordinal order. Accepted canonical function
identities and their unique original physical heads account for 61
of those roles, including the newly typed 45-byte
AnimationHandle::operator==(uint32_t) body at original 0x00449430.

Six remaining roles were previously reported as unknown because the
new source emits valid typed C++ symbols that do not independently
appear in the canonical manifest with the original *folded*
physical address. A name-only search therefore could not establish
whether a byte-identical source implementation existed. This
is not reason to substitute a helper, invent an address, or mark
the enclosing 3,111B parent exact.

## Independent complete native evidence for five folded call occurrences

Four different natural compiled C++ whole methods match the entire
physical original bytes, with zero relocations in each small method.

| Original call ordinal(s) | Natural typed source role | Original physical destination | Whole original body verified |
| --- | --- | --- | --- |
| 29, 30 | Context::enemy_controller() | 0x00412730 | 17/17B, both calls |
| 46 | AnimationHandle::operator=(uint32_t) | 0x004117A0 | 21/21B |
| 62 | PlayerValues<PlayerOption,10>::begin() | 0x0040BDA0 | 14/14B |
| 65 | PlayerValues<PlayerOption,12>::begin() | 0x0040BDA0 | 14/14B |

Each whole original code body is decoded from immutable PE at the
reported **original target**, independently of the Player caller's
COFF field. Each candidate body is independently extracted from
its actual current canonical MSVC source/COFF owner:
src/Context.cpp, src/AnimationHandle.cpp, and
src/PlayerOptionManagement.cpp, respectively. They use the
already accepted native provider receipts and complete original
byte/return extents, not fabricated stubs. The two typed begin
instantiations both match the same original 14B implementation;
they receive no double physical code credit.

The original 17B destination is historically catalogued as an
IntrusiveLink<DamageRegion> previous-value accessor, the original
21B as Identifier32 assignment, and the original 14B as a
Motion position accessor. Their *machine-code equality* is
independently verified, but the exact historical linker ICF/COMDAT
provenance and original source spelling remain provisional.
This does **not** reclassify these old physical targets or
add separate source functions to game-owned exact counts.

## The sixth formerly unknown role: real 555B Player movement

Original E8 call ordinal **51**, at original 0x004FA61F, targets
the complete original Player::apply_move_delta at 0x004FFA10.
It is independently inventoried as a **555-byte original method**,
with the real two-integer Player __thiscall ABI and complete
maintained source src/PlayerMovement.cpp. The whole Player
main-frame candidate emits this same typed native call role.

**The 555B movement child is still NONEXACT.** Mapping its
complete native original head and its real source/call signature
supports the source-level *callee identity*, not a claim of
byte-identical compiled code or a resolved original linker
alias. Its separate SSE spill/register issue remains active.

## Complete main-frame E8 census and limits

The independently decoded original has 67 E8 physical call targets;
the complete compiled parent has 67 REL32 in the corresponding
ordinal call sequence. All 67 call roles now have independent
support: **61 previously verified**, **five newly proven
whole-body-compatible folded call occurrences**, and **one
typed source-present 555B nonexact movement callee**.
There are **zero presently unresolved call roles** at this
source/physical-code compatibility level.

This is not a declaration of 67 exact relocated fields in a
canonical Player whole-parent unit, not proof that the original
linker made each suggested fold, and not proof that the Player
parent's native control flow/stack/absolute relocations match.
The actual parent is still **3,111B / 783 original instructions
versus 3,110B / 784 candidate**, with 759/783 original mnemonic
kinds aligned and original 37 PE HIGHLOW fields only matched
by source **count**. No part of the parent is newly admitted exact,
no helper native code is double-counted, and there is still no
game-wide linked executable.

## Reproduction and scoped validation

- .analysis/core664-player-callee-folded-independent-proof.py/json:
  four complete original PE physical targets compared byte-for-byte
  with distinct current canonical MSVC C++ whole methods,
  plus original Player movement source/ABI mapping.
- .analysis/core665-player-67-roles-callee-audit.py/json:
  full original 67-call census against actual latest whole
  Player C++ COFF, incorporating only the independently
  verified 45B handle equality and four folded C++ method
  identities, plus the mapped nonexact movement child.
- .analysis/core662-player-main-typed-callee-audit.py/json:
  previous whole frame 61 supported physical call roles before
  reconciling the remaining five folded instances and movement.
- docs/PLAYER_ANIMATION_HANDLE_TYPED_EQUALITY_NATIVE_FRONTIER.md:
  45/45-byte typed equality and the already successful
  116-provider, 486-strict-original-unit header closure.

**Changed native compiler inputs in this checkpoint: zero.**
This is an independent original-PE and currently accepted COFF
whole-body/caller audit. No new cold replay of an unchanged
native graph, no target patch, no shared header edit, and no
full repository replay were performed. Game-authored strict
coverage remains **499 functions / 179,444 original bytes**.
