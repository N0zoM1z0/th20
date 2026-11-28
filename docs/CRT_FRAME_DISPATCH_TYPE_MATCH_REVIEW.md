# VCRuntime FrameHandler3 dispatch and type matching

Three complete MSVC 14.44.35207 x86 `libvcruntime.lib(frame.obj)` sections
identify three pending library origins in the locked Japanese TH20 Steamless
target. All 409 contiguous instruction bytes in `0x00547033..0x005471CB`
and all six relocation roles agree. Existing extents remain unchanged;
these sections own no alignment, data or local EH tables.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x00547033` | 142 | TypeMatchHelper for FrameHandler3 |
| `0x005470C1` | 258 | internal FrameHandler3 dispatcher |
| `0x005471C3` | 9 | internal FrameHandler3 wrapper |

## Type matching has two early success paths

A null catch TypeDescriptor or empty name denotes ellipsis and returns integer
one immediately. The bad_alloc compatibility combination also returns one
before normal type or qualifier checks: catch flag 0x80 and catchable flag
0x10 must both be set.

Otherwise, identical TypeDescriptor pointers match the basic type. Different
pointers require equal names, compared by an inlined unsigned-byte strcmp
starting at TypeDescriptor+8. This compares the complete decorated name,
including its first character. It differs from
[std type-info comparison](CRT_TYPE_COMPARISON_MEMBER_BRIDGES_REVIEW.md),
which skips that character. A name mismatch returns zero.

For a basic-type match, catchable by-reference-only flag 2 requires catch
reference flag 8. Throw const flag 1 requires catch const flag 1; throw
volatile flag 2 requires catch volatile flag 2. The x86 body has no unaligned
qualifier test. These ordinary paths return full EAX integer zero or one,
not an AL-only bool contract. Installed `frame.cpp`, `ehdata.h` and
`ehdata_values.h` corroborate the branch order, layouts and flags.

## Internal handler preserves unwind and search distinctions

The dispatcher first calls the previously reviewed context validator, then
the required VCRT PTD getter. When the PTD's rethrow state at +0x20 is zero,
a foreign exception other than STATUS_LONGJUMP can be skipped for an /EHs
function: masked FuncInfo magic must be at least 0x19930522 and EHFlags mask
1 must be set. The function returns ExceptionContinueSearch, value one.

Exception flags masked with 0x66 select the unwind path. It calls
FrameUnwindToEmptyState only when FuncInfo maxState is nonzero and catch
depth is zero, then returns continue-search. It does not perform ordinary
handler search during that path.

In the search path, dispatch is needed when the function has try blocks,
has an exception-specification pointer with magic at least 0x19930521, or
has the noexcept flag (EHFlags mask 4) with magic at least 0x19930522.
The magic field is masked to its low 29 bits. Other cases return one.

Forward compatibility requires the C++ exception code 0xE06D7363, at least
three parameters, exception magic strictly greater than 0x19930522 and a
nonnull ThrowInfo+8 handler. That indirect cdecl call receives the original
eight arguments, with recursive BOOLEAN explicitly zero-extended from its
low byte, and passes the established guard check. Its disposition result
is returned unchanged. Otherwise the dispatcher calls its normal FindHandler
and returns continue-search if that call returns.

The wrapper preserves the original arguments and tail-jumps to this complete
dispatcher. Installed source deliberately omits the FrameHandler4-only
try/finally for FrameHandler3; adding even an empty finally would introduce
an unwind call absent from this nine-byte body.

## Independent callees and rejected short shapes

The full 931B FindHandler section uniquely locates at `0x00546B5A`; the
full 24B FrameUnwindToEmptyState section uniquely locates at `0x0054747F`.
Their complete ordinary-byte signatures independently identify the two
local callees, without deriving either identity from the dispatcher field
being checked. Their complete protocols are now covered by the
[FindHandler owner](CRT_FIND_HANDLER_OWNER_REVIEW.md) and
[frame-unwind review](CRT_FRAME_UNWIND_STATE_REVIEW.md). Context validation,
required VCRT PTD and the guard pointer retain their preceding reviewed
bindings.

The wrapper's nine-byte ordinary shape has sixteen matches. Only
`0x005471C3` jumps to `0x005470C1`; the other fifteen have different callees.
The same shape appears in both public and class TypeMatch wrappers in the
archive, but none of these sixteen target candidates jumps to the complete
TypeMatchHelper at `0x00547033`. Those wrappers remain unlocated, including
interior matches in already reviewed allocation forwarders.

## Evidence and affected scope

Private `.analysis/origin-boundary/frame-dispatch/` retains `review.py`,
`reviewed.json` and original ledger rows. It reuses the complete frame member,
unique-section locations and bounded attested `type-handler-native.txt`
under `.analysis/origin-boundary/type-info/`. All 163 listed instructions,
branches, REL32/DIR32 roles and HIGHLOW sets agree, with no omitted bytes.
The report retains the complete callee identity signatures and each rejected
wrapper's actual destination separately from accepted bodies.

Only classification, evidence, handoff and generated progress change.
All 2,151 protected native input/product hashes remain unchanged. Exact
replay scope is **zero units**, with no new authored or maintained-source
exact credit.
