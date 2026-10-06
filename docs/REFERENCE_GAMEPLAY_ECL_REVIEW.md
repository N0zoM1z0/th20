# Gameplay and ECL implementation review

## REF-036 — complete ECL batch

All 128 remaining ECL implementations now have individual body-hash-bound
outcomes: one absorbed, 26 nonexact and 101 support. Together with REF-035,
all 144 ECL implementations are reviewed: six absorbed, 31 nonexact and 107
support. All seven indexed source files and the five additional module recipe,
README and report files were fully read. Two parser-gap files are reconciled;
their empty-vector default argument initializers produce missing type_identifier
sites, while the complete instruction builders are already indexed.

Global coverage is 5,081 terminal / 1,863 pending of 6,944 implementations;
81 parser-gap files are reconciled and 32 remain pending. Gameplay's 1,019
implementations remain pending, as do Sprite540, StageBackground121 and183
other support implementations. No inventory or module-wide decision substitutes
for individual source reading.

RandomStream::signed_unit is absorbed through the existing, independently
written 129-byte game_random_signed_unit member. The reference adapter's
four injected references and intrinsic helper calls remain a different ABI;
the natural GameRandom member already preserves sample/(modulus/2-1)-1 and
replays exactly. Its native next/lock/startup implementation remains an explicit
dependency. This absorption introduces no new source or canonical unit.

All 156 complete canonical units replay from 44 fresh frozen-source objects.
Their disjoint target ranges contain **10,559 bytes**: a fresh sum corrects the
earlier prose total of10,558; no contribution, extent or source changed.
Source156, pending origins95/library4 and confirmed authored57/4,074 are
unchanged. Historical display/Overlay reference receipts still predate the
ScalarMath source freeze and require rebuilding before reuse.

Both unmodified ECL production TUs compile serially under the locked candidate
MSVC, C++20 containing-game recipe, strict FP/SSE2, actual native/binary include
paths and permissive-. The standalone ECL recipe declares C++17. These are
diagnostic choices and reference recipe facts, not original global flag proof.
VM COFF inventories contain532 defined function symbols,66 static; math contains
26/six static. Generated STL/EH/deleting/helper contributions receive no indexed
source or exact credit. Twenty-four complete VM contribution comparisons all
have length differences; representative results are:

| Contribution | Reference bytes | Native candidate bytes |
| --- | ---: | ---: |
| Stack::absolute / local | 117 / 31 | 102 / 120 |
| Stack::push / pop / peek | 113 / 114 / 119 | 265 / 242 / 192 |
| Stack::enter_frame / leave_frame | 130 / 56 | 170 / 52 |
| Runtime::current / call_into | 315 / 1,014 | 80 / 923 |
| Runtime::tick | 8,428 | 11,110 |
| Scheduler::spawn / tick | 376 / 148 | 182 / 217 |

A separate fresh x86 layout probe establishes reference Stack20 (SP12/BP16),
Subroutine44 and Runtime80 (time20/stack32/flags64/interpolators68), with56-byte
interpolation records. Native Stack24 has SP16/BP20; native Runtime72 has time0,
stack12, flags68 and interpolation vector52. The original resource table uses
eight-byte name/code records. Reference Engine virtual method order also differs
from native manager slots: its execute method follows the variable methods,
whereas native execute occupies slot4. Replacing these owners with padded or
renamed declarations would not establish their actual allocator/vtable ABI.

Native push/pop/peek take byte-length or output-pointer parameters and return
integer status; push/pop also support arbitrary-length memcpy paths. The
reference API handles four-byte values and returns void/value. Native push
sign-extends char tags; reference widens an unsigned char. Native enter_frame
uses wrapping32-bit arithmetic, logs failure and returns-1/0; reference uses an
int64 guard and bool. Original NULL destination/current results become checked
source exceptions. Program storage, synchronous/asynchronous call prototypes,
pool ownership and cleanup remain unresolved. Even the small leave-frame method
requires the genuine Stack/pop protocol rather than a synthetic receiver.

Twenty-eight focused original ranges completely PE-decode and corroborate
Ghidra instruction bytes, including102 instructions omitted by its selected
function bodies. All direct branches in these ranges stay within their
candidate ranges; rejected extents remain provisional. The actual signed16
opcode load, unsigned range check and98-entry table53E128 are independently
read. All75 supported case addresses match the retained table; other entries
lead to default53DEF5. Address53E00C lies inside53B5C0: the reference's separate
tick_interpolators helper has no standalone native function there. Native
entity dispatch48C010 remains a distinct owner and reconstruction scope.

The retained CPU report sums to41,067 with zero failures and binds all five
current vm/math/header/fixture hashes plus the locked EXE. It includes640 async
call setups and16,320 interpolation updates. The reviewed fixture compares
full int results, time bits, sub/IP, SP/BP,4096 stack bytes, mutable instruction
headers, full56-byte interpolation records and RNG state. The report does not
bind all transitive headers, compiler options or the executed oracle binary;
this review did not rerun Windows CPU comparisons. NoEngine rejects all variable
and entity requests. Raw preallocates storage and leaves the vector proxy zero,
avoiding native allocator/growth/loader/container ownership. RNG exercises an
already-owned recursive lock on one thread, not initialization or cross-thread
ordering. Invalid scripts/stacks, integer CPU faults and legacy CRT NaN/error
delivery remain outside the comparison domain.

