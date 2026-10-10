# Whole ECL file loading and derived lifetime

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

EXACT-069 reconstructs the complete 556-byte file-loading member and three
derived lifetime contributions. Four whole functions add 682 instruction and
comparison bytes. The frozen graph has 509 units / 95 objects / 91,055 disjoint
comparison bytes. Origins remain separate: 436 pending / 9 library / 64 authored,
with 16,948 authored bytes unchanged.

| Canonical unit | Native entry | Complete bytes |
| --- | --- | ---: |
| ecl_file_loader_load | 004A74D0 | 556 |
| ecl_file_loader_ctor | 004A2E40 | 57 |
| ecl_file_loader_dtor | 004A3900 | 20 |
| ecl_file_loader_scalar_dtor | 004A4060 | 49 |

## Actual loading protocol

The loader obtains the actual EnemyController through Context and scans its
PMR filename vector. An exact, case-sensitive string match emits the native
diagnostic hint and returns -1 before any resource or append call. A new name
is registered before looking up or reading data. This ordering suppresses
recursive include cycles and persists even if a later append fails.

The process cache at 005C49F4 is a real PMR list of
`std::pair<uint8_t*, std::pmr::string>`. Its x86 entry is 32 bytes and the list
is 12 bytes. A matching name selects the first cached pointer and emits the
original cross-player hint. When the selected pointer is null or no match exists,
the loader constructs the resource path, calls the reader with null size output
and mode zero, and inserts the pointer/name pair. It then calls base append and
normalizes every negative result to -1 and every nonnegative result to zero.
There is no added null-buffer, capacity, path or truncated-header check here.

The two insertion endpoints return references: vector 004A2A20 forwards the
temporary PMR string and returns its inserted reference; list 004A29E0 returns
the inserted pair at node +8. These are emplace_back specializations. Their
results are discarded by the loading member. Parent instruction equality alone
does not identify these callee interfaces; complete native callee evidence is
required. The maintained body passes the actual temporary values to emplace_back.

An independent controller teardown at 004A3920 traverses this same process cache,
copies each pair, explicitly releases its resource pointer through the actual
diagnostic allocator, and clears the cache. It independently binds the cache
identity and borrowed-buffer relationship. This enclosing teardown and global
startup remain unclosed; a list destructor alone does not free raw file buffers.

## Actual derived owner and virtual interface

Native COL/type-descriptor data identifies original global `EclResourceInf`.
Its table at 005703E8 has load 004A74D0, include parser 004A5BE0 and scalar deleting
destructor 004A4060. EclFileLoader is the maintained semantic role name. Its
564-byte SptResourceInf/EclLoader base is followed by player index at +564 and
Context pointer at +568, making the complete x86 owner 572 bytes. Construction
calls the real base constructor, sets the derived vptr and zeros those fields.

The native ordinary destructor only calls base cleanup. An inline defaulted
destructor naturally emits its whole 20 bytes. An out-of-line defaulted or empty
user-provided body emits 29 bytes with an additional derived vptr store. The
maintained inline default follows the actual trivial derived fields and native
cleanup; original declaration spelling remains an inference. Generated scalar
deletion tests flag bit one and calls independently bound sized delete with 572.

The complete derived include caller independently establishes the first virtual
slot's const filename-pointer input. EclLoader now declares load(const char*)
and supplies the actual zero-return default. That complete 15-byte body folds
with the existing default include callback at 00414B50 and receives no duplicate
coverage credit. Earlier fixtures for the unknown first slot are removed.
The 516-byte derived include parser and 54-byte player binding remain unclosed;
no fake Session layout is introduced to implement the latter.

## Whole exception evidence and canonical ownership

EclFileLoader.cpp owns the four canonical contributions; EclFileLoader.hpp owns
the real derived declaration and process cache/interface declarations. The source
uses natural range loops, standard PMR string/pair temporaries and defaulted
lifetime behavior. There are no exact-only branches, byte arrays, fake return
contracts, inert locals, artificial padding, assembly or compiler-header changes.

The native loader has two ordinary synchronous unwind states, for the PMR string
temporary and cached pair temporary. Handler 005697D8 is 42 bytes and checks the
actual canary locations before dispatching to CxxFrameHandler3. FuncInfo 005AA9E0
has two states and flags one. Its two-entry unwind map at 005AA9D0 selects
005697C0 and 005697C8. The complete 66-byte cleanup/handler section, including
its compiler alignment bytes, and complete 52-byte xdata section replay exactly
with independent string/pair destructor anchors. These 118 supporting bytes get
no extra function, data or authored credit.

The successful explicit profile is the pinned x86 candidate with
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
All 95 objects are cold-built for the final frozen source graph and all 509 units
pass strict complete canonical relocation replay. An earlier partial cold job
was stopped when the insertion interface evidence required correction; its
superseded-source objects do not establish credit for the final source.

Some candidate STL child contributions still differ from their native bodies:
the candidate emplace_back wrappers are 33/43 bytes versus native 40/62, with
different forwarding emission. Their actual typed argument/reference-return
protocol is independently established, but their complete compiler emission and
whole-library linkage are not claimed. Complete parent replay does not close
every recursively called library or resource dependency.

## Owned validation and remaining work

Owned C++20/O2/UBSan tests link the real derived/base lifetime, loading member,
Context getter and diagnostic hint. Actual PMR containers exercise registration
before recursion, duplicate -1, cross-player cached pointer reuse, case-sensitive
names, negative append propagation, nonnegative result normalization, and retained
name/cache state after append failure. Recording resources verify exact allocation
size/alignment releases. Failure during the initial string allocation leaves
registration unchanged. Failure during cache-node insertion destroys the pair's
temporary string while retaining the already registered name. Borrowed buffers
survive loader destruction. Fixtures supply unresolved controller startup,
resource path/read, whole append and derived include bodies; they do not execute
native archive I/O or parse malformed SCPT data. All 42 public tests and tracking,
progress and source checks pass.

The reference load and derived/base destructor associations now close. All 6,945
reference bodies remain terminal, with 139 absorbed-exact associations. The
constructor association still includes the unclosed scalar factory and remains
reviewed-nonexact. Complete append 0053FE60/876 remains nonexact at 878 bytes;
instruction getter 0053E8E0/54 retains two structural differences. New signed/unsigned
64-bit index probes grow the getter to 62 bytes; long, byte and signed-byte forms
retain the 54-byte disagreement. No partial body is accepted.

Continue with complete derived include, actual process/resource ownership and
the larger Enemy dispatcher. Whole-game compilation/link/runtime remains open.
Failed probe sources, native exports and diagnostic records remain private.

## Storage maintenance

All 42 public tests and target/tracking/progress gates pass. Cleanup retires
14 superseded probe object/receipt files / 995,805 bytes. All 190 current
canonical object/receipt hashes are unchanged and 509 strict existing-object
comparisons pass afterward; no unchanged cold rebuild is needed. Cumulative
retirement: 2,440 files / 999,274,525 bytes. build is 4.0 MiB and .analysis
is 78 MiB. Native exports, failed source/diagnostics and installed tools remain
intact. The one-time core069-cleanup writer is stamped; never rerun it.

