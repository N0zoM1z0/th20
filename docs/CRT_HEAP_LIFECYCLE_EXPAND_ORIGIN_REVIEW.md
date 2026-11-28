# CRT heap lifetime, initializer rollback and in-place resize

Nine library entries complete this heap-control group, including four missed
heap-handle heads. Four whole Windows SDK 10.0.26100.0 x86 `libucrt.lib` code
contributions match 416 instruction bytes plus 45 original INT3 bytes. The full
128B initializer table independently pairs heap initialization and shutdown.
The target is the locked Japanese TH20 v1.00a Steamless executable.

| Entry | Body bytes | SDK symbol / role | Member |
| --- | ---: | --- | --- |
| `0x0055F640` | 6 | `_get_heap_handle`, recovered public getter | `heap_handle.obj` |
| `0x0055F650` | 17 | `__acrt_initialize_heap`, recovered | `heap_handle.obj` |
| `0x0055F670` | 10 | `__acrt_uninitialize_heap`, recovered | `heap_handle.obj` |
| `0x0055F680` | 6 | `__acrt_getheap`, recovered internal getter | `heap_handle.obj` |
| `0x0055F686` | 104 | `__acrt_execute_initializers` | `shared_initialization.obj` |
| `0x0055F6EE` | 49 | `__acrt_execute_uninitializers` | `shared_initialization.obj` |
| `0x0055F720` | 11 | `_expand`, patchable forwarding head | `expand.obj` |
| `0x0055F730` | 151 | `_expand_base` | `expand.obj` |
| `0x0055F7D0` | 62 | `is_contraction_possible` | `expand.obj` |

## Process heap ownership and complete handle block

The four handle entries occupy the complete 70B block at
`0x0055F640..0x0055F685`. Its 39 instruction bytes and 31 INT3 bytes all agree
with the archive. The initializer calls `KERNEL32.dll!GetProcessHeap` through
the original IAT slot `0x0056C084`, stores its result at `__acrt_heap`
(`0x005E5990`), and reports nonnull success in AL. This is the same slot used by
the [reviewed heap allocators](CRT_HEAP_ALIGNED_ALLOCATION_ORIGIN_REVIEW.md).
The defining archive contribution gives it four BSS bytes; the original PE
places it in zero-filled virtual data.

The uninitializer clears that slot and returns true in AL. It does not call
HeapDestroy or destroy the process heap. Both six-byte getters read the current
CRT slot, so a read after uninitialization returns the cleared value. Their
ordinary bytes alone have many possible matches; the full nontrivial block,
shared heap operand and paired initializer-table records fix these two distinct
physical owners. The SDK source is `ucrt/heap/heap_handle.cpp`.

The complete `initialization.obj` table at `0x00599410..0x0059948F` contains
sixteen initializer/uninitializer pairs and 25 nonnull pointer relocations.
All ordinary/null fields and the full HIGHLOW set agree. The heap pair is at
offsets `0x28`/`0x2C`: original fields `0x00599438` and `0x0059943C` point to
`0x0055F650` and `0x0055F670`. Attested Ghidra data references independently
show both fields even though these callback heads were absent from its function
inventory. Other table callbacks remain separate review scopes.

## Forward startup, reverse rollback and reverse shutdown

The complete 104B executor visits eight-byte records in `[first,last)` from
first to last, skips null initializers and tests each callback's boolean in AL.
A failure rolls back only earlier records, in reverse order; each rollback
requires both its initializer and uninitializer to be nonnull. It passes
literal false to those uninitializers and returns false in AL. An empty range
or full success returns true. The failed record itself is not rolled back.

The separate 49B normal shutdown executor visits the same kind of range in
reverse. It calls every nonnull uninitializer, including records whose
initializer is null, always passes false, ignores the callback result and
returns true in AL. Both executors retain the guard-pointer checks at
`0x0056C37C`; no exception-catching branch is added. Their complete independent
archive sections and `ucrt/internal/shared_initialization.cpp` establish these
different rollback/shutdown rules.

## In-place resize and failed contraction

The public `_expand` head tail-transfers to the complete base at `0x0055F730`.
The full shared section is 238B: 11B head, five INT3 bytes, 151B base, nine
INT3 bytes and the 62B predicate. The complete section fixes the head despite
several identical eleven-byte forwarding shapes elsewhere in the executable.
The earlier aligned reallocators independently call this public head.

The base requires a nonnull block and checks the `0xFFFFFFE0` size bound.
A zero request becomes one byte. It obtains old size through HeapSize and uses
HeapReAlloc flag `0x10`, preserving the in-place-only contract. This differs
from `_realloc_base`: it does not allocate a replacement for null, free an
existing block for zero, or enter the new-handler retry loop.

On a failed resize, a requested size no greater than the old size leads to the
contraction predicate. An old size above `0x4000` returns true immediately.
Smaller sizes use HeapQueryInformation class zero to query heap compatibility;
query failure or heap type two (LFH) returns false. When contraction is deemed
unavailable, the base reports success by returning the original block. It does
not replace that result with null merely because HeapReAlloc failed.

The remaining failure path obtains GetLastError after that control flow, maps
it through `__acrt_errno_from_os_error` at `0x00551606`, stores errno and returns
null. The aligned caller's separate saved-errno/malloc fallback remains as
recorded in the [aligned allocation review](CRT_HEAP_ALIGNED_ALLOCATION_ORIGIN_REVIEW.md).
The complete SDK implementation is `ucrt/heap/expand.cpp`.

The PE import lookup table independently names the GetProcessHeap, HeapSize,
HeapReAlloc, HeapQueryInformation and GetLastError IAT fields; all agree with
the archive relocation roles. Initialization/termination and contraction
predicate results use AL booleans, while handle/pointer results use EAX.

## Evidence and affected scope

Private evidence is in `.analysis/origin-boundary/heap-control/`: extracted
objects, `handle-native.txt`, `handle-references.txt`, `executor-native.txt`,
`expand-native.txt`, `review.py` and `reviewed.json`. Pinned contiguous decoding
supplements the twelve getter bytes absent from Ghidra's instruction listing.
The audit checks all 461 code-section bytes, all local branches and the public
tail, both original callback fields, all 128 table bytes, complete HIGHLOW sets
and independently named imports. Searches of `heapchk`/`heapmin`/`heapwalk`
members produced no full ordinary-byte location; no addresses are inferred
from those unmatched sections.

Only classification, evidence, handoff and generated progress change. All 2,151
protected native input/product hashes remain unchanged. Exact replay scope is
**zero units**, with no authored or maintained-source exact credit added.
