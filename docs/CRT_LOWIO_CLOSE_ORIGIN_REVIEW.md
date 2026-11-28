# UCRT descriptor close, shared standard handles and complete exceptional unlock

Three complete SDK 10.0.26100.0 x86 close.obj contributions match the locked
Japanese TH20 Steamless target. All 468B/171 instructions, twelve REL32/nine
DIR32 roles, the full 28B scope table and four following zero alignment bytes
are reviewed. Four existing entry extents remain unchanged; a missing
three-byte exception prefix completes the 145B guarded owner.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x0056641D` | 130 | guarded close primary |
| `0x0056649F` | 3 | recovered compiler result restore |
| `0x005664A2` | 12 | compiler descriptor unlock |
| `0x005664AE` | 163 | `_close_internal` |
| `0x00566551` | 160 | `_close_nolock_internal` |

The complete 468B interval is contiguous and has no owned code padding,
additional static data or switch table. CodeView establishes int32 returns:
the guard is thiscall with three closure-reference arguments and RET 12;
both internal APIs are cdecl with int32 descriptor and cached-host reference.
The guard's empty receiver is separate from its explicit captures.

## Validation and recheck preserve different error paths

Descriptor -2 returns -1 after clearing cached doserrno DWORD at host+0x20,
marking it valid at +0x24, then marking errno valid at +0x1C and storing
EBADF/9 at +0x18. It does not call the invalid-parameter handler.
Other negative/out-of-range descriptors or missing FOPEN take the callback
path: doserrno validity precedes its zero payload, then errno validity and
EBADF, followed by the reviewed internal handler with five null arguments
and the same host. A returning handler leads to -1. Keep those original
store orders rather than replacing both branches with one generic helper.

A valid precheck constructs lock/body/unlock captures and calls the guard.
Lock and unlock hold descriptor values; the body holds the address of the
original descriptor plus the cached-host pointer. The guard initializes its
saved result to zero, acquires the reviewed descriptor lock, activates try
state zero and repeats the FOPEN test. Recheck failure caches only EBADF and
returns -1, without another handler or doserrno clear. Recheck success calls
the complete nolock owner and saves its full int result.

Normal completion sets try state -2 and calls the twelve-byte unlock.
The recovered instruction at `0x0056649F` restores ESI from parent EBP-0x1C
on exceptional entry, then falls into that unlock. Its descriptor comes
from the original cleanup capture, not the body result. Exceptions propagate;
they are not converted into a successful zero result.

## OS-handle policy and unconditional descriptor reset

The nolock owner first calls the reviewed `_get_osfhandle`. A raw -1 skips
CloseHandle and selects OS error zero. Otherwise, descriptor 1 checks whether
descriptor 2 is open, and descriptor 2 checks whether descriptor 1 is open.
Only in those cases does it compare their actual OS handles; equality skips
CloseHandle without error. This special sharing rule does not apply to other
descriptor numbers. Original repeated getter calls and their existing global
error behavior remain intact.

For an ordinary close it obtains the handle again and calls the actual
CloseHandle import. Success selects zero; failure captures GetLastError.
The captured DWORD survives all later cleanup. Irrespective of that result,
this owner calls `_free_osfhnd`, ignores its return and clears the complete
lowio flags byte at +0x28. The association reset retains its independently
reviewed range/FOPEN/standard-handle behavior; it does not close the handle.

Only after reset does a nonzero captured OS error go through the reviewed
cached mapper and select -1. Zero selects success. Thus a failed CloseHandle
with GetLastError zero also follows the original success result; no invented
fallback error is added. An actual OS close failure still leaves the descriptor
association/flags reset. The nolock API adds no independent descriptor
validation or synchronization before these operations.

## Full scope and rejected standalone/public candidates

The scope table at `0x005AC700` has header `-2,0,-44,0` and record
`-2,0,0x0056649F`. Its complete independent search uses the source header and
callback offset 130 in the independently located guarded contribution before
comparing the code metadata pointer. Its one HIGHLOW and four following zeros
agree. Ghidra omits the three-byte prefix from its listing; the full object
comparison and bounded pinned decoding cover it without database changes.

The source's separate 106B close_os_handle_nolock has no whole ordinary-byte
location: its actual policy is inlined in the complete 160B owner. Both 48B
public close/close_nolock signatures instead locate the already reviewed
fclose at `0x00564518`. Their middle relocations require the independent
163B/160B lowio owners, but that target calls the 151B fclose owner. Both
public candidates are rejected; no false or duplicate entries are added.

Private `.analysis/origin-boundary/lowio-close/` retains the full locations,
CodeView, attested listing/call references, complete comparisons and recovered
prefix. It reuses close.obj/provenance in `stdio-fclose/`, the actual
[fclose caller](CRT_STDIO_FCLOSE_ORIGIN_REVIEW.md), reviewed descriptor helpers,
cached errors, pioinfo/nhandle layout and SEH4 prolog. Installed source is
`ucrt/lowio/close.cpp` and the lowio/PTD propagation headers.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected hashes remain unchanged. Exact replay scope is **zero
units**, with no new authored or maintained-source exact credit.
