# Whole archive-owner and resource-reader candidates

## CORE/EXACT-094 production update

The nine complete archive/resource bodies are now shared production source
and canonical units. The full File dependency is also maintained. Frozen replay
passes 646 units/128 fresh objects; actual cipher/LZSS/allocator/File/resource and
SaveManager integration checks pass. The prior private-only state is historical.
See [whole production evidence](ARCHIVE_RESOURCE_EXACT_RECONSTRUCTION.md).

CORE-092 independently reconstructs the archive directory and member-reading
protocol. Nine complete private probe bodies strictly replay 2,869 bytes and
118 independently established relocations. They are not yet production source,
canonical units, authored exact credit or absorbed reference associations.
The accepted public checkpoint remains CORE/EXACT-091.

| Entry | Observed operation | Complete bytes |
| --- | --- | ---: |
| 539E60 | Allocate and copy an owned name | 97 |
| 539ED0 | Read, decrypt and decode the archive directory | 669 |
| 53A170 | Close and release owner resources | 151 |
| 53A210 | Parse directory records and final sentinel | 319 |
| 53A350 | Find the first matching record | 101 |
| 53A3C0 | Seek, read, decrypt and optionally decode a member | 596 |
| 53A620 | Find and return decoded size or zero | 48 |
| 53A6F0 | Close, allocate a file reader and open an archive | 305 |
| 410AA0 | Read an archive member or a loose file | 583 |

## Storage and native interfaces

Independent startup at 401030 clears sixteen bytes at 5B66C8 and initializes
four fields. The owner contains the record-array pointer at zero, signed count
at four, owned name pointer at eight and polymorphic file pointer at twelve.
The constructor contribution is folded with another four-field initializer;
no duplicate coverage is claimed. Names and the original nonvirtual owner
declaration remain inferred.

The stream allocation has twelve bytes. Native RTTI identifies `Pbg::File`
and its `Pbg::IFile` base, correcting misleading automatic Ghidra library names.
The eight vtable slots are open, close, read, write, position, size, seek and
virtual destruction. File storage contains its vptr, Win32 HANDLE and access
word. Complete native constructor, destructor and method listings corroborate
that layout; it is not a FILE pointer or replacement vector-backed reader.

The directory allocates count plus one sixteen-byte records through the actual
array allocator. Each record owns a C-heap name and three signed words: file
offset, decoded size and an unresolved word at twelve. Stored member length is
the next record's offset minus the current record's offset. The final sentinel
supplies the directory start offset and decoded size zero. No extra stored-size
field or replacement ownership API is introduced.

Name duplication uses `strcpy_s` with strlen plus one. Find uses `_stricmp`,
including its native CRT locale path, and returns the first matching record
pointer. The initial strcmp probe was rejected during independent relocation
closure; matching non-relocation instruction bytes did not establish its API.

## Directory and member protocol

The sixteen-byte disk header is decrypted with 1B/37 and block/limit sixteen.
Magic is THA1. Decoded directory size, stored size and count subtract
123456789, 987654321 and 135792468, respectively. File size minus stored directory
size supplies the seek position and final sentinel offset. Directory bytes use
3E/9B and block 128 before the existing real LZSS decoder.

Names advance to the next four-byte boundary. The separate word helper at
53A650 advances by four and **dereferences the new position** for its return
value. An earlier private CORE-090 note incorrectly described a pointer return;
that interpretation is superseded. Directory callers ignore the helper's result,
but its read still requires readable storage at the new position. Short storage,
overflow, malformed records and missing allocation guards remain native domains.

Member decryption selects one of eight twelve-byte parameter records using the
wrapped unsigned name sum modulo eight. Key and step use bytes zero/one; block
and limit use words four/eight. The complete native 96-byte table independently
identifies its anchor. Unconsumed bytes two/three and original global initialization
remain unresolved; there is no complete production data-definition claim.

Stored and decoded lengths determine whether temporary storage and decompression
are required. The original ownership behavior is preserved: uncompressed reads
with a null destination free temporary storage before returning its pointer.
Failure can free a supplied destination. These are recorded observations, not
repaired interfaces. Reopening after directory initialization also ignores its
boolean result. Close releases owned names, the array and the file reader, then
clears count; it retains the process-shared codec dictionary.

## Resource-reader control flow

Mode zero searches the archive without a loose-file fallback. Backslash trimming
precedes slash trimming; each missing separator restores the original filename
pointer. This preserves the native mixed-separator behavior. The archive size is
reported before rejecting zero length. Allocation uses the original filename
as its diagnostic label; the member-read return value is ignored.

Loose mode uses a local HANDLE, separate from the process output handle. A
short-lived filesystem path precedes CreateFileW and is destroyed immediately
afterward. File size is replaced by the reported ReadFile byte count, even though
the boolean result is ignored. Allocation and open failures use the common null
return route, while both successful paths share the same buffer-return route.
This closes the earlier 683/586-byte probes with natural ownership and control
flow; the complete native entry is 583 bytes.

## Evidence and remaining gates

Native exports explicitly retain known Ghidra indexing gaps as gaps. Complete
locked-PE instruction ranges, full contribution sizes and returns supply the
boundary evidence; no shortened prefix is accepted. Whole NUL-terminated literals,
the actual import-name lookup tables, independent owner/file consumers and
complete native helper protocols establish relocation identities.

The resource EH code section has a unique complete 52-byte identity. The entire
44-byte unwind/funcinfo section is then independently identified using its actual
COFF ownership and cleanup identities. Both sections and the complete 37/103-byte
cursor helpers strictly replay as support only. No compared root field supplies
an anchor, and there is no additional exact coverage for these contributions.

Array helper/destructor emission and the scalar file factory's pre-clear remain
open. A private probe can call their independently identified native ABI without
claiming their entire emitted bodies exact. Formal admission still requires
shared production owners and bodies, real codec/allocator/file protocol checks,
fresh canonical builds, frozen graph replay and consistent tracking updates.
Startup, full CRT failure domains, native disk execution and a playable linked
reconstruction remain separate unfinished work.

Private evidence is `core092-whole-shapes-v4.json`, `core092-bindings.json`,
the bounded `core092-*-native.asm` exports and original versioned probe sources.
Completed binding and retirement writers must never rerun. Historical receipts
require the complete original SHA-bound inputs; sources and rejected diagnostics
remain protected when obsolete object files are retired.

The interim retirement removes six superseded products (492,029 bytes),
with original receipts archived losslessly and all original inputs unchanged.
All 252 canonical/active product hashes remain protected. All 625 current
canonical units and nine active private probe roots strictly replay afterward
using existing objects. Net savings after archives and verification are
354,296 bytes. Only V4 remains active; formal admission is still pending.

## CORE-093 File dependency update

The real File/IFile private bodies now close twelve whole entries, including
construction, destruction, seven file operations and conversion. Strict replay
covers 1,153 bytes /35 independent relocations with the complete destructor
alignment. Actual O0/O2/UBSan checks execute these bodies with narrow OS/CRT
fixtures. See [native File protocol](PBG_FILE_RECONSTRUCTION.md).
The factory pre-clear, array helpers and shared production/canonical admission
remain pending. No archive/resource credit follows from dependency closure.

A further protected retirement removes 6 old probe/host products /449,414 bytes;
254 current canonical/active hashes remain unchanged. Existing 625 canonical
units and 21 active whole roots replay afterward; net savings 348,238 bytes.
Preserve archive V4 and File V3 sources, objects, receipts and native evidence.
