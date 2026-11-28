# UCRT stdio initialization, retirement, stream locks and buffer release

Five complete SDK 10.0.26100.0 x86 libucrt.lib contributions identify library
origins in the locked Japanese TH20 Steamless target. All 380B/137 instructions,
ten REL32/twenty DIR32 roles and 184B of owned data are reviewed. Two missing
entries are recovered; all three existing extents remain unchanged.

| Entry | Bytes | Instructions | Symbol | Member |
| --- | ---: | ---: | --- | --- |
| `0x00551851` | 200 | 66 | `___acrt_initialize_stdio` | _file.obj |
| `0x00551919` | 76 | 23 | `___acrt_uninitialize_stdio` | _file.obj |
| `0x00551965` | 20 | 9 | `__lock_file` | _file.obj |
| `0x00551979` | 20 | 9 | `__unlock_file` | _file.obj |
| `0x0055CE36` | 64 | 30 | `___acrt_stdio_free_buffer_nolock` | _freebuf.obj |

The four _file owners fill `0x00551851..0x0055198C` contiguously, without
alignment, omitted tails or EH records. The buffer helper includes two real
NOP instructions. None has an embedded table. CodeView establishes a cdecl
int32 initializer, a void no-argument terminator and three void functions
with one FILE pointer; incidental EAX contents are not status results.

## Complete standard-stream layout and startup records

The full 168B _iob contribution has a unique data location at `0x005B26C8`.
Its three 56B records initialize stdin with flags 0x2001/file 0, stdout with
0x2002/file 1 and stderr with 0x2002/file 2. All other initial bytes are zero.
CodeView independently gives the complete layout: public FILE/ptr union +0,
base +4, count +8, flags +12, descriptor +16, char buffer +20, buffer size +24,
temporary-name pointer +28 and the 24B critical section at +32. Native stride
56 and lock offsets agree. The complete eight-byte BSS contribution places
_nstream at `0x005E5318` and __piob at `0x005E531C`, both in loader-zero data.
Earlier lowio/lifetime consumers independently identify the latter pointer.

The separate stdio_initializer.obj owns a four-byte `.CRT$XIC` initializer
record at `0x0056C428` and four-byte `.CRT$XPXA` terminator record at
`0x0056C44C`. Full startup and exit range bindings, original data references,
matching pointer fields/HIGHLOW roles and both guard-FID symbol indices agree.
The forty-byte C-initializer context and twenty-byte pre-terminator context
retain their zero delimiters and every nonnull pointer. The owned records
select the two independently located code bodies above.

## Initialization publishes the table and preserves allocation fallback

A zero _nstream becomes 512; a nonzero signed value below three becomes three.
The initializer calloc-allocates _nstream four-byte pointers and immediately
publishes the result. Failure sets _nstream to three and retries that allocation.
A second failure returns -1. Both detached temporary owners still make their
original free_base(null) call; these calls are part of the complete code.

For the three standard records, it initializes each lock with spin count 4000
and flags zero, ignores the wrapper's return, and publishes the static record
in __piob. It then reads the corresponding lowio handle through the reviewed
__pioinfo array, with 64-record blocks and 56B stride. A handle of -1, -2 or
zero changes the FILE descriptor to -2; other values retain its existing value.
Success returns integer zero. No new partial-lock rollback or absent-lowio
fallback is introduced.

## Retirement and buffer ownership retain their original order

The void terminator calls flushall then fcloseall and ignores both results.
For each of the first three table entries it releases the CRT-owned buffer,
then deletes that entry's critical section. It finally frees __piob and
clears the pointer. It does not reset _nstream or recreate the static records.
The native sequence has no null-table check or new cleanup-failure branch.

The buffer helper first reads allocated bit 0x2000, then separately rereads
CRT-buffer bit 0x40. Either false condition returns without freeing anything.
The two original NOPs follow these interlocked-read expansions. On the release
path it frees base, atomically clears only 0x40 and 0x100 with LOCK AND, then
zeros base, ptr and count. Other flags, descriptor, buffer size, char buffer
and temporary-name fields remain intact. User-provided buffers are not freed.

Lock/unlock both add 32 to the supplied FILE pointer, then call the original
EnterCriticalSection/LeaveCriticalSection imports. Their complete ordinary
bytes are identical after masking; the independent PE IAT identities select
`0x00551965` as lock and `0x00551979` as unlock. Neither adds a string-stream
special case or null check.

## Evidence and next owner

Private `.analysis/origin-boundary/stdio-lifetime/` retains the five members,
full code/data locations, CodeView signatures/layout, attested listings/data
references, complete comparisons and original rows. Installed sources are
`ucrt/stdio/{_file,_freebuf}.cpp`, `ucrt/inc/corecrt_internal_stdio.h` and
`ucrt/initializers/stdio_initializer.cpp`. Reviewed allocators, lowio state,
critical-section wrapper and startup/exit ranges supply external identities.

The complete closeall contribution at `0x0055CADC` now has its
[full counting/retirement/finally review](CRT_STDIO_CLOSEALL_ORIGIN_REVIEW.md).
The flushall contribution at `0x0055CE2D` now has its
[complete shared flush/lock review](CRT_STDIO_FLUSH_ORIGIN_REVIEW.md), including
both nested guarded owners, full metadata and original no-op/buffer behavior.
The separate iob accessor, stream-buffer-pointer accessor and unreferenced
cflush state have no established native ownership in this batch. Tiny folded
helper matches receive no duplicate credit.

Only classification, evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
