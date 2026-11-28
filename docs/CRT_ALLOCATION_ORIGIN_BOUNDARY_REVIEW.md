# CRT allocation, shared failure entries and corrected aligned-new boundary

Seven pending candidates have reviewed library origins, and one missing shared
throw entry is now inventoried. The former 3,046-byte aligned-new ledger span
combined two disjoint bodies. Independent complete CRT contributions identify
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
The called allocator/handler implementations remain separate review work.

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
RTTI identities and corrected nonoverlapping ledger ranges. Tracking and
generated progress pass. All 2,089 protected native inputs/products retain their
hashes. No maintained native input, unit extent or binding changed; canonical
exact replay scope is **zero units**. This review adds no source-present or
exact credit.
