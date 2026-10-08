# Current reconstruction handoff

## CORE/EXACT-088 — 2026-10-08 — Real archive writing and full codec integration

Whole archive encryption at 4103C0 strictly replays all 446 bytes and six
independently established relocations. ArchiveCrypt.cpp owns both cipher
directions under the existing signed ABI and real new[]/delete[] scratch family.
Whole compression at 539550 now uses the actual shared ring/tree, C allocator,
lookahead and token protocol. Its complete candidate is 964/native 1036 bytes,
so it remains nonexact, with no partial unit or reference absorption.
Original filectrl.cpp/LzssUtil.cpp diagnostics establish both authored origins.
See [complete protocol and unresolved emission](ARCHIVE_WRITE_RECONSTRUCTION.md).

The compressor initializes a native scalar and updates it in seven byte-flush
chains; no consumer, return or escape is established. Its 70 instruction bytes
do not fully explain the 72-byte extent difference. No inert accumulator or fake
result is added for emission. Source identity, stack/expression differences and
the unused sum's purpose remain open; keep this negative evidence intact.

Actual O2/UBSan checks exercise compression -> encryption -> decryption ->
decoding -> checksum/parser -> backup/copy-back over complete CR/ST records,
all eighteen Profiles, fallback and Metadata. Independent token/permutation
models cover four patterns, fourteen positive lengths through 20000, ring wrap,
overlap, complete-byte counts, retained tails and untouched failure state.
Independent synthetic malformed-record fixtures remain. Native startup and disk
load/save boundaries are fixtures; full filesystem writes/game runtime are open.

Frozen replay passes 615/615 units /120 fresh objects /120303 disjoint bytes.
There are 622 source mappings, including seven complete nonexact methods.
Exact-unit origins: 541 pending /9 library /65 authored. Confirmed authored
functions total 67; authored exact bytes are 17394, or 90.34% of the expanded
provisional denominator. All 6945 reference reviews remain terminal, with 213
absorbed associations. All 58 public tests pass in 127.297 seconds.

Protected retirement removes 6 obsolete probe products
(144787 bytes). Original receipts and all
3 historical input versions are losslessly
archived. Net savings after evidence archives and cleanup replay: 31538 bytes.
All 240 canonical product hashes and 4733
retained evidence files stay unchanged. Post-cleanup 615/615 strict replay uses
120 existing objects without rebuilding. Cumulative retired build products:
2656 files /1015284912 bytes.
Analysis is 82M and build is 5.6M; tools, target, reference and Ghidra are protected.
Proofs: core088-whole-audit.json, core088-native-unused-accumulator.json,
core088-final-frozen-source.json, exact088-canonical-results.json.gz,
core088-cleanup.json and core088-post-cleanup-results.json.gz.
Completed configuration, registration, cleanup and documentation writers must
never rerun. Restore original SHA-bound declarations before historical probes.

Continue whole SaveManager load 562/write 1198/save 174 with original path, I/O
and initialization owners. Respect load's 2x10 physical visits across nine-element
rows and fallback. Whole Enemy/State, Controller and Player remain open.
Keep one writer, serial nice 15, repo-python, attested Ghidra, no REA/delegation
and periodic protected retirement. Reconstruction remains active.

## CORE/EXACT-087 — 2026-10-08 — Whole progress-file parsing and protected retirement

Complete SaveManager parsing now executes the actual checksum, archive cipher,
LZSS decoder, C allocator and current/backup merge. It remains whole nonexact:
813 candidate/native824 bytes, with every native branch/tail retained. The actual
record-header member checksum strictly replays all 80 bytes. Typed 2x9 Profiles
replace the flat declaration without changing layout; the complete existing
Snapshot 143 and all prior units remain strict exact. Complete native literals
are independently verified under the source-local CP932 compiler recipe.
See [parser evidence and correction](PROGRESS_FILE_PARSE_RECONSTRUCTION.md).

CORE/EXACT-086's array-delete fixture and heap-family claim were incorrect and
are superseded: native 41F610 uses malloc and 41F670 uses free. Production and
lifecycle tests now use that actual family and shared null-safe reset protocol;
ordered real free calls are observed after save. ArchiveCrypt scratch keeps its
separate new[]/delete[] family. Complete lifecycle candidates remain nonexact:
constructor 198/native 199, commit 68/70, destructor 304/299. No new lifecycle credit,
fake returns, emission-only locals, padding or shortened extents are introduced.

Frozen replay passes 614/614 units /120 fresh objects /119857 disjoint bytes.
There are 620 source mappings, including six whole nonexact methods. Exact-unit
origins are 541 pending /9 library /64 authored; authored exact bytes stay 16948.
Independent score.cpp diagnostics establish this nonexact parser as authored,
so 65 authored functions are now confirmed and authored-byte exactness is 95.36%
of the expanded provisional denominator. Checksum identity remains pending.
One complete reference association closes: 212 absorbed across all 6945 terminal
reviews. All 57 public tests pass (131.530 seconds).

Actual O2/UBSan encrypted synthetic files execute all 18 selectors, fallback,
complete CR/ST records, metadata members, buffer identity, decoded contents and
real backup -> parse -> copy-back. Tests cover all observed header rejections,
retained decoded ownership, version/checksum/size rejection, unknown-magic stop,
copy-before-negative-remaining, checksum prefix exclusion and safe negative
extents. Host assignment tests compare members; native REP MOVSD/padding is
separate x86 evidence. Process startup and disk load/save remain explicit
fixtures. Native malformed UB domains, compression/encryption writing and full
game runtime remain open. The older boundary test keeps its explicit parse
fixture to exercise full signed merge results; it does not link the real parser.

Protected retirement removes 15 completed/rejected probe products
(338711 bytes) and 8 copied private headers
(13613 bytes). Original receipts and all 11
historical/copied input versions are losslessly archived. Net savings after
archives and post-cleanup replay: 179919 bytes. All 240 canonical product hashes
and 4692 retained evidence files remain unchanged.
Post-cleanup 614/614 strict replay uses 120 existing objects without rebuilding.
Cumulative retired build products: 2650 files /
1015140125 bytes. Analysis is 81M and
build is 5.6M; locked tools, target, reference and Ghidra stay protected.
Proofs: core087-final-frozen-source.json, exact087-canonical-results.json.gz,
core087-whole-audit.json, core087-cold-support.json and
core087-post-cleanup-results.json.gz. Completed configuration, registration,
cleanup and documentation writers must never rerun. Historical probes require
restoration of their original hash-bound declarations before reproduction.

Continue whole SaveManager load 562/write 1198/save 174 with actual I/O and codec
protocols. Load's 2x10 initializer visits cross 9-element row geometry and reach
fallback; do not invent out-of-array typed subscripts. Whole Enemy/State,
Controller and Player remain open. Keep one writer, serial nice 15, repo-python,
bounded attested Ghidra, no REA/delegation and periodic protected retirement.
Reconstruction remains active.

## CORE/EXACT-086 — 2026-10-08 — SaveManager ownership and member tasks

The actual 1242D8 SaveManager now composes two real Snapshots, a neutral zero
word/64-byte interval and the existing Worker. Complete member-task construction,
invocation/start and current/backup copy/merge strictly replay five whole units,
463 bytes and nineteen independent relocations. EH39/13/44 also agrees without
additional coverage. The native three-word callable copies receiver, member
operation and argument; its heap-tuple/invoke consumers are independently
reviewed. The reference no-argument lambda/free-copy/raw facade is not imported.
See [whole-owner evidence](EXACT_PROGRESS_SAVE_MANAGER_RECONSTRUCTION.md).

The complete lifecycle roots remain nonexact: constructor198/native199,
commit68/70 and destructor262/299. Native post-call NOPs and caller null-check
partition remain unresolved; moving the identical join body into the class
does not close the difference. The member jthread constructor is116/native123
with named-forwarding differences. No fake return, redundant shaping condition,
assembly or shortened extent is introduced. Void one-word callback spelling is
an inference; original source names and authored identity remain pending.

Frozen replay passes613/613 units /119 fresh objects /119777 disjoint bytes.
Source mappings total618, including five whole nonexact methods; exact-unit
origins are540 pending /9 library /64 authored (16948 authored bytes unchanged).
Two reference associations close,211 absorbed across all6945 terminal reviews.
All 56 public tests pass (174.781 seconds). Actual O2/UBSan thread/owner
checks cover copied inputs, detached replacement, join-before-save, destructor
waiting, real ordered four-buffer release and null-buffer teardown. Whole
nineteen-Profile/Metadata copies preserve file size/buffer ownership; merge
returns full positive/negative fixture results and copies back in either case.
Load/save/parse and allocator startup are explicit fixtures and genuine pending
production dependencies. No disk/checksum/serialization/game runtime follows.

Protected retirement removes 10 completed probe products
(391494 bytes). Original receipts and 2
historical input versions are losslessly archived; net savings after those
archives and the post-cleanup replay are 254260 bytes. All238 canonical product
hashes and 4624 retained evidence files stay
unchanged. Post-cleanup613/613 strict replay uses119 existing objects without
rebuilding. Cumulative retired products: 2635 files /
1014801414 bytes. Analysis is81M and
build is5.5M; tools, target, reference and Ghidra stay protected.
Proofs: core086-final-frozen-source.json, exact086-canonical-results.json.gz,
core086-cold-support.json and core086-post-cleanup-results.json.gz.
Completed configuration, registration, cleanup and documentation writers must
never rerun; restoring older probes requires their original hash-bound inputs.

Continue whole SaveManager parse824/load562/write1198/save174 with real record,
allocator, codec and I/O protocols; do not reinterpret a pending dependency as
an accepted replacement service. Whole Enemy roots/readers/State, Controller
and Player remain open. Keep one writer, serial nice15, repo-python and
attested Ghidra, without REA or delegation. Reconstruction remains active.

## EXACT-085 — 2026-10-08 — Complete Snapshot and Metadata owners

The complete Metadata constructor at 50E6E0 strictly replays 612 bytes, and
Snapshot at 50E540 replays its full 138/143-byte contribution. Nine independently
anchored relocations and the complete folded EH handler29/info36 flags5/array56
all agree. The actual 92140 Snapshot composes eighteen real Profiles, a separate
fallback and 1F8 Metadata with natural alignment. There is no explicit padding
member or raw whole-record facade. See [whole-owner evidence](EXACT_PROGRESS_STORAGE_RECONSTRUCTION.md).

Independent indexing/startup/consumer evidence proves nine available and used
counter slots; the final available slot defaults to nine. Selection consists of
two eight-entry tables (sixteen values total), rather than the historical review's
two sixteen-entry description. Ten Metadata name bytes remain untouched until
startup. Unknown byte-region roles retain neutral names without speculative word
widths. Defaulted shared constructors under the explicit C++17 TU profile explain
all native bytes; original spelling, authored/compiler identity and global flags
remain unproven. Snapshot's fixed construction is genuinely noexcept; the early
noexcept Metadata hypothesis emits an absent wrapper and is rejected.

The frozen graph strictly replays 608 units /118 fresh objects /119314 disjoint
comparison bytes. Source mappings total 610, including the two whole nonexact
ECL buffer methods. Exact-unit origins are 535 pending /9 library /64 authored;
authored coverage stays 16948 bytes. Two whole reference associations close,
209 absorbed across all 6945 terminal reviews. All 55 public tests pass
(159.441 seconds). O2/UBSan checks execute actual standalone Metadata and two
complete Snapshots across four dirty patterns under C++17 and C++20; every
Profile member, all 123 physical Spell slots, fallback, Metadata defaults,
preserved names and live aliases are checked. No record fixture or game data
supplies construction. Native pointer layout, padding and support are separately
verified by the full x86 comparison.

The whole Enemy State tick was observed with only its historical strict-FP
profile's language setting changed to C++17. It retains the same complete1280
extent, relocation records and 180 differences as C++20. The late missing NOP
remains open; this negative observation grants no unit, source or partial credit.
The advancement candidate keeps its void contract; no invented return or inert shaping is used.
Whole Enemy roots/readers/State, Controller and Player remain core work.
Complete startup, parsing/load/save, locking/checksum/RNG, Worker and buffer
release still remain open for the new storage owners; this is not game-runtime
acceptance. Continue coherent core batches, serial nice15, repo-python and
attested Ghidra, without REA or delegation. Reconstruction remains active.

Protected retirement removes 10 completed probe products
(207309 bytes) and 84 copied private headers
(131990 bytes). Original receipts and exact copied inputs are losslessly archived.
Savings after those archives are 233496 bytes; the post-cleanup
replay archive costs 57070 bytes, leaving 176426 net
bytes saved. All 236 canonical product hashes and
4566 retained evidence files remain unchanged.
Post-cleanup 608/608 strict replay uses 118 existing objects without rebuilding.
Cumulative retired products: 2625 files /
1014409920 bytes; copied-input and earlier archival savings
are separately recorded. Analysis is 80M and build 5.4M;
installed tools, target, reference and Ghidra evidence stay protected. Current
proofs are core085-final-frozen-source.json, exact085-canonical-results.json.gz,
core085-canonical-support.json and core085-post-cleanup-results.json.gz.
Completed configuration, registration, cleanup and documentation writers must
never rerun. Archived copied headers restore by path and SHA256 before probing
the historical private State candidate again.

## EXACT-084 — 2026-10-08 — Whole Profile construction and protected cleanup

The complete Profile constructor at 50AF20 strictly replays 13,684 body bytes,
the full 13,689-byte contribution and all 131 independently anchored relocations.
The actual typed 7AE8 owner contains seventy Scores, 123 physical Spell records,
72-byte Statistics and 63 Practice records. Independent startup initializes only
113 Spell identifiers/defaults; the extra ten roles remain unknown. The previous
113-slot constructor description is corrected by the whole producer extent.
See [whole-owner evidence](EXACT_PROGRESS_PROFILE_RECONSTRUCTION.md).

Natural partial aggregate initialization under the explicit C++17 TU profile
recovers the complete constructor. Genuine fixed nonallocating noexcept
construction agrees with the full 29-byte folded EH handler, 36-byte information
record (flags 5) and 56-byte array construction iterator. Existing Score defaults
become implicit shared member initialization; the complete 81-byte Score
constructor moves to its actual instantiating Profile TU without duplicate
credit. There are no emission-only fields or profile-selected source bodies.
This establishes neither global language/flags nor original source identity.

The frozen graph strictly replays 606 units /117 fresh objects /118559 disjoint
comparison bytes. Source mappings total 608, including the two whole nonexact
ECL buffer methods. Exact-unit origins are 533 pending /9 library /64 authored;
authored coverage remains 16948 bytes. One complete reference association closes,
207 absorbed across all 6945 terminal reviews. All 54 public tests pass
(168.600 seconds). Actual complete Profile construction and aliasing run in
dirty guarded buffers under both C++17 and C++20 with O2/UBSan; every physical
slot, both counter modes, Score row and Practice row is checked. Existing Score
dirty default-construction checks also pass. Host tests do not certify native
padding writes; the full x86 comparison verifies those separately.

Protected retirement removes 12 completed probe products
(285566 bytes). Original receipts and
2 historical input versions are losslessly archived;
product savings after those archives are 204874 bytes. The
post-cleanup replay archive costs 56882 bytes, leaving
147992 bytes of net retirement savings. All 234 canonical product hashes and
4513 private evidence files remain unchanged.
Post-cleanup 606/606 strict replay uses 117 existing objects without a cold
rebuild. Cumulative retired products: 2615 files /
1014202611 bytes. Analysis is 80M and build 5.4M;
installed tools, target, reference and Ghidra evidence stay protected. Current
private proofs are core084-final-frozen-source.json,
exact084-canonical-results.json.gz and core084-post-cleanup-results.json.gz.
Completed configuration, registration and cleanup writers must never rerun.

Whole Snapshot/metadata, active-record initialization, loading/saving and game
runtime remain open. Whole Enemy root/readers/State tick, Controller frame and
Player remain core dependencies. C++17 is new per-owner compiler evidence, not a
license to repeat unchanged failed hypotheses or switch global profiles.
Continue coherent core batches, serial nice15, repo-python and attested Ghidra,
without REA or delegation. Reconstruction remains active.

## CORE/EXACT-083 — 2026-10-08 — Actual ECL buffer pipeline and protected cleanup

Complete production append and instruction resolution now run in the actual
VM/Manager/Stack/Loader/PMR pipeline, replacing its buffer-resolution fixture.
Both remain nonexact: append is 878/native 876 bytes; instruction is 54 bytes
with two structural differences. Neither receives a canonical unit or absorption
credit. The whole 54-byte derived player binding strictly replays through the
actual Session/context. See [buffer protocol evidence](ECL_BUFFER_RECONSTRUCTION.md).

The frozen graph strictly replays 605 units /116 fresh objects /104870 disjoint
comparison bytes. There are 607 source mappings, including two whole nonexact
buffer methods; exact-unit origins are 532 pending /9 library /64 authored,
with authored coverage unchanged at 16948 bytes. One complete reference binding
association closes: 206 absorbed across all 6945 terminal reviews. All 53 public
tests pass (141.326 seconds), including writable-buffer aliasing, duplicate
stability, recursive include publication, rejection, nontransactional allocation
failure and actual binding to both Session contexts. Four compiler-local literal
labels are independently reidentified by complete native text at existing
addresses; all existing contributions retain exact bytes.

Whole Controller frame 4A5040/734 is newly exported with attestation but remains
unimplemented. Twenty pointer-initialization compiler fixture functions are
identical under C++14/17/20 and emit no native preclear under the tested profile.
The Player +0x14850 interval remains unknown; its bounded negative scan supplies
no complete owner/type proof. Whole Enemy root/readers/State tick and game runtime
remain open. Derived include/resource I/O, link allocation, startup, unused
frame/interpolation and Enemy outer movement/opcode/retirement remain dependencies
or explicit fixtures. Continue core protocols in coherent batches, serial nice15,
repo-python, attested Ghidra, no REA/delegation. Reconstruction remains active.

Protected retirement removes 12 completed probe products (331306
bytes). Original receipts and three historical input versions are losslessly
archived; savings after those archives are 268753 bytes. The
post-cleanup replay archive costs 56064 bytes, leaving
212689 bytes of net retirement savings. All 232 canonical product hashes and
4470 private evidence files remain unchanged.
Post-cleanup 605/605 strict replay uses 116 existing objects without a cold
rebuild. Cumulative retired products: 2603 files /1013917045 bytes; earlier
separate archival savings remain recorded. Analysis is about 79 MiB and build
5.3 MiB; tools/game/reference remain protected. Current private proofs are
core083-final-frozen-source.json, exact083-canonical-results.json.gz and
core083-post-cleanup-results.json.gz. Completed registration, configuration and
cleanup writers must never rerun.

## EXACT-082 — 2026-10-08 — Actual ECL async and call setup

Seven complete contributions add 524 bytes: actual Manager spawn/find/mark-only
invalidation, Runtime scalar allocation, Loader activation and two owned getters.
VM opcode21 now calls invalidate_async at53E560, distinct from destructive owner
cleanup at4973C0. The inherited 22-byte current-instruction getter moves to its
actual Manager base without additional physical coverage. Existing Position,
Runtime and Manager lifetime units retain exact bytes under genuine nonthrowing
initialization contracts; original annotation spelling remains inferred. See
[whole async evidence](EXACT_ECL_ASYNC_RECONSTRUCTION.md).

The frozen graph strictly replays 604 units /115 fresh objects /104816 disjoint
comparison bytes. Origins:531 pending /9 library /64 authored /16948 bytes.
Six complete reference associations close,205 absorbed across6945 terminal reviews.
Owned O2/UBSan tests now execute actual VM/call_into/Manager/Stack/Loader and PMR
lifetime bodies across signed IDs, skips, descriptor conversions, missing names,
deferred spawn, signaling and invalidation-before-retirement. Node factory53B410,
buffer resolution, startup, unused interpolation/frame routes and Enemy movement/
opcode/outer retirement remain fixtures. Bit0's wider role stays unknown. Whole
41 KB Enemy root/readers/State tick, Player and game runtime remain open.

Continue whole core protocols in coherent batches, serial nice15, repo-python,
attested Ghidra, no REA/delegation and protected storage retirement. The graph is
frozen in core082-final-frozen-source.json and fully replayed in
exact082-canonical-results.json.gz. Completed configuration/registration writers
must never rerun. Reconstruction remains active.

All52 public tests pass (183.390 seconds); target/tracking/reference/progress
checks pass. Protected cleanup retires16 completed probe object/receipt files,
445529 bytes;252 copied private headers (395825 bytes), original receipts and
seven historical input versions are losslessly archived. Net product/input
savings after the three archives:597030 bytes. All230 canonical product hashes
and4428 private evidence files remain unchanged. Post-cleanup604/604 strict replay
uses115 existing objects without a cold rebuild. Cumulative retired products:
2591 files /1013585739 bytes; prior separate archival savings remain documented
in earlier batches. Analysis is about78 MiB and build5.2 MiB; tools/game/reference
remain protected. Final cleanup proof:core082-post-cleanup-results.json.gz.
Completed cleanup writer must never rerun.

## EXACT-081 — 2026-10-08 — Initialization hypothesis and protected storage cleanup

The defaulted/value-initialized Enemy hypothesis preserves the complete existing
215-byte constructor contribution, but its allocation emits 79 bytes versus
native `4A2910`/73. The direct `memset` call differs from the native thiscall
initialization helper. This experiment supplies no new exact credit, original
source identity or complete EH claim. Production owners/profiles/layouts stay
unchanged; Controller diagnostic/generation side effects are not replaced. See
[initialization observations](EXACT_CONTROLLER_CONSTRUCTION_RECONSTRUCTION.md).

The graph remains 597 units /113 objects /104292 disjoint comparison bytes;
origins 524 pending /9 library /64 authored /16948 bytes; reference absorption
199 across all 6945 terminal reviews. The full existing graph strictly replays
after probe retirement without a cold rebuild. Continue whole core owners and
dispatchers; avoid repeating this failed factory explanation unchanged. Serial
nice15, repo-python, attested Ghidra and no REA/delegation remain required. The
reconstruction goal remains active.

Four completed probe products (81293 bytes) are retired. Original receipts and
84 copied private headers (131922 bytes) are losslessly archived with original
paths and SHA-256 identities; product/input savings after archives are 158990
bytes. A separate pinned D3DX download cache (9833468 bytes) is removed after
checking all 63 extracted SDK files byte-for-byte. Bootstrap now reuses the
installed SDK without re-downloading that cache; a real bootstrap run, including
locked analysis/compiler/version checks, succeeds after removal. Total product,
input and cache savings are 9992458 bytes; the compressed current replay proof
costs an additional 55188 bytes. All 226 canonical products and installed SDK
files retain their hashes. Native evidence and failed probe source remain
preserved. Cumulative retired products/cache: 2575 files /1013140210 bytes;
copied-header archival is accounted separately.

Private inventories are core081-cleanup.json and core081-d3dx-cache-plan.json;
complete proof is core081-post-cleanup-results.json.gz. Restore private copied
headers from core081-retired-probe-headers.json.gz before rebuilding the probe.
The one-time retirement writer is completed; never rerun. Source still matches
core080-final-frozen-source.json. After cache retirement, all 574 distinct current
receipt inputs/headers, the installed SDK and canonical product hashes are
re-attested; the existing strict replay remains valid. This final attestation is
core081-final-cleanup-attestation.json. All 51 public tests pass (157.721 seconds),
with target/tracking/reference/progress gates current.

## EXACT-080 — 2026-10-08 — Actual State/Manager script pipeline

Three complete script-progression/async-traversal/Timer-step contributions add
419 bytes. Actual 752-byte State uses a four-byte member callback at +2E0;
whole invocation, null initialization and layout are compiler-verified against
the native ECX/word/full-result protocol. Original C++ spelling stays inferred.
Manager preserves cached-next traversal, primary-failure context and real async
runtime destruction before link detach/release. Clock lookup preserves the
established mode0 domain; no fictitious extra clock entries are introduced. See
[script pipeline evidence](EXACT_ENEMY_SCRIPT_PIPELINE_RECONSTRUCTION.md).

The frozen graph is 597 units /113 fresh objects /104292 disjoint comparison bytes.
Origins remain 524 pending /9 library /64 authored /16948 bytes. Three complete
reference associations close, 199 absorbed across all 6945 terminal reviews.
Owned O2/UBSan checks now execute real production VM tick as well as the Manager/
State pipeline and real PMR lifetime: completion subsets, distinct primary context,
deferred spawn, signed failures, callback recursion and IEEE step values. Loader,
spawn, movement, Enemy opcode/outer retirement and unused helper routes remain
explicit fixtures. Full State tick's 1280-byte candidate stays nonexact: two natural
advancement/ownership experiments retain the same NOP discrepancy. Whole dispatcher,
readers, Player and runtime remain open. Continue serial nice15, repo-python,
attested Ghidra, no REA/delegation and protected cleanup. Goal remains active.

All 51 public tests pass (133.069 seconds); target/tracking/reference/progress
gates pass. Protected cleanup retires 10 completed probe object/receipt products,
244614 bytes. Original receipts and 6 historical source/header versions are
losslessly preserved in compressed archives of 74399 and 5153 bytes; net savings
165062 bytes. All 226 current canonical product hashes and all native/failed
source evidence remain unchanged. Post-cleanup 597/597 strict replay uses existing
objects without a cold rebuild. Cumulative retired products: 2570 files /
1003225449 bytes; separate prior archival savings: 12865565 bytes. Analysis is
about 77 MiB and build 5.1 MiB; installed tools/game/reference remain protected.
Final source is frozen in core080-final-frozen-source.json; current complete proofs
are exact080-canonical-results.json.gz and core080-post-cleanup-results.json.gz.
One-time configuration/registration/cleanup writers are completed; never rerun.

## EXACT-079 — 2026-10-08 — Enemy spawn and time-scale orchestration

