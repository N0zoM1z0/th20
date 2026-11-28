# UCRT commit validation, raw OS errors and complete descriptor unlock

Two complete SDK 10.0.26100.0 x86 commit.obj contributions identify four
library/compiler entries in the locked Japanese TH20 Steamless target.
All 287B/96 instructions, ten REL32/seven DIR32 roles and the complete 28B
scope table are reviewed. One omitted three-byte exception entry is recovered;
all three existing extents remain unchanged.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x00564548` | 147 | int-returning descriptor-lock guarded primary |
| `0x005645DB` | 3 | recovered compiler ESI restore prefix |
| `0x005645DE` | 12 | compiler descriptor-unlock body |
| `0x005645EA` | 125 | `_commit` |

The entries fill `0x00564548..0x00564666` without code padding. CodeView gives
a cdecl int32 `_commit(int32)` and a thiscall int32 guarded template with
three closure-reference arguments. The primary's RET 12 and full EAX result
agree. The exception prefix and unlock retain their compiler-frame ownership.

## Initial validation preserves the special no-console path

The public function handles descriptor -2 before other validation. It sets
errno to EBADF/9 and returns -1 without invoking invalid-parameter handling.
It does not clear doserrno. Other negative descriptors, unsigned values at
least _nhandle, or entries lacking FOPEN set the same errno and call the
reviewed returning invalid-parameter wrapper before returning -1. Those
paths likewise have no local doserrno store.

Valid descriptors construct the original lock/body/unlock captures and enter
the complete guarded owner. Array access uses the previously reviewed
__pioinfo at `0x005E5690`, _nhandle at `0x005E5890`, 64-record blocks, 56B
record stride and FOPEN at record+0x28. No new bounds or null-block checks
replace the original conditions.

## The locked operation retains FOPEN recheck and fixed EBADF

The guarded owner acquires the reviewed per-descriptor lock, then activates
its try state and rechecks FOPEN. A closed entry sets errno 9 and returns -1;
this locked path neither calls invalid-parameter handling nor stores doserrno.

For an open entry, the reviewed get_osfhandle supplies the raw handle to
KERNEL32.dll!FlushFileBuffers through IAT `0x0056C074`. Success retains zero
as the full int result. API failure calls GetLastError through the independently
named IAT `0x0056C130`, stores that raw DWORD through the reviewed doserrno
getter, then sets errno to 9 and selects -1. It does not map the OS error to
a different errno. Existing errno/doserrno values receive no new stores on
the API-success path.

Normal completion saves the result, changes try state to -2 and calls the
unlock at `0x005645DE`, then returns the retained ESI value through EAX.
The exception entry at `0x005645DB` first restores ESI from parent EBP-0x1C
and falls into that same unlock. The full scope table at `0x005AC6C0` has
header `-2,0,-44,0` and record `-2,0,0x005645DB`. Its source header and the
independently located owner's callback offset identify the table before the
primary metadata pointer is compared. The complete HIGHLOW role and four
following zero alignment bytes agree. Exceptions continue after cleanup;
no failure return is manufactured for that path.

## Evidence and affected scope

Private `.analysis/origin-boundary/lowio-commit/` retains full locations,
CodeView signatures, attested listing, comparison/CFG/fields and scope search.
It reuses commit.obj from `stdio-flush/`, the descriptor lifetime/state proof,
SEH4 prolog and errno/invalid-parameter providers. Source is
`ucrt/lowio/commit.cpp`, `corecrt_internal.h` and `corecrt_internal_lowio.h`.
Ghidra omits the recovered MOV ESI instruction; bounded pinned decoding and
complete source/native bytes retain its three bytes and metadata reference.
The nine-byte lambda shape at `0x005645E1` is a suffix of the existing unlock,
not another reviewed physical entry. Other unlocated standalone helpers remain
separate from the complete inlined guarded contribution.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
