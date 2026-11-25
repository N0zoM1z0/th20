# 5,993B Animation Draw Boss: mode35/36 Ghidra local and x87 evidence

**Status: semantic/native evidence only; parent remains SOURCE-PRESENT, NONEXACT.**
This note pins the original decompiler's mode35/36 expression order against the
original PE instruction stream and the current scalar-C++ compiler probes. It
does not promote any parent bytes or change `src/AnimationDrawBoss.cpp`.

## Original decompiler context

The original `0x00443880` function decompiles its nested mode switch as follows
(the native PE is SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`):

```cpp
case 0x23:
    FUN_00445880((int)param_1);              // first result discarded
    fVar6 = (float)FUN_004456C0((int)param_1);
    fVar7 = (float)FUN_004456E0((int)param_1);
    iVar2 = *(int *)((int)param_1 + 0x444);
    fVar9 = local_1c / DAT_0056c8d0;          // half-height before second getter
    fVar8 = FUN_00445880((int)param_1);
    FUN_0043C780(..., (float)fVar8 + fVar9,
                 local_1c / DAT_0056c8d0 + local_20, ...);
    break;

case 0x24:
    FUN_00445880((int)param_1);              // first result discarded
    fVar6 = (float)FUN_004456C0((int)param_1);
    fVar7 = (float)FUN_004456E0((int)param_1);
    iVar2 = *(int *)((int)param_1 + 0x444);
    fVar9 = local_1c / DAT_0056c8d0;          // half-height before second getter
    fVar8 = FUN_00445880((int)param_1);
    FUN_0043C780(..., (float)fVar8 - fVar9,
                 local_20 - local_1c / DAT_0056c8d0, ...);
    break;
```

The decompiler's `float10 fVar8` is its representation of an x87 return value,
not evidence for an MSVC `long double` declaration. The 93B recursive helper at
`0x00445880` has already been independently reconstructed as a natural C++
`float` function with a strict canonical replay. The decompilation also makes
the evaluation order explicit: first getter; packed colors; count; half-height;
second getter; adjusted-scale and width expressions.

## Original x86 details

Mode35's relevant original instructions are:

```asm
0FC8  call 0x445880
0FCD  fstp  dword ptr [ebp-0x160] ; first result, never read later
0FD6  call 0x4456c0              ; color494
0FE4  call 0x4456e0              ; color490
0FFE  movss xmm0, [ebp-0x18]
1003  divss xmm0, [0x56c8d0]
100E  movss [ebp-0x14c], xmm0    ; fVar9 / half-height
1016  call 0x445880              ; second result
101B  fstp  dword ptr [ebp-0x148]
1021  movss xmm0, [ebp-0x148]
1029  movss xmm1, [ebp-0x14c]
1031  addss xmm0, xmm1
1035  movss [ebp-0x15c], xmm0
```

Mode36 has the corresponding original sequence:

```asm
10B5  call 0x445880
10BA  fstp  dword ptr [ebp-0x160] ; first result, never read later
10C3  call 0x4456c0              ; color494
10D1  call 0x4456e0              ; color490
10EB  movss xmm0, [ebp-0x18]
10F0  divss xmm0, [0x56c8d0]
10FB  movss [ebp-0x168], xmm0    ; fVar9 / half-height
1103  call 0x445880              ; second result
1108  fstp  dword ptr [ebp-0x164]
110E  movss xmm0, [ebp-0x164]
1116  movss xmm1, [ebp-0x168]
111E  subss xmm0, xmm1
1122  movss [ebp-0x178], xmm0
```

The native stack slot `[ebp-0x160]` is written exactly twice, at `+0x0FCD`
and `+0x10BA`. A complete decoded-body operand scan finds no later read of
that slot. This is a real write-only x87 spill in the original code, although
the original source-level name/ownership of the dead local is not recovered.
The two adjusted-scale operations are register-register (`addss`/`subss`), and
the width half-height is independently recomputed later in each renderer
argument sequence.

## Natural C++ probe frontier

A current-source-derived probe with one function-scope
`[[maybe_unused]] float first_inherited_scale`, assigned by the first getter in
both modes, recovers both `fstp [ebp-0x160]` stores. With a value-equivalent
half-height role swap it also recovers both register-register adjusted-scale
instructions. It retains the current mode45/46 source and compiles to:

| Measure | Maintained source | Current spill probe |
| --- | ---: | ---: |
| Function code | 5,993B | 5,989B |
| Ordinary bytes | 4,840/5,376 | 3,801/5,372 |
| Physical E8 positions | 114/123 | 89/123 |
| First getter spill | 0/2 | 2/2 |
| Adjusted-scale register form | 0/2 | 2/2 |

The first 88 physical E8 sites match in the spill probe. From the mode36
renderer call at native `+0x1198`, all later E8 sites are four bytes early.
The reason is isolated: the probe reuses its pre-getter half-height local for
the width argument, while native mode36 recomputes `height / 2` after
adjusted-scale and uses the newly computed value with `width` in XMM1. This
shorter direct-memory width subtraction removes four bytes. A double
float-to-double-to-float round trip adds the displacement back but is not an
original operation and is rejected.

A native-order source variant stores the half-height local before the second
getter and recomputes width after it, but MSVC emits the adjusted-scale
subtraction as `subss xmm0, [half]` rather than the original
`movss xmm1, [half]; subss xmm0, xmm1`. Declaration order, mutability, copy,
reference and volatile scalar probes do not change that selection. `/fp:fast`,
`/fp:strict` and `/fp:precise` all produce the same code. Moving the half,
inherited-scale and adjusted-scale declarations to the start of each case while
keeping their assignments in the native evaluation order also leaves the
same stack operands and E8 positions. SSE intrinsic variants change
stack/register allocation and contribution shape and are rejected.

No candidate currently preserves the original dead spill, both register
operands, original width evaluation, the full 5,993B extent and the maintained
source's E8 sequence together. The production source remains unchanged and
the parent receives zero new exact credit. The next source experiment should
focus on natural local declaration/ownership that makes the native half-height
reload materialize in XMM1 without changing the later width recomputation.