Two complete Enemy core functions and the Animation slowdown setter add 1257 body
/1399 comparison bytes. Full 780-byte spawn includes the eight-entry jump table
and all 110 selectors; full 448-byte tick preserves ordered handle resolution,
IEEE clock clamping/save/restore, sticky flags and delegated signed return. Actual
Enemy/EnemyState/Session, PMR records, health/pattern members and Timer value
assignment remain shared natural owners. See
[spawn/tick evidence](EXACT_ENEMY_SPAWN_TICK_RECONSTRUCTION.md).

The frozen graph is 594 units /110 fresh objects /103873 disjoint comparison bytes.
Origins remain 521 pending /9 library /64 authored /16948 bytes. Two complete
reference associations close, 196 absorbed across all 6945 terminal reviews.
Owned O2/UBSan checks cover 108 IEEE time-scale cases and 3300 spawn cases using
production lifetimes and orchestration. Whole State tick, renderer/retirement and
virtual readers are explicit fixture boundaries. Negative rank modes are outside
the defined shift domain. No runtime or whole-game credit follows.

A whole 1280-byte EnemyState tick experiment remains nonexact because a missing
NOP after Pattern tick shifts subsequent Timer code. Candidate source, headers,
profiles and diagnostics are retained privately. The 41 KB dispatcher and both
whole readers remain open. Continue serial nice15, repo-python, attested Ghidra,
no REA/delegation and protected cleanup. Goal remains active.

All 50 public tests pass (135.233 seconds); target/tracking/reference/progress
gates pass. Protected cleanup retires 14 completed probe object/receipt products,
481332 bytes. Original receipts and 16 historical source/header versions are
losslessly preserved in compressed archives of 113827 and 9495 bytes; net savings
358010 bytes. All 220 current canonical product hashes and all native/failed
source evidence remain unchanged. Post-cleanup 594/594 strict replay uses existing
objects without a cold rebuild. Cumulative retired products: 2560 files /
1002980835 bytes; separate prior archival savings: 12865565 bytes. Analysis is
about 76 MiB and build 4.9 MiB; installed tools/game/reference remain protected.
Final source is frozen in core079-final-frozen-source.json; current complete proofs
are exact079-canonical-results.json.gz and core079-post-cleanup-results.json.gz.
One-time configuration/registration/cleanup writers are completed; never rerun.

## EXACT-078 — 2026-10-08 — Bullet pool and resource ownership

Eleven complete contributions establish actual 1320-byte Bullet values and the
2649512-byte BulletInf owner with a typed 2001-entry pool, fourteen ExtendedCommands
per Bullet, a typed 2001-handle array and real free/active intrusive lists. Native
allocation, RTTI/vtable/literal/publication, complete array/EH contracts and genuine
shared_ptr<ShotMetadata> lifetime are independently checked. Bullet +88 is a
distinct packed color; +58 is the actual borrowed BulletStyle pointer. Color is
independently assigned0xFFD08080 and transferred to
EffectParameters; it is not an Animation handle despite the folded constructor. Two six-pointer draw
arrays replace flattened reference integers; Controller +44 is its count. Full
construction/destruction/disable/count/context contributions add 1471 body /1491
comparison bytes; frozen 591 units /108 fresh objects replay 102474 disjoint bytes.
Origins are 518 pending /9 library /64 authored /16948 bytes. Five complete reference
associations close, 194 absorbed across all 6945 terminal reviews. See
[Bullet evidence](EXACT_BULLET_STORAGE_RECONSTRUCTION.md).

Context slot0 now has the actual borrowed BulletController pointer. Both process
478E80 and direct40C300 routes reach BulletInf; 4992F0 reads its count44. Actual
EnemyController lookup remains478060/slot8. Typed Context getter/setter and array/
shared-pointer support pass complete strict comparisons without duplicate credit.
Reference Session primary_owner returns a pointer reference instead of the stored
pointer value and remains nonexact; owner closure does not justify ABI substitution.

Owned O2/UBSan checks cover all2001 dirty records/natural gaps, real defaults and
sentinels, two Context routes, full count/binding mutation boundaries, actual
callback disabling and complete shared metadata release including the final slot,
then actual pool destruction after reacquiring a resource. Controller destruction
and enable are explicit fixtures; full factory/initialize/update/draw/retirement,
renderer, Player tail/ANM lifetime, both Enemy readers and41KB opcode root stay open.
No runtime/whole-game credit follows. Source is frozen; one-time configuration and
registration writers are completed. Continue serial nice15, repo-python, attested
Ghidra, no REA/delegation and protected cleanup. Goal stays active.

All49 public tests pass (145.482 seconds); target/tracking/reference/progress gates
pass. Protected cleanup retires six completed probe object/receipt products /160000
bytes, while losslessly preserving original receipt texts in a45320-byte compressed
archive; net savings114680 bytes. All216 current canonical hashes and all native/
failed-source evidence remain unchanged. Post-cleanup591/591 strict replay uses
existing objects without a cold rebuild. Cumulative retired products2546 files /
1002499503 bytes; separate earlier successful-snapshot archival savings12865565
bytes. Analysis is about75 MiB and build4.8 MiB; installed tools/game/reference
remain protected. Final proof is exact078-final-canonical-results.json.gz; the first
exact078-canonical-results.json.gz is historical pre-color byte evidence only.
Final source is frozen in core078-final-frozen-source.json; never rerun completed
one-time writers. Original Enemy/Card/Bullet log identities independently reconcile
current compiler-local labels without changing native destination addresses.

## EXACT-077 — 2026-10-08 — Actual Game construction and state

Five complete contributions establish the actual 272-byte GameInf owner and
state queries/bit 6 clearing. Native 0x110 allocation, Task, two Timer and Configuration
construction, original GameInf RTTI/vtable and GameTaskInf literal, two actual
double fields and complete nonthrowing EH are independently checked. Predicates
return full-width int; no bool ABI or Services suffix is imported. These add
362 body /367 comparison bytes; the frozen graph strictly replays 580 units /
106 fresh objects /100,983 disjoint bytes. Origins are 507 pending /9 library /
64 authored /16,948 bytes. Five whole reference associations close, 189 absorbed
across 6,945 terminal reviews. See
[Game evidence](EXACT_GAME_CONTROLLER_RECONSTRUCTION.md).

Owned O2/UBSan checks use actual production Game/Task/Timer/Configuration:
dirty guards, retained high Configuration option bits/natural gaps, 512 flag
states with unrelated high bits, signed restart extremes and whole-state
snapshots. Game destruction is an explicit fixture; full allocation/publication,
loading/update/subsystem retirement/graphics/audio remain open.

Correction: 4992F0+44 is reached through Context slot0 both directly via
40C300 and through 478E80, which itself calls Session context 40BBC0 then 40C300.
Both routes refer to the borrowed primary owner, whose complete type/storage
remain unresolved. The intermediate EnemyController attribution was incorrect;
actual process EnemyController lookup is 478060 through slot8/accessor 412730.
These reader routes do not establish Game or EnemyController storage.
Native 450880 conditionally returns 1 or invokes actual
renderer Controller update 4497D0, not an Animation member or free bool helper.
Do not create a fake/padded owner to close either protocol. Full Player tail /
ANM lifetime, both whole Enemy readers and 41 KB opcode root remain open.

Source is frozen; configuration/registration/cleanup writers are completed
one-time operations. Compressed proofs and repeatable `core077-audit.py` retain
all original type/log/full EH checks. Continue serial nice 15, repo-python,
attested Ghidra, no REA/delegation and protected cleanup. Goal stays active.

All 48 public tests pass (91.308 seconds); target, tracking, reference and
progress gates pass. Protected cleanup retires two probe products /27,645 bytes
and archives two inactive successful snapshots /248,274 bytes saved, with
original-content hash roundtrips. All 212 canonical hashes/native and failed
source evidence remain unchanged; 580/580 existing-object strict replay passes
with no rebuild. Total batch savings 275,919 bytes; cumulative products 2,540 /
1,002,339,503 bytes and separate archival savings 12,865,565 bytes. Private
inventory `core077-probe-cleanup.json`; compressed current proofs
`exact077-canonical-results.json.gz` and `core077-post-cleanup-results.json.gz`.
Historical ref036/ref037 canonical snapshots now use `.json.gz`; read with
gzip.open through repo-python. Never rerun completed one-time writers. Analysis
about 74 MiB /build 4.7 MiB; installed tools/game/reference protected. Enemy original
literal COFF name stays `$SG111396`, independently checked at 570420.

## EXACT-076 — 2026-10-08 — Actual Player storage construction

Seven whole constructors establish actual 300-byte Option, 92-byte Feedback, 32-byte collision
bounds, 20-byte motion parameters, 292-byte Shot and 75,160-byte ShotController storage. The
controller owns a typed 256-shot pool, two real intrusive lists and six Timers.
Full member order, native counts/strides and complete nonthrowing Option/pool
EH are independently checked. These add 1,484 body /1,494 comparison bytes; frozen
575-unit /105-fresh-object replay covers 100,616 disjoint bytes. Origins remain
502 pending /9 library /64 authored /16,948 bytes. Four complete reference associations
close, 184 absorbed across 6,945 terminal reviews. See
[Player storage evidence](EXACT_PLAYER_STORAGE_RECONSTRUCTION.md).

Production O2/UBSan checks use dirty guarded whole records, all 256 Shot defaults
and full pool/list insertion, transfer, removal and sentinel recovery. No
constructor fixture is used. Unreferenced gameplay methods are discarded at
portable link time; this does not accept native EH execution or whole gameplay.
Shared damage-handle/array-loop heads receive no duplicate credit; independent
IntrusiveList constructor emission remains nonexact.

Native Player allocation 4F32B0 requests 1485C /84,060 bytes and its 794-byte root
constructor includes actual ANM /10+12 Options /Feedback /256 Shots. The untouched
four bytes at +14850 have no established original declaration/type. The only
literal byte pattern in .text belongs to an unrelated REL32 CALL at 49612C;
this scan is not a proof against alternate/indirect accesses. Do not invent a
padding word or facade to close the root. Full Player/ANM lifetime/gameplay,
both whole Enemy readers and 41 KB opcode root remain open. Failed noexcept/
std::array probes and original evidence are retained privately.

All 47 public tests pass (87.568 seconds); target, tracking, reference and
generated-progress gates pass.

Configuration/registration/cleanup writers are completed one-time operations;
never rerun. Proofs are gzip from outset. Continue serial nice 15, repo-python,
attested Ghidra and protected periodic cleanup; no REA or delegation.

Protected cleanup retires six completed probe products /126,345 bytes. All
210 canonical hashes and native/failed source evidence remain unchanged;
575/575 post-cleanup strict replay uses existing objects with no rebuild.
Inventory `core076-probe-cleanup.json` and gzip proof are private. Cumulative
retired products are 2,538 files /1,002,311,858 bytes; separate archival savings
remain 12,617,291 bytes. Analysis is about 74 MiB and build 4.6 MiB; installed
tools/game/reference/Ghidra stay protected. Whole proof is compressed from
the outset at `exact076-canonical-results.json.gz`. The original Enemy literal
COFF identity stays `$SG111396`, independently checked at 570420. Goal remains
active; this is a progress checkpoint.

## EXACT-075 — 2026-10-08 — Actual Card construction and time state

Six complete contributions add 725 body /730 comparison bytes: actual Card
construction, wrapping time encoding, full-width validation, active-state
observation, stored-index Context binding and real process lookup. Native C8
allocation, independent CardInf RTTI/vtable/literal identity, five actual
AnimationHandles, Timer/Vector3, aligned doubles and complete nonthrowing EH
establish the owner. Context slot10 now has its real borrowed Card type;
getter/setter physical folding adds no duplicate coverage. See
[Card evidence](EXACT_CARD_RECONSTRUCTION.md).

The frozen graph strictly replays 568 units /104 fresh objects /99,122 disjoint
comparison bytes. Origins are 495 pending /9 library /64 authored /16,948
authored bytes. Three complete reference associations close; all 6,945 reviews
remain terminal, now 180 absorbed. The remaining multi-target initialization,
factory/disposal and independent Region binding associations retain their
nonexact status. Configuration and registration writers are completed one-time
operations; never rerun. Whole proof is compressed from the outset at
`.analysis/exact075-canonical-results.json.gz`; full original/type/EH/alias
support is checked by `core075-audit.py`.

O2/UBSan checks use real production construction and Session/Context, dirty
guards/natural gaps, wide-integer wrap oracles, valid/corrupted checksum words,
whole-state preservation and two-context publication. Card destruction remains
an explicit fixture boundary. Factory/initialization/gameplay/disposal, Player/
game owners, whole readers and the 41 KB opcode root remain open. Original
reference free/raw/service bodies are not imported. DamageRegion binding's
same physical head does not independently close its owner protocol.

Before source changes, two inactive successful replay snapshots were losslessly
archived, saving 861,845 bytes (842 KiB). Original-content hash roundtrips and
562/562 strict existing-object comparisons pass; all 206 protected hashes stay
unchanged. Inventory `core075-storage-cleanup.json` and compressed proof
`core075-storage-canonical-results.json.gz` are private. This one-time writer
is completed; never rerun. Separate cumulative archival savings are now
12,617,291 bytes. Installed tools, original game/reference and native evidence
are protected. Continue serial nice 15, repo-python, attested Ghidra and
protected cleanup; no REA or subagents. Goal stays active.

All 46 public tests pass (83.163 seconds); target, tracking, reference and
generated-progress gates pass. Frozen source replay rebuilt stale objects once;
the original Enemy creation literal's COFF label changed from `$SG111392` to
`$SG111396` and was independently rebound to the unchanged original/source
literal at `570420`. No relocation destination was solved from compared bytes.

Protected batch cleanup then retires four completed Card probe object/receipt
files /60,070 bytes. All 208 canonical object/receipt hashes and private native/
failed source evidence stay unchanged; 568/568 strict post-cleanup comparisons
pass using existing objects. Inventory `core075-probe-cleanup.json` and proof
`core075-post-cleanup-results.json.gz` are private. This one-time writer is
completed; never rerun. This turn's archival plus product retirement frees
921,915 bytes (900 KiB). Cumulative product retirement is 2,532 files /
1,002,185,513 bytes, separate from 12,617,291 bytes of archival savings.
Analysis remains about 74 MiB, build 4.6 MiB and installed tools 4.2 GiB.

Next, continue actual Player/Game owners for whole Enemy readers `49ABC0`
(4,668 comparison bytes) and `4995D0` (5,612). Card process lookup `478EA0`
and active query `4887A0` are now closed dependencies. Native Player constructor
`4F46A0` is 794 bytes and exposes large typed Option/Shot pools; prove complete
allocation/field/child storage before maintaining its owner. The older 15 KiB
Player estimate is not evidence. Original full reader CFG/table audits and
all failed Controller iterator/pre-clear experiments remain authoritative.

## EXACT-074 — 2026-10-08 — Actual Controller and Task construction

Two complete constructors add 380 body /385 comparison bytes: actual
Controller 312/317 and Task 68. Independent EnemyCtrlInf RTTI/vtable identity,
original log literal, complete nonthrowing EH and real Task/Data/PMR/Timer/list/
identifier construction establish the caller protocol. Explicit aggregate flag
zeroing before setting bit1 replaces the prior implicit Task constructor's
53-byte emission. Original declarations/names and broader flag roles remain
unknown. See [Controller construction evidence](EXACT_CONTROLLER_CONSTRUCTION_RECONSTRUCTION.md).

The frozen graph strictly replays 562 units /103 fresh objects /98,392 disjoint
bytes; origins are 489 pending /9 library /64 authored /16,948 bytes. All 6,945
reference reviews remain terminal, 177 absorbed. The Controller constructor
association also includes its unmatched 73-byte factory and remains nonexact;
no partial reference association or authored-origin credit is granted. Creation
tests now use production Controller/Task construction, dirty guarded defaults
and real generation wrap effects. Disposal, allocation, VM/startup, Session
lookup and whole-list-find remain explicit test boundaries. Other loading/
movement tests retain Controller fixtures and link actual Task construction.

Whole find 251 and two separate 219-byte statistics retain missing compiler
iterator pre-initialization. Natural range-for/initialization/default-argument/
named-return variants did not resolve the 10-byte search difference. Unsupported
default declarations and renamed operators were reverted; no dummy constructor,
clear or inert local is introduced. Seven independent SDL compiler fixtures
also emit no helper. Natural new T/new T() factories remain 60/73. Original
sentinel constructor remains 31/40 due two observed tail stores; redundant
assignments are not introduced. Complete source/native/failed evidence is
retained privately. Whole Controller disposal/search, both Enemy readers,
Player/card/game owners, 41 KB opcode root and whole-game link/runtime remain open.

Source is frozen. Configuration/registration writers are completed one-time
operations; never rerun them. Whole proof is compressed from the outset at
`.analysis/exact074-canonical-results.json.gz`; constructor audit/support are
`core074-audit.py`/`core074-support.json`. Keep English/repo-python/attested
Ghidra, no REA/subagents, serial nice 15 and periodic protected cleanup. Goal
stays active; no unchanged cold rebuild for documentation or cleanup.

All 45 public tests pass (79.805 seconds), including real guarded Controller/
Task construction and creation. Target, tracking, reference and progress gates
pass. Protected cleanup retires 20 completed probe object/receipt files /
551,844 bytes (539 KiB), preserving every failed source/header/log/native export.
All 206 current canonical object/receipt hashes are unchanged; post-cleanup
comparison uses existing objects without a cold rebuild. Proof is compressed
from the outset at `.analysis/core074-post-cleanup-results.json.gz`; inventory
is `.analysis/core074-cleanup.json`. This one-time writer is completed; never
rerun it. Cumulative obsolete-product retirement is 2,528 files /1,002,125,443
bytes; separate lossless archival savings stay 11,755,446 bytes. Analysis is
about 74 MiB, build 4.6 MiB and installed tools 4.2 GiB.

## EXACT-073 — 2026-10-08 — Actual process Session and player-table protocol

Twenty complete contributions add 1,167 body /1,177 comparison bytes: real
Session/PlayerTable construction, compiler-owned process initializer, indexed
Context/table/record queries, selected current-record and Controller lookups,
mode/clamp queries, continue updates and bitfield setters. Native construction,
independent double-clock consumers, actual 704-byte BSS and original CRT slot
establish complete storage and startup contributions. Natural alignment gaps
replace explicit reference padding; both complete EH records and real array
construction replay. Shared Context/array helper folding adds no duplicate
coverage. See [Session evidence](EXACT_SESSION_RECONSTRUCTION.md).

The frozen graph strictly replays 560 units /101 fresh objects /98,007 disjoint
bytes. Origins remain 487 pending /9 library /64 authored, with 16,948 authored
bytes unchanged. Eleven whole reference associations close; all 6,945 reviews
remain terminal, 177 absorbed. New O2/UBSan verification uses production Session,
Context and PlayerRecord lifetimes/lookups, dirty guarded construction and natural
gaps, whole-object preservation, wrap/clamp edges and retained flag bits. Existing
Enemy creation tests still have explicit lookup/search fixture boundaries; no
whole creation/runtime integration claim follows.

Source is frozen. Cold replay and one-time configuration/registration writers
have completed; never rerun completed writers or another unchanged cold build.
Private whole replay: `.analysis/exact073-canonical-results.json.gz`. Actual
Player entity, primary game/frame/card owners and Controller search/range
iteration still block whole Enemy readers. Both original reader CFG/table audits
remain authoritative; neither whole reader nor the 41 KB opcode root receives
partial credit. Session clock/statistics, process-wide initialization order and
whole-game link/runtime remain open. Keep English/repo-python/attested Ghidra,
no REA/subagents, serial nice 15 and periodic protected cleanup. Goal stays active.

All 45 public tests pass (77.360 seconds), including the new actual Session test;
target, tracking, reference and generated-progress gates pass. Protected cleanup
retires eight obsolete Session probe object/receipt files /172,587 bytes. Two
inactive successful EXACT-072 snapshots are losslessly archived, saving another
1,608,770 bytes, with decompressed content and both hashes verified. All 202
canonical object/receipt hashes and remaining private evidence are unchanged.
This batch frees 1,781,357 bytes (1.70 MiB); cumulative obsolete-product
retirement is 2,508 files /1,001,573,599 bytes, and separate archival savings total
11,755,446 bytes. Analysis is about 74 MiB, build 4.4 MiB and tools 4.2 GiB.
Private inventory: `.analysis/core073-cleanup.json`; cleanup-only proof is
compressed from the outset at `.analysis/core073-post-cleanup-results.json.gz`.
This cleanup writer is a completed one-time operation; never rerun it. Strict
post-cleanup replay uses existing objects and requires no unchanged cold build.

## Storage maintenance — 2026-10-08

Seven inactive successful replay snapshots from EXACT-061 through EXACT-068
are losslessly archived as `.json.gz`, saving 4,915,722 bytes (4.69 MiB).
Original content/hash roundtrips pass; all 200 current canonical object/receipt
hashes remain unchanged. Every other pre-existing native/failed source and
evidence file is retained. Build contains only the 100 canonical objects and
their receipts; no obsolete products remain there. Current strict comparison
passes all 540 units using existing objects, without another cold rebuild.
All 44 public tests and the public-tree/progress checks pass after archival.

Private inventory: `.analysis/core072-storage-cleanup.json`; compressed current
proof: `.analysis/core072-storage-canonical-results.json.gz`. This one-time
cleanup writer is completed; never rerun it. Cumulative obsolete-product
retirement stays at 2,500 files /1,001,401,012 bytes; separate lossless archival
savings now total 10,146,676 bytes. Analysis is about 75 MiB and build 4.4 MiB.
Installed compiler/SDK/Wine (about 4.2 GiB), reference, game and Ghidra remain
protected. Source and exact coverage are unchanged; the whole core
reconstruction goal and the next reader/Player/Session scope remain active.

## EXACT-072 — 2026-10-08 — Whole Enemy variable destinations and handles

Six complete contributions add 1,820 body /2,183 comparison bytes: actual integer
and floating destinations including full compressed tables, checked Controller
selection, player-0 identifier resolution and genuine Data/16-slot construction.
The former animation-handle declaration is corrected to EnemyHandle and the real
std::array; native pure zero construction and complete nonthrowing EH replay.
Folded scalar construction and full checked-array/throw/EH support add no duplicate
coverage. See EXACT_ENEMY_VARIABLE_RECONSTRUCTION.md.

The frozen graph strictly replays 540 units /100 objects /96,830 disjoint bytes.
Origins are 467 pending /9 library /64 authored, with 16,948 authored bytes
unchanged. Six complete reference associations close; all 6,945 reviews remain
terminal, 166 absorbed. Actual creation tests extend to real variable/handle
bodies and Data lifetimes, signed bits, aliases, repeated player-0 queries,
stale/null fallback, complete writable-slot counts and checked bounds. Session
and whole-list-find remain explicit fixture boundaries; other owner tests now
use actual Data construction. Source is frozen; configuration/registration
writers are one-time operations. Never rerun completed stamps.

Both whole reading functions now have complete normal-flow/table audits: integer
4,668 comparison bytes /112 case heads and float 5,612 bytes /107 case heads.
They retain distinct conversion/null/owner policies, 51/47 direct dependencies
and the original unreferenced integer JMP. Full list-find remains 241/251 due
compiler iterator auto-initialization. Whole readers/search, Player/Session and
Controller/startup, the 41 KB Enemy root and whole-game link/runtime remain open.
No partial read/dispatcher acceptance. Keep English/repo-python/attested Ghidra,
no REA/subagents, serial nice 15 and protected storage cleanup. Goal stays active.


Protected cleanup retires 12 completed probe object/receipt files /379,171 bytes.
Two inactive EXACT-071 successful snapshots are losslessly archived as .json.gz,
saving another 1,559,710 bytes. Original content/hash roundtrips and all 200
current canonical hashes are verified. This batch frees 1,938,881 bytes
(1.85 MiB); cumulative retirement is 2,500 files /1,001,401,012 bytes, with
5,230,954 archival savings recorded separately. Native/failed evidence and all
receipt-verified original private header snapshots are retained. All 44 public
tests pass; post-cleanup comparison uses existing objects without a cold rebuild.
Cleanup/configuration/registration writers are completed; never rerun them.

## EXACT-071 — 2026-10-08 — Whole ECL Runtime/Manager lifetime and async disposal

Ten complete functions add 701 body bytes /706 comparison bytes: actual Runtime
and Manager construction/destruction/scalar cleanup, saved-next async clearing,
typed Runtime/link release and the floating default. Independent SptInf RTTI,
real zero initialization, aggregate flag storage, allocation-free node contract,
PMR ownership and destruction before slot-1 locking establish the protocol.
The complete Manager destructor includes its five natural compiler INT3 bytes;
its 29-byte EH handler and 36-byte zero-state FuncInfo strictly replay. Folded
position/node/default-slot and complete vector/destroy_at support add no duplicate
credit. See EXACT_ECL_RUNTIME_LIFETIME_RECONSTRUCTION.md.

The frozen graph strictly replays 534 units /98 objects /94,647 disjoint bytes.
Origins are 461 pending /9 library /64 authored, with 16,948 authored bytes
unchanged. All 44 public tests pass, including actual lifecycle/reset/default
slots, three-node async disposal, stale sentinel validity, scalar/virtual cleanup,
resource capture/release order and independent cross-thread lock observation.
The argument test now runs real production Runtime/Manager lifetimes; bounded
whole tick/call/Enemy fixtures retain their declared game interfaces. Three
complete reference associations close; all 6,945 reviews remain terminal,
160 absorbed. Whole resource append/getter/include, actual variable/Player/Session
owners, process startup, 41 KB Enemy root and whole-game link/runtime stay open.

Full private include516 retains four constant byte-index lowering differences;
new getter expression probes retain full nonexact evidence. A generated Enemy
literal label changed after header refinement: independently verified original
source/COFF/native string identity binds SG111257 to existing native570420.
The cold tail reuses current receipts and builds only missing objects. Source is
frozen. Configuration/registration writers are completed; NEVER rerun.

