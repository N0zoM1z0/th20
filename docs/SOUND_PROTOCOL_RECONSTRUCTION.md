# SoundInf owner and whole command dispatcher

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

## CORE-113 — Complete private WaveReader I/O and buffer filling

The file reader and buffer-filling chain now have shared private C++ bodies,
using actual owned WaveReader/CSound/StreamingSound objects, SDK records, typed
arrays and recursive guards. Five complete contributions replay 999 bytes
without differences; all 23 relocations are checked. No source, canonical,
authored, mapping or reference admission follows from these private results.

| Complete private contribution | Native address | Compared bytes | Full result |
| --- | --- | --- | --- |
| WaveReader::~WaveReader | 00459920 | 67 | Zero differences; 62 code + 5 native CC, COFF ownership open |
| WaveReader::close_file | 00459A30 | 64 | Zero differences |
| WaveReader::open_file | 0045AB40 | 327 | Zero differences |
| WaveReader::read | 0045AFF0 | 347 | Zero differences |
| CSound::restore | 0045B780 | 194 | Zero differences |
| WaveReader::reset | 0045B5F0 | Object388 / native396 | 369 full differences, including8 absent native bytes |
| CSound::fill | 0045A240 | Object539 / native540 | 351 full differences, including1 absent native byte |

Original memory/file and lost/available-buffer paths are mutually exclusive
if/else branches. These natural scopes, also corroborated by the pinned SDK
recovery source, explain the earlier shorter read/recovery contributions.
Reset still lacks the native unconsumed seek-result stores and stack local;
fill still lacks the native NOP after its ignored initial reset call. An explicit
void cast correctly states the discarded HRESULT but does not close that
emission disagreement. No inert locals, empty statements, narrowed comparison
or false void prototype are added. All native bytes and earlier failed whole
comparisons remain preserved.

File opening stores mode and clears memory mode before validation. Mode one
requires a filename, converts through CP932 using a 261-WCHAR array and capacity
260, then opens a shared-read sequential file. Conversion and initial reset
results are ignored. Failed opening leaves the invalid handle and previous
metadata/name; other modes return success without opening. Closing in mode one
always logs and attempts CloseHandle, including null/invalid handles, ignores
failure and writes INVALID_HANDLE_VALUE. Repeated closing still attempts the API.
The complete destructor calls this same close body without invented rollback.

Memory reads check the current pointer, optionally report a byte count and
clamp to the logical view. File reads gate only on null handles, require output
and count pointers, then subtract the capped request from the chunk-size word
before ReadFile. They ignore BOOL and report the supplied actual count, returning
S_OK even for a defined failed-read observation. A short read therefore consumes
requested remaining length, not actual length. File reset checks both null and
invalid handles, while memory reset ignores position. Signed-positive metadata
checks coexist with unsigned position/wrap arithmetic; file positions beyond the
end subtract the loop span once, rather than applying modulo repeatedly.

Fill restores and locks the buffer, discards initial reset status, reads data,
and selects either silence or repeated data. Eight-bit PCM silence is128; other
bit depths use zero. Successful completion discards Unlock status. Failed
restore/lock/reset/read paths retain the original early exit and any acquired
lock; no RAII cleanup is inserted. Recovery calls Restore twice per iteration,
sleeps only for BUFFERLOST from the first call, and repeats whenever the second
call is nonzero, including unrelated failures. Zero-progress repeat can also
remain in its loop. Both behaviors are preserved.

Same-body O2/ASan/UBSan checks pass 48 independent data/seek cases and36 owned
fill cases, plus failed conversion/open/seek/read/status/lock/unlock/reset,
repeated close, invalid versus null handles, signed metadata, silence, ordering
and virtual resource retirement. Two explicit fixture exceptions stop bounded
observations of zero-progress reads and nonzero recovery statuses; they are test
observation boundaries, not native API exception guarantees or production guards.
Original pointer wrap/overlap/unwritten failure count, COM driver, allocator/EH,
startup, concurrency and full link/runtime remain unaccepted. Real memory
arithmetic stays within actual128-byte arrays even when logical views are shorter.

