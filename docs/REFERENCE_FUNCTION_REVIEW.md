# REF-002: exhaustive implementation review in progress

The user requires a function-by-function review of every existing reference
implementation. REF-001's repository scan and module dispositions do not meet
that requirement. This work stays active until each implementation has an
explicit outcome. Easily recoverable exact functions are absorbed immediately;
difficult cases receive specific evidence and remaining work, then the review
continues. No default module-wide rejection or completion is permitted.
Following the user's batching instruction, related owners and modules are
reviewed together, with one serial compiler pass and a combined exact replay.
Each implementation still receives its own hash-bound outcome.

## Coverage and decisions

`reference-function-index.csv` inventories explicit C/C++ definitions, defaulted
definitions and lambdas, Python functions/lambdas, and whole Python/PowerShell
module bodies. Top-level script execution needs review even without functions.
Deleted declarations and generated Ghidra exports are excluded.
`reference-source-files.csv` includes 916 nongenerated C/C++ files, 76 Python
files and ten PowerShell files: 1,002 files, including files without functions.
Names, address hints and role hints are discovery metadata, not mappings.

The current inventory has 6,944 implementation entries: 6,706 C/C++ definitions,
152 Python functions/lambdas and 86 script module bodies. Roles are 4,193
reconstruction candidates, 2,439 test/oracle bodies, 277 tooling/support entries
and 35 historical bridge bodies. These role hints need review. There are gaps
in 113 files, including ten explicit PowerShell function-inventory gaps;
manual reconciliation remains required, and this inventory is not asserted
to be a complete compiler AST. Private gap ranges are recorded rather than
silently omitted. Tree-sitter 0.25.2 and its C++ grammar 0.23.4 are pinned in
the analysis environment. Export annotation `API` and scheduler CPU-oracle
`__cdecl` annotations are blanked only in their individually reconciled files.
Flat inline-assembly statements are blanked only in the manually reconciled
platform-services CPU oracle. Offsets and hashes use the original bytes; reference source is never edited.
Python uses the standard-library AST with original UTF-8 byte offsets, including
decorators in function hashes. PowerShell currently has whole-file entries;
each file still needs manual function enumeration and gap reconciliation.

`reference-function-reviews.csv` binds every decision to its exact body hash.
`report-reference-functions.py` validates those bindings, counts explicit
terminal decisions separately from intermediate work, and reports untouched
bodies as pending. No scan, compile or module status grants review credit.
The first 1,092 native-core/export/scheduler/runtime/archive/input/platform-service/
runtime-state/program-entry/diagnostic/platform-window/startup/audio/session/stage-clear/help/notice/card/ending/trophy/screen/tool/test entries have explicit decisions. The
remaining 5,852 indexed entries are pending. The separate
`reference-parse-gap-reviews.csv` binds manual reconciliation to the file hash
and parser-gap count: twenty-one of 113 files are reconciled, leaving 92 pending.

## REF-021: ScreenEffect and shared Timer/vertex recovery batch

All forty-three ScreenEffect entries have individual hash-bound decisions:
seventeen nonexact and twenty-six support. Full production sources, header,
CPU driver, CMake recipe and retained report were read. The driver's seven
WINAPI annotation gaps are manually reconciled; all thirteen bodies are indexed.
Coverage is 1,092 terminal/5,852 pending; gaps 21 reconciled/92 pending. All four
unmodified production TUs freshly compile using their declared transitive
sprite/runtime/gameplay include paths. Seventeen complete native contributions
receive compiler size diagnostics; all differ in complete size. No native-sized
prefix is compared or accepted, and the original CPU oracle is not compiled/run.

Three natural shared contributions are newly canonical exact:

| Member | Native address | Complete bytes |
| --- | --- | --- |
| Timer fractional age | 0x00423BD0 | 17 |
| Timer signed <= predicate | 0x00423590 | 46 |
| ColoredVertex construction | 0x00423470 | 43 |

Both Timer bodies and their Screen update call sites are independently read.
The getter returns offset8 through x87 ST0; the signed predicate reads current4,
returns bool and cleans its integer argument. The vertex's complete 20-byte
storage is independently established by array construction count4/stride20 in
the original rectangle routine, typed Vector3 coordinate copies and FVF0x44/
stride20 COM submission. Its constructor invokes the existing Vector3 zero
constructor at422E10, then clears reciprocal-w12/color16. That relocation anchor
precedes probing and all four bytes are replayed. Original source names and
authored/shared/compiler/library origins of all three remain pending. Cold
replay passes 89/89 units, twenty-two objects and 5,662 complete bytes. Authored
credit remains56 functions/4,056 bytes; source mappings89, pending-origin29,
library4. Reference aggregates and decompiler bodies are not imported.

Actual ScreenInf has a16-byte TaskInf base, scalar fields10..2C, typed Timer30
and view40, total44 hex bytes. Native constructor187/dtor121 include original
base/vptr/EH/diagnostics/scheduler ownership that the reference changes.
Initialization has637 instruction bytes throughRET24, three alignment bytes and
ten-entry40-byte jump table, all read. It registers direct update24/drawpriority,
sets mode3 alpha255, shutdown and actual Timer assignment, then scalar arguments.
Reference constexpr arrays/forwarding callbacks and invalid-mode exception
change this partition and policy. Native factory is39-byte default-view wrapper
plus81-byte factory through65-byte diagnostic allocator; reference126-byte
nothrow-new/memset/placement body merges them. Shutdown native29/source19 also
changes tracked allocator ownership. No fake Screen/Game/Renderer receiver is
introduced to absorb isolated field operations or the simple solid callback.

All seven native update extents are contiguous, with no omitted instruction
holes: fade-out180, fade-in239, hold221, flashes264, solid82, linear shake1040
and envelope1318 bytes. Timer predicates/conversion/postfix/assignment remain
distinct real members, while reference fields and free helpers change calls.
Envelope checks flags0x77 and unsigned wrapped tail conversion; linear shake
ticks before its termination test. The unsigned-conversion double table at
56CDD0/56CDD8 is independently read as0.0/4294967296.0, selected by a logical
shift of the input sign bit. Both callbacks consume two bounded3 calls from
actual GameRandom stream1 at5BA4C4 and update four cameras. Native linear zero-Y really
writes camera3point2 at5C553C, unlike its nonzero point0Y at5C552C; the reference
preserves this observed asymmetry. The four drawing callbacks have complete
128/172/105/202-byte extents. Native rectangle1407 creates typed vertices,
performs eleven ordered COM calls and invokes six actual renderer-cache members;
reference711-byte explicit receiver/device helper factors geometry and writes
cache fields directly. None of these full owner/callback functions is exact.

The retained124,288 checks/zero failures agree with all seven current reported
source hashes and the driver arithmetic:7*4096*4 updates +640*5 lifecycle
+5*320*4 drawing. Updates compare full68-byte owner/return/fullDE8 Graphics/RNG28
under dirty scalar/quarter-frame/nullable clock/Game/cancellation fixtures.
Lifecycle covers ten valid modes, dirty construction, node registration and
normal destructor removal; vptr/nodes are normalized and callback identities
reduced to presence. It never invokes shutdown or either factory. Drawing records
COM order/arguments/full vertex bytes, selected Controller caches and Graphics
with host D3DX matrices. These are historical CPU/recording observations,
excluding GPU pixels, invalid modes, allocation failures, startup, concurrent
or exception lifetime. Manual process cleanup does not restore every mapped
global. The report omits target SHA and hashes for the driver, dependencies and
toolchain despite a SHA assertion in its driver, so a current full historical
build binding cannot be established. Private evidence is `.analysis/ref021-*`.

Next coherent batch: text_renderer, followed by all remaining indexed bodies
and manual gaps. Earlier checkpoint counts below are historical.

## REF-020: Trophy queue, messages, resources and frame lifecycle batch

All forty-nine Trophy entries have individual decisions: twenty nonexact,
twenty-eight support and one absorbed. Full production sources, headers,
extractor, both oracle bodies, recipes and report scope were read. The five
parser errors in two files are WINAPI annotations; all seven CPU-driver and
eight pool-fixture bodies are present. Both files are manually reconciled.
Coverage is 1,049 terminal/5,895 pending, with twenty gap files reconciled and
93 pending. Fifty relevant native functions were independently queried,
decompiled and read through the attested Ghidra wrapper. Six original production
TUs freshly compile with their declared public sprite/ECL/binary dependencies.
Neither original CPU oracle was compiled or executed here.

Three related natural contributions pass complete canonical relocation replay:

| Member | Native address | Complete bytes |
| --- | --- | --- |
| Trophy shared text decode | 0x0052F060 | 106 |
| Trophy Message id reset | 0x0052F590 | 20 |
| Timer integer assignment wrapper | 0x00423520 | 26 |

The decoder includes the encoded NUL, starts key 0x77/step 7 and advances the
step by 16 modulo 256. Its independently observed result at 0x005C6860 is a
shared 256-byte buffer, overwritten on each call. The maintained function uses
real byte arithmetic and character storage; both absolute relocations are
explicitly replayed against that original global. Valid input terminates within
256 bytes; no bounds recovery or reentrancy is claimed. Portable tests use a
closed-form key calculation across all 256 lengths, high bytes, key wrap,
trailing-byte preservation and result-pointer reuse. This does not accept the
encoder: its original cdecl parameter is an owned 28-byte PMR string passed by
value, indexed at zero and destroyed, while the reference takes a char pointer.

Native resource allocation and parsing independently establish the actual
0x704-byte Message record: signed id at zero, title at four and two-by-three
description rows at 0x104, each row 256 bytes. The accepted member sets id to -1
without touching the remaining 1,792 bytes. No padding facade or record allocator
is added. Timer assignment keeps the actual void/RET4 member and delegates to
already accepted set at 0x00423F80. Its source spelling and origin remain pending.
Cold replay passes 86/86 units over twenty-one objects, 5,556 complete bytes;
authored credit is 56 functions/4,056 bytes, with 26 pending-origin and four
library units. Integer += remains nonexact, 33 versus 31 bytes.

TrophyInf's native 0x54 owner contains its TaskInf base, animation-file pointer,
checked 24-byte PMR deque with eight-byte proxy, three state words, Timer at
0x38 and three typed handles at 0x48. Construction/destruction, diagnostics,
allocator/base/vtable/EH and original queue partition remain unresolved. Native
push has separate value/address/emplace contributions; grow uses actual typed
allocation/getter/copy/zero/max-size/error helpers. Destruction cleans map blocks
backwards and destroys elements and proxy through separate members. The native
pop takes an index and erases through checked iterators; the source provides
only no-argument front-pop. Valid front-pop event/topology agreement does not
establish arbitrary indexed deletion or checked-container exactness.

Native achievement query returns full EAX 0/1 through SaveManager thiscall,
tracked slot20 lock, metadata verification/getter and a checked 128-byte array
at metadata+0x68. The mutation follows its own getter/checksum member path.
Reference bool/free/global wrappers change ABI and ownership. The factory has
a separate enqueue member and diagnostic allocator; initialization registers
update17/draw93, while the shared draw thunk preserves a separate constant-return
member. Native resource release returns int zero, versus the reference void
wrapper. Preload at 44EE50 is distinct from the cached/load member at 44EB30.
Full extents retain independently decoded unreachable JMPs at 52E4B1/52E4CD
in the 1,308-byte initializer and 52F97C in the 165-byte factory.