Protected cleanup retires 20 completed probe object/receipt files /650,871 bytes.
All 196 canonical hashes remain unchanged. Five inactive successful replay JSON
snapshots are losslessly archived as .json.gz, saving a further 3,671,244 bytes;
original content/hash roundtrips are verified and native/failed evidence remains
intact. This batch frees 4,322,115 bytes (4.12 MiB). Cumulative obsolete-product
retirement is 2,488 files /1,001,021,841 bytes; archival savings are recorded
separately. build is 4.2 MiB, analysis about 79 MiB, installed tools 4.2 GiB.
Cleanup/archival writers are completed; NEVER rerun. Strict existing-object
replay verifies cleanup without another unchanged cold build. Keep English,
repo-python, attested Ghidra, no REA/subagents, serial nice 15 and periodic cleanup.
The full reconstruction goal remains active.

## EXACT-070 — 2026-10-08 — Whole ECL argument and tagged stack protocol

Fifteen whole functions add 2,886 bytes: actual current instruction lookup,
eleven separate integer/float consuming/nonconsuming/supplied-value/destination
members and generic push/pop/peek. Natural returning if/else branches and direct
virtual expressions close the former nine-byte discrepancy; complete native
unreachable jumps remain compared. Independent constant identity rejects the
old private negative-eight multiplier: the original uses positive 8.0f.
Direct const payload reading reproduces the whole native float return without
extra SSE rounding spill. Three complete library supports add no duplicate
coverage. All 524 units / 97 frozen-source cold objects / 93,941 disjoint bytes
strictly replay; origins are 451 pending / 9 library / 64 authored, with
16,948 authored bytes unchanged. See EXACT_ECL_ARGUMENT_STACK_RECONSTRUCTION.md.

Owned O2/UBSan checks run all fifteen real bodies and cover sixteen mask slots,
literal bits, real local/destination/virtual dispatch, -1/-100/fraction/-0,
consumption/nonmutation, arbitrary 0..32-byte and tagged 8-byte copies, i/f
conversion, signed tags, saved frames, allocation failure and PMR release.
Existing whole tick/invocation tests now use production push/pop. All 43 public
tests pass. Eighteen whole reference associations close; all 6,945 reviews remain
terminal, 157 absorbed. Original Runtime/Manager construction, complete resource
instruction54/append876/include516, production variable owners, whole 41 KB Enemy
root and whole-game link/runtime remain pending. The resource getter still has
two pointer-constant lowering differences. No global compiler profile or fake
compiler headers are introduced. One-time core070 configuration/registration
writers are completed; NEVER rerun. Source is frozen and canonical audit passes.

Protected cleanup retires 28 completed probe object/receipt files / 1,096,445 bytes.
All 194 current canonical hashes remain unchanged. Cumulative retirement is
2,468 files / 1,000,370,970 bytes. build is 4.2 MiB, analysis 79 MiB, installed tools 4.2 GiB.
Native exports, failed probes/diagnostics, source and tools remain intact.
One-time core070-cleanup writer is completed; NEVER rerun. Existing-object
strict replay verifies cleanup without another unchanged cold rebuild.
Keep English/repo-python/attested Ghidra/no REA/no subagents/serial nice 15,
authorized main push and periodic protected cleanup. The full goal stays active.

## EXACT-069 — 2026-10-08 — Whole ECL file loading

The whole 556-byte derived ECL loading member and three lifetime contributions
add 682 bytes. Actual Context/EnemyController filename registration precedes
recursive include handling; the real process PMR pair-list shares writable
buffers across players. Reference-return emplace_back endpoints, native original
EclResourceInf RTTI, 572-byte owner and complete two-state EH establish the
protocol. Inline defaulted cleanup naturally reproduces the complete 20-byte
derived destructor. Default base load folds with the existing 15-byte include
callback without extra coverage. All 509 units / 95 cold objects / 91,055
disjoint bytes strictly replay; origins remain 436 pending / 9 library /
64 authored, with 16,948 authored bytes unchanged. Complete 118-byte native
EH support replays without extra credit. See EXACT_ECL_FILE_LOADING_RECONSTRUCTION.md.

Owned O2/UBSan checks exercise actual virtual loading, duplicate -1, cycle
suppression, cross-player cache reuse, case-sensitive names, append failure and
both temporary allocation/cleanup paths. Controller startup, resource I/O,
whole append and derived include remain explicit test boundaries. The complete
556-byte load and derived/base destructor reference associations close; all
6,945 reviews remain terminal, 139 absorbed-exact. The constructor association
still includes the unclosed scalar factory. Complete append876, getter54,
include516, Session-based binding54, process startup/teardown, candidate STL
child forwarding emission, 41 KB Enemy root and whole-game link/runtime remain
pending. Source is frozen; configuration, callee refinement and registration
writers are completed one-time operations. Never rerun their writers. Keep
English/repo-python/Ghidra/no REA/no subagents/serial low-priority work and cleanup.

All 42 public tests and target/tracking/progress gates pass. Cleanup retires
14 superseded probe object/receipt files / 995,805 bytes. All 190 current
canonical object/receipt hashes are unchanged and 509 strict existing-object
comparisons pass afterward; no unchanged cold rebuild is needed. Cumulative
retirement: 2,440 files / 999,274,525 bytes. build is 4.0 MiB and .analysis
is 78 MiB. Native exports, failed source/diagnostics and installed tools remain
intact. The one-time core069-cleanup writer is stamped; never rerun it.

## EXACT-068 — 2026-10-08 — Whole ECL base resource lifetime

Five whole contributions add 252 bytes: base resource construction/destruction,
compiler scalar deleting destructor, default include callback and implicit PMR
ScriptStack cleanup. Actual allocator capture, borrowed file buffers, fixed
arrays, original global SptResourceInf RTTI and independently bound native
cleanup establish the protocol. Existing 42-byte ScriptStack construction gains
its allocation-free noexcept contract without new credit. All 505 units / 94
cold objects / 90,373 disjoint bytes strictly replay; origins remain 432 pending /
9 library / 64 authored, with 16,948 authored bytes unchanged. Owned O2/UBSan
resource capture/release/virtual cleanup checks use the actual maintained bodies;
ECL call/tick and Enemy creation tests replace duplicate base fixtures. See
EXACT_ECL_RESOURCE_LIFETIME_RECONSTRUCTION.md.

The full 876-byte append body remains nonexact at 878 bytes; byte-pointer offset
lowering and receiver register allocation differ. The full 54-byte instruction
getter retains two structural byte differences. Derived loading, first callback,
global production ownership, the 41 KB Enemy root and whole-game link/runtime
remain pending. Reference constructor/destructor/append reviews retain their
terminal nonexact state; all 6,945 reviews remain terminal, 137 absorbed-exact.
Fresh successful objects complete the staged cold graph without duplicate
compilation. One-time core068 configuration/registration writers are completed;
never rerun them. Canonical audit and failed native/source evidence remain private.
Keep English/repo-python/Ghidra/no REA/no subagents/serial reduced-priority work.

All 41 public tests and target/tracking/progress checks pass. Cleanup retires
36 superseded experiment objects/receipts / 1,598,909 bytes. All 188 current
canonical object/receipt hashes remain unchanged and 505 strict existing-object
comparisons pass afterward; no additional cold build is needed. Cumulative
retirement: 2,426 files / 998,278,720 bytes. build is 3.8 MiB and .analysis
is 77 MiB. Native exports, failed source/diagnostics and installed tools remain
intact. One-time core068-cleanup writer is stamped; never rerun it.

## Storage maintenance — 2026-10-08

Retired 301 downloaded MSVC installer cache files / 926,379,294 bytes
(883.46 MiB) after checking the installed tools. All 207 protected hashes,
including the 186 canonical objects/receipts, critical installed tools and the
pinned manifest, remain unchanged. Tool attestation and all 500 strict canonical
comparisons pass afterward using existing objects; no cold rebuild was needed.
Cumulative retirement, including this cache: 2,390 files / 996,679,811 bytes.
Private core067-storage-plan/cleanup JSON records paths, sizes and hashes;
core067-storage-canonical-results.json records the complete post-cleanup replay.
The cache cleanup stamp has completed; never rerun it. Installed tools, native
exports, reference sources, failed probes and supplied files remain intact.
No reconstruction credit or source graph changes result from storage maintenance.

## EXACT-066 — 2026-10-08 — Whole Enemy creation and script selection

Nineteen whole functions add 1,279 bytes: actual controller creation, complete
Enemy initialization, inherited ECL reset, PMR stack reserve/reset, generation,
binary subroutine lookup/selection and non-consuming value forwarding/hidden
Identifier32 return. Native callees distinguish reserve from resize and supplied
values from consuming helpers. One complete folded script-loader getter alias
replays without duplicate coverage. Frozen-source cold batch covers all 93
objects once (90 existing plus three new); all 500 units / 90,121 disjoint bytes
strictly replay. Origins: 427 pending / 9 library / 64 authored, 16,948 authored
bytes unchanged. Eight reference associations close; unrelated/shared-address
and partially covered wrappers retain their reviewed state. Owned O2/UBSan
creation/reset/list/generation/lookup checks run actual maintained bodies with
explicit unresolved boundaries. All 40 local public tests and tracking/progress
checks pass. See EXACT_ENEMY_CREATION_RECONSTRUCTION.md.

Whole 653-byte opcode spawning is still nonexact (14 load/reservation-order
bytes); clean scalar factory, runtime virtual materialization, list prepend
emission and 780-byte spawn application remain pending. No fake Session or
compiler header is introduced. Whole 41 KB 48C010 and whole-game link/runtime
remain open. Native/failed source evidence is retained privately.
User explicitly requires no REA skills or MCP; use the existing attested Ghidra
wrapper directly. English/repo-python/no subagents/serial low-priority heavy
work/authorized main push and periodic protected cleanup persist.

Cleanup retires 43 superseded files / 1,153,194 bytes. All 186 current canonical
object/receipt hashes are unchanged and 500 strict replays pass after cleanup.
Cumulative retirement: 2,089 files / 70,300,517 bytes. Native exports, failed
probe sources/diagnostics, supplied files and locked tools remain intact.
One-time core066 configuration/registration/cleanup writers have completed
stamps; NEVER RERUN. core066-audit.py now reads canonical objects; no unchanged
cold build is needed solely for documentation or cleanup.

## EXACT-065 — 2026-10-08 — Whole Enemy animation dispatcher and parameters

Twenty whole functions add 2,218 instruction bytes and 77 compiler alignment/
table bytes. The complete 00496B90 animation sub-dispatcher contributes 967
instruction bytes and all nineteen pointers over 1,044 comparison bytes. Actual
Enemy/State/ANM/Color3/PMR and interpolation owners replace reference adapters.
Direct list initialization preserves ordered Vector3 reads without an extra
reference spill. Real packed color/channel representations, mixed flag modes
and complete signed layer selection close the parameter protocol. Eight whole
folded/template/container support contributions independently replay without
extra credit. Frozen-source cold replay: 481 units / 90 objects / 88,842 disjoint
bytes. New origins stay pending: 408 pending / 9 library / 64 authored, with
16,948 authored bytes unchanged. Two existing reference associations close.
All 39 public tests pass, including owned whole dispatch/forwarding/parameter
checks under O2/UBSan. See EXACT_ENEMY_ANIMATION_RECONSTRUCTION.md.

The whole 0048C010 root remains pending; do not turn this direct dependency into
partial opcode or whole-root credit. Next integrate these real interfaces while
closing laser virtual ownership, callback tables and remaining whole direct
bodies. Copying factory/control and queue reference emission still differ.
Native full CFG/tables and the five real temporary EH owners remain reusable.
English/repo-python/Ghidra/serial low-priority work/no subagents/authorized main
push persist. Configuration/registration writers are one-time operations; never
rerun completed stamps. Private core065-audit.py replays current canonical
objects; no additional cold build is needed for documentation or cleanup.

Cleanup retires 25 superseded files / 728,450 bytes. All 180 current canonical
object/receipt hashes remain unchanged and 481 strict replays pass afterward.
Cumulative retirement: 2,046 files / 69,147,323 bytes. Native exports, failed
probe sources/diagnostics and locked tools are retained. See private
core065-cleanup.json. build is 3.5 MiB; .analysis is 72 MiB.

## EXACT-064 — 2026-10-08 — Actual shot allocation and shared control

Eight complete bodies add1,131 instruction+10compiler alignment bytes. Full
frozen-source cold replay:461units/87objects/86547disjointbytes. Native RTTI
establishes global EtamaArgInf and DebugAllocator; th20::ShotMetadata remains
an alias of the same actual76-byte PMR command owner. Real allocation/release
lock process slot1 and use scalar new/unsized delete. Removing the unsupported
private converting-ctor noexcept reproduces whole control release123+5padding.
Generated complete RTTI/vtable/EH and direct support independently replay without
coverage credit. Five std-associated functions are independently library-owned;
source origins388pending/9library/64authored16948. Actual copying factory227/236,
copy-control177/192 and wholequeue396/305 remain nonexact due intrinsic forwarding
and result-reference materialization. Do not replace headers or add inert locals.
Whole48C010 dispatcher/tables/five temporary EH states remains the next core root.
Owned locking/recursion/allocator-selected isolated copy/move/strong-weak lifetimes
pass. Original global definition/startup and whole-game link/runtime stay open.
See EXACT_SHOT_ALLOCATION_RECONSTRUCTION.md. Older entries are historical.

Cleanup retires18superseded files /978879bytes; all174 canonical object/receipt
hashes are unchanged and461strict replays pass afterward. Cumulative retirement:
2021files /68418873bytes. Native exports, probes and locked tools remain intact.
All38public semantic/control-plane tests pass. Source is frozen; no additional
cold build is needed for these documentation/cleanup updates.

core064-configure.py/register.py are one-time writers with completed stamps;
NEVER RERUN. Private core064-audit.py and exact064-replay.log retain full proof.
Keep English/repo-python/serial MSVC-Ghidra/no subagents/authorized main push.
Reduce scheduling priority and memory use, as the user now explicitly requires.
Periodic protected cleanup follows the stable batch; see RE_WORKFLOW.md.

## EXACT-063 — 2026-10-08 — Actual Enemy dispatcher temporary lifetimes

Eleven whole functions add1,384 instruction and five compiler alignment bytes.
The frozen-source graph strictly replays453units/86coldobjects/85406disjointbytes.
Actual ShotMetadata0x4C owns PMR BulletCommand44 values, constructs two commands,
and retains implicit trailing padding. Four laser parameter values0x54/74/5C/50
own their command vectors and now supply all five native dispatcher cleanup
states. See EXACT_ENEMY_TEMPORARY_RECONSTRUCTION.md. New origins remain pending:
385pending/4library/64authored16948. One reference constructor association closes;
header/implicit laser constructors receive no fabricated reference-body credit.

IMPORTANT: independent full vector48BA60/157 proves ShotMetadata48BB00/241 is
move assignment. The initial private copy hypothesis has the same outer241
bytes but its vector child is121; reject that relocation/ownership inference.
Native handler5679A0/29 plus full FuncInfo5A91B8/36 flags5 establishes the metadata
nonthrowing constructor, including allocation failure termination. Five complete
PMR library contributions plus both EH records independently replay without
extra coverage. The whole Enemy dispatcher stays flags1, not nonthrowing.
Type3 +30 is float. Type2 +28 is a four-byte flag aggregate with unknown original
aggregate/union spelling; scalar initialization differs. Its curve pointer is
not destroyed here; the curve owner remains open. Existing Enemy fixtures now
use the real metadata;37public semantic/control-plane tests pass.

Queue498B80/396 (COW) and498D10/305 (ensure-only) remain private/nonexact.
std::pair forwarding explains467CC0/55, but allocation/temporary-reference emission
differs in whole accessors. Do not promote allocator/std::move hypotheses or
child coverage into whole queue/dispatcher credit. Next close actual allocation/
shared-control/aggregate-return protocol and integrate the complete48C010 root,
all primary/nested tables and real EH states. No leaf-only detour is needed.
Private core063-resume.md records probe/replay/cleanup state. One-time writers
core063-configure.py/register.py are completed; never rerun them.
Periodic cleanup retires8 superseded files /321,504bytes,
protecting all172 current object/receipt hashes and replaying453 units. Cumulative
retirement:2003files /67,439,994bytes. See private
core063-cleanup.json. Continue after stable batches; preserve native exports,
probe sources, active inputs and locked tools.
English/repo-python/serial MSVC-Ghidra/no subagents/authorized main push persist.

## CORE-062 — 2026-10-07 — Complete Enemy dispatcher graph and nested tables

The whole48C010/41967 investigation now follows all174 primary case paths,
including four rank tables at496978/988/998/9B8 (4/4/8/8 pointers). Native indexed
jumps, bounds, Ghidra xrefs and complete destinations independently corroborate
these96 additional bytes. All8856 case-path heads plus40 prologue/dispatch heads
cover the entire8896-instruction listing. No unresolved indirect jumps, external
successors or unselected table entries remain. Shared tails stay explicit;
no partial opcode/function exact credit is given. See CORE_ENEMY_DISPATCH_LAYOUT.md.

The raw contiguous body/table block is43464bytes, including one NOP at4963FF;
eight trailing INT3 bytes before4969E0 still need cold COFF ownership attribution.
Do not compare only the prior two tables. Native42-byte EH observation at5694AC
references FuncInfo5AA704, flags1, five unwind states and separate11-byte thunks.
Stores locate actual temporary lifetimes in600 and702/703/713/711. Actual shot/
laser owners, synchronous EH and full compiler contribution remain open; do not
add a nonthrowing root contract or trivial byte transports. Native cleanup targets
are47C450/47C4B0/47C490/48B890/48B8B0. Ghidra lacks handler membership; locked PE
read-only decoding supplies this separate evidence without database mutation.

All1264 direct sites /236 dependencies are inventoried;55 canonical entries
cover590 sites (navigation only, excluding aliases/library support). Independent
parameter-wrapper exports show nonvirtual argument destinations distinct from
virtual variable-resolution slots. Four natural rank-switch statement drafts
remain private and uncompiled for integration into the whole root. No new exact
unit or accepted source:442units/84objects/84017bytes, authored64/16948 unchanged.
The generic audit now exports optional normal reachable case paths and checks
explicit nested bindings against their actual JMP operands. Four new synthetic
cases cover alias/shared tails, disconnected/unselected code and invalid/unknown
branch/table handling. All36 public tests and private target/tracking/progress
checks pass; production source is unchanged, so no cold rebuild is required.

Next reconstruct the actual shot metadata and four laser temporary owners and
the complete natural dispatcher; retain all primary/nested tables/default/exits,
parameter order and real cleanup. See private core062-resume.md. Configuration/
registration writers from older checkpoints remain one-time completed operations.
Periodic cleanup removes 5 superseded files / 2,638,115 bytes: completed
environment smoke products/copied SDK DLL and the initial case catalog. The
saved smoke proof, probe source, master SDK DLL, full native evidence and all168
canonical object/receipt hashes remain intact. Cumulative cleanup: 1,995
files / 67,118,490 bytes. See private core062-cleanup.json. Cleanup after
stable batches remains explicitly requested.
English/repo-python/serial MSVC-Ghidra/no subagents/authorized main push persist.

## EXACT-061 — 2026-10-07 — Whole Enemy movement and graphics owners

Fifteen complete functions add 4,205 instruction bytes and ten alignment bytes.
The full frozen-source graph strictly replays: 442 units / 84 cold objects /
84,017 disjoint comparison bytes. The new bodies include Enemy movement update
4A7710/1675, Graphics construction 4D8990/941, viewport construction 471790/319,
Configuration construction 4B9C10/473, AnimationFile construction 448A30/186 and
Context construction 423320/133. New origins stay pending: 374 pending, four
library, 64 authored / 16,948 bytes. See EXACT_ENEMY_UPDATE_RECONSTRUCTION.md.

Actual Graphics0xDE8 owns six ViewportState0x16C values, native SDK records,
Configuration0xB0 and two Workers. Independent startup establishes global base
5C4D40; the movement offset belongs to viewport zero's final vector. Context
has twelve separate pointer slots; EnemyController0x134 includes actual PMR,
TaskInfo, EnemyData, timers, list, Identifier32 and file pointers. Its lifetime
and file-selection implementations remain undefined. AnimationFile0x70 owns
real PMR strings and an atomic value, with a separately audited constructor chain.

Whole movement preserves parent following, interpolation order, frozen viewport
offsets, composition, direction-transition/file-before-retirement order and
strict departure flags. Native float absolute widens to double CRT fabs; the
comparison-based geometry absolute is a different operation. Fourteen complete
support aliases/library/EH contributions replay without duplicate credit. Actual
flags5 EH reproduces Graphics/Configuration nonthrowing contracts; no existing
child contracts were weakened. Owned semantic fixtures explicitly delimit open
production dependencies; no whole-game linkage/runtime claim follows.

Four independently reconstructed reference bodies now have exact associations;
the combined graphics-startup and file-creation wrappers remain nonexact despite
their accepted constructor dependencies. Native Context size is 133, correcting
the earlier 165-byte note. Viewport +11C/+124 are real zeroed Vector2 values,
not uninitialized lanes. All 32 public semantic/control-plane tests and private
target/tracking/progress/full Ghidra gates pass.

Cleanup removes 33 superseded files / 7,810,424 bytes: duplicate probe object/
receipt pairs and old aggregate replay JSON completely superseded by current
results at identical target addresses and full extents. All 168 canonical
object/receipt hashes remain unchanged. Cumulative cleanup: 1,990 files /
64,480,375 bytes, approximately 61.5 MiB. Native exports, logs, probe sources,
registration stamps, references, game files, Ghidra and tools are retained.
See private core061-cleanup.json and exact061-resume.md. Configuration and
registration were one-time operations; NEVER RERUN.

Next priority is the complete Enemy dispatcher 48C010 / 41,967 bytes and all
174 pointer-table entries / 704 index bytes. Actual production Controller,
handle resolution/retirement, file spawn and global lifetime remain dependencies
to close coherently. Do not award individual cases or shorten whole bodies.
English, repo-python, serial MSVC/Ghidra, no subagents, gpt-6.1-sol: commits and
authorized main push persist. Older entries below are historical.

## EXACT-060 — 2026-10-07 — ANM lifetime, reset and inherited extents

Ten complete Base/Animation construction/destruction/reset/resource/scales
functions add 2,855 instruction bytes and fifteen alignment bytes. All427 units /
79 cold objects /79,802 disjoint bytes strictly replay after source freeze and
shared AnimationHandle/DiagnosticAllocator declaration changes. New origins
remain pending; authored64/16948 is unchanged. See
EXACT_ANIMATION_LIFETIME_RECONSTRUCTION.md.

Actual owners are Base0x4C0, Animation0x5E4 and pooled storage0x600. Real typed
Timer/vector/Angle/interpolation/matrix/variable/link values, native array ctor/
dtor consumers and complete flags5 EH establish construction and nontrivial
Animation destruction. The reset is partial: owned resources/handle/Base timer,
other matrices and interpolation samples/timers/modes remain retained. Parent
scales recurse through+558 unless local flag bit12 suppresses inheritance.
Resource release preserves the native nonzero+550 infinite handle-clear path.
The identity constant has independent64-byte copy consumers; its production data
initialization remains open. Callback destruction is a declared real allocator
dependency, not an accepted production body. Shared handle/node physical aliases
and complete EH support replay independently without duplicate coverage.

Natural PooledAnimation construction with the actual Animation destructor emits
115/native59 under this owner recipe; the complete mismatch remains pending.
Do not restore an implicitly trivial Animation, change child exception contracts,
shorten contributions or adopt reference packed/raw transports. Eight reference
body reviews now link their independent exact reconstructions; pooled/free
forwarding boundaries remain explicitly nonexact. All31 public semantic/control
plane tests and private target/tracking/progress/full Ghidra gates pass.

The whole Enemy movement update4A7710/1675 and dispatcher48C010/41967 remain
priority. Next close actual Controller/Context/file binding, handle resolution/
retirement and viewport/global ownership together. Controller constructor4A2E80
is exported completely:312 bytes, flags5 EH, CallbackOwner base, EnemyData,
PMR vector, timers, eight file pointers, script loader, sentinel/list and a real
Identifier32 at+128 (not an invented raw padding word). No source for that next
owner is accepted yet. Existing Enemy base/destructor/global dependencies remain
open; no partial opcode credit or whole-game linkage claim is made.

Cleanup totals now1,957 retired files /56,669,951 bytes, approximately54 MiB.
The latest two removed duplicate probe object/receipt files total50,431 bytes;
all158 current canonical object/receipt hashes are unchanged. Raw native evidence,
probe source, reference/game files and Ghidra/toolchains remain intact. See
private core060-cleanup.json and exact060-resume.md. Current audit uses canonical
objects only. Configuration/registration were one-time operations; NEVER RERUN.
English, repo-python, serial MSVC/Ghidra, no subagents, gpt-6.1-sol: commits and
authorized main push persist. Older entries below are historical.

## EXACT-059 — 2026-10-07 — Whole Enemy movement composition and construction

Nine complete functions add 1,285 instruction bytes and ten alignment bytes:
movement composition/bounds844, Motion Y access17/26, normalized angle78,
speed26, three mode selections26/29/29 and Enemy constructor210. All 417 units /
78 cold objects / 76,932 disjoint bytes strictly replay. New origins remain
pending; authored64/16948 is unchanged. Shared X getter/setter physical heads
are independently exact aliases with no duplicate credit. See
EXACT_ENEMY_MOVEMENT_RECONSTRUCTION.md.

Complete independent native handlers567600/567750 and FuncInfo5A91B8 flags5
establish explicit nonthrowing contracts. Natural compiler metadata/handlers
and complete 83/215-byte contributions reproduce all native bytes, closing the
previous Enemy constructor168/native210 gap. Existing child contracts stay
natural; base/list/function dependencies and destructor/resolvers remain open.
Cold supporting EH and aliases independently replay without additional coverage.
Owned C++20/O2/UBSan composition tests pass for multiple records, both bounds,
redistribution, timer/nonfirst retention, frozen state, NaN, modes/flag retention,
signed zero and normalized angle. Full public/target/tracking/progress gates pass.

