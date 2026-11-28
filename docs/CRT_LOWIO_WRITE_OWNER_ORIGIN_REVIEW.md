# UCRT write_internal cached errors and complete exception unlock

The complete 273B/91-instruction write.obj contribution at `0x00564E0D`
is reviewed against SDK 10.0.26100.0 x86 libucrt.lib and the locked Japanese
TH20 Steamless target. All five REL32/five DIR32 roles and the full 28B scope
table agree. A missing six-byte exceptional entry is recovered; the existing
259B primary and 8B unlock retain their extents. The complete interval ends
at `0x00564F1D`, immediately before the independently located write_nolock.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x00564E0D` | 259 | `_write_internal` primary |
| `0x00564F10` | 6 | recovered compiler descriptor/result restore |
| `0x00564F16` | 8 | compiler descriptor unlock |

CodeView establishes cdecl int32 return and four arguments: int32 descriptor,
const void pointer, uint32 byte count and cached PTD host reference. There is
no local host construction/destruction. The descriptor-validation failures
return -1, despite the installed source introduction saying zero on failure.
The delegated result is returned unchanged rather than normalized to a bool
or fabricated failure value.

## Validation writes the caller's cache before any descriptor lock

The -2 no-console path marks cached doserrno valid and writes zero, then marks
cached errno valid and writes EBADF/9. It returns -1 without invoking the
invalid-parameter dispatcher. Other negative descriptors, unsigned values at
least _nhandle, or missing FOPEN perform the same cached writes, call the
reviewed internal invalid-parameter dispatcher and return -1 if it resumes.
The call passes five zero diagnostic values and the original host reference.

Payloads are full DWORDs at host+0x18/0x20; their validity bytes are at
+0x1C/+0x24. The original byte-before-payload stores and doserrno-before-errno
validation order remain. These are cached fields, not immediate writes through
the public errno getters. The caller's established host lifetime controls
later publication. This owner does not replace that dispatcher with the
no-info wrapper used by public commit.

Array access uses the reviewed _nhandle and __pioinfo state, 64-record blocks,
56B record stride and FOPEN byte at +0x28. Buffer validation and zero-count
handling are delegated; a zero count does not bypass this descriptor validation.
No null-array or buffer fallback is added to the parent.

## Locked recheck, delegated result and both cleanup entries

After acquiring the reviewed per-descriptor lock, the parent initializes the
saved result to -1 and activates try state zero. It rechecks FOPEN using the
original block/record indices. A closed entry writes errno 9 then doserrno zero,
with the same full payload and validity widths, and proceeds to unlock without
calling invalid-parameter handling. This write order follows the source's
explicit locked-error assignments, distinct from the validation macro order.

An open entry calls write_nolock with all four original arguments. It saves
the returned EAX in EBX and the parent result slot, then resets try state to -2
and calls the 8B unlock. Normal completion returns the saved EBX result through
EAX. The unlocked result is not recomputed from errno or requested length.

The six-byte exception entry first restores descriptor EDI from parent EBP+8,
then result EBX from EBP-0x1C, and falls into that same unlock. The complete
scope table at `0x005AC6E0` has header `-2,0,-52,0` and record
`-2,0,0x00564F10`. Its source header and independently located owner/callback
offset identify it before comparing the primary metadata pointer. All HIGHLOW
fields and four following zero alignment bytes are checked. Exceptions continue
after cleanup; initial validation has no active descriptor-unlock try state.

## Evidence and affected scope

Private `.analysis/origin-boundary/lowio-write/` retains complete locations,
CodeView signatures, full comparison/CFG/fields and scope search. It reuses
write.obj in `stdio-flush/`, reviewed lowio state/lock and cached-host/internal
invalid-parameter identities. Installed source is `ucrt/lowio/write.cpp`,
`corecrt_internal_lowio.h` and `corecrt_internal_ptd_propagation.h`.
Ghidra omits the two restore instructions; bounded pinned decoding and the
complete object/native comparison retain all six bytes and their scope root.

The complete 540B write_nolock contribution at `0x00564F1E` has a unique member
identity and the same four-argument ABI. Its text/encoding/write/error protocol
remains the next owner review. The current member's 55B public write wrapper
has no full ordinary-byte location and receives no reviewed credit.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
