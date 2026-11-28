# CRT exception-object lifetime and termination scopes

Eleven complete installed CRT contributions establish ten pending origins
and seven recovered entries in the locked Japanese TH20 Steamless target.
All 538 instruction bytes, four INT3 bytes and 60B of SEH/strong callback
data agree. The original destructor and terminate owners are partitioned
without dropped or duplicated bytes. Other existing extents remain unchanged.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x005463E0` | 103 | DestructExceptionObject primary |
| `0x00546447` | 14 | recovered destruction filter |
| `0x00546455` | 5 | recovered destruction handler |
| `0x0054645A` | 46 | recovered WinRT/return continuation |
| `0x00546488` | 13 | stdcall member-call bridge |
| `0x00546495` | 87 | FilterSetCurrentException |
| `0x005464ED` | 38 | destruction eligibility query |
| `0x00546513` | 37 | PMD pointer adjustment |
| `0x00546538` | 85 | FrameUnwindFilter |
| `0x0054658E` | 9 | current-exception slot getter |
| `0x00546597` | 9 | current-context slot getter |
| `0x005465A0` | 5 | recovered std_terminate |
| `0x00547AC8` | 28 | unexpected |
| `0x00547B87` | 40 | terminate primary |
| `0x00547BAF` | 4 | recovered always-accept filter |
| `0x00547BB3` | 3 | recovered terminate handler |
| `0x00547BB6` | 12 | recovered state-reset/abort continuation |

The providers are libvcruntime.lib's `ehhelpers.obj`/`unexpected.obj` and
Windows SDK 10.0.26100.0 x86 libucrt.lib's `terminate.obj`.

## Strong destruction callback and accepted record format

The complete four-byte readonly definition at `0x00597180` points to
`0x005463E0`, including its original DIR32/HIGHLOW. The destructor is
independently located through its whole 168B SDK section; its address is
not obtained by solving the callback field. This closes the named callback
dependency in the [SEH4 dispatcher](CRT_SEH4_COOKIE_DISPATCH_REVIEW.md).
The selected definition comes from ehhelpers rather than the dispatcher's
four-byte common-null fallback.

Destruction first requires a nonnull exception record, code 0xE06D7363,
three parameters and magic 0x19930520, 0x19930521 or 0x19930522. A nonnull
ThrowInfo with a nonzero unwind-function pointer invokes that member
destructor through the 13B bridge. The bridge receives two stack arguments,
loads this into ECX, calls the supplied pointer and returns with RET 8.
It does not add the guard check present on the separate COM call path.

Only that member call is inside the try scope. The filter reads the low
byte of the original BOOLEAN throw-policy argument. If it is true and the
new exception passes the same full MSVC-format predicate, the filter saves
the new record/context in VCRuntime PTD and calls terminate. Other cases
return EXCEPTION_CONTINUE_SEARCH/0. The source's broad destructor-throw
comment does not replace these actual format and policy conditions.

When no member destructor exists, ThrowInfo attribute 0x10 selects the
separate WinRT path. The first pointer in the exception-object storage is
treated as IUnknown; if nonnull, its vtable slot +8 is invoked as Release,
with the original guard check and stdcall argument. This path remains
outside the active member-destructor try scope. No new object-pointer
validation or broader catch scope is introduced.

## Complete destruction scope and continuation

The whole 168B contribution consists of a 103B primary, 14B filter, 5B
handler and 46B continuation. The handler restores parent ESP and jumps to
the existing state-reset path; the continuation owns WinRT Release and the
shared epilogue. The full 28B SEH table at `0x005AC0F8` has header
`-2,0,-40,0` and record `-2,0x00546447,0x00546455`. These independent
relocated entries identify Ghidra's omitted filter and handler bytes.

## Frame-chain eligibility, PMD adjustment and PTD identity

The eligibility query follows VCRuntime PTD's frame-info chain at +0x24.
Each record contains the exception-object pointer at +0 and next at +4.
A raw pointer match returns false; reaching the end returns true. The
query neither unlinks frames nor destroys or frees anything.

PMD adjustment starts with object+mdisp. If pdisp is negative it returns
that address. Otherwise it loads the vbtable pointer from object+pdisp,
reads the signed 32-bit displacement at **byte offset** vdisp, then adds
that displacement and pdisp. The original 32-bit loads and absence of
null checks remain; vdisp is not scaled as an array index.

The two nine-byte helpers return addresses of VCRuntime PTD fields +0x10
and +0x14, rather than loading their exception/context values. Their required
getter is `__vcrt_getptd` at `0x005467D6`. This differs from UCRT's required
getter at `0x005579C2`; the two PTD layouts are not interchangeable.

## Frame unwind has a different predicate

FrameUnwindFilter tests exception code 0xE06D7363 alone, without the full
three-parameter/magic predicate above. That path publishes the current
exception/context and terminates. For managed codes 0xE0434F4D and
0xE0434352 it decrements the signed ProcessingThrow count at PTD+0x18 only
when positive, then returns continue-search/0. Other codes also return zero.
The strict destructor predicate is not substituted into this separate filter.

## Terminate and unexpected retain different escape policies

Terminate reads UCRT PTD's callback at +0x0C. A nonnull handler runs under
a scope whose four-byte filter always returns execute-handler/1. Handler
return or any escaping structured exception reaches the same state-reset
and abort continuation; null callback goes directly to abort.

The complete 60B SDK contribution contains 40B primary, 4B filter, 3B
handler, 12B continuation and one final INT3. The 59 instruction bytes
of the old candidate remain covered once. Its full 28B scope table at
`0x005AC238` has header `-2,0,-40,0` and record
`-2,0x00547BAF,0x00547BB3`. The handler restores ESP and falls into the
continuation. No return is invented after the terminal abort call.

Unexpected instead reads VCRuntime PTD's callback at +4. It has no such
catch scope: a thrown handler exception may escape. Missing or returning
handler calls terminate. Its whole section is 28 instruction bytes plus INT3.

The five-byte std_terminate entry jumps to the real whole terminate owner.
Earlier complete C++ EH metadata independently names this entry at
`0x005465A0`; its resolved callee agrees with the complete ehhelpers section.
The other 5,245 ordinary branch candidates do not receive an identity from
that shape. Getter/setter/default-adapter sections without complete target
matches remain uncredited.

## Evidence and affected scope

Four original INT3 bytes follow FilterSetCurrentException, FrameUnwindFilter,
unexpected and terminate. The complete code intervals are
`0x005463E0..0x005465A4`, `0x00547AC8..0x00547AE4` and
`0x00547B87..0x00547BC2`. The two 28B scope tables and four-byte strong
callback definition form the complete 60B data scope. Unreferenced SDK RTTI
and WinRT callback definitions receive no ownership claim from this proof.

Private `.analysis/origin-boundary/exception-lifetime/` retains the full
members, bounded attested listings, search/relocation details, `review.py`,
`reviewed.json` and original ledger rows. The audit covers every ordinary
byte, branch/call, REL32/DIR32 and HIGHLOW, complete scope closures, the
strong readonly callback and prior independent std_terminate references.
Pinned decoding covers Ghidra's omitted funclets and five-byte helper without
changing its database. Source corroboration is the installed VCRuntime
`ehhelpers.cpp`/`unexpected.cpp` and UCRT `misc/terminate.cpp`.

Only classification, focused evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact replay
scope is **zero units**; no authored or maintained-source exact credit is added.