Whole Enemy dispatcher48C010/41967 remains the priority; 49 movement opcode
indices are a coherent group. No partial cases receive credit. Native double
-999999.0, ordered typed arguments, mirrored normalization and real interpolation/
parent/controller interfaces must be preserved. Whole movement update4A7710/1675
is completely reviewed and remains pending on actual ANM/context/global owners.
4A8260/1258 plus20table is the animation update, not the movement update.

The requested obsolete artifact cleanup remains complete: 1,944 files /
56,330,189 bytes removed while protected canonical objects/receipts, native
evidence, reference/source and game files stayed intact. No blanket .analysis
deletion. Read .analysis/exact059-resume.md for this checkpoint.
After cold acceptance, another 11 superseded probe/cache files /289,331 bytes
were removed; all 156 canonical object/receipt files retained identical hashes.
Private core059-audit.py now replays with --canonical, since duplicate private
probe objects are retired while their source and native evidence remain intact.
Configuration/registration writers are stamped NEVER RERUN. English, repo-python, serial
MSVC/Ghidra, no subagents, gpt-6.1-sol: commits and authorized main push persist.
Older entries below are historical.

## EXACT-058 — 2026-10-07 — Enemy state lifetime and argument protocol

Eleven complete functions add 1,581 bytes on actual EnemyState752/Enemy0x428
owners: State construction765, destruction65, initialization416, three record
constructors, the complete virtual dispatcher wrapper25 and four argument
forwarders36 each. All 408 units / 76 cold objects / 75,637 disjoint bytes strictly
replay. New origins remain pending; authored64/16948 is unchanged. See
EXACT_ENEMY_STATE_RECONSTRUCTION.md. The whole Enemy dispatcher48C010/41967
remains pending and is the next priority; no cases receive separate credit.

Owned C++20/O2/UBSan checks validate retained animation and queued ownership,
movement rebuild, phase clear without capacity release, partial health/timer/
flags reset and complete PMR allocation release. Whole-game linkage, dependency
implementations and exception behavior remain open. Enclosing Enemy constructor
probe168/native210 misses EH; rejected rather than changing child contracts.

Retired artifacts cleaned before reconstruction:1,944 files /56,330,189 bytes.
Previous74 canonical objects/receipts retained identical hashes and397 complete
comparisons passed without rebuild. Native evidence, review records and current
Enemy work remain intact; cleanup detail is private core058-cleanup.json.

Read .analysis/exact058-resume.md for the current checkpoint and open hypotheses.
Do not rerun configuration/registration writers. English, repo-python, serial
MSVC/Ghidra, no subagents, gpt-6.1-sol: commits and authorized main push persist.
Older entries below are historical.

## EXACT-057 — 2026-10-07 — Whole ECL runtime dispatcher exact

The complete root53B5C0 passes canonical all-byte replay:11,110instructionbytes,
two native alignment bytes and the entire392-byte/98-entry jump table,11,504bytes
total. All401relocations have independent anchors, including the table pointer
and98entries from real COFFlocal symbol offsets. The accepted maintained body is
src/EclRuntimeTick.cpp on shared EclRuntime/ScriptStack owners. Meaningful named
constfloat direction and length values preserve native argument order and lifetime;
no source shaping or ABI substitutions. See EXACT_ECL_TICK_RECONSTRUCTION.md.

All397units/74coldobjects/74056disjointbytes cold replay after owner declarations
changed. Source/mapped397, pendingorigins329, library4, authored64/16948. Authored
coverage excludes table/alignment and GameRandom::radians4297D0/45's unresolved
utility origin. The native shared random5BA4A8 has independent startup401120/
constructor422C50 evidence; source declares its owner without inventing startup.

Owned C++20/O2/UBSan whole-dispatch tests use maintained owners, actual math and
interpolation, with explicitly bounded constructor/resolver/stack/async fixtures.
They cover rank/time/ended state, signed arithmetic and tagged consumption, NaN
comparisons, logical/bit operations, post-decrement, ordered polar reads, relative
branches, delegated0/-1/1status branches, async state and interpolation's saved
instruction/frame tail. Invocation remains independently tested by EXACT056.
Host -fno-strict-aliasing models native raw-word access; unsigned size comparisons
retain native conversions. Production dependency/lifetime/flags bodies and full
game linkage/runtime remain open. All30public tests and private target/tracking/
progress/full Ghidra gates pass.

One new rejected whole probe gives extra inner scope to both polar samples:
body11111,whole11504,only6593/9900structuralbytes. The accepted same-case lifetime
probe matches all9900structuralbytes and then every byte under canonical replay.
Never promote earlier rejected or merely equal-size probes, nor solved fields.
Whole EnemyState48C010/41967 is the next priority; defer unrelated leaves.

EXACT057 configuration/registration writers and56/54/older writers are stamped
NEVER RERUN. Source/probes froze before complete replay. Read private
.analysis/exact057-resume.md for exact handles/checkpoint, independent audit and
raw evidence locations. Active native goal, English, repo-python, serial MSVC/
Ghidra, no subagents, gpt-6.1-sol: commits and authorized main push persist.
Older entries below are historical.

## EXACT-056 — 2026-10-07 — Complete ECL invocation and return frames

The whole invocation at 0053F3B0 / 923 bytes passes all-byte canonical replay
with 27 independently established relocations. EclRuntimeCall.cpp uses the
maintained Runtime72/Manager112/Loader564 model and canonical ScriptStack24.
The actual five-byte diagnostic hook is empty; its unresolved ICF/library
origin receives no authored credit. Original Japanese format data is independently
verified as 28 CP932 bytes including NUL. See EXACT_ECL_CALL_RECONSTRUCTION.md.

All 395 units / 72 cold objects / 62,507 disjoint bytes cold replay after shared
ScriptStack declarations changed. Mapped/source 395; pending origins 328;
library 4; authored 63 / 5,838. Original target and full Ghidra remain immutable.
Owned C++20/UBSan frame tests cover fresh/nested targets, ordered typed transfers,
numeric conversion, post-consumption pointer, skipped name/arguments, saved
caller fields, guard words, success restore and failure retention. Unaccepted
constructor, generic stack, resolver and activation bodies are labeled fixtures.
Host tests model MSVC raw-word aliasing with -fno-strict-aliasing.
All29public tests pass; target/tracking/progress and full Ghidra attestation pass.

New native evidence corrects three earlier hypotheses: Manager defaults are
concrete, the invocation's final argument is name_skip, and 40C6B0 does not log.
Activation first sets the loader at41DFB0; sorted lookup is540340. On failure,
the caller is invalidated while current_runtime remains switched to the target.
Runtime/lifetime/flags construction and these dependency implementations remain
open; the declaration model is not a whole-game build.

Whole ECL tick remains pending. Its best private whole-size probe is
9875/9900 structurally matching non-relocation bytes, with25case81 differences;
1604relocationbytes and the full table remain unproven. Native reads angle2 then
length3. Aggregate and structured-binding snapshot probes preserve whole size
but broadly change local slots and were rejected. Do not accept case fragments,
the wrong-order nested expression or exact-size diagnostics. Continue with this
core and then the complete EnemyState root48C010/41967; defer unrelated leaves.

Private exact056-defs/results/replay logs and core056 exports are ignored.
EXACT056 configuration/registration writers and54/older writers are stamped;
NEVER RERUN. Source/probes froze before replay; do not rebuild unchanged units
merely for documentation edits. Active goal, English, repo-python, serial MSVC,
no subagents, gpt-6.1-sol: commits and authorized public main pushes persist.
Read .analysis/core056-resume.md for exact handles/checkpoint on resume.

## CORE-055 — 2026-10-07 — Whole ECL and Enemy dispatcher investigation

The user's current priority is complete core dispatchers; defer unrelated leaves.
No EXACT055 source or exact unit is accepted. EXACT054 remains 393 units /
70 cold objects / 61,579 disjoint comparison bytes, with authored 62 / 4,915.
Public src/probes have not changed since that complete cold replay.
See CORE_ECL_DISPATCH_RECONSTRUCTION.md for evidence and reproduction commands.

ECL tick 0053B5C0 is completely audited: 11,110 body bytes, 2,525 instructions,
98 table pointers / 76 distinct case heads, 288 direct calls / 52 dependencies.
Retain its two alignment bytes and entire 392-byte table, totaling 11,504 bytes.
The private whole C++ member compiles with actual Runtime72 / Manager112 /
Stack24 / ScriptInterpolation56 / Loader564 assertions. Argument order, shared
stack expressions, scoped return restoration and the delegated status protocol
have been reconciled progressively. Complete source acceptance, native local
placement/temporary lifetime, relocation replay and dependency/startup ownership
remain pending. Exact-size or case-shape diagnostics cannot promote this root.

EnemyState execute 0048C010 is completely audited: 41,967 body bytes / 8,896
instructions, 174 primary table entries plus 704 compressed opcode indices,
1,264 direct calls / 236 dependencies. Ghidra's inferred function contains only
54 heads. New read-only disassemble_range exports all 8,896 existing listing
heads without editing database ownership. ECL still has 80 undefined listing
heads; the complete PE audit explicitly retains them. Enemy wrapper4969E0/25
adjusts the receiver by88; the large body belongs to EnemyState, not Enemy.

New audit-dispatcher.py checks complete PE decoding, independently supplied
tables, compressed indices and Ghidra/PE agreement while reporting missing heads
and outside branches. It grants no source/exact credit and writes raw reports
only under .analysis. Three synthetic rejection/coverage tests pass, and all28
public tests pass locally. Optional decoder tests skip when the pinned package
is absent from a public checkout. Real audits and both range exports pass;
target/tracking/progress gates pass. Preserve the locked target and full database.

Private work is .analysis/exact055-ecl-probe.hpp/.cpp and complete compile/case
diagnostics; no raw source/export/object is public. Read the current private
exact055-resume.md before continuing. NEVER RERUN stamped EXACT054 or earlier
configure/registration writers. All prior authorizations and rules persist:
active native goal, English, repo-python, serial compiler, no subagents,
gpt-6.1-sol: commits and authorized public main push.

## EXACT-054 — 2026-10-07 — Archive codecs and allocation protocol

Sixteen complete bodies add 2,676 instruction/comparison bytes. All 393 units /
70 cold objects / 61,579 disjoint complete comparison bytes strictly replay.
Mapped/source 393; pending origins 327; library 4; authored 62 / 4,915 bytes.
See EXACT_ARCHIVE_CODEC_RECONSTRUCTION.md for the bodies and deferred owners.

Signed block decryption and the persistent LZSS decoder share the actual
8-byte DiagnosticAllocator and process mutex 1. Seven compression-tree methods
share the real 8,193-node dictionary owner. PMR aligned allocation/deallocation
use actual standard allocation and guards. The native allocator constructor and
meaning of its first word remain unresolved; no invented production startup.
Two complete GS/EH handler/cleanup/metadata groups replay independently as six
support contributions, without extra function credit. The full compressor and
archive manager are audited; checksum ownership and real stream/record lifetime
remain open. Missing Ghidra failure jumps are included in whole PE extents.

All 25 public tests pass, including independent codec vectors, overlapping and
wrapped dictionary references, retained dictionary state, native exhaustion,
guarded buffers, tree replacement/removal and actual owned aligned allocation.
The counted-name fixture now binds its shared translation unit's process globals.
Target/full Ghidra attestation and tracking/progress pass. Maintained src/probes
froze before the complete cold replay. EXACT054 configure/registration writers
completed once and are stamped. NEVER RERUN them or older writers.

The user's latest priority is complete core dispatchers, deferring standalone
leaves. Next target is ECL Runtime tick 0053B5C0: 11,110 body bytes, 2,525 decoded
instructions and an independent 392-byte / 98-entry jump table. Private EXACT055
boundary audit reconciles all 80 Ghidra-omitted heads and 76 distinct case heads;
no prefix/body fragment is accepted. Recover the actual 72-byte Runtime, 112-byte
ScriptManager and direct stack/loader/interpolation dependencies together.
The downstream Enemy opcode dispatcher 0048C010 / 41,967 bytes follows this VM.
No EXACT055 source or exact claim is accepted yet. Reference facades and its
older 80-byte Runtime are not production ABI evidence.

Native reconstruction stays active. English / repo-python / serial compiler /
no subagents / `gpt-6.1-sol:` commits / authorized public main push persist.
Earlier entries are historical checkpoints.

## EXACT-053 — 2026-10-07 — Worker launch and shutdown lifetime

Five complete Worker lifecycle bodies add666 instruction bytes and five
destructor alignment bytes. All377 units /67 coldobjects /58,903 disjoint complete
comparison bytes strictly replay; source377 / pendingorigins316 / library4 /
authored57 and4,074 unchanged. See EXACT_WORKER_RECONSTRUCTION.md.

Actual Worker16 owns jthread12 plus atomic<bool> at12. Native start replaces
threads by guarded detach, resets the close flag and moves a temporary real
jthread. Close/join, plain detach, nested close/detach and destructor preserve
original mutex6 ownership and atomic assignment. One GS/EHsc/Gd/SDL recipe
covers all six Worker units, retaining the earlier44-byte constructor.
Fourteen complete EH support contributions canonically replay with independent
handler/metadata/unwind anchors. Support helpers receive no extra coverage.

Native loading4BAD40/4119, graphics launch4B99F0/164, graphics close4D9E30/53 and
snapshot4DE040/425 are completely audited. Loading retains all14 otherwise
unreferenced failure jumps and its separate32-byte eight-entry path table.
Graphics close belongs to the owner with Worker atD90, not to Worker itself.
Complete graphics/loading/surface/resource/allocator ownership remains pending;
no artificial owners or merged free-function ABIs are maintained. Standard
jthread function-constructor120/native150 and move76/native94 remain nonexact:
locked named-cast intrinsics omit native forward/move calls; Oi-off fails to
close this gap. Do not modify locked headers/compiler or claim these bodies exact.

All24 public C++20/UBSan tests pass, including owned actual tasks, replacement,
blocking join, detach, restart flag reset, mutex6 exclusion and destructor wait.
Target/full Ghidra attestation and tracking/progress pass. Maintained src/probes
froze before cold replay; EXACT053 configure/registration writers completed
once and are stamped. NEVER RERUN them or older writers. All handles closed at
publication. Native goal stays active; continue coherent substantive batches.
English / repo-python / serial compiler / no subagents / `gpt-6.1-sol:` commits /
authorized public main push persist. Earlier entries are historical checkpoints.

## EXACT-052 — 2026-10-07 — shared locks and random stream state

Nine complete units add 693 body bytes and five constructor alignment bytes.
All 372 units / 67 cold objects / 58,232 disjoint complete comparison bytes
strictly replay after shared-header and canonical-profile changes. Source 372 /
pending origins 311 / library 4; authored 57 / 4,074 remains unchanged. See
EXACT_LOCK_RANDOM_RECONSTRUCTION.md for accepted functions and deferred roots.

FunctionChainNode construction/access closes the actual 44-byte node. Its
four-byte flags aggregate and nonthrowing constructor are corroborated by
native producers, consumers and shared EH metadata. The real 22-slot recursive
mutex registry now constructs, exposes slots and tracks enabled recursive depth.
GameRandom seed/next use actual std::lock_guard on shared slot 10 and the real
standard engine, retaining raw last before modulus reduction. One GS/EHsc/Gd
profile covers each FunctionChain/LockRegistry source; GameRandomStream.cpp uses
that profile with /sdl. This is local compiler evidence, not a whole-game claim.

Native update/draw dispatch 412810/611 and 412AA0/587, their complete tables,
both 381-byte sorted insertions and removal/allocator dependencies are reviewed.
Insertion probes remain 371 versus 381: native zero-initialization of the real
iterator precedes begin(). Helper 40C080 is memory initialization, not allocation.
Its original compiler/source policy remains open; do not insert redundant clears
or artificial empty constructors to force matching. Production registry startup,
thread lifetime and complete controller/pool ownership also remain unresolved.

Owned C++20/UBSan tests cover all 22 mutexes, 256 recursive depths, paired gated
calls, cross-thread exclusion and 1,800 independently checked RNG samples.
All 23 public tests, tracking, target and full Ghidra attestation pass.
EXACT052 configure/registration writers completed once; NEVER RERUN them or
older stamped writers. Maintained src/probes froze before full cold replay.
The native goal remains active: continue coherent batches with substantive
roots and immediate dependencies. English / repo-python / serial compiler /
no subagents / `gpt-6.1-sol:` commits / authorized public main push persist.
Earlier entries are historical checkpoints.

## EXACT-051 — 2026-10-07 — intrusive observation and Region lifetime

Twenty complete units add 1,827 body bytes and 15 compiler alignment bytes.
All 363 units / 66 cold objects / 57,534 disjoint complete comparison bytes
strictly replay after shared-header changes. Source 363 / pending origins 302 /
library 4; authored 57 / 4,074 remains unchanged. See
EXACT_INTRUSIVE_LIFETIME_RECONSTRUCTION.md for the accepted and deferred scope.

Real linked-node/list/iterator storage is 20/24/8 bytes on x86. Append/remove,
owner-aware detach, observation migration, search, begin/end and iterator
construction/destruction/advance share one typed protocol. Existing physical
aliases receive no duplicate credit. Region construction closes the previous
317-versus-359 mismatch: native EH handlers and complete FuncInfo flags 5
corroborate natural nonthrowing construction. One precise-FP/GS/EHsc profile
covers all nine Region units, including seven previously accepted members.
Region update calls a declared native retirement dependency, whose body and
controller/allocator lifetime remain undefined. Tests observe calls only.

Complete damage controller 4C0480/1707 and its pool/initialization neighborhood
are reviewed; actual Player/Bullet/Enemy/Effect/score interfaces remain pending.
List construction 31 versus native 40 and reset's equal-size store-register
mismatch remain nonexact. Sorted insertion requires the real registry lock and
controller owner. Do not replace these owners or lifetimes with fake facades.

Maintained src/probes froze before the full cold replay. Public C++20/UBSan
checks, tracking, target and full Ghidra attestation pass; reference 6945/113
is unchanged. EXACT051 configure/registration writers have completed once;
NEVER RERUN them or earlier stamped writers. The native goal stays active;
continue coherent batches. English / repo-python / serial compiler / no subagents /
`gpt-6.1-sol:` commits / authorized public main push persist.
Earlier entries are historical checkpoints.

## EXACT-050 — 2026-10-07 — Damage Region routing/configuration

Thirteen complete units add3,532 bytes, including the2,696-byte dispatcher,
rectangle/circle configuration and Motion/identifier dependencies. All343 units /
65 coldobjects /55,692 disjoint complete bytes strictly replay. Public C++20/UBSan
routing, state preservation, signed duration, alias-order and typed-node checks
pass. See EXACT_DAMAGE_REGION_RECONSTRUCTION.md for all reviewed/deferred neighbors.

Actual196-byte Region contains existing Motion72/Timer16/Angle4/Vector2 values,
three identifier words, flags and a typed linked prefix. One IntrusiveLink<T>
body now serves real Region/FunctionChainNode values, preserving the three old
exact link units. Position-reference40BDA0 was anchor-only; its complete14-byte
head now receives one canonical unit. Shared constructor411970/zero425CC0 and
getter aliases never receive duplicate coverage. No complete controller facade.

Natural Region construction remains317 versus native359: FS/cookie/handler EH
ownership open; no credit or fabricated link destructor. Region update/retire,
controller/pool/list/observer ownership remain pending with exact addresses and
reasons recorded. Source343/pendingorigins282/library4/authored57/4074. Target/DB
and full reference6945/113 remain unchanged. Maintained src/probes frozen before
full cold replay. EXACT050 configure/registration writers completed once; NEVER
RERUN them or previous REF/EXACT writers. Active native reconstruction continues
in coherent batches. English/repo-python/serial compiler/no subagents and
`gpt-6.1-sol:` commits/authorized public main push persist.
Earlier entries are historical checkpoints.

## EXACT-049 — 2026-10-07 — rectangle/segment neighborhood

All twelve reviewed collision roots and nine direct dependencies close in one
batch: 21 complete units / 10,759 new bytes. All 330 units / 63 cold objects /
52,160 disjoint complete comparison bytes strictly replay after rebuilding the
previous graph. Public C++20/UBSan geometry/rotation/alias/boundary tests pass.
See EXACT_RECTANGLE_COLLISIONS_RECONSTRUCTION.md.

Actual Vector2/Vector3 corner/line/hit arrays, cdecl AL/full-EAX/ST0 ABIs, finite
line length, two line tolerances, XY-only distances, inclusive/strict boundaries,
unrotated center shortcuts and signed finite ellipse sampling remain native.
Scalar XY rotation now has one typed template body for both genuine values,
sharing the already canonical physical head without duplicate coverage. Array
rotation has one body with two exact native stride variants. Cyclic edge table
has an independent read-only anchor and natural initializer; no extra credit.

Source330/pendingorigins269/library4/authored57/4074. All twelve candidates are
exact; no structural-only/deferred candidate remains in this bounded batch.
Full dispatcher/controller ownership, original names/origins, exceptional FP,
linkage and whole-game runtime remain open. Target/database/reference6945/113
unchanged. Source/probes frozen before full cold replay. EXACT049 configure and
registration writers complete once; NEVER RERUN them or earlier REF/EXACT writers.
Active unlimited native goal continues in coherent batches. English / repo-python /
serial compiler / no subagents / gpt-6.1-sol: commits / authorized public main persist.
Earlier entries are historical checkpoints.

## EXACT-048 — 2026-10-07 — native collision geometry batch

Ten complete predicates/vector dependencies add 3,841 comparison bytes. All
309 units / 61 cold objects / 41,401 disjoint complete bytes strictly replay.
C++20/UBSan geometry, threshold/aliasing, boundary/count and Z preservation
checks pass. See EXACT_COLLISION_SHAPES_RECONSTRUCTION.md.

Circle/ellipse containment and finite sampling, polygon/star radial-edge tests,
AL bool/cdecl ABI, signed counts, actual Vector3 edge arrays, and native paired-Y
collinear quirks are preserved. Normalization threshold is 0.01f and tiny vectors
retain original-vector scaling. Division retains actual hidden-result member ABI.
Native array constructor iterator receives an independently audited anchor only,
with no extra source/authored credit. Original names/origins and enclosing native
collision dispatcher/controller ownership remain open.

Source309/pendingorigins248/library4/authored57/4074. Full previous graph rebuilt
following shared source/header changes. Maintained src/probes frozen before cold
replay. EXACT048 configure and registration writers complete once; NEVER RERUN
them or completed REF/EXACT writers. Target/database unchanged, reference6945/113
unchanged. Active unlimited native goal continues in coherent dependency batches;
remaining collision families are close neighbors. English / repo-python / serial
compiler / no subagents / gpt-6.1-sol: commits / authorized public main persist.
Earlier entries are historical checkpoints.

## EXACT-047 — 2026-10-07 — Enemy interpolation dependency batch

The 2,433-byte current-first/per-axis Enemy update and its direct dependencies
add eight complete functions / 2,716 comparison bytes. All 299 units / 60 cold
objects / 37,560 disjoint complete comparison bytes strictly replay. Public
C++20/UBSan mixed-axis, clock, terminal, negative-duration, indexed storage and
half-speed acceleration checks pass. See EXACT_ENEMY_INTERPOLATION_RECONSTRUCTION.md.

Source 299 / pending origins 238 / library 4; authored 57 / 4,074 unchanged.
The existing 100/388/12/72-byte owners retain their layouts and prior exact units.
Full signed duration reads preserve negative states. Terminal endpoint selection
uses shared mode even on the axis path; early returns leave current unchanged.
Enemy stop binds the prior duration-at-4C physical head without duplicate credit.
Axis modes use a real three-int array; Vector3 indexing addresses actual named
float subobjects via byte representation, with established index domain 0..2.

Maintained src/probes frozen before the full cold replay; canonical receipts
were rebuilt after shared declaration changes. EXACT047 configure/registration
writers execute once; never rerun completed writers or any older REF/EXACT writer.
Target/database unchanged. Reference review remains 6,945 terminal / 113 grammar.
The active native goal remains open: continue substantial coherent owner batches.
Enclosing Enemy/PMR/ECL/resource/VM lifetime and original origins remain unresolved.
English / repo-python / serial compiler / no subagents / gpt-6.1-sol: commits /
authorized public main push persist. Earlier entries are historical checkpoints.

## EXACT-046 — 2026-10-07 — shared interpolation protocol batch

Shared 4,154-byte easing and all eight interpolation update bodies now have
one maintained template protocol, with two evaluations that leave time unchanged.
32 complete units add 13,952 comparison bytes. All 291 units / 60 cold objects /
34,844 disjoint comparison bytes strictly replay; public C++20/UBSan checks pass.
See EXACT_INTERPOLATION_RECONSTRUCTION.md for storage, ABI, complete dispatch,
shared heads, signed/byte wrapping, active evaluation order and acceptance limits.

Source 291 / pending origins 230 / library 4; authored 57 / 4,074 unchanged.
Reference review remains 6,945 terminal bodies / 113 reconciled grammar files.
Maintained src/probes frozen before the full cold replay; all canonical receipts
were rebuilt after shared declarations changed. EXACT046 configure/registration
writers execute once; never rerun completed writers or any older REF/EXACT writer.
Target and Ghidra database remain unchanged.

Continue substantive native reconstruction in coherent batches. Enemy's distinct
current-first/per-axis interpolation is the closest next dependency family;
resource/EH/allocator-heavy schedulers and archive owners retain open questions.
English / repo-python / serial compiler / no subagents / gpt-6.1-sol: commits /
authorized public main push persist. Earlier sections are historical checkpoints.

## EXACT-045 — 2026-10-07 — shared Motion protocol batch

Two substantive Motion updates and their direct dependency family now have
18 complete canonical units: 2,527 code bytes / 2,572 complete comparison bytes.
All 259 units / 59 cold objects / 20,892 disjoint comparison bytes strictly
replay. Public finite C++20/UBSan protocol tests replace the old update stubs.
See EXACT_MOTION_RECONSTRUCTION.md for native flow, dispatch/padding, member
semantics, profiles, security cookie, shared heads and acceptance limits.

