# UCRT PTD allocation, FLS lifetime and errno ownership

Twenty-four pending origins are reviewed, with three recovered heads: the 54B
PTD initializer and two 29B compiler EH entries. Complete Windows SDK
10.0.26100.0 x86 `libucrt.lib` members `per_thread_data.obj` and `errno.obj`
agree with 1,749 instruction bytes, sixteen INT3 bytes and 581B of complete
owned state/tables/metadata in the locked Japanese TH20 v1.00a Steamless target.

## Complete PTD owners and physical partitions

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x005575DC` | 70 | multibyte construction guarded primary |
| `0x00557622` | 12 | its unlock funclet |
| `0x0055762E` | 95 | multibyte retirement guarded primary |
| `0x0055768D` | 12 | its unlock funclet |
| `0x00557699` | 73 | locale retirement guarded primary |
| `0x005576E2` | 12 | its unlock funclet |
| `0x005576EE` | 78 | locale construction guarded primary |
| `0x0055773C` | 12 | its unlock funclet |
| `0x00557748` | 153 | `construct_ptd` |
| `0x005577E1` | 33 | stdcall `destroy_fls` |
| `0x00557802` | 205 | `destroy_ptd` |
| `0x005578CF` | 168 | slow PTD head allocator |
| `0x00557977` | 75 | unlocked locale replacement |
| `0x005579C2` | 14 | `__acrt_getptd` |
| `0x005579D0` | 61 | `__acrt_getptd_head` |
| `0x00557A13` | 135 | `__acrt_getptd_noexit` |
| `0x00557A9F` | 68 | explicit nullable getter |
| `0x00557AE8` | 54 | recovered `__acrt_initialize_ptd` |
| `0x00557B1E` | 26 | `__acrt_uninitialize_ptd` |
| `0x0056B2D3` | 29 | nullable getter's EH handler |
| `0x0056B30D` | 29 | shared head/explicit EH handler |

The main interval `0x005575DC..0x00557B37` is complete: 1,356 instruction bytes
and sixteen INT3 bytes. The required-head, nullable and explicit getter sections
own six, five and five trailing INT3 bytes respectively. The four SEH owners
remain complete 82B/107B/85B/90B contributions split into their primary and
12B unlock partitions. No original extent is shortened.

The required getter's 14B ordinary-byte shape also matches `0x005467D6`.
That candidate calls a different nullable getter and is rejected. The selected
head calls the complete UCRT nullable owner at `0x00557A13` and aborts on null.

## Initialization, reentrancy and LastError

The original paired UCRT table independently names initialization at
`0x00557AE8` and retirement at `0x00557B1E`; the earlier
[full table proof](CRT_HEAP_LIFECYCLE_EXPAND_ORIGIN_REVIEW.md) is reused.
Initialization detects TLS2 support, stores its boolean at `0x005E55F8`, and
registers destroy_fls through FlsAlloc. The 4B FLS index at `0x005B2784` starts
at `-1`. Failed registration returns false. If the first nullable PTD request
fails, initialization releases the allocated FLS index before returning false.
Retirement frees a valid index, resets it to `-1` and returns true.

The slow allocator preserves Win32 LastError and first publishes a `-1` FLS
sentinel. This prevents allocator error handling from recursively allocating
PTD through errno. Failure to publish the sentinel returns null. It then
calloc-allocates one zeroed `0x364`-byte PTD and publishes the real pointer before
construction, allowing construction's nested CRT calls to find that allocation.
Allocation or publication failure attempts to clear the FLS value and frees the
held pointer. Failed clear attempts are not given a new branch. All original
free(null) calls after allocation failure and successful detach remain intact.

The public nullable getter selects FlsGetValue2 when the initialized capability
flag is true. Its legacy FlsGetValue path saves and restores LastError. Both
reject the reentrancy sentinel and use the same slow allocator on a missing
head. The explicit getter uses FlsGetValue under its caller's LastError guard;
for a nonnull head it adds `global_state_index * 0x364`. No index validation is
added. Required head/getter paths abort on failure. Actual
[FLS wrappers and TLS2 capability](CRT_LOCALE_WINAPI_WRAPPER_ORIGIN_REVIEW.md)
retain their already established identities.

## Construction, reference ownership and cleanup

Construction initializes the random state, shared signal-action pointer,
global-locale bit, initial multibyte pointer, both `C` locale-cache characters
and null downlevel-locale state. It increments the multibyte reference under
lock 5, then installs the supplied current locale under lock 4. The PTD block
was zeroed by the allocator; construction does not manufacture extra stores.

The FLS callback returns for null, otherwise destroys the single-state PTD and
frees its allocation. destroy_ptd keeps its ten original free sites: the action
table is conditional on differing from the shared default, followed by nine
owned buffers/context fields. Its separate multibyte and locale guarded owners
release shared references. A multibyte object is freed only when nonnull, at its
last reference and different from the initial static object.

Locale replacement releases the old reference and frees it only if it is
neither current global nor initial locale data and has zero references. It
then assigns the new pointer and adds its reference when nonnull. The four
complete 28B SEH tables at `0x005AC480`, `0x005AC4A0`, `0x005AC4C0` and
`0x005AC4E0` bind every normal/exception unlock to its real parent frame.

## Complete compiler EH and shared metadata

The nullable getter binds its handler through the original prologue to
`0x0056B2D3`. That complete 29B handler references the full 52B unwind/FuncInfo
section at `0x005AC33C`. Its two unwind states both target std_terminate.
Required-head and explicit getters bind the same physical 29B handler at
`0x0056B30D`; both complete SDK handler contributions and both 44B metadata
contributions agree at the shared record `0x005AC370`. Its one unwind state
also targets std_terminate. The 36B FuncInfo portion starts after the owned
unwind map, not at each section's first byte.

Ghidra has no function at either handler address. The attested query preserves
that observation; pinned decoding and complete SDK/target comparison cover all
58 original bytes. Cookie checks, metadata pointers, FrameHandler3 tails and
complete HIGHLOW sets agree. These compiler heads receive one row each; folded
source sections do not create duplicate physical credit. Named std_terminate
and FrameHandler3 dependencies receive no body credit here.

## Errno pointers and complete OS-error mapping

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x00551587` | 127 | OS-error table binary search |
| `0x00551606` | 95 | `__acrt_errno_from_os_error` |
| `0x00551665` | 35 | immediate OS-error mapper |
| `0x00551688` | 36 | mapper into cached PTD host |
| `0x005516AC` | 21 | doserrno pointer getter |
| `0x005516C1` | 21 | errno pointer getter |

