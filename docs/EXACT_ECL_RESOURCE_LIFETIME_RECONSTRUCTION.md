# Whole ECL resource initialization and destruction

EXACT-068 adds five whole contributions / 252 instruction and comparison bytes.
The frozen source graph has 505 units / 94 objects / 90,373 disjoint comparison
bytes. Origins remain independently tracked: 432 pending / 9 library / 64
authored contributions; 16,948 authored bytes are unchanged. This closes the
base resource lifetime used by the larger script-loading protocol.

| Canonical unit | Native entry | Complete bytes | Maintained owner |
| --- | --- | ---: | --- |
| ecl_loader_ctor | 004A3650 | 119 | EclLoaderBase.cpp |
| ecl_loader_dtor | 004A3D40 | 49 | EclLoaderBase.cpp |
| ecl_loader_scalar_dtor | 004A4150 | 49 | EclLoaderBase.cpp, compiler generated |
| ecl_loader_include_default | 00414B50 | 15 | EclLoaderBase.cpp |
| script_stack_dtor | 0048B900 | 20 | EclLoaderBase.cpp, implicit member cleanup |

## Native observations and independent anchors

The base constructor sets its vptr, clears the two counts, zero-initializes two
256-byte arrays, constructs the PMR eight-byte record vector at +524 and the
actual 24-byte ScriptStack at +540. The complete native array-index helper at
00414580 corroborates std::array indexing for the 64 file pointers. These
fields retain the previously established 564-byte x86 base layout. The parallel
array's higher-level role remains unknown.

Native COL/type-descriptor data independently identifies the original global
class spelling `SptResourceInf`. The table at 005703A0 has two folded 00414B50
entries followed by deleting destructor 004A4150. EclLoader is the maintained
semantic role name. This evidence binds the table relocation without solving a
field under comparison; no complete RTTI/vtable data reconstruction is claimed.

The ordinary destructor restores the base vptr and destroys globals before
records. The implicit ScriptStack destructor calls unsigned word-vector cleanup
0048B830, independently bound through the already accepted signed word-vector
destructor alias in cursor_destruct. Both have trivial four-byte elements. Record
cleanup 00414440 has independent callers at 00416840 and 00416CA5; its complete
00414E10 child computes the capacity in eight-byte elements, deallocates through
the actual captured PMR resource, and clears the three storage pointers.

Default PMR record construction uses the same folded default-instantiation
endpoint 004141C0 as the independently accepted ScriptStack constructor. Native
default-resource access at 00541550 selects the configured resource at 005E4D28
or the fallback object at 005B2578. Neither default constructor allocates element
storage. This is allocator capture, rather than an invented null allocator.
These library dependencies receive no additional coverage credit.

The complete scalar deleting destructor calls base cleanup, tests flag bit one,
and calls sized delete with the real 564-byte size when requested. Sized delete
0054278D is independently bound by shot_control_block_scalar_dtor. The generated
member returns the original receiver and uses RET 4.

The default second virtual callback returns zero and uses RET 4. The native
derived 004A5BE0 implementation consumes a writable include block with ANIM/ECLI
markers; the complete append caller supplies buffer +0x24. This recovers the
pointer argument and maintained name include_resources. The derived body and
the first callback's higher-level contract remain open. The two folded base
entries receive one physical exact unit.

## Source, compiler and owned behavior

EclLoaderBase.cpp contains natural field initialization, a defaulted destructor
and the default include callback. The compiler emits scalar deletion and the
implicit ScriptStack cleanup in this canonical object. No target byte arrays,
inert locals, artificial padding, fake containers or split exact-only bodies
are used. Existing ScriptStack construction now declares its actual nonthrowing
contract: default PMR construction plus pointer/frame zeroing performs no
allocation. The native enclosing constructor has no unwind state. Under EHsc,
the previous potentially throwing declaration creates a 175-byte constructor;
the recovered contract reproduces the whole 119-byte native body. The existing
42-byte stack constructor remains exact and receives no new coverage credit.
The maintained noexcept contract is an inference from the actual nonthrowing
operations and enclosing native emission; original declaration spelling is unknown.

The new object uses the pinned x86 candidate and the explicit per-object profile
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
This is a successful local profile, not proof of global game build flags.
All 94 objects are cold-built once for the frozen shared source graph, and all
505 units pass complete canonical relocation replay. A generated Enemy creation
string label changes from `$SG111153` to `$SG111240` after the header declarations
change. Its independently checked source/native literal and 00570420 anchor
remain identical; only the COFF label changes. Successfully built fresh objects
are reused when completing that staged cold batch.

Owned C++20/O2/UBSan checks run actual maintained initialization, stack reset,
base include behavior and virtual cleanup. Two recording memory resources prove
that changing the process default after construction leaves subsequent record
and word allocations bound to the original resource, with matching sizes and
alignments on release. Construction allocates no element storage. Borrowed file
buffers survive base destruction. Fixtures provide only unresolved first-slot
behavior and derived include handling. Existing ECL call/tick and Enemy creation
tests now link the actual base resource lifetime instead of duplicate fixtures.
Public CI, tracking, source and progress checks cover 41 tests. This does not
establish a linked or playable reconstructed game.

## Larger loading body remains nonexact

The whole append function at 0053FE60 is 876 bytes. It stores the borrowed file
pointer, validates SCPT and version one, and clears the slot on either failure.
Its 36-byte header and include size locate the offset/name tables. It adds the
subroutine count and inserts actual eight-byte name/code records using find_if:
the predicate takes each record by value and tests strcmp(name, record.name) < 0.
Equal names remain ahead of the newly inserted record. It advances the name and
offset pointers, increments file count, calls the second virtual slot when the
include block is present, ignores that callback's result, and returns the old
file index. This function adds no capacity or truncated-header checks.

Complete natural probes recover this algorithm and actual owner but remain
nonexact: the closest complete append contribution is 878 bytes. Native pointer
indexing lowers a constant byte offset as MOV 36; SHL 0, while the candidate
uses MOV 1; IMUL 36. Register allocation also changes two record-receiver ADD
encodings. The complete 54-byte instruction getter at 0053E8E0 has two structural
differences: native MOV 16; SHL 0 versus candidate MOV 1; SHL 4. Constant, index,
pointer, source-spelling and bounded profile probes retain these differences;
the original build/source-emission cause is unresolved. No prefix, partial
opcode or getter body is accepted to conceal them.

Native exports, complete failed probe sources and diagnostics remain private.
Reference constructor/destructor reviews cover additional factory/derived
owners and retain reviewed-nonexact status; append also remains nonexact. All
6,945 reference bodies remain terminal with 137 absorbed-exact associations.
The 41 KB Enemy root, derived loading, global production lifetimes and whole-game
link/runtime are still pending. Continue from complete bodies and actual owners.

## Storage maintenance

All 41 public tests and target/tracking/progress checks pass. Cleanup retires
36 superseded experiment objects/receipts / 1,598,909 bytes. All 188 current
canonical object/receipt hashes remain unchanged and 505 strict existing-object
comparisons pass afterward; no additional cold build is needed. Cumulative
retirement: 2,426 files / 998,278,720 bytes. build is 3.8 MiB and .analysis
is 77 MiB. Native exports, failed source/diagnostics and installed tools remain
intact. One-time core068-cleanup writer is stamped; never rerun it.