The native 564-byte frame member consumes queued messages, spawns three typed
animations, produces two centered texts and sound79, tests age>=240, then
switches to queued/start or teardown state. State2 deletes the three handles and
retires the actual owner, returning one without another tick. Other states use
the real postfix Timer member. Two distinct eight-byte completion callable
types invoke 46EBB0 -> 46A4B0 -> empty40E5E0; the empty body still has an actual
ECX entry and library/closure ownership. A source empty callback is insufficient
to accept those function/callable partitions.

Retained CPU validation reports 295,327 checks: 16,384 full-buffer encodings and
16,384 decodings, sixty-four queue constructors/destructors and 131,072 operations
each checked for return/allocation sequence and complete map/element topology,
plus 287 decoded rows across forty-one source-parsed records. The native parser
is never invoked there. Source-added truncated/overlong/index exceptions and
std::string/istringstream/span factoring remain nonexact against the PMR/native
inline parser. The report binds target and asset hashes, but no source hashes;
its referenced oracle/build/source_hashes.json is absent in this checkout.
Current historical executable/source identity cannot be re-established.

The separate retained 34,404 owner/frame subset matches all twenty-eight counters
in the hash-bound shared report and all 389 current source hashes. It covers
256 dirty constructors, actual cache-hit initialization and owned-node teardown,
and 2,048 full frames. Both real deferred queues execute GDI raster/upload tasks;
612 submitted pixel buffers, rectangles, COM counts, both outline polarities,
full 64-ANM state, normalized owner/scheduler graphs, sound and PMR event order
are observed. The fixture uses preloaded bounded ANM, host font2, recording COM,
synthetic locks/resource globals and pointer-role normalization that can also
rewrite coincidental scalars. Manual normal-exit cleanup and clock reset to one
do not establish exception/concurrent lifecycle. Save mutation, factory failures,
preload/file I/O, full assets/scheduling/GPU remain excluded. Historical 612
pixel/PMR failures bind 316 of 335 current source hashes and are not current
failures; the retained case41 allocation trace contains twenty identical events.

The next coherent batch is all forty-three screen_effect implementations. Every
remaining indexed body and manual parser gap stays in the exhaustive scope.

## REF-019: Ending and its shared Timer/input protocols reviewed as a batch

All 39 Ending implementation entries have individual decisions: twenty-two
nonexact and seventeen support. Complete production/header/extractor/constants,
both CPU fixture fragments, recipes and report scope were read. There are no
Ending parser gaps. Total coverage is 1,000 terminal and 5,944 pending; eighteen
gap files are reconciled and 95 remain pending. Sixty-six relevant native
functions were independently queried and decompiled through the attested
wrapper. Six original production TUs freshly compile after restoring their
declared transitive sprite-renderer/ECL/binary include paths. This is compilation,
not native oracle execution or linkage.

Eight natural shared-owner contributions are newly canonical exact:

| Member | Native address | Complete bytes |
| --- | --- | --- |
| Timer construction | 0x00422D90 | 54 |
| Timer current integer conversion | 0x0040FF90 | 17 |
| Timer signed remainder | 0x00472040 | 25 |
| Timer integer subtraction wrapper | 0x00429E70 | 28 |
| Timer postfix increment | 0x00423540 | 22 |
| Timer postfix decrement | 0x00429420 | 24 |
| InputButtonState current bits | 0x004495A0 | 21 |
| InputButtonState held-frame count | 0x004A0A20 | 79 |

All target extents and call anchors precede probing. The held query retains
actual thiscall/full uint32/RET4 and shared std::array indexing; the free nullable
reference helper remains nonexact. Timer operator spelling is inferred and all
six Timer origins remain pending. Integer += is maintained as a natural dependency
but emits 33 bytes against 31 native bytes, including an extra XORPS; no shortened
comparison or shaping is accepted. Subtraction uses defined modulo negation.
Existing Timer/input contributions retain one body/profile per source. Complete
cold replay passes 83/83 units across twenty objects, 5,404 bytes; authored credit
is 54 functions/3,930 bytes, source-present 83, exact-origin-pending 25.
Dirty/sentinel Timer, signed conversion/remainder, four stepping operations and
all thirty-two held indices/bit31/full-byte preservation tests pass.

EndingInf's actual 0x28 owner and Script's 0xF0 layout are corroborated, with
three typed Timers, two five-handle arrays, two Vector3 values, four files,
sixteen typed handles and a sixteen-byte Worker at 0xDC. Native construction,
diagnostic/base/allocator/EH, repeated animation resolving, typed deletion and
original owned teardown differ from the aggregate reference. No artificial
layout or whole scene owner is absorbed. Full native instruction extents were
checked, including independently decoded unreachable two-byte JMPs at 4A048B
and 4A103F that Ghidra omitted from update and factory listings.

The VM has 4,107 instruction bytes, an eighteen-slot opcode table and a separate
four-slot difficulty table. Recognized opcodes, two wait paths, signed timing,
music, by-value scene-handle deletion and credits restart are corroborated.
Reference merged cases/helpers, added bounds/malformed-text exceptions and
ordinary std::string closures change the native PMR/member/EH partition.
Native update_script returns full int 0/1; the fixture invokes it as cpu<bool>
before widening, so return-byte agreement does not close that ABI.
The metadata array helper does independently check index<32; its source wrapper
still changes receiver/getter/lock and error partition. Initialization, selectors,
original filename-path buffer and owned resources remain unclosed.

Plain native flag loads/stores surround asynchronous resource launch; source
atomic_ref updates are an additional memory-access policy. The original Worker
callback reloads global EndingInf when it executes, forwards through a member
to its current Script and returns int zero. Source jthread/free-void helpers
change launch/callback/stop-source/lock/lifetime protocol. No concurrent oracle
or failed-I/O acceptance is inferred.

Ordinary and ruby native queued closures are distinct: Script pointer at zero,
28-byte PMR string at four, then Animation at 0x20, or x/spacing/Animation at
0x20/0x24/0x28. Both read Script colors at execution. Their completion callable
objects retain actual Animation pointer and invoke event2 through
4A0C20 -> 49EA50 -> 49F1E0 -> 4888E0 -> 477450 -> 42B5D0, without manager
predraw. This behavior is corroborated, while reference unified capture, allocator,
copy/move/EH and ownership remain nonexact. Four independently read callable
tables have six function slots followed by RTTI locator or 392.0 float;
exploratory seventh words are not callable entries. All 23 ending names, five
alias credits names, three floats and text/error strings independently match.

Retained 200,618 comparisons bind to forty-four exact subset counters in the
shared report; all 389 source hashes are current. No reference native oracle was
compiled or run here. The fixtures provide 256 dirty constructors/Script-only
destructors, 12,288 mixed VM/frame calls, 8,192 valid held queries and 1,024 actual
queued CP932/ruby GDI/deferred upload/completion programs. Text colors change
between scheduling and execution; 1,706 pixel comparisons, rectangles, COM
counts and synthetic ANM state are retained observations. This is stronger
closure behavior coverage than the Card queue-count-only fixture, without
granting source exactness or physical GPU/whole-ending acceptance.

Fixtures normalize owner vptr and Screen mode0/5 node graphs, manufacture locks,
PMR/resources/input and valid synthetic ANM, and use host GDI fonts with recording
COM surfaces. Graph word replacement may also normalize coincidental scalars.
Opcode7 is absent; opcode12 forces gallery early return, excluding achievement,
credits replacement and I/O. Whole EndingInf destruction, initialization, file
unloading and active-thread lifetime are excluded. Cleanup is manual normal-exit
restoration and resets the clock to one. Historical sound failures total 659;
only 328/343 hashes match current source, so that report is historical evidence.

Private evidence: `.analysis/ref019-*`. Next coherent batch is all 49 Trophy
entries, followed by every remaining implementation and 95 manual gap files.

## REF-018: all 32 Card implementation entries reviewed

All 32 bodies have individual decisions: seventeen nonexact and fifteen support.
Production source, owner/record headers, extractor/constants, six complete CPU
include fragments, build recipes and reports were read. Same-line nested lambdas
have distinct records. No family parser gap occurs. Coverage is 961 terminal
and 5,983 pending; global gaps remain eighteen reconciled and 95 pending.
Forty-nine relevant native functions were independently queried and decompiled.
All seven original production TUs freshly compile serially after supplying the
runtime_state/ECL public include dependencies declared by CMake. The initial
five missing-binary-header failures were recipe errors, not algorithm rejection.
Compiler probes remain diagnostics; neither linkage nor a new CPU run is claimed.

Native Card construction, drawing and smoothing expose one coherent twelve-byte
three-float value owner. Maintained Vector3 recovers both constructors and the
subtraction, scaling and add-assignment members naturally. Complete extents are
46, 54, 88, 80 and 85 bytes, totaling 353. Coordinate-constructor calls in the two
aggregate-return operators were independently established before canonical
probing. Hidden return storage, RET12/RET8/RET4 and reference return are preserved;
no arbitrary padding, duplicate body, ABI fiction or emission-shaping local.
Original class spelling and authored/compiler/library origin remain unknown, so
all five are excluded from authored credit. Tests cover dirty zero construction
with adjacent sentinels, signed-zero/NaN representation copying, a three-lane
position update, nonmutation and self-aliasing add assignment. Full cold replay
passes 75/75 units across twenty objects and 5,134 bytes. Source-present is 75;
authored remains 52/3,830 and exact origin-pending contributions rise to nineteen.

Card's full C8-byte owner remains unresolved. Native constructor is 348 bytes,
with actual base, five typed animation handles, Timer, char64, aligned doubles,
Vector3 and diagnostic call. Reference aggregate integer handles/Timer/position
change member and EH partition; explicit alignment-gap fields do not establish
typed storage. Native destructor's 180 bytes release three handles individually
and own scheduler/base teardown. Initialize is a 121-byte member with separate
view/context setter, Session context and Context+10 owner setter, callbacks40/12
and Timer reset. Source free functions/direct fields/generalized helpers differ.
Factory is 92 bytes, including independently decoded unreachable JMP488B53
omitted by Ghidra's body map. Diagnostic allocator/new/zero/constructor/failure
release are not the source's placement factory. No fake layout-only Card is added.

Original time encoder at488990 is a 105-byte void member that writes A8 in three
assignments and returns with RET8; source is a pure int function. Original invalid
time predicate at4885E0 is 148 bytes and returns full EAX0/1. Ghidra calls it bool,
but retained tests compare only sizeof(bool), so upper return bytes and member
ABI are not verified. Signed remainders and wrap are corroborated, not absorbed
into a fabricated A8 receiver. Record helper486E10 is an unchecked member of the
array already at Profile+B08; reference adds an index exception and changes the
receiver. Separate capture/attempt increment members merge into a generic source
offset helper. Actual E0 record/113-element array and SaveManager lifetime remain open.

