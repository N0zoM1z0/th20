# Whole progress-file loading, saving and native file I/O

CORE/EXACT-165 later resolves the entire Metadata byte-sum root at 0x463F20.
Its signed address comparison, byte return and 134-byte canonical replay are
recorded in [focused exact evidence](PROGRESS_INTEGRITY_BYTE_EXACT.md).
The historical 125/134 nonexact table below describes the earlier CORE089
checkpoint, not the current result.

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE/EXACT-089 reconstructs the complete save/load protocol on the existing
SaveManager, Snapshot, Profile, Metadata, Worker, allocator and codec owners.
CORE/EXACT-091 adds complete serialization and parsing to the eight CORE-089
exact contributions. Whole load and Metadata byte sum remain nonexact.
See [complete exact evidence](PROGRESS_FILE_EXACT_RECONSTRUCTION.md) and
[earlier serialization experiments](PROGRESS_WRITE_PROTOCOL_RECONSTRUCTION.md).
This is component reconstruction; original process startup, filesystem runtime
and a linked playable game remain open.

## Whole contributions and source ownership

| Native entry | Maintained source | Candidate / native bytes | Result |
| --- | --- | --- | --- |
| 410840 output open | GameFileIo.cpp | 323 / 323 | Exact |
| 411060 output write | GameFileIo.cpp | 255 / 255 | Exact |
| 4106E0 output close | GameFileIo.cpp | 179 / 179 | Exact |
| 454230 error report | DiagnosticLog.cpp | 221 / 221 | Exact |
| 50EF00 Profile defaults | ProgressInitialize.cpp | 400 / 400 | Exact |
| 50F090 Metadata defaults | ProgressInitialize.cpp | 211 / 211 | Exact |
| 4BEB60 Metadata integrity update | ProgressIntegrity.cpp | 161 / 161 | Exact |
| 50FB60 save thread entry | ProgressFileWrite.cpp | 174 / 174 | Exact |
| 50F3B0 load thread entry | ProgressFileLoad.cpp | 574 / 562 | Whole nonexact |
| 50F6B0 file serialization | ProgressFileWrite.cpp | 1198 / 1198 | Exact |
| 50EB70 file parsing | ProgressFileParse.cpp | 824 / 824 | Exact |
| 463F20 Metadata byte sum | ProgressIntegrity.cpp | 125 / 134 | Whole nonexact |

The eight CORE-089 roots contribute 1,924 disjoint bytes and 95 independently
established relocations. CORE-091 adds 2,022 bytes and 72 independent relocations.
Twenty-three complete CORE-089 library/EH contributions also
replay as support, without additional coverage. Custom score-record transforms,
score.cpp diagnostics, shared game locks, the process file handle and custom
log error state corroborate authored origins separately from byte identity.
SDK string, array, filesystem and formatting helpers receive no authored credit.
Original function/type spellings remain inferred.

## Actual protocol

Load uses slot 20, the real user-data directory, backup filename first and
current filename second. Each read delegates to the genuine pending
read_game_resource entry at 410AA0, including mode 1 and the signed size output.
It initializes Metadata and performs two rows of ten physical Profile visits
per Snapshot. Actual row storage has nine Profiles: the tenth visit crosses into
the next physical value, revisits row 1's first Profile and finishes at fallback.
Source computes these addresses from the complete Snapshot byte view, preserving
that behavior without an invalid profiles[character][9] array subscript.
Backup parsing precedes current loading; the existing real merge operation
copies backup records to current, parses current and copies the result back.

Serialization returns -1 immediately for a missing file buffer. It allocates a
2 MiB staging buffer through the actual C-heap allocator and copies the complete
44-byte file header. Each CR Profile among the eighteen selected slots receives
its selector and actual record checksum before its complete bytes are appended.
Fallback always receives character 2 while retaining its index. Complete
fallback and Metadata records are always appended with their record checksums.
The real compressor processes the staged payload, updates the original header's
compressed and decoded lengths, and the real cipher uses AC/35 with block 16.

The resulting user-data path is opened through actual file I/O. Failure reports
the native CP932 error and frees compressed then staging storage. Success writes
header then payload, closes the output and performs the same ordered release.
The serializer ignores both write return values, as the native body does.
Save holds slot 20, writes backup before current, copies current records to
backup and calls the original empty diagnostic hook. Its unused one-word thread
argument and thiscall/RET4 ABI are preserved.

The native C-heap family is malloc/free at 41F610/41F670. Codec scratch retains
its separate new[]/delete[] family. No allocation-failure handling, exception
recovery or stronger I/O policy is inferred from the successful-domain protocol.