Legacy unused SDK prefix types, original packing and uncalled virtual signatures
remain unproven. New consumers establish the chunk-size word's remaining-length
role, but not all other MMCKINFO/MMIOINFO members. The tentative file-base input
at005C0004 has two reset reads and no recovered producer. It resides in BSS;
scalar/aggregate ownership and startup remain open. Its reset relocation is a
consumer-derived diagnostic hypothesis, never an accepted canonical anchor.
Other API anchors are independently verified against the locked PE import table.

Preserve active core113-WaveIo-v2 and core113-SoundFill-v2 pairs, whole comparison
receipts, both completed semantic reports, frozen private sources, bounded native
exports/attestations, import/global-binding audits and original v1 input archives.
Retirement removes four replaced products; current261 source hashes and147
canonical pairs remain protected. All761 exact results equal CORE111 after cleanup,
without repeating an unchanged-source cold build. Production remains761 units /
147 objects /144535 disjoint bytes; authored87 /27766 bytes and reference238.
CORE112 matching-head remote CI succeeded at15b3449, run37971167572.

Continue major whole-function work after recording these unclosed source/type
boundaries. Item update and the complete SoundInf dispatcher remain the main
frontier; do not park on isolated small helper admissions or manufacture missing
stores/NOPs to raise exact counts.

All70 public tests pass in262.679 seconds; the full gate passes in
264.582 seconds. Temporary semantic executables and CI bytecode caches
retire automatically. Cleanup removes four replaced files /163920 bytes;
all761 results and261 source /294 canonical /12 private hashes remain unchanged
after CI. Build9.2MiB /analysis121MiB. Preserve core113-public-ci.log, its
completion receipt, cleanup receipt and pre-deletion retirement plan.

## CORE-112 — Whole private memory-stream factory and lifetime protocol

The complete 735-byte memory-stream factory now replays without differences
under the pinned x86 compiler. Its 22 relocations use independently identified
callee, process-global, SDK IID and diagnostic-string anchors. All five native
strings are checked through their terminators; IID_IDirectSoundNotify is checked
against the actual SDK GUID. The initial candidate's single flag-byte mismatch
was a real policy error: the native factory selects LOCSOFTWARE, not
CTRLFREQUENCY. The corrected body retains flags OR 0x18188.

| Complete private contribution | Native address | Compared bytes |
| --- | --- | --- |
| SoundDeviceOwner::create_memory_stream | 00459D70 | 735 |
| WaveReader::WaveReader | 004596D0 | 214 |
| WaveReader::open_memory | 0045AC90 | 92 |
| CSound::CSound | 00459530 | 255 |
| StreamingSound::StreamingSound | 00459630 | 150 |
| CSound::~CSound | 004597B0 | 237 |
| StreamingSound::~StreamingSound | 00459900 | 29 |
| CSound scalar deleting destructor | 00459970 | 49 |
| StreamingSound scalar deleting destructor | 004599B0 | 49 |

These nine private contributions compare 1,810 bytes. The base destructor has
232 code bytes and five emitted CC bytes which also match the native image;
original COFF alignment ownership remains unresolved. No compared extent is
shortened. Its previous 237-versus-232 report remains preserved. The initial
base constructor had eleven differences from using two separate loop-index
variables; the original shared mutable index is independently corroborated by
native reuse and the pinned SDK source. No unused shaping local is added.
Two complete allocation-release dependencies replay another 217 bytes without
differences. Original deeper allocation/constructor/EH closure remains open.

