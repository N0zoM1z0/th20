# Complete Snapshot and Metadata construction

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

EXACT-085 closes the actual persisted-record hierarchy started by EXACT-084.
The complete Metadata constructor at 0050E6E0 strictly replays 612 bytes.
The complete Snapshot constructor at 0050E540 replays its 138-byte body and
143-byte compiler contribution, including the five following INT3 bytes.
All nine relocations use independently established native destinations.

## Native owners and independent consumers

| Metadata member | Offset | Storage / construction |
| --- | --- | --- |
| Common ProgressRecordHeader | 0000 | Existing 12-byte owner |
| Name | 000C | Ten bytes preserved by default construction |
| Neutral byte arrays | 0016 /0036 /0056 /0058 | 32 /32 /2 /8 zero bytes |
| Neutral eight-byte scalar | 0060 | Zero |
| Neutral byte arrays | 0068 /00E8 | 128 /64 zero bytes |
| Selection values | 0128 | Sixteen 32-bit values |
| Available counters | 0168 | Nine 32-bit slots; slot eight defaults to 9 |
| Used counters | 018C | Nine zero 32-bit slots |
| Randomized bytes | 01B0 | 32 zero bytes |
| Neutral byte /checksum byte | 01D0 /01D1 | Zero |
| Randomized bytes | 01D2 | 32 zero bytes |

Metadata occupies 1F8 bytes with natural eight-byte alignment. Unknown byte-array
roles retain neutral names; their representation does not assert word widths
inside the 0068/00E8 intervals. No explicit padding is introduced. Default
construction preserves the ten name bytes and natural terminal alignment gap.
The separate startup protocol writes the name, record tags and randomized bytes.

The full retained native producers are rechecked instruction by instruction
against the locked PE, with complete coverage of both bodies. Separate consumer
0050F090 supplies the name capacity, byte-indexed 32-byte randomized regions and
the 0168 array's index-eight assignment. Mutable array indexing at 004BD080
checks capacity nine and uses a four-byte stride. Read protocol 004BD6B0 also
indexes this real array through an independently observed const adapter.
These consumers reject the early eight-slot-plus-independent-scalar model.
The ninth slot's broader gameplay meaning remains unresolved.

Consumer 00464100 distinguishes the selection table at 0148 when mode is four
and the table at 0128 otherwise; each table has two characters and four slots.
The first slot defaults to its character index, and the other three default to
eight. There are sixteen values total, rather than two sixteen-entry tables.
The historical REF-025 review wording is corrected at this checkpoint. Native
used-count consumers at 0051B970/0051BA10 corroborate 018C and four-byte indexing;
complete manager locking, validation and checksum behavior remains open.

Snapshot contains a zero file-size word and two null buffer pointers, followed
by eighteen selectable Profiles at 0010, a separate fallback at 08A460, and
Metadata at 091F48. Native size is 092140 bytes. The existing real Profile owner
is used directly, with all seventy Scores, 123 Spell slots and 63 Practice slots
per record. The four-byte gap after the pointer prefix follows Profile's natural
alignment; no padding member or raw 600-KiB receiver buffer represents the type.
The enclosing save manager's observed cleanup releases the two buffer slots;
this constructor does not perform allocation, file I/O or thread startup.

## Source, compiler and complete support

ProgressStorage.hpp and ProgressStorage.cpp supply shared production declarations
and defaulted constructors. C++17 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc is an explicit per-TU observation. Both C++17 and C++20 use the same
headers and semantic bodies. Original declaration spelling and authored/compiler
identity remain pending; no global game build profile follows from these units.

An early noexcept Metadata declaration emits a 588-byte contribution with an
exception wrapper absent from the native constructor. Without that annotation,
the initial eight-slot counter model emits 541 bytes, differing from native at
the first available counter. The genuine nine-slot array with explicit defaults
recovers all 612 bytes. Unknown intervals remain byte arrays, without speculative
word types. No inert fields, raw whole-record memset, copied decompiler body,
assembly or source-selected branch supplies exactness.

Fixed Snapshot construction is genuinely nonallocating and nonthrowing. Its
complete folded exception handler at 00567600 is 29 bytes, its information record
at 005A91B8 is 36 bytes with flags five, and the array construction iterator at
0040BC20 is 56 bytes. All three replay independently, using the earlier reviewed
EH/runtime graph and existing Profile anchor. Folded support gets no duplicate
coverage. Metadata has no exception wrapper in this recovered profile.

The unrelated whole Enemy State tick was also observed under C++17, changing
only the language setting from its historical strict-FP profile. Its full
1280-byte contribution retains the same 180 differences and relocation records
as C++20. The late missing NOP remains unexplained; this observation grants no
source registration, canonical unit or partial credit. The advancement candidate retains
its void contract; no fake return is introduced to shape it.

## Executed scope and remaining work

O2/UBSan checks construct standalone Metadata and two complete Snapshots in four
dirty guarded buffers under both C++17 and C++20. All nineteen actual Profile
constructors execute in each Snapshot. Every Score, physical Spell slot, mode
counter, Statistics member and Practice cell is inspected, together with Metadata
defaults, the untouched name and all selection/counter capacities. Aliases
change the last selectable Profile, fallback, final Spell mode, ninth used
counter and final selection independently of the backup and adjacent slots.
The initial test expectation indexed default selections incorrectly; the
corrected check follows the independent mode/character/slot consumer protocol.
These are maintained constructors without record fixtures or original data.

Portable tests check live members, aliases and guards; complete native comparison
separately verifies x86 pointer layout, padding and compiler support. They do not
accept parsing, saving, buffer release, checksum/RNG updates, thread lifecycle or
playable game behavior. Those protocols and whole Enemy/Player roots remain open.

The graph is 608 canonical units /118 comparison objects /119314 disjoint bytes.
Source presence is 610 mappings, including two whole nonexact ECL methods.
Authored exact coverage remains 64 functions /16948 bytes. Two whole reference
associations close, bringing absorption to 209 across 6945 terminal reviews.
Preserve canonical products, native evidence and failed inputs; retire completed
probe builds only after frozen strict replay and public CI, then recompare the
existing graph without rebuilding it. Reconstruction remains active.

Final checkpoint: all 55 public tests pass (159.441 seconds). Protected
retirement removes 10 probe products and 84 archived header copies,
saving 176426 net bytes after receipt/input and replay archives. All 236
canonical product hashes remain unchanged; post-cleanup replay is
608/608 strict exact using 118 existing objects without rebuilding.

CORE/EXACT-086 now composes these real Snapshots in the actual SaveManager and
checks owned threads, nineteen-record/Metadata merge extents and real four-buffer
release. Five whole member-task/copy/merge contributions are exact; its three
whole lifecycle roots remain nonexact. Disk load/save/parse and allocator startup
are explicit test boundaries, not completed runtime. See
[SaveManager evidence](EXACT_PROGRESS_SAVE_MANAGER_RECONSTRUCTION.md).
