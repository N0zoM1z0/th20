# UCRT floating-format dispatch, layout and rounding owners

Fifteen complete Windows SDK 10.0.26100.0 x86 contributions identify pending
library origins in the locked Japanese TH20 Steamless target. Twelve cvt.obj
contributions cover the full interval `0x005585CD..0x005590FB`; three fenv
contributions supply the rounding query used by hexadecimal formatting.

| Entry | Instruction bytes | Operation |
| --- | ---: | --- |
| `0x005585CD` | 98 | IEEE double classification |
| `0x0055862F` | 178 | hexadecimal nearest/tie-even decision |
| `0x005586E1` | 828 | a/A formatting |
| `0x00558A1D` | 144 | e/E conversion wrapper |
| `0x00558AAD` | 322 | e/E internal layout |
| `0x00558BF0` | 137 | f/F conversion wrapper |
| `0x00558C79` | 224 | f/F internal layout |
| `0x00558D59` | 199 | g/G conversion and layout selection |
| `0x00558E20` | 148 | NaN/Infinity text |
| `0x00558EB5` | 52 | NUL-inclusive string shift |
| `0x00558EE9` | 147 | hexadecimal rounding policy |
| `0x00558F7C` | 384 | fp-format dispatcher |
| `0x00559A20` | 15 | fegetround |
| `0x00559A70` | 38 | common x87/SSE rounding extraction |
| `0x00559AA0` | 471 | packed floating-control snapshot |

All 3,385B/1,379 instructions agree. The complete 3,387B contributions also
retain final INT3 bytes at `0x00558BEF` and `0x00558EB4`. Every existing
instruction extent remains unchanged. The full comparisons bind 51 REL32
and 20 DIR32/HIGHLOW fields, including the complete data closure below.
The full control-flow traversal covers every instruction; Watson calls are terminal.
There is no local EH metadata in these contributions. The newly reviewed
functions use cdecl; existing register-ABI integer helpers keep their own
previous complete proofs.

## Dispatch preserves the four buffer checks and option policies

The 384B dispatcher checks result pointer, nonzero result count, scratch
pointer and nonzero scratch count. Failure caches EINVAL/22 in the supplied
PTD host and calls the real internal invalid-parameter provider; it returns
22 if that provider returns. A/E/F/G select capital output.

Options bit 0x8 bypasses modern special-value classification. Otherwise a
nonfinite value goes directly to the complete NaN/Infinity text owner.
Bit 0x10 selects three exponent digits rather than two. Without bit 0x20,
the original rounding argument is replaced by legacy mode zero; with that
bit set the supplied mode is preserved.

a/A, e/E and f/F select their complete providers. The remaining branch,
including g/G and unsupported format values, selects g formatting. The
release target has no extra unsupported-format error path. Every provider's
status is returned with its original stack cleanup and common epilogue.

## Classification and the complete special-value data closure

The 98B classifier reads the double's exponent, mantissa and sign fields.
It returns finite zero, infinity one, quiet NaN two, signaling NaN three or
indeterminate four. Indeterminate requires the original negative sign and
exact special mantissa mask; other quiet-bit NaNs remain quiet NaNs.

The text helper requires space for a basic three-character name, terminator
and optional minus. Insufficient space clears the result's first byte and
returns ENOMEM/12. A minus is emitted first; bounded counts decrease by one,
while the original unbounded SIZE_MAX count is preserved.

Its complete 64B table at `0x0059A380` contains four rows and four columns:

| Class | Long capital / short | Long lower / short |
| --- | --- | --- |
| infinity | INF / INF | inf / inf |
| quiet NaN | NAN / NAN | nan / nan |
| signaling NaN | NAN(SNAN) / NAN | nan(snan) / nan |
| indeterminate | NAN(IND) / NAN | nan(ind) / nan |

The long form is selected only when count exceeds its strlen. The real
strcpy_s copies the selected form; its unexpected error reaches the full
Watson provider, retaining the terminal call and original following INT3.

Data binding is independent of the helper's table operands. Complete literal
bytes plus their COFF four-byte alignment identify each string; this rejects
the unaligned legacy INF/NAN suffix matches. The resulting full 64B pointer
table has one location. All sixteen fields are then compared against those
independent literal addresses. The table, eight complete names and complete
`e+000` literal total 124B; eight original zero alignment bytes between known
literals are also checked. No table row or terminator is omitted.