Source 259 / pending origins 198 / library 4; authored 57 / 4,074 unchanged.
Reference review remains 6,945 terminal bodies / 113 reconciled grammar files.
No target/database mutation. Maintained src/probes frozen after this batch;
all canonical receipts were cold-rebuilt because shared declarations changed.
The private EXACT045 configure and registration writers each execute once;
never rerun old REF001..REF044 or completed EXACT045 writers.

The active goal is substantive native exact reconstruction. Continue in
coherent dependency batches, prioritizing interpolation evaluation/easing or
another high-return main owner. Archive decoding and scheduler bodies retain
allocator/EH/iterator and global-state questions; record blockers and continue
with independently closable families. English / repo-python / serial compiler /
no subagents / gpt-6.1-sol: commits / authorized public main push persist.
The sections below are historical checkpoints.

## REF-044 — 2026-10-07 — existing-reference review complete

All remaining 184 bodies across 46 files fully read and recorded as support.
All 16 remaining grammar files / 119 sites individually reconciled. Manual
reading recovered the omitted historical ABI invoke_probe: index now 6,945,
with all 6,944 previous identities/hashes unchanged. Global 6,945 terminal /
zero pending; all 113 grammar files complete. See REFERENCE_SUPPORT_REVIEW.md.

- No new canonical source in this tooling/bridge batch. All 241 complete units
  replay using current hash-verified cold-build receipts: 57 objects / 18,320
  disjoint bytes. Authored exact credit remains 57 / 4,074; 180 origins pending.
- Final reference outcomes: 114 absorbed / 3 library / 1,877 nonexact /
  4,951 support. Reference-body counts do not measure native game completion.
- Historical playable packaging retains original engine instructions. Sparse
  frame capture, static dispatch/CFG checks, scoped component oracles and
  source snapshot builds retain their documented acceptance limits.
- REF044 registration completed once; NEVER RERUN ref044-record.py or any
  REF001..REF043 writer. Maintained src/probes unchanged, current canonical
  receipts valid; older reference diagnostic objects may be stale.
- One synthetic parser regression added for naked MSVC/line assembly, original
  CRLF hashes and preserved raw gaps. English / repo-python / serial compiler /
  no subagents / commit prefix / authorized public main push persist.

The requested exhaustive review is closed. Further reconstruction can select
coherent native owner families from the recorded nonexact cases; full owner/
vtable/EH/resource/allocator/startup/link/gameplay acceptance remains open.
The sections below are historical checkpoints.

## REF-043 — 2026-10-07 — complete StageBackground batch

All 121 remaining StageBackground bodies were individually read across 16 files:
5 absorbed / 26 nonexact / 90 support. One grammar file/site reconciled; global
6,761 terminal / 183 pending, grammar 97 complete / 16 pending. Goal active.

- Genuine FogValue28 contains two distances, four float channels and packed
  color. Six complete members and shared FogInterpolation164 construction add
  1,043 bytes. Native camera construction, five-value strides, seven-word copies
  and hidden-result member calls independently establish real storage/ABI.
- All 241 units / 57 cold objects / 18,320 disjoint bytes exactly replay.
  Source 241 / pending origins 180 / library 4; authored 57 / 4,074 unchanged.
  Public g++13/C++20/UBSan dirty guarded construction, widened finite arithmetic,
  conversion edges, signed zero/raw distance payload, repacking, input preservation
  and assignment alias tests pass. Channel truncation must be int32-representable;
  portable nonfinite/out-of-range channel conversion remains outside acceptance.
- Eleven fresh unmodified reference production TUs define 528 functions / 91
  static functions. All 35 complete comparisons across 32 bodies differ in size.
  Actual Fog members replace semantic helpers; free helpers get no native ABI
  credit. Full Camera/Background/ScriptState/ANM/VM/vptr/EH/resources remain open.
- Historical state/fog 62,048 binds 3/3 hashes; STD VM 43,080 binds 7/7;
  shared pool 2,915,831 binds 389/389. Stage subset 35,476 field comparisons /
  77 groups retains finite inputs, pointer normalization, valid grids, excluded
  transition allocation and empty foreground global layers39/40. No Windows
  oracle/writer rerun or executed binary/compiler/startup binding.
- Maintained src/probes frozen; all 241 canonical receipts and this batch's 11
  reference TU receipts current. Other older reference receipts are stale.
  REF043 manifest configured once; ref043-record.py and the corrective
  ref043-finish-record.py completed registration. NEVER RERUN either writer
  or any REF001..REF042 registration writer. See the full batch document
  REFERENCE_STAGE_BACKGROUND_REVIEW.md.

Continue all 183 remaining bodies: root PowerShell 5, incremental 62, audit 39,
platform_services 1, tests 10 and tools 66, plus 16 grammar files. Serial MSVC,
no subagents, English, repo-python, commit prefix and public main persist.

## REF-042 — 2026-10-07 — complete Sprite / ANM / texture batch

All 540 remaining Sprite bodies were individually read across 46 indexed files:
7 absorbed / 153 nonexact / 380 support. Five grammar files and 17 indexed sites
were reconciled. Global coverage is 6,640 terminal / 304 pending; grammar files
are 96 complete / 17 pending. The exhaustive review goal remains active.

- Thirteen natural complete contributions add 1,387 bytes: IntegerTriple,
  Matrix4, three Sprite vertex values, mixed AnmVariables, three instantiations
  of the shared Interpolation template, and four cdecl texel accumulators.
  Native nested calls, array strides/counts, channel extraction and independent
  relocation anchors establish actual components; original names/origins remain
  pending. Full Animation/Controller/Worker/resource owners remain unaccepted.
- All 234 canonical units cold-replay from 56 objects over 17,277 disjoint bytes.
  Source presence 234 / pending origins 173 / library 4; authored 57 / 4,074
  unchanged. Portable C++20/g++13/UBSan passes 2,613,444 independent guarded
  construction, exhaustive 16-bit channel, wrapping and alias-order checks.
- Thirty-six actual unmodified reference production TUs freshly compiled after
  final source freeze: 1,516 defined / 297 static functions. The 212 complete
  comparisons across 159 bodies yield 210 size differences and two mismatches.
  A natural typed AnimationBase probe is 707 versus 725 bytes and rejected
  whole; no prefix, padded owner or compiler-shaping workaround is accepted.
- Six retained reports were read and rebound without executing their drivers
  or writers. Controller CPU binds 13/14 distinct source hashes: Worker header
  stale. Other retained hash counts and prepared-object/COM/finite-domain limits
  are documented in REFERENCE_SPRITE_REVIEW.md. They do not bind the executed
  binaries/compiler/startup or establish full rendered gameplay.
- The complete source ANM dispatcher has 163 cases; 161 nondefault routes match
  the independently checked native 161-slot table and 636-byte index. Full VM
  member/EH ABI and external dependencies remain open. Native constructor
  callbacks and matrix consumers corroborate values, not complete owners.
- ref042-record.py and ref042-configure-units.py executed ONCE; NEVER RERUN them
  or any earlier registration writer. Maintained src/probes are frozen. All 234
  canonical receipts and this batch's 36 reference TUs are current; unrelated
  older reference objects need rebuild before reuse.

Continue StageBackground's 121 bodies, then 183 other bodies and 17 grammar
files. Serial MSVC, no subagents, English, repo-python, commit prefix and public
main authorization persist. See REFERENCE_SPRITE_REVIEW.md for the full batch.

## REF-041 — 2026-10-07 — PlayerRecord and remaining Gameplay batch

All169 remaining Gameplay bodies individually read across18 files:3 absorbed /
25 nonexact /141 support; prior Player ctor review upgraded separately. Global
6100 terminal/844 pending; all1019 Gameplay bodies reviewed; gaps91/22 unchanged.
Exhaustive goal active. Next Sprite540, StageBackground121 and183 other bodies.

- Real PlayerRecord240 has64-bit score/individual integer and byte fields with
  natural implicit gapsA6/A7,B1..B3. Array stride240/count2/constructor pointer,
  score and mutating-power consumers independently corroborate real value.
- All45 setters plus ctor/score/power naturally match. Two shared heads41DF50 /
  412D10 already canonical elsewhere get no duplicate credit.46 new units add
  3654 bytes. Full221unit/51object cold replay covers15890 disjoint bytes;
  source221/pendingorigins160/library4, authored57/4074 unchanged.
- 24080 independent dirty guarded/default/edge/full-byte C++20/UBSan checks pass.
  Full48 PE ranges agree with attested Ghidra; native setter stores/constants/
  RET4/call471170 anchor verified independently, no relocation-solving credit.
- Eight actual reference TUs freshly compiled after final source freeze:
  486 defined/127 static;71 complete comparisons27bodies:69 size differences,
  Game restart20/clearbit6 32 structural-only (full Game owner unclosed).
- Static eight308-byte stage rows/448 scalars/168nullable pointers and18difficulty
  constants PE verified. Extraction writers fully read, never executed/imported.
- Historical Game107522 binds2/2; Player58025 and Loading40345 bind12/13 (each
  entry adapter stale). Frame225280 binds389/389 and shared2915831 report digest
  verified; prepared activation/replay/secondary exclusions and pointer-word
  normalization retained. NullHUD Player fixture does not prove active observer.
  No Windows oracle/writer rerun or executed binary/compiler/startup bind.
- ref041-record.py executed ONCE; NEVER RERUN any registration writer. src/probes
  frozen. All221 canonical receipts and these8 reference TUs current; unrelated
  older reference receipts stale after PlayerRecord addition. Table/Session/
  Game/vptr/EH/HUD/worker/resource owners and original names/origins unaccepted.

Serial MSVC/no subagents/English/repo-python/commit prefix/public main persist.
See REFERENCE_GAME_LOADING_REVIEW.md. Continue all844 pending bodies/22gap files.

## REF-040 — 2026-10-07 — complete entity-opcode batch

All 243 scoped implementations individually read across22 files:26 nonexact /
217 support. No new exact source or unit. Five grammar files/39 indexed sites
reconciled; complete bodies already indexed. Global5,931 terminal/1,013 pending;
gaps91/22; Gameplay169 pending. Exhaustive goal remains active.

- Maintained src/probes/profiles unchanged since REF039. All175 canonical units /
  50 existing cold objects /12,236 disjoint bytes still pass fresh receipt checks
  and strict replay. Source175/pending origins114/library4/authored57/4074 unchanged.
- Eleven actual reference TUs freshly compiled serially:1,134 defined/196 static.
  Twenty-seven complete diagnostics across26 bodies all lengths differ. Extracted
  optional-int handlers are not standalone native48C010 function extents.
- Original704-byte opcode map4966B8/174-slot primary496400 fully PE verified.
  Exactly224 defined cases;569/unknown default4963DF clears full EAX. Full
  dispatcher EH/shared flow/owners and all case behavior remain unclosed.
- Ten native helper ranges fully PE decode/closed direct branches; no accepted
  heads. Phase methods actual Enemy+340 vector/RET16,8 differ from free State
  helpers. Callback tables and four phase name strings independently verified.
- CPU1,254,134/0/frame7,682 each105 current hashes; entity prose count1,254,114
  is stale. Selected six opcode groups381,824 checks, not whole-game evidence.
  Resource3,304 only100/105 current hashes. No Windows oracle/writer rerun or
  executed binary/compiler/startup bind. Creation patches six endpoints; Laser
  patches three plus synthetic vtable; misc patches four. Metadata padding and
  pointer/vptr normalization, null HUD/finite domains and heavy exclusions noted.
- Private ref040-record.py executed ONCE; never rerun it or any older writer.
  Current175 canonical receipts remain valid. Other historical reference objects
  need rebuild before reuse; this batch's eleven are current.

Continue other Gameplay169, then Sprite540/StageBackground121/other183 and22
remaining grammar files. Serial MSVC/no subagents/English/repo-python/commit
prefix/public main authorization persist. See REFERENCE_ENTITY_OPCODE_REVIEW.md.

## REF-039 — 2026-10-07 — Enemy damage/drop/defeat/mesh batch

All 141 scoped bodies individually reviewed: 5 absorbed / 17 nonexact / 119
support. Two prior health/pattern reset reviews upgraded separately. Twenty-one
indexed files; two grammar files / ten fastcall annotations reconciled. Global
5,688 terminal / 1,256 pending; grammar 86/27; Gameplay 412 pending. Goal active.

- Nine natural complete members on real EnemyHealth28 and EnemyPattern168 add
  677 bytes. Full 175-unit / 50-object cold replay covers 12,236 disjoint bytes.
  Source175 / pending origins114 / library4; authored57 / 4,074 unchanged.
- Native State constructor proves health at18C and pattern at1A8. Full EAX
  health queries, modulo32 / signed division7, genuine sixteen-count arrays,
  Timer protocols and reset preservation restored. Original names/origins open.
- Direct PE decode retains Ghidra-omitted4A3FDD jump. Ordinary if/else returns
  naturally reproduce all123 apply bytes; no prefix or compiler-shaping code.
- Ten actual reference TUs freshly rebuilt; 219 defined functions / 73 static.
  Twenty-six complete diagnostics across22 bodies all differ in length.
  Other older reference receipts are stale after this maintained source freeze.
- Dirty guarded construction, 10,000 independent widened-arithmetic/full-byte
  cases and Timer/count/reset edge checks pass under portable C++20/UBSan.
- CPU1,254,134/0 and frame7,682 bind105/105 current hashes; resource3,304 binds
  only100/105. No Windows oracle/writer execution or executed binary/recipe bind.
  Damage cases exclude active child paths; source fixture records their order.
  Drop patches Item; defeat patches nine endpoints and fake tick controls revival;
  mesh shares original initialization/strip callees. Whole-owner behavior open.
- Private ref039-record.py executed ONCE; never rerun any historical writer.
  Maintained src/probes remain frozen at the full canonical replay checkpoint.

Continue entity-opcode batch243, then other Gameplay169, Sprite540,
StageBackground121 and183 other bodies; grammar27 files remain. Serial MSVC,
no subagents, English, repo-python, commit prefix/public main authorization
persist. See REFERENCE_ENEMY_DAMAGE_REVIEW.md.

## REF-038 — 2026-10-07 — Enemy movement/frame/spawn/read batch

All236 scoped bodies individually reviewed:1 absorbed/36 nonexact/199 support;
prior REF037 movement constructor upgraded separately to absorbed.23 indexed
files, one grammar file/two default-Vec3 nodes reconciled. Global5,547 terminal/
1,397 pending; grammar84/29; Gameplay553 pending. Exhaustive goal stays active.

- Four natural full constructors add405 bytes:Spawn47BB30/95, current-first
  EnemyMotionInterpolation48B270/123, Movement48B550/90, generic Vector2
  Interpolation447AC0/97. Actual84/100/388/64-byte values; no whole Enemy facade.
- Full166-unit/48-object cold canonical replay covers11,559 disjoint bytes.
  Source166/pending origins105/library4; authored57/4,074 unchanged. Dirty
  guarded construction and embedded Counter reset C++20/UBSan checks pass.
- Spawn Counter20 is four integer/eight float words, tail50 a native4-byte
  value subobject. Identifier32 original tag/role unknown; shared425CC0 is not
  proof of AnimationHandle type and gets no second standalone address credit.
- Eleven actual production TUs rebuilt after final source freeze; all unrelated
  older reference receipts stale.560 defined symbols/189 static;37 complete
  diagnostics across36 bodies all differ in length; no structural matches.
- CPU1,254,134/0 and frame7,682 assertions bind105/105 current source hashes.
  Movement94080/getters88666 are retained finite prepared-object groups;
  no Windows oracle/report writer rerun, binary/compiler/startup unbound.
- Resource3304-assertion report binds100/105 hashes only:Enemy/frame/CPU driver/
  resource test/frame test stale. Current source review does not refresh that
  historical result. GPU recorded; full simulation/drawing explicitly excluded.
- Frame PAGE_NOACCESS test really destroys then guards retired storage; prior
  CPU20 hazard fixture leaves it accessible. Full native-frame equivalence,
  owner/allocator/vptr/EH, merged getter/Reader ABI and opcode dependencies open.
- Private ref038-record.py executed ONCE; never rerun. All older
  writers already executed. Maintained src/probes frozen at canonical replay.

Continue553 Gameplay, Sprite540/StageBackground121 and183 other bodies plus29
remaining grammar files. Serial MSVC/no subagents/English/repo-python/commit
prefix/public main authorization persist. See REFERENCE_ENEMY_MOVEMENT_REVIEW.md.

## REF-037 — 2026-10-07 — Enemy owner, stack and VM batch

All230 scoped Gameplay implementations individually reviewed:4 absorbed/62
nonexact/164 support.13 indexed files plus relevant three type headers, recipe,
README and retained reports fully read. Two grammar files reconciled. Global
5,311 terminal/1,633 pending; gaps83/30. Exhaustive goal remains active.

- Six natural value members add595 complete bytes:ScriptStack ctor4A36D0/42,
  absolute53E630/102,local53E6A0/120,leave_frame540300/52; EnemyCounters
  ctor47BAA0/141,reset4AB1B0/138. Genuine PMR vector16/Stack24 and four-int/
  eight-float Counter48 established through native producers/consumers.
- All162 canonical units freshly replay from46 frozen-source objects/11,154
  disjoint bytes. Source162/pending origins101/library4, authored57/4,074.
  Portable C++20/UBSan value/growth/frame-observation tests pass. Generic
  output-pointer/int-status pop remains undefined in maintained production;
  vector/allocator implementation and full VM/Enemy/vptr/EH owners unaccepted.
- All47 Gameplay production TUs compile; seven used for diagnostics rebuilt
  after new source freeze.1,451 defined symbols/211 static;74 full comparisons
  across63 bodies give73 lengths/one mismatch. clear_async93 matches only21/81
  structural bytes.33 native ranges full PE-decode;79 omitted Ghidra instructions
  retained. Only six accepted extents; original call anchors precede probes.
- Native loader4A3650 calls the same PMR-stack ctor4A36D0 at+21C, where
  reference declares std::string24. Raw-loader parser fixture bypasses ctor;
  initialization/container/lifetime mismatch recorded, full loader still open.
- Retained1,254,134/0 binds105 source hashes;37,707 general VM comparisons
  include800 direct call setups and400 six-frame real native allocating/deleting
  chains. Actual PMR/heap/locks now exercised historically, but executed binary/
  toolchain/startup unbound. Windows CPU oracle/writer not rerun. Iterator20
  hazard cases retain storage and do not establish safe access after free.
- Private ref037-record.py executed ONCE; never rerun. All older writers also
  already executed. Canonical src/probes frozen. Historical unrelated reference
  receipts require rebuilding before reuse; only seven Gameplay TUs are current.

Continue coherent Gameplay789, then Sprite540/StageBackground121 and183 other
support implementations. Every body/gap still needs its own decision; do not
mark complete with1,633 bodies/30 gap files pending. English/repo-python/
gpt-6.1-sol subjects/public main pushes and serial-MSVC/no-subagent rules persist.
See REFERENCE_GAMEPLAY_ECL_REVIEW.md and private ref037 resume notes.

## REF-036 — 2026-10-07 — complete ECL batch

All128 remaining ECL implementations reviewed individually:1 absorbed/26
nonexact/101 support; entire144-body ECL module is closed for review. Seven
indexed source files plus recipe/README/reports fully read. Two empty-default
initializer grammar files reconciled. Global5,081 terminal/1,863 pending;
gap coverage81/32. Exhaustive goal remains active.

- signed_unit semantics reuse existing game_random_signed_unit129; no new
  source/units. All156 canonical units replay from44 fresh frozen-source objects.
  A recount gives10,559 complete bytes, correcting the earlier10,558 prose
  total without changing any contribution. Source156/pending origins95/library4,
  authored57/4,074 unchanged. Both original ECL TUs freshly compile serially.
- Twenty-four complete reference comparisons all differ in length; VM532
  defined symbols/66 static, math26/six. Genuine source Stack20/Runtime80/
  Subroutine44 differ from native24/72/eight-byte records; vtable order,
  arbitrary-length stack/output-pointer/status ABI and pool lifetimes unclosed.
  Small leave_frame cannot accept a fabricated native owner/pop protocol.
- Twenty-eight focused native ranges fully PE-decode;102 omitted Ghidra
  instructions retained. Original98-entry table53E128/75 case addresses checked.
  Interpolation53E00C is inside53B5C0, not a separate function. Rejected extents
  remain provisional, entity48C010 separate. No target/database edits.
- Retained41,067/0 binds five current source hashes and locked EXE; executed
  oracle binary/includes/compiler recipe not bound.21 JSON histograms reproduce
  23,760 total/15,872 core counts, without fresh raw-resource provenance.
  Fresh unmodified C++20/UBSan source tests pass. Native CPU oracle, writer,
  allocator traversal, entity/invalid-stack/error/cross-thread/oldCRT NaN
  equivalence remain unexecuted or unproved.
- Private ref036-record.py executed ONCE; never rerun. Older writers also
  already executed. Previous43 display/Overlay reference receipts remain
  historical and require rebuilding before reuse. src/probes remain frozen.

Continue Gameplay1019, then Sprite540/StageBackground121 and183 remaining
support bodies. Every implementation/gap still needs its own outcome; do not
mark complete with1,863 bodies/32 gap files pending. English/repo-python/
gpt-6.1-sol subjects/public main push and no-subagent/serial-MSVC rules persist.
See REFERENCE_GAMEPLAY_ECL_REVIEW.md and private ref036 resume notes.

## REF-035 — 2026-10-07 — scalar math component checkpoint

Four natural scalar wrappers add153 complete exact bytes:sin439820/35,
cos4397C0/35,sqrt446B30/35,atan2459280/48. Full156-unit cold replay across44
objects/10,558 bytes and portable C++20/UBSan finite identities/squares/quadrants/
signed-zero checks pass. Source156,pending origins95/library4,authored57/4,074
unchanged. Original names and authored/compiler/library identity remain pending.

- All16 ECL math.cpp implementations individually reviewed:5 absorbed/5
  nonexact/6 support. wrap_angle reuses existing angle_normalize/187; no extra
  canonical unit for that absorption. Math header/recipe fully read. Global
 4,953 terminal/1,991 pending; gap coverage79/34 unchanged. Goal active.
- Related Gameplay1019/ECL144 family has114 indexed files/1163 bodies; only16
  math bodies closed so far,1147 remain pending. File hashes/inventory are not
  reading or review. Full VM/Enemy/owner/fixtures/report/gap audit still required.
- All four native ranges PE/Ghidra/RET attested. Original CALL operands precede
  probe; FSIN/FCOS/FSQRT/error strings and atan2 descriptor59A980 independently
  corroborate actual CRT anchors. cdecl float->double->float/ST0, atan2 y,x
  order and original caller cleanup confirmed. Original CRT bodies/global
  startup/errno/NaN/exception environment are dependencies, not reconstructed.
- Fresh unmodified math TU/26 symbols (six static) gives ten full comparisons:
  four structural/six lengths. Natural angle_difference probe163/native150
  deferred. Polar output-vector pointer vs two references, rotate separate
  input/output pointers and saved-X alias order, typed interpolation/Timer/clock
  and complete easing/switch ownership remain unclosed. No fake declarations.
- Whole156 canonical build receipts bind final src/probes freeze. Previous43
  display/Overlay reference receipts describe the historical REF034 source
  fingerprint and need rebuilding before future reuse; this component review
  relies only on the freshly rebuilt math TU. No simultaneous MSVC builds.
- Private .analysis/ref035-record-math.py EXECUTED ONCE; NEVER RERUN. All
  REF034/older writers already executed too.

Continue coherent Gameplay/ECL1147 implementations, then Sprite540/
StageBackground121 and183 remaining support bodies. Do not mark goal complete
with1,991 bodies/34 gap files pending. See REFERENCE_GAMEPLAY_ECL_REVIEW.md and
private ref035 resume notes. English text/repo-python/gpt-6.1-sol commit subjects
and public main push authorized; no subagents/concurrent compiler sessions.

## REF-034 — 2026-10-07 — complete Overlay batch

All376 Overlay implementations individually reviewed:180 nonexact/196 support,
40 fully read indexed files. Entire672-body Overlay/HUD/SmallScore/completion
family closed for individual review. Global4,937 terminal/2,007 pending of6,944;
nine grammar files/28 sites reconciled, gaps79 complete/34 pending. Exhaustive
goal active; nonexact/support decisions are not recovered game implementations.

- No new canonical source or units. All152 complete contributions replay with
  fresh unchanged-source receipts,43 objects/10,405 bytes. Source152, pending
  origins91/library4, confirmed authored57/4,074 unchanged. Existing cold builds
  remain valid; no maintained source/header/profile changes this checkpoint.
- All16 Overlay production objects attested, actual static/external/template/
  callback/deleting/EH inventories retained.318 complete comparisons across174
  indexed bodies:268 length differences/50 structural matches;47 static-symbol
  diagnostics. No prefix acceptance or diagnostic-solved relocation anchors.
- Native18 factory entries,540 strategy slots/30 base slots/three owner slots
  independently PE-check.16 constructors call52FAD0 directly; reference adds
  StandardWeapon constructor/vptr. Six31-byte constructors structurally match
  but that extra owner cannot be relabeled as the actual native base.
- Actual factories21 bytes pass diagnostic strings to thiscall global5B8894;
  allocators135/141 retain receiver/string/RET4/EH4. Destroy532740 calls532840,
  then deleting532AB0(flags0), then532950 restoring575810. Reference defaulted
  nonvirtual destructor emits no body. Real allocator/type/lifetime unclosed.
- Owner ctor532880/208/vtable576228/Counter532850 corroborated. Nine focused
  native functions fully decode; missing JMP532C52->532D59 retained. Other
  rejected extents and broader436-head export remain provisional.
- Native phase end/update calls test full EAX; retained weapon fixtures often
  compare AL only. Base queries return MOVZX raw bytes34/35 versus source!=0;
  original bool/byte types and noncanonical object domain remain unproved.