The factory publishes memory fields through open_memory with flag zero, then
ignores its E_NOTIMPL result. Only flag one returns S_OK; publication precedes
the check. Notification offsets retain uint32 wrap, including zero count/stride
and overflowing stride arithmetic. Failed CreateSoundBuffer or QueryInterface,
a positive HRESULT with a null notification interface, and null/throwing array
allocation preserve the original early resource retention. After a notification
registration attempt, both success and negative HRESULT release the notification
interface and array. Stream allocation follows these releases; output publication
and descriptor/device/event/busy fields follow construction. No invented
rollback, null guard or RAII cleanup changes these paths.

The shared factory/WaveReader bodies pass O2/ASan/UBSan across 200 independently
modeled arithmetic, COM and allocation-boundary cases. A second same-body check
passes sixteen real owned stream construction/destruction cases, negative and
positive fill/position statuses, retained dirty representation bytes, virtual
retirement and throwing construction before ownership transfer. Helpers use
actual typed allocations and recursive guards. Portable COM mocks declare the
full SDK method order and retain host pointer widths; native ABI evidence comes
from the actual Windows SDK build, not a forged portable layout. Explicit fixture
specializations are declared before use so inline array templates do not bypass
failure observations. Failed preliminary harness runs remain preserved.

The legacy WaveReader prefix, unconsumed CSound fields, original four-byte
packing and uncalled virtual signatures remain private hypotheses. Native scalar
factories clear their full allocation before construction; constructor-only dirty
storage checks do not claim to reproduce those unresolved factory helpers.
Original WaveReader file retirement, fill implementation, COM driver, allocator
failure/EH behavior, startup, notification threading and full link/runtime remain
open. Therefore none of these private results adds maintained source, mapping,
authored, reference or canonical credit. The accepted graph remains 761 units /
147 objects / 144,535 disjoint bytes, with 261 source files.

Preserve core112-factory-replay-v3.json.gz, core112-wave-replay-v2.json.gz,
core112-lifecycle-replay-v2.json.gz, both semantic receipts, bounded attested
native exports and the three active object/receipt pairs. Original replaced
input closures and failed/earlier full comparisons remain lossless. Eight replaced
trial files were retired in two passes; current canonical pairs, source hashes
and all 761 replay results are protected. The first pass's byte sizes were not
persisted before a stale baseline path stopped verification; its recovery uses
the actual CORE111 baseline and claims no retired byte count. The final pass
persists a retirement inventory before deletion. No unchanged-source cold build
is repeated. CORE111 matching-head GitHub CI succeeded at bcb1cf6, run37964687061.

All 70 public tests pass in 212.344 seconds; the full gate passes in
213.895 seconds. Temporary CI bytecode caches and semantic executables retire
automatically. Current 261 source / 294 canonical-file hashes remain unchanged
after CI. Final retirement removes two replaced files / 89,486 bytes; build
remains 9.0 MiB and analysis 120 MiB. Preserve core112-public-ci.log, its
completion receipt and both protected cleanup receipts.

## CORE/EXACT-111 — Complete preload and loading protocol

The complete 1,146-byte preload and 835-byte loading functions are maintained
in `src/SoundLoading.cpp`, together with their actual 119-byte buffer release,
26-byte default destructor and 26-byte Graphics option getter. Five complete
roots add 2,152 disjoint canonical bytes and 77 independently reviewed
relocations. The frozen 261-source-file graph passes all 761 strict units in
147 fresh objects over 144,535 disjoint bytes. The two main functions have
independent application-origin evidence from the original whole command
dispatcher and TH20 core/sound.cpp diagnostic provenance; authored exactness
is 87 functions / 27,766 bytes, confirmed authored 90. Three support origins
remain pending. No constructor, poll or stream implementation is admitted here.

| Complete contribution | Native address | Bytes |
| --- | --- | --- |
| SoundInf::preload | 00427360 | 1146 |
| SoundInf::load_track | 00426890 | 835 |
| SoundInf::free_preload | 00428EE0 | 119 |
| SoundInf::~SoundInf | 00426030 | 26 |
| Graphics::uses_preloaded_music | 00428FA0 | 26 |

