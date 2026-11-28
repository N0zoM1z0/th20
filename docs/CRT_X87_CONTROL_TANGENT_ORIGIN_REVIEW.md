# CRT x87 control, tangent and shared exits

The public CRT entry at `0x00550000` computes **tan**, while `_sqrt` begins at
`0x00550050`. Complete SDK archive sections establish those identities. This
corrects three maintained float adapters whose ordinary bytes agreed even with
incorrect external symbol names. The review also resolves the false 755-byte
span at `0x0055B518` and classifies seventeen entries as library code, including
six previously missing heads.

The scope is the locked Japanese TH20 v1.00a Steamless executable, Windows SDK
10.0.26100.0 x86 `libucrt.lib`, and the existing attested Ghidra project. Private
evidence is under `.analysis/origin-boundary/x87/`: `native.txt`,
`tangent-and-exits.txt`, extracted archive members, `review.py` and
`reviewed.json`. Pinned Capstone supplements instructions absent from Ghidra's
listing; it does not change the database.

## Complete boundaries

| Entry | Bytes | Archive symbol / role | Member |
| --- | ---: | --- | --- |
| `0x00550000` | 67 | `_tan` public dispatcher | `tan.obj` |
| `0x00550050` | 14 | `_sqrt` public entry | `sqrt.obj` |
| `0x0055B410` | 59 | `__CItan` intrinsic dispatcher, recovered head | `tan_impl.obj` |
| `0x0055B44B` | 20 | `__CItan_default`, recovered head | `tan_impl.obj` |
| `0x0055B45F` | 151 | `__tan_default` | `tan_impl.obj` |
| `0x0055B500` | 24 | `__CItan_pentium4` | `tan_pentium4.obj` |
| `0x0055B518` | 6 | `__tan_pentium4` stack-input head | `tan_pentium4.obj` |
| `0x0055B51E` | 564 | shared tangent kernel, object local start label | `tan_pentium4.obj` |
| `0x0055B760` | 21 | `__twoToTOS`, recovered head | `common.obj` |
| `0x0055B775` | 23 | `__load_CW` | `common.obj` |
| `0x0055B78C` | 25 | `__convertTOStoQNaN` | `common.obj` |
| `0x0055B7A5` | 67 | `__fload_withFB` | `common.obj` |
| `0x0055B7E8` | 22 | `__checkTOS_withFB` | `common.obj` |
| `0x0055B7FE` | 13 | `__fast_exit`, recovered head | `common.obj` |
| `0x0055B80B` | 42 | `__math_exit` | `common.obj` |
| `0x0055B835` | 20 | `__check_overflow_exit`, recovered head | `common.obj` |
| `0x0055B849` | 163 | `__check_range_exit`, recovered head | `common.obj` |

The nine common entries partition the complete 396-byte section. The overflow
entry jumps into the range exit at `+0x14`; that shared tail remains owned once.
The tangent implementation section is 230 bytes (59 + 20 + 151). Its Pentium4
section is 608 bytes: three partitions totaling 594 bytes plus fourteen original
assembler alignment bytes at `0x0055B752`:
`8B FF 8D A4 24 00 00 00 00 EB 03 CC CC CC`.
The sequence is MOV EDI,EDI, LEA ESP,[ESP], a jump over three INT3 bytes, and
ends immediately before `__twoToTOS`. It is retained in the section comparison.

The six-byte head loads XMM0 and falls into the kernel. Its previous convex
755-byte span crossed the kernel, alignment and several independent common
helpers. The shared kernel also uses the original stack argument view and
returns through x87; the intrinsic head creates that view from ST(0). A simple
one-register C prototype would omit part of this interface.

All seventeen entries total 1,301 code bytes. The five complete literal/table
sections total 5,929 bytes: `common.obj` 68B at `0x0059A920`, `tan_impl.obj` 7B
at `0x0059A870`, `tan_pentium4.obj` 160B at `0x0059A880`, `tan_tables.obj`
5,632B at `0x005A0FE0`, and `87disp.obj` 62B at `0x0059D890`.
`reviewed.json` records full ordinary-byte agreement, the complete HIGHLOW field
sets, archive relocation roles and consistent shared placements for every code
and data section. These archive comparisons establish origin and boundaries;
they add no maintained-source exact credit.

