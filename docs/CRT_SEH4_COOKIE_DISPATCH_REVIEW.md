# CRT SEH4 dispatch, collided unwind and cookie initialization

Ten complete installed CRT code contributions identify nine pending library
origins and recover one omitted shared unwind handler in the locked Japanese
TH20 Steamless target. All 877 instruction bytes, 48 INT3 bytes and the
complete 68B cookie/complement definition agree, including every relocation
and actual import. Existing candidate extents remain unchanged.

| Entry | Ledger bytes | Role |
| --- | ---: | --- |
| `0x00543C85` | 77 | entropy collection |
| `0x00543CD2` | 75 | security cookie initialization |
| `0x005465E0` | 50 | ValidateLocalCookies |
| `0x00546620` | 350 | except_handler4, including one final INT3 |
| `0x00547740` | 159 | local unwind core |
| `0x005477E0` | 70 | recovered temporary unwind handler |
| `0x00547830` | 23 | fastcall filter bridge |
| `0x00547850` | 25 | nonreturning handler transfer |
| `0x00547870` | 26 | global unwind bridge |
| `0x00547890` | 23 | fastcall local unwind bridge |

The full members are `chandler4.obj` and `exsup4.obj` from libvcruntime.lib,
and `gs_support.obj`/`gs_cookie.obj` from libcmt.lib. `chandler4gs.obj` has no
code sections; the 70B noexcept variant has no complete target match.

## Cookie definition and initialization

The cookie at `0x005B25C0` is a 64B aligned union containing the 32-bit value
0xBB40E64E and 60 zero bytes. Its complement at `0x005B2600` is 0x44BF19B1.
All 68 bytes of the independent gs_cookie data section match, including
the gap. The source explicitly makes the cookie occupy its own cache line.
This replaces an assumption of two adjacent DWORDs with the complete actual
layout; no native binding or header changes in this classification review.

Initialization retains an existing cookie only when it differs from the
default and its high word is nonzero. That path still updates the complement.
Otherwise the 77B entropy helper XORs both FILETIME halves, thread ID,
process ID, both performance-counter halves and the address of its local
cookie variable. Those four WinAPI imports are independently named in the
PE directory. No tick-count call occurs in this compiled x86 contribution.

Entropy equal to the default becomes default+1. Other results with zero
high word are ORed with `(cookie | 0x4711) << 16`. The final value and its
bitwise complement are stored at their real 64-byte-separated addresses.
The source's architecture/minimum-version alternatives do not replace the
branches actually present in the complete target body.

## Scope decoding and local cookie checks

Let E denote the establisher's EXCEPTION_REGISTRATION_RECORD pointer. The
full SEH4 record starts at E-8; the virtual parent frame pointer is E+16.
Encoded scope pointer and try level are at E+8/E+12. Exception pointers
used by filters are stored at E-4. The scope pointer is decoded with the
global cookie before local checks and context validation.

The scope header's four DWORDs are GS cookie offset, GS XOR offset, EH
cookie offset and EH XOR offset. GS checking is skipped only when its
cookie offset equals -2. EH checking always executes. Each value is computed
as the DWORD loaded at frame+cookie-offset XOR the **address** frame+XOR-offset.
The XOR offset does not name a second memory load. The final EH check
tail-transfers to the real fastcall security checker. This agrees with the
[complete SEH4 prolog](CRT_FRAME_STACK_HELPER_ORIGIN_REVIEW.md).

The handler first normalizes the exception code through the named x86 SSE2
filter, validates both applicable cookies, and calls the context validator.
The SSE2 filter and context-validator bodies are outside this review.

## Dispatch, filter results and accepted handlers

The handler tests unwind mask 0x66: unwind, exit unwind, target unwind and
collided unwind. With none set, it publishes the EXCEPTION_POINTERS pair
and walks 12B scope records through their enclosing levels until -2. Null
filters are skipped during dispatch. A called filter sets the revalidation
flag and its signed result determines the path:

- Negative: revalidate cookies, return ExceptionContinueExecution/0.
- Zero: continue to the enclosing record; revalidate on final return if
  any filter ran, then return ExceptionContinueSearch/1.
- Positive: unwind and transfer to the selected handler without returning.

These dispatcher dispositions differ from the filter's own signed result.
For a positive Microsoft C++ exception, the optional destruction callback
is invoked with the exception and TRUE only when its pointer is nonnull
and its slot passes IsNonwritableInCurrentImage. The original guard check
on that indirect callback remains. The observed slot is `0x00597180`;
chandler4's four-byte common fallback symbol does not establish the selected
strong data definition or give it new ownership credit.

Global unwind runs before local unwind to the accepted level. The record's
try level becomes the enclosing level before cookies are revalidated and
control transfers to the handler. For any nonzero 0x66 unwind mask, an active
level instead unwinds to -2 and revalidates before continuing search. No
extra target-unwind exclusion is added from a source comment.

## Finally order and collided unwind

The 159B local core installs a temporary FS:[0] node with its own cookie
XOR node-address. Each iteration decodes the scope table through the supplied
cookie pointer. It stops at level -2, or when a non--2 target has been reached
using the original unsigned level comparison. It stores the enclosing
level **before** inspecting or invoking the record's callback. Filtered
records advance without a finally call. Finally records emit NLG notification
0x101 and invoke the finally with abnormal-termination flag 1.

The temporary node's 70B handler was absent from the candidate ledger.
It tests only unwind flags 0x6, unlike the public handler's 0x66. Otherwise
it returns search/1. On unwind it validates the temporary cookie, restores
the saved parent EBP and calls the local core with saved cookie pointer,
registration and target level. It then writes its node to dispatcher
context and returns ExceptionCollidedUnwind/3. Normal local completion
restores the previous FS chain and nonvolatiles.

The filter bridge sets parent EBP, preserves original nonvolatiles, clears
EAX/EBX/EDX/ESI/EDI before the callback and returns the raw filter result.
The handler-transfer bridge sets parent EBP, emits NLG code 1, clears
EAX/EBX/ECX/EDX/EDI and jumps to the handler retained in ESI.
It has no normal return. The local-unwind fastcall bridge supplies EBP and
forwards the two register and two stack arguments, returning with RET 8.

The global-unwind bridge preserves nonvolatiles and calls the independently
named RtlUnwind import with establisher, its own internal ReturnPoint,
exception record and zero return value. The complete ReturnPoint DIR32
field and HIGHLOW are included. NLG notification/call helpers remain named
external dependencies, without new body credit in this group.

## Full extents, evidence and affected scope

ValidateLocalCookies has fourteen following INT3 bytes before except_handler4.
The latter retains its existing 350B extent: 349 instructions and one final
INT3. The six assembly helpers retain all 33 alignment bytes between them.
Thus the three complete intervals are `0x00543C85..0x00543D1C`,
`0x005465E0..0x0054677D` and `0x00547740..0x005478A6`.
There is no locally owned scope table in these shared handlers; their
per-function scope inputs remain owned by the reviewed callers.

Private `.analysis/origin-boundary/seh4-dispatch/` retains the full members,
bounded attested listings, search/relocation details, `review.py`,
`reviewed.json` and original ledger rows. The audit covers every ordinary
byte, branch/call, REL32/DIR32 field, HIGHLOW, all five actual imports and
the full cookie data section. Source corroboration is the installed
`i386/chandler4.c` and `vcruntime/{gs_support,gs_cookie}.c`; assembly bridge
contracts also come from chandler4's fastcall declarations and the complete
exsup4 artifact/native instructions. This does not globally identify the
game's compiler settings.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**; no authored or maintained-source exact credit is added.