Complete update is 875 bytes: flags, ages60/300/120, signed bonus decay/rem10,
mirrored96/128/448 fade thresholds, boss smoothing0.05 and Bomb state. Source
uses one enemy lookup rather than repeated original getters, inlines vector and
flag helpers, replaces typed handle methods and throws for hardware IDIV traps.
The accepted adjacent vectors do not accept this parent. Draw's 797 bytes use
Renderer mode/alpha setters, typed resolve and repeated profile/record selection;
source direct field writes, cached selection and free APIs change partition.
Valid count/bonus/string behavior is corroborated. Full Renderer/Card owners,
PMR temporary strings, GS and resource lifetime remain unresolved.

Finish's 602 bytes own Background, typed interrupts/deletion, HUD, score, separate
record members and the all-113 achievement call. Native fallback getter488700
returns SaveManager+8A460, matching current.profiles[18] (10+18*7AE8), not backup.
Start's 1,896-byte member/RET16 owns separate flag/record writes, hidden handle
results, actual 28-byte PMR name and closure, score table and two portrait variants.
Reference ordinary std::string capture, bounds exceptions and generalized free
dependencies change allocator/EH/call partition. Queued title invocation was
independently traced through488460/486AE0/486E80 to44B020. Completion captures
Card and follows488440/486AD0/486E50/488920 into typed handle short event4.
Those bodies are reviewed individually; no queue-count oracle accepts their execution.

Eight floats, three doubles, text stem and five render strings independently
match the PE. The extractor's exploratory seven-word read at56FE44 extends the
six-slot callable interface into the0.05 float. The59A740 fmod dispatcher block
contains mixed metadata and function data, not another vtable. Post-frame is a
645-byte Card member with actual Window clock, fmod dispatcher, half-step0.0167,
floor and signed32 conversion, member encoding/checksum and Replay getters.
The543310 thunk/543320 CRT conversion returns INT_MIN on overflow; it is not a
64-bit low-word conversion. Source intrinsic value agreement does not reproduce
the x87 input/exception/feature-dispatch ABI or the full Window/Replay protocol.

Retained 206,784 passes/zero failures are exactly the Card subset of the actual
shared 2,915,831 report, verified against its hash and all 49 counters.389/389
bound source hashes are current. No retained oracle was compiled or executed
here. Constructor/dtor and scheduler checks normalize vptr, node/link/callback
addresses; pointed-to node fields/topology are compared, but address-valued
scalar words can also be replaced. Other comparisons use controlled whole
Card/Renderer/Background/Player/HUD/manager/pool/record/sound snapshots.

The valid domain includes two contexts,113 indices, NaN/infinite player Y,
integer/count edges, synthetic child programs and eight isolated Replay stage
objects. Update denominator inputs exclude300; original IDIV traps are not run.
Start checks queued-task count only, clears tasks without executing raster or
completion, and sets all portrait file selectors to-1. Finish excludes all113
captures/achievement40. Timing substitutes QPC at the import boundary with
frequency1/origin0/offset0 and manufactures lock ownership. There is no factory
failure, replay file I/O/lifecycle, real portrait asset or asynchronous GDI/GPU
acceptance. Cleanup is normal-exit-only and shared clock state is reset to1.
Historical timing failure has 46 failed checks from23 cases, with280/302 current
hashes; it cannot prove current failure or a fresh successful rerun. Empty JSONL
files alone are not acceptance evidence. Shared renderer bodies remain pending.

Private evidence: `.analysis/ref018-*`. Continue with ending_scene's39 entries
and every remaining implementation/manual gap; the exhaustive goal stays active.

## REF-017: all 30 Notice implementation entries reviewed

Every indexed implementation has its own body-hash-bound decision: thirteen
nonexact and seventeen support. Same-line fixture lambdas are reviewed as
distinct bodies, not collapsed by name or line. Complete production source,
header, extractor, constants, fixtures, recipes and retained report were read.
All42 relevant original functions were independently queried and decompiled
through attested Ghidra. Both unmodified production TUs freshly compile serially
after reconciling declared binary and transitive ECL/runtime include paths.
This is compilation, not linkage or runtime acceptance. Two WINAPI annotation
gaps in pool_fixture.hpp account for both indexed implementations; no omitted
body. Totals929 terminal/6,015 pending; gaps18 reconciled/95 pending.

Natural AnimationHandle construction at0x00425CC0 recovers the real four-byte
value owner observed in Notice's seven-element array and secondary member.
Array stride4/count7, constructor return and resolve/interrupt consumers were
independently checked before canonical probing. One scalar member initializer
emits all23 bytes through RET, with no relocation, padding, ABI fiction or source
shaping. Authored/compiler origin remains pending; no authored credit is added.
Dirty-storage testing checks the zero word and surrounding sentinel bytes.
Full cold replay70/70 across19 objects covers4,781 bytes; source-present70,
authored52/3,830 and origin-pending exact14. Whole Notice constructor remains
nonexact despite this accepted adjacent value contribution.

Original constructor281 bytes calls actual base, Timer, Cursor, seven typed
handles, secondary handle, filename initialization and diagnostic helpers.
Reference aggregate Timer/integer handles replace member/EH partition. Original
167-byte destructor owns node removal, slots14/22, Cursor/base and global owner;
the retained tests do not exercise loaded assets or concurrent lifetime. Factory
4DFB90 uses allocator4DEA10 and separate selected setter49C490. Source placement
allocation/free initialization changes that graph. Register/enable/thunk methods
require the actual Notice owner, whose full declaration remains unresolved.
Reference draw comment is again incorrect:49DEA0 calls16-byte ECX-saving member
478BF0; free direct return1 merges two contributions. No artificial owner is added.

Seven extracted NUL-terminated byte strings and all50 message constructor
bindings were independently verified. Native CRT initializer40AA40 constructs
50 separate PMR strings at5C5B40 with EH and exit registration. Source default
array construction plus aggregate move assignment has a different lifetime.
Fixture native table construction uses source messages; independently verified
constants corroborate values, not native CRT initialization or allocator identity.

Extractor calls five completion interfaces seven-slot vtables. Actual interface
has six function pointers; the seventh raw word is the next table's RTTI locator
in the first four cases and ASCII SetV after the last table. Raw reported words
match, but their interpretation overreads the interface. The common invoke
46EBB0/46A4B0/40E5E0 chain is empty. Replacing five typed std::function callables
with an empty function object still changes EH, initialization and ownership.
Native callable constructor/reset partition was inspected; it is not absorbed
as fake empty class methods or source-authored progress.

Complete update contains2,379 instruction bytes through return at4DF63A plus
four-state/eight-substate tables. Independent decoding includes unreachable
five-byte JMP4DF285 omitted by Ghidra's body map. Native Cursor count99 and
unchecked message indexing differ from source's0..24 exception policy. The real
StoneMenu names getter usesF4+index*1024, consistent with source names[stone*4]
for valid rows. Named spawn returns a typed handle through hidden storage and
array indexing; generalized Controller wrappers differ. Secondary interruption
uses a typed handle member. Cursor extra argument, Timer wrapper, raw image
ownership and Controller texture protocols remain separate unresolved calls.

Retained59,904 passes/zero failures are a subset of the actual shared2,915,831
report, verified against its hash/counters;389/389 source hashes are current.
No retained oracle was compiled or executed here. Cases consist of1,536
constructor/destructor snapshots,1,024 synchronous cache-hit graph checks,
49,152 controlled frames and4,096 each upload pixels/deferred rectangles.
Fixtures normalize vptr/proxies/callback/global/node addresses; graph encoding
can also replace coincidental address-valued scalar words. Proxy contents are
separately compared, but this is not unnormalized exact byte comparison.

Frame cases exclude image substate3 and use valid message indices, synthetic
Stone names and64-entry ANM pools, absent game state, substituted PMR resources,
manufactured lock ownership and host GDI fonts7/8. In-memory COM surfaces always
succeed, fix1088x96/pitch4352 and do not model nonzero rectangle offsets or device
failure. No async launch, real I/O, failed load, factory, loaded teardown or GPU
lifetime is exercised. Cleanup is normal-exit-only and resets clock to1 rather
than the prior value. Shared renderer snapshots remain separately pending bodies;
reading Notice include fragments grants no unrelated renderer review credit.

Private evidence: `.analysis/ref017-*`. Continue with card_system and every
remaining implementation/manual gap; the exhaustive goal remains active.

## REF-016: all 25 Help implementation entries reviewed

Every indexed body has a specific decision: fifteen nonexact and ten support.
All production code, header, recipes, README and status report were read. Both
unmodified production TUs freshly compile serially after supplying help_system's
declared binary includes and inherited ECL/runtime include paths.26 relevant
original functions were independently queried and decompiled. No family parser
gaps or original CPU/frame/thread/COM oracle; status report8/8 hashes current
only binds historical compilation, not runtime. Total899 terminal/6,045 pending;
global gaps17 reconciled/96 pending. Original Help update's2072-byte instruction
extent and six-entry jump table at4BF8B8 were fully inspected; no prefix claim.
Ghidra omits three unreachable five-byte JMPs inside that extent; an independent
PE decoder reconciles them at4BF4A3/4BF662/4BF70F. They remain part of the full
contribution and are not discarded as padding.

Natural Timer::less_than restores signed current<argument at423560, complete46
bytes with thiscall/bool/RET4 and no relocations. The existing Timer declaration
and portable signed-edge/nonmutation fixture are shared by all three predicates.
Full cold69/69 across18 objects covers4,758 bytes; authored52 functions/3,830
bytes; source-present69. Help update remains nonexact despite this adjacent
accepted component. No bytes, assembly, padding or shaping bodies imported.

Help construction uses TaskInf, Timer, Cursor and fourteen typed-handle array
constructors plus diagnostic helper; reference aggregate timers/integer handles
change the original partition. Teardown preserves actual Cursor/base and
diagnostic calls. Factory calls diagnostic allocator4BEDF0 then original member
initialization, with41F7C0 failure cleanup. Full Help/Cursor/handle/allocator
lifetime remains unclosed. No fabricated layout-only owners are maintained.

The reference draw comment is inaccurate: scheduler installs cdecl49DEA0,
which forwards ECX to478BF0. That member is16 bytes, saving ECX before returning
int1; it is not literal mov1/ret. Reference direct free return1 merges both
contributions. Update thunk4BFAD0 likewise calls the original thiscall member.
Small callbacks do not justify fake receiver declarations or duplicate credit.

Graphics launch4B99F0 returnsint0 and forwards entry plus argument through
Worker+D90 (fixed5C5AD0), with tracked slot6 guards, diagnostic and EH. Reference
entry() free API/manual recursive_mutex/jthread graph changes argument/owner
partition. Native load_image4BF8D0 directly stores410AA0's owned buffer and size
output; reference vector/second allocation/copy changes ownership and failure.
Both native and inspected source detach paths set close_requested true before
detach and reacquire the recursive lock; that flag behavior is corroborated,
not a discrepancy. Real resource/thread/global lifetime has no new validation.

