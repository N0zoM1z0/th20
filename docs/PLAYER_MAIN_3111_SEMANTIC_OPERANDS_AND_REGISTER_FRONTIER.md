# CORE/RECON-721 — complete original Player main frame: invariant gameplay literals, object fields and seven remaining native register encodings

**Player::update_main_frame remains NONEXACT.** This whole-function immutable original PE versus genuine maintained MSVC i386 comparison independently narrows the source/ABI frontier without substituting mnemonic similarity for native byte exactness.

Original Japanese TH20 v1.00a Steamless target SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897. Original physical Player method: 0x004F9C30, **3,111B /783 i386 instructions**. Actual complete maintained src/PlayerMainFrame.cpp, compiled with pinned MSVC 19.44 i386 /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc: **3,114B /783 i386 instructions**.

## New full-body operand test: distinguish game values from codegen layout

Both original native body and newly emitted real COFF whole method have **all 783 mnemonic kinds in precisely the same ordinal order**. Decoding detailed Capstone x86 operands from the immutable original PE and the real MSVC body then yields:

| Restricted, explicitly defined operand comparison | Native original vs maintained actual C++ |
| --- | ---: |
| Total entire-function instruction heads | **783/783** in the same mnemonic order |
| Nonrelocated ordinary instruction immediate operands, excluding all relative calls/JMP/Jcc and PE/COFF relocation fields | **164/164 identical numeric values** |
| Positive game-object/child member displacements on non-stack, non-absolute memory operands, excluding all relocation fields | **67/67 identical byte offsets** |
| Real original PE HIGHLOW inside whole original 3,111B body | 37 |
| Actual real compiled COFF DIR32 inside whole candidate | 37 |
| Original direct E8 vs compiled REL32 field count | 67 / 67 |
| Previously separately proven original E8 callee roles by physical ordinal | 67/67 roles accounted for; one 555B movement child still NONEXACT |
| Whole strict native body byte exact | **NO** |

This is a **filtered semantics check**, not a full register/memory equality claim: it explicitly excludes stack-local frame slots, native absolute globals/PE relocations and relative branch/call offsets, all of which may remain different. The native original 783-instruction conditional control flow has not yet been asserted byte-exact, nor have compiled relocation field **offsets** been claimed equal merely because totals match.

The independent original checks nevertheless support the actual game field offsets and constant values in the maintained entire boss after correcting original direction script slots [1..4], the two focus-mask reads, signed speed selection, real 9x2 directional table, original time conditions and 33-history shift. There was no reason to rewrite those genuine game expressions merely to alter compiler register allocation.

## Exactly seven x86 instruction-length differences: register ownership, not a new constant

The two complete ordinal opcode streams are length-identical at **776/783** individual instructions. The remaining seven are all original-vs-compiled ADD of the same positive native member displacement into a different register:

| Original Player method offset | Original machine instruction | Current real MSVC instruction | Current minus original byte width |
| --- | --- | --- | ---: |
| +0x1A5 | ADD EAX,0x2070 | ADD EDX,0x2070 | +1B |
| +0x4CF | ADD ECX,0x654 | ADD EAX,0x654 | -1B |
| +0xA0D | ADD EAX,0x60C | ADD EDX,0x60C | +1B |
| +0xAAC | ADD EAX,0x20FC | ADD ECX,0x20FC | +1B |
| +0xB09 | ADD EAX,0x20FC | ADD ECX,0x20FC | +1B |
| +0xB7E | ADD EAX,0x12C | ADD EDX,0x12C | +1B |
| +0xBAF | ADD ECX,0x123C | ADD EAX,0x123C | -1B |
| **Net** | | **Five +1B and two -1B** | **+3B** |

These ADDs belong to genuine original Timer, AnimationHandle, 33-slot history and two option-group receiver calculations. EAX has a shorter x86 encoding for ADD accumulator-with-immediate32 than a generic register. Changing the selected register therefore changes physical bytes **even when the numerical field displacement and mnemonic kind are identical**.

**Do not conclude that exactly seven instructions are different.** The method still has many different register operands, frame-slot references and relocation/branch fields, as separately seen in the ordinal operand listing. The seven rows describe only instruction LENGTH mismatches that account arithmetically for the entire +3B footprint.

## Original compiler profile hypothesis independently tested and rejected

The full maintained Player main method was genuinely cold compiled under four separate bounded original MSVC profile probes: /fp:strict (without /sdl), /fp:precise /sdl, /fp:strict /sdl and /fp:fast /sdl. **Every whole method remained 3,114B/783 x86 with the same 317 exactly equal printed operand strings by ordinal, 67 REL32 and 37 DIR32**. Thus this specific frontier is **not** solved by toggling the float or /sdl profile. The two other whole nonexact original owners, 555B Player movement and 273B Bullet draw group, were likewise separately compiled in three /fp-/sdl configurations with unchanged code lengths. Incorrect floating-point results must not be introduced merely to imitate original registers.

Next correct step: experiment with natural original C++ receiver and temporary lifetimes at the seven identified genuine field calculations, and compare the **whole method** after each change. Do not insert no-op uses, artificial register variables, volatile, inline asm, fake game methods, or compiler-binary patches.

## Reproducible evidence and bounded scope

- .analysis/core721-player-main-native-field-operand-audit.py/json — original entire PE 3,111B/783 instructions, real entire 3,114B/783 compiled source and detailed operand comparison, 164 exact ordinary numeric immediates, 67 exact nonstack positive game-member offsets and the seven original/compiled ADD encoding differences; independently re-parses the original PE .reloc directory.
- build/core717-probes/PlayerMainFrame.obj — pinned real whole maintained Player main method compilation, full original PE bytes not edited.
- build/core718-probes/strict_fast.obj, precise_sdl.obj, strict_sdl.obj and fast_sdl.obj — four complete method compiler-profile source probes, all nonexact at 3,114B/783.
- .analysis/core703-player-main-native-script-callee-proof.py/json — previous independent all-67 original native E8 role validation from genuine original PE caller destinations.
- docs/PLAYER_MAIN_NATIVE_SCRIPT_INDICES_AND_OPTION_LOOPS_3111.md — previous correction to actual native four script slots and cached option begin/end semantics, which remain in the maintained source.

**No source, shared header, original target, canonical compiler unit, match-ledger original interval, C++ symbol or PE relocation was modified.** Player main remains noncanonical NONEXACT. The game-authored exact total is unchanged at **537 full functions /184,665 disjoint original bytes**; no global cold replay was performed.