The actual SoundInf storage uses SDK pointers/handles, real fixed record arrays
and the native PMR vector. TrackFormat is 52 bytes with an actual 18-byte
WAVEFORMATEX and implicit tail alignment. PreloadedTrack has four observed
fields, totaling sixteen bytes on x86. SoundDeviceOwner contains the actual
DirectSound pointer at offset zero; its constructor, destructor and factory
body remain genuine undefined interfaces. StreamingSound stays forward-declared;
the unproven private CSound/StreamingSound/WaveReader prefixes are not imported.
Original SoundInf construction, lookup, reopening and notification callback
also remain undefined production interfaces.

Preload holds the real recursive lock at slot 2, grows/value-initializes its
PMR vector, then checks the receiver's cached allocation/name. A cache hit
returns before publication. Otherwise it writes the process-global track name,
which is distinct from the receiver's name array, before option/device gating.
Replacement frees only allocation; format/current/size remain retained even
if the new file or allocation fails. Successful reading publishes the original
format pointer, allocation/current pointer and requested preload size. It does
not use the number of bytes actually read to shorten the record or initialize
unfilled malloc storage.

The path is a real 261-element WCHAR array, cleared by its actual size; the
conversion call requests MAX_PATH=260 using CP932. Conversion, file seek,
ReadFile BOOL/count and secure-CRT statuses are ignored exactly as observed.
File open failure returns -1; allocation failure closes the opened file and
returns -1. Preserve the original diagnostic path and misspelled `Streming`
messages. The Japanese factory-error payload remains original CP932 data,
represented as string escapes, not machine-code bytes.

Loading checks the actual device owner, configuration byte and DirectSound
pointer before any OS creation. With preload disabled it delegates to genuine
reopening using the receiver's name. With preload enabled it requires an
allocation, publishes current_track and calculates notification size with
uint32 multiplication/wrap, a right shift by four and block-alignment rounding.
Nonzero nBlockAlign is an original precondition; no new division guard is added.
The event precedes the thread, which precedes the memory-stream factory. The
callback parameter is the process Graphics window. Event/thread failure does
not prevent the factory call; negative HRESULT returns -1 without invented
handle rollback and without updating the selected preload index.

The factory's actual x86 interface passes GUID by value, with 48 explicit stack
bytes, rather than a reference. Ordinary SDK GUID_NULL naturally emits the
native copies and stack alignment. Flags are CTRLPOSITIONNOTIFY |
GETCURRENTPOSITION2 (0x10100), notification count 16. The volume flag is not added
at this caller. Positive HRESULT, including S_FALSE, follows the success path.

Complete preload EH handler42, FuncInfo36, one-state unwind map8 and guard
cleanup16 replay privately without differences. Native handler/ABI metadata
independently identify cleanup destinations; no compared relocation field is
solved. The cleanup compares all five emitted native CC alignment bytes, whose
original COFF ownership is separate. Three whole vector wrappers replay103B;
deeper resize/allocation/EH/library closure remains unaccepted support.

The maintained body executes under O2/ASan/UBSan with actual SoundInf/Graphics
owned storage, member constructors, PMR containers, locks and malloc/free
allocator. The independent arithmetic model uses wide multiplication plus
explicit uint32 truncation across 140 rate/alignment/factory/event/thread cases.
Additional checks cover global-versus-receiver names, value initialization,
short/error reads, ignored conversion/seek failure, cached no-op, replacement
failure, retained fields and a real PMR bad_alloc with cross-thread lock release.
Public O2/UBSan uses the same production body. Fixtures supply only unresolved
startup and API/factory/lookup/reopen observations; they never execute the
notification thread or dereference an invented stream/COM object. A malloc
sentinel observes untouched read tails and is explicitly fixture instrumentation.