- Full weapon/owner/frame/visuals/Environment/fixtures/recipe/writer/report text
  read.870400/0 binds42 current post-run hashes, not executed build identity;
  oracle excludes owner/lifecycle/factory/visuals production linkage. Mock
  resources, ControlledWeapon, callback/vptr normalization/byte-only returns
  and real GPU/thread/retirement/closure owners remain scoped. No Windows
  CPU oracle, evidence writer or game playthrough executed during this review.
- Private .analysis/ref034-record.py EXECUTED ONCE; NEVER RERUN. All older
  registration/review writers also already executed. Preserve frozen src/probes
  and current43 reference receipts while continuing serial compiler work.

Next coherent batches: Gameplay1019/ECL144, Sprite540/StageBackground121 and183
remaining support implementations. Review every body/gap and absorb easy natural
exact components; do not mark the goal complete with2,007 bodies/34 gaps pending.
No subagents/concurrent MSVC builds. English maintained text, repo-python,
gpt-6.1-sol subjects and public main push remain authorized. Full family review:
REFERENCE_OVERLAY_HUD_SCORE_COMPLETION_REVIEW.md; private ref034 resume notes.

## REF-033 — 2026-10-07 — HUD batch and Dialogue protocol

All134 HUD implementations individually reviewed:2 absorbed /59 nonexact /
73 support,36 fully read indexed files. Global4,561 terminal /2,383 pending of
6,944; three retained-C grammar files/eleven sites reconciled, gaps70/43.
Family296/672 reviewed; Overlay376 remains pending. Exhaustive goal active.

- Natural DialogueFlags66, SJIS predicate62 and decoder197 add325 complete bytes.
  Full152-unit cold replay across43 objects /10,405 bytes; source152, pending
  origins91/library4, authored57/4,074 unchanged. Actual+104 four-byte flags
  retain upper25; native byte/full-int predicate ABI and signed decoder loads.
- Independent constructor/caller/helper/BSS xrefs precede anchors; accepted
  ranges fully PE-decoded/closed, including missing JMP4B6498. Buffer storage
  externally declared, extent/lifetime unproved. Valid NUL/pair domain explicit;
  synthetic256-byte/all-byte/all-length/dirty flags checks pass C++20/UBSan.
- All43 actual family production TUs freshly compiled after final source freeze.
  Eighteen HUD objects inventoried including static/load templates/lambdas/EH.
  Forty full length rejections; three49-byte structural deleting wrappers need
  original owners/vtable/dtor/EH and receive no canonical credit. Vtable57062C
  independently read4B06A0/4B5BB0/421760. Missing VM/factory JMPs decoded.
- Native4AC290/4AFEE0 closure partition differs from free callback. Resource
  wrapper4B5900 pushes0;4B5920 returns fullEAX0/1 versus no-argument/bool source.
  Keep unknown callback parameter/real Worker ownership unresolved.
- HUD232192/0 is shared Sprite subset389 current hashes/digest. Historical
  1798099/960 has235 current/17 stale hashes; frame_pool960 failures retained.
  Full domain/hooks/report/writer/fixtures read; none executed. Draw28 constants
  independently PE-attest. VM workers/active Dialogue/StoneMenu/GPU remain open.
- Full Overlay production and all oracle text now read;870400/0 binds42 current
  post-run hashes, excludes owner/lifecycle/factory/visuals linkage and samples
  several virtual returns only in AL. Individual body/owner/table/COFF review
  remains pending; reading/compilation alone is not a terminal decision.
- Private .analysis/ref033-record.py EXECUTED ONCE; NEVER RERUN. REF032/all older
  writers also already executed. Preserve final src/probes freeze while using
  current152 exact/43 reference receipts. No live compiler/Ghidra processes.

Next: finish all376 Overlay bodies,18-position factory/actual vtables/return ABI,
unmodified production objects and parser gaps, then Gameplay1019/ECL144,
Sprite540/StageBackground121 and183 support bodies. Do not mark goal complete
with2,383 bodies /43 gap files pending. English text, repo-python,
gpt-6.1-sol commit subjects and public push remain authorized. Full review:
REFERENCE_OVERLAY_HUD_SCORE_COMPLETION_REVIEW.md; private ref033 resume notes.

## REF-032 — 2026-10-07 — display values and score/completion checkpoint

Three natural constructors add193 complete bytes: ScoreEntry50FD50/127,
HudGauge4AECE0/34 and OverlayCounter532850/33. Full149-unit cold replay across
41 objects /10,080 bytes and C++20/UBSan dirty construction checks pass. Source149,
pending origins88/library4; authored57/4,074 unchanged. ScoreEntry's implicit
alignment bytes3A/B are retained; actual Vector3/Timer anchors precede matching.

All162 SmallScore74/StageCompletion88 implementations are individually reviewed:
one absorbed /28 nonexact /133 support, nineteen fully read indexed files.
Global4,427 terminal /2,517 pending; two grammar files/six sites reconciled,
gaps67/46. See REFERENCE_OVERLAY_HUD_SCORE_COMPLETION_REVIEW.md.

- All43 production TUs in the four-module family freshly compile after final
  maintained source freeze. Actual inherited include paths/strict FP retained.
  Nine score/completion objects' static/external symbols, inline/adapters and
  deleting wrapper yield30 full diagnostics:28 sizes, one mismatch, one
  structural match. SmallScore deleting wrapper lacks canonical owner/dtor/EH.
- Fifty-five focused native heads PE-attest below caps; four missing two-byte
  direct JMPs independently decoded. Constructor-bound SmallScore vtable's
  three entries read. The436-head broader family export is still provisional.
- Native unlock getter returns raw byte/full EAX, reference normalizes bool;
  Replay mode also returns full-int rather than bool. Playtime CRT conversion,
  repeated getters/clock and SaveManager checked arrays/lock/EH remain open.
- Retained score46208/0 has28 current/one stale text.hpp hash; completion126976/0
  has13 current local hashes excluding inherited dependencies. Full driver/hooks/
  normalization/writers audited; no Windows CPU oracle/writer executed and no
  executed-build identity. Shared49152 Progress checks not double-counted.
- REF032 component registration and review writer already executed ONCE;
  NEVER RERUN. All REF031/older writers also executed. Preserve frozen src/probes
  during serial compiler reuse/rebuild; current149 canonical/43 ref receipts.

Continue remaining510 Overlay/HUD implementations and their full fixtures,
report/owner/control-flow/table/grammar review. This family originally totals672;
compilation alone closes none of its remaining bodies. Then Gameplay1019/ECL144,
Sprite540/StageBackground121 and183 support bodies. The exhaustive goal remains
active:2,517 bodies /46 grammar files pending. No subagents/concurrent MSVC builds.
English maintained text, repo-python and gpt-6.1-sol commits/public push authorized.

## REF-031 — 2026-10-07 — Player / Bomb / Item batch complete

All884 implementations individually reviewed:1 absorbed /221 nonexact /662
support, across101 fully read source files. Global4,265 terminal /2,679 pending
of6,944. Eight grammar files/27 sites reconciled; gaps65 complete /48 pending.
Exhaustive goal active. See REFERENCE_PLAYER_BOMB_ITEM_REVIEW.md.

- Two more natural Motion members add184 bytes: update47A1F0/28 and bounds
  47A400/156. Complete146-unit cold replay /38objects /9,887bytes passes.
  Source146/pending origins85/library4; authored57/4,074 unchanged. Underlying
  velocity/position dependencies remain undefined, actual72-byte owner retained.
- Full-int bounds ABI independently confirmed by Orb EAX caller; strict edges,
  unordered comparisons and receiver preservation covered. C++20/UBSan tests
  observe update dependency order and boundary/lattice/IEEE behavior.
- All52 original production TUs freshly compile after final source freeze.
  Static/external symbols/all real overloads and31/16/10 callback wrappers plus
  merged dispatchers yield434 complete comparisons:420 size differences,
  two mismatches,12 structural matches. Actual Bomb owners/vtables/EH unclosed.
- Native341 heads uncapped; large42B5D0 expanded,62 missing direct-JMP ranges
  independently decoded/PE-attested. Six constructor-bound vtables and three
  callback tables expose87 observed slots; rejected extents/tables not shortened.
- Reports/recipes/fixtures/writer fully audited, none executed. Player duplicate
  1,032,161 reports bind81 current hashes,2,754 source-only assertions. Item
  287,824 binds33 current/one stale rewards.hpp; post-run hash rebinding is not
  executed-binary proof. SharedBomb137,408 is a subset ofSprite2,915,831;
  cancellation digest/389 hashes current. Scoped hooks/domain limits retained.
- Both private REF031 registration scripts already executed ONCE; NEVER RERUN.
  All REF030/older writers also executed. Current final exact/ref receipts bind
  unchanged src/probes; preserve freeze during any serial compiler rebuild.

Continue all remaining2,679 implementations and48 grammar files in related
batches. Next coherent family: Overlay376 / HUD134 / SmallScore74 /
StageCompletion88 =672, following Player weapon/reward/finish dependencies.
Gameplay1019/ECL144 and Sprite540/StageBackground121 form subsequent families;
183 tool/platform/historical support bodies also remain. Do not claim complete
reconstruction from terminal nonexact decisions. Repo-python,
English maintained text, gpt-6.1-sol commits and public push remain authorized.

## REF-030 — 2026-10-07 — Player / Bomb / Item component checkpoint

Seven shared natural value contributions add581 complete bytes: Angle24/50,
normalization187, Motion142, VectorInterpolation97 and IntPoint33/48. Full144
units cold-replay across38 objects /9,703 bytes; authored57/4,074 unchanged.
Source144/pending origins83/library4. All884 related reference entries remain
pending in this batch; global3,381 terminal /3,563 pending, gaps57/56. Goal active.

- Full native extents/calls/PE constants independently audited; all branches
  close. Actual72/84/8-byte owners, no fake Player/Bomb facade. Angle source uses
  strict FP; other source profiles unchanged. Existing shared units replay.
- C++20/UBSan dirty-value, IEEE/bounded-angle/16,001-input congruence and wrapping
  coordinate checks pass. CVTT conversion117/native61 remains unaccepted.
- All52 original production TUs compiled before these source additions with
  actual inherited CMake paths/strict FP; initial receipts now stale. Refresh
  after final source freeze before final COFF evidence. Never edit src/probes
  during serial MSVC builds. All101 source-file/884 body bindings are private.
- Continue remaining Player production/adapters, all fixtures/drivers/writers/
  retained-report bindings, full static/external COFF/native owner/table audit
  and parser gaps; do not default-reject or mark884 terminal merely from binding.
  See REFERENCE_PLAYER_BOMB_ITEM_REVIEW.md and private ref030 resume notes.
- Component registration script executed once; never rerun. All previous
  record writers are already executed. Repository Python uses repo-python;
  English maintained text, gpt-6.1-sol commits and authorized public push.

## REF-029 — 2026-10-07 — Bullet / Laser / Damage batch checkpoint

All413 implementations individually reviewed:3 absorbed /214 nonexact /196
support. The earlier REF-028 recorded two absorptions; REF-029 records the
remaining411, including radius. Global3,381 terminal /3,563 pending of6,944.
Four gap files/six sites reconciled; gaps57 reconciled /56 pending. Goal active.

- New natural bullet_radius485700/18bytes. Full137-unit cold replay /36objects /
  9,122bytes passes. Source137, pending origins76/library4; authored57/4,074
  unchanged. Synthetic50-record dirty/IEEE/nonmutation C++20/UBSan checks pass.
- Actual writable50*344-byte BSS array5C06A8/radius+144 independently follows
  whole401280 initializer38,669bytes/5,126instructions,3415 direct stores and20
  checked memset calls. All4300 literal words independently audited. Production
  storage/initializer undefined; no original literal data copied into source.
- All56 strict-FP original production TUs compile serially after final source
  freeze; current objects/receipts attest.236 unsliced COFF diagnostics:222 size
  differences, one mismatch,13 structural matches. Other12 structural matches
  need actual Bullet/Laser/Type3 owners/vtables/EH, no padded receiver shortcuts.
- All250 native leads below cap;37 missing JMPs independently decoded. Skipped
  nine-byte LEA/CALL/NOP has unclosed ownership. Four constructor-bound34-slot
  laser vtables/136 entries audited; rejected switch/tables remain provisional.
- Full source/header/fixture/include/writer/tool and report-binding audit done.
  Bullet341623/0 and Laser431652/0 bind389 current hashes/shared digest; Laser64
  source-only distinguished. Damage296121/0 has45 current hashes but post-run
  writer rebinding, not executed-binary proof. Historical6/7/11/14 stale hashes
  preserved; shared totals overlap. No Windows CPU oracle/writer executed.
- Type2 ETEX13 checked source differs from native two-command OOB copy; ECL
  local reachability conditional. Damage Bomb inactive/heap-retire domain and
  replaced callbacks/Item events, Bullet whole-hit/resource and original PMR/
  EH/GPU/thread/game ownership remain explicitly open. Read full review.
- Private .analysis/ref029-record.py executed ONCE; NEVER RERUN. It prevalidates
  all411 body/file hashes,56 receipts,137 exact units and four gap records before
  maintained mutation. All REF028/older writers already executed too.

Next coherent batch: player_entity611 + bomb_system83 + item_system190 =884.
Continue every remaining implementation/gap; do not mark the goal complete.
Maintain source freeze during serial MSVC compilation, repo-python invocation,
English maintained text and gpt-6.1-sol commit prefix. Current checkpoint public
gates/authorized push are recorded with its commit; raw artifacts stay ignored.

## REF-028 — 2026-10-07 — Bullet / Laser / Damage component checkpoint

The exhaustive goal remains active. Related413-body batch is underway:
Bullet100 / Laser216 / Damage97. Only two complete geometry predicates have
terminal absorption records here;411 bodies remain pending in this batch.
Global2,970 terminal /3,974 pending of6,944; gaps53 reconciled /60 pending.
Do not equate this component checkpoint with finishing the batch.

- Seven natural components add640 complete bytes: Vector235, ExtendedCommand
  ctor106, ShotParameters106, BulletCommand127, absolute49, circle95, rectangle
 122. Full136-unit cold replay /35 objects /9,104 bytes passes. Authored57/4,074
  unchanged,75 origin-pending/four library/source136.
- Independent native arrays47B740/4C81F0 establish stride64/count14/24; allocator
 47A790 establishes44. Shoot481780 signed short counts+24/+26; opcode24 in47DCF0
  reads script+28, passing to4A8920/4A73F0. Header preserves actual angle-step /
  speed order and natural host pointer width. Real enclosing owners remain open.
- Geometry uses comparison-based absolute retaining-0/quiet-NaN sign, circle<=,
  rectangle strict short-circuit/full dimensions. Independent2.0/sign mask PE
  anchors and existing Timer/Vector3 recovered callees precede canonical replay.
  Portable dirty construction/lattice/nextafter/IEEE checks pass UBSan.
- All56 original production TUs compile strict-FP serially, refreshed after
  final source freeze. Never edit src/probes while compiling. No Windows CPU
  oracle/reference writer run; retained reports and full COFF audits pending.
- Private .analysis/ref028-* retains413 locked body bindings and native/value
  evidence. Body binding is not reading or a terminal review. Continue remaining
 411 individual decisions, complete COFF/native boundaries, table initializer,
  remaining fixtures/writers/report-source bindings and four parser gaps.
- .analysis/ref028-register-components.py is one-shot and already executed;
  never rerun it. It registers seven canonical components and ONLY two reference
  geometry absorptions. Existing REF027/older writers also already executed.
- Concrete deferred easy probes: LaserSegment60 has genuine flags at+38 whose
  representation remains open; CurveNode60 has Angle member+2C and EH4/cookie.
  Do not create array[1], padded giant receiver or inert locals for exactness.

Read REFERENCE_BULLET_LASER_DAMAGE_REVIEW.md; private resume notes enumerate the
remaining reads. Keep batching related work and record difficult cases, without
claiming all413 reviewed. Stable component gates and authorized public push use
the requested gpt-6.1-sol commit prefix.

## REF-027 — 2026-10-07 — Effect / Special State batch checkpoint

All 322 implementations individually reviewed (Effect191 / Special131):
6 absorbed / 133 nonexact / 183 support. Global 2,968 terminal / 3,976 pending
of 6,944; gap files 53 reconciled / 60 pending after eight manual reconciliations.
The exhaustive goal remains active. See REFERENCE_EFFECT_SPECIAL_REVIEW.md.

- Sixteen natural canonical value/member additions,765 complete bytes: actual
  PackedColor4, EffectParameters56 / x86 EffectRequest72, SelectionPulse8 and
  shared Interpolation<byte32/float44> constructors/setters/begin. All129 units
  cold replay across32 objects / 8,464 bytes. Authored57 / 4,074 unchanged;
  pending origins68/library4/source129. No whole Effect/Special owner credit.
- Independent native calls anchor member construction/setters; begin takes live
  const references with observable alias order and raw float copying. Mode
  setter returns signed assignment. Implicit byte/parameter/pulse padding kept.
  Portable C++20/UBSan dirty-padding/256-byte/alias/flags/NaN-bit tests pass.
- All22 unmodified production TUs compile strict-FP serially after final source
  freeze.163 complete unsliced COFF diagnostics:162 size differences, one
  SelectionPulse structural match separately accepted through canonical replay.
- Two missing Ghidra entries independently recovered from actual six-slot
  vtables and approved PE: Converging45C360/2884 bytes/768 instructions/17
  internal branches and Wavering467430/993/277/18. No database mutation.
  Waver4673F0 is deleting destructor, not containing update. Six other analysis
  holes decoded as internal jumps; rejected sample/factory extents remain intact.
- Independently audited15 descriptors32bytes + only8 terminator bytes, and ten
  callback vtables. Native typed arrays, EH4/cookies, handles/sret, callbacks,
  Worker/resource/real allocator and full owners remain open. No fake facades.
- Retained Special116736/0 has32 current/2 stale hashes; Spiral69120/0 has189
  current/15 stale and old shared digest; Additional357860/0 has389 current and
  matching digest. Shared Sprite2915831/0 binds389 current files; Effect485796
  subtotal across266 groups overlaps reports. Writers/native CPU not run.
- Special destructor advances BEFOREfree; native frees first then accesses
  observer. Fixture free only records events, text records LENGTH not content,
  parameter padding masked and SpawnParameters constructor replacedzero-fill.
  Entry initializer/production adapters excluded; no game/GPU/thread acceptance.
- Stable checkpoint gates: target/tracking/reference/progress/public CI, then
  authorized public main push with gpt-6.1-sol prefix. Raw evidence stays ignored.
  Do not rerun .analysis/ref027-record.py or any older record writer.
- Next coherent review batch: Bullet100 / Laser216 / Damage97, following their
  shared pool, RNG, collision and cancellation protocols. Review every body and
  actual owner, compile all real production TUs serially, absorb easy complete
  natural exact components, record hard cases and continue.3,976 remain pending.

## REF-026 — 2026-10-07 — Title batch checkpoint

The exhaustive goal remains active. All 803 Title entries individually reviewed:
66 nonexact / 737 support. Global 2,646 terminal / 4,298 pending of 6,944.
Sixteen Title gap files reconciled; global 45 reconciled / 68 pending.

- Two new complete exact units add121 bytes: TitleFlags constructor51D9B0/66
  and real PracticeScore member52CA30/55. Cold113/113 across30 objects/7,699
  bytes. Authored57/4,074 unchanged, pending-origin52/library4/source113.
- Real four-byte flags preserve upper28; ctor caller+58D4 and main/frame/Replay
  consumers independently read. Predicate uses signed bytes9 then8 on existing
  sixteen-byte record; independent stage/draw callers establish owner/ABI.
  Whole Title ctor and guarded whole-Profile query remain nonexact.
- Portable dirty flag/Replay-bit checks and all65,536 signed-byte pairs pass.
  Source frozen before final113-unit cold replay. Subsequent candidate builds
  are serial; do not edit src/probes while compiling or invalidate receipts.
- Fifty actual CMake production TUs plus one standalone Sprite fixture probe
  compile;65 complete COFF diagnostics reject. Standalone macro comes from its
  actual recipe, not native execution evidence. 28 internal jumps in thirteen
  native heads independently decoded; no trimmed spans or solved anchors used.
- Handle arrays8/32/139 natural33/33/36 versus native75/75/78; EH4/cookies/
  templates unresolved. Shade105-byte thiscall/RET12 differs from free helper.
  Actual Title0x5978 with Cursors/Worker/mesh/resources remains unclosed.
- MainCPU296/sharedDraw389/parser23 input bindings current; nameDraw has two
  stale, heap-tail one/stage eleven. Replay16 log hashes verified (14returns/
  two AVs); five post-run source hashes are not build binding. Save12 inline
  logs match, no hashes/binary binding. No native oracle/report writer run.
- Full parser/enumeration/format/save/draw/keyboard/page flows and tools read.
  Independent238 data checks do not grant code credit. Raw owner/Env/CRT/thread,
  malformed varargs/heap-tail/error/GDI/GPU/game behavior remain open.

Next related batch: effect_system191 + special_state131, then all remaining
implementations and parser gaps. Details: REFERENCE_TITLE_REVIEW.md.
Private `.analysis/ref026-record.py` already executed; never rerun it. Earlier
checkpoint counts are historical. Keep Ghidra and compiler operations serial.

## REF-025 — 2026-10-07 — Progress and Replay batch checkpoint

The exhaustive goal remains active. All 145 entries individually reviewed:
3 absorbed / 69 nonexact / 73 support; global 1,843 terminal / 5,101 pending.
Two member-pointer gap files reconciled; global 29 reconciled / 84 pending.

- Six new complete exact units, 986 bytes: Replay header, CR/ST header, score
  and practice values, Replay input reset/update. Cold 111/111 across 29 objects,
  7,578 bytes. Source 111/pending-origin 50 / library 4; authored 57 / 4,074 unchanged.
  Original names/origins pending; no authored constructor inference.
- Real 48/12/40/16-byte values use implicit padding; retained two-byte blocks
  inferred from constructor clearing, field meanings still unknown. Existing
  704-byte InputButtonState now distinguishes individual Replay scalar fields
  from two 32-word history arrays. Independent fill 50A030/index 414580 anchors.
- Portable padding/state tests cover all 32 bits/80 frames/release/reset/unsigned
  wrap and unrelated physical input retention. Source/profile frozen before
  final 111-unit cold replay; no repeated builds needed absent further edits.
- All 16 unmodified production TUs compile strict-FP serially; 68 complete COFF
  diagnostics differ. One omitted factory JMP decoded; missing virtual 508F70
  independently decoded as 598 bytes/175 instructions. Automatic other extents
  remain provisional; no prefix credit. Callback/priorities independently read.
- Native append returns int32, reference bool/one-byte tests differ; native
  arrays/link templates, separate rewind members, EH/base/Configuration/
  PlayerTable/allocator ownership unresolved. Do not create raw giant facades.
- Retained Progress 99312/0 and Replay 35840/0 reports lack execution/source hash
  binding. Progress module 31 hashes:28 current / 3 stale; Replay build manifest
  absent. Demo 11 hashes current and supplied th20.dat matches recorded archive
  digest; retained verifier missing. No new native CPU or demo execution.
- Full file/load/save/merge/compression/source/oracle/writer flows read. Data
  independently checked: 113 defaults/17 strings/18 character pointers/5 ranks.
  Invalid-input guards, native thread timing/CRT/heap/OS failures/full gameplay
  remain open. Writers not run; never refresh hashes to imply execution.

Next related batch: title_system 803, then all remaining implementations/gaps.
Private .analysis/ref025-record.py already executed; never rerun. Archive notes
143/144 subsequently corrected in ledger after supplied archive attestation.
Prior checkpoints are historical; compiler and Ghidra work stay serial.

## REF-024 — 2026-10-07 — Pause and Stone Menu batch checkpoint

The exhaustive goal remains active. All 368 entries individually reviewed:
six absorbed / 60 nonexact / 302 support; global 1,698 terminal / 5,246 pending.
Four gap files (16 errors) reconciled; global 27 reconciled / 86 pending.

- Nine new exact units: real Cursor destructor/snapshot/full-int predicates/
  setters/save/restore and real four-byte PauseFlags construction. Cold replay
  105/105 across 27 objects, 6,592 complete bytes. Source 105, pending-origin 44,
  library four; authored 57 / 4,074 unchanged. All nine origins/spellings pending.
- Cursor owns PMR vector<int> and two std::stack<int,std::deque<int>>. Real proxy,
  allocator and adapter call graphs independently establish 0x4C storage; native
  release deque still owns _Container_base12 proxy. No handmade DequeStorage.
  Constructor remains nonexact (native138, natural96, EH probe156); original EH,
  whole menu construction/library runtime and linkage remain unaccepted.
- Public semantic tests cover 4,096 growing/unwinding frames, empty restore,
  signed predicates, unrelated fields, PMR release and dirty flag upper bits.
  Source/profile frozen before final105-unit cold replay.
- All24 original production TUs compile serially with declared strict-FP recipe;
  53 complete COFF diagnostics differ. Fifteen Ghidra gaps contain16 JMPs decoded
  independently; switch tables of rejected large members remain provisional.
  Pause registration15/95 and callbacks4E6520/4E66A0 independently read.
- Full Pause/Stone state machines, resources, lifecycles, fixture/driver/include
  and writer bodies read. Data checks:16floats/10strings/name pointer/fourPause
  tables and88Stone pointer/length records. Invalid-resource policy differs.
- Historical PauseCPU114688/0 has four stale hashes; Stone110128/0 has input.hpp
  stale and missing stocktext. PauseDraw81920/0 has389 current hashes/shared digest
  but overlaps larger sprite report; initial196-failure report retained. Do not
  refresh report hashes to imply execution. No new native CPU compile/run.
- CPU raw owners/normalized pointers, host stringstreams, recorded sideeffects,
  cachedJobs/FNVtext/effectpadding masking/valid fixture domains do not close
  original allocator/EH/file/audio/GPU/wholegame behavior. Pause update return
  discarded and entire menu protocol intercepted in its CPU driver.

