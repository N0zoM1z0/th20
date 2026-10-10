# REF-026: Title batch review

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

All 803 indexed Title implementations were individually read and have body-hash
bound decisions: 66 nonexact and 737 support. This includes 333 candidate-role
entries, 455 oracle bodies and 15 tools; role hints are not acceptance decisions.
The standalone Replay format probe is fixture support despite its candidate hint.
All production files, owner/interface headers, lambdas, fixture include fragments,
data extractors, Python drivers, PowerShell commands and CMake recipes were read.
The reference checkout remains unchanged and ignored.

Global coverage is 2,646 terminal / 4,298 pending of 6,944. Sixteen Title parser-gap
files were manually reconciled against their original bytes: calling-convention
decorators inside indexed hooks, fixture-only `fldcw` inside `prepare_case`, and
the fully enumerated PowerShell runner. There are 45 reconciled / 68 pending gap
files globally. No complete compiler-AST or exhaustive game reconstruction claim.

## Complete exact components

| Component | Native head | Complete bytes | Independent ownership evidence |
| --- | --- | --- | --- |
| TitleFlags construction | 0x0051D9B0 | 66 | Title constructor 0x0051DB00 passes +0x58D4; main/frame and Replay reader consumers |
| PracticeScore availability | 0x0052CA30 | 55 | Stage update call 0x005296A7; draw calls 0x00529C5F and 0x00529D0F pass actual sixteen-byte rows |

TitleFlags is a real four-byte value with four individual bits: delayed music,
initial menu, Replay read cancellation and completion. Natural bit-field
initialization clears the four low bits through successive DWORD masks and
preserves the upper 28. Native music/main/Replay producers and consumers were
read independently before registering the canonical unit. The whole Title
constructor remains nonexact; reference primitive arrays and byte masking do
not recover its actual subobjects, EH or vtable.

PracticeScore is the existing sixteen-byte disk value, with native signed-byte
reads at +9 then +8. Its natural const member returns whether either is nonzero.
The constructor still matches after changing those two fields to signed bytes.
The reference `stage_available` instead takes a whole raw Profile, validates
selectors, computes the row address and reads +8 before +9. That helper remains
nonexact; the separate member receives the exact credit. Original field meanings,
class spelling and authored/compiler/shared origins remain pending.

Cold replay passes 113/113 complete functions across 30 objects, 7,699 bytes.
Both new functions have no relocations. Authored progress remains 57 functions /
4,074 bytes; 52 source-present origins are pending, with four library units.
Portable tests check dirty Title flag storage, retained upper bits, Replay bit
updates and all 65,536 signed-byte pairs without changing the practice record.

## Compiler and native boundaries

The actual module recipe owns 50 production translation units. A further
standalone Replay format diagnostic belongs to the Sprite pool test: 51 candidate
files compile serially with the reviewed include paths and strict-FP profile.
Its required `TH20_NATIVE_CORE_SHA256="unused"` macro comes from that test's CMake
target; it is not a successful native-fixture execution attestation.

Sixty-five complete reference COFF contributions differ from their independently
exported native spans. No prefix, table truncation or solved relocation anchor
was promoted. The 66th nonexact decision is the inline whole-Profile availability
helper, whose owner/ABI/partition differences are established separately.
The two `read_shortcut_keyboard` overloads have separate outcomes: only the span
overload was compared with 0x0051F310; its no-argument forwarding wrapper has no
independent original head.

Native exports cover 107 heads. All 28 internal analysis holes across thirteen
heads were independently decoded from the approved executable: each is an
unconditional jump within the complete control-flow span. Full spans were kept.
This does not settle all tables, shared tails or ownership of large rejected
pages. Target and mapped Ghidra bytes remain unchanged.

Native handle-array constructors for 8/32/139 elements occupy 75/75/78 bytes and
call the known AnimationHandle constructor through the native array iterator.
Natural standard arrays emit 33/33/36 with either reviewed EH profile. Original
EH4/cookie/template ownership remains open; no fake destructor, padding or
assembly was introduced. Shade 0x0051E100 is a full 105-byte member with unused
ECX and RET12; the reference free clamp helper changes the ABI.

