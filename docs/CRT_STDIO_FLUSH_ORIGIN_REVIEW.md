# UCRT shared flush, no-op counting, buffer reset and complete lock owners

Eight complete SDK 10.0.26100.0 x86 fflush.obj contributions identify ten
library/compiler entries in the locked Japanese TH20 Steamless target.
All 687B/289 instructions form the continuous interval
`0x0055CB87..0x0055CE35`. Five original NOPs, all 21 REL32/six DIR32 roles,
two full 28B scope tables and eight zero metadata-alignment bytes are checked.
All existing entry extents remain unchanged; no code padding or tail is omitted.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x0055CB87` | 128 | stream-lock guarded void primary |
| `0x0055CC07` | 12 | its compiler finally/unlock |
| `0x0055CC13` | 160 | index-lock guarded void primary |
| `0x0055CCB3` | 12 | its compiler finally/unlock |
| `0x0055CCBF` | 76 | common_flush_all |
| `0x0055CD0B` | 49 | common_flush_all_should_try_to_flush_stream |
| `0x0055CD3C` | 35 | is_stream_flushable_or_commitable |
| `0x0055CD5F` | 105 | __acrt_stdio_flush_nolock |
| `0x0055CDC8` | 101 | _fflush_nolock |
| `0x0055CE2D` | 9 | _flushall |

CodeView gives void thiscall interfaces for the two guarded template owners,
with three closure-reference arguments and RET 12. The two predicates return
bool in AL, not a full int32 status. The other four functions return int32
through EAX. common_flush_all takes a bool whose low stack byte controls the
return selection. The source FILE wrapper is one pointer passed by value;
stdio_flush_nolock also receives the cached PTD host by reference.

## Precheck, recheck and the two result modes

The common wrapper initializes separate count/error ints to zero and constructs
closures holding their addresses and the mode address. Under stdio-index lock
8, the outer guard snapshots __piob and its end using the current _nstream.
Its pointer loop uses inequality against that fixed end, unlike fcloseall's
per-iteration count reload. The prior stdio review supplies both state owners.

The precheck rejects null or unallocated streams. It considers a stream
flushable when `(flags & 3) == 2` and a CRT/user buffer bit in 0xC0 is set;
commit bit 0x800 also makes it eligible. An allocated stream that satisfies
neither condition increments count and skips its stream lock entirely.
Thus an ordinary read stream can count as successful without clearing its
input buffer. The installed flushall comment about clearing input buffers
does not describe this complete native path.

For an eligible stream, the inner guard locks the FILE and repeats the same
check. This second check retains concurrent state changes and can count a
newly no-op stream. In false mode, a stream also needs write bit 2 before
calling _fflush_nolock. A result other than -1 increments count; -1 sets the
separate error to -1 and traversal continues. True mode returns count; false
mode returns error. The nine-byte _flushall entry passes true and preserves
the full int result. No failed stream terminates the ordinary traversal.

The inner capture holds stream-wrapper/count/mode/error references; the outer
capture holds count/mode/error references. Both template primaries acquire
their actual lock before activating the try state. Their finally entries
load the original cleanup capture and call the reviewed FILE unlock or global
unlock. Normal completion resets state to -2 and calls the same entry selected
by the scope table on exceptional exit. Exceptions are not converted into a
flush count or status.

## Buffer reset precedes write, and short writes keep the reset state

The 105B stdio_flush_nolock returns zero immediately for a nonflushable mode.
For a flushable stream it computes the signed int32 ptr-minus-base length,
sets ptr to base and count to zero, then tests that length. A nonpositive
length returns zero after the reset, without clearing the write flag.

A positive length calls the reviewed fileno and independently identified
write_internal with the original base, requested count and cached PTD host.
Any returned count unequal to the requested count atomically ORs IOERROR/0x10
and returns -1. The buffer reset remains after that failure; no retry or
restoration of pending bytes is added. Exact-count success rereads flags and,
only for update bit 4, atomically clears write bit 2. Other flags remain.
The original separate reads, NOPs, LOCK OR and LOCK AND are retained.

The 101B _fflush_nolock constructs the reviewed 40B cached PTD host. Null FILE
calls common_flush_all(false). A nonnull FILE calls stdio_flush_nolock first;
its failure suppresses commit and returns -1. On success, commit bit 0x800
selects fileno followed by the original _commit; any nonzero commit result
becomes -1. Every ordinary exit destroys the cached host before returning the
saved result, retaining its existing deferred-error propagation. A read stream
without commit remains a no-op here as well.

## Complete metadata and evidence

The full scope tables are at `0x005AC5A0` and `0x005AC5C0`. Their headers are
`-2,0,-40,0` and `-2,0,-76,0`; their records both start `-2,0` and select
`0x0055CC07`/`0x0055CCB3`. Each table is independently located using its source
header and the already located owner's callback offset, before comparing the
code's metadata pointer. All HIGHLOW fields and four following zero bytes
per table are retained. No additional EH record belongs to these eight sections.

Private `.analysis/origin-boundary/stdio-flush/` retains the complete attested
listing, CodeView, whole comparisons/CFG/fields and independent scope searches.
It reuses fflush.obj and unique whole locations in `stdio-lifetime/`, plus
reviewed stdio state/layout, lock, fileno, SEH4 prolog and cached-host providers.
Installed source is `ucrt/stdio/fflush.cpp` and `corecrt_internal_stdio.h`.
The newly retained write.obj/commit.obj uniquely identify their complete
273B/125B contributions at `0x00564E0D`/`0x005645EA`; their own protocol and
metadata closure remains pending. Public fflush and its separate int-returning
guarded template have no complete ordinary-byte locations in this member.

Only ten origin rows, focused evidence, handoff and generated progress change.
Tracking/progress checks pass and all 2,151 protected hashes remain unchanged.
Exact replay scope is **zero units**, with no new authored or maintained-source
exact credit.
