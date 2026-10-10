# ECL buffer registration and instruction resolution

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE/EXACT-083 adds complete production bodies for EclLoader::append and
EclLoader::instruction, and an exact EclFileLoader::bind_player contribution.
The two buffer methods have semantic and compiler evidence but remain nonexact.
They have source mappings without canonical comparison units or exact credit.
This distinction is intentional: functional progress must not inflate exactness.

## Native protocol and maintained source

| Native function | Complete native extent | Maintained source | Result |
| --- | ---: | --- | --- |
| EclLoader::append at 0053FE60 | 876 bytes | src/EclLoaderBuffer.cpp | Whole candidate 878 bytes; nonexact |
| EclLoader::instruction at 0053E8E0 | 54 bytes | src/EclLoaderBuffer.cpp | Whole candidate 54 bytes; two structural differences |
| EclFileLoader::bind_player at 004AB8B0 | 54 bytes | src/EclFileLoaderBinding.cpp | Complete strict relocation replay exact |

Append borrows the writable file buffer. It publishes the current file slot,
checks SCPT and version one, and clears that slot on either rejection. The
36-byte header and unsigned 16-bit include size locate the offset table; the
unsigned 16-bit subroutine count locates the consecutive NUL-terminated names.
Only consumed prefix fields are interpreted; the rest of the header remains
opaque. Names and subroutine headers point into the borrowed original buffer.

The loader adds the declared count before inserting records. Each record is
inserted before the first lexicographically greater name, so earlier equal
names retain priority. The native predicate receives the record by value.
After all insertions, file_count advances before the second virtual slot runs.
Include recursion can register more files; its return value is discarded and
append returns the parent's original index. An insertion exception leaves the
already published slot/count and any earlier insertions intact. The native
function supplies no rollback, capacity, null-buffer or truncated-input checks.

Instruction resolution uses the actual PMR record table, then adds 16 bytes
past the subroutine header and the signed byte offset. The original buffer is
writable: VM mutations reach that buffer directly. The valid domain requires
an existing record and an in-buffer instruction position. Added bounds checks
would change the native protocol. Bind_player stores the index and obtains
Session::context from the actual process Session at 005BA568 through 0040BBC0.
It adds no validation; the observed Session has two contexts.

## Compiler and source evidence

The locked MSVC x86 profile is C++20, Od, Ob0, GS, Gy, Zl, SSE2, fp:precise,
sdl and EHsc. Natural pointer indexing still disagrees with the target: native
constant indexing uses MOV 36 / SHL 0 or MOV 16 / SHL 0. The candidates use
MOV 1 / IMUL 36 or MOV 1 / SHL 4; append also differs in receiver register
allocation. Existing 068/069 attempts are retained rather than repeated.
A fresh typed-header arithmetic observation produces complete extents of
863/48 instead of 876/54. It is rejected, and its opaque fixture declarations
are not imported into production. No padding, assembly, inert locals, fake ABI
or shortened contribution hides the disagreement.

Native provenance comes from the attested 067 loader listing, the 068 resource
and STL evidence, the 069 derived loader listing and the accepted 073 Session
owner. Private 083 compiler receipts and complete observations preserve the
actual production candidates. Binding anchors come from those independent
Session/native data and call observations, never a solved comparison field.
Original authored identity remains pending for all three functions.

## Executed checks and remaining boundaries

O2/UBSan checks execute actual append, buffer resolution, sorted name lookup,
VM tick, call_into, Manager spawn/find/invalidation/tick, State script advance,
Stack and the existing PMR lifetimes. The prior instruction-resolution fixture
is removed from that pipeline. Synthetic aligned SCPT files contain five real
subroutine headers and mutable instruction records; no game data is embedded.
Existing signed-ID, descriptor-conversion, deferred-spawn, signal and retirement
checks now use these production buffer methods.

A separate buffer protocol test checks unsorted names, duplicate stability
across files, buffer aliasing and writeback, both header rejection routes,
recursive include publication and discarded return, allocation failure state,
and all 64 valid empty-file slots. The file-loading/cache test additionally
executes actual binding to both real Session contexts. Its append hook remains
an explicit fixture for that separate loading-isolation test. The derived
include parser, graphics/resource I/O, link allocation factory, allocator
startup, unused interpolation/frame routes and Enemy outer movement/opcode/
retirement remain open boundaries. A playable reconstruction is not claimed.

## Additional core observations

An attested read-only listing covers the complete 734-byte Controller frame
at 004A5040, including its Timer/HUD, real intrusive iterator, Enemy tick and
pointer-lvalue release protocol. Its iteration requires the unresolved 40C080
preclear call; Renderer, HUD and Player dependencies remain unclosed. No source
or exact credit follows from that listing alone.

Twenty emitted compiler fixture functions produce identical whole function
bytes/relocations under C++14, C++17 and C++20. With the locked compiler and
the tested sdl/EHsc profile, the routes leaving pointer members uninitialized
emit neither the target's preclear call nor inline pointer zeroing. The overload
with explicit pointer initialization retains its ordinary member assignment.
This narrows the existing initialization hypothesis; it does not establish the
original compiler/source cause. The documented feature remains described in Microsoft's
[/sdl reference](https://learn.microsoft.com/en-us/cpp/build/reference/sdl-enable-additional-security-checks?view=msvc-170).

A bounded linear scan of the locked executable finds no direct memory operand
using displacement 0x14850. This is incomplete negative evidence: tables,
indexed/relative accesses and omitted instruction heads can escape that scan.
The Player constructor's untouched four-byte interval at +0x14850 remains
unknown; no fictitious padding or complete Player owner is accepted.

## Verification and storage

The final graph has 605 canonical units across 116 comparison objects, covering
104870 disjoint comparison bytes, and 607 source-present mappings. Two of those
mappings are explicitly nonexact and lack canonical units. Origins remain
pending except the existing 9 library and 64 authored contributions; authored
exact coverage stays 16948 bytes. One complete reference binding association
closes, bringing absorbed-exact reviews to 206 across all 6945 terminal reviews.

Run the frozen graph, public CI and tracking gates before protected retirement.
Current canonical objects and receipts, native evidence, failed probe source,
toolchain, game and reference inputs are retained. Completed 083 probe products
are regenerable; their original receipts and changed input versions are saved
losslessly before retirement. Post-cleanup verification reuses the current
canonical objects without another cold build. Reconstruction remains active.

Final verification: all 53 public tests pass in 141.326 seconds; target,
tracking, reference, build and progress gates pass. Frozen and post-cleanup
replays each pass all 605 units. Four compiler-local literal labels were
reconciled by full original text at the unchanged independently bound addresses.
Protected retirement removes 12 products /331306 bytes and
preserves 232 canonical hashes and 4470 evidence files. Lossless original
receipts and three historical input versions cost 62553 bytes; the additional
replay archive costs 56064 bytes. Net retirement savings are 212689 bytes.
The one-time retirement writer is complete and must never rerun.
