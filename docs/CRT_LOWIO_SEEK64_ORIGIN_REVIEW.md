# UCRT 64-bit nolock seek and complete result handling

The complete 131B seek owner at `0x0056513A` and 30B internal wrapper at
`0x005651BD` match SDK 10.0.26100.0 x86 lseek.obj in the locked Japanese
TH20 Steamless target. All 161B/64 instructions and three REL32/three DIR32
roles are reviewed. Existing extents remain unchanged; neither section owns
additional data, padding, EH or tables.

The 52-instruction owner is `common_lseek_nolock<__int64>`; the 12-instruction
wrapper is `_lseeki64_nolock_internal`. CodeView establishes cdecl with int32
descriptor, signed 64-bit offset, int32 origin and cached-host reference. The
wrapper forwards five stack DWORDs, releases twenty bytes after the call and
preserves the full EDX:EAX signed 64-bit result. Failure sets both halves to
0xFFFFFFFF, not only the low DWORD.

## Handle, API error and EOF flag order

The owner first calls the independently reviewed 106B `_get_osfhandle`.
A returned raw handle of -1 marks cached errno valid at host+0x1C, stores
EBADF/9 at +0x18 and returns -1. There is no additional invalid-parameter
callback or explicit doserrno store in this owner; the getter retains its
own global error/callback behavior. No separate range/open validation or
lock is inserted here.

Other handle values are passed to the actual SetFilePointerEx import at
`0x0056C0AC`. Both input offset halves and the unchanged origin are forwarded;
the API writes a complete eight-byte local result. API failure calls
GetLastError, then the already reviewed 36B cached OS-error mapper with the
same host. It returns full 64-bit -1 without changing the descriptor flag.
There is no added origin check, position rollback or 32-bit range restriction.

On API success, the code tests both result halves for the -1 sentinel by
AND followed by comparison with 0xFFFFFFFF. That exact result returns -1
without clearing EOF or synthesizing another cached error. Every other
result, including other negative bit patterns, follows the normal success
path. Only then does it clear FEOFLAG/0x02 in the original lowio record's
byte at +0x28, preserving every other bit. Descriptor blocks remain 64 records
of 56B addressed through the reviewed pioinfo array. The result retains the
API's high DWORD and reloads its low DWORD after the sentinel test.

The reviewed [write dispatcher](CRT_LOWIO_WRITE_DISPATCH_ORIGIN_REVIEW.md)
uses this wrapper for append positioning with offset zero and FILE_END/2.
It ignores the seek result and continues writing, without undoing any error
side effects. This establishes a caller contract, not a new seek retry.

## Relocations distinguish the same-shaped locked wrapper

The SDK's 30B `_lseeki64_internal` and `_lseeki64_nolock_internal` sections
have identical complete ordinary bytes. Both masked signatures therefore
locate `0x005651BD`. Their single call relocations name different owners:
locked common_lseek in section 6 versus nolock common_lseek in section 11.
The target calls `0x0056513A`, independently located by the full 131B nolock
contribution. That resolves the wrapper as nolock; ordinary bytes alone would
misidentify it. No duplicate locked-wrapper entry or credit is added.

Private `.analysis/origin-boundary/lowio-seek64/` retains CodeView, the complete
attested listing and `review.py`/`reviewed.json`, including that rejected
locked-wrapper hypothesis. It reuses the original lseek.obj, provenance and
whole-member locations in `lowio-write-nolock/`. Every ordinary byte,
relocation/HIGHLOW, CFG edge, return width and PE import identity agrees.
The source is `ucrt/lowio/lseek.cpp`; existing getter, cached mapper and
pioinfo evidence remain in their respective focused reviews.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected hashes remain unchanged. Exact replay scope is **zero
units**, with no new authored or maintained-source exact credit.