## Decimal conversion keeps error, rounding and layout separate

The e/f/g wrappers generate digits through the independently identified
fltout and strflt-to-string providers. The original sign-space reservation,
SIZE_MAX handling, fixed/scientific precision style and trailing-digit flag
remain intact. A strflt-to-string error clears the first result byte and
returns that error.

The e internal owner keeps its strict capacity check, optional sign/decimal
insertion, g-mode shift and complete `e+000` suffix. Exponent sign and digits
come from decpt minus one, with the original zero-mantissa handling. A
two-digit minimum removes a leading exponent zero by moving three bytes,
including NUL. Locale access uses the already reviewed complete 91B updater.
The strcpy_s failure remains terminal, with the original final INT3 retained.

The f internal owner keeps the g-round-expansion placeholder, sign, leading
zero handling and the special g/zero case. Decimal insertion and fractional
zero filling use the real shift/memset owners. Shift_bytes moves strlen+1
through the real memmove whenever distance is nonzero, preserving the NUL.

g formatting generates fixed-style digits, records the magnitude before
rounding and recomputes it afterward. Magnitude below -4 or at least precision
selects e layout. Otherwise it selects f layout, removing the extra final
digit when rounding expanded the magnitude. The original >= threshold and
all cursor adjustments remain in the complete owner.

## Hexadecimal layout retains the original rounding decisions

The a owner clamps negative precision to zero, clears the initial result byte
and keeps its strict capacity check. An all-ones exponent delegates to e
formatting. If an e suffix is found, it changes that marker to p/P and trims
its zero exponent.

Finite output preserves sign, normal/denormal/zero debias choices, leading
digit, locale decimal byte, hexadecimal nibbles and carry propagation. It
emits the significand and p/P exponent; the outer output owner supplies the
0x prefix. Zero padding, absent-decimal marker and signed exponent digit
emission remain complete, including their real 64-bit helper calls.

Legacy rounding increments when the next nibble is at least eight. Standard
rounding queries fegetround. Nearest examines lower discarded mantissa bits
and uses the retained digit's parity for ties, including the first-digit
exponent case. Upward/downward use the original next-nibble-nonzero and sign
tests; toward-zero or an unrecognized mode returns false. Those directed
branches are not replaced by a new all-discarded-bits test.

## The control snapshot and common rounding query

The 471B snapshot saves x87 state with FNSTENV and immediately reloads it
with FLDENV. Its complete exception/precision/rounding/infinity normalization
and return packing remain intact. STMXCSR is behind the original signed
ISA-level >=1 check, bound to the independently reviewed ISA-level slot
`0x005E5288`. The result is the original packed value in EAX.

The 38B common extractor compares `(packed >> 14) & 0x300` with
`(packed >> 22) & 0x300`. Matching modes return that value; differing x87/SSE
modes return 0xFFFFFFFF. Fegetround passes the single 32-bit snapshot to this
extractor and returns its result. The complete 15B wrapper and every branch
of both providers agree, including the mode-mismatch result.

## Evidence and remaining digit-generation work

Private `.analysis/origin-boundary/fp-dispatch/` retains members/provenance,
scoped locations, full attested listings, independent literal/table binding,
complete comparisons, control-flow coverage and original rows. It reuses
cvt.obj and the dispatcher listing in `format-floating-owner/`, the complete
91B locale updater and the existing string/integer/invalid-parameter providers.
Installed `convert/cvt.cpp`, the floating-traits header and fenv declarations
corroborate the format and rounding roles.

The 249B strflt-to-string at `0x00562724` and its decimal rounding helpers are
now covered by the [complete decimal digit review](CRT_STRFLT_DECIMAL_ROUNDING_ORIGIN_REVIEW.md).
The separate 5,326B fltout at `0x0056281D` and shared big-integer divide are
now covered by the [complete binary-to-decimal digit review](CRT_BINARY_DECIMAL_DIGITS_ORIGIN_REVIEW.md),
including their full call, table, fraction and trailing-digit protocols.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass; all 2,151 protected native input/product hashes
are unchanged. Exact replay scope is **zero units**, with no new authored or
maintained-source exact credit.
