# UCRT SSE log10 entries, data and return contracts

Four disjoint entries belong to the complete SDK 10.0.26100.0 x86
log10_sse2_precise.obj and log10_pentium4.obj contributions in the locked
Japanese TH20 Steamless target. Their full 1,344B consists of 1,319B/296
instructions and 25B of original alignment. All 42 relocation roles (three REL32 and 39 DIR32)
and the complete 2,592B of constants/tables are reviewed. Existing extents
remain unchanged; the six-byte stack-input entry was missing from the ledger.

| Entry | Instruction bytes | Symbol / role | Return contract |
| --- | ---: | --- | --- |
| `0x00566030` | 675 | `__libm_sse2_log10_precise` | XMM0 input/result |
| `0x00566A30` | 24 | `__CIlog10_pentium4` | ST(0) input/result |
| `0x00566A48` | 6 | `__log10_pentium4` | stack double input, ST(0) result |
| `0x00566A4E` | 614 | local start / shared kernel | XMM0 and original stack view, ST(0) result |

The descriptive ledger name `__log10_pentium4$shared_kernel` identifies the
object's local start at offset 30. Its code is owned once. It is not an
independent C export or a general one-register function interface.

## The entry paths keep different floating return interfaces

The precise owner saves MXCSR, requires `(MXCSR & 0x7F80) == 0x1F80`, then
checks `(CW & 0x7F) == 0x7F`. A failed check stores its XMM0 argument to the
temporary stack slot, calls the reviewed x87 log10 default, consumes its ST(0)
result with FSTP and reloads XMM0 before returning. The normal and error paths
also return in XMM0. The fltout caller's real register transfers corroborate
this interface.

The 24B CI adapter reserves storage, aligns ESP to sixteen bytes, consumes
its ST(0) argument into a double temporary and loads XMM0 before calling the
shared kernel. LEAVE restores the unaligned stack after the call. The separate
six-byte ordinary head loads XMM0 from `[ESP+4]` and falls into the same kernel.
The kernel's special paths still read that original stack argument. Its normal
result is stored to a temporary and loaded into ST(0); its error path likewise
loads the possibly changed result from memory into ST(0).

## Full reduction, split tables and polynomial evaluation

Both implementations preserve sign/exponent extraction, duplication of the
input lane, mask/OR construction of a normalized mantissa, table-assisted
reduction and high/low argument splitting. Their complete coefficient
evaluation and split log10(2) exponent correction retain the original lane
selection and addition order. The zero-combined-index mask selection remains
part of each body; no arithmetic is replaced by a host log10 call.

| Data | Address | Full bytes |
| --- | --- | ---: |
| observed precise constants | `0x005A2650` | 256 |
| observed Pentium4 constants | `0x005A2FE0` | 256 |
| log10 high/low table | `0x005A27B0` | 1,040 |
| duplicated reduction factors | `0x005A2BC0` | 1,040 |

Each table contains 65 complete sixteen-byte rows, including the final row.
The first high/low pair is zero and the last is the full split log10(2)
constant. Each reduction-factor row has equal lanes; the endpoints are the
local CC value and CC/2.

The table offset is bounded by the native bit construction. The normalized
mantissa is in [1,2), and Magic is exactly `2^42 - 127/128`. Adding those
endpoints bounds the rounded low-word index from 8 through 1032, at a double
spacing of `2^-10`. Mask `0x7F0` therefore selects offsets 0 through 1024
in sixteen-byte steps. This exact bit/fraction inference accounts for all
65 rows; it is not a runtime numerical-accuracy experiment.

## Denormal, zero, infinity and NaN paths remain complete

Denormal handling keeps the multiply by 2^52, exponent adjustment -52 and
retry into reduction. The original special classification reads the saved
argument and checks sign, exponent and mantissa. Positive infinity loads the
positive-infinity constant. Zero performs the original division and uses
negative infinity with error code 8. Negative-domain input retains the zero
divided by zero operation and code 9. NaNs use code 1001.

Both error paths pass real argument/result pointers to the now reviewed void
libm_error_support. They retain its callback/errno behavior and reload the
result using their own return interface. Neither treats the callback bridge
as nonreturning or substitutes a new NaN payload or error policy.

The precise contribution ends with two original LEAs totaling 13B at
`0x005662D3`. The Pentium4 contribution retains twelve bytes at `0x00566CB4`:
LEA ESP,[ESP], a jump to `0x00566CC0` and three INT3 bytes. These alignment
bytes are compared with their whole contributions rather than credited as
additional function instructions. There is no owned EH or embedded jump table.

## Origin evidence and the remaining canonical bank limit

The two private 256B banks are byte-identical. Complete code, full data,
native relocation roles, entry/return contracts and control flow establish
the library origins. The linked bank instances in the table above come from
native operands; duplicated contents alone do not independently select those
addresses for a future canonical source unit. The earlier pending review is
now resolved at the origin/boundary level, while that canonical binding limit
is retained. No canonical unit or exact receipt is created.

Private `.analysis/origin-boundary/log10-sse/` retains the full code/data
comparisons, bounded attested listing, unlisted six-byte head, both alignment
sequences, complete control-flow coverage and the labelled table-index
inference. It reuses members/locations in `fp-fltout/` and `log10-ceil/`.
The matching implementation source is absent from the installed snapshot;
complete archive/native bodies and the reviewed callers supply the evidence.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
