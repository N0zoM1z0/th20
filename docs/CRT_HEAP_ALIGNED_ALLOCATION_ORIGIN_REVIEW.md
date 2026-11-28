# CRT heap bases, aligned owners and new-mode state

Twenty-five pending entries are library code in the heap allocation protocol.
Seven complete Windows SDK 10.0.26100.0 x86 `libucrt.lib` code contributions
agree with the locked Japanese TH20 v1.00a Steamless target: 5,463 instruction
bytes and all 220 original INT3 alignment bytes, 5,683 bytes in total. Existing
body boundaries remain valid. The complete 5,124B `align.obj` section contains
sixteen distinct public/internal entries; identical ordinary bytes do not make
their physical owners interchangeable.

## Complete aligned allocation section

`align.obj` occupies `0x00554310..0x00555713`. All of its 152 relocation fields,
full HIGHLOW set, internal branches and 179 INT3 bytes are retained in the
comparison. There is no owned EH or table section in this object. The internal
names below come from the archive's static decorated function symbols.

| Entry | Body bytes | Archive operation |
| --- | ---: | --- |
| `0x00554310` | 26 | `_aligned_free` |
| `0x00554330` | 101 | `_aligned_malloc` |
| `0x005543A0` | 137 | `_aligned_offset_malloc` |
| `0x00554430` | 74 | `_aligned_msize` |
| `0x00554480` | 508 | `_aligned_offset_realloc` |
| `0x00554690` | 672 | `_aligned_offset_recalloc` |
| `0x00554940` | 396 | `_aligned_realloc` |
| `0x00554AE0` | 564 | `_aligned_recalloc` |
| `0x00554D20` | 26 | internal `_aligned_free_base` |
| `0x00554D40` | 101 | internal `_aligned_malloc_base` |
| `0x00554DB0` | 74 | internal `_aligned_msize_base` |
| `0x00554E00` | 135 | internal `_aligned_offset_malloc_base` |
| `0x00554E90` | 513 | internal `_aligned_offset_realloc_base` |
| `0x005550A0` | 658 | internal `_aligned_offset_recalloc_base` |
| `0x00555340` | 396 | internal `_aligned_realloc_base` |
| `0x005554E0` | 564 | internal `_aligned_recalloc_base` |

Complete-context placement distinguishes the two 26B frees, the two 101B
allocators, both 74B size methods, both 396B reallocators and both 564B
recallocators. The independent [aligned-new owner](CRT_ALLOCATION_ORIGIN_BOUNDARY_REVIEW.md)
already calls the public `_aligned_malloc` at `0x00554330`; aligned delete calls
the public free at `0x00554310`. The entire archive section fixes the remaining
static/public placements without selecting an arbitrary identical-body match.

The shipped `ucrt/heap/align.cpp` explains the protocol. Alignment must be a
nonzero power of two, then is raised to at least four bytes. Offset allocation
requires zero offset or `offset < size`. The owner computes the pointer-sized
header, offset gap and alignment slack, checks addition overflow, and allocates
through the already reviewed `malloc` at `0x0054A550`. It stores the original
allocation pointer just before the aligned user view. Free rounds the user
address down to a four-byte boundary, loads the preceding original pointer and
calls `free` at `0x0054A540`; null free remains an immediate return.

Aligned resize first handles null block through allocation, then an existing
block with size zero through free. It validates alignment/offset, recovers the
original pointer, computes available bytes with `_msize_base`, and limits the
copy to the smaller of available and requested data. Its in-place `_expand`
attempt is conditional on the old/new layout being safe. On failed expansion
it restores the saved errno before trying malloc. Moving uses `memmove`, and
the old allocation is freed only after a successful replacement and copy.
The returned view and stored original-pointer header are both updated.

Aligned recalloc preserves the count/product guard and computes its fill start
through the aligned size method, then zeroes only successful growth. The size
method subtracts header/footer/alignment overhead from the underlying heap size.
Its actual null branch reports EINVAL and returns `size_t(-1)` if the invalid
parameter handler returns; a nearby SDK comment describing a zero return is
inconsistent with both the implementation and original instructions.

## Base allocation, size and patchable forwarding

