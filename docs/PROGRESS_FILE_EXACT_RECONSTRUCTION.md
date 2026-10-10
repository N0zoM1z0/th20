# Complete progress-file serialization and parsing

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE/EXACT-091 closes two existing authored roots with fresh canonical builds:

| Entry | Owner | Complete bytes | Independent relocations |
| --- | --- | --- | --- |
| 0050F6B0 | ProgressSaveManager::write | 1,198 | 49 |
| 0050EB70 | ProgressSaveManager::parse | 824 | 23 |

Both complete bodies strictly replay through their final returns. The frozen
graph passes all 625 units across 125 fresh objects and 124,249 disjoint
comparison bytes, including previously accepted compiler contributions.
No partial functions or extra library/support coverage are credited.

## Header and record ownership

The staging allocation remains `char`, as the native score.cpp diagnostic
states. Its first 44 bytes contain the independently established file header.
The codec receives the address immediately after that typed header, expressed
as `&staged_header[1]`. Parsing uses the same view of the existing file-buffer
prefix. This produces the observed MOV44/SHL0 addressing without inventing
an array owner, padding, local variable or alternate source body.

Profile records use ordinary value assignment into the existing two-by-nine
matrix or fallback. The pinned x86 compiler emits the complete native bulk
copy, with destination evaluation preceding source evaluation. Metadata
assignment continues to emit REP MOVSD. Earlier explicit memcpy and byte-index
hypotheses remain preserved as rejected experiments.

The file-format checks, malformed-input behavior, buffer guards, record ordering,
checksum evaluation, actual C allocator and string/path/buffer cleanup ordering
are retained. The parser replaces decoded storage as observed; the writer
ignores write results. See the [file protocol](PROGRESS_FILE_IO_RECONSTRUCTION.md)
and [parser protocol](PROGRESS_FILE_PARSE_RECONSTRUCTION.md).

## Independent relocation identities

Seven complete NUL-terminated diagnostic literals have unique identities in
the locked PE. Their addresses are found from the whole constants, independently
of the compared instruction fields. Native CP932 text is retained.

Whole SDK function bodies, installed SDK declarations and independent Game
consumers establish the filesystem and narrow-string call identities. Eight
complete cursor/range and four SDK functions strictly replay as support.
Range-tag kind and original spelling remain inferred; folded begin functions
receive no duplicate coverage.

The complete 63-byte writer EH code section has one independent native match.
Its three function contributions retain natural padding. With those cleanup
identities established, the complete 52-byte unwind/funcinfo section also has
one match; its self pointer follows actual COFF section ownership. Both sections
strictly replay, including all relocations, as support only.

The SDK path-append EH section has two independently matching native candidates.
That linkage choice remains unresolved. No compared handler field is used to
select a candidate, and the SDK append function receives no standalone strict
exact claim. The authored writer's call entry is independently established by
other complete callers and SDK ABI evidence.

## Executed checks and remaining scope

The actual encrypted-packet integration test now checks the complete Profile
representation, including distinctive alignment bytes, and its record checksum
after serialization and parsing. It also omits an invalid CR Profile and checks
the other slots, fallback and Metadata. The maintained production bodies run
under O2/UBSan; no replacement parser or serializer supplies the result.

This establishes the observed representation transfer for the tested host and
pinned x86 compiler. Portable C++ assignment does not universally promise
padding transfer. Invalid selectors/lengths, allocation failures, secure-CRT
failure domains, original startup, native disk/game execution and linking a
playable reconstruction remain open. Whole load, Metadata byte sum, archive
compression and other pending owners retain their existing nonexact status.

Private proofs are `core091-bindings.json`, `core091-cold-audit.json`,
`core091-final-frozen-source.json` and `exact091-canonical-results.json.gz`.
The first records independent identities; the second verifies them against
fresh canonical objects. Historical probes require their original SHA-bound
input set. Completed registration and replay writers must never rerun.

The final public suite passes all 59 tests in 140.855 seconds. Protected
retirement removes six obsolete probe products (257,559 bytes),
preserving original receipts and two historical input versions. Net savings
after archives and verification are 135,890 bytes; all 250 canonical hashes
remain unchanged and all 625 units pass existing-object post-cleanup replay.
No unchanged cold build is repeated for cleanup or documentation.