Native Help uses fixed-event selected/deselected methods and a separate typed
handle short-event method; source generalized free execute/interrupt APIs merge
their receiver/argument partitions. File named spawn uses hidden handle sret.
Input2 masks80001/106/10/20, age20/30, nine menu handles/image13 and effects7/9/10
agree in the observed state graph, but do not accept rendering/input globals.

Texture replacement44DC20 is a Controller member returningint0 with six stack
arguments/RET24; source free void drops the receiver and an unused argument.
Original format mapper44CFB0 consults Graphics configuration; source omits it
and adds bounds exceptions. Independently checked first nine format entries
are0/21 and all nine bytes-per-pixel entries4: there is no claimed BPP difference
in that valid source domain. Container pointer arithmetic is corroborated;
native unused rectangle locals are not required semantic source fields.
Original D3DX entry540696 is a static import; source adds lazy LoadLibrary/
GetProcAddress/FreeLibrary lifetime and throws. Failed symbol lookup leaks its
module on constructor failure. Clear449D80 is a188-byte TextureRecord member
with an uninitialized surface output; source initializes it to null and changes
ABI. Failed COM-output behavior, complete typed owners and real GPU execution
remain open. The three help/help.anm/help_%.2d.png strings independently match.

Private evidence: `.analysis/ref016-*` and complete69-unit cold replay. Continue
with notice_system30 and every remaining implementation/manual gap.

## REF-015: all 17 stage-clear implementation entries reviewed

Every body has an individual outcome: eleven nonexact and six support. Complete
production code, headers, two fixture fragments, recipes, extractor, constant
evidence and retained reports were read. All four unmodified production TUs
freshly compile serially. The diagnostic include recipe now carries stage_clear's
actual runtime_state/ECL binary-header dependency. CPU fragments were read,
not compiled or run. No family parser gaps; totals874 terminal/6,070 pending,
global gaps17 reconciled/96 pending.33 original functions independently queried
and decompiled through the attested Ghidra wrapper.

Natural Timer predicates restore current>=argument at4235C0 and current==argument
at4785E0 into the existing complete16-byte Timer record. Each46-byte function
retains thiscall, signed comparison, bool result and RET4. Full extents end
after their three-byte returns; no tables, padding or relocations are omitted.
Both complete COFF contributions replay with zero differences. Portable signed
boundary tests also check every Timer byte stays unchanged. Full cold68/68
across18 objects covers4,712 bytes; authored51 functions/3,784 bytes;
source-present68. This adjacent recovery does not accept the full StageClear
update, whose reference row remains explicitly nonexact.

Native construction uses TaskInf/vptr, two typed handles, two Timer constructors,
array memset and diagnostic helper calls; reference integer handles, aggregate
timers and direct zeroing change the typed-member/EH partition. Destructor has
diagnostic/base/member-handle teardown. Outer factory retires existing owner
through4217C0, invokes allocator member510930, then initialize; failure retirement
uses41F7C0. Source combined nothrow/memset/placement/generic retirement differs.
No full StageClear/base/allocator owner is imported with artificial padding.

The eight level/phase getters are separate Player members, not a slot-based
free API with bounds exceptions. Bonus arithmetic is inline in native update,
repeatedly resolves Player, stores partial bonus and calls Session score member
488550. Source factoring captures Player and substitutes a Player score helper.
States1->2->4 and age120/input80001/age300, state6 and age10 completion/deletion
are corroborated; original helpers and lifetimes remain open. Draw preserves
native typed-handle lookup, GameController full-width freeze getter, position/
format/text calls, signed64-bit bonus grouping and animation-tree lookup.
Text reset4E67E0 is a190-byte member with fourteen ordered setter calls, whereas
reference writes fields directly. Complete Renderer and GameController owners
remain pending rather than introducing offset-only facades.

All eight binary32 constants and six CP932 strings including NUL independently
match the pinned PE and documentary constants. The hardcoded Windows extractor
was read, not executed; its assert, PE-span and output-alias assumptions remain
tool limitations. Its printed closure-table label is not native identity proof.

Retained95,232 passes are a subset of the shared2,915,831-check report, whose
hash and exact subset counters match;389/389 bound source hashes are current.
This is one historical run, not two independent or newly executed oracles.
Coverage:256 dirty-state constructors/empty destructors,8192 direct getter cases,
4096 updates,2048 draws using six existing cached text jobs. Factory/resource
I/O/scheduling, owned-node/handle destruction, state6/age10 self-deletion, new
job allocation, GDI, deferred scheduling and GPU are excluded. Audio mutex11
and game globals are manufactured fixtures. Retained freeze failure has220
failures,260/280 current hashes and20 stale paths; it is not current rejection
of all source. No inherited runtime acceptance or whole-game claim.

Private evidence: `.analysis/ref015-*`, serial reference receipts and complete
cold replay. Next coherent family: help_system25, then every remaining body.

## REF-014: all 21 game-session implementation entries reviewed

Every indexed body has a specific decision: thirteen nonexact and eight support.
The seventeen production definitions, four CPU-driver bodies, complete header,
CMake, README and both reports were read. The single unmodified production TU
compiles serially; CPU driver was not compiled, linked or run. No family parse
gap exists. Total857 terminal/6,087 pending; gaps17 reconciled/96 pending.
Production source and all66 canonical units are unchanged from REF-013.

Independent Ghidra queries cover22 native functions and21 are decompiled.
Original constructors return receivers, use scalar assignments and actual
array-construction/member calls; the reference substitutes free void initializers,
memset/fill_n/range loops and a new constructor wrapper. Native Player preserves
bytes+A6/A7 and+B1..B3; PlayerTable preserves+224..227; Session preserves+84..87.
Nonzero player defaults and two F0-byte player strides are corroborated. Typed
members and natural alignment remain open: reference explicit padding and
offset-grouped word arrays cannot establish full original declarations. Native
Session+2B0 uses XORPS/MOVSD; reference declares uint64. This is floating-type
evidence requiring consumer confirmation, not permission to reshape a class.

Session context lookup is thiscall with30-byte stride. Player lookup separates
Session->PlayerTable, global wrapper and F0-byte indexed PlayerTable member.
Primary/overlay wrappers call actual context members returning stored pointers;
reference CallbackOwner*& returns pointer-field addresses. The five source alias
checks never execute those original getters and cannot prove their return ABI.
Default-player binding and combined flag clearing are new source convenience
functions rather than additional original entries. Each setter/counter body is
deferred on its own receiver/type/partition evidence, without fabricated prefix
padding. Native continue increment receives Session in ECX; reference free
no-argument increment uses a global. The native add stores modulo32 ADD before
passing the member and local0/9 bounds to a reference-returning clamp chain;
independent signed comparator evidence overrides Ghidra's misleading
_Find_unchecked library label. Source local memcpy/clamp changes that partition.

Retained14,342 passes are14,337 isolated native comparisons and five source-only
alias checks. Dirty storage tests meaningfully exercise retained padding, but
pointer types, real global initialization, helper ABI and original getter calls
are not proven by byte equality. Module4/4 source hashes are current; no execution
receipt was inherited or tests rerun. Output alias/write/exception cleanup gaps
are recorded separately. REF-013's CPU-driver review note is corrected: that
driver was read only; its eight compiled TUs comprise seven production sources
and the source-only backend smoke. All eight compilation results stand.

Private evidence: `.analysis/ref014-*`. Next coherent family: stage_clear's17
entries, then every remaining implementation and manual gap. The exhaustive
goal remains active; authored49/3,692 and canonical66/18objects/4,620 unchanged.

## REF-013: all 122 audio-runtime implementation entries reviewed

All 122 C++ bodies have individual hash-bound decisions: four absorbed exact,
63 nonexact and 55 support. Full source, three owner headers, constants, both
test drivers, COM fixtures, README, CMake and the retained CPU report were read.
All eight unmodified production/test translation units compile serially with
the diagnostic recipe; neither test program was linked or run. Four WINAPI
annotation gap files are manually reconciled against all actual definitions.
Coverage is now 836 terminal and 6,108 pending; gaps17 reconciled/96 pending.

Independent attested Ghidra queries and decompilation cover 78 native functions,
including the separately queried memset anchor before constructor probes.
Natural maintained records restore actual constructor and release ownership:

| Target | Complete bytes | Maintained contribution |
| --- | ---: | --- |
| 0x00425CE0 | 55 | SoundEffectRequest constructor |
| 0x00425FC0 | 65 | SoundCommand constructor |
| 0x00425D20 | 73 | SoundEffectChannel constructor |
| 0x00428380 | 46 | SoundEffectChannel::release |

The first two constructors store scalar fields then memset their actual arrays;
all return the receiver with thiscall ABI. The reference free void bulk
initializers have a different partition. Release invokes COM slot2 and clears
the pointer conditionally. Full cold replay passes66/66 units across18 objects,
4,620 full bytes. Authored exact is49 functions/3,692 bytes; source-present66.
Three constructor origins remain pending, bringing origin-pending exact units
to13; they are excluded from authored progress. Portable dirty-storage tests
check all request/command bytes and channel fields. No COM driver is executed.

Specific native differences and remaining owner work are recorded per body:

- SoundInf construction calls real array/PMR helpers; CRT startup separately
  clears0x57E8. The reference zeros more retained fields and adds Context.
  Its historical native constructor fixture prezeros storage, masking this.
  Ready returns full int, whereas the reference returns bool. The preload
  predicate belongs to Graphics at+24C, not the reference SoundInf adapter.
- Native audio initialization returns-1 for device/buffer/channel failures,
  1 for resource-load failure and0 on success; reference void loses statuses.
  Effect creation receives Channel in ECX and reads fixed SoundInf globals;
  reference receives SoundInf plus Channel&. Device factory4259A0 is not a
  constructor. Full SDK, PMR, diagnostic allocator and fixed-global ownership
  remain open. The natural stop probe has100 versus120 bytes (GS/local state);
  DeviceOwner destructor93 versus88 bytes (EH partition), both deferred.
- Primary format success-with-null buffer yields E_FAIL in native but can
  return S_OK in reference. Native releases only after successful SetFormat
  and normalizes success to S_OK; reference changes failure cleanup/status.
  Preload returns int and writes fixed track-name globals; reference void,
  bounded vector access and receiver fields change the contract.
- The native stream has separate CSound/CStreaming base/derived construction,
  vtables and destruction. Reference merges them, zeros retained fields and
  appends a parent pointer. Restore returns S_FALSE when no restoration is
  needed; reference returns S_OK. Skipped notification returns an error in
  native and S_OK in reference. Both reject a second lock region, but source
  adds zero-progress exceptions to native refill loops. Set-volume is native
  void; reference HRESULT. Four native fade functions become one mode API.
- WaveReader constructor initializes selected blocks rather than all160 bytes;
  separate factory clearing does not establish constructor equivalence. Its
  opaque MMIO regions require actual SDK declarations. File/reset/reopen use
  fixed globals instead of reference extra base-offset parameters. Native
  failed ReadFile can leave received count uninitialized; source initializes
  it. Native thread ignores its passed HWND and uses fixed globals/plain busy;
  source receiver/atomic_ref/zeroedMSG changes threading and initialization.

