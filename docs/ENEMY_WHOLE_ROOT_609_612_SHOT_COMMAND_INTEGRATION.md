# CORE187: four Enemy shot-command opcodes in the entire dispatcher host

The user-selected locked TH20 Japanese v1.00a Steamless target is still SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint extends **one continuing 41,967-byte native Enemy dispatcher
reconstruction**, `EnemyState::execute_opcode` at `0x0048C010`.
No subfragment is represented as an independent native function or as
canonical machine-code exactness.

## Independent native evidence: a large, shared case

The locked opcode dispatch table maps **609, 610, 611 and 612 to the same
primary head** `0x004931DD`. Capstone decodes **1,457 bytes / 314 instructions**
through the unconditional final jump at `0x00493789`; the block ends before
`0x0049378E` and has 29 original direct call sites. A separate native case-path
catalog independently agrees on the entire local instruction-head set, normal
successors and branch boundaries, with no unresolved indirect jump or outside
successor. The branch SHA-256 is
`f129e860c6aaf09aa107aca146fc85abc1eb021721d052c6e2f7c2430dabb98b`.
The complete original calls, original target digest and instruction checks are
under `.analysis/core187-native-609-612-audit.json`.

The common code first evaluates `integer_argument(0)` and calls the **full
396-byte native queued-metadata selector `0x00498B80`**, which works with
`EnemyState+0x168` forward-list ownership and an eight-byte **pair of raw
record/metadata pointers**, not a `shared_ptr` return. That ABI was
independently verified in subsequent CORE188; see
[the corrected pair and COW contract](ENEMY_QUEUED_SELECTOR_PAIR_COW_RECONSTRUCTION.md).
That selector is a separately **unaccepted** game function: the original
CORE187 private host
captures only its interface and preserves real `ShotMetadata` owners and
subsequent real C++ storage. It does not fabricate a complete production
selector or claim its 396 bytes.

Actual independently declared storage and native field accesses agree:
`ShotMetadata` (`EtamaArgInf`) has a `std::pmr::vector<BulletCommand>` at `+0x4`
and a cursor at `+0x30`; each command has a **44-byte stride**. Native
`0x00486600` counts the 44-byte elements, `0x004862F0` forwards vector growth
and `0x0047C6C0` indexes one command at `base + index*44`. Its stores are
observed at command offsets `+0x24`, `+0x20`, `+0x10`, `+0x14`, conditionally
`+0x18`, `+0x1C`, and finally float offsets `+0`, `+4`, conditionally `+8`,
`+0xC`. Those offsets match the maintained shared `BulletCommand` layout.

The native opcode comparisons divide the family along two independent axes:

| Native opcodes | Command index | Additional fields |
| --- | --- | --- |
| 609 | `integer_argument(1)` | First 4 integers, then 2 floats |
| 610 | `integer_argument(1)` | First 6 integers, then 4 floats |
| 611 | Current metadata cursor | First 4 integers, then 2 floats |
| 612 | Current metadata cursor | First 6 integers, then 4 floats |

Operand reads preserve original order and start at index 2 for 609/610,
but at index 1 for 611/612. Both routes grow the real vector only when its
unsigned length is smaller than `command_index + 1`. The original comparisons
are unsigned; overflow and unbounded malicious script indices have not been
validated or given fabricated safety checks.

After all successful command writes, the cursor stores either `index+1`
(for 609/610) or `previous_cursor+1` (for 611/612). Earlier stores and vector
growth survive exceptions while the cursor is not advanced. All four paths
share the same native exit; no separate roots are claimed.

## Integration and independent scenario checks

Active private whole-root candidate:
`.analysis/core187-enemy-dispatch-candidate.cpp`.
Existing cases from CORE185, including 539 and 555, remain in the same
single `exercise_dispatch_candidate` function. New bounded fixture inputs:
`.analysis/core187-dispatch-host.cpp`,
`.analysis/core187-shot-command-host-cases.inc` and
`.analysis/core187-dispatch-host-recipe.json`. The candidate invokes real
`EtamaArgInf`/`BulletCommand` constructors, genuine PMR vector storage and
resize. Its only new captured nonproduction boundary is the native
queued-record selector. All original native branch evidence is kept separate
from the host's independently formulated expectations.

The new matrix passes **888/888** cases with real `ShotMetadata` and real
44-byte command elements: 864 genuine fixture selection callbacks,
216 actual vector-growth situations, 432 cursor-mode situations,
432 extended-field situations, 22 expected selection/operand exceptions and
12 preserved-partial-write checks. It validates all command fields bitwise,
including distinct signed-zero, infinity and NaN payload representations;
complete selected state images; call order; existing surrounding array entries;
and cursor commit timing. It does not claim behavior for out-of-bounds indices,
invalid metadata pointers or concurrent owner mutation.

Both entire-host runs passed all **39,861/39,861** scenarios (the preexisting
38,973 plus the 888 new cases):

- GCC 13 `-O2 -Wall -Wextra -Werror` with UBSan:
  `.analysis/core187-dispatch-host.log`.
- GCC 13 `-O2 -Wall -Wextra -Werror` with ASan and UBSan:
  `.analysis/core187-dispatch-host-asan.log`.
  **Only `-fsanitize=vptr` was disabled** because the private host intentionally
  does not link the still-unimplemented `WeaponStoneInfo` key-function RTTI.
  Address, alignment, arithmetic and other sanitizer checks remain enabled;
  this is not a pass for vptr checking.

The private SHA-bound attestation is
`.analysis/core187-enemy-whole-root-proof.json`; it protects four active
source/recipe inputs, both binaries `build/core187-dispatch-host*` and both
successful host logs. Prior CORE185 and CORE183 candidate/proof artifacts remain
unaltered and protected. The authored whole-root draft currently covers
**128 effective opcode values / 96 distinct original primary heads** out of
174 native primary heads; this is semantic coverage, not a completed machine
code or native acceptance percentage.

## Compiler and acceptance scope

CORE187 changed no maintained production source, shared header, compiler
profile, canonical unit manifest or reconstruction acceptance ledger.
Consequently **canonical cold build / strict native replay affected scope is
zero units** for this checkpoint. CORE185's five affected native production
objects and 33/33 strict units were already verified and are unchanged.
Only the separate 81-translation-unit whole-root GCC fixture was rebuilt
at reduced priority (one UBSan build and one ASan+UBSan build). No whole-graph
cold replay or native game image build was attempted. The underlying full
41,967-byte Enemy root, EH, jump tables and compiler partition remain
machine-code **nonexact**.

High-value continuation: reconstruct the native **396-byte queued selector
`0x00498B80`** from its actual forward-list/shared-owner topology and byte
ordering; independently reconcile the 33-byte command accessor `0x0047C6C0`
and the resizing dependencies before attempting compiler-exact closure.
Other large missing root families (including lasers 702/703 and VM command
resources) remain available; do not replace whole families with short stubs.
