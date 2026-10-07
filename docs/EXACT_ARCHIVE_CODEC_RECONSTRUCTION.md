# Archive codec, shared dictionary and allocation

EXACT-054 reconstructs sixteen complete native functions in one protocol batch:
2,676 instruction bytes, with no extra function padding. The complete graph has
393 units, 70 cold objects and 61,579 disjoint comparison bytes. Five independently
identified application functions add 841 authored bytes; authored totals become
62 functions and 4,915 bytes. Eleven utility, template and lifetime origins remain
pending. All new bodies require complete canonical relocation replay.

## Native protocol

`archive_decrypt` preserves the signed six-argument cdecl interface and returns
the original input pointer. It first computes the small remainder and odd-byte
tail, allocates a `new[]` copy of `min(size, limit)`, copies that entire range,
then transforms complete blocks from the copy. Within each block it visits the
last byte and every second byte backwards, then the other parity. The byte key
advances after every write. Small/odd tails remain untouched. The block argument
can shrink for the final block. Cleanup releases the original scratch owner and
clears its lvalue through one shared ownership macro.

The maintained valid domain uses nonnegative sizes/limits, positive even blocks,
readable input and a copy limit covering each transformed block. The original
does not add parameter validation, checked arithmetic or an allocation-null
branch. Signed division, copy timing, pointer return and original allocation
family are retained. Header parsing and member reads independently produce all
six arguments. The existing counted filename sum remains a separate 71-byte
exact contribution; it does not imply a complete parameter-table selector.

`archive_decompress` preserves input pointer, signed input length, optional
output pointer and requested allocation size. A null output requests `malloc`
storage through the actual shared allocator; allocation failure returns null.
With caller-supplied output, that size is not a decoder bounds check. Output
must hold all tokens. The caller releases allocated output with `release_bytes`.

The MSB-first reader fetches a byte before testing input exhaustion. Exhausted
input becomes zero bits without cursor advancement. A readable guard byte after
the declared input is therefore part of the fixture/caller contract. The token
flag distinguishes eight-bit literals from thirteen-bit absolute dictionary
offsets. Offset zero terminates; a nonzero offset is followed by a four-bit
length plus three. Backreferences copy sequentially through the same ring,
including overlap and wrapping. The dictionary at 005C6B38 has 8,192 bytes and
survives calls; only the local write cursor resets to one. No per-instance
dictionary or reference implementation's checked-before-fetch policy is imported.

The companion compressor uses that same dictionary and an 8,193-element tree
at 005C8B38. Each real twelve-byte node stores signed parent/left/right indices.
Index 8,192 is the root sentinel and zero is the missing-child sentinel. Seven
complete tree operations preserve native tie handling, eighteen-byte maximum
matches, predecessor replacement, recursive deletion, stale detached child
fields and writes through node zero. Reset clears both complete arrays. The
decoder itself does not call reset.

## Actual allocator and resource

Native startup at 0041E821..0041E869 allocates eight bytes, calls constructor
0041F5B0 and publishes the pointer at 005B8894. Constructor and destructor
independently establish a zero word at offset zero and the real four-slot
`DebugMemoryResource` at offset four. The word's meaning/type and the production
startup constructor remain unresolved; it is recorded storage, not padding.
Tests provide an owned fixture constructor and the two process-global bindings.

Byte allocation/free, typed byte-array allocation/delete and PMR aligned
allocation/delete unconditionally guard shared recursive mutex slot one. The
registry's separate tracking-enabled flag does not control these ordinary
guards. Diagnostic labels are accepted but unused inside the maintained
allocation methods. `malloc/free`, `new[]/delete[]` and aligned `operator new` /
`operator delete` remain distinct families. PMR deallocation ignores the byte
count and passes alignment; the existing always-true equality is retained.