Next related batch: progress_state79 + replay_system66, then title_system803 and
all remaining implementations/gaps. No default module-wide rejection. Private
`.analysis/ref024-record.py` already executed; never rerun. Earlier checkpoints
are historical. Keep compiler builds and Ghidra operations serial.

## REF-023 — 2026-10-07 — Options and Key Config batch checkpoint

Exhaustive goal remains active. User requests related batches; all109 Options/Key
entries now have individual hash-bound decisions:28 nonexact/81 support.
Total1,330 terminal/5,614 pending of6,944; gap files23 reconciled/90 pending.
Both full drivers, owner headers, seven production TUs, shared menu draw fixture
and report writer read. Two Options cdecl parser gaps manually reconciled.

- New exact Timer greater_than461070/46 on existing16-byte owner. Cold96/96,
  25 objects/6,180 bytes; source96/pending-origin35/library4. Authored57/4,074
  unchanged; original spelling and origin pending. Signed-edge tests extended.
- All7 unchanged reference TUs compiled serially with declared strict-FP recipe;
  23 complete COFF diagnostics differ. No prefix or table-truncated acceptance.
  Native large switch tables/allocator/member partitions remain open.
- Eight Ghidra gaps/nine JMPs decoded independently:4E042E/4E0433/4E0497,
  4E10B3,4C5893,4C758F/4C76A4,4C6647,4C7CE3. Database/target unchanged.
- OptionA4/Key114 base/Cursor/Timers/Vector3/vptr/diagnostics/EH/storage observed.
  Key ctor clears96bindingbytes with32-byte strides, copies16bytesperrecord.
  Cursor owns real vector16/two deque20 records; proxy/map/allocator lifetime
  remains open. No fake owner added to accept callbacks or state setters.
- Independent307strings/17floats/9pointertables/allowed72 exact data observations.
  Native volume signedbyte/music-based attenuation; source boundary differs.
  Original save return/path/CRT/errorargument differs; no disk acceptance.
- Historical Options393216/Key229376/sharedDraw18432,all0failure;13/12/25 current
  hashes. Crucial limitation: record_menu_evidence.py attaches current hashes
  after CPU execution without binary binding/re-execution. Script not run.
  Full transitive/build inputs absent. No new native CPU oracle compiled/run.
- Rawowners onlyCursorconstructed,Keyslot0/historypreallocated,drawcachedJobs;
  sideeffects recorded. Both native Key page draws returnint1 versus sourcevoid;
  fixtures discard native page results. Draw18432 already included inText57113.
  No full startup/lifetime/player2/heapgrowth/error/device/audio/file/GPU/game proof.

Next related batch: pause_system + stone_menu, including Cursor/history protocol,
then every remaining5,614 implementation and90 gap files. Never mark the goal
complete with pending entries. `.analysis/ref023-record.py` already executed;
do not rerun it. Shared source/profile frozen before96-unit cold replay. Earlier
counts below are historical. Keep MSVC and Ghidra operations serial.

## REF-022 — 2026-10-07 — Text renderer batch checkpoint

Exhaustive goal active. User requests faster related batches; each indexed body
still requires its own hash-bound decision. All129 text_renderer entries are
terminal:63 nonexact/63 support/3 absorbed. Total1,221 terminal/5,723 pending of
6,944; gaps22 reconciled/91 pending. Entire driver/header adapters/menu include
read, four WINAPI gaps reconciled. Do not mark the exhaustive goal complete.

- Six new exact contributions: TextLine ctor46ABA0/219, overlap470920/72,
  IntPoint ctor40DE00/33, IntRectangle ctor40DE30/53, outline scale416CF0/18,
  Vector3 *=429690/77. Cold95/95,25 objects/6,134 bytes. Authored57/4,074;
  source95, pending-origin34/library4. Only outline setter adds authored credit.
- Actual Line320 constructs char256,Vector3 and individual fields; count/stride
  independently observed in46A6B0. Atlas returnPoint8 and Job rectangle16
  independently establish two value owners. No fake Renderer/Bitmap facade.
  Overlap uses unsigned endpoint arithmetic, signed comparisons and inclusive
  edges; public independent lattice/overflow checks pass UBSan.
- Independent global5AE120 initial1 and raster consume/reset anchor; original
  core/grpfont.cpp links authored producer. Vector3 *= actual three-float member
  is invoked by original Line commit; full scalar contribution/RET4 retained.
- All13 original production TUs compile with declared strict-FP/transitive
  includes.56 COFF comparisons retained; fallback104/character72 structural
  candidates lack closed real owner/callee partition, no exact credit.
- 75 unique native entry exports; main decompilations/selected leaves read.
  JMP46DF27->46DF45 and47108F->471096 separately decoded. Switch-bearing
  diagnostic native sizes are instruction spans, not accepted table extents.
- AsciiInf1A360/Job684/Bitmap124-hex ownership, Animation/PMR/ClockScalar,
  RTTI/EH/allocator/lists/GDI/COM partitions remain open. Native draw_jobs int0
  versus sourcevoid, FPS actualreceiver/int1 versus sourcefreevoid are recorded.
- Retained57113/0 binds targetSHA;45/46 source hashes current, format.cpp stale.
  Driver/menu include hashes current; test_environment/full build inputs absent.
  Included menu18432 leaves38681 text observations. Full read captures precise
  fixture scope and two native-call ABI mistakes; no CPU oracle compiled/run,
  no GPU/startup/whole-owner/error/concurrency claim. See full REF-022 review.

Next batch: options_system + key_config, then remaining5,723 bodies/91 gap files.
`.analysis/ref022-record.py` already executed; never rerun it. Latest ledger
polish corrected draw0 to470530 (4710F0 is floating conversion), native diagnostic
sizes and source hash scope. Source/profile frozen before95-unit cold replay;
earlier counts below are historical. Preserve serial MSVC/Ghidra discipline.

## REF-021 — 2026-10-07 — ScreenEffect batch checkpoint

Exhaustive goal active. User requests related functions/modules in batches;
retain individual body-hash outcomes and serial compiler/Ghidra discipline.
All43 Screen entries reviewed:17 nonexact/26 support. Total1,092 terminal/
5,852 pending of6,944; gaps21 reconciled/92 pending. CPU driver fully read;
seven WINAPI annotations reconciled without changing reference source.

- Three new complete exact shared contributions: Timer fraction423BD0/17,
  signed <=423590/46, actual20-byte ColoredVertex ctor423470/43. Cold89/89,
  twenty-two objects/5,662 bytes; authored56/4,056 unchanged, source89,
  pending-origin29/library4. Original spelling/origin pending for all three.
- Vertex is actual typed Vector3 + reciprocal-w12/color16. Native rectangle
  array helper count4/stride20/ctor423470 and FVF44/stride20 establish complete
  value owner. Existing Vector3 zero ctor422E10 anchor observed before probing.
  No fake Screen/Game/Renderer facade, padding, inert locals or body copying.
- All native17 main functions and relevant15 leaf-query addresses read;
  seven extra actual entries decompiled. Main17 instruction bodies have no
  holes. Initialization637 code +3 padding +40 jump-table bytes =680 contribution.
  Native44 ScreenInf ctor187/dtor121 retain base/vptr/EH/diagnostics; factory
  wrapper39/factory81/allocator65 and shutdown29 remain separate. Reference
  changes callback wrappers and invalid-mode behavior. Full owner remains open.
- Seven updates180/239/221/264/82/1040/1318; four draw callbacks128/172/105/202;
  rectangle1407. Reference compiler complete sizes all17 differ; preserve no
  prefix matches. All four original production TUs compile with declared public
  include paths; no original CPU oracle compiled/run.
- Native linear zero-Y uses camera3point2 at5C553C, nonzero point0Y5C552C;
  reference preserves it. Envelope mask0x77/tail unsigned conversion and actual
  two RNG stream1 calls checked. Four camera writes use stride16C/point8.
- Retained124288/0 report verifies seven current source hashes and counts
  7*4096*4 +640*5 +5*320*4. Full normalized68 owner/DE8 Graphics/RNG28,
  recorded COM/vertex bytes/selected caches and normal lifecycle corroborated.
  Report omits target/driver/dependency/toolchain hashes; SHA assertion in
  driver alone cannot restore full historical build binding. Factories/shutdown,
  invalid modes/heap failures/GPU/startup/concurrent or exception cleanup open.

Next batch: text_renderer, then all remaining bodies and92 manual gap files.
`.analysis/ref021-record.py` already executed; do not rerun. C++ source/profile
frozen before final89-unit cold replay. Earlier counts below are historical.

## REF-020 — 2026-10-07 — Trophy batch checkpoint

Exhaustive goal active; continue coherent batches with individual body-hash
decisions. All49 Trophy entries reviewed:20 nonexact/28 support/1 absorbed.
Totals1,049 terminal/5,895 pending of6,944; gaps20 reconciled/93 pending. Both
Trophy oracle WINAPI gap files fully read and reconciled without source edits.

- Three new complete exact units: shared text decoder52F060/106 bytes,
  Message id reset52F590/20, Timer integer assignment423520/26. Cold86/86,
  twenty-one objects/5,556 bytes; authored56/4,056, source86, pending-origin26,
  library4. Natural shared source; no reference/decompiler body copying.
- Actual Message704 record has id0/title4/description104, seven256-byte rows.
  Decoder actual result5C6860 is shared/nonreentrant, valid encoded NUL within256
  bytes. Closed-form-key portable tests cover all256 lengths/high bytes/wrap/
  untouched suffix and pointer reuse. Reset preserves1792 string bytes.
- Timer assignment preserves actual void/RET4/call423F80. Origin/operator name
  pending. Integer += still33 vs31; no shaping or shortened comparisons.
- Full Trophy54 owner, checked PMR deque24/proxy8, Timer38/three typed handles48
  and all50 relevant original functions queried/decompiled/read. Six original
  production TUs compile using actual public sprite/ECL/binary include paths.
  No original CPU oracle compiled/run. Omitted JMPs52E4B1/52E4CD/52F97C decoded
  and retained in full1308-byte resource initializer/165-byte factory extents.
- Original pop is indexed; source only front-pop. SaveManager achieved returns
  full EAX0/1, checked128-byte array; source bool/free wrappers remain nonexact.
  Original resource release returns int0 versus void. PMR encode takes owned
  28-byte string by value, not a raw char pointer. State2 deletes three handles
  then retires actual owner without ticking; callable completion chain runs
  46EBB0 ->46A4B0 ->empty40E5E0 through two distinct eight-byte callable types.
- Retained295,327 codec/queue checks have exact target/asset hashes but no
  report source hashes; oracle/build/source_hashes.json absent.41 records/287
  source-encoded rows merely decode with native helper, not native parser
  equivalence. Retained34,404 owner/frame subset validates28 shared counters,
  389 current hashes; historical612 failures bind316/335 current hashes.
  256 dirty ctor/cache-init/dtor and2,048 full frames execute actual deferred
  GDI/COM text tasks,612 pixel buffers; host font/preloaded bounded ANM/normalized
  pointers/synthetic locks/PMR/manual cleanup constrain conclusions. Save,
  preload/file I/O/factory failures/full scheduling/concurrency remain open.

Next batch: all43 screen_effect entries, then remaining modules and93 gap files.
`.analysis/ref020-record.py` already ran; do not rerun. Source frozen before
final86-unit cold replay. Earlier checkpoint counts below are historical.

## REF-019 — 2026-10-06 — Ending and shared-owner batch checkpoint

The exhaustive goal remains active. User now requests coherent batches; keep
individual hash-bound decisions while compiling and replaying related owners
together. All 39 ending_scene entries are reviewed: 22 nonexact/17 support.
Total 1,000 terminal/5,944 pending of 6,944. Gaps remain 18 reconciled/95 pending;
Ending has none. Complete sources/fixtures/reports read, 66 relevant original
functions queried/decompiled. All six original production TUs freshly compile
with corrected transitive sprite/ECL/binary includes. No reference oracle run.

- Eight new canonical exact contributions, 270 bytes: Timer ctor54/current17/
  remainder25/subtract28/post-increment22/post-decrement24, input current21/
  held79. Natural shared bodies, independently observed original call anchors.
  All six Timer origins and original operator spelling pending; input adds two
  authored members. Cold 83/83, twenty objects/5,404 bytes; authored54/3,930,
  source83/origin-pending exact25. Dirty/sentinel/signed/step/bit31 tests pass.
- Timer integer += maintained dependency remains nonexact, 33 vs31 bytes/extra
  XORPS. Subtraction preserves modulo unsigned negation; postfix dummy argument
  and native member boundaries retained. No shaping or shortened extent.
- EndingInf28/ScriptF0 actual typed arrays/Timers/Vector3/Worker16 corroborated;
  full owner, allocator/base/diagnostics/PMR/EH/teardown remain open. Native
  VM4,107 instruction bytes plus18/4 jump tables. Independently decoded omitted
  JMPs4A048B/4A103F retained in full update/factory extents.
- update_script actual int0/1; retained cpu<bool> widens only one byte. Native
  metadata32-byte index helper has a bounds check; no false unchecked claim.
  Resource flag mutations native plain stores versus source atomic_ref.
  Worker callback reloads active owner at execution; full launch/lifetime open.
- Distinct ordinary/ruby PMR closures and actual captured Animation event2
  completion chain traced through4A0C20/49EA50/49F1E0/4888E0/477450/42B5D0.
  All23+5 names/three floats/two strings independently match. Four tables each
  six slots then RTTI locator or392.0, not seven functions.
- Retained200,618 subset matches44 counters/shared report hash and389 current
  source hashes; no fresh original oracle. Actual text tasks/deferred uploads/
  GDI/COM recording/ANM completion run historically in1,024 fixture programs,
  1,706 pixel comparisons. Host fonts/synthetic locks/pool/PMR/valid indices,
  normalized Screen graphs and manual cleanup limit conclusions. Opcode7 and
  non-gallery12, init/owned Ending dtor/file unload/active threads excluded.
  Historical659 sound failures have328/343 current hashes, not current failures.

Next coherent batch: all49 trophy_system entries, then every remaining body
and95 manual gap files. `.analysis/ref019-record.py` has already run; do not
rerun its guarded append transaction. Source frozen before final cold83 replay.
Earlier checkpoint totals below are historical.

## REF-018 — 2026-10-06 — Card review checkpoint

The exhaustive goal remains active. All32 card_system implementations have
individual decisions:17 nonexact/15 support. Total961 terminal/5,983 pending
of6,944. No Card parser gaps; global18 reconciled/95 pending of113. All sources,
headers, extractor/constants, six full fixture fragments, recipes and reports
read.49 relevant native functions independently queried and decompiled. Seven
original production TUs freshly compile after transitive include-path correction.

- Actual three-float Vector3 owner naturally restores zero/coordinate constructors,
  subtraction, scalar multiplication and add assignment:46/54/88/80/85 bytes.
  Independent coordinate-ctor anchors, hidden sret/reference/RET ABI, no shaping.
  All five origins pending; authored52/3,830 unchanged. Cold75/75 across20 objects,
  5,134 bytes/source75/exact-origin-pending19. Dirty/sentinel/bit/alias tests pass.
- Full CardC8 owner remains open: typed five handles, Timer, base, Vec3, PMR/EH/
  diagnostics differ from aggregate reference. Encodervoid member105/RET8 versus
  pureint function; checksum member148 returns fullint, fixture comparesbool only.
  No fake padded Card/record/Background/Renderer or merged member accepted.
- Full update875/draw797/finish602/start1896/post-frame645/init121/factory92
  instruction extents checked. Independent unreachable JMP488B53 included.
  Fallback getter+8A460 corroborates current.profiles[18], not backup.
- Actual title PMR closure and completion chains traced through44B020 and typed
  info handle short event4. Start oracle queues/clears without executing them;
  portrait files=-1. Finish omits all113 achievement40. Record/owner origins open.
- Eight floats/three doubles/text stem/five render strings independently match.
  Completion six slots then0.05 float; fmod dispatcher mixed metadata/function
  block, not vtable.543310/543320 signed32/x87 conversion checked; intrinsic
  value equivalence does not establish FP flags/feature/helper ABI.
- Retained206,784 subset counters/hash checked,389/389 source hashes current;
  no native oracle compiled/run. Normalized constructor/scheduler addresses,
  synthetic ANM/locks/valid indices/eight isolated replay records and deterministic
  QPC limit conclusions. No hardware IDIV trap/factory/GDI/portrait/replay I/O
  lifetime acceptance. Historical timing failure46/23cases,280/302 hashes current.

Next coherent family: ending_scene39, then every remaining implementation and95
manual gap files. Private `.analysis/ref018-*`; earlier counts are historical.

## REF-017 — 2026-10-06 — Notice review checkpoint

The exhaustive goal remains active. All30 notice_system implementations have
individual decisions:13 nonexact/17 support. Total929 terminal/6,015 pending
of6,944. One full five-line fixture header reconciles two WINAPI gaps; global
18 reconciled/95 pending of113. Complete sources/headers/extractor/constants/
fixtures/recipes/report read;42 relevant native functions queried and decompiled.
Both original production TUs freshly compile after include dependency correction.

- Natural actual four-byte AnimationHandle constructor425CC0 adds23 complete
  canonical exact bytes. No relocations/shaping/padding; origin remains pending,
  no authored increment. Cold70/70 across19 objects/4,781 bytes; source70,
  authored52/3,830, origin-pending exact14. Dirty zero plus sentinel test passes.
- Full130-byte Notice owner remains open. Typed seven-handle array/Timer/Cursor/
  base construction, allocator factory/selected setter and teardown differ from
  aggregate reference. Accepted value constructor does not accept whole Notice.
- Seven NUL strings/all50 native PMR constructor bindings independently match.
  Source default array/move assignment and native CRT/EH/lifetime differ. Fixture
  constructs native table from source messages; no CRT initializer acceptance.
- Completion extractor overreads: actual six function slots, seventh following
  RTTI locator/string word. Empty invoke corroborated; five callable/EH protocols
  remain open. Draw thunk49DEA0→16-byte ECX-saving member478BF0 is not literal
  free return1. No fake layout-free class/ABI identity credited.
- Full update2,379 bytes and4/8 jump tables checked; independent unreachable
  JMP4DF285 retained. Native unchecked Cursor99/message table versus source
  index exception; Stone names stride1024 matches valid source rows. Image
  substate3, typed interruption, text/texture/Worker owner protocols unclosed.
- Retained59,904 subset bound to shared report/hash/counters,389/389 current
  source hashes; no new CPU oracle run. Vptr/proxy/callback/graph normalization,
  synthetic ANM/Stone/PMR/COM/locks/fonts and valid rows limit conclusions.
  No async, factory, failed I/O, loaded teardown or GPU/device lifetime checks.

Next coherent family: card_system32, then every remaining implementation and95
manual gap files. Private `.analysis/ref017-*`; earlier counts are historical.

## REF-016 — 2026-10-06 — Help review checkpoint

The exhaustive goal remains active. All25 help_system implementations reviewed:
15 nonexact/10 support. Total899 terminal/6,045 pending of6,944. Global gaps
17 reconciled/96 pending of113, no Help gaps. Full source/header/recipe/status
read;26 relevant original functions queried and decompiled. Both original TUs
freshly compile after declared/transitive include-path recipe correction.

- Natural Timer::less_than423560 adds46 complete exact bytes, thiscall/bool/
  RET4, no relocations. Cold69/69 across18 objects/4,758 bytes; authored52/3,830,
  source69. Signed-edge and byte-preservation tests pass. Source frozen first.
- Actual draw thunk49DEA0 calls16-byte member478BF0; reference literal-return
  comment/direct free body merges native partition. No fabricated owner/ABI.
- Native image load owns410AA0 output directly; source vector/second allocation
  differs. Both detach paths set close flag true then detach; Worker/D90 address
  corroborated but actual launch argument/tracked guard/global lifetime open.
- Texture update Controller thiscall/int0/RET24 differs from free void source.
  Format map consults Graphics; first nine BPP values all4, no false mismatch.
  Native static D3DX import vs source lazy library; error/module lifetime differs.
  Clear original uninitialized surface versus source null output; typed owner open.
- Original update2072 instruction bytes plus six-pointer jump table inspected.
  Independently decoded three unreachable JMPs omitted by Ghidra at4BF4A3/
  4BF662/4BF70F; full extent retained, no prefix/padding exclusion.
  Three strings and two nine-entry table prefixes independently read. Historical
  compiled-only status8/8 current hashes; no native Help CPU/thread/COM/GPU run.

Next coherent family: notice_system30, then every remaining implementation and
96 manual gap files. Private.analysis/ref016-*; earlier counts historical.

## REF-015 — 2026-10-06 — stage-clear review checkpoint

The exhaustive goal remains active. All17 stage_clear implementations individually
reviewed:11 nonexact/six support. Total874 terminal/6,070 pending of6,944.
No family gaps; global17 reconciled/96 pending of113. Complete production/
header/extractor/constants/fixtures/recipes/reports read;33 native functions
queried and decompiled. All four original production TUs freshly compile;
declared runtime_state/ECL include dependency added to diagnostic recipe.

- Natural Timer::at_least/equals restore original signed current predicates,
  thiscall/bool/RET4,46 complete bytes each. No relocations/shaping/padding.
  Full cold68/68 across18 objects/4,712 bytes; authored51/3,784,source68.
  Portable signed-edge and complete-byte nonmutation checks pass.
- Reference StageClear construction/lifetime/factory/scheduling, Player getter
  partition, Session score receiver and Renderer setter graph remain nonexact.
  Specific records for every implementation; no fake original class declarations.
  Update row retains nonexact despite two accepted adjacent Timer helpers.
- DATA8floats/6NUL strings independently match. Retained95,232 subset checks
  bound to actual shared report/counters,389/389 hashes current. No new native
  oracle execution. Factory/I/O, owned destruction, self-deleteage10 and new
  text/GDI/GPU excluded. Freeze failure220/260current of280hashes,20stale.
- Source/probe tree frozen before complete replay; ledger/docs follow without
  invalidating receipts. Reference checkout unchanged. Private.analysis/ref015-*.

Next coherent family: help_system25 entries, then every remaining implementation
and96 manual gap files. Historical checkpoint totals below are not current.

## REF-014 — 2026-10-06 — game-session review checkpoint

The exhaustive goal remains active. All21 game_session bodies individually
reviewed:13 nonexact/eight support. Total857 terminal/6,087 pending of6,944.
No family gaps; global17 reconciled/96 pending of113. One original production
TU freshly compiles; complete source/header/CPU driver/recipes/reports read.
22 native functions queried and21 decompiled through attested wrapper.

- Constructor free/memset/fill loops differ from native thiscall/receiver
  return/array helpers; reference explicit padding/grouped words do not close
  typed Player/Context/PlayerTable/Session owners. MOVSD+2B0 is evidence for
  floating storage, requires consumer proof. No fake layout or new exact credit.
- Getter partition: Session context30 stride, Session->PlayerTable and Player
  F0 stride. Native primary/overlay return stored pointers, source returns
  references to pointer fields. Original setters/counter receive actual owners
  in ECX; reference convenience wrappers change ABI/global/lifetime partition.
- Native continue count ADD precedes signed clamp0..9. Clamp helper's Ghidra
  _Find_unchecked label is misleading; actual call chain/comparator checked.
  Five historical alias checks are source-only, not native getter validation.
- Retained14,342 passes14337 native/five source only, module4/4 current hashes.
  CPU driver not compiled/run; report not inherited. REF-013 CPU-driver note
  corrected to read-only; audio compilation includes seven production TUs and
  backend smoke (eight total), not the CPU driver. Source unchanged,66-unit
  cold replay remains current; authored49/3,692/full4,620 bytes/18 objects.

Next coherent family: stage_clear17 entries, then every remaining body and96
manual gap files. Private `.analysis/ref014-*`; earlier counts historical.

## REF-013 — 2026-10-06 — audio-runtime review checkpoint

The exhaustive goal remains active. All122 audio_runtime C++ bodies are
individually reviewed: four absorbed,63 nonexact,55 support. Inventory6,944;
terminal836/pending6,108. Four manually reconciled WINAPI gap files bring
global totals to17 reconciled/96 pending out of113.

- Natural Request/Command/Channel constructors55/65/73 and Channel release46
  add239 complete canonical bytes. The three constructors retain unknown
  authored/compiler origins; only release adds authored credit. Real typed
  records and SDK pointer, no padding/assembly/decompiler body imported.
- Cold66/66 across18 objects/4,620 bytes. Authored49/3,692; source-present66;
  origin-pending exact13. Portable dirty-storage semantics pass, no COM runtime.
  Source frozen before full replay; documentation/ledgers do not invalidate it.
- Full source/header/constants/test/recipe/report reading; all eight original
  TUs freshly compile serially.78 native functions independently queried and
  decompiled. Both memset anchors independently established before probing.
- Native ready/int, initialization-1/1/0, Channel ECX creation, Graphics preload
  predicate, CSound/CStreaming split owners, partial WaveReader initialization,
  S_FALSE restore/no-notification error, primary-format null/failure handling,
  fixed globals/plain thread busy differ from reference. Every hard body has
  its own record. Natural stop100/120 and DeviceOwner dtor93/88 deferred.
-90 definitions,72 filename strings,five floats independently match PE.
  Historical31,219 CPU cases/zero failures have12/12 current source hashes,
  but exclude real startup/thread/driver/audio and skip allocation/join stages.
  No backend report present; neither oracle rerun or inherited. Checkout clean.

Next coherent family: game_session21 indexed entries, then all remaining bodies
and96 manual gap files. Private `.analysis/ref013-*`; earlier counts historical.

## REF-012 — 2026-10-06 — startup-scene review checkpoint

The exhaustive goal remains active. All 49 startup_scene implementation entries
are individually reviewed: 45 C++ and four Python entries. Decisions: two exact,
eleven deferred, 36 support. Inventory6,944; terminal714/pending6,230. No family
parser gap; global gaps13 reconciled/100 pending out of113.

