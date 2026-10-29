# CORE/EXACT-645 — complete original 3,735-byte TH20 Bullet emitter strictly exact

**Accepted within the repository's canonical locked-MSVC native replay: the
full original 3,735-byte/935-instruction BulletController::emit gameplay
boss, plus the complete 3,832-byte compiler contribution.**

Game owner: original Japanese TH20 v1.00a Steamless, immutable original
file resources/th20.exe, SHA-256
a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897,
actual native address **0x004818E0**. The function is game-authored;
the adjacent alignment NOP and switch tables are compiler contributions
verified but deliberately excluded from authored byte credit.

## Critical independent original evidence and previous mistaken hypotheses

The complete original native has exactly 935 real x86 instructions,
3,735 bytes, 60 E8 direct calls and 45 PE HIGHLOW relocations inside
the code. The original full contribution additionally has **one**
physical NOP at method +0xE97 and **two original compiler jump tables**
containing **13+11 pointers / 24 additional original PE HIGHLOW fields**.
The entire untruncated original contribution is therefore 3,832 bytes
and 129 physically distinct original relocated fields.

The maintained C++ originally differed from the immutable PE for three
substantive reasons, fixed in natural source rather than by patching:

1. **Mode 11 real trigonometric operands:** the native game first saves
   its circular angle into [ebp-0x6C], then copies to heading
   [ebp-0x24], which is the actual value loaded at *both* cosine
   +0x600 and sine +0x628 call arguments. Earlier source used a
   numerically equivalent, but different-lived circle-angle local.
   Natural cosine(heading), sine(heading) restores the genuine stack
   layout, x87 return lifetimes and following speed/step products.
2. **Mode 12 real nested floating-point evaluation:** the original
   x87 sine -> absolute result is returned by fstp [ebp-0x7C],
   **then reloaded with movss**, then the ShotParameters
   speed-step address is fetched with mov. A detached const value
   local had reversed the pointer fetch and movss. Nesting the actual
   sine/absolute calls into the natural speed expression reproduces
   the original order, without an invented volatile float.
3. **Original consecutive Timer calls and physical NOP ownership:**
   native Timer setters +0xF1 and +0x10D must both run regardless
   of shot.rows. Ordinary separate source statements led MSVC to
   insert a spurious one-byte EH npad at +0x112. A C++17
   if-initializer contains the same two real unconditional Timer
   setters before the same rows > 1 speed selection and emits no
   internal NOP. The only compiler NOP lands at the original
   post-function +0xE97, just before the two native tables.

A final **gameplay semantics correction** was essential: earlier
documents erroneously assumed the first-command velocity multiplier
was 2.0f. The independently original file-backed constant at
**0x0056C8E0 is exactly 4.0f** (IEEE-754 bytes 00 00 80 40),
and the actual original E8 Vector3::operator-= consumes the preceding
Vector3 multiplied by that constant. The previous C++ candidate
referenced the separate 2.0f constant, which a masked-byte diagnostic
could not detect. The source now uses position -= velocity * 4.0f.
The old 2.0f statements in dated CORE/RECON-571 documents are
superseded, not accepted game evidence.

## Relocation evidence: complete, not field-count-only

The independently verified original PE .reloc stream contains **69**
HIGHLOW fields across the complete 3,832 bytes. The exact compiler
produces **69** DIR32 fields with the *same actual offsets*, plus
**60** REL32 at the same original E8 operand offsets.

All 60 real E8 physical callee identities were separately reviewed
against accepted function symbol targets and the genuine old STL
folded/linker aliases; zero are guessed, rejected or unresolved.
The 69 absolute targets are grounded independently in original game
data/function ownership and compiler-local symbol definitions:

- Old original EH handler 0x0056918D, independently verified native
  handler prologue against the actual distinct COFF EH handler, and
  real native security cookie 0x005B25C0.
- Original file-backed float constants (zero, 0.5f, 1.0f, 2.0f,
  **4.0f**, pi, -1.0f), real animation Z default and process RNG.
- Original game BulletStyle 0x158-stride array, real current animation
  pool owner, genuine Bullet animation script callee, original
  32-byte eight-script cancellation map at 0x005AEFF8.
- Every native internal label symbol is defined at the exact original
  compiled instruction head or original first/second jump-table head;
  source labels and table word destinations are validated individually,
  not assigned by reverse-solving those table values.

The separate whole-object check first compares all **3,316/3,316
unrelocated bytes**, using only independently original physical
fields as masks. Then explicit independently anchored relocation
values are applied to those 129 real fields. The resulting entire
compiler product matches the original **3,832/3,832 bytes**. This
includes all 3,735 original code bytes, one original NOP, all 24
switch target words, compiler code after the nested two-level switch,
early return/EH setup, original real call sites and epilogue.

## Actual locked canonical exact admission and scoped replay

Canonical unit: **bullet_emitter_whole_3735** in config/match-units.toml.
Actual whole-source provider src/BulletEmitter.cpp; locked object at
build/core645-canonical/BulletEmitter.obj with an input/header/compiler
hash receipt. The genuine MSVC 19.44.35211 x86 C++20 profile is
/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc.

The unit declares size=3735 authored and compare_size=3832 for the
entire contiguous compilation contribution. It lists **all 129**
original-source-anchored relocations, including addends obtained
from the freshly compiled COFF rather than assumed from the PE
target. Running the actual repository canonical strict comparator
returns result=exact, matched_bytes **3735/3735**, and
matched_compared_bytes **3832/3832**. The independent fresh
source-scoped cold replay reports:

    bullet_emitter_whole_3735: exact (3735/3735 coverage bytes; 3832/3832 compared bytes)
    Exact replay: 1/1 units, 1 cold objects

**Only this one new native source/object was recompiled and replayed.**
No shared source/header, previously accepted original exact unit,
outside original game target, or unrelated compiler object changed.
There was **no full cold replay**, no emitted-target patch, no
generated-body hardcoding and no global binary link/runtime claim.

Private native evidence (ignored, not an invented accepted artifact):
- .analysis/core644-emitter-independent-129-anchors.py is actually
  retained as .analysis/core643-emitter-independent-129-anchors.py;
  its generated independent result is
  .analysis/core644-emitter-independently-anchored-129-native-bytes.json.
- .analysis/core644-emitter-native-60-call-proof.py/json, genuine
  original E8 physical destination cross-check in order.
- .analysis/core644-emitter-original-full-3832-byte-audit.py/json,
  true PE relocation field site and unrelocated byte census.
- .analysis/core645-emitter-whole-canonical-strict-result.json and
  .analysis/core645-bullet-emitter-targeted-cold-replay.log.
- Full pinned build/core645-canonical/BulletEmitter.obj and matching
  .receipt.json, which remain for strict canonical verification.

## Authored byte accounting and remaining whole-game work

Exactly **one new distinct full game-authored native function** is
admitted: the entire 3,735-byte Bullet emitter at original
0x004818E0. Original strict game-authored exact counts advance
from **498 functions / 175,709 bytes** to **499 functions / 179,444
disjoint original bytes**. The compiler NOP, both jump tables,
private support function EH metadata, physically folded callees,
and 63-byte separate STL library move assignment are **not**
counted as additional authored bytes. Total configured canonical
units move 1,184 -> 1,185; distinct object providers 243 -> 244;
source-present mappings stay at 1,183.

This strict native proof does **not** imply full linked game
equivalence, runtime playability, or exactness of the distinct
12,140-byte Bullet command dispatcher, 39,470-byte Animation VM,
41,967-byte Enemy dispatcher, Player main frame or movement.
