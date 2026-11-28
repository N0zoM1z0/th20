# CRT math dispatch and corrected disjoint boundaries

Four provisional spans of 42,022, 43,546, 45,698 and 48,339 bytes conflated small
math entry points with distant fallback implementations. Complete UCRT objects
resolve the actual entries for acos, atan, sin and floor. Five existing candidates
now have reviewed library origins and eleven omitted entries are inventoried.
The target remains Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

| Entry | Bytes | Independent symbol | Complete object section |
| --- | ---: | --- | --- |
| 0x0054FEB0 | 67 | `_acos` | `acos.obj` |
| 0x0054FF00 | 67 | `_atan` | `atan.obj` |
| 0x0054FFB0 | 67 | `_sin` | `sin.obj` |
| 0x005500F0 | 64 | `__floor_no_sse41` | `floor_pentium4.obj`, offset 0 |
| 0x00550130 | 32 | `_floor` | `floor_pentium4.obj`, offset 64 |
| 0x00550150 | 189 | `__floor_pentium4` | `floor_pentium4.obj`, offset 96 |
| 0x0055A1D0 | 59 | `__CIacos` | `acos_impl.obj`, offset 0 |
| 0x0055A20B | 20 | `__CIacos_default` | `acos_impl.obj`, offset 59 |
| 0x0055A21F | 183 | `__acos_default` | `acos_impl.obj`, offset 79 |
| 0x0055A840 | 59 | `__CIatan` | `atan_impl.obj`, offset 0 |
| 0x0055A87B | 20 | `__CIatan_default` | `atan_impl.obj`, offset 59 |
| 0x0055A88F | 139 | `__atan_default` | `atan_impl.obj`, offset 79 |
| 0x0055B150 | 59 | `__CIsin` | `sin_impl.obj`, offset 0 |
| 0x0055B18B | 20 | `__CIsin_default` | `sin_impl.obj`, offset 59 |
| 0x0055B19F | 147 | `__sin_default` | `sin_impl.obj`, offset 79 |
| 0x0055BD10 | 243 | `__floor_default` | `floor.obj` |

## Dispatch conditions and distinct input interfaces

The three 67-byte public entries test `__use_sse2_mathfcns` at `0x005E59AC`.
When enabled, they save MXCSR and the x87 control word to inspect the original
conditions: `(MXCSR & 0x7F80) == 0x1F80` and `(CW & 0x7F) == 0x7F`.
The temporary stack storage is released on both outcomes. Failure selects the
corresponding default entry; success tail-transfers to the Pentium4/SSE entry.
All original branches are present in the independent 67-byte contributions.

The `__CI` forms are separate 59-byte dispatchers for an argument already in
x87 ST(0). Their 20-byte default adapters save the argument, call
`__checkTOS_withFB`, and invoke the shared default algorithm after its ordinary
stack-input loading preamble. The ordinary default entry instead obtains the
double from the caller's stack through `__fload_withFB`. The complete objects
corroborate both entry styles; Ghidra's provisional thiscall signatures do not
describe these interfaces.

Each CI adapter calls into its default body's offset +9. The ledger assigns
the shared algorithm to that default body and retains the distinct adapter
head. Comparing the entire 262/218/226-byte implementation sections accounts
for the dispatchers, adapters and shared code together, without duplicate bytes.

## Default algorithms and floor's earlier compatibility entry

The acos default path preserves its endpoint, out-of-range and NaN handling,
including the x87 square-root/atan calculation and common math exits. Atan
preserves its finite, infinite and NaN branches and sign handling. Sin retains
FSIN and the repeated FPREM1 range-reduction path. All three preserve the shared
control-word, fast-exit and error-reporting destinations recorded in the private
comparison. Those external helper bodies remain separate owners.

Atan contains a five-byte `MOV EAX,1` at `0x0055A8F6` that Ghidra omitted from
its inferred body. It is present in the original and complete CRT section.
The default contribution remains 139 bytes, including that instruction; the
134-byte reachable subset is not used as its boundary.

The 32-byte floor public entry tests `__isa_available >= 2`, uses
`ROUNDSD XMM0,XMM0,9`, and returns the double through x87. Its backward fallback
edge reaches the separate 64-byte `__floor_no_sse41` entry at `0x005500F0`.
That entry uses the same MXCSR/control-word tests before selecting the 189-byte
Pentium4 implementation or the distant 243-byte default implementation.

The complete 285-byte `floor_pentium4.obj` code section contains all three
nearby entries. Its entire 80-byte constant section also agrees. The default
implementation preserves control-state save/restore, special-input
classification, the finite rounding operation and common exception-reporting
calls. Its complete 243-byte body and eight-byte 1.0 constant agree with
`floor.obj`.

## Boundary accounting and next math scope

The old Ghidra unions explain the oversized ledger spans:

- acos combines 67 entry bytes and 183 distant default bytes;
- atan combines 67 entry bytes and 134 reachable default bytes, omitting the
  five-byte instruction retained by the complete source contribution;
- sin combines 67 entry bytes and 147 distant default bytes;
- floor combines its 32-byte public entry, the earlier 64-byte compatibility
  dispatcher and the distant 243-byte default body.

The corrected ledger keeps each complete physical entry and every external
transfer. It assigns none of the intervening CRT functions to these four roots.
All eight reviewed code sections total 1,435 bytes, with no unaccounted padding
inside them. Five complete literal sections total 111 bytes. They have no owned
EH tables or trailing jump tables.

The SSE entries at `0x0055A2F8`, `0x0055A938` and `0x0055B258` remain the next
scope. Each current six-byte ledger entry is an input load that falls through
to its separately inventoried kernel. Review each complete kernel and its
intrinsic adapter together before assigning those six-byte prefixes an origin
or accepting their provisional boundaries. This review names their outgoing
roles from independent symbols without giving those rows credit.

## Evidence and validation

Private `.analysis/origin-boundary/disjoint/` retains the eight selected members
from installed `Windows Kits/10/Lib/10.0.26100.0/ucrt/x86/libucrt.lib`, attested
original listings and `reviewed.json`. The earlier
`allocation/overlapping-provisional-spans.txt` retains the original body-union
observations. `review.py` checks every byte of all eight code sections and five
literal sections, complete HIGHLOW sets, consistent shared relocation roles and
the disjoint entry partition. Pinned Capstone supplements unlisted CI/adapter
instructions and the atan gap without changing the Ghidra database.

Tracking and generated progress pass. All 2,089 protected native inputs/products
retain their hashes. No maintained native input or canonical unit changed;
exact replay scope is **zero units**, and source-present/exact credit remain
unchanged. No compiler run was needed for this archive-based origin review.
