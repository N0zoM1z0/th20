# Complete progress-file parser and checksum

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE/EXACT-091 strictly replays the complete 824-byte parser at 0050EB70 with
23 independent relocations. Typed one-past-header payload addressing and
ordinary Profile value assignment close the earlier CORE-087 emission gaps;
see [complete exact evidence](PROGRESS_FILE_EXACT_RECONSTRUCTION.md).
The record checksum at 0050FC90 strictly replays all 80 bytes without
relocations. Native score.cpp diagnostics establish
the parser's authored origin independently of its byte comparison. Checksum
authorship and original class/function spelling remain unknown.

## File and record protocol

The real 44-byte file prefix carries TH02 disk magic 32304854, version four, the
Spell/Profile/Metadata/Snapshot sizes, compressed and decoded lengths. Four
bytes at 1C and the word at 20 retain neutral names. Default creation clears
the entire prefix, then writes magic, version, word20=100 and the four sizes.
It leaves Snapshot file_size, decoded-buffer ownership and records alone.
The writer's independent consumers corroborate this header layout.

The parser validates magic, version, the four sizes and compressed length
against Snapshot file_size minus 44. It does not validate the header's own
file_size word. An absent buffer or rejected header follows the shared default
path. Rejection releases only the old file buffer, retaining decoded storage
and records. No minimum-file-size policy is added from the reference helper.

Valid input is decrypted in place through the actual ArchiveCrypt body with
key AC, step 35, block 16 and compressed-size limit. The real C allocator
allocates decoded_size shifted left two, and the actual ArchiveLzss decoder
fills that storage. As in native code, assignment replaces the decoded-buffer
pointer without releasing an existing allocation. The decoder retains its
shared dictionary and fetches a readable input byte before checking exhaustion.
These behaviors are documented rather than silently replaced by a vector or a
new validation service.

CR records require magic 5243, version one, the checksum of the complete 7AE8
Profile, and size 7AE8, in that evaluation order. The checksum sums unsigned
bytes from offset eight to the caller-supplied signed extent. Neither the first
eight bytes nor the header's size field determines that extent. Two-dimensional
indexing selects two rows of nine real Profiles; character two selects the
separate fallback and ignores the second selector. The native parser adds no
selector bounds checks. Ordinary Profile assignment emits a whole memcpy in
the pinned x86 compiler and preserves every Profile byte there.

ST records require magic 5453, version two, checksum over 1F8 and size 1F8.
Assignment copies the actual Metadata owner; native MSVC emits REP MOVSD for
all 126 words. A recognized but invalid record is skipped. Unknown magic logs
the native diagnostic and exits. Each iteration subtracts record size from the
signed remaining count after any copy, exits on a negative result, and advances
by the record's stored size. All paths return zero. Zero size can prevent
progress; short storage, invalid selectors and extreme lengths remain native
malformed-input domains, not newly accepted safe inputs.

## Shared owners and corrected heap family

The Snapshot Profile declaration changes from eighteen flat elements to a
2x9 matrix. Complete parser indexing and the independent writer's nested two
and nine loops corroborate this shape. The layout, fallback and Metadata
offsets do not change. The complete existing Snapshot constructor still
strictly replays its full 143-byte contribution with the original six anchors.
No second constructor or duplicate coverage is introduced.

This batch corrects an error in CORE/EXACT-086: its destructor and test fixture
used array delete for file/decoded buffers. Native 0041F610 allocates with malloc;
the actual 0041F670 release_bytes uses free. Production cleanup and the fixture
now use that C heap family. The shared null-safe release/reset operation does
not evaluate process_allocator for a null pointer. Caller conditions and that
shared contract account for the observed two layers of null checks. It is not
an invented return or an inert padding operation. ArchiveCrypt's distinct
new[] scratch allocation retains its existing array-delete protocol.

The old 086 heap-family acceptance claim is superseded. A GNU free wrapper now
observes actual ordered release after the final save; four real malloc buffers
replace the old new[] fixture. Null teardown and the null-pointer macro also
execute with a null process allocator. Current complete lifecycle candidates
remain nonexact: constructor 198/native199, commit 68/70, destructor 304/299.
No lifecycle unit is added and no artificial NOP or shortened extent is used.

## Historical CORE-087 emission evidence and executed scope

ProgressFileParse.cpp owns both parser and checksum under an explicit C++20
/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc /Gd profile without /sdl.
UTF-8 source and CP932 execution encoding reproduce all five complete native
diagnostic literals, independently checked at their established PE addresses.
The shared data-error literal has one maintained definition. This is a local
compiler observation, not a claim about every original translation unit.

Whole parser observations retain every exit and the native 824-byte boundary.
Flat addressing emits 806 bytes; the typed matrix with the meaningful pointer
offset emits 813. Address-of-element alternatives with sizeof, signed casts or
the documented 44-byte format offset emit 825 and disagree. Native payload
addressing emits MOV44/SHL0, while the natural maintained expression emits an
ADD44. Further argument-address evaluation also differs. These hypotheses are
recorded as nonexact; no expression-only padding local or ABI change is added.
An early do/while reset wrapper emits an absent loop under /Od and is rejected.

O2/UBSan checks execute complete SaveManager/Snapshot owners, actual checksum,
cipher, decoder, allocator and locks using independently generated encrypted
literal-token streams. Every one of the eighteen matrix slots, fallback with
an ignored second selector, complete CR/ST records, metadata members, buffer
identity, decoded bytes and real backup -> parse -> copy-back run together.
Tests cover all observed header rejection fields, preserved decoded storage,
CR/ST version/checksum/size rejection, unknown-magic interruption, application
before negative remaining length, checksum prefix exclusion and safe negative
checksum extents. Host Metadata checks compare all actual members; portable
assignment does not promise padding transfer, which remains x86 oracle evidence.

Only process startup and load/save disk boundaries are fixtures in the new
integration test. The earlier lifecycle-boundary test keeps its explicit parser
fixture to exercise signed merge results; it does not link ProgressFileParse.cpp.
No test replaces the new production checksum/cipher/decoder/parser. These tests
establish neither native malformed UB behavior nor disk serialization/loading,
compression/encryption writing, complete process startup or playable game.

Continue whole SaveManager load562/write1198/save174 with actual I/O and codec
dependencies. The load initializer's two-by-ten visits cross nine-element row
geometry and reach fallback; do not introduce out-of-array typed subscripts.
Whole Enemy/State, Controller and Player roots remain open. Use serial nice15,
repo-python, bounded attested Ghidra and protected periodic retirement.

Historical CORE-087 checkpoint: 57 public tests pass (131.530 seconds); 614/614 units
strictly replay over 120 fresh objects /119857 disjoint bytes. Protected
retirement saves 179919 net bytes, preserves 240 canonical hashes and repeats
614/614 strict replay with 120 existing objects and no rebuild.
