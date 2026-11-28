# UCRT special-value classification, current-mode rounding and except1

Three complete SDK 10.0.26100.0 x86 contributions identify pending library
origins in the locked Japanese TH20 Steamless target. Their 447B/170
instructions, all nine REL32/one DIR32 fields and 24 following INT3 bytes
are reconciled. All existing extents remain unchanged. There is no owned
static data, EH table or embedded switch table.

| Entry | Bytes | Symbol | Member |
| --- | ---: | --- | --- |
| `0x005524B0` | 114 | `__sptype` | frexp.obj |
| `0x00553A00` | 310 | `__except1` | fpexcept.obj |
| `0x00564240` | 23 | `__frnd` | frnd.obj |

The first two bodies have CodeView procedure records: sptype returns int32
from one double, while except1 returns double from two int32 values, an
argument double, a result double and an unsigned int32 control word. Both
are cdecl. The complete frnd instructions and reviewed ceil/floor callers
establish its stack-double input and ST(0) double result.

## Classification uses the original bits without floating arithmetic

Sptype reads the double's two 32-bit words. Exact positive/negative infinity
returns 1/2. An all-ones exponent with the quiet bit set returns 3, independent
of sign. Other nonzero NaN payloads return 4. Finite values, both zeros and
denormals return zero. The complete 114B owner has no external dependency
or floating instruction; it does not signal an exception merely to classify
a NaN. Ceil/floor's codes 1/2/3 therefore retain their original passthrough
behavior, separate from the signaling-NaN error path.

## Frnd keeps the caller's control word and double spill

The 23B frnd owner loads the stack double, executes FRNDINT using the current
x87 mode, stores a double temporary with FSTP, then reloads it before returning
through ST(0). It does not install a mode or access MXCSR. Preserve the spill,
stack effect and original floating instructions rather than replacing it
with floor, ceil or an integer cast. The next independent entry starts at
`0x00564257`, immediately after this body.

## Except1 forwards a mutable result and saved control word

Except1 retains its original sixteen-byte stack alignment, EBX-based argument
view and two cookie-checked exits. It first passes the flags, result address
and saved control word to the reviewed handle_exc. If handling is incomplete,
it clears the original local-record validity bit and calls raise_exc_ex with
the local record, control-word pointer, flags, opcode, argument/result pointers
and zero width selector. The returning path reloads the saved word, preserving
the exception handler's opportunity to change it and the result.

The original flag priority selects the matherr record type:

| First matching flag | Record type |
| --- | --- |
| `0x20` | 5, total loss |
| `0x08` | 1, domain |
| `0x04` | 2, singularity |
| `0x01` | 3, overflow |
| `0x02` | 4, underflow |
| none | 0 |

If a user matherr is present and the type is nonzero, except1 passes that
type, opcode, original argument, a zero second argument, updated result and
saved word to umatherr. Its ST(0) result is returned directly after the cookie
check. This is a double-returning call, not an integer handled/not-handled
result. The parent does not add another control-word restore on that path.

Without that call, only domain sets errno 33 and singularity/overflow set
errno 34. The other types have no errno fallback here. The common exit restores
the raw word through the reviewed ctrlfp and loads the updated double result.
All original callback-presence, zero-type, handler-return and errno branches
remain; no record-wide initialization or new failure fallback is introduced.

## Evidence and next provider

Private `.analysis/origin-boundary/math-special-round/` retains full unique
locations, attested listings, ordinary-byte/relocation/CFG comparisons,
CodeView signatures, archive provenance and original rows. It reuses fpexcept.obj
and complete handling/raising/callback/errno/control providers from the earlier
math-error and floating-state reviews. The source tree lacks these tran
implementation files; the archive/native bodies supply their implementation
evidence. The fourteen INT3 bytes after sptype and ten after except1 are checked.

The complete 255B umatherr at `0x00554210` now has its
[full name-table and callback review](CRT_UMATHERR_NAME_TABLE_ORIGIN_REVIEW.md),
including the double result and original control-restoration order.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