- Shared-resource init/release134/62 bytes add196 authored bytes. Preserve eight
  ordered calls each, original zero-helper calls, immediate -1 exits without
  rollback, stone release's observed zero argument and full int HUD/trophy ABI.
  All16 REL32 anchors derive from independently queried original dependencies.
- Full cold62/62 across16 objects,4,381 full bytes. Authored48/3,646;
  source-present62. Source owner SceneResources has declarations only for
  dependencies; no whole resource owner, linkage or native loading runtime claim.
- Pure portable tests cover three null-factory paths, trophy failure, early
  stopping and full teardown order. Original resource/API code not executed.
- Full source/headers/scripts/fixtures/CMake/reports read;37 native functions
  independently queried,32 decompiled. Both production TUs freshly compile.
- LoadingInf animation/base/Worker/diagnostic allocator lifetime remains open.
  Source changes typed handle/member partition, thread callable argument,
  readiness atomics, chrono slot method and original shutdown's thiscall ABI.
  Four startup DATA declarations independently compare against locked target.
- Retained startup report4/6 hashes current2stale; named-spawn4/4 current.
  Evidence script refreshes hashes without CPU execution. Retained4096/24576
  checks attest selected fixture scope only; actual named_spawn implementation
  still awaits sprite_renderer review. No reference checkout mutation/tool run.

Next coherent family: audio_runtime122 indexed C++ entries, then all remaining
native/script bodies and100 manual gap files. Continue individual decisions and
absorb easy exact work. Private `.analysis/ref012-*`; earlier totals historical.

## REF-011 — 2026-10-06 — platform/window review checkpoint

The exhaustive goal remains active. All 189 platform_window entries are
individually reviewed: 170 C++ definitions and 19 Python function/module entries.
Decisions: four absorbed, 65 nonexact and 120 support. Inventory 6,944;
terminal 665, pending 6,279. Seven manual gap reconciliations bring totals to
thirteen reconciled and 100 pending out of 113 files.

- Five new canonical authored contributions total 190 bytes: two input queries,
  repeat reset, Japanese locale detection and font enumeration callback.
  Whole window creation remains deferred despite extracting its reset method.
- Cold complete replay: 60/60 units, fifteen objects, 4,185 full bytes.
  Authored exact 46/3,450; source-present 60. Independent caller/import/global
  evidence establishes all relocations. No solved comparison fields promoted.
- Portable semantics cover bit31/raw masks, repeat8 selection, nonmutation and
  counter edges/isolation. OS locale/font APIs not invoked; font pointer storage
  and original initialization remain undefined. No linked window/game claim.
- All twenty unmodified reference production TUs compile serially. Full source,
  headers, scripts, fixtures, resources and reports read; 68 native functions
  independently queried/decompiled through the attested Ghidra wrapper.
- Concrete native differences: dialog return0 paths versus reference1; live
  IsWindowEnabled navigation; snapshot/encoder/data-open int statuses and
  allocator ownership; wall-time pointer return and chrono helper partition.
  Full Graphics PMR/worker/global owner and original SDK calls remain open.
- Forty data declarations match locked PE bytes. Two Japanese dialogs match
  retained original hashes; no fresh resource compilation. Module report has
  23/31 current hashes and eight stale inputs, plus missing link dependencies.
  Historical platform/texture fixture passes were not rerun or inherited.
  Texture evidence tool can refresh hashes without rerunning old CPU results.

Next coherent family: startup_scene's 49 indexed entries, then all remaining
native/script bodies and 100 manual gap files. Keep individual decisions and
absorb easy exact work as encountered. Private `.analysis/ref011-*`; earlier
counts below describe historical checkpoints.

## REF-010 — 2026-10-06 — diagnostics review checkpoint

The exhaustive goal remains active. All seven diagnostics implementation
entries have individual support decisions: three C++ functions, two Python
functions and two complete script modules. Inventory6944, decisions476 and
pending6468. Parser gaps113, reconciled6/pending107. Source55, authored41/3260
and complete canonical55/14objects/3995bytes unchanged; no production mutation.

- Read four implementation files, CMake, four debugger logs, two ASAN reports,
  six state snapshots, three build manifests and source-runtime narrative.
- Minidump tool reads modules only; DIA lookup lacks image/PDB identity and
  uses regex names. Live-state reader assumes x86 source offsets, basename
  identity and separate unsynchronized reads, not a coherent original snapshot.
- Debugger source TU compiles unmodified with pinned x86 compiler. Optional DIA
  SDK header/runtime absent; no DIA compile/link/runtime acceptance. Tools not
  invoked, no process attached or APPDATA/source checkout mutation.
- Retained null/heap/UAF/allocation-mismatch reports are historical source
  observations. ASAN interception compatibility bypass is explicitly incomplete.
  State samples stage1/3 do not prove complete gameplay or whole-state identity.
- Manifests462/463/463 inputs contain15/9/9 hashes stale versus pinned checkout;
  every manifest explicitly denies complete equivalence. No report inherited.

Next coherent family: platform_window189 entries, then all remaining native/
script implementations and107 manual gap files. Each difficult case gets its
own evidence and follow-up; keep advancing exhaustive coverage. Private
`.analysis/ref010-*`. Earlier counts below are historical checkpoints.

## REF-009 — 2026-10-06 — entry/window review checkpoint

The exhaustive goal remains active. All 26 program-entry C++ definitions and
both tools (eight Python entries) have individual decisions: six absorbed exact,
eight native deferred and twenty support. Current inventory is 6,944 entries:
6,706 C/C++ definitions, 152 Python functions/lambdas and 86 script modules in
1,002 files. Decisions469; pending6,475. Gap files113, reconciled6/pending107.

- Eight new canonical contributions341 bytes: five WindowState field methods,
  system restoration, flags default construction and foreground API wrapper.
  Six authored methods add217 bytes; the other124 bytes retain pending origins.
- Cold complete replay55/55, fourteen objects, 3,995 full bytes. Authored exact
  41/3,260; source-present55. Ten exact contributions retain pending origins.
- Independent full Window construction establishes natural0x2138 layout and
  real double+2098. Field methods preserve thiscall and uint32 reset return.
  Restore uses fixed global5B6758, verified USER32 imports and IME thunk54065A;
  no tests invoked restoration or changed OS settings.
- Portable field/isolation/signed-byte/retained-bit checks pass. Original Window
  constructor and global storage stay undefined; no linked/window startup claim.
- Main2537 bytes, frames433/583/370 and CRT argument pushes independently read.
  Source zeroed MSG, free/injected ABI, omitted no-ops and replaced lifetime
  remain deferred. Graphics needs real PMR/config/viewport/jthread declaration.
- Both tools read, not executed. Retained graph22 nodes/194 static edges omits
  indirect calls; retained symbol report is not fresh linkage/runtime evidence.
  All five CP932 constants independently match; none imported into production.
- Script inventory adds238 formerly omitted entries, including whole-file code.
  All6,706 earlier C/C++ rows and435 review bindings remain unchanged. Python
  synthetic offsets/decorator/lambda checks pass. Ten PowerShell files explicitly
  require manual function enumeration; whole-file entries alone cannot close it.

Next coherent families: diagnostics, then platform_window and every remaining
implementation/script/manual gap. Do not treat expanded discovery as review
credit or defer the whole repository behind one difficult owner. Private
`.analysis/ref009-*` and compiler receipts. Earlier totals below are historical.

## REF-008 — 2026-10-06 — runtime-state review checkpoint

The exhaustive goal remains active. All 27 runtime-state definitions in six
files have individual decisions: five absorbed exact, one library exact,
seven native deferred and fourteen support. Current decisions435; pending
6,271 of6,706. Parser gaps remain six reconciled/97 pending out of103.

- Added real28-byte GameRandom owner with actual uint32 standard engine at+4.
  Constructor85, bounded49 and float wrappers113/129 add376 authored bytes.
  Engine constructor29/normalization36 are complete library units, excluded;
  original float receiver setter25 is exact with origin pending.
- Cold complete replay: 47/47 units, twelve objects, 3,654 full compared bytes.
  Authored exact35/3,043; source-present mappings47. Original fixed-global
  next/seed locking remains undefined; do not claim linked sampling.
- Independent startup callers establish four global addresses/ids. Standard
  random header establishes library origin; constants/callees queried before
  canonical anchors. Natural uint32 float casts recover full original emission.
- Portable tests cover defaults/edge seeds, zero/count sampling, high-bit and
  near2^24 conversion, unclamped signed output and scalar bit preservation.
  Deterministic test-only next fixture does not implement native lock protocol.
- All motion/source/oracle bodies read and specific ABI/helper/FP differences
  recorded; native bounds is int, source bool. Real Motion owner/helper/table
  work remains open, including its small combined-update member.
- Two production TUs compile after restoring dependency-propagated include
  paths in the diagnostic recipe. Both retained reports reviewed, not rerun;
  their manufactured startup/FP state and unguarded output paths are recorded.

Next coherent family: program_entry's 26 definitions, followed by every
remaining implementation and manual parser gap. Private evidence:
`.analysis/ref008-*` and compiler receipts. Earlier totals below are historical.

## REF-007 — 2026-10-06 — platform-services review checkpoint

The exhaustive goal remains active. All 43 actual definitions in ten platform
service files have individual decisions: two absorbed exact, fourteen native
deferred and twenty-seven support. Current terminal decisions: 408; 6,298 of
6,706 pending. Six of 103 parser-gap files reconciled; 97 remain pending.

- Added Configuration owner: signed 48-byte binding construction309, default
  16-byte slots85 and low-nine-bit flags137 with retained high bits. Three
  full canonical units add531 bytes; only bindings adds309 authored bytes.
  Slots and flags retain unknown authored/compiler origins without credit.
- Cold complete replay: 40/40 units, eleven objects, 3,188 full compared bytes.
  Authored exact: 31 functions, 2,667 bytes; source-present mappings: 40.
- Portable checks cover all defaults and retained flag bits. Four unmodified
  production TUs compile serially; no wholesale platform/clock acceptance.
- Recovered actual inline-assembly oracle owner and removed two phantom bodies
  with file-specific parse normalization; all 365 older review bindings remain
  unchanged. New regression verifies original offsets/hashes; gap reconciled.
- Native pushes disprove reference's missing-%s argument claim. Logged path,
  fixed globals, guard/EH, returned statuses, buffer lengths/initialization and
  allocator/file ownership differences are individually recorded.
- Read retained CPU report and source-only service tests, without rerunning
  them. Report includes source-only checks and forces SSE2; complete conversion
  helper has feature-dispatched code. System settings were not changed.

Next coherent family: runtime_state's 27 definitions, then program_entry and
all remaining implementations/parser gaps. Deferred protocols remain specific
follow-ups. Private evidence: `.analysis/ref007-*` and compiler receipts.
Earlier checkpoint totals below are historical.

## REF-006 — 2026-10-06 — input review checkpoint

The exhaustive goal remains active. All 84 definitions in seven input files
have individual decisions: five absorbed exact, twenty-eight native deferred,
fifty-one support. Current terminal decisions: 365; 6,342 of 6,707 pending.
Five of 103 parser-gap files are reconciled; 98 remain pending.

- Added InputState owner with original thiscall Device header members, cdecl
  byte mapping and full 583-byte button update. Five new authored units: 809
  bytes. Independent Device constructor/poll/frame consumers establish layout;
  separately queried indexed-array callee0x414580 anchors eleven relocations.
- Cold complete replay: 37/37 units, ten objects, 2,657 full compared bytes.
  Authored exact: 30 functions, 2,358 bytes; source-present mappings: 37.
- Portable cadence/bit31/release/wrap/retained-state/header/binding checks added.
  Constructor, polling and enclosing Controller are still unreconstructed.
- Recorded original results dropped as void, Device-to-Controller receiver
  changes, appended context, fixed global/Host dispatch differences, callback
  userdata changes, WMI allocation/cleanup and added failure-domain exceptions.
- All three selected unmodified production TUs compile serially. Reviewed all
  fixtures/adapters/tests; the upstream 44,271 CPU comparisons were not rerun
  and are not exact credit. Two annotation parser-gap files reconciled fully.

Next coherent family: platform_services' 44 definitions, then every remaining
implementation/parser gap. Deferred owner/ABI cases remain specific follow-ups;
do not stall exhaustive coverage or treat a module as collectively rejected.
Private evidence: `.analysis/ref006-*` and compiler receipts under `build/`.
Earlier checkpoint totals below are historical.

## REF-005 — 2026-10-06 — tools and test review checkpoint

The exhaustive goal remains active. Added 91 individual support reviews: all
39 tooling definitions, 37 root test bodies and 15 scheduler CPU-oracle bodies.
Current inventory: 6,707 definitions; 281 terminal decisions; 6,426 pending.
Of 103 parser-gap files, three are manually reconciled and 100 remain pending.

- Removed one unreviewed phantom scheduler callback body caused by `__cdecl`
  forward declarations consuming the next class. Narrow parse-view annotation
  normalization preserves original source bytes, offsets and hashes. All 190
  earlier review IDs/body hashes remain valid. Synthetic regression passes.
- Manually reconciled conditional CLI entry declarations and inline x87 test
  instructions. Reviewed tool rejection policies and CPU-oracle limitations;
  source tests and normalized state comparisons add no native exact credit.
- Portable binary-parser CTest passes. No production source/profile/layout/
  anchor changed: existing 32 units, nine objects, 1,848 full compared bytes;
  authored exact 25 functions, 1,549 bytes. No redundant cold replay required.

Next: input's 84 definitions, then every remaining implementation and parser
gap. Native core's indexed production bodies were already reviewed; the older
REF-004 suggestion of remaining native-core owners was inaccurate. Deferred
native owner/protocol work is still individually recorded. Private evidence:
`.analysis/ref005-*`. Earlier checkpoint totals below are historical.

## REF-004 — 2026-10-06 — archive review checkpoint

The exhaustive goal is still active. All eight archive source/header files and
64 explicit definitions now have individual reviews: eighteen native cases
deferred with specific contracts and forty-six integration/test/report helpers.
No archive parser gap remains. Total terminal decisions: 190; 6,518 indexed
bodies and 103 parser-gap files elsewhere are pending.

- Recovered counted filename sum 0x456270, complete 71-byte canonical unit.
  Its caller, not the sum, selects eight independently read crypt records.
- Cold full replay: 32/32 units, nine objects, 1,848 compared bytes.
  Authored exact: 25 functions, 1,549 bytes; source-present mappings: 32.
- Independent target distinguishes signed native crypt/allocator ABI, pointer
  LZSS with persistent global dictionary, sixteen-byte ArcMngr/record storage,
  virtual stream lifetime, CRT name comparison and full locked file selection.
- Recorded extra source rejection policies, ASCII-view versus CRT comparison,
  raw-pointer versus optional/vector returns, omitted native size-out parameter
  and reference storage/global ownership changes. Do not bulk-import archive.
- All four selected unmodified production/verifier TUs compile serially after
  adding its declared CMake source-SHA macros to the diagnostic recipe. Cached
  receipts remain conservative; any source change triggers revalidation/retry.
- Added portable filename-sum cases for explicit count, embedded zeros, high
  bytes, wrap and zero-length input. Public CI and private tracking pass.

Next coherent families: native_core's remaining value/string/container/file
owners, then every remaining indexed implementation and manual parser gap.
Scheduler/runtime/archive deferred native protocols remain individually logged
follow-ups. No new approval is needed to continue the user-authorized goal.

Private evidence: .analysis/ref004-*, reference-functions/exact-replay-008.log
and compiler receipts under build/. REF-003 and earlier totals below are history.

## REF-003 — 2026-10-06 — runtime review checkpoint

The exhaustive user goal remains active. Every existing implementation needs
an individual decision; record difficult cases and continue without a module
default rejection. Next: archive source/ownership and its tests, followed by
every remaining indexed implementation and parser gap.

- Added explicit README credits to Oracatt/Touhou20 and N0zoM1z0/th095.
- All nine runtime_core source/header/include files and 67 explicit bodies
  reviewed: nine absorbed reference bodies, twenty-four native deferred cases,
  thirty-four integration/test helpers. Each decision binds its own body hash.
- Total explicit decisions: 126; 6,582 indexed bodies still pending.
- cpu_compare.cpp's single WINAPI annotation parse gap manually reconciled
  against the full file and five indexed definitions. Public hash/count-bound
  reconciliation ledger leaves 103 of 104 gap files pending.
- Eleven new full canonical units: LockRegistry flag members, custom PMR
  constructor/destructor/equality, TaskInfo destructor/virtual wrappers/helpers,
  and Worker construction. Independent file-backed RTTI/vtable and separately
  queried library/node callees establish all anchors before canonical replay.
- Cold complete replay: 31/31 units, eight objects, 1,777 compared bytes.
  Authored exact: 24 functions, 1,478 bytes; source-present mappings: 31.
- Three exact empty/defaulted PMR/TaskInfo lifetime contributions have pending
  authored/compiler origins and no authored credit, in addition to two pending
  float-view functions and two excluded STL equivalents.
- Worker destructor and custom PMR allocation/deallocation remain declared
  without definitions. These are partial owners, not complete linked services.
- Deferred concrete contracts include checked versus unchecked indexing,
  fixed native globals, allocator receiver/deleting flags, CRT new-handler
  paths, native variadic logging and conversion-failure behavior, and graphics
  0x4D9E30 owning its Worker at +0xD90. Read the individual review rows.
- Portable UBSan tests cover registry representation-preserving toggles and
  nullable TaskInfo callback masking, plus all previously accepted components.
- The installed D: runtime play aid matches the maintained no-hit scripts;
  hits return before effects/death. Actual hit playthrough remains unverified.

Private evidence: .analysis/ref003-*, reference-functions/exact-replay-007.log
and build object receipts. Public CI and private tracking gates pass. No
reference implementation text or executable bytes were imported publicly.
Read REFERENCE_FUNCTION_REVIEW.md and SOURCE_MAP.md; do not equate this bounded
runtime checkpoint with completing the exhaustive reference goal.

## REF-002 — 2026-10-06 — exhaustive review remains active

The user clarified that every existing reference implementation must receive
an individual review. Easy exact recoveries should be absorbed immediately;
difficult cases should record evidence and remaining work, then continue.
Do not treat REF-001's file/module scan as satisfying this requirement.

- Index: 916 nongenerated C/C++ files; 6,708 definitions, including 4,193
  reconstruction candidates. Role/address hints are provisional, not mappings.
- Parser gaps in 104 files require manual reconciliation. Deleted declarations
  and generated Ghidra exports are excluded; defaulted bodies and lambdas remain.
- Explicit decisions cover 59 native-core/export/scheduler bodies. The other
  6,649 indexed bodies are pending, as are parse-gap reconciliations.
- Timer mode now matches through its natural two-bit field representation.
- Timer add/tick restore original receiver/global-clock/helper-call ABI and
  match all 295/324 bytes, including eight/ten independent relocations.
- Two float receiver helpers match 16/35 bytes. Their enclosing owner/origin
  remains pending, so they receive no authored progress credit.
- Scheduler: all 35 indexed implementation bodies have individual decisions:
  eleven absorbed exact, eighteen deferred nonexact, six integration helpers.
  Link construction/insertion and eight node operations restore receiver ABI.
- Cold replay: twenty units, four objects, 1,450 bytes. Authored exact: sixteen
  Timer/FunctionChain functions, 1,231 bytes; source-present mappings: twenty.
- User-requested runtime invincibility launcher is installed beside the
  D: game. Hit entry now returns before any effects; the earlier stock-only
  mode is superseded. Revised Windows launch/readback passes; file unchanged.
  See RUNTIME_PATCH.md; no hit/respawn playthrough or reconstruction credit.
- README now follows TH095: supplied title image centered at width 640,
  followed by the separate 560x176 progress SVG.
- Private original-reference TU probes cover scheduler/archive/runtime; build
  include dependencies and verifier hash macros need distinct recipe handling.

Read `REFERENCE_FUNCTION_REVIEW.md`. Use `index-reference-functions.py --check`
and `report-reference-functions.py` through `scripts/repo-python`; explicit
review outcomes bind to body hashes. Reference compiler probes stay serial and
never confer semantic or exact credit. Continue runtime/archive and every
remaining implementation; scheduler constructor/EH, iterator/allocator aliases
and dispatch are specifically recorded follow-ups rather than accepted source.
No approval or new task is needed to keep progressing.

Private evidence: `.analysis/ref002-*`, `.analysis/reference-functions/`.
The following records are historical checkpoints.

## REF-001 — 2026-10-06

The reference-wide review and first independently verified absorption are
recorded in `REFERENCE_REVIEW.md`. The pinned local checkout is
`_reference/Touhou20`, explicitly ignored and blocked from public CI's tracked
tree. The public repository is https://github.com/N0zoM1z0/th20, with TH095-style
README/progress, About and topics. Maintained prose is English; official names
and original evidence retain their language. Commit subjects use
`gpt-6.1-sol: <description>`.

All Python invocations now go through `scripts/repo-python`, modeled on TH10.
Shell launchers and public CI use the same entry point; it prefers the pinned
local environment and supports standard-library-only fresh public checkouts.

- All 10,822 reference files audited; 55 group dispositions account for them.
- Same target hash: registry/package identification is 1.00a, embedded
  title/replay labels are 1.00c. Both are verified in target provenance.
- 153 diagnostic sites in 124 functions independently accepted as routing
  evidence, with no mapping/source/exact credit inherited.
- Maintained source: `src/Random.*` and `src/Timer.*`; five source-present mappings.
- Four canonical units replay complete contributions from two cold objects.
- Authored exact credit: two Timer functions, 131 bytes. RNG's two exact
  equivalents are excluded as MSVC STL; __aullshr is excluded as CRT.
- Timer mode: natural source, behavior checked, three differing bytes; no credit.
- Current origin review: three authored, three exclusions, 6,922 pending.
- Public semantic/synthetic CI, private target/tracking/Ghidra checks, reference
  byte/freshness audit and independent source-diagnostic checks pass.
- Portable reference binary-parser and archive CTests pass. Linux cannot link
  its Windows-wmain archive verifier; no game/runtime credit follows.
- No whole-game build/runtime or reference implementation bulk import.

Next coherent family: Timer delta/tick and global clock/rounding, or enclosing
RNG seed/distribution/storage ownership. Other candidate families are indexed
in the reference review; avoid inheriting its service-suffixed layouts or
historical behavior counts. Replay existing units after any shared-source change.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/ghidra.py check
scripts/repo-python scripts/review-reference.py
scripts/repo-python scripts/ghidra.py architecture
scripts/repo-python scripts/import-reference-leads.py --check
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python scripts/ci.py
```

Private evidence: `.analysis/reference-review/`, `.analysis/reference-core*`,
`.analysis/reference-rng-anchor*`; receipts are beside `build/Random.obj` and
`build/Timer.obj`. The bootstrap record below is historical.

## BOOT-001 — 2026-10-06

The TH20 control plane and local build/analysis environment are initialized.
The user selected existing **Japanese v1.00a Steamless** as the sole exact
oracle. The Steam-original backup remains provenance evidence. This decision
is persistent; do not ask again or silently substitute the non-Steam variant.

- Target SHA-256: `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
- Repository: `/home/pentester/coding/codex_ida/th20-reconstruction/th20`.
- Supplied files: `../game_exe/`; ignored target symlink `resources/th20.exe`.
- Analysis: independent Ghidra 12.1.3 `TH20` project, fully target-attested.
- Inventory: 6,928 provisional functions, all origins/boundaries awaiting review.
  Architecture export has 22,731 direct call edges, 11,307 global-reference rows
  and 711 string-reference rows; these are routing evidence only.
- Mapping/source/exact: **0 / 0 / 0**; canonical manifest and claims are empty.
- Candidate compiler: MSVC 19.44.35211 x86, linker 14.44.35211.0,
  toolset directory 14.44.35207, SDK 10.0.26100.0, D3DX 9.29.952.8.
  Game compiler build and flags remain unproved; see `ORACLES.md`.
- Shared analysis-tool symlinks point at TH095's `.tools/`. Compiler/SDK/Wine
  and private Ghidra state are local to TH20. TH095 source, ledgers, database,
  environment and protected untracked files were not changed.
- Optional project-agnostic web bridge is prepared with a TH20 env template
  and launcher. No listener, user service or external endpoint was published.

## Validation evidence

Passed target/provenance verification, locked tool fingerprints/version banners,
Ghidra check plus bounded entry disassembly/decompilation and architecture
export, tracking/build-graph/progress gates, synthetic exact-oracle tests and
public CI. The target verifier rejects the Steam-original backup as a substitute;
the Ghidra attestation rejects a deliberately wrong expected target hash without
mutating the database or executing a query. Exact replay reports zero configured
units and does not manufacture matching credit.

The cold compiler probe passed x86 COFF, Win32/DirectX C++ headers, PE32 linker
and Wine/D3DX runtime checks. Infrastructure probe hashes at this checkpoint:

- Source: `f043a7f400b12088efe5cab8ca30e67c8a7803070fa6e0be022f340a2f5cce0a`.
- Object: `3053df6b6a59a90c3514c2445542530581691acec2058e550851e6227e87d27d`.
- PE32 executable: `9e8c92f9d647ac954ebf1fe3234087a7de81bd3004b6454029cc200277b53c02`.

Objects, debug records, raw decompilation, downloaded registry/manifests and
full command receipts stay in ignored `build/` and `.analysis/bootstrap/`.
The smoke executable is a console infrastructure probe, not a game build.

## Resume

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/ghidra.py check
scripts/repo-python scripts/ci.py
```

Read `AGENTS.md`, `RE_WORKFLOW.md`, `ARCHITECTURE.md`, `ORACLES.md`,
`SEMANTIC_RECONSTRUCTION.md` and `SOURCE_MAP.md` first. Next lane: one bounded
owner/ABI family from the provisional inventory, using independent target-local
evidence and clean compiler probes. Do not project TH095 roles/layouts/flags
onto TH20. Maintain one writable session and serial compiler/Ghidra access.
