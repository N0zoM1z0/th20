# Exact ECL registration and record insertion

CORE/EXACT-127 accepts complete registration at `0x0053FE60` and fifteen
supporting physical functions from the real ECL buffer translation unit. The
sixteen new units cover 1,874 bytes. Existing instruction resolution remains
exact after the same affected object is rebuilt. See the earlier
[wire-header review](ECL_BUFFER_EXACT_RECONSTRUCTION.md) for the fixed 36-byte
file header, 16-byte subroutine prefix and independent record-index anchor.

## Unsigned file-relative addresses

The native registration loop reads an unsigned 32-bit offset, adds the borrowed
file base and stores the resulting address in a record. Neither registration
nor its name predicate dereferences that subroutine-header address. The input
offset table remains unchanged. Header validation and instruction execution are
separate consumers.

Maintained source constructs the address through `std::uintptr_t` before
converting it to the record's byte pointer. This preserves all wire-offset bits
and uses the target's pointer width. On x86 it expresses the observed unchecked
32-bit address addition. It also avoids truncating real pointers in the portable
fixtures. The exact original C++ spelling remains an inference. No temporary,
padding, alternate source body or ABI change is introduced.

The existing actual-owner buffer fixture additionally registers eight unsigned
offset patterns, including `0x80000000` and `0xFFFFFFFF`. It checks the stored
address displacement, original offset word and live name pointer without
executing those opaque records. Other fixtures retain live in-buffer instruction
storage. Existing rejection, stable duplicate insertion, recursive include and
nontransactional allocation-failure checks continue to exercise this source.

## Per-source language profile

One locked MSVC x86 C++17 build explains this object's forwarding and iterator
emission. The production body is shared with portable C++20 semantic tests.

| Whole contribution | C++20 observation | C++17 observation | Native extent |
| --- | ---: | ---: | ---: |
| Registration with unsigned address rebasing | 876 | 876 | 876 |
| Record-vector emplace | 350 | 407 | 407 |
| Wrapped iterator seeking | 20 | 29 | 29 |

The C++17 candidates agree structurally across each complete extent. Canonical
relocation replay, rather than that diagnostic equality, admits the units.
The profile is C++17 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc.
Other translation units retain their recorded profiles. These observations do
not establish the game's global language flags, original STL configuration or
whole-program template/link selection.

## Complete code and physical aliases

| Native entry | Complete bytes | Maintained role |
| --- | ---: | --- |
| 0053FE60 | 876 | Buffer registration |
| 0040B670 | 26 | Name-capture construction |
| 004702B0 / 00470550 | 66 / 67 | Record-vector begin/end |
| 0053FCA0 | 151 | Name search with find_if |
| 00540420 / 0053FB00 | 36 / 407 | Record-vector insert/emplace |
| 0053FDB0 | 57 | Captured-name predicate |
| 00413FA0 / 00414000 | 33 / 37 | Mutable/constant iterator construction |
| 004690E0 / 0046EF50 | 13 / 25 | Iterator unwrapping |
| 004EE740 / 004FCCD0 | 29 / 30 | Wrapped seeking/pointer publication |
| 0040EC90 | 13 | Empty iterator adoption role |
| 0040B280 | 8 | Vector-storage address/forwarding identity |

Each complete COFF function or section boundary is retained. PE control-flow
review finds no omitted instruction heads or external direct branches in these
sixteen roots. Following inter-entry `0xCC` fill is recorded separately and
receives no credit. No root is a target-sized prefix of a larger compiler body.

The file-slot array accessor folds to the existing 22-byte Vector3 index unit at
`0x00414580`. The iterator preclear folds to the existing 31-byte HitCtrlInf
compiler initializer at `0x0040C080`. The range verifier folds to the existing
empty cdecl diagnostic hook at `0x0040C6B0`. Constant/mutable unwrapping and
several forwarding identities also share physical code. Independent alias
checks preserve their actual calling conventions and full extents; physical
addresses receive canonical credit only once.

Native begin/end construct four-byte iterators through a hidden result pointer,
using the real PMR vector's allocator/storage ownership. The predicate receives
the complete eight-byte record by value and returns a bool in AL. Its captured
name is compared with the record name through the independently anchored CRT
strcmp. The sign of that comparison preserves insertion before the first
greater name and the earlier priority of equal names.

## Relocation and exception evidence

Canonical destinations come from reviewed callee bodies, existing canonical
anchors, complete literal payloads and the actual vector/iterator storage
protocol. Literal addresses are independently unique in the locked .rdata
section. Caller relocation fields are navigation leads and never supply a
canonical destination under comparison.

The emplace exception handler is independently identified through its temporary
lifetime and data. A unique unwind map at `0x005ABE90` links state zero to the
temporary cleanup at `0x0056B1E0`. Complete FuncInfo at `0x005ABE98` has one state
and flags one. Its complete 44-byte compiler data contribution replays after
binding the independently identified unwind action and map.

The associated 52-byte code contribution binds the temporary at EBP-0x1C to
destruction at `0x0053FD40`, two existing security-cookie checks and that FuncInfo.
A bounded independent signature search identifies its handler at `0x0056B1ED`;
the emplace DIR32 field is not used to select it. Ghidra omits the two instructions
of the eight-byte cleanup funclet, so the full locked PE contribution is retained
alongside the attested listing. Its runtime tail branch remains an uncredited
dependency. The 52 code and 44 data bytes add no canonical byte credit here.

## Origin and acceptance boundaries

Registration retains its previously reviewed application-authored origin. The
57-byte custom SCPT-name predicate adds a separate authored review. Eleven
complete iterator/vector/algorithm implementations receive library-origin
classification from their pinned SDK bodies and native producer/consumer ABI.
The existing preclear receives compiler-origin classification through independent
automatic MSVC emission for actual HitCtrlInf and ECL iterator owners.

Capture construction, empty adoption and the primitive address identity retain
unknown physical origin because their folded contributors are unresolved.
Verified SDK roles do not automatically exclude possible application contributors.
Neither auto-analysis labels nor byte identity alone establish authorship.

Only the EclLoaderBuffer object is rebuilt. Its new canonical path is
`build/core127-canonical/EclLoaderBuffer.obj`; protect the sibling receipt.
Original inputs and the replaced object's immutable receipt are preserved in
`.analysis/core127-original-inputs.json.gz`. Private observations, boundaries,
alias checks and exception evidence are under `.analysis/core127-*`.

The frozen graph passes 844 complete strict units across 161 objects and 162,849
disjoint comparison bytes. All 80 public tests pass in 322.805 seconds; target,
tracking, reference, build and progress gates pass. One production object was
rebuilt and 160 were reused. Protected retirement removes six replaced products
(311,929 bytes) after preserving original inputs and receipts in a 186,304-byte
archive. All 322 current canonical hashes remain unchanged, and all 844 units
strictly replay after cleanup without another compiler invocation.