The supported caller domain is indices 0..15, terminated valid names fitting
their 256-byte arrays, valid track-format/storage records, representable
allocation sizes and nonzero block alignment. Original Unicode/CRT constraint
handling, resource-owning retirement, SDK/COM factory behavior, stream/WaveReader
ownership, thread races, full link and game runtime remain separate requirements.
The earlier complete private poll remains2920/native2948 with1222 differences;
the private129-byte reopen match still depends on unaccepted base ownership.
Continue coherent factory/stream and whole dispatcher work, recording unresolved
source-context differences without inert stores or padding.

Preserve core111 production/root/EH/semantic/origin reports, the frozen source
map, exact111 canonical results, bounded native exports and attestation logs.
The pre-admission archive preserves original 756-unit/145-object and five active
probe input/receipt closures. Retired products remain reproducible from these
SHA-bound inputs; their historical receipts are not relabeled fresh after
source-graph changes. Current 147 canonical pairs remain protected.

All70 public tests pass in273.260s, including the new whole loading resource
protocol. Temporary semantic executables and CI bytecode caches retire
automatically. Current261 source/294 canonical-file hashes remain unchanged
after CI. Build8.8MiB/analysis119MiB; current canonical evidence stays protected.

## CORE-109: historical private owner investigation

CORE-109 investigated the actual sound owner used directly by Item update.
Production at that checkpoint remained CORE107: 756 canonical units, 145 objects and 142,383
disjoint compared bytes. Private compiler results do not add source, reference,
origin or canonical credit.

## CORE-110: complete private dispatcher candidate

The complete main dispatcher now has a private C++ body with all nine commands,
both playback paths, stage waits, queue retirement, lock scopes and final effect
processing. A fresh pinned build emits 2,920 bytes, including its entire
nine-slot jump table. Comparison includes every emitted byte and every byte of
the 2,948-byte native code/alignment/table interval: 1,222 differences, including
28 native bytes beyond the emitted extent. The object table starts at offset
2,884; the native table starts at 2,912. This is a whole nonexact candidate,
with no source, mapping, authored, reference or canonical admission.

All eighteen emitted logging literals are checked through their terminators
against thirteen distinct native payloads. Internal relocations retain the
object's own case offsets. They are not redirected to different native case
heads to disguise the table disagreement. Two complete genuine allocator
supports replay privately without differences: `release_object<StreamingSound>`
97 bytes and `std::destroy_at<StreamingSound>` 27 bytes. Destruction calls the
actual virtual destructor before deletion under process lock slot 1. Native
shared code does not imply an AnimationCallback receiver at this call site.

Fresh attested constructor, factory, destruction and caller evidence separates
the polymorphic CSound base from its StreamingSound derivative. The private
base compiles to 0x88 bytes with four-byte member alignment; the derivative
compiles to 0xA8, with its ordinary integer busy field at 0xA4. Native allocation
clears the complete derived storage before construction. The constructor has
four explicit arguments and no appended SoundInf parent pointer. Its two
observed virtual slots are destruction and reset. Original packing directives,
some retained member types, virtual declarations and resource lifetime remain
inferred or open; these private layouts are not maintained type acceptance.

