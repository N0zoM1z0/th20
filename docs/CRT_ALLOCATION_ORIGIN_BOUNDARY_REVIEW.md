# CRT allocation, shared failure entries and corrected aligned-new boundary

The allocation roots and new-handler state protocol have reviewed library/compiler
origins, including recovered shared failure and EH entries. The former
3,046-byte aligned-new ledger span combined two disjoint bodies. Independent
complete CRT contributions identify
its 52-byte parent and the separate 28-byte failure helper without discarding
either path. The target is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

| Entry | Code bytes | Independent library symbol | Evidence owner |
| --- | ---: | --- | --- |
| 0x0040E100 | 36 | `??0bad_array_new_length@std@@QAE@XZ` | pinned SDK header probe |
| 0x00540D24 | 30 | `??0bad_alloc@std@@QAE@XZ` | `throw_bad_alloc.obj` |
| 0x00540E7B | 28 | `?__scrt_throw_std_bad_alloc@@YAXXZ` | `throw_bad_alloc.obj` |
| 0x0054273F | 30 | `__freea_crt` | `StlLCMapStringA.obj` |
| 0x0054275D | 48 | `??2@YAPAXI@Z` | `new_scalar.obj` |
| 0x0054278D | 14 | `??3@YAXPAXI@Z` | `delete_scalar_size.obj` |
| 0x00542E42 | 52 | `??2@YAPAXIW4align_val_t@std@@@Z` | `new_scalar_align.obj` |
| 0x00543A0C | 28 | `?__scrt_throw_std_bad_array_new_length@@YAXXZ` | `throw_bad_alloc.obj` |

## Allocation retry and failure selection

The scalar operator calls `malloc(size)` at `0x0054A550`; aligned new calls
`_aligned_malloc(size, alignment)` at `0x00554330`. A successful allocation returns
the pointer. Failure calls `_callnewh(size)` at `0x00552860` and retries when that
returns nonzero. A zero handler result selects the bad-array helper for size
`0xFFFFFFFF`, otherwise the bad-allocation helper. Both final transfers are
nonreturning branches, as the independent CRT source and full objects show.
The underlying heap allocation implementations remain separate review work.

The full original aligned-new listing contains 52 bytes at
`0x00542E42..0x00542E75` and 28 bytes at `0x00543A0C..0x00543A27`.
Ghidra reports 80 actual body addresses, although the old ledger used the
3,046-byte convex span between the first and last addresses. The scalar-new
parent also branches to `0x00543A0C`. The corrected ledger therefore retains
both complete physical entries and every shared failure edge; intervening
functions are not owned by aligned new. Neither parent has an owned EH table
or extra padding in its complete CRT contribution.

## Exception construction and complete shared type records

Each 28-byte throw helper constructs a 12-byte local exception, passes its
address and ThrowInfo to `_CxxThrowException@8` at `0x00544A7C`, then does not
return. Each complete archive contribution also contains one following INT3:
`0x00540E97` and `0x00543A28` are both compared. No fake epilogue is supplied.

The default bad-allocation constructor clears the message/ownership fields,
installs the static `bad allocation` message and publishes its class vtable.
The bad-array constructor calls the private bad-allocation message constructor
with `bad array new length`, then installs the derived vtable. Original vtables
`0x0056C49C` and `0x0056C4A8` have complete-object locators pointing to the same
type descriptors referenced by their exception records.

The audit follows both complete ThrowInfo records at `0x005ABEE8` and
`0x005A9644`, both catchable arrays, all three shared catchable-type records and
all three type descriptors. These ten records total 239 bytes. Complete sizes,
ordinary fields, type names and HIGHLOW sets agree with `throw_bad_alloc.obj`.
The catchable sets are bad_alloc/exception and
bad_array_new_length/bad_alloc/exception. Shared records are checked once;
destructor/copy destinations remain references to their separate bodies.