These six complete bodies fill all 335B at `0x00551587..0x005516D5`.
The full 45-record/360B table at `0x005989D8` agrees and is strictly ascending.
Codes 1..13 use direct indexing; other eligible codes use the complete unsigned
binary search. Missing entries use the original access range 19..36 or exec
range 188..202, otherwise EINVAL. The immediate mapper writes doserrno then
mapped errno; the cached mapper sets the payload/validity fields consumed by
the already reviewed [PTD host destructor](CRT_SECURE_STRING_INVALID_PARAMETER_ORIGIN_REVIEW.md).

Both pointer getters call the identified nullable PTD owner. Success returns
PTD+0x10 for errno or +0x14 for doserrno. Failure returns writable global cells
at `0x005B26BC` and `0x005B26C0`, initially 12/ENOMEM and 8/Win32 out-of-memory.
They are persistent pointer targets, rather than immutable immediate return
values; callers may write through them. The full two 4B initializers agree.

## Evidence and affected scope

Private `.analysis/origin-boundary/ptd-fls/` retains both SDK members, complete
bounded provider/lifetime/errno listings, the no-function handler query,
locations, `review.py` and `reviewed.json`. The audit compares 23 whole physical
code contributions plus the folded handler alias, all 27 entry partitions,
sixteen INT3 bytes and the complete owned data set. Its 581 distinct data bytes
comprise four SEH tables (112B), unique EH/unwind records (96B), FLS/TLS2 state
(5B), OS-error table (360B) and fallback cells (8B). It rejects the other 14B
PTD implementation through its callee identity and reuses the prior full
initializer-table and WinAPI-wrapper proofs. External locale/signal tables and
callee owners are identified dependencies, outside these owned extents.

Installed source is `ucrt/internal/per_thread_data.cpp` and
`ucrt/misc/errno.cpp`. Only classification, focused evidence, handoff and
generated progress change. All 2,151 protected native input/product hashes
remain unchanged. Exact replay scope is **zero units**, with no new authored
or maintained-source exact credit.
