# Recovered purecall and handler getter

The complete installed MSVC 14.44.35207 x86
`libvcruntime.lib(purevirt.obj)` contribution identifies two missing library
entries in the locked Japanese TH20 Steamless target: the 7B
`__get_purecall_handler` at `0x0054626B` and the 27B `__purecall` at
`0x00546272`. Their complete 35B interval ends with the original INT3 at
`0x0054628D`. It lies between the complete strchr and wcschr owners and
contains 34B/12 instructions, including the getter's original NOP.

## Complete callback and terminating path

The getter returns the raw handler pointer observed at `0x005E52CC` through
the original x86 read/NOP/return sequence. The separate complete
`purevirt_data.obj` defines a 4B null-initialized handler slot; the observed
location agrees with that full loader-zero BSS state. Its address is observed
through the identified getter and is not a new canonical exact-source anchor.

Purecall preserves the supplied ESI value on the stack and calls this getter.
It saves the returned handler in ESI, tests for null, and skips directly to
abort for null. A nonnull pointer is put in ECX for the original indirect-call
guard through `___guard_check_icall_fptr` at `0x0056C37C`, then invoked through
ESI. If that handler returns, execution still calls the real complete abort
owner at `0x00547B43`. The original terminating body has no normal return
epilogue. No callback-result test or synthesized return is added.

The guard pointer and its initial 3B fastcall nop at `0x005435EA` retain
[their preceding complete proof](CRT_EXCEPTION_VALIDATION_NLG_REVIEW.md).
The real abort retains its existing complete origin review. All ordinary
bytes, the getter DIR32, both caller REL32 fields, the guard DIR32 and their
complete HIGHLOW sets agree. The parent has no local EH metadata.

## Independent virtual roots distinguish the tiny getter lookalike

The preceding full facet lifetime/RTTI proof places `0x00546272` in both
pure-virtual slots of the `_Facet_base` vtable at `0x0057268C`. Both original
pointers and their HIGHLOW records remain present. The complete purecall
body matches uniquely and names the getter immediately preceding it.

The getter's ordinary seven-byte shape also matches `0x005571C0`. That entry
is the independently reviewed query_new_mode and reads the different slot
`0x005E55E0`. The actual purecall REL32 selects `0x0054626B`; the other shape
receives no duplicate identity or origin credit. The member's exchange/read
template helpers and purecall-handler setter have no complete location here.

Ghidra's bounded attested listing returns zero instructions for the entire
35B interval, and its reference query misses the original getter call.
Bounded decoding of the locked bytes recovers all twelve instructions and
the final INT3 without changing the analyzer database. The vtable roots,
complete member and actual control flow establish the entries despite those
listing omissions.

## Evidence and affected scope

Private `.analysis/origin-boundary/purecall/` retains both members and archive
provenance, the attested empty listing, complete decoded supplement, full
comparison, getter negative and original empty row selections. The earlier
facet roots and exception-validation guard evidence are reused. Installed
`vcruntime/purevirt.cpp` and `purevirt_data.cpp` corroborate the raw handler,
conditional call and unconditional terminating continuation.

Two missing entries are added without changing a preceding extent. All 2,151
protected native input/product hashes remain unchanged. Tracking/progress
checks pass. Exact replay scope is **zero units**, with no new authored or
maintained-source exact credit.