| Entry | Body bytes | Library role | Member |
| --- | ---: | --- | --- |
| `0x005584C0` | 81 | `_malloc_base` | `malloc_base.obj` |
| `0x00557B40` | 96 | `_calloc_base` | `calloc_base.obj` |
| `0x0055DC90` | 105 | `_realloc_base` | `realloc_base.obj` |
| `0x0055F5B0` | 109 | `_recalloc_base` | `recalloc.obj` |
| `0x0055F630` | 11 | `_recalloc` forwarding head | `recalloc.obj` |
| `0x0055F810` | 51 | `_msize_base` | `msize.obj` |
| `0x0055F850` | 11 | `_msize` forwarding head | `msize.obj` |
| `0x005571C0` | 7 | `_query_new_mode` | `new_mode.obj` |
| `0x005571D0` | 47 | `_set_new_mode` | `new_mode.obj` |

`_malloc_base` rejects sizes above `0xFFFFFFE0`, normalizes zero to one byte,
then calls HeapAlloc. `_calloc_base` checks product overflow using division,
also normalizes a zero product to one byte, and uses HeapAlloc flag 8 for
zero initialization. `_realloc_base` handles a null block before its zero-size
branch: null/zero delegates to malloc and its one-byte request, whereas an
existing block/zero frees it and returns null. Nonzero resize uses HeapReAlloc.
These loops preserve `_query_new_mode` and `_callnewh` at `0x00552860`: a
successful handler requests a retry; disabled/failed handling returns null with
ENOMEM (12). Source evidence is in the corresponding installed `heap/*.cpp`
files and the [existing new-handler review](CRT_ALLOCATION_ORIGIN_BOUNDARY_REVIEW.md).

`_recalloc_base` checks the product bound, obtains old storage size through
`_msize_base`, calls `_realloc_base`, and fills only the successful growth from
the old measured size. `_msize_base` validates nonnull input, otherwise sets
EINVAL (22), calls the invalid-parameter handler and retains its `-1` return.
The valid path returns HeapSize directly. The independent 11B public wrappers
tail-transfer to these base owners, preserving each physical head.

The complete recalloc section is 139B: 109B base, nineteen INT3 bytes and the
11B wrapper. The msize section is 75B: 51B base, thirteen INT3 bytes and the
11B wrapper. These alignment bytes are not clipped out of the evidence.

## Shared state and independently named imports

All reviewed base allocators and the earlier `_free_base` use `__acrt_heap` at
`0x005E5990`. The PE import lookup table independently names these original
IAT slots, agreeing with SDK relocation roles:

| IAT slot | Import |
| --- | --- |
| `0x0056C0E4` | `KERNEL32.dll!HeapAlloc` |
| `0x0056C0A8` | `KERNEL32.dll!HeapReAlloc` |
| `0x0056C080` | `KERNEL32.dll!HeapSize` |

The new-mode getter and setter share a four-byte state cell at `0x005E55E0`.
The archive gives it BSS storage, and the PE places it in zero-filled virtual
data. The getter retains its MOV, NOP and return; nine following INT3 bytes
complete its interval. The setter accepts only 0/1, exchanges the cell with a
memory XCHG and returns the old mode. Other inputs set EINVAL, call the
invalid-parameter handler and return `-1` if it returns. The entire shared
new-mode text section is 63B. Mode controls whether malloc-family failures use
the new-handler protocol; it does not replace that separately owned callback.

Other recorded external roles include `_expand` at `0x0055F720`, `memmove` at
`0x00543E20` and `memset` at `0x00544760`. Their bodies remain separate owners.
Heap-handle initialization and the `_expand` family are useful next scopes.

## Evidence and affected scope

Private `.analysis/origin-boundary/heap/` retains the seven members,
`locations.json`, bounded `aligned-native.txt` / `base-native.txt`, `review.py`
and `reviewed.json`. The full aligned Ghidra query reached its 1,800-instruction
limit; pinned Capstone supplements the remaining 214 original code bytes.
Every complete body decodes to its ledger end. All local branches, explicit
external tail transfers, 183 archive relocation fields, full HIGHLOW sets and
the entire 220B alignment set pass the review. The whole shared align section
and both base/wrapper sections prevent target-sized-prefix acceptance.

Only the twenty-five rows in each classification ledger, evidence, handoff and
generated progress change. All 2,151 protected native input/product hashes stay
unchanged. Exact replay scope is **zero units**; this archive/source origin
review adds no authored or maintained-source exact credit.
