# SoundInf owner and whole command dispatcher

CORE-109 investigates the actual sound owner used directly by Item update.
Production remains CORE107: 756 canonical units, 145 objects and 142,383
disjoint compared bytes. Private compiler results do not add source, reference,
origin or canonical credit.

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