Microsoft's pinned SDK sample supplies independent corroboration for the
legacy wave records: HMMIO, two MMCKINFO values and MMIOINFO precede the memory
reading fields. Its original format pointer and resource buffer differ from
the private modified-wave hypothesis. See the
[official SDK wave declaration](https://raw.githubusercontent.com/microsoft/DirectX-SDK-Samples/07e3eaa10e7dd026ec9d95fe326db2d5c4227e1b/C%2B%2B/DXUT/Optional/SDKwavefile.h).
This corroboration does not establish TH20's unused prefix types. Native
WaveReader is allocated as 0xA0; its constructor clears only twenty bytes at
each of 0x04, 0x18 and 0x30. A proposed 72-byte MMIOINFO at 0x30 therefore retains
52 bytes. No blanket constructor zeroing or opaque padding is introduced.

The native nonpreloaded start path uses the command's own name when its track
index is negative, and the indexed track name otherwise. Command 9 also uses
the command name. The current-track filename is not substituted. Preloaded
stage 2 tests reset failure, whereas streamed stage 3 ignores reset status and
tests fill failure. Reopen is a void forwarding interface; recreate's native
HRESULT is ignored. Fade targets the process-global SoundInf wrapper. Busy
pause/resume leaves the command queued, and pause alone logs the busy wait.

Native thread retirement contains both a conditional and an unconditional
stream-pointer clear. Native also writes an unused zero before the request
range loop. The candidate does not manufacture these extra stores; their
original source context remains unresolved. Numerical overflow, CRT constraint
handling, constructor failure/EH maps, complete stream/wave/device bodies and
runtime admission remain open. Continue the main protocol, without admitting
only its matching destruction helpers.

Preserve `core110-poll-replay.json.gz`, its complete private source and active
v2 object/receipt, both fresh native exports and attestation logs, and original
v1 SHA-bound input/receipt archive. Failed diagnostics remain evidence; completed
proof writers are not rerun. Retire only the replaced v1 build pair after
checking the archive and active replacement, then protect all current canonical
pairs and replay the existing 756 units. The remote CORE109 CI succeeded at
4353a94; its private receipt is `core109-remote-ci.json`.

The protected cleanup removes two replaced files totaling 88,200 bytes. All
756 existing canonical results remain identical to CORE107; 256 source and
290 canonical object/receipt hashes remain unchanged. Native evidence and
active inputs are protected. Build storage is 8.3 MiB and analysis storage
114 MiB; installed tools, supplied game files and the database are preserved.
All 69 public tests pass in 243.532 seconds, with temporary caches automatically
retired. The maintained reconstruction graph remains unchanged.

## Whole dispatcher evidence

Fresh attested Ghidra range export and locked-PE decoding agree on all 787
instruction heads in the 2,909-byte body at `004277F0`, through RET at
`0042834C`. There are nine distinct command targets, 76 direct call sites and
32 distinct direct dependencies. Preserve the three-byte alignment NOP and
the complete nine-pointer table at `00428350`: the code/alignment/table
interval is 2,948 bytes through `00428373`. Original COFF ownership remains
untested. No dispatcher body is accepted or compared as a shortened prefix.

| Command | Native case head |
| --- | --- |
| 1 | 004278EE |
| 2 | 00427991 |
| 3 | 00427F38 |
| 4 | 00427DA7 |
| 5 | 00427FB0 |
| 6 | 00427FE2 |
| 7 | 0042804E |
| 8 | 004278C6 |
| 9 | 004280AA |

The first lock scope checks the real device owner and returns integer zero
when absent. Independent maintained/native constructor and destructor bindings
identify `std::lock_guard<std::recursive_mutex>`, using LockRegistry slot 11.
Command handling and the final effect-request dispatch have separate scopes.
The original shift copies whole 268-byte command records; the command pointer
advances during shifting and is retained on the preload repeat edge. Do not
silently reset it to the first record. Sleep occurs after releasing the
command lock. Preserve stage waits, failure paths and original stream calls
when implementing the complete body.

## Actual storage and call protocol

Native CRT startup at `004011C0` first clears 0x57E8 bytes, constructs the
owner at `00425D70` and registers destruction. The private declaration has
actual SDK pointers/handles, twelve 520-byte requests, a 16-byte x86 PMR vector,
ninety 24-byte channels, seventy-two source buffers/counts and thirty-two
268-byte commands. It has no appended Environment or Context pointer.

| Member | Native offset |
| --- | --- |
| Device owner | 000C |
| Requests | 001C |
| Preloaded-track vector | 187C |
| Track-format allocation | 1890 |
| Effect channels | 1994 |
| Source buffers / duplicate counts | 2204 / 2324 |
| Commands | 2544 |
| Sixteen track names | 46C4 |
| Music filename | 56C4 |
| Stream pointer / notification handle | 57C4 / 57CC |
| Music / effect level | 57DC / 57E0 |

The private 52-byte TrackFormat uses an actual 18-byte SDK WAVEFORMATEX and
implicit trailing alignment. PreloadedTrack has four independently observed
fields totaling sixteen bytes. Resource ownership, complete stream/wave/device
declarations and teardown remain open; forward pointers do not establish them.

Request processing first reads signed 16-bit cooldown by table index. It scans
twelve requests until the negative-ID sentinel, merges an existing request
only for counts 0..59 and drops a new request when all twelve slots are used.
The first new ID write uses the genuine checked `array::at`; pan/count writes
use unchecked indexing. Separate callee evidence distinguishes these methods.
Channel binding searches the unsorted definition table for a matching ID;
native has no fabricated unknown-ID exception or ninety-entry search bound.
The supported ID domain requires an existing definition and indices 0..89.

Command insertion uses only slots 0..30; slot 31 is the sentinel. Native
`strcpy_s` ignores its status and retains CRT constraint handling. Logging also
occurs when the queue is full. Ready returns a complete integer 0/1, rather
than a bool ABI. The preload flag belongs to actual Graphics.configuration,
read at Graphics+024C; it is not a SoundInf method or source-only service.

## Private compiler observations and admission boundaries

One natural body is compiled serially with pinned x86 MSVC and explicit
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc /std:c++20`.
Seven complete roots replay without differences over 868 bytes: ordinary
destruction 26, binding 79, cooldown assignment 22, effect request 320,
position request 52, integer readiness 41 and command insertion 328.
Original source spelling, const qualifiers and authored classification remain
inferred. No production admission follows from this private result.

The constructor emits 578 bytes: its complete 573-byte native code plus five
compiler-generated CC bytes. All 578 bytes are compared and equal after
explicit relocation replay. Native has nineteen CC bytes before the next
record constructor; original COFF ownership of the five included bytes remains
open. The interval is preserved without inserting padding in C++ or slicing
the emitted contribution.

Seven whole array access/assignment supports, the complete 29-byte constructor
EH handler and 13-byte enqueue unwind funclet also replay. Complete float
payloads, logging text including its terminator and the 36-byte constructor
EH record are independently checked. Three array constructors remain whole
nonexact: emitted 36/36/33 versus native 78/78/75 bytes, including native EH
frames. PMR internals and the enqueue EH unwind map remain unclosed. Matching
callers do not establish full link, constructor failure handling or retirement.

The position request emits original MULSS/DIVSS/CVTTSS2SI. Its current private
C++ cast has a defined portable domain only for representable finite results;
NaN/out-of-range native behavior and the SSE exception environment require a
genuine shared semantic contract before admission. No fake fallback is added.

Next work is the full dispatcher with genuine separate base/stream ownership,
WaveReader prefix, native virtual signatures, stage/resource/error protocol,
host semantics and the frozen affected production replay. Do not admit only
the helpers while this coherent main-function closure is open.

## Evidence and retention

Preserve private `core109-sound-*-native.asm` exports and attestation logs,
`core109-sound-poll-dispatch.json`, `core109-private-replay-v4.json.gz`,
the actual private source and active v4 object/receipt. The v3 report records
the still-nonexact earlier binding attempt, including its failed expectation;
the completed writer is not rerun or overwritten.

Replaced v1/v2/v3 pairs are retired after original receipt/input verification
against three lossless SHA-bound archives and installed SDK files. Cleanup
protects all current canonical pairs, 256 production sources, active v4 and
native/private evidence, then replays the 756 existing canonical units. No
unchanged-source cold rebuild or deletion of tools, references, supplied game
files or the database is needed. The removal inventory remains private in
`core109-cleanup.json.gz`.