The archive's optimized bad-array default constructor is 30 bytes and does not
match the original 36-byte method. One natural private source including `<new>`
and allocating `std::bad_array_new_length` emits the full 36-byte SDK method
with locked MSVC 19.44.35211 and
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc`.
All ordinary bytes and the message, base-constructor and vtable roles agree.
This explains the local variant without assuming a single game-wide profile.

## Two distinct deallocation interfaces

The 30-byte `_freea_crt` takes its pointer on the stack, skips null, subtracts
the eight-byte header and invokes the reviewed `_free` at `0x0054A540` only for
marker `0xDDDD`. It corresponds to `internal_shared.h`; the stack marker causes
no release. It is distinct from the previously reviewed 25-byte scoped-buffer
destructor at `0x00542556`, which reads a pointer from its thiscall receiver.

The 14-byte sized scalar delete ignores the size argument and forwards its
pointer to the existing unsized delete at `0x005429FC`. The full body agrees
with `delete_scalar_size.obj` and its source; the size is not a second pointer
or an allocator-selection flag.

## New-handler state, encoding and complete SEH cleanup

The complete UCRT `new_handler.obj` shared text section occupies 317 bytes at
`0x00552860..0x0055299C`. The original and object agree throughout, including
both EH-only prefixes, both normal cleanup entries and all 57 INT3 bytes.
The pointer codecs and two remaining allocator wrappers also agree with their
complete independent contributions.

| Entry | Code bytes | Role | Origin |
| --- | ---: | --- | --- |
| 0x00542E76 | 14 | aligned scalar delete | library |
| 0x0054A550 | 11 | `malloc` forwarding head | library |
| 0x00552860 | 44 | `_callnewh` | library |
| 0x005528A0 | 15 | `__acrt_initialize_new_handler` | library |
| 0x005528C0 | 75 | `_query_new_handler` | library |
| 0x0055290B | 3 | query EH restore prefix | compiler |
| 0x0055290E | 9 | query finally unlock | compiler |
| 0x00552920 | 89 | `_set_new_handler` | library |
| 0x00552979 | 3 | setter EH restore prefix | compiler |
| 0x0055297C | 9 | setter finally unlock | compiler |
| 0x00552990 | 13 | C++ `_set_new_handler(int)` overload | library |
| 0x0055299D | 27 | fast pointer decoder | library |
| 0x005529B8 | 31 | fast pointer encoder | library |

`_callnewh` obtains the current decoded handler, returns zero for null, otherwise
performs the CFG check and invokes the callback with the requested allocation
size. It normalizes any nonzero callback result to integer one. It does not
introduce a catch around the callback.

The initializer stores the supplied encoded value unchanged at `0x005E548C`.
Query acquires UCRT lock index zero, decodes that global and releases the lock.
Setter acquires the same lock, decodes and preserves the previous handler,
encodes the supplied pointer, stores it and returns the previous decoded value.
These use the independently reviewed `_acrt_lock`/`_acrt_unlock` destinations;
the pool is distinct from the STL `_Lockit` critical sections.

For cookie `C` at `0x005B25C0`, the 32-bit decoder computes
`ROR(encoded ^ C, C & 31)`. The encoder computes
`ROR(pointer, 32 - (C & 31)) ^ C`, with x86 rotation-count masking.
The existing Ghidra encoder name describes a different callback signature;
the new-handler object and its actual consumers establish this shared pointer
operation without assigning an exclusive callback type to the physical body.

The legacy integer overload ignores its argument and pushes the value of
`__security_cookie` before calling the pointer-valued setter. The independent
object emits the same operation, including its encoded-null conversion helper.
Preserve that actual operand rather than replacing it with literal zero or
assuming that this overload clears the callback.

Each normal query/set body calls its nine-byte unlock entry directly. The
corresponding SEH table instead targets a three-byte `MOV ESI,[EBP-0x1C]` prefix
that falls through to that same unlock body. Those two prefixes and the legacy
overload were missing from the ledger. All physical heads are retained without
counting either unlock body twice. The complete 60-byte `.xdata$x` section at
`0x005AC2C0` includes both 28-byte scope tables and their four-byte separation;
all ordinary fields and both cleanup-pointer HIGHLOW relocations agree.

The full text partition is 44+20 bytes for the call entry and alignment,
15+17 for initialization, 75+3+9+9 for query, 89+3+9+11 for setter, and 13 for
the legacy overload. This accounts for every byte of the 317-byte section.
The adjacent codec contributions are 27 and 31 bytes. The malloc head retains
its hotpatch/frame instructions before tail-transferring to `_malloc_base`
at `0x005584C0`. Aligned delete ignores the alignment argument and forwards
the pointer to `_aligned_free` at `0x00554310`.

Four provisional ledger spans at `0x0054FEB0`, `0x0054FF00`, `0x0054FFB0` and
`0x00550130` intersected this region. The later
[math dispatch review](CRT_MATH_DISPATCH_ORIGIN_BOUNDARY_REVIEW.md) resolves them
as small public entries and separate distant fallbacks. The original body-union
query remains in `overlapping-provisional-spans.txt` beside the handler evidence.

## Evidence and validation

Private `.analysis/origin-boundary/allocation/` retains complete archive members,
original function/body/constructor listings, full comparisons and `reviewed.json`.
The parent listing is
`.analysis/origin-boundary/allocation-native.txt`. CRT members come from installed
`VC/Tools/MSVC/14.44.35207/lib/x86/libcmt.lib`; the previously extracted cleanup
member is reused from `libcpmt.lib`. Sources are under `crt/src/vcruntime`, plus
the SDK `vcruntime_exception.h` definitions. The natural probe is
`sdk-bad-array.cpp`; its complete object and include/command receipt are retained
in `build/gpt61-origin-allocation/BadArray.obj` and `BadArray.receipt.json`.

`review.py` checks all 266 code bytes, two INT3 bytes, complete instruction
coverage, relocation roles, full HIGHLOW sets, complete shared type records,
RTTI identities and corrected nonoverlapping ledger ranges.

The handler/forwarding review uses `new_handler.obj` and `malloc.obj` from
`Windows Kits/10/Lib/10.0.26100.0/ucrt/x86/libucrt.lib`, plus
`delete_scalar_align.obj` from `libcmt.lib`. Its behavior is read from the complete
original instructions and named object contributions. `remaining-native.txt`,
`new-handler-native.txt` and `reviewed-handler.json` retain that evidence.
`review-handler.py` compares all 400 bytes of the complete shared text, codecs
and forwarding contributions, including 57 alignment bytes, and the entire
60-byte SEH section. Bounded pinned Capstone decoding covers the three unlisted
heads without changing the Ghidra database. All other instructions reuse the
attested listings. No additional compiler run is needed for this part.

Tracking and generated progress pass. All 2,089 protected native inputs/products
retain their hashes. No maintained native input, unit extent or binding changed; canonical
exact replay scope is **zero units**. This review adds no source-present or
exact credit.