The observed 0x8123 pointer poisoning in array deletion is emitted naturally by
the locked compiler with SDL checks. No manual poison assignment is maintained.
Microsoft documents invalidating the delete operand under
[/sdl](https://learn.microsoft.com/en-us/cpp/cpp/delete-operator-cpp?view=msvc-170).
One GS/EHsc/Gd/SDL recipe now covers all five PMR functions and retains the three
previous exact bodies. The allocator destructor normally destroys its actual
resource member. Its defaulted lifetime and both array-template origins remain
pending, separate from byte identity.

| Address | Body bytes | Operation |
| --- | ---: | --- |
| 004100E0 | 446 | Signed block decryption and scratch ownership |
| 005391F0 | 706 | Persistent dictionary decoder and optional allocation |
| 0041F610 | 88 | Guarded malloc |
| 0041F670 | 85 | Guarded free with null early return |
| 0040D8C0 | 143 | Guarded typed byte-array allocation |
| 0040D840 | 120 | Guarded typed byte-array deletion |
| 0041F5F0 | 23 | Allocator resource destruction |
| 0041F6D0 | 141 | PMR aligned allocation |
| 0041F760 | 81 | PMR aligned deletion |
| 005399A0 | 45 | Dictionary/tree reset |
| 005399D0 | 64 | Root initialization |
| 00539060 | 284 | Tree insertion and longest-match search |
| 00539960 | 52 | Predecessor search |
| 00539180 | 103 | Child replacement and unlink |
| 00539A10 | 153 | Full node replacement |
| 005394C0 | 142 | Recursive node removal |

## Evidence and validation

Complete native instructions, control flow, returns, caller argument producers,
global startup, four-slot resource table, CRT roles and original diagnostic
strings establish canonical anchors independently of comparison fields. Every
new source body is natural maintained C++; no copied decompiler text, assembly,
byte arrays, inert shaping locals or target-sized prefixes are used.

Two whole 39-byte EH handlers, two whole 13-byte cleanup contributions including
their five-byte alignment tails, and two whole 44-byte unwind/data sections also
replay exactly. The array handler 005676ED selects FuncInfo 005A95AC and unwind
table 005A95A4; PMR handler 0056808D selects 005A9B14 and table 005A9B0C. Both
release the live guard at stack offset -14. Independently decoded metadata has
one unwind state and flags one. These six support contributions add no function
or authored coverage.

The public C++20/UBSan fixture checks an independent decryption model over block,
size and limit combinations; guarded tails and unchanged buffer boundaries;
literal/backreference tokens, overlap, wrapping, persistence and exhaustion;
optional output allocation and failure; aligned storage; recursive mutex use;
ownership reset; and all tree deletion cases, matching ties and sentinels. All
25 public tests pass. A full cold build replays all 393 units, retaining prior
components rather than relying on earlier receipts. Target and complete mapped
Ghidra text identity remain locked.

## Reviewed gaps and next batch

The complete 1,036-byte compressor at 00539550 is reviewed. Its byte-flush paths
accumulate a checksum at stack -1C with no identified consumer in this body. Its
buffer allocation is twice the signed input size and the final partial byte is
not flushed. Recover the actual shared bit-writer/checksum protocol and valid
domains before accepting a source body; do not add an inert accumulator merely
to force emission. The seven tree bodies do not claim compressor exactness.

The archive manager retains sixteen bytes of actual record/count/name/stream
ownership. Its parse669, catalog319, lookup101, read596, close151, name-copy97,
integer-cursor37, aligned-name-cursor103 and record-destructor95-byte bodies have
complete native boundary audits. Twelve otherwise unlisted failure jumps are
included: seven in parse, one in catalog construction and four in member read.
No prefix or shortened Ghidra extent is accepted. The derived twelve-byte stream
has an independently decoded eight-slot table at 00576774, with base construction
at 00539040. Recover those real method roles and filename/record cleanup together
when returning to this owner; do not replace them with vector, throwing or fake receiver
interfaces. Parameter-table ownership at 005AE000, loose-file behavior and global
startup remain open. No playable whole-program or filesystem oracle is claimed.

The user's subsequent priority is core large functions. The next main target is
the complete 11,110-byte ECL tick dispatcher at 0053B5C0, including its 98-entry
table, real runtime/stack owner and direct call dependencies. Archive-manager
leaves are deferred while that full dispatcher is pursued. The larger 0048C010
entity dispatcher remains a downstream core target; extracted reference case
handlers do not count as reconstructed standalone native functions.

The previously reviewed [Oracatt/Touhou20](https://github.com/Oracatt/Touhou20)
archive work remains a lead and is credited in README. Its vector/throwing API
does not provide inherited native exact credit. The
[TH095 workflow](https://github.com/N0zoM1z0/th095) remains the control-plane model.
All existing 6,945 reference-body and 113 parser-gap decisions stay unchanged.
