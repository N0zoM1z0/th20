# Gameplay and ECL implementation review

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
