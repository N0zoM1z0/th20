# x86 integer-helper origins, boundaries and result registers

Eight pending native candidates, totaling 1,024 bytes, are complete CRT integer
helpers. Each full body equals its corresponding complete object contribution in
the installed MSVC 14.44.35207 x86 `libcmt.lib`, without relocation masking. They
are classified as library exclusions. The locked comparison target remains
Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

| Entry | Bytes | Instructions | CRT symbol | Archive member |
| --- | ---: | ---: | --- | --- |
| 0x00543050 | 170 | 70 | `__alldiv` | `lldiv.obj` |
| 0x00543100 | 52 | 19 | `__allmul` | `llmul.obj` |
| 0x00543140 | 178 | 69 | `__allrem` | `llrem.obj` |
| 0x00543200 | 104 | 43 | `__aulldiv` | `ulldiv.obj` |
| 0x00543270 | 117 | 44 | `__aullrem` | `ullrem.obj` |
| 0x005432F0 | 31 | 15 | `__allshl` | `llshl.obj` |
| 0x005672F0 | 149 | 58 | `__aulldvrm` | `ulldvrm.obj` |
| 0x00567390 | 223 | 91 | `__alldvrm` | `lldvrm.obj` |

The previously excluded 31-byte `__aullshr` at `0x00542E90` also agrees with its
whole `ullshr.obj` contribution. Its ledger row remains unchanged and receives
no second review credit.

## Complete control flow and native ABI

The multiplication, divide and remainder helpers take two 64-bit operands on the
stack and remove sixteen argument bytes at return. The signed division paths
normalize signs, select the small-divisor or normalized-divisor algorithm,
correct an overestimated quotient and restore the result sign. The signed
remainder follows the dividend's sign. Unsigned remainder preserves the full
quotient-product correction and subtraction. Multiplication uses one fast path
when both high words are zero and otherwise combines the low-word product with
the two cross products; the same low 64-bit result serves signed and unsigned
multiplication.

The combined divide/remainder routines have two register-pair outputs:
**EDX:EAX is the quotient, EBX:ECX is the remainder**. Their native register
shuffles and CRT source comments independently agree. EBX is therefore an
output, even though ordinary x86 C++ conventions normally preserve it. A normal
C++ function declaration with one scalar return would misdescribe these entry
points. No maintained callable wrapper or replacement source is added here.

The left-shift helper takes its value in EDX:EAX and count in CL. It explicitly
separates counts below 32, 32 through 63, and at least 64. The last group returns
zero; the middle group moves the old low word to EDX and masks CL to five bits.
This protocol must not be inferred from a C++ expression with an out-of-range
shift count.

All 409 instructions of the eight new entries were read in the complete attested
listing. Every body decodes contiguously from entry to ledger end. Direct branch
targets stay inside the corresponding body and each exit is a real RET. There
are no callees, distant shared tails, jump tables, COFF relocations or native
HIGHLOW fields in these bodies. Every byte agrees with the complete CRT object,
including relative branch displacements. Adjacent linker alignment gaps remain
outside the candidates; no extent is shortened.

## Evidence and validation

The shipped CRT sources under
`.tools/msvc/VC/Tools/MSVC/14.44.35207/crt/src/i386/` corroborate operand layout,
return registers and signedness. Each archive member has an independent public
symbol and full code-section extent. The library SHA-256 and member/body hashes
are captured privately in
`.analysis/origin-boundary/integer-abi/member-comparisons.json`. Extracted
objects and the bounded audit script remain beside it. They are origin evidence,
not newly compiled reconstruction products.

The full attested listing is
`.analysis/origin-boundary/integer-abi-helpers.txt`. It can be reproduced with
`nice -n 15 scripts/repo-python scripts/ghidra.py query`, operation
`disassemble 250`, followed by the table's addresses. The private
`integer-abi/compare-members.py` compares the whole members, checks listing
coverage and verifies the absence of original relocation fields.

Only these eight classification rows, progress and review notes change. Source,
headers, canonical manifests, match records and compiler products are unchanged;
the affected exact replay scope is **zero units**. Tracking and generated
progress checks pass, and the existing protected input/product hashes agree.
This classification adds no authored or canonical exact credit.
