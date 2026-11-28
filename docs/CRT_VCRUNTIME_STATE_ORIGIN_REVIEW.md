# VCRuntime startup, lock ownership and per-thread state

Ten complete libvcruntime.lib contributions identify ten pending library
origins in the locked Japanese TH20 Steamless target. All 486 instruction
bytes, fourteen INT3 bytes and 72B of lock/PTD/FLS state agree with the
installed MSVC 14.44.35207 archive. Every existing extent remains unchanged.
Actual callees and state reject the same-shaped UCRT and lifecycle candidates.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x005465A5` | 31 | VCRT initialization |
| `0x005465C4` | 23 | VCRT release uninitialization |
| `0x005467BA` | 28 | stdcall FLS cleanup callback |
| `0x005467D6` | 14 | required VCRT PTD getter |
| `0x005467E4` | 146 | nullable allocating PTD getter |
| `0x00546876` | 56 | nonallocating PTD getter |
| `0x005468AE` | 51 | PTD initialization |
| `0x005468E1` | 30 | PTD index cleanup |
| `0x005476CC` | 60 | lock initialization |
| `0x00547708` | 47 | lock cleanup |

The full members are `initialization.obj`, `locks.obj` and
`per_thread_data.obj`. Their selected contributions own no SEH or C++ EH
tables; the compared data closure consists of the three state sections below.

## Complete local state and startup order

| Address | Bytes | Definition |
| --- | ---: | --- |
| `0x005B2630` | 4 | FLS index, initially 0xFFFFFFFF |
| `0x005E52A4` | 40 | static startup-thread PTD, loader-zero |
| `0x005E52D0` | 28 | one 24B critical section and initialized-count DWORD |

The source's VCRT lock enum contains only the undname lock. The full native
initialization loop likewise stops after 24B. The counter is at `0x005E52E8`.
Initialization uses the VCRT CriticalSectionEx shim with spin count 4000 and
flags zero. It increments the count only after success, and failure invokes
the real VCRT cleanup. Cleanup walks initialized slots backwards, calls
the independently named DeleteCriticalSection import, and decrements the
count. Both helpers return bool in AL.

The outer initializer creates the lock first, then PTD. Lock failure returns
false immediately; PTD failure rolls back locks before returning false.
The compiled x86 string initializer makes no call here. Release
uninitialization examines the low byte of its terminating argument. True
skips cleanup; false cleans PTD index before locks. It returns true in either
case, preserving the original ignored cleanup results.

## Static startup PTD and FLS publication

PTD initialization allocates an index using the actual stdcall cleanup
callback at `0x005467BA`. An allocation result of 0xFFFFFFFF returns false.
Otherwise it publishes the static 40B startup object into FLS. Publication
failure invokes the complete index cleanup and returns false. No dynamic
PTD allocation is required for the startup thread.

Index cleanup calls the named FlsFree shim for a valid index, ignores its
return, writes 0xFFFFFFFF and returns true. The cleanup callback separately
skips null and the static startup object; other pointers go to the already
reviewed free wrapper at `0x0054A540`. It has no extra -1 sentinel special
case. Its RET 4 preserves the one-argument stdcall ABI.

The x86 PTD is exactly 40B. Its relevant fields agree with the earlier
exception-lifetime evidence: unexpected at +4, current exception/context
at +0x10/+0x14, ProcessingThrow at +0x18 and frame chain at +0x24.
The separate UCRT PTD layout is not substituted.

## Nullable getter, reentrancy and LastError

An unallocated index returns null before calling GetLastError. For a valid
index, the allocating getter saves LastError and reads FLS. A returned -1
sentinel becomes null; an existing nonnull PTD is returned directly. With
no PTD, it first publishes -1 to prevent recursive allocation. If that
publication fails, it returns null without allocating.

It then calls the named calloc entry with `(1,40)`. Allocation or PTD
publication failure attempts to clear the FLS value, ignoring that clearing
result. The temporary allocation is freed when needed. Successful publication
detaches the allocation; the compiler's original free(null) remains, as does
free(null) after a failed calloc. LastError is restored on all normal
valid-index return paths. No additional exception recovery is inferred from
the source RAII names or introduced into the native protocol.

The noinit getter performs the same index guard and LastError-preserved FLS
read, maps -1 to null and never allocates. The required getter calls the
complete VCRT nullable owner at `0x005467E4` and branches to the real abort
if null. The UCRT lookalike at `0x005579C2` instead calls `0x00557A13`.
Its previously established UCRT identity remains unchanged.

## Rejected lock and lifecycle aliases

Both 21B VCRT lock/unlock shapes match inside UCRT's helpers at
`0x00551EA5` and `0x00551EED`. Those instructions reference the UCRT table,
not `0x005E52D0`, so neither is a VCRT entry. Similarly, the alternate
47B cleanup match at `0x00551EBC` references the UCRT table/count. The whole
VCRT initialization/cleanup pair independently binds its own full 28B state.

The proposed thread-attach match at `0x00558390` actually calls the reviewed
CompareStringEx accessor at `0x00557CA5`; it is the locale-API availability
query, not VCRT thread attach. The eight-byte detach/critical-cleanup shape
at `0x005538E6` is the independently reviewed environment-retirement callback,
calling `0x00553516`. It neither calls the VCRT index cleanup at `0x005468E1`
nor establishes a VCRT current-thread cleanup implementation. These candidates
receive no new VCRT identity. Unlocated weak heap/empty helpers likewise
gain no body credit from their source spelling.

## Evidence and affected scope

The initialization interval `0x005465A5..0x005465DF` includes five INT3
bytes after uninitialization. The full PTD interval is
`0x005467BA..0x005468FE`. The lock interval `0x005476CC..0x0054773F`
includes nine final INT3 bytes. All instructions and alignment agree.

Private `.analysis/origin-boundary/vcrt-state/` retains the three full
members, bounded attested listings, search/relocation results, `review.py`,
`reviewed.json` and original ledger rows. Every ordinary byte, branch/call,
REL32/DIR32, HIGHLOW and complete initialized/BSS section is compared. Actual
GetLastError, SetLastError and DeleteCriticalSection names come from the PE
import directory. Source is the installed VCRuntime
`{initialization,locks,per_thread_data}.cpp` and `vcruntime_internal.h`.

The FLS/CriticalSectionEx shims and calloc entry remain named external
dependencies without body credit in this review. This preserves the actual
calls while leaving their API fallback and allocation behavior for their
own complete providers. Only classification, evidence, handoff and generated
progress change. All 2,151 protected native input/product hashes remain
unchanged. Exact replay scope is **zero units**, with no new authored or
maintained-source exact credit.
