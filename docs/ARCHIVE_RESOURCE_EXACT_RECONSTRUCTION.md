# Whole archive and resource production protocol

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE-094 maintains shared production File/IFile, archive-owner and resource-reader
bodies. Twenty-one complete fresh production candidates strictly replay 4,022
comparison bytes and 153 independently established relocations. Frozen canonical
replay passes all 646 units across 128 fresh objects and
128,271 disjoint comparison bytes. Nine newly exact authored operations add
2,869 bytes; twelve Pbg File origins remain unknown. Independent native
application diagnostics, THA1-specific records/ciphers and process consumers
establish the nine archive/resource operations as application-authored.

## Shared source and interfaces

[PbgFile.hpp](../src/PbgFile.hpp) owns the RTTI-proven classes and eight-slot
interface; [PbgFile.cpp](../src/PbgFile.cpp) maintains the actual Win32 protocols
and named conversion helper. The selected File and Runtime scalar allocations
share [DiagnosticObjectFactories.hpp](../src/DiagnosticObjectFactories.hpp).
There is one ordinary template body. The File factory currently emits 129 bytes
versus the native complete 67-byte body; its exception/initialization emission
remains open. No fabricated clear, constructor or ABI declaration is introduced.

[ArchiveOwner.hpp](../src/ArchiveOwner.hpp) owns the sixteen-byte owner and
sixteen-byte entries, four-byte cursor, sixteen-byte header and consumed cipher
parameter fields. [ArchiveOwner.cpp](../src/ArchiveOwner.cpp) maintains whole
name duplication, directory load, close, parse, find, member read, size and open.
[GameResourceIo.cpp](../src/GameResourceIo.cpp) owns the original complete reader;
its one declaration is shared with EclFileLoader. Process archive startup,
read/seek globals and parameter-table initialization remain external dependencies.
Unused parameter bytes and complete production data-definition exactness are
unresolved. Portable fixture initializers supply only consumed fields.

## Native protocol and ownership

Whole native intervals and independent producer/consumer evidence retain the
known Ghidra indexing gaps. The nine complete root extents are 97, 669, 151, 319,
101, 596, 48, 305 and 583 bytes. The twelve File roots add 1,148 function bytes;
all five destructor alignment bytes are also compared. Complete NUL-terminated
constants are identified at their actual COFF symbol values within pooled data
sections. The empty Unicode literal uses its earlier complete constant-pool
identity. Root relocations are never solved to produce canonical anchors.

Catalog names use C-heap duplication and secure copying; lookup uses the actual
case-insensitive CRT. The count-plus-one entry array retains the final sentinel
and derives stored size from adjacent offsets. Word advance reads its new
position even when its return is discarded. Valid decoded storage must include
the final readable word; malformed/short/overflow input remains a native domain.

File calls preserve mode scanning, stale access after failed open, ignored OS
booleans and seek failures, module/colon/empty prefixes and actual close/destruction.
Archive open ignores the final reopen boolean. Member reads retain the native
failure ownership, including freeing a supplied destination. Uncompressed reads
with null destination return already released temporary storage. The resource
reader retains its mixed-separator quirk, zero-mode no-fallback, early size report,
ignored member return and loose-mode reported-count overwrite. These behaviors
are observed and preserved; no replacement vector/optional manager is imported.

## Actual semantic checks

The public File check executes production File/IFile bodies at O0/O2 with UBSan.
The archive/resource check executes actual File, owner, C allocator, cipher,
LZSS decoder, recursive-lock and resource-reader bodies at O2 with UBSan.
An independent literal-token encoder supplies a synthetic THA1 directory;
plaintext expectations verify all eight cipher selectors, case-insensitive first
match, compressed/uncompressed members, caller and optional destination storage,
sentinel extents and retained dictionary. Existing codec tests separately check
cipher/decoder behavior against independent models.

The existing SaveManager file/checksum/record/backup test now also calls the
actual resource reader, File and archive-owner implementations. Its replacement
resource-reader body is removed. Only heap/OS/startup/data and valid-input CRT
boundaries are fixtures; the heap fixture provides an explicit readable guard
for the native decoder while retaining each logical allocation request size.

Additional pipeline checks cover both resource modes, mixed separators, zero
members, missing names/files, ignored reopen/ReadFile results, stored/decoded/name/
filename allocation failure, failed reads/closed handles, caller-buffer release,
ignored resource member results and repeated close. Only startup/data globals,
Win32 and valid-input CRT boundaries are fixtures. ASCII/host wchar4 checks do
not establish complete native CP932, CRT invalid-parameter or disk/game behavior.

## Canonical registration and remaining work

The whole production recipes have independent strict proof in private
core094-production-bindings.json, based on completed core092/core093 native,
RTTI, import, constant and EH audits. Both cursor helpers, both scalar deleting
destructors, both mutable wchar wrappers and complete resource/File EH code/data
sections strictly replay as support only. No additional units cover this support.

Formal registration admits all twenty-one complete canonical units. Authored
exact coverage is 84 functions / 24,209 bytes, with 87 confirmed authored functions
and a provisional 25,941-byte denominator (93.32%). Source mappings total 654;
the previous eight whole nonexact methods remain explicit. Canonical origins are
553 pending, nine library and 84 authored. Fourteen reference associations close
only after every associated target has a canonical unit, bringing absorbed
associations to 234. The combined directory/cursor row and mixed resource/player
row remain nonexact; free replacement wrappers remain support only. All 6,945
reference reviews remain terminal. All 61 public tests pass in 147.984 seconds.
Protected retirement removes four
obsolete probes/products (233,647 bytes), retaining original SHA-bound source
and receipts losslessly. All 256 canonical hashes and 5,032 evidence files remain
protected. Post-cleanup 646/646 strict replay reuses the existing 128 objects.
Net savings after source/receipt/replay archives are 46,336 bytes. Build is 6.7M
and analysis 86M; locked tools, original target and native/reference evidence
remain protected.

Native scalar factory and array helper emission, original access
visibility and nonvirtual spellings, unused cipher bytes, process initialization,
full CRT/failure domains and linked/native runtime remain unfinished work.
Original probe sources and SHA-bound pre-change source/receipts are retained
losslessly; completed evidence writers must never rerun.