Ninety20-byte definition records, all72 pointer-selected NUL-terminated file
names and five float constants independently match the locked PE. IDs cover
0..89 in an unsorted table; native binding searches IDs while request cooldown
indexes the table by ID. These are DATA comparisons, not executable exactness.
The historical CPU report records31,219 cases/zero failures with12/12 current
input hashes. It maps isolated calls, substitutes imports/heap/clock/PMR/COM,
normalizes pointer/vptr values, excludes added fields and skips selected
allocation/join stages. It cannot establish whole-game, real thread, failed I/O,
driver or audible-output equivalence. No backend_validation.json is present in
the pinned checkout; the README's source-only silent smoke claim is not a
retained result. Neither historical test was rerun or inherited as acceptance.

Private evidence: `.analysis/ref013-*` and serial compiler receipts.
Next coherent family: game_session's21 entries, then every remaining body and
96 manual gap files. The exhaustive goal remains active.

## REF-012: all 49 startup-scene implementation entries reviewed

All 45 C++ definitions and four Python function/module entries have individual
decisions: two absorbed exact, eleven deferred and 36 support. The nineteen
production definitions include newly introduced namespace bridges; the other
26 C++ bodies are the named-spawn fixture. Both production TUs, the owner/data
headers, scripts, CMake recipes and retained reports were read in full. No parser
gap occurs in this family. Both unmodified TUs compile serially; no link or
original loading-worker execution is claimed.

Independent attested queries cover 37 native functions, including every
dependency of the shared-resource routines; 32 are also decompiled. Natural
maintained orchestration restores the omitted calls and observed ABI:

| Target | Complete bytes | Maintained contribution |
| --- | ---: | --- |
| 0x004D82C0 | 134 | initialize_shared_scene_resources |
| 0x004D8560 | 62 | release_shared_scene_resources |

Both functions retain eight calls, including three calls to the observed
zero-return helper 0x4A7700. Initialization preserves each early -1 return and
does not unwind previous resource acquisitions. Release passes zero to stone
cleanup 0x51B6D0; the callee currently ignores that stack argument. Independently
observed HUD/trophy release entries return full int0, unlike the reference void
interfaces. Original caller/callee evidence precedes compiler probes; all sixteen
REL32 fields have independently established canonical anchors. Resource types
are forward declarations and their dependency implementations remain undefined.
These component comparisons do not establish complete resource ownership/linkage.

Cold replay passes 62/62 complete units across sixteen objects, 4,381 bytes.
Authored exact: 48 functions, 3,646 bytes; source-present: 62. Pure fixture tests
cover successful order, all three factory-null paths, trophy failure, immediate
stopping without rollback and the complete teardown order. They use pointer
tokens that are never dereferenced; no original resource/API is executed.

LoadingInf's observed 0x61C layout is corroborated, but its complete typed
Animation/base/Worker owner remains open. Native constructor/destructor invoke
separate handle/member/no-op calls; the reference changes that partition and
allocator/EH protocol. The factory replaces a diagnostic allocator receiver
with nothrow new, zeroing, placement construction and catch cleanup. Registration
replaces the real Worker function/captured-argument protocol with nested mutexes
and a new jthread closure. The draw routine changes plain readiness loads/stores
to atomic_ref operations. The worker's native argument storage is overwritten
from the global after Sleep; the source drops the argument and uses direct
chrono tick assignment instead of the original slot-indexed timepoint method.
Scene shutdown is a native thiscall function although it uses fixed globals;
the source free bridge and combined flag helper change its ABI/partition.
Each of these bodies has a specific pending-owner or behavior record.

Two strings and two floats independently match the locked PE. The startup
module report has four of six current input hashes; startup.cpp and CMake are
stale. Named-spawn's four input hashes are current, but record_evidence rewrites
hashes and module reports without rerunning its CPU tests. Retained 4,096 cases
and 24,576 checks cover selected groups, flags, stems, placement and layers;
they do not attest the full loading scene, ordinary startup, threading or gameplay.
The fixture snapshots only selected lists, sixteen pool entries, generation and
free-list fields, and throws for unexercised RNG/geometry/effect dependencies.
Actual named_spawn production bodies await the sprite_renderer family review.
No reference evidence tool was run or checkout file changed.

Coverage: 714 terminal and 6,230 pending; gaps remain thirteen reconciled and
100 pending. Private evidence: `.analysis/ref012-*`. Next: audio_runtime's
122 indexed C++ entries, then all remaining bodies and manual parser gaps.

## REF-011: all 189 platform-window implementation entries reviewed

Every one of the 170 C++ definitions and 19 Python function/module entries
has an individual body-hash-bound decision: four absorbed exact, 65 native
deferred and 120 support. All twenty production translation units, six headers,
both CPU fixture sources, four Python files, CMake recipes, dialog definitions
and retained reports were read. Twenty unmodified production TUs compile
serially with the pinned x86 compiler and their actual inherited include paths;
this does not establish linkage. Seven parser-gap files are manually reconciled,
including annotation-only headers and fixture inline assembly. No definition
was omitted and no reference file was changed.

Independent attested disassembly and decompilation cover 68 native functions.
Five natural maintained contributions add 190 authored bytes. Repeat reset is
recovered from window creation; the enclosing creation function remains deferred.

| Target | Complete bytes | Maintained contribution |
| --- | ---: | --- |
| 0x00419C00 | 22 | InputButtonState::pressed_bits |
| 0x0041A280 | 61 | InputButtonState::repeated_or_pressed |
| 0x0041CC90 | 40 | WindowState::RepeatCounter::reset |
| 0x0041D0C0 | 47 | is_japanese_user_locale |
| 0x00414820 | 20 | mark_font_available |

The input methods preserve ECX, RET4, raw uint32 masks and the separately
anchored pressed-method call; the second method uses repeat8, not repeat12.
Native creation supplies four reset arguments 15/12/12/8 to twelve-byte embedded
counters. Locale detection returns int, unlike the reference bool. Its actual
LCID local holds the API observation. Font enumeration returns int1 with RET16
and writes through the independently observed global pointer. KERNEL32 import
0x56C0A4 and font initialization 0x416D20 establish import/global anchors before
canonical replay. Font initialization and pointer storage remain undefined.

Cold replay passes all 60 complete units across fifteen objects, 4,185 bytes.
Authored exact: 46 functions and 3,450 bytes; source-present mappings: 60.
Portable tests cover raw bit31, pressed/repeat precedence, excluded repeat12,
query nonmutation, reset edge values and adjacent-counter preservation. Locale
and font APIs were compiled and compared, not invoked.

Several deferred functions have concrete behavior or ABI disagreements:

- Native settings_dialog_proc 0x41ABE0 returns 0 for initialization, rejected
  raw input and unrelated commands; the reference returns 1. Navigation in
  0x41AE70 queries IsWindowEnabled rather than its own disabled-control array.
- Encoder lookup 0x4D97F0 returns int and uses a diagnostic allocation family;
  the source bool and generic allocate/free protocol differ. Snapshot worker
  0x4D9210 returns int0 and uses a distinct new/zeroing helper. Capture 0x4DE040
  returns -1/1/0 on its observed paths; the source void loses those statuses.
- Game-data opening 0x4D9EA0 returns -1/0 and receives an owned raw buffer with
  a size output. The source drops the status and reallocates a vector copy.
  Wall-time update 0x4AC0E0 returns the receiver's +0xD0 record and uses chrono
  helpers; the reference void/direct tick conversion changes that protocol.
- Graphics layout, viewports, camera, device state, presentation, callbacks and
  lifetime still require their real PMR/worker/global owners and native member
  partition. New scalar/helper factoring, table loops, dynamic SDK loading and
  opaque storage do not reproduce the original contributions. Each body has
  its own narrower finding and remaining work in the review ledger.

Forty read-only data declarations compare independently with the locked PE:
twelve narrow strings, two UTF-16 strings, four int arrays, fourteen floats and
eight doubles. Original Japanese dialogs 203/204, language1041, are 914/1,012
bytes and their hashes match the retained resource report. No fresh RC compile
is claimed. No extracted game data or reference production bodies are imported.

Retained CPU results are evidence of their stated historical fixture scope.
The 30,867 platform passes include three source-only thread cases; ordinary
entry/TLS startup, complete OS-message behavior, real GPU output and gameplay
are excluded. Logical font comparisons exclude HFONT/glyphs and unused tails.
The texture fixture's 222,014 cases cover selected pixel/helper and COM traces;
its implementation belongs to the still-pending sprite_renderer review.
Its record_evidence tool rewrites source hashes in an old CPU report without
rerunning the oracle, so current hashes alone cannot attest fresh execution.
The module report has only 23/31 current hashes and eight stale inputs, alongside
29 missing domain and 73 missing source symbols. Its tests were not rerun and
its linkage/completion claims are not inherited. Extraction utilities also have
assert-only SHA gates and partial resource/range checks, recorded individually.

Coverage is now 665 terminal decisions and 6,279 pending; parser gaps are
thirteen reconciled and 100 pending. Private evidence: `.analysis/ref011-*`.
Next coherent family: startup_scene's 49 indexed entries, then every remaining
native/script implementation and manual parser gap.

## REF-010: diagnostics' seven implementation entries reviewed

All four implementation files, CMake, four debugger logs, both ASAN reports,
six state snapshots and three retained build manifests are reviewed. Three C++
functions, two Python functions and two script modules each receive an explicit
support decision. None implements an original game function. Current terminal
coverage: 476 entries; 6,468 pending. Parser gaps remain six reconciled and
107 pending out of 113. Existing 55 canonical units and authored 41/3,260 bytes
are unchanged; no production source/profile/anchor changed, so no new cold
replay was needed.

The minidump parser reads module stream4 only, despite its thread-metadata
comment; it trusts counts, offsets and strings and guards the magic by assert.
The DIA utility uses PDB regular-expression data lookup or RVA function/line
queries without checking PDB/image identity. Error handling leaves unchecked
COM initialization/export/numeric input paths and incomplete failed cleanup.
The optional DIA SDK header/runtime is absent locally; no fresh DIA build or
run is claimed. The source debugger TU freshly compiles unmodified with pinned
x86 MSVC; it was not linked or launched.

The live-state tool checks only executable basename and combines PDB RVAs
with the enumerated base. It does not match GUID/age or image hash, suspend
threads or obtain a coherent snapshot. Its fixed x86 offsets are source-build
assumptions; the returned module count can exceed the 1,024-slot array. Exact
ReadProcessMemory byte-count checking helps, but separate reads can tear and
cannot establish native layout or whole-frame equivalence.

The debugger isolates APPDATA, permits two source-build filenames and handles
second-chance exceptions, stack traces and minidumps. These are filename guards,
not cryptographic identity checks. It leaves several API results unchecked,
allows a child to survive debugger failure, and omits exception information in
the MiniDumpWriteDump call. Its optional ASAN mode continues only an announced
interception-warning breakpoint; the tool itself explicitly denies complete
sanitizer validation in that mode. Stack walking is fixed i386 and may duplicate
the first PC; unsymbolized addresses do not identify original function owners.

