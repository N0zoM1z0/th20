# CORE/RECON-630 — original mode-11 heading operands in the 3,735-byte Bullet emitter

**Status: the complete original BulletController::emit at 0x004818E0 remains NONEXACT.**
This investigation compares the independently verified TH20 Japanese v1.00a
Steamless original (resources/th20.exe, SHA-256
a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897)
with genuine pinned-MSVC x86 whole-method C++ builds. Aligned mnemonics
and operand identity are evidence, not exact-byte credit.

## Independently observed original instructions

The native pattern-11 path first saves the circular angle to [ebp-0x6C] at
+0x5F0, reloads it at +0x5F5, and copies it into the mutable heading at
[ebp-0x24] at +0x5FA. Crucially, both original trigonometric calls
receive the **heading** slot:

- +0x600: movss xmm0, [ebp-0x24] before cosine at +0x60A.
- +0x628: movss xmm0, [ebp-0x24] before sine at +0x632.

The original cosine x87 return is stored at +0x612 then multiplied with
shot.speed into [ebp-0x44]. The original sine result at +0x63A is
multiplied with shot.speed_step into [ebp-0x48]. Subsequent calls are
the genuine game geometry norm and arctangent.

The previous maintained C++ used the numerically equivalent but distinct
circle_angle variable as the trigonometric parameter. Under pinned MSVC
/Od, this kept a different angle slot alive at [ebp-0x34], shifted
other native locals and mismatched operand origins. Replacing both
calls with cosine(heading) and sine(heading) reestablishes the original
[ebp-0x6C] circular-angle temporary, [ebp-0x24] trig argument,
and [ebp-0x44]/[ebp-0x48] products. This follows actual original
dataflow, without an artificial volatile variable, inline assembly
or any target/COFF patch.

## Full-function native comparison

Eight distinct complete C++ method builds were probed, including
baseline, cosine-only, sine-only, both-heading, heading-copy, separate
assignment and const-local forms. This is a complete whole-parent
comparison, not a toy function.

| Whole-method evidence | Previous source | Corrected source |
| --- | ---: | ---: |
| Original method | 3,735B / 935 x86 | same |
| Pinned C++ method | 3,736B / 936 x86 | **3,736B / 936 x86** |
| Original ordered mnemonics aligned | 934/935 | **934/935** |
| Same operand text among aligned heads | 747 | **788** |
| Original E8 / C++ REL32 | 60 / 60 | **60 / 60** |
| Original physical E8 targets correct in order | 60/60 | **60/60** |
| Original PE HIGHLOW / candidate DIR32 by count | 69 / 69 | **69 / 69** |
| Original whole-parent strict exact | NO | **NO** |

Sine(heading) is the important natural source change for matching
the original intermediate local allocation. Both trig sources use
heading in the maintained code because both original physical call
argument loads establish this independently. The 747 to 788 count
uses Capstone mnemonic alignment plus displayed operand equality;
unlinked COFF relocation placeholders differ from absolute PE targets.
This is **not a byte-exactness percentage**.

Remaining blockers include a compiler-emitted NOP at +0x112 absent
from original (49 later E8 field positions drift +1 byte), different
mode-12 scalar return/ShotParameters read ordering, complete field-site
identity, frame local offsets, EH and the two original switch tables.
The entire 3,735B gameplay boss is still NONEXACT.

## Verification artifacts and replay boundary

- .analysis/core629-emitter-mode11-operand-source-probes.py and .json —
  eight source variants compared against the immutable complete PE body.
- .analysis/core630-emitter-maintained-mode11-native-proof.json —
  actual final maintained source built and independently decoded.
- .analysis/core630-emitter-native-60-call-proof.py and corresponding JSON —
  newly rebuilt source checked against all 60 original real PE E8
  physical destinations and independent known-symbol identities.
- build/core630-probes/BulletEmitter.obj — ignored pinned compiler
  build with /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc.

**Replay scope is zero configured canonical match units:** the changed
src/BulletEmitter.cpp is not a canonical-unit provider. A filtered request
explicitly reports this source as unconfigured, rather than running a
global cold replay. No public headers, previously exact sources or
canonical receipt inputs changed. Game-authored exact totals stay fixed.
