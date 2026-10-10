# Complete ECL runtime dispatcher

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

EXACT-057 reconstructs the complete EclRuntime::tick at `0053B5C0`: 11,110
instruction bytes, two native alignment bytes and the entire 392-byte jump
table. Canonical replay compares all 11,504 bytes with zero differences after
independently binding all 401 COFF relocations. No prefix or case fragment is
credited. The coherent shared random-angle dependency at `004297D0` contributes
another complete 45-byte unit; its original utility authorship remains open.

The full accepted graph is 397 units / 74 cold objects / 74,056 disjoint
comparison bytes. Authored credit is 64 functions / 16,948 instruction bytes.
The table/alignment and unresolved random utility are outside authored totals.
All units were cold rebuilt after shared owner declarations changed.

## Whole behavior and owner

EclRuntimeTick.cpp uses the shared EclRuntime72, Manager112, Loader564,
ScriptStack24 and ScriptInterpolation56 owners established by EXACT-056.
The production body contains time/rank gating, frame return and invocation,
async controls, relative jumps, integer and float stack expressions, scalar and
vector math, interpolation configuration and the interpolation update tail.
The actual generic stack and resolver protocols remain declared dependencies.
The six manager virtual slots retain their observed concrete native layout.
Production initialization, flags wrapper, allocation/lifetime and full-game
link/runtime behavior are separate pending work.

Already-ended positions return minus one. Rank-mismatched instructions advance
without stack dropping. Executed ordinary instructions drop the shared byte
count before advancing by instruction length. Tagged stack expressions have
their own operand consumption and bypass that instruction-level drop; arithmetic
clears the actual instruction's drop field. Relative jumps update both script
time and the byte-addressed instruction position. Successful calls restart time
checking; failure ends the caller through the accepted invocation protocol.

Default opcode dispatch preserves all three delegated status branches: zero
uses the shared drop path, minus one goes directly to interpolation, and one
rechecks time without advancing. Other statuses use the ordinary case exit.
The interpolation tail reads the original instruction at its saved subroutine
and offset, resolves destination argument 1 with its saved frame base, and uses
the maintained scalar interpolation sample. End invalidates offset/subroutine.

Float comparisons and division retain native operation order and edge behavior.
Opcode 96 retains both observed greater-than tests against the two half-pi
bounds; it is not simplified to a guessed sign predicate. Input domains for
integer overflow, invalid stack offsets and invalid division are not broadened
by replacement guards. Portable tests use valid integer domains and explicitly
exercise unordered float comparisons.

## Parameter order and lifetime breakthrough

Opcode 81 constructs the actual Vector3, reads and normalizes direction argument
2, reads length argument 3, then invokes polar and stores the two destination
lanes. Nested C++ call arguments reversed the reads under the locked compiler.
Saving only direction fixed order but shortened the complete body by 16 bytes.
Aggregate and structured-binding records preserved size but changed many slots.

Two separately named const float values retain both meaningful samples and
their lifetimes throughout the case. That natural source reproduces both native
temporary stores, frame reservation `5A0`, full local placement and the complete
switch/exit shapes. An extra inner scope around these two values changes the
body to 11,111 bytes and relocates later instructions; it was rejected. Lifetime
evidence, rather than exact size alone, distinguishes the accepted version.

The final maintained owner migration still matched all 9,900 non-relocation
bytes. Full independent relocation replay then established every remaining
byte, including the table. These are distinct evidence stages; the earlier
structural diagnostics in CORE-055/EXACT-056 were not exact claims.

## Relocation and table evidence

The complete native interval has 2,525 decoded instructions, 288 direct calls,
52 distinct direct dependencies and one delegated virtual call. The 401 COFF
relocations contain 288 REL32 and 113 DIR32 records. Ninety-nine DIR32 entries
refer to real local labels: the table pointer and all 98 table entries.
Their destinations come from the compiled contribution's actual COFF symbol
values plus the native root address, not from solving target fields. Every
replayed table entry matches the independent native audit, covering 76 distinct
case heads. Native alignment is the two-byte `66 90` NOP.

Existing accepted math, interpolation, stack and CRT canonical anchors are
reused. New resolver/manager/frame/loader addresses are identified from complete
attested definitions and layout producers/consumers. The PMR interpolation
vector's begin/end, size, index, resize and pop_back helpers are independently
recognized from their allocator/three-pointer storage and 56-byte element
stride. Their compiled library bodies receive no extra matching credit.

| New role family | Independent native entries |
| --- | --- |
| Integer read / consuming read / destination | `0053ED50` / `0053EEE0` / `0053E850` |
| Float read / consuming read / destination | `0053E970` / `0053EB70` / `0053E720` |
| Saved-frame float destination / loader instruction | `0053E7C0` / `0053E8E0` |
| Enter frame / frame base getter | `005405B0` / `0041CA90` |
| Spawn / find / terminate async runtime | `0053E390` / `0053E920` / `0053E560` |
| Intrusive node value | `0040C300` |
| Vector unchecked begin / end | `00414F30` / `00414F70` |
| Vector size / element / resize / pop_back | `0053F780` / `0053B560` / `0053F390` / `0053F1B0` |
| Script interpolation tangent start / end / reset | `00439460` / `00438B00` / `004395B0` |
| Random radians | `004297D0` |

The shared GameRandom object at `005BA4A8` is independently established by
startup `00401120`, which passes stream ID 0 to the real constructor `00422C50`,
and other game consumers. Source declares this owner without inventing its
production startup. The radians helper calls the accepted signed_unit and
multiplies by the native float pi. Constant negative one at `0056E0F4` is
corroborated by argument resolvers and a separate Vector3 consumer at `004DA45B`;
all constant bytes are checked independently. Other equal words in .rdata are
not assumed interchangeable.

## Validation and practical limits

The pinned MSVC 19.44.35211 x86 tick recipe is C++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:strict /Gd /sdl. The random-angle translation unit uses the same
base without /sdl. These are per-unit observations, not global game flags.
Shared owner changes trigger a complete cold replay of all 397 accepted units.

tests/ecl_tick_semantics.cpp executes the whole maintained dispatcher on its
actual owners with real math and interpolation implementations. Independent
expected values cover rank/time/ended state, ordered signed arithmetic, tagged
stack consumption, unordered float comparisons, logical/bit operations,
post-decrement, ordered polar/direction reads, conditional jumps, delegated
statuses, async state changes, and interpolation's saved frame/instruction tail.
The invocation has separate EXACT-056 owned tests. Constructors, argument
resolvers, four-byte stack copies, async routing and script lookup are explicitly
test-only fixtures; their native production bodies are still unaccepted.

Host checks use C++20, optimization, warnings and UBSan, with
-fno-strict-aliasing for the native MSVC raw-word stack contract. The native
unsigned vector-size comparison is retained and its host sign warning is
explicitly disabled. Host checks do not establish game playability, complete
library linkage, invalid-domain behavior or cross-platform float bit identity.
All 30 public tests and target/tracking/progress/full Ghidra checks pass.

```bash
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python scripts/compare-coff-function.py --unit ecl_runtime_tick
scripts/repo-python scripts/ci.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/ghidra.py check
```

Next core is the complete EnemyState opcode dispatcher at `0048C010` / 41,967
bytes. Immediate runtime/lifetime dependencies remain open alongside it.
Unrelated leaves stay deferred. Raw exports, rejected probes and compiler
artifacts remain ignored; the reconstruction goal remains active.