Retained observations include a null-read crash, heap-corruption crash, enemy
iterator use-after-free and laser operator-new/free mismatch. These belong to
historical source builds, not freshly reproduced original behavior. Six states
sample source processes reaching stages1/3; separate fields and frame samples
do not prove complete runs or matching game state. The accompanying runtime
report also distinguishes these limits. Manifests list462/463/463 source inputs;
447/454/454 match the pinned checkout and15/9/9 are stale. All three explicitly
set full_game_equivalence_verified=false. No diagnostic utility was invoked,
process attached, private build rerun or reference checkout changed.

Private evidence: `.analysis/ref010-*`. Next: platform_window's189 indexed
implementation entries, then all remaining native/script bodies and manual gaps.

## REF-009: program entry and frame schedulers reviewed

All six C++ source/header files, both Python tools, README, CMake and retained
symbol/call-graph reports are read in full. Every one of the 26 C++ definitions
and eight Python implementation entries has an individual decision: six
absorbed exact, eight native deferred and twenty support. No parser gap occurs
in this family. Current totals: 469 terminal decisions; 6,475 entries pending.

| Target | Complete bytes | Maintained contribution | Authored credit |
| --- | ---: | --- | --- |
| 0x0041CC70 | 20 | WindowState::display_mode | 20 |
| 0x0041D080 | 25 | WindowState::needs_device_reset | 25 |
| 0x0041DCC0 | 22 | WindowState::set_draw_counter | 22 |
| 0x0041DE00 | 44 | WindowState::set_device_reset | 44 |
| 0x0041DE30 | 25 | WindowState::set_reset_delay | 25 |
| 0x0041B490 | 81 | WindowState::restore_system_settings | 81 |
| 0x00418DD0 | 108 | WindowFlags::Bits default construction | Origin pending |
| 0x0041B480 | 16 | Foreground API wrapper | Origin pending |

Independent CRT global initialization and the complete window constructor
establish an 8,496-byte naturally aligned WindowState. The member at +0x2098 is
a double, rather than the reference's unknown byte range. Real pointer, pair,
path, clock and repeat-counter fields explain the storage without explicit
padding. Five methods restore the original thiscall ABI; needs_device_reset
returns uint32 rather than the reference's free bool. Native flags clear bits
0..7, with bits 3..4 a single two-bit field, and retain the high 24 bits.
Main supplies draw counter -4; frame consumers increment its signed-byte storage.

System restoration saves ECX but reads three option bytes from the fixed global
at 0x5B6758, rather than the reference's receiver. Independently identified
SystemParametersInfoW IAT and WINNLSEnableIME thunk establish all anchors and
COFF addends. Tests do not execute this method or mutate system settings.
The foreground wrapper's sole observed caller ignores its result; its original
source/origin identity remains pending. Exact default-bitfield initialization
also remains outside authored credit until origin is established.

Cold replay passes 55/55 complete units across fourteen objects, 3,995 bytes.
Authored exact: 41 functions, 3,260 bytes; source-present mappings: 55.
The eight new contributions total 341 bytes, including 217 authored bytes.
Portable tests cover all signed-byte values, field isolation, flag preservation,
delay/mode edge values and low-byte flag construction. Original WindowState
construction, fixed-global storage and startup remain undefined; fixture value
initialization is explicit test setup, not accepted native startup.

The original main has a corrected four-argument WINAPI ABI and complete
2,537-byte extent. CRT entry/cookie/tail jump and argument pushes independently
corroborate it. Reference MSG zeroing, free/injected APIs, omitted proven no-op
calls and replaced resource/global lifetime prevent exactness. Native frame
schedulers have complete extents 433/583/370 bytes; reference arithmetic/draw/
update helpers change partitioning and omit the full constant-zero member.
Clock locking, COM/graphics ownership and complete frame runtime remain open.
Graphics getters/releases await its real PMR/config/viewport/jthread owner;
opaque reference ranges cannot substitute for that declaration.

The symbol report enumerates 50 unresolved functions, 13 globals, two scheduler
imports and 23 platform symbols in its retained build. It is not fresh link or
runtime evidence. The selected graph has 22 nodes and 194 static edges; it uses
historical analysis tables and omits indirect calls. All five retained CP932
constants independently match the locked file, but none was copied into
production source. Neither reference tool was executed or allowed to rewrite
the pinned checkout. Three unmodified production TUs compile serially.

The inventory now includes previously omitted scripts: 238 additional entries.
All 6,706 existing C/C++ rows and 435 previous review bindings remain unchanged.
Synthetic parser checks cover decorated/nested Python, UTF-8 offsets, lambdas,
function-free modules and explicit PowerShell gaps. These new pending entries
expand exhaustive coverage; they confer no review or exact credit by discovery.
Private evidence: `.analysis/ref009-*` and fresh compiler receipts.

## REF-008: runtime state's 27 definitions reviewed

All six source/header/oracle files are read in full. Twenty-seven actual
bodies have individual decisions: five absorbed exact components, one library
normalization, seven native cases deferred and fourteen support helpers. Both
READMEs, CMake and the two retained CPU reports are also reviewed. No parser
gap occurs in this family. Total decisions: 435; 6,271 bodies remain pending.

| Target | Complete bytes | Maintained contribution | Authored credit |
| --- | ---: | --- | --- |
| 0x00422C50 | 85 | GameRandom constructor | 85 |
| 0x00423EA0 | 49 | GameRandom::bounded | 49 |
| 0x00429830 | 113 | GameRandom::unit | 113 |
| 0x004298E0 | 129 | GameRandom::signed_unit | 129 |
| 0x00422C30 | 29 | Standard engine default constructor | Library excluded |
| 0x00422C00 | 36 | Standard engine seed normalization | Library excluded |
| 0x004292A0 | 25 | ClockScalar::set | Origin pending |

The 28-byte owner contains an actual four-byte standard engine at +4, range
fields at +8/+12/+16, last raw sample at +20 and stream id at +24. Four separately
queried CRT startup callers establish ids and object addresses; process-global
startup is not imported. The explicit uint32_t standard engine also keeps this
layout on portable hosts with wider uint_fast32_t. Installed MSVC's random
header independently explains the normalization/default-construction bodies;
Ghidra's locale name at 0x422C30 does not establish library identity.

Ordinary unsigned-to-float casts naturally emit the original staged binary64
correction and binary32 conversion. Extra explicit double casts did not explain
the original emission. Callee 0x423EE0 and file-backed double table {0,2^32},
float 1 and float 2 were independently checked before canonical anchoring.
Bounded zero skips sampling; signed_unit uses modulus/2-1 then subtracts one
without a clamp. Shared setter uses the original float receiver and RET4,
not the reference's fixed-global free-function ABI. Its origin remains pending.

Cold complete replay passes 47/47 units, twelve objects, 3,654 full bytes.
Authored exact: 35 functions, 3,043 bytes; source-present mappings: 47.
Portable checks cover default construction, edge seed normalization, zero/count
sampling, high-bit conversion, rounding near 2^24 and unclamped signed output.
A clearly marked test-only next fixture supplies deterministic observations;
maintained GameRandom::next remains undefined until its lock-slot-10 protocol
is recovered. No linked sampler or full game-global lifetime is claimed.

Native seed/next use fixed lock storage, tracked guards and security cookies;
source mutex references, aggregate adapters and domain_error on zero modulus
are separate contracts. Motion's raw floats/free functions replace native
scalar/angle/vector receivers, hidden aggregate returns and fixed-rate reads.
Complete switch tables, float floor helper and original Motion declaration
remain deferred. Bounds returns a native 32-bit integer, unlike source bool.
The simple combined member awaits that same canonical Motion owner.

The retained RNG report's 164,000 comparisons use manufactured lock ownership,
a single resolved thread-id IAT and prepared four-mode floating environments.
Zero-modulus fault, original entry/TLS/global startup and cross-thread ordering
are outside the evidence. Motion's 41,984 comparisons force the host SSE4.1
floor path and nearest rounding: finite trajectories, bounds including NaNs
and zero-state constructors do not cover nonfinite trajectories or other FP
modes. Both report writers lack an input/output alias guard; the motion report
omits a target-hash field, although its driver checks the target before mapping.
These retained reports were read, not freshly rerun or credited as exactness.

Both unmodified production TUs compile serially after adding the include paths
actually propagated by their reviewed ECL/binary CMake dependencies. The
initial missing-header diagnostics were recipe gaps, not source defects.
Private evidence: `.analysis/ref008-*` and fresh compiler receipts.

## REF-007: platform services' 43 definitions reviewed

All ten C++ source/header files are read in full, with individual decisions for
43 actual definitions: two absorbed exact components, fourteen native cases
deferred with specific differences and twenty-seven support helpers. The
README, CMake recipe, CPU-validation report and top-level extract_evidence.py
are also reviewed. That Python helper has no function definitions: its hash
guard is useful, but hardcoded paths and prefix extents are diagnostic only.
Total decisions: 408; 6,298 definitions and 97 parser-gap files remain pending.

| Target | Complete bytes | Maintained function | Authored credit |
| --- | ---: | --- | --- |
| 0x0041FB10 | 309 | InputBindings constructor | 309 |
| 0x0041FC50 | 85 | InputBindingSlots constructor | Origin pending |
| 0x004B9B80 | 137 | ConfigurationFlags constructor | Origin pending |

Three 16-byte signed binding records recover the original receiver ABI,
member-default construction and twenty-four assignments. Native signed loads
and disabled -1 bindings independently corroborate the int16 fields. The
zeroing member constructor is independently queried before anchoring three
REL32 calls. Flags initialize nine one-bit members individually and preserve
bits 9..31. Native configuration construction and six independent graphics
option consumers corroborate storage and named bits. The complete 176-byte
configuration owner is still deferred. Default-slot and flag constructors
might be compiler-generated contributions and receive no authored credit.

Cold complete replay passes 40/40 units, eleven objects, 3,188 full bytes.
Authored exact: 31 functions, 2,667 bytes; source-present mappings: 40.
Portable checks cover all signed defaults, standalone slot zeroing and retained
high flag bits in preinitialized storage. Four unmodified reference production
TUs compile serially; this does not accept their native protocols.

The CPU oracle's five flat inline-assembly statements caused two phantom
bodies and hid the actual enclosing original_conversion function. Narrow
parse-view normalization recovers that owner and removes both phantoms; all
365 prior reviewed IDs/body hashes remain unchanged. Regression verifies
original body/file hashes and offsets. Two remaining WINAPI annotation gaps
are manually reconciled; the reference files remain untouched.

Deferred native clock code uses fixed globals, lock-5 tracked guards and a
special compiler conversion ABI. Its full unsigned-conversion helper includes
feature-dispatched AVX512VL code; testing only SSE2 is not complete equivalence.
Native rounding returns an integer status through separate CRT helpers, while
the reference uses a bool adapter. Writer lock-2/EH, 522-byte buffer clearing,
uninitialized write count, raw allocator/file ownership and returned save status
are not recovered by the source RAII/vector/void replacements. Initialization
uses one retained 4096-WCHAR scratch buffer and writes system-option results to
adjacent globals; no system-setting mutation was executed during this review.