A fresh C++20/UBSan run of the unmodified source tests passes async insertion,
delayed traversal, converted arguments, lookup, retirement/current restoration,
252-versus256 frame limits, shared borrowed script-header writes, duplicate
midpoint lookup and host-CRT NaN classification. These are source semantics;
native task allocation/traversal and old CRT NaN payload/errno remain untested.
The retained NaN probe records0xC0000005 without a traced failing instruction,
so its precise attribution remains unknown.

All21 resource JSON names and histogram entries independently reproduce23,760
instruction occurrences /15,872 core occurrences and every per-opcode count.
They do not establish fresh archive provenance, executable coverage or game
completion. export_opcode_evidence.py was fully reviewed as a source-directory
dependent writer; it was not executed and the reference checkout remains clean.

## REF-035 — scalar math component checkpoint

The related batch contains Gameplay1,019 / ECL144 implementations across114
indexed files. This checkpoint reviews all16 implementations in ECL math.cpp:
five absorbed, five nonexact and six support. The other1,147 implementations
remain pending in this family. Global4,953 terminal /1,991 pending of6,944;
parse-gap coverage remains79 complete /34 pending. Inventory/file hashing alone
does not establish source reading or a terminal decision.

Four natural independently written scalar wrappers add153 complete exact bytes:

| Wrapper | Native entry | Complete bytes | Original CRT dependency |
| --- | --- | ---: | --- |
| sine | 439820 | 35 | sin54FFB0 |
| cosine | 4397C0 | 35 | cos54FF50 |
| square_root | 446B30 | 35 | sqrt550050 |
| arctangent | 459280 | 48 | atan25500E0 |

Each cdecl wrapper widens float arguments to double, invokes the real double
CRT entry and narrows the x87 result to float. atan2 preserves the original
y,x order. Original function names and authored/compiler/library origins
remain pending. The canonical bodies contain no matching-only implementation,
assembly, raw instruction bytes, inert locals or synthetic receiver.

Full native ranges are independently PE-decoded and match Ghidra instructions,
ending at their actual RET. Native CALL operands were read before compilation;
canonical relocations do not use solved diagnostic fields. Original CRT
fallback FSIN/FCOS/FSQRT instructions and error-name strings sin/cos/sqrt,
plus atan2's descriptor at59A980, independently corroborate callee identity.
Original caller listings contain24/18/12/11 callers respectively. Rotation
458FA0 and vector-angle456210 show float stack arguments, cdecl cleanup and
x87 return consumption. CRT fallback extents, startup state and error handling
are dependencies, not reconstructed library contributions.

Complete canonical replay passes156/156 units across44 cold objects,10,558 bytes.
Source156, pending origins95/library4; confirmed authored57/4,074 remains
unchanged. All objects are rebuilt after final maintained source freeze.
Portable C++20/UBSan checks cover4,096 exact integer square roots,513 bounded
angles with Pythagorean/parity identities,128 scale-invariant four-quadrant
atan2 cases and signed-zero/known-angle results. These tests establish the
shared wrapper behavior against the host CRT, not equivalence of old/new CRT
NaN payloads, errno, exceptional inputs or complete game numerical environment.

The reference wrap_angle semantics are absorbed through the already accepted
187-byte normalize_angle: bounded34-step reduction, unordered comparisons and
infinite-input behavior remain in the existing production body. The reference
intrinsic arithmetic helpers change its emission but do not prevent semantic
absorption through the independent exact rewrite.

All other math implementations receive individual outcomes. Helpers a/s/m/d,
power and shifted_quadratic are factored source support with no independent
native standalone identity. angle_difference's natural direct C++ probe emits
163 versus native150 bytes and remains unaccepted. Reference polar takes two
float references, while native439330 takes one output-vector pointer followed
by angle/length. Reference rotate mutates separate x/y references; native458FA0
takes separate output/input vector pointers and angle, computing saved X before
writing Y then X. Original vector ownership, alias order and helper partition
remain open. No fabricated receiver or changed ABI is used to accept them.

easing groups polynomial, sine and shifted-quadratic modes. Sampling separately
handles Hermite basis-first arithmetic. Interpolator::sample uses a56-byte semantic
owner with an ECL suffix and explicit clock argument; actual native typed
interpolation ownership, Timer/member calls and original prototype remain
unclosed. Full original contribution comparisons retain their complete extents;
no prefix or shortened switch-table span is accepted.

The unmodified original math TU compiles with a fresh frozen-source receipt.
Ten complete COFF diagnostics give four structural matches and six length
differences: wrap241/187, difference301/150, polar91/89, rotate280/137,
easing1992/4154 and sample1402/649. The four wrappers are independently accepted
through canonical replay; diagnostic structural results alone confer no credit.
Rejected native switch/interpolation extents remain provisional.

The original math header/implementation and ECL CMake recipe are fully read.
The diagnostic uses C++20 from the containing game, strict FP/SSE2 and actual
native/binary includes; standalone ECL declares C++17. These are reference
recipe facts, not proof of the original game's global compiler flags. The
retained41,067 ECL CPU count has not yet undergone the full VM/fixture/report
binding audit and is not promoted here. No Windows oracle or writer ran.

Continue all remaining Gameplay/ECL owners, opcodes, adapters, fixture bodies,
reports and grammar gaps, then Sprite/StageBackground and remaining support.