## File and log boundaries

All three file methods use the actual slot-2 recursive lock and process handle
at 5AE060. Open builds a real std::filesystem::path and calls CreateFileW with
GENERIC_WRITE, FILE_SHARE_READ, CREATE_ALWAYS and FILE_ATTRIBUTE_NORMAL. Invalid
handle failure obtains GetLastError, calls FormatMessageW with 1300/400, invokes
the diagnostic hook, calls LocalFree and returns -1.

Write returns -1 for an invalid handle. It ignores WriteFile's boolean result
and compares its reported byte count; a short count closes the handle and
returns -2. Close returns zero after the invalid-handle check or CloseHandle.
Neither operation clears the process handle. Consequently a short header write
still permits the serializer's payload write attempt and final close on the
same closed handle, and the serializer returns zero. Tests preserve this native
behavior rather than supplying a new failure policy.

The error reporter is a separate variadic cdecl entry. It owns a zeroed
1024-byte narrow stack buffer, formats through the real fixed-array secure-CRT
overload, appends through std::pmr::string::operator+=(const char*), sets the
owner's error byte at 1C and returns the original format pointer. Independent
append/clear consumers establish the 28-byte x86 PMR string and 32-byte owner.
Ghidra's wide-formatting/assign labels are not accepted: the complete downstream
formatter copies bytes and terminates a narrow string. No invented append
member or merged bool/va_list helper is introduced. Log construction, flushing
and global lifetime remain pending.

Windows compiles the real SDK/CRT declarations. Portable fixtures provide only
those external boundaries; filesystem conversion to a wide name occurs at the
portable OS fixture call. Tests cover ASCII paths and valid secure-CRT inputs,
not native non-ASCII path conversion, CRT error handlers or Windows filesystem
execution. There is one shared production protocol body.

## Defaults, random state and integrity

Profile defaults set CR/version 1/size 7AE8, initialize seven groups of ten
scores using the original signed int expression, and write stage 1, eight
dashes, zero timestamp, continues and slowdown. The first 113 of the actual
123 Spell values receive their index and the external default word. All other
fields and the remaining ten Spell values retain their prior state.

The complete independently reviewed 113-word table matches 452 PE bytes at
5AF058 uniquely, and independent spell consumers corroborate that identity.
Production declares the table externally with no invented total extent or
copied data definition. Synthetic tests supply distinct default words.

Metadata sets ST/version 2/size 1F8 and an eight-space name. Sixty-four separate
calls to the actual progress random stream supply the two salt arrays. The
nine-element stones accessor is the genuine checked std::array::at operation,
not unchecked operator[]: its entire 34-byte helper and native failure chain
are independently reviewed. The separate 18-byte CRT initializer at 401100 and
other consumers establish progress_random at 5BA4C4; global startup remains an
external dependency. Integrity then sums bytes [58,1D0), increments a first salt
selected by another random draw, increments checksum, adds two to the tag, and
increments a second independently selected salt, preserving byte wraparound.

An initial unchecked-access candidate matched the caller structurally but used
the wrong 22-byte helper. It was rejected and replaced with the correct .at
operation before canonical acceptance. The SDK out-of-range helper itself emits
16 bytes versus the native noreturn 13-byte tail; checked-at identity is
established, but the full exception helper is not claimed exact.

## Independent evidence and unresolved emission

All twelve native roots are reviewed through their final return, including
every branch and complete extent. Bounded attested Ghidra listings agree with
the locked PE instructions. Separate owner consumers and the full PE import
descriptor/lookup tables supply global and IAT identities. Named diagnostics
match their entire NUL-terminated native constants, including CP932 encoding.
No compared relocation field is solved to populate the manifest.

Five full EH graphs independently identify handler, state table and cleanup
addresses. Natural cleanup padding is retained. Complete handler, unwind and
cleanup contributions replay, including the shared save/Worker cleanup graph.
They provide support only and are not separate exact progress.

CORE-090 replaces finite std::views::iota with the independently corroborated
one-word range/cursor protocol. Original tag kinds/type spellings remain inferred;
complete helpers replay as support without additional exact credit. CORE-091
closes writer and parser emission with the existing typed header prefix and
ordinary Profile value assignment. Load retains the full
562-byte native scope; its stack/source emission differs. The byte checksum
retains all 134 native bytes, including an unresolved multiply-by-zero/index
expression and signed comparison; source uses a safe complete-owner byte view.
No inert local, artificial zero index, emission-only signed-pointer cast,
fake result, assembly or shortened unit is introduced.