The reference's missing-%s argument comment is contradicted by native pushes:
0x4DC473..476 supplies the filename, and caller 0x41E8E5 supplies th20.cfg.
The source instead logs a joined path. Source path initialization also appends
a log entry where the native path calls a verified no-op, changing normal-path
behavior. Truncated-file rejection and eager zero initialization differ too.

The retained 66,270-check CPU report includes fourteen source-only decode
checks, leaving 66,256 native fixture checks. It maps the target without normal
entry/TLS startup, manufactures lock/global/IAT state and forces SSE2. NaN/
subnormal offsets, feature-dispatch variants, real files/path initialization and
cross-thread scheduling are outside that evidence. Reports and source-only
Windows service tests were read, not rerun or credited as native exactness.

Private evidence: `.analysis/ref007-*` and fresh compiler receipts.

## REF-006: input's 84 definitions reviewed

Every definition in all seven input source/header/test files now has an
individual hash-bound decision: five absorbed exact components, twenty-eight
native cases deferred with specific differences and fifty-one support helpers.
Both parser-gap files are manually reconciled: nine WINAPI callback annotations
and two CALLBACK annotations; all actual bodies are present in the index.
Total review decisions: 365; 6,342 definitions and 98 parser-gap files pending.

| Target | Complete bytes | Maintained function | Relocations |
| --- | ---: | --- | --- |
| 0x00421720 | 50 | InputDevice::reset_header | None |
| 0x00421AB0 | 31 | InputDevice::initialize_keyboard | None |
| 0x00421AD0 | 40 | InputDevice::initialize_xinput | None |
| 0x00420510 | 105 | map_input_byte | None |
| 0x004228B0 | 583 | InputButtonState::update | Eleven REL32 calls |

The original Device entries are thiscall members, while the reference exposes
free functions. Maintained members restore the original receiver, parameter
widths and callee stack cleanup. Reset affects only the first sixteen bytes;
keyboard/XInput initialization preserves other header fields and all history.
The byte-mapping helper retains separate conditional OR and return expressions,
including the second byte read after the store and disabled negative bindings.

ButtonState is 704 bytes; Device is 980 bytes on x86, with state/raw/tail at
+0x10/+0x2D0/+0x3D0. Native constructor, poll and frame consumers corroborate
retained storage rather than arbitrary padding. Update walks a real array of
32 counters using progressive remaining-input and output-bit cursors. Unsigned
wrap, threshold-eight held mask, first repeat at frame 26 and eight/twelve-frame
recurrences remain intact. Retained arrays and suppression/device-kind words
are preserved. The independently queried callee 0x414580 implements receiver
plus index*4 with RET4; installed MSVC std::array indexing matches its contract.
Canonical relocation anchors use that separate observation, not solved fields.

Cold complete replay passes 37/37 units, ten objects, 2,657 full bytes.
Authored exact: 30 functions, 2,358 bytes. Portable checks exercise frame cadence,
bit31, releases, wrap, retained state, partial-header initialization and negative/
high-bit byte bindings. All three unmodified input production TUs compile in
serial diagnostics; compilation alone grants no native acceptance.

Deferred entries preserve specific ABI/ownership differences. Native polling,
legacy polling, startup sampling, shutdown, rebuild, XInput enumeration and
whole-frame sampling produce results that the reference drops as void. Device
DirectInput initialization has a Device receiver; reference moves it to
Controller. Native Controller owns 0x2EF8 bytes, TaskInf/RTTI/EH and fixed globals;
reference appends a context pointer and introduces Host virtual dispatch.
Native enumeration callbacks ignore userdata and use singleton/device globals;
reference uses injected userdata. WMI deliberately differs in BSTR allocation
and VariantClear behavior. Keyboard-clear failure and invalid mapping/selection
exceptions are changed policies. Native bit mapping's wide x86 shift domain
still needs a defined natural C++ explanation before exact acceptance.

The upstream 44,271 CPU comparisons are reviewed retained evidence, not a fresh
run. The oracle maps the target and initializes original locks but bypasses
ordinary entry/TLS startup, fixtures OS/COM observations, excludes vptr/context
from Controller comparison, and checks empty COM shutdown. Live discovery,
original allocator/teardown and concurrent reconfiguration remain unverified.
Support adapters and fixtures are individually reviewed without game credit.

Private evidence: `.analysis/ref006-input-*.asm`, `ref006-input-*.decomp`,
`ref006-input-compile.log`, `ref006-exact-replay.log` and compiler receipts.

## REF-005: tools and root/scheduler tests reviewed

All 39 tooling/support definitions, 37 root test definitions and 15 scheduler
CPU-oracle definitions now have individual support-reviewed decisions. These
91 reviews cover binary/PE/ECL readers, serialization and reporting, CLI output
guards, indexed asset extraction, synthetic parser fixtures, target mapping,
floating-point preparation and scheduler state normalization. They grant no
native exact credit. Native core's indexed production bodies were already
reviewed; the next coherent production family is input, with 84 definitions.

The scheduler oracle's forward declarations were incorrectly parsed as one
extra `shutdown_callback` body swallowing the following `World` class. Narrow
annotation normalization removes that unreviewed phantom and its three parser
errors; all 190 prior review IDs and original body hashes remain unchanged.
A synthetic regression checks real definitions, preserved offsets and original
hashes. Two further gaps are manually reconciled: CLI Windows/POSIX conditional
entry declarations share one body; root CPU-test inline x87 instructions are
inside already indexed functions. Neither omits another implementation.

The portable binary-parser CTest passes, including 928 ECL bit mutations, but
its stricter error policies are tool contracts. CPU tests map the original
without ordinary entry/TLS startup and prepare a fixed FP environment; x87
control-word restoration does not restore the full floating-point stack/status.
Scheduler tests manufacture nodes and callbacks, disable source dispatch locking
and normalize address-like state words. Owned-node allocation is source-only.
These tests do not establish native allocation, renderer shutdown, cross-thread
locking, exception unwinding or complete raw-byte equivalence.

Production source, profiles and relocation anchors are unchanged. The existing
32 complete exact units remain the last cold replay checkpoint; no new exact
claim is added by this review batch. Private evidence: `.analysis/ref005-*`.

## Native core: accepted components

The original target, retained reference bodies and our maintained C++ have
been checked individually. Validation-only free functions and export adapters
are distinguished from the original ECX receiver ABI.

| Target | Complete bytes | Maintained function | Exact replay | Authored credit |
| --- | ---: | --- | --- | --- |
| 0x00423FE0 | 38 | Timer::set_mode | Passed | 38 |
| 0x004530F0 | 295 | Timer::add | Passed, eight relocations | 295 |
| 0x004533B0 | 324 | Timer::tick | Passed, ten relocations | 324 |
| 0x004292E0 | 16 | ClockScalar::operator float | Passed | Origin pending |
| 0x00452F50 | 35 | ClockScalar::operator* | Passed | Origin pending |

Existing Random and Timer reset/set units still pass. Current cold replay is
forty-seven complete units, 3,654 bytes, twelve independently rebuilt objects.
Authored credit is thirty-five functions, 3,043 bytes. Four standard engine
contributions are excluded as STL; the three shared float-view functions, three empty/defaulted lifetime
contributions and two configuration initializer contributions remain under origin review and are not added to authored totals.
Exact names do not establish an enclosing clock or
interpolation type.

### Mode representation

Both orders of the raw masked-word expression were investigated: they differed
from the full target by three or seventeen register/instruction bytes. A
natural two-bit field assignment emits all 38 bytes exactly. The maintained
Timer has shared raw-word/bit-field union views of its observed four-byte flag
storage: bit 0 initialized, bits 1..2 mode, and the other 29 flags preserved.
This uses the MSVC x86 representation, with GCC's supported union view used
by portable state-invariant tests. It adds no padding or alternate body.

### Clock protocol and independent anchors

Add and tick initialize lazily, conditionally clear nonzero modes, select the
default clock slot, and save the previous integer. Add accumulates a scaled
delta and truncates. Tick's near-one/null paths increment the integer
independently of its float value; other rates accumulate then truncate.

The reference supplies a rate pointer as an extra parameter and replaces the
original float receiver calls with intrinsics. Maintained members restore the
target ABI, repeated float reads and actual helper calls. Scalar conversion
and multiplication are independently checked as complete 16/35-byte target
bodies, including x87 float returns and SSE multiplication.

Before canonical relocation comparison, independent Ghidra xrefs/disassembly
and raw file-backed data establish the default slot at 0x005AEFE0, initially
pointing to the 1.0f storage at 0x005AEFE4. Only the observed default slot is
declared; Timer add/tick clamp the selected mode to zero. This does not invent
four valid pointers from adjacent unrelated storage. Constants at 0x0056E72C
and 0x0056E730 encode 0.99f/1.01f; independently referenced 0x0056C8CC is 1.0f.
These anchors were inspected before the structural diagnostic reported any
solved destinations. Reset/mode anchors already have independent full units.

Portable tests cover initialization, flag preservation, interval endpoints,
null/default clocks, fractional accumulation, independent integer/float
values, and integer wrap. Float-to-integer tests use finite representable
inputs. Locked target-identical x86 emission also preserves CVTTSS2SI hardware
behavior; no broader portable invalid-conversion contract is asserted.

The 0x00423520 forwarding entry is independently inspected (26 bytes, 174
callers). Its enclosing declaration/origin remains a follow-up, rather than
inventing a constructor or return contract to gain another match.

## Scheduler: all 35 indexed implementation bodies reviewed

Every definition in scheduler.cpp and scheduler.hpp has an individual
body-hash-bound outcome: eleven absorbed exact, eighteen reviewed nonexact,
and six integration/support helpers. Tests and callers in other files still
need their own review; this is not a module-wide completion claim.

| Maintained contribution | Original entry | Complete bytes |
| --- | --- | ---: |
| Link constructor | 0x00411970 | 64 |
| Link::insert_after | 0x00411EE0 | 76 |
| Link::insert_before | 0x00411F30 | 76 |
| Node::set_callback | 0x00412D50 | 42 |
| Node::set_userdata | 0x00412D10 | 22 |
| Node::set_owned | 0x00412D30 | 26 |
| Node::enable | 0x00412D80 | 26 |
| Node::disable | 0x004127F0 | 26 |
| Node::set_before_insert | 0x00412DC0 | 22 |
| Node::set_shutdown_callback | 0x00412DA0 | 22 |
| Node::clear_callbacks | 0x00411B80 | 41 |

All eleven pass complete canonical replay with no relocations: 443 authored
bytes. Target node construction and link consumers independently establish
five Link pointer slots and 20/44-byte x86 Link/Node storage. Dispatch's
indirect calls pass userdata on the stack, clean four bytes in the caller,
and inspect EAX, establishing cdecl int32(void*) callback ABI. The /Gd profile
states that calling convention explicitly. Portable tests check flag masking,
callback clearing without invocation, link initialization, neighbor insertion
and null-end branches.

