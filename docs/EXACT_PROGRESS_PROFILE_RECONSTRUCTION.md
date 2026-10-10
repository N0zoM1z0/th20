# Whole Profile construction

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

EXACT-084 reconstructs the complete 13,684-byte Profile constructor at
0050AF20, including all 123 physical Spell records. Its full compiler
contribution is 13,689 bytes, including the five following INT3 bytes.
All 131 relocations are replayed against independently reviewed record,
array-construction, diagnostic-runtime and exception anchors. No prefix or
masked structural comparison supplies exact credit.

## Native owner and capacities

| Member | Native offset | Count / stride |
| --- | --- | --- |
| Common ProgressRecordHeader | 0000 | 12 bytes |
| Two scalar words | 000C /0010 | 32 bits each |
| Scores | 0018 | 7 rows of 10 /40 bytes |
| Spell records | 0B08 | 123 /224 bytes |
| Scalar word | 76A8 | 32 bits |
| Statistics | 76B0 | 72 bytes |
| Practice records | 76F8 | 7 rows of 9 /16 bytes |

The complete Profile occupies 7AE8 bytes (31,464), with ordinary eight-byte
alignment. No explicit padding field is introduced. The Score, Spell and
Statistics types remain real shared values, with unknown roles named by offset.
Native Snapshot construction independently supplies the Profile stride and
constructs eighteen selectable records followed by a separate fallback record.
Snapshot, metadata, saving, parsing and gameplay linkage remain open here.

The retained, attested native listing is rechecked instruction by instruction
against the locked executable: all 3,549 heads cover all 13,684 body bytes.
It has one first-name byte store plus a 191-byte clear, followed by 122
192-byte name clears. Every record has two mode-indexed 32-bit counter pairs,
two 32-bit scalar values and an eight-byte scalar. These writes occupy exactly
123 records through 76A7; the next scalar store is at 76A8. This is storage
capacity evidence, rather than the count from a gameplay loop.

The independent startup function 0050EF00 iterates only 113 records when it
assigns identifiers and default values. It does not establish a 113-slot
physical array. Historical reference notes describing 113 constructor records
are corrected by this larger producer evidence. The extra ten slots are
constructed; their intended roles remain unknown.

Native members 00488510 and 00488590 index C0/C8 with a four-byte stride,
use signed comparison against 99,999, and increment below that limit. These
consumers corroborate separate signed capture/attempt counters for two modes,
instead of the rejected eight-byte scalar interpretation. The independent
Spell indexing member at 00486E10 multiplies its index by E0. None of these
small members receives additional credit from this construction comparison.

## Natural source and compiler observations

ProgressScore now expresses its defaults as member initializers with an implicit
constructor. Its existing complete 81-byte constructor stays exact at 0050E4A0;
physical ownership moves to ProgressProfile.cpp, where construction of the
remaining sixty Scores actually instantiates it. There is one shared semantic
body and no added physical coverage for this move. Default construction still
leaves the Score's natural alignment gaps untouched. Aggregate/value
initialization is a different language operation and must be tracked separately.

The maintained Profile uses partial aggregate initialization for its Score
matrix, Spell array and Statistics. The locked C++17 profile produces the native
first-row unrolled initialization, then the sixty-record zero/constructor
protocol, all 123 Spell records, Statistics and the 63-record practice loop.
The typed layout accounts for alignment gaps and has no raw giant byte buffer,
memset facade, copied decompiler source, arbitrary padding, assembly, inert
locals or profile-selected body. The original source spelling remains inferred.

Two early aggregate-initialization observations produce whole constructor
extents of 353 bytes under C++20 and 364 under C++17, using compiler helpers.
Partial initialization produces the native first Score row but initially gives
14,342 bytes when counter pairs are incorrectly modeled as eight-byte scalars.
Correct counter widths yield 13,604 bytes, leaving the Statistics initialization
difference. Giving the real Statistics members their observed zero defaults
recovers the complete 13,689-byte contribution without emission-only fields.
All failed candidates, complete contributions and observations remain private.

The genuine fixed, nonallocating constructor is noexcept. The complete folded
29-byte exception handler at 00567600 and 36-byte information record at
005A91B8 match, including information flags 5. The 56-byte array construction
iterator at 0040BC20 and the existing Score constructor match independently.
These folded support bodies receive no duplicate credit. Header and Practice
construction use their existing real owners and canonical native anchors.
Original annotations and authored/compiler identity remain pending.

ProgressProfile.cpp uses the explicit profile C++17 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc. This is a per-translation-unit observation;
it does not establish a global game build profile. Production headers and
semantic bodies remain shared under C++17 and C++20. C++20 helper emission is
not hidden with preprocessor branches or a weaker oracle.

## Executed semantic scope

O2/UBSan tests construct the complete production Profile in four dirty guarded
buffers under both C++17 and C++20. They inspect all seventy Scores, all 123
Spell records, both mode counter pairs, Statistics and all 63 practice records.
Aliasing checks change the final Spell slot, a distinct active slot and the
last Score/practice cells without changing adjacent slots or modes. All
constructors and the availability predicate are production code, with no
construction fixtures or original game data.

Existing dirty default-construction checks for the 81-byte Score contribution
also pass after the implicit-constructor change. Portable tests check member
values, aliases and guard preservation. They do not certify MSVC's Profile
padding writes: complete x86 replay verifies those separately. Runtime loading,
backup/saving, active-record initialization and full game behavior remain open.

## Frozen graph and storage

The graph has 606 canonical units across 117 comparison objects and 118559
disjoint comparison bytes. Source presence is 608 mappings, including the two
previous whole nonexact ECL buffer methods. Authored exact coverage remains
64 functions /16948 bytes; Profile's authored/compiler identity is pending.
One whole reference Profile association closes, bringing absorption to 207
across all 6945 terminal reviews. Existing reference raw bodies are historical
behavioral leads and are not imported.

After fresh frozen replay, public CI and tracking checks, retire completed probe
products with current canonical objects/receipts protected. Preserve native
listings, failed hypotheses, original receipts and changed input history.
Post-cleanup replay must reuse the existing graph without another cold build.
Reconstruction remains active; whole Enemy roots/readers/State, Player and game
runtime are still open. Continue coherent core batches at reduced scheduling
priority, using repo-python and attested Ghidra without REA or delegation.

Final checkpoint: all 54 public tests pass (168.600 seconds). Protected
retirement removes 12 probe products (285566 bytes), with
147992 net bytes saved after lossless receipt/input and replay archives.
All 234 canonical product hashes remain unchanged; post-cleanup replay
is 606/606 strict exact using 117 existing objects without rebuilding.