## Owner and page observations

Title is a 0x5978 callback owner with five Cursors, three Timers, a Worker at
+0x5968, 100 Replay pointers at +0x5740, flags at +0x58D4 and a mesh at +0x5924.
Initialization registers update/draw priorities 11/89, owns ANM slots 11/12 and
waits for loading/animation completion. Destruction joins the worker, removes
callbacks, retires metadata/animations, releases mesh, rebuilds input and then
destroys actual subobjects. Environment injection, flattened handles, raw owners,
thread factories, allocator and exception partitions prevent whole-owner credit.

The batch follows main-menu notices and ten destinations, character/difficulty
and resume flows, loadout/effect freezes, stage/practice selection and launch,
music loading/parser/track cleanup, data and keyboard unlocks, rank name editing,
Replay enumeration/cancellation/playback/save, trophies, backgrounds and page
draws. Each enclosing page and each extracted lambda has its own decision.
Native callbacks return full int results; selection fixtures using `cpu<void>`
discard those results and cannot establish return-width equality.

Data and Stones use distinct 776-byte keyboard unlock states. Data's idle test
is signed, Stones' is unsigned; production keyboard modes are 0/1, while synthetic
mode2 in fixtures is not real OS input. The independent data audit verifies 238
checks, including complete 113-difficulty and 455-group tables, resume/last-stage
values, keyboard sequences, float bits, label/pointer tables, eighteen adjacent
character labels and nine stone labels. These are data observations, not code
exactness or complete record/file behavior.

## Retained oracle limits

| Retained evidence | Historical result | Current binding audit |
| --- | --- | --- |
| Main Title CPU | 2,540,032 checks / 0 failures | All 296 build-bound input hashes current |
| Shared menu draw | 122,880 / 0 | All 389 source bindings and enclosing Sprite report digest current; overlapping report totals |
| Music parser | 12,578 / 0; 4,096 cases | All 23 source bindings current; supplied archive digest verified |
| Separate heap-tail parser | 295 / 1; only 2 / 4,096 cases | 22 current / one stale source binding |
| Name input draw | 196,608 / 0; 24,576 scenarios | 271 current / two stale: compare.cpp and Worker header |
| Stage fixture history | 720 failures | 360 current / eleven stale inputs; window-scale fixture issue |
| Replay format faults | Sixteen logs: fourteen returns / two AVs | All log SHA256 digests verified; five source hashes recorded after execution, not build-bound |
| Save slot format faults | Twelve logs | Inline retained text matches logs; no source/build or log-hash binding |

No native Windows oracle or report writer was executed in this batch; retained
binaries are absent. Current hashes alone do not attest a fresh execution.
The shared drawing report overlaps its containing Sprite totals. CPU queues,
cached TextJobs and normalized job/heap pointers do not compare fresh GDI text,
GPU output, real input/audio, whole-game scheduling or lifetime/failure paths.

Replay format 0x005751C4 contains an extra `%s` consuming a double's low word as
a pointer and reads past the supplied arguments. The source only emulates its
zero-word valid subset and throws otherwise. Save format 0x005753A8 similarly
consumes mismatched x86 words; explicitly constructing a double changes the
callee graph. Character*9+stone indexing crosses contiguous native label tables,
where reference bounds guards may reject access. These differences are recorded,
without claiming universal fault or varargs equivalence.

The music worker has an unused stack argument and RET4, plus native resource,
string/parser/EH behavior. Splitting it into a void bounded reader and host parser
changes ABI and allocation-tail behavior; native unbounded NUL reads are limited
by the isolated Win32 heap in its retained fixture. Asynchronous loading,
malformed documents, disk errors and allocator/CRT lifetimes remain open.

See the individual ledger for body-specific calls, state, native addresses,
diagnostic sizes and unresolved work. Continue related batches through every
remaining implementation and parser gap; the exhaustive goal remains active.
