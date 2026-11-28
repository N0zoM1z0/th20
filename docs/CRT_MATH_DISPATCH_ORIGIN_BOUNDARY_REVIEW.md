# CRT math dispatch and corrected disjoint boundaries

Four provisional spans of 42,022, 43,546, 45,698 and 48,339 bytes conflated small
math entry points with distant fallback implementations. Complete UCRT objects
resolve the actual entries for acos, atan, sin and floor. The dispatchers,
default implementations and complete SSE entry/kernel groups have reviewed
library origins; eleven omitted entries are inventoried.
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

## Boundary accounting

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

## Complete SSE entry/kernel groups

The nine SSE entries below also have reviewed library origins. Their three
complete Pentium4 objects contain 2,532 bytes: 2,530 code bytes and two original
NOPs. All entry styles and shared bodies are compared together.

| Group | Intrinsic adapter, 24B | Stack-input head, 6B | Shared kernel | Whole code section |
| --- | --- | --- | --- | ---: |
| acos | 0x0055A2E0 | 0x0055A2F8 | 0x0055A2FE, 1,334B | 1,364B |
| atan | 0x0055A920 | 0x0055A938 | 0x0055A93E, 681B | 712B |
| sin | 0x0055B240 | 0x0055B258 | 0x0055B25E, 425B | 456B |

The adapters have independent symbols `__CIacos_pentium4`,
`__CIatan_pentium4` and `__CIsin_pentium4`. Each saves EBP, reserves storage,
aligns ESP to 16 bytes, consumes ST(0) into a double temporary and loads the
input register before calling its shared kernel. LEAVE restores the original
stack after the call. The ordinary `__acos_pentium4`/`__sin_pentium4` heads load
the stack argument into XMM0; `__atan_pentium4` loads XMM7. Those six-byte heads
fall through into the same kernels.

The six-byte ledger spans are entry partitions with explicit shared fallthrough,
and each kernel has one physical owner. Internal entry is not a general vector
calling convention: special-result paths also read the original stack argument,
and results return through x87. The intrinsic adapters create that stack view
before their internal call. The descriptive `$shared_kernel` ledger names refer
to each object's local `start` label at code-section offset 30.

The complete acos kernel retains table-assisted evaluation, endpoint/invalid
branches and the call to `__libm_error_support` at `0x0055BA70`. Atan retains its
table evaluation, tiny-value arithmetic and special-input returns. Sin retains
its table-assisted path and the final large-input transfer to the already
reviewed `__sin_default` at `0x0055B19F`. The full atan and sin sections end with
one NOP each at `0x0055ABE7` and `0x0055B407`; these bytes remain compared
outside their kernel code counts.

All three complete local constant sections agree: acos 288B, atan 336B and sin
160B. Independent provider objects also identify and match every byte of the
four shared tables:

| Original address | Bytes | Provider and symbol |
| --- | ---: | --- |
| 0x0059D8D0 | 3,840 | `acos_asin_tbl_addr.obj`: `___acrt_acos_asin_tbl_addr` |
| 0x0059E7D0 | 2,048 | `acos_asin_t_table.obj`: `___acrt_acos_asin_t_table` |
| 0x0059EFD0 | 6,160 | `atan_table.obj`: `__atan_table` |
| 0x005A07E0 | 2,048 | `cos_sin_ctable.obj`: `___acrt_cos_sin_ctable` |

The seven complete constant/table sections total 14,880 bytes. They are shared
data evidence and receive no function-code credit. No owned EH or jump-table
extent is omitted from these code sections.

## Evidence and validation

Private `.analysis/origin-boundary/disjoint/` retains the eight selected members
from installed `Windows Kits/10/Lib/10.0.26100.0/ucrt/x86/libucrt.lib`, attested
original listings and `reviewed.json`. The earlier
`allocation/overlapping-provisional-spans.txt` retains the original body-union
observations. `review.py` checks every byte of all eight code sections and five
literal sections, complete HIGHLOW sets, consistent shared relocation roles and
the disjoint entry partition. Pinned Capstone supplements unlisted CI/adapter
instructions and the atan gap without changing the Ghidra database.

The additional Pentium4 and table members are retained beside those objects.
`sse-native.txt` contains the bounded attested adapter/kernel listings;
`reviewed-sse.json` records the whole sections, observed relocation roles and
supplementary decoding. `review-sse.py` checks all three full code sections,
both NOP bytes, all seven constant/table sections, complete HIGHLOW sets and
instruction coverage. Their origin comparisons do not create canonical units.

Tracking and generated progress pass. All 2,089 protected native inputs/products
retain their hashes. No maintained native input or canonical unit changed;
exact replay scope is **zero units**, and source-present/exact credit remain
unchanged. No compiler run was needed for this archive-based origin review.
