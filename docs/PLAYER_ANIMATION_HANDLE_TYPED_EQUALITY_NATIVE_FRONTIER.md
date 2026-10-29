# CORE/RECON-663 — typed Player AnimationHandle equality and protected native closure

The original game-owned Player::update_main_frame at 0x004F9C30
remains **NONEXACT**. The complete original body is **3,111 bytes /
783 x86 instructions** in the hash-locked Japanese TH20 v1.00a
Steamless executable (SHA-256
a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897).
This checkpoint repairs one native **callee/receiver ABI** within
the maintained complete Player parent; it does not accept partial
parent code or invent 45 more authored original bytes.

## The original four-byte Player object and real equality call

The independently strict-exact complete original 794-byte Player
constructor at 0x004F46A0 calls the actual 23-byte
AnimationHandle default constructor at original 0x00425CC0
**twice**, with receivers Player+0x60C and +0x610. These are
two genuine AnimationHandle members, not arbitrary untyped
four-byte placeholders or instances of EffectAnimationHandle.
The already maintained Player layout and exact constructor agree.

When the whole original Player main frame reaches its focused
animation effect path, it passes **Player+0x60C** and zero to a
real call at 0x004FA273, targeting original physical function
**0x00449430**. The entire 45-byte target compares the
receiver's 32-bit word with the argument, returns TRUE on
equality, and has zero external relocations. Its precise native
body is already separately accepted under
EffectAnimationHandle::matches_value(uint32_t), whose object
contains the same four-byte AnimationHandle representation.

The earlier Player source used !(handle_60c != 0), which calls
the distinct physical 45-byte AnimationHandle::operator!= at
0x0047C650. The numerical boolean result is generally equivalent
but the real emitted call target and predicate function are not.
Reinterpreting the live AnimationHandle member as an unrelated
EffectAnimationHandle violates C++ object-lifetime requirements
and is not an acceptable native reconstruction.

The maintained typed correction adds a normal member method
AnimationHandle::operator==(uint32_t) const, implemented in
src/AnimationHandleEquality.cpp as return value == input, and
makes the Player parent call handle_60c == uint32_t{0}.
A fresh pinned MSVC 19.44.35211 i386 build emits the complete
**45/45 identical original instruction bytes** at
0x00449430, with zero relocations. This is a plausible original
COMDAT/ICF-folded semantic alias, NOT proof of historical linker
settings or a separate original physical body. No duplicate
game-authored 45-byte credit is claimed. No Player layout
change or dubious aliasing cast is needed.

## Whole 3,111-byte boss progress and separate remaining blockers

A fresh complete src/PlayerMainFrame.cpp build preserves the
previous input/Timer/signed-speed corrections and emits
**3,110 bytes / 784 instructions**, now with **759/783 original
mnemonic heads aligned in original order** (758/783 before
the typed equality). The candidate keeps 67 E8 and 37 DIR32
references, equal to the original counts of 67 E8 and 37
PE HIGHLOW by COUNT only. The newly typed equality E8
is original call ordinal 36, now using the 45-byte
original-compatible member's concrete C++ symbol.

Independently auditing the physical original 67 E8 identities
against the current complete candidate gives **61 known
correct**, **zero known incorrect**, and **six at this dated checkpoint still requiring
individual alias/source-origin reconciliation**. A subsequent
[independent complete original 67-callee audit](PLAYER_MAIN_FRAME_67_ORIGINAL_CALLEE_ROLES_FRONTIER.md)
now corroborates all six remaining source/physical call roles
(five fully native-byte-identical folded helper occurrences,
plus the genuine mapped 555B nonexact Player movement child).
The exact historical linker ICF settings remain unknown.
A correct call *role* is not byte-exact acceptance of
the 3,111-byte enclosing boss. Real stack lifetimes,
branch shapes and actual physical original 37 absolute field
positions remain unresolved. The complete parent is **NONEXACT**.

The 45-byte equality candidate is a new noncanonical source
component and is deliberately **not** added as a separate
canonical unit with duplicate original bytes. The existing
effect-handle canonical 45-byte physical function stays exact.

