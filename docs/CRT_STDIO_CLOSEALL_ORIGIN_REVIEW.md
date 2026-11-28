# UCRT fcloseall counting, object retirement and complete finally owner

The complete 171B/57-instruction closeall.obj contribution at `0x0055CADC`
is reviewed against SDK 10.0.26100.0 x86 libucrt.lib and the locked Japanese
TH20 Steamless target. The existing 162B primary and 9B compiler finally
entry at `0x0055CB7E` retain their extents. All five REL32/nine DIR32 roles,
including the full 28B scope table, agree. There is no code alignment or
embedded jump table; the original flag-read NOP remains inside the primary.

CodeView establishes cdecl int32 `_fcloseall(void)`. Its result is the
accumulated count of successful closes. A returned EOF from one fclose does
not make fcloseall return EOF, despite the installed source's introductory
comment. The implementation and complete original control flow agree on
counting only in-use streams whose fclose result is not -1.

## Every nonnull extra stream is retired after an ordinary close result

The function acquires the reviewed UCRT stdio-index lock 8, then activates
its try state. Its loop starts at index three and continues while the index
is unequal to the current _nstream. It rereads that global at each iteration;
no less-than test, clamp or extra table validation replaces the original.
The already reviewed state is _nstream at `0x005E5318` and __piob at
`0x005E531C`.

A null slot is skipped. For a nonnull stream, allocated bit 0x2000 selects
the fclose call, and a result other than -1 increments the local count.
After an ordinary return, every nonnull slot has its lock at +32 deleted,
its object freed through free_base, and its table pointer cleared. That
cleanup also occurs for an unallocated stream or a returned fclose failure.
The first three standard records, the pointer table itself and _nstream
are retained by this owner.

The 48B fclose entry at `0x00564518` now has its
[complete cleanup/reset/EH review](CRT_STDIO_FCLOSE_ORIGIN_REVIEW.md), including
the recovered six-byte exceptional restore and full scope table.

## Normal and exceptional unlock share the complete scope table

Normal loop completion changes the try state back to -2 and calls the
9B finally entry. That entry passes lock ID 8 to the already reviewed
unlock and returns. The primary reloads the saved count, restores FS:[0]
and the original frame/registers, then returns EAX. The SEH path selects the
same finally entry; it does not convert an exception into a count result.
An exception before try activation, while obtaining the lock, has no new
local cleanup branch.

The full 28B scope table at `0x005AC580` has header `-2,0,-48,0` and record
`-2,0,0x0055CB7E`. It is independently located using the source header and
the already located owner's callback at offset 162, before comparing the
primary's metadata pointer. Its one HIGHLOW role and four following zero
alignment bytes are checked. The original SEH4 prolog identity is reused;
no extent is shortened to omit the compiler callback or inline epilogue.

## Evidence and affected scope

Private `.analysis/origin-boundary/stdio-closeall/` retains the complete
attested listing, CodeView signature, table search/comparison, all fields,
complete CFG and original rows. It reuses closeall.obj and the established
stdio state/layout, allocation and critical-section identities in
`stdio-lifetime/`. The fclose member and full location results stay here;
its own complete review is retained in `stdio-fclose/`. Source is
`ucrt/stdio/closeall.cpp` and `corecrt_internal_stdio.h`.

Two existing origins become library/compiler exclusions. Tracking/progress
checks pass and all 2,151 protected hashes remain unchanged. Exact replay
scope is **zero units**, with no new authored or maintained-source exact credit.
