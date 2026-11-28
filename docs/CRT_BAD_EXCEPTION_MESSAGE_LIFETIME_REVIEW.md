# bad_exception identity and standard exception message lifetime

Eleven complete code contributions close ten pending origins and recover one
destructor in the locked Japanese TH20 Steamless target. All 579 instruction
bytes, 342B of complete class/throw/string data and six zero data-alignment
bytes agree. Natural installed-header emission resolves the target's different
base-class optimization variants without changing maintained native source.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x0040E160` | 60 | exception copy constructor |
| `0x0040E650` | 35 | exception destructor |
| `0x0040EAF0` | 46 | exception scalar deleting destructor |
| `0x004117C0` | 43 | exception what |
| `0x00540E3D` | 17 | bad_exception destructor, recovered |
| `0x00540E4E` | 45 | bad_exception scalar deleting destructor |
| `0x005449F7` | 99 | std exception-data copy |
| `0x00544A5A` | 34 | std exception-data destroy |
| `0x005471CC` | 27 | bad_exception copy constructor |
| `0x005471E7` | 30 | bad_exception default constructor |
| `0x00548610` | 143 | strcpy_s, shared with its template body |

Every existing extent remains unchanged. The recovered destructor's six
instructions are absent from Ghidra's listing; supplemental decoding and the
full archive contribution cover all seventeen bytes. There is no code padding
or owner-local EH table in these selected sections. The secure-copy loop's
original six-byte NOP remains an instruction.

## Class identity distinguishes similar constructors and deleting bodies

Both classes are 12B: vptr, message pointer and an ownership byte with padding.
The default bad_exception constructor zeroes the data, installs the static
`bad exception` message and publishes its vptr. Its copy constructor calls
the real base copy constructor and then installs the derived vptr.

| Class | Vtable | Deleting destructor | what | TypeDescriptor |
| --- | --- | --- | --- | --- |
| exception | `0x0056C47C` | `0x0040EAF0` | `0x004117C0` | `0x005B3030` |
| bad_exception | `0x00597188` | `0x00540E4E` | `0x004117C0` | `0x005B4030` |

The optimized frame.obj deleting bodies have identical ordinary bytes for
both class names. They do **not** establish a target alias: the base vtable
selects its separate 46B header-emitted implementation. The base destructor
is likewise the separate 35B header body; the 17B bad_exception destructor
resets to the base vptr and invokes the common data destroyer.

Both compiler-generated deleting bodies test flag bit one, use sized delete with size
12 when selected, return this in EAX and pop their explicit four-byte flag.
The base body calls its 35B destructor; the derived body inlines its cleanup.
The objects' weak vector-deleting declarations fall back to their scalar
definitions. Their names do not supply a vector-destruction loop absent
from the actual bodies.

The six copy-constructor shapes are distinguished by their real base call
and vptr; five are rejected. Of two default-constructor shapes, the other
is the already reviewed bad_alloc at `0x00540D24`, with its own message and
vtable. Its earlier identity remains unchanged.

## Copying and destroying message storage

The base copy constructor initializes the destination's vptr and full data
storage before calling the 99B runtime copy owner. An unowned source message,
or a null message, copies the pointer and clears destination ownership.
An owned nonnull message uses the original strlen loop, allocates length+1,
copies with strcpy_s, detaches the buffer and sets ownership true. Allocation
failure leaves the initialized destination unchanged. The native cleanup
retains free(null), including after detachment; no new exception or allocation
recovery policy is introduced.

The data destroyer frees the message when its ownership byte is set, then
clears that byte and the pointer. The what method returns a nonnull stored
message or the static `Unknown exception` string at `0x0056C484`. It returns
a borrowed pointer and does not inspect ownership or allocate.

The full 143B strcpy_s and common_tcscpy_s definitions share one physical
head. Null destination or zero capacity reports errno/return 22 through the
existing resumable invalid-parameter helper. Null source first clears a valid
destination, then reports 22. Capacity exhaustion clears destination[0] and
reports 34; a copied terminator returns zero. The original loop, six-byte
NOP and error paths remain, with no extra string fill in this release body.

## Complete metadata independently locates the throw closure

The 18 data sections cover both vtables with their COL prefixes, both complete
RTTI hierarchies and base arrays/descriptors, both TypeDescriptors, two messages
and the complete bad_exception throw closure. The class hierarchies have one
and two base descriptors respectively. Three zero bytes align each 5B/9B
base array before its next selected descriptor: `0x005A32A9` and `0x005A69F5`.

ThrowInfo `0x005AC1FC` selects destructor `0x00540E3D` and the two-entry
catchable array at `0x005AC20C`. The bad_exception record at `0x005AC218`
names its full TypeDescriptor and copy constructor `0x005471CC`; the shared
base record at `0x005A9628` names copy constructor `0x0040E160`. Both use
size 12 and their complete PMD fields. Whole named descriptors, catchable
records and arrays locate this closure independently of FindHandler's fields.
The previously reviewed allocation metadata corroborates the shared base
record and type_info vtable binding.

## Natural header evidence and scope

The installed MSVC 14.44.35207 frame/std_exception members and SDK
10.0.26100.0 x86 strcpy_s member provide the archive contributions. A fresh
private source including `<exception>` and returning a real exception copy
emits the complete 60B/43B/35B/46B base methods with MSVC 19.44.35211 and
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc`.
Full bytes and relocation roles agree. The archive's optimized 50B copy and
14B what variants have no complete target match. These results explain the
local variants, without establishing a game-wide compiler profile.

Private `.analysis/origin-boundary/bad-exception/` retains the complete members,
natural probe, bounded attested listings, failed scalar-alias hypothesis,
constructor negatives, original rows, `review.py` and `reviewed.json`.
Fresh object/receipt are in `build/gpt61-origin-exception-copy/`; earlier
BadArray products remain untouched. Every ordinary byte, branch, REL32/DIR32
role, HIGHLOW field and complete data section agrees. Installed
`vcruntime_exception.h`, `std_exception.cpp` and UCRT secure-copy templates
corroborate the layouts and lifetime protocol.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact
replay scope is **zero units**, with no new maintained-source or authored
exact credit.
