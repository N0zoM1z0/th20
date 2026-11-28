# CRT global retirement: locale, lazy facets and the ten-entry exit stack

The six startup/exit callbacks left pending by the lock review now have
independent library owners. Together with their cleanup dependencies and one
compiler handler, this batch classifies twelve complete bodies: 406 code bytes,
five original alignment bytes and 36 bytes of EH metadata. Two omitted code
entries are added; no source mapping or canonical exact credit is introduced.
The target remains Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

| Entry | Body bytes | Original library role | Origin |
| --- | ---: | --- | --- |
| 0x0040AED0 | 12 | `??__E_Fac_tidy_reg@std@@YAXXZ` | compiler |
| 0x0040AEDC | 12 | `??__Eclassic_locale@std@@YAXXZ` | compiler |
| 0x0040AEE8 | 12 | `??__Einit_atexit@@YAXXZ` | compiler |
| 0x004F5600 | 80 | `??1locale@std@@QAE@XZ` | library |
| 0x00541A11 | 49 | `??1_Fac_node@std@@QAE@XZ` | library |
| 0x00541A42 | 36 | `??1_Fac_tidy_reg_t@std@@QAE@XZ` | library |
| 0x005424BF | 99 | `??1_Init_atexit@@QAE@XZ` | library |
| 0x00542527 | 47 | `?_Atexit@@YAXP6AXXZ@Z` | library |
| 0x00567600 | 29 | `__ehhandler$??1_Init_atexit@@QAE@XZ` | compiler |
| 0x0056B453 | 10 | `??__F_Fac_tidy_reg@std@@YAXXZ` | compiler |
| 0x0056B45D | 10 | `??__Fclassic_locale@std@@YAXXZ` | compiler |
| 0x0056B467 | 10 | `??__Finit_atexit@@YAXXZ` | compiler |

## Startup callbacks identify the original objects

The complete `locale0.obj` startup contributions register `_Fac_tidy_reg` and
`classic_locale`; their exit invokers supply the actual native receivers at
`0x005E4E28` and `0x005E4E1C` before transferring to the corresponding cleanup
functions. `iosptrs.obj` likewise supplies `init_atexit` at `0x005E4EA1` and its
real destructor. The full twelve-byte registrations and ten-byte invokers agree
with the original code and relocation roles, and their original CRT-table
references were retained in the preceding review. The same `iosptrs.obj` also
contains a separate `_Init_locks` instance and its `.CRT$XCC` entries, explaining
the second lock lifetime pair next to the exit controller.

The classic locale registration contains no constructor call. The pinned
`xlocale` header's `_Uninitialized` constructor deliberately leaves `_Ptr`
untouched: locale initialization can placement-construct that static object's
storage before the nominal deferred construction. Its later retirement still
runs the real locale destructor. That source protocol explains the native
registration without inventing a missing initialization call.

## Locale and lazy facet retirement

`std::locale::~locale` at `0x004F5600` checks its implementation pointer at +4,
calls the implementation's virtual `_Decref` at vtable +8, and applies the
virtual scalar deleting destructor only to a nonnull returned pointer. The
classic-locale exit invoker independently identifies its library owner.

The installed `locale0.obj` emits an optimized, guarded 53-byte destructor.
For the native 80-byte body, one bounded probe includes the pinned `<locale>`
header and explicitly destroys a `std::locale`. MSVC 19.44.35211 with
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc` naturally emits
the entire original 80-byte body, with zero relocations and zero byte differences.
This identifies the library method and its ABI. The game's overall build
configuration remains unresolved.

The 36-byte `_Fac_tidy_reg_t` destructor removes the head node from the list at
`0x005E4E24` before destroying it, then frees the node and reads the live head
again. The 49-byte `_Fac_node` destructor operates on the facet pointer at +4,
calls virtual `_Decref`, and conditionally invokes scalar deletion on the result.
Both original indirect-call guard checks remain in the node body. Complete
`locale0.obj` contributions identify the two functions and their distinct
node/facet lifetimes. The facet and its registration node retire separately.

## Encoded exit callbacks and complete EH support

`_Atexit` at `0x00542527` manages ten encoded callbacks at `0x005E4EA4`, with the
cursor at `0x005B2584` initially ten. Registration checks for a full stack,
branches to `abort` when the cursor is zero, encodes the pointer and stores it
after decrementing the cursor. The separate controller destructor advances the
cursor before decoding and invoking each callback, skips decoded nulls and
re-reads the live cursor after each call. This ordering also preserves callback
registration during cleanup.

The controller has a 99-byte instruction body followed by five INT3 bytes;
all 104 bytes agree with its complete `iosptrs.obj` contribution after recording
the original relocation fields. Its independently owned handler at `0x00567600`
is **29 bytes**, including two leading NOPs, security-cookie validation, the EH
metadata load and a tail transfer to `__CxxFrameHandler3`. Treating it as a
simple ten-byte handler would omit the cookie check.

The full 36-byte metadata at `0x005A91B8` agrees byte-for-byte with the object's
`.xdata$x`: magic `0x19930522`, zero state/map counts and pointers, flags 5.
Original HIGHLOW fields and the independent object symbols bind the cookie,
metadata and frame-handler roles. Original import descriptors identify
`EncodePointer` and `DecodePointer`; the guard slot retains the previously
reviewed CRT identity. These complete code/data contributions remain separate
from canonical exact acceptance.

## Evidence and scoped validation

Private evidence is under `.analysis/origin-boundary/locks/`, with original
listings in the adjacent `locks-neighbor-cleanups.txt`, `locks-facet-cleanup.txt`,
`locks-facet-node-and-register.txt` and `locks-atexit-handler.txt` files. Earlier
startup listings and xrefs bind all six callback entries. The private
`reviewed-neighbors.json` captures full contribution sizes, object hashes,
relocation roles and the EH-data hash. The three installed source files are
`stl/locale0.cpp`, `stl/iosptrs.cpp` and `include/xlocale`.

The bounded SDK probe source is `locks/locale-dtor.cpp`; its compile command
and include closure are captured in
`build/gpt61-origin-locale/Locale.receipt.json`, alongside the object. The probe
was built serially at reduced priority. It is retained as origin evidence,
without adding a maintained source owner or match unit.

All twelve bodies have complete attested instruction coverage. Full archive
contributions and the full SDK-emitted destructor were compared; the five
alignment bytes, complete handler and all EH metadata are retained. Tracking,
generated progress and protected executable-input/product hashes pass. Existing
native inputs and canonical roots are unchanged, so **zero canonical exact
units require replay**. The one private SDK compilation addresses the specific
unresolved 80-byte library-origin question.
