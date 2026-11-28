# UCRT libm error records, callbacks and full switch ownership

The 539B/143-instruction entry at `0x0055BA70` is
`___libm_error_support` from SDK 10.0.26100.0 x86 libm_error.obj. Its whole
660B contribution also contains one NOP, fifteen case pointers and sixty
selector bytes. Complete ordinary bytes, both REL32 fields and all 37 DIR32 roles,
every selector and all case destinations agree in the locked Japanese TH20
Steamless target. The existing instruction extent stays unchanged.

The NOP is at `0x0055BC8B`, the 60B pointer table at `0x0055BC8C`, and the
60B selector table at `0x0055BCC8`. Both tables remain part of this owner.
Twelve original INT3 bytes follow at `0x0055BD04..0x0055BD0F`, before the
reviewed floor default. There is no local EH table.

## Void interface and the original callback record

CodeView establishes `void __cdecl`, three 32-bit void pointers and a signed
32-bit error_types enum. The pointers supply two double arguments and the
result location; an EAX value at return is not a function result. The complete
32B `_exception` layout has type/name at offsets 0/4, arguments at 8/16 and
retval at 24. Installed corecrt_math.h independently corroborates that layout
and exception-type constants.

When the observed four-byte flag at `0x005E5894` is zero, the callback is the
already reviewed `___acrt_invoke_user_matherr` at `0x00555940`. Otherwise the
function decodes the common four-byte pointer at `0x005E59A8` through the
PE-named KERNEL32!DecodePointer import at `0x0056C19C`. These cells are zero
in the PE's virtual tail. The function reads them without initializing them;
their runtime writer is not established here. The member's separate 43B
libm setter has no complete target location and receives no credit.

Each actual callback uses the original guard slot at `0x0056C37C`, passes
the initialized exception record and copies its possibly changed retval back
to the supplied result pointer. Domain and range paths test the callback's
integer return; a nonzero result suppresses the function's errno fallback.
Underflow ignores that return value and has no errno fallback of its own.
No pointer validation, record clearing or replacement error path is added.

## Every switch selector is accounted for

The sixty-byte map covers codes 2 through 61 and selects all fifteen case
labels. CodeView's 188 enum entries identify the actual selected cases:

| Codes | Operation | Record / fallback |
| --- | --- | --- |
| 2, 8 | log/log10 of zero | singularity; errno 34 if unhandled |
| 3, 9 | negative log/log10 | domain; errno 33 if unhandled |
| 14, 24 | exp/pow overflow | overflow; errno 34 if unhandled |
| 15, 25 | exp/pow underflow | underflow; no callback-result test or errno fallback |
| 26 | pow zero to zero | store the original 1.0 constant; no callback |
| 27 | pow zero to a negative power | singularity; errno 34 if unhandled |
| 28, 49, 58, 61 | negative pow base/noninteger exponent, negative sqrt, acos/asin outside range | domain; errno 33 if unhandled |

All remaining selectors reach the real default epilog. The signed comparison
with 1000 and subsequent unsigned range check remain intact. Codes 1000/1001
(log_nan/log10_nan) copy the first double argument to the result without
arithmetic. Other out-of-range codes return without that copy. In particular,
the enum names exp_nan, atan_nan and ceil_nan do not imply a handled branch
in this body. Existing ceil's `0x3EC` call retains that original default path.

The seven complete function-name literals total 33B; the pooled 1.0 adds
eight bytes. All content, terminators and eleven following zero alignment
bytes are checked. Some names also have local copies in other math members.
The linked literal and BSS instances here are recorded as native observations;
they are not promoted to independent canonical source-unit anchors. The
32-bit enum/void ABI, complete code and table ownership establish the library
origin separately from a future maintained-source exact comparison.

## Evidence and affected scope

Private `.analysis/origin-boundary/libm-error/` retains the attested full
listing, complete comparison, all sixty selectors, CodeView procedure/record/
enum metadata, observed state and original ledger rows. It reuses the member
in `log10-ceil/` and the existing errno, callback and guard proofs. The matching
tran implementation source is absent from the installed source snapshot;
the archive/native bodies provide implementation evidence.

Only classification, focused evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