Raw proofs stay in ignored .analysis/: core089-whole-audit.json,
core089-cold-support.json, core089-final-frozen-source.json,
exact089-canonical-results.json.gz and the bounded native exports. Historical
rejected probe inputs are preserved by SHA-256 before product retirement.

## Semantic checks

The new O2/UBSan test links the real Worker, SaveManager lifetime/load/write/save,
initializers, random stream, parser, checksum, codec, allocation, log and file
method bodies. Startup storage, pending read_game_resource, Windows APIs and
valid-input secure CRT are explicit boundary fixtures. Independent assertions
cover all eighteen Profile selectors, fallback and Metadata; complete encrypted
packets; actual backup-before-current ordering; default preservation; 64+2 RNG
draws; integrity wraparound; real reload and current-missing fallback; null input;
open failure/logging; ordered C allocations/releases; short writes; stale handle
behavior; thread join and destructor save/release. No production dependency is
replaced by a fixture method with an accepted native mapping.

Run the focused public check with:

```bash
nice -n 15 scripts/repo-python -m unittest discover -s tests -p test_progress_file_io_semantics.py -v
```

Private replay uses the normal locked compiler and manifest. Serial whole-graph
replay is required after shared declarations change; cleanup-only verification
reuses canonical objects and receipts. Whole native resource loading, startup,
invalid allocation/CRT domains, actual disk execution and game runtime remain
open.

## CORE-089 frozen verification and protected storage retirement

The final source strictly replays 623/623 units across 125 fresh objects and
122227 disjoint comparison bytes. All 59 public tests pass in 157.214 seconds.
Source presence totals 633 mappings; 10 entire methods remain nonexact. The 73
authored exact functions contribute 19318 bytes; pending/library units are
separate. Five complete reference associations close, 218 absorbed total.

Protected retirement removes 26 completed probe products
(1314539 bytes) after preserving original receipts and
8 historical input versions losslessly.
All 250 canonical object/receipt hashes and retained evidence remain unchanged.
Post-cleanup 623/623 strict replay reuses 125 objects. Net storage savings after
archives and verification: 996949 bytes. No unchanged cold build is repeated.
Private proof paths above are historical evidence, not public build inputs.

## CORE/RECON-1083 — separate CP932 one-shot Win32 file Bosses exact

The file-I/O protocol also includes two previously unclassified
[whole-original strict-exact game functions](GAME_FILE_CP932_BOSSES_368_493_STRICT_EXACT.md):
`0x00410CF0` native 368B persistent input-file opener and
`0x00410E70` native 493B one-shot output-file writer. These functions
use the real slot2 lock and CP932 Win32 name conversion, but are
**distinct native executable code** from the already exact persistent
output open/write/close methods listed above. The 493B writer opens
a local handle, closes it on successful and short-write paths, and
has the genuine native short-write failure branch before success.
Both compile 368/368 and 493/493 strictly exact, adding 861 distinct
game-authored `.text` bytes with no earlier game/file output code
credited twice.

## CORE/RECON-1084 — 266B persistent input reader whole exact

The same native persistent HANDLE `0x005AE060` opened by the original
368B CP932 input opener is consumed by a distinct
[WHOLE EXACT 266B game input `ReadFile` Boss](GAME_FILE_INPUT_READ266_STRICT_EXACT.md).
It locks slot2, allocates via the separately exact 88B
`DiagnosticAllocator::allocate_bytes` with the original native
filectrl.cpp label, handles allocation failure with `CloseHandle`,
then reads and logs without inventing short-read failure handling.
The 266B reader (8 E8/11 HIGHLOW) is a separate physical source
owner, adding +266 original game-authored `.text` bytes without
re-crediting any existing exact 368B/493B file Boss or native
allocator/Win32 helper.

## CORE/RECON-1085 — game filesystem existence wrapper source frontier

The adjacent original game slot2-serialized
[`0x004107A0` 157B filesystem-exists function](GAME_FILE_EXISTS157_NATIVE_FRONTIER.md)
now has complete meaningful C++ source, but remains **NONEXACT**.
The locked native path-copy constructor has a real extra format=0
argument which the installed C++20 STL copy constructor does not
emit, leaving a complete 155B/46 vs original 157B/47 method.
All native seven E8 and three HIGHLOW are independently verified.
The 368B/266B/493B file I/O Bosses remain separate whole-exact
code heads; no new exact credit is awarded for the 157B function.