The pointer stores at 0x00412DA0/0x00412DC0 also serve equivalent Link
observer/owner accessors. Each original address receives credit once; shared
emission does not establish a unique Node owner. List/Iterator allocation,
construction and destruction are not inferred from matching setters.

Deferred cases have individual reasons in reference-function-reviews.csv.
Examples include Iterator construction's two original stack arguments versus
one reference argument; Node/Iterator FS/EH registration missing from free
initializers; the List/base constructor's two tail stores; allocator/debug
owner indirection; merged update/draw APIs with extra Environment/bool
arguments; original separate accessor calls; and shutdown's missing renderer
flush at 0x004D9E30. These are current direct-absorption limits, not proofs that
future natural reconstruction is impossible. No padding, inert stores or
invented signatures were added to force them.

Private independent evidence is in .analysis/ref002-scheduler-{leaves,links,
dispatch,remaining}.* and exact-replay-004.log. Reference TU compilation is
only diagnostic; no behavior claim is inherited from its passing tests.

## REF-003: runtime_core's 67 explicit definitions reviewed

All nine nongenerated runtime_core source/header/include files were read.
Their 52 candidate and 15 test/oracle definitions each have a body-hash-bound
decision: nine absorbed reference bodies, twenty-four deferred native cases
and thirty-four integration/test helpers. Those nine absorbed bodies restore
eleven distinct original contributions; wrappers/helpers are counted once per
original address. No other module is marked reviewed by this checkpoint.

| Maintained contribution | Original entry | Complete bytes |
| --- | --- | ---: |
| LockRegistry::enable / disable | 0x0041CCC0 / 0x0041CA30 | 21 / 21 |
| DebugMemoryResource constructor / destructor | 0x00418DB0 / 0x00418E90 | 31 / 29 |
| DebugMemoryResource::do_is_equal | 0x0041C9F0 | 15 |
| TaskInfo::~TaskInfo | 0x0041FDF0 | 20 |
| TaskInfo virtual enable / disable | 0x00421680 / 0x00421760 | 20 / 20 |
| TaskInfo enable / disable helpers | 0x004216A0 / 0x00421780 | 53 / 53 |
| Worker constructor | 0x0040B780 | 44 |

Cold canonical replay passes every byte and relocation of these eleven units,
327 new compared bytes, of which 247 receive authored credit. Existing units remain exact. The complete replay is
31/31 units across eight freshly built objects; comparison includes all 1,777
bytes, with 1,478 authored bytes. Partial PMR/Worker declarations do not close
allocation or thread lifetimes, and no whole-program linkage is claimed.

Custom RTTI establishes the PMR/TaskInfo class identity, but does not identify
whether their empty/defaulted constructor/destructor contributions were
authored or synthesized by the compiler. Those three full exact functions stay
under origin review and receive no authored credit; their units remain replayable.

Independent constructor disassembly establishes 22 recursive mutexes of 48
bytes, followed by 22 depth bytes and the enable byte at +0x436. Portable tests
check that toggling changes only that byte and restores the object state;
Linux mutex storage is not used as proof of the x86 representation.

Raw file-backed RTTI and vtables independently establish debug_memory_resource
at 0x0056C920 with four PMR slots, and TaskInf at 0x0056D4C0 with three slots.
The PMR equality override always returns true; installed standard new/delete
resources use identity equality, corroborating a custom implementation. Natural
defaulted custom construction/destruction call the original shared std base
helpers and install the observed custom vtable. Matching these function bodies
does not establish complete matching vtable/RTTI data or deleting destructors.

TaskInfo restores virtual forwarding plus separate two-node helpers rather
than merging both into each virtual body. Portable tests cover null, one and
two nodes, masking only the disabled flag, preserving callback/data state and
never invoking callbacks. Worker construction follows independently checked
jthread and atomic<bool> constructor chains: twelve-byte thread state at +0,
false at +12, preserved tail padding. Installed MSVC headers corroborate those
library identities before canonical anchors are accepted.

Each deferred case records its own evidence and follow-up. Specific differences
include reference array.at bounds checks versus unchecked native indexing;
lazy lock singleton versus fixed native global storage; native allocator
receiver/deleting flags versus free factories; raw allocation's two native
arguments and new-handler failure path; merged va_list logging versus two
complete cdecl variadic entries; and a conversion-failure exception absent
from the original finish-log body. The reference worker synchronization helper
is not the complete graphics member at 0x004D9E30: that native body logs a
diagnostic and closes its Worker subobject at +0xD90.

Program-entry bridges and injected renderer lambdas are recorded as reference
integration support, not duplicate native implementations. The isolated CPU
oracle resolves selected imports/heap state and redirects the mapped original
PMR default global to a source resource. It checks limited constructor, lock,
string, allocation and source-created-thread cases. It omits allocation
failure/new-handler, original variadic formatting, MessageBox and original game
entry. Its report is not inherited as our runtime acceptance. Source-only
tests and every explicit fixture lambda are reviewed separately.

Manual reconciliation of cpu_compare.cpp's sole parse gap identifies WINAPI
on line 10 as the annotation error. Full reading accounts for all five explicit
bodies and the separately indexed included worker fixtures. The hash/count
binding is checked publicly; no completeness claim follows for the other 103
files with parser gaps.

Private independent evidence: .analysis/ref003-runtime{,-extra}.asm,
ref003-{resource,task}-vtable.json, ref003-worker-{construct,library}-anchors.asm,
ref003-pmr-base-anchors.asm and reference-functions/exact-replay-007.log.

## REF-004: archive's 64 explicit definitions reviewed

All eight nongenerated archive source/header files were read, including both
test drivers and the extraction verifier. Every indexed definition receives
an individual decision: eighteen native cases deferred with specific ABI or
behavior differences, and forty-six source API, integration, fixture or report
helpers. No archive file has an outstanding parser gap. Total explicit reviews
are 190; 6,518 indexed bodies and 103 parser-gap files remain pending elsewhere.

Independent full target disassembly covers the crypt primitive, filename sum,
LZSS, header/catalog parsing, aligned name advancement, lookup, member reads,
manager close/open/size and full file-selection wrapper. It establishes:

- 0x00456270 only sums a caller-counted byte sequence modulo 256 and returns
  a byte. The parameter-table lookup happens inside 0x0053A3C0, after strlen
  and this sum. Eight twelve-byte records at 0x005AE000 independently match
  the reference's key/step/block/limit values. An aggregate-return parameter
  selector is a reference API, not the native sum contribution.
- 0x004100E0 is a six-argument cdecl in-place crypt routine. It uses signed
  32-bit lengths and an allocator-owned copy of min(size, limit), whereas the
  reference uses vectors, signed 64-bit arithmetic and additional rejection
  conditions. Odd-byte/short-quarter-block tail and permutation/key behavior
  are corroborated, without accepting the new ownership or failure contract.
- Native 0x005391F0 accepts input/length/optional-output/allocation-size, can
  allocate through the original owner and returns a pointer. Dictionary
  0x005C6B38 persists and each stream cursor starts at one. Its bit reader
  fetches before the exhaustion check; the reference checks before indexing.
  Reference expansion/final-size exceptions and vector return are additional
  policies. Literal, thirteen-bit ring address and length-plus-three behavior
  agree on valid streams; malformed-input equivalence is not claimed.
- Native ArcMngr is sixteen bytes: records +0, count +4, names +8 and stream
  +12. Parse uses stream virtual calls and allocates count+1 sixteen-byte
  records, with a final stored-end sentinel. Close logs and separately releases
  names, records and stream. Reference vector/unique_ptr/path/error storage
  and injected/embedded dictionary are different lifetime/receiver designs.
- Native lookup returns a record pointer or null and calls CRT comparison
  0x00555750. That helper has an ASCII fast path and a global-state-dependent
  alternate path. Reference explicit-length ASCII views and throwing index
  results cannot represent its complete native contract.
- The full file-selection entry 0x00410AA0 owns lock-2/EH, a size-output
  argument, raw buffers and explicit loose-file mode. Its two strrchr calls
  preserve the observed backslash/slash quirk; an absent archive member does
  not select filesystem fallback. A standalone view-return basename helper
  is not the whole original entry.

Maintained ArchiveCrypt recovers the counted filename sum with its original
two-argument cdecl ABI and one shared natural body. All 71 bytes replay exactly,
with no relocations. The reference selector row records this accepted subpart
while leaving its broader aggregate-return API nonexact. Tests cover explicit
lengths, embedded zeros, high bytes, wrap, zero length and the sum of all 256
byte values. This adds one authored function; cold replay is now 32/32 units,
nine objects, 1,848 compared bytes. Authored exactness: 25 functions, 1,549 bytes.

The source tests, dictionary-borrowing lambdas, manager tests and extraction
verifier are individually classified as support. Their checks compare valid
decoded resources to external extraction or exercise source-defined rejection
and lifecycle behavior; none executes the original game. Duplicate-index
comparison and first-match unique-member tests have different scopes and are
not summed. Old report totals are not imported as fresh acceptance.

All four selected unmodified archive production/verifier TUs compile in serial
diagnostic probes. The verifier recipe now supplies the source SHA string macros
from its actual CMake contract; missing build definitions are not algorithm
failures. Conservative receipt checks still retry after any source changes.
This compilation result is not linkage, native runtime or direct ABI acceptance.

Private evidence: .analysis/ref004-archive-target.asm, ref004-name-compare.asm,
ref004-crypt-table.json, reference-functions/exact-replay-008.log and serial
reference compiler receipts/logs. Original bytes and reference source stay private.

## Compiler diagnostics and remaining work

`compile-reference-probes.py` compiles unmodified reference translation units
serially through the locked wrapper. Its profile and all compiler/header/source
identities are recorded privately. These probes discover ABI/emission/build
issues; successful compilation is not semantic acceptance, and failed recipes
do not reject all functions in a file. Build dependencies and test-specific
macros are reconciled before interpreting compiler errors.

Initial scheduler/archive/runtime probes found the runtime CMake dependency on
the scheduler include directory and archive-verifier hash macros. The diagnostic
recipe now supplies the scheduler include. Cached probes verify the object,
receipt, all source fingerprints and included headers; stale entries and failed
compilations are retried rather than being accepted by source hash alone. The standalone verifier needs its
declared CMake definitions; that build issue carries no algorithm conclusion.

Next: review platform_services' 44 definitions and every
remaining implementation. Deferred scheduler/runtime/archive/input owner/ABI recovery
is recorded separately.
Continue through every indexed implementation; investigate and record hard
cases without stalling or marking untouched bodies as reviewed.

```bash
scripts/repo-python scripts/index-reference-functions.py --check
scripts/repo-python scripts/report-reference-functions.py
scripts/repo-python scripts/compile-reference-probes.py --resume
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python scripts/ci.py
```

Private evidence: `.analysis/ref002-*`, `.analysis/reference-functions/` and
object receipts under `build/`. No upstream implementation text, raw target
bytes or decompiler output is distributed.
