# SoundInf owner and whole command dispatcher

CORE-109 investigates the actual sound owner used directly by Item update.
Production remains CORE107: 756 canonical units, 145 objects and 142,383
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
