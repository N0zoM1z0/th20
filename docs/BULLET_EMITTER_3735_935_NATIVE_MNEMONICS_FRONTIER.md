# CORE/RECON-632 — all 935 original Bullet emitter mnemonic heads in native order

**The complete 3,735-byte game-owned BulletController::emit at 0x004818E0
remains NONEXACT.** This is a whole-function original PE analysis and
real pinned-MSVC C++ compile, not a byte-equality claim.

Reference is the independently re-attested Japanese TH20 v1.00a Steamless
resources/th20.exe with SHA-256
a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

## Original mode-12 scalar return dataflow

The original complete method has 935 native x86 instructions / 3,735 bytes.
In the mode-12 wave case, original instruction heads are:

- +0x712: call the original scalar_math::sine.
- +0x71A: call the original scalar_math::absolute on the x87 result.
- +0x722: fstp dword ptr [ebp-0x7c].
- +0x725: **movss xmm0, dword ptr [ebp-0x7c]**.
- +0x72A: **mov ecx, dword ptr [ebp+8]**, fetching ShotParameters.
- +0x72D: mulss xmm0, dword ptr [ecx+0x20], the real step amplitude.

The previous separate local declaration (const float value = abs(sin(...)))
incorrectly compiled the last two operands in reverse order:
fstp -> ShotParameters pointer mov -> movss. A previous private test
could match the native order with const volatile, but a volatile variable
had no independent semantic justification and was rejected.

Directly nesting the existing real game sine/absolute calls in the
ordinary source expression for the speed multiplier yields native
fstp -> **movss** -> **mov**, followed by mulss of the real
ShotParameters.speed_step field. This uses natural C++ float
evaluation, no volatile or compiler-shaping dummy and no target patch.
In the genuine rebuilt candidate these occur at +0x723, +0x726,
+0x72B, +0x72E, exactly one byte after original due to the still
unresolved prior extra NOP.

## Full candidate and original verification

| Measurement | Immutable original | Rebuilt whole C++ |
| --- | ---: | ---: |
| Function bytes | 3,735 | **3,736** |
| x86 instructions | 935 | **936** |
| Original mnemonic heads matched in order | 935 | **935/935** |
| Original aligned operands identical by Capstone text | — | **789** |
| Direct E8 / CXX REL32 | 60 | **60** |
| Independently mapped real original E8 callees in order | 60 | **60/60** |
| Original PE HIGHLOW / CXX DIR32 (counts only) | 69 | **69** |
| Whole original code byte exact | — | **NO** |

The additional candidate instruction is a compiler NOP at method
+0x112 (original +0x112 starts a real MOV), so the candidate has 936
instructions even though **all 935 original mnemonic kinds align
in order**. An all-mnemonic match is not complete byte equality:
the first 11 original E8 field sites are aligned but the other 49
are +1 byte, actual relocations/jump tables, EH, branch displacements,
data operands and stack lifetimes outside recovered regions still
differ. None of the 3,735 authored original bytes is admitted exact
on the basis of this structural score.

## Scoped real compiler validation

- .analysis/core631-emitter-temporary-lifetime-nop-probes.py and .json:
  fourteen whole-parent natural source trials. Relocating unused base/speed
  declarations does not remove the NOP. Direct inline sine/absolute
  expression, unlike the detached value local, restores original mode-12
  order and 935/935 instruction alignment.
- build/core632-probes/BulletEmitter.obj:
  freshly compiled actual src/BulletEmitter.cpp under pinned MSVC x86
  /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc.
- .analysis/core632-emitter-mode12-maintained-native-proof.json:
  independent whole PE-to-COFF disassembly, physical native sequence and
  instruction/relocation type counts.
- .analysis/core632-emitter-native-60-call-proof.py and corresponding JSON:
  all sixty original E8 destinations independently mapped in original
  ordinal order to newly rebuilt COFF relocated symbols.

**Affected canonical replay scope: zero units.** src/BulletEmitter.cpp
remains noncanonical and has no configured match-unit provider.
No accepted unit's native source/header/profile changed; no global
cold replay was run. The source still needs a natural, evidence-backed
solution to the extra NOP and full byte/relocation exactness.