## Pre-edit shared-header closure: strict native protection

The only shared interface edit is a new member declaration in
src/AnimationHandle.hpp; the genuine object remains four bytes
and the Player fields remain at their original offsets.
Prior to editing, every configured canonical provider's
existing compiler receipt was inspected for that header.
The captured original include closure consists of
**116 real source/COFF providers with 486 previously accepted
strict original units**, out of the complete graph's 244
providers and 1,185 configured units. Those are precisely
the previously accepted inputs affected by the header edit;
the others were not rebuilt.

All 116 affected providers were freshly compiled under their
own pinned native MSVC profile, serially and at reduced priority,
in eight bounded batches. Every one of the **486/486 original
units passed complete strict relocation-aware replay**:
70/70, 82/82, 78/78, 76/76, 82/82, 41/41,
52/52, and 5/5. The last batch explicitly included
the newly strict 3,735B Bullet emitter with its entire
3,832B code/NOP/switch-table comparison, the 1,404B
Bullet command-11 boss, and independent Animation owners.
The complete 794B Player constructor remained exact.

The new C++ declaration deterministically shifted several
MSVC-private source string labels in some unchanged compiled
function units. **34** recorded old private $SG labels needed
renumbering, but not one original relocation offset/type,
original physical destination, function size, profile or
original source owner changed. Before each such strictly
limited manifest symbol edit, the newly generated COFF
initialized NUL-ended string was compared **byte-for-byte**
with the independently known original PE file-backed
string at its *existing* original anchor. Renames were
accepted only for proven identical original strings.
One initial 57-byte sprtlib string, followed by each
remaining individual audited string, was validated;
unrelated names/fields would instead have failed the
comparator. No target field was reverse-solved, patched
or excluded from the exact replay.

All 116 regenerated canonical receipts record the new
AnimationHandle.hpp SHA-256 and match their generated
COFF object hashes. A separate independent manifest
comparison confirms exactly the 34 private symbol-only
renames; all 1,185 canonical units retain their
original relocation positions, types and destinations.

## Reproducible evidence and affected-only scope

- .analysis/core659-player-animation-handle-typed-equality.json:
  actual whole-method and separate typed 45-byte native object.
- .analysis/core662-player-main-typed-callee-audit.py/json:
  whole original 67-call identity audit with an independently
  45/45-byte checked typed equality alias (61 known, zero wrong).
- .analysis/core657-player-animation-equality-preedit-closure.json:
  all pre-edit canonical receipts and exact include closure.
- .analysis/core660-animation-handle-affected-replay-batches.json:
  the eight verified provider/strict-unit replay batches.
- .analysis/core660-prebuild-batch-1.log through batch-7.log,
  .analysis/core660-replay-batch-0.log, and
  .analysis/core660-existing-strict-batch-1.log through batch-7.log:
  cold native compilation and actual strict original replays.
- .analysis/core660-private-symbol-audit-batch-1.json through
  batch-7.json: independent original PE string checks
  before changing only compiler-private $SG symbol labels.
- .analysis/core661-animation-handle-complete-closure-proof.json:
  affected closure and current receipt SHA audit.
- .analysis/core663-independent-private-string-34-proof.py/json:
  **recreated from prior Git HEAD versus the current manifest**,
  independently checks all 34 changes against new live COFF
  initialized strings and immutable original PE NUL-ended bytes;
  every manifest relocation location, type and target stays fixed.
  This complete proof does not depend on intermediate private
  batch JSON artifacts retaining their old contents.
- build/core659-probes/AnimationHandleEquality.obj and
  build/core659-probes/PlayerMainFrame.obj:
  complete actual noncanonical native source probes with receipts.

**Replay scope: precisely 486 previously strict units in 116
affected canonical objects, and two current noncanonical native
source probes.** This was not a global or unfiltered cold replay.
No existing exact original authored body was lost, no target was
changed, and no linked/playable game is claimed. Canonical
game-authored coverage remains **499 exact functions,
179,444 original native code bytes**, including the already
exact Bullet emitter but excluding all still nonexact
Player main-frame parent bytes.
