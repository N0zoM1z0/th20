# VCRuntime type comparison and member-call bridges

Five whole MSVC 14.44.35207 x86 `libvcruntime.lib` contributions identify
five pending library origins in the locked Japanese TH20 Steamless target.
All 137 instruction bytes, the single call relocation and three final INT3
bytes agree. Every existing extent remains unchanged.

| Entry | Bytes | Member and role |
| --- | ---: | --- |
| `0x0054677E` | 60 | std_type_info.obj: std type-info comparison |
| `0x00547205` | 31 | frame.obj: type_info equality |
| `0x0054761F` | 16 | frame.obj: one-argument member-call bridge |
| `0x0054762F` | 19 | frame.obj: two-argument member-call bridge |
| `0x00547642` | 11 | frame.obj: getESTypes |

The last three bodies occupy `0x0054761F..0x0054764C`, followed by the
three INT3 bytes before the next owner at `0x00547650`. None of the five
sections owns data, a vtable, RTTI descriptors or an EH table. The only
relocation is the equality wrapper's REL32 call to the complete comparison
provider; there are no HIGHLOW fields in this scope.

## Comparison addresses, characters and return width

The cdecl comparator first compares its two `__std_type_info_data` pointers.
Equal pointers return zero without reading name bytes. Otherwise it compares
strings at data+5: four bytes skip the cached undecorated-name pointer, and
one skips the leading decorated-name character. The native loop processes
up to two bytes per iteration, stopping on a null or mismatch. Carry from
the byte comparison produces -1 or 1; equal strings produce zero. This is
unsigned-byte lexicographic order, not subtraction of signed char values.

The installed `std_type_info.cpp` explicitly compares `_DecoratedName + 1`.
The compiler inlines strcmp in this archive contribution. The cached
undecorated pointer neither supplies comparison text nor changes the result.

The thiscall equality wrapper passes class+4 data addresses for both objects
to that provider. It converts zero to bool true and nonzero to false in AL,
then returns popping the single four-byte explicit argument. Its other EAX
bits are not a full-width integer boolean contract. The complete
`frame.obj` wrapper identifies the comparator independently of its Ghidra
name and corroborates `vcruntime_typeinfo.h`'s layout and inline equality.

## Member-call ABI and exception-specification pointer

Both member-call bridges have a void stdcall interface. They load the first
argument into ECX as the member's this pointer and invoke the second
argument as a thiscall target. The first bridge pushes one explicit pointer
argument and returns with RET 12. The second pushes its final integer and
then its pointer argument, returning with RET 16. No local exception
handler or guard-check call appears in either complete body. The installed
`trnsctrl.h` definitions use `__declspec(guard(ignore))` and the corresponding
natural thiscall function-pointer casts.

The retained full `frame.obj` member and `frame.cpp` also identify their
catch-object construction roles. The two-argument form carries the extra
integer used for the virtual-base copy-constructor case. This review does
not change the enclosing catch-object construction owner.

The cdecl getESTypes helper simply returns the pointer at FuncInfo+0x1C.
Installed `ehdata.h` defines the x86 absolute `pESTypeList` at that offset,
and `frame.cpp` returns `FUNC_PESTYPES`. The body adds no null, version or
magic-number test and does not convert an image-relative displacement.

## Evidence and remaining owners

Private `.analysis/origin-boundary/type-info/` retains the two full archive
members, bounded attested listings, locator/relocation results, original
ledger rows, `review.py` and `reviewed.json`. Every instruction and branch,
the complete REL32 role, absence of HIGHLOW and final alignment agree.
No instruction is omitted from these five bounded listings.

The same member search found no complete target match for std type-info
name, hash or name-list cleanup. Their generic allocation/free callbacks
and pointer-getter shapes confer no additional identity. Nearby
`0x005471CC` and `0x005471E7` are now the reviewed bad_exception copy/default
constructors in the [complete class/message proof](CRT_BAD_EXCEPTION_MESSAGE_LIFETIME_REVIEW.md).
The nine-byte frame-handler wrapper at `0x005471C3` also has its
[full dispatcher/callee review](CRT_FRAME_DISPATCH_TYPE_MATCH_REVIEW.md).

Only classification, evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact
replay scope is **zero units**, with no new authored or maintained-source
exact credit.