## Shared control and error contracts

`__load_CW` reads the caller's saved control word through its private stack
contract, preserves precision bits `0x300`, adds `0x7F`, stores and loads the
modified word. `__twoToTOS` uses FRNDINT, F2XM1 and FSCALE. Neither helper should
be reconstructed from an invented ordinary C calling convention.

`__fload_withFB` receives a double pointer in EDX. Finite inputs use FLD64.
For exponent `0x7FF`, it builds an extended representation and uses FLD80,
preserving the original high word in EAX and reporting the special class with
ZF set. `__checkTOS_withFB` classifies the saved double high word at `[ESP+8]`
without consuming ST(0), also returning the classification in flags/EAX.
`__convertTOStoQNaN` tests the quiet bit, conditionally adds the shared One
constant, and clears EAX. These flag results matter to the tangent fallback.

`__fast_exit` restores the saved control word when it differs from `0x27F`,
removes the saved slot and returns. `__math_exit` retains the precision/status
checks and one-argument error path. The complete range exit checks overflow and
underflow, applies the original scaling and min/max constants, and chooses the
two-argument helper for EDX `0x1D`; otherwise it uses the one-argument helper.
Their independently named destinations are `0x005640A0` and `0x005640B7`.
Those error-handler bodies remain a useful next review scope.

## Correcting semantic bindings

The 67-byte public dispatchers share their ordinary opcode shape. A masked
shape search alone therefore cannot distinguish acos, atan, cos, sin and tan.
`tan.obj` names both outgoing REL32 roles; the complete default body contains
FPTAN (`D9 F2`) at `0x0055B47D`, argument reduction and the original error exits.
Its SSE fallback, coefficients and full 5,632-byte tangent table corroborate the
identity. The independent fourteen-byte `sqrt.obj` contribution matches
`0x00550050`, with calls/tails to `__fload_withFB` and `__sqrt_common`.

| Float adapter | Correct source call | Correct CRT destination | Previous error |
| --- | --- | --- | --- |
| `0x00439850` | `std::tan(double)` | `_tan`, `0x00550000` | sqrt |
| `0x00439760` | `std::acos(double)` | `_acos`, `0x0054FEB0` | asin |
| `0x00439790` | `std::atan(double)` | `_atan`, `0x0054FF00` | acos |

The acos/atan identities were independently established by the
[complete disjoint math sections](CRT_MATH_DISPATCH_ORIGIN_BOUNDARY_REVIEW.md).
The camera distance is integer-halved viewport height divided by tan(FOV/2), consistent
with the corrected tangent call. Animation VM opcodes `0x20`, `0x21`, `0x22`
call these same three owners. The separate ScalarMath square-root adapter at
`0x00446B30` already called the true `_sqrt` and retains that binding.

The source bodies, names and canonical relocations now agree with this
evidence. The three adapter origins remain unknown/review; no authored head or
byte is added. The old wrong-symbol objects/receipts remain intact as evidence.

## Affected validation

Captured include closures identify 82 units using `ScalarMath.hpp`, plus the
camera and tangent adapter: **84/84 complete canonical units passed from 31
fresh locked-compiler objects**, including full owned extents and relocations.
The two previous ScalarMath providers had identical profiles and now share one
fresh provider. All output paths are under `build/gpt61-origin-tangent-canonical/`.
The before/after scopes and replay log are in
`.analysis/origin-boundary/tangent-binding/`.

The NONEXACT Animation VM was compiled before and after the correction with
the same locked profile. Its complete 39,764-byte contribution (39,124 code +
640 switch bytes), 505 direct calls, and all four runtime sections agree after
exactly the three intended external-name substitutions. This is a consumer
regression check, with no VM exact credit. See `consumer-comparison.json`.

Both public camera verifiers pass. The tangent verifier also rejects the old
sqrt-backed object despite its identical 31 ordinary bytes. The 64 superseded
canonical objects/receipts in the captured affected scope retain their hashes.
Of the earlier 2,089 protected files, only the seven intended source/header/
manifest inputs changed or moved; the other 2,082 retain their hashes. A new
`protected-hashes-tangent.json` retains current inputs and fresh products while
preserving the earlier baseline.
