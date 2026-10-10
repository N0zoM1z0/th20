# Enemy spawn and time-scale orchestration

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

EXACT-079, 2026-10-08. Three complete contributions on the locked Japanese
Steamless target add 1257 body /1399 comparison bytes. They use the actual
1064-byte Enemy, 752-byte EnemyState and 704-byte Session owners.

| Unit | Native address | Body bytes | Complete comparison bytes | Source |
| --- | --- | ---: | ---: | --- |
| Enemy::apply_spawn | `0x004A89C0` | 780 | 922 | `src/EnemySpawnApplication.cpp` |
| Enemy::tick | `0x004A8760` | 448 | 448 | `src/EnemyTick.cpp` |
| Animation::set_slowdown | `0x0045D130` | 29 | 29 | `src/AnimationParameters.cpp` |

The two Enemy translation units use the locked MSVC x86 candidate with
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
AnimationParameters retains its existing manifest profile. Complete function
COMDAT extents, all canonical relocations, eight jump-table slots and the
110-byte compressed selector map are compared. Native destinations come from
attested Ghidra exports and previously established native members. Compiler-local
branch labels use their actual offsets in the same complete function section.
No target field under comparison supplies a relocation destination.

The frozen graph contains 594 units in 110 comparison objects and 103873 disjoint
comparison bytes. Fresh locked-compiler receipts and strict replay cover the
entire graph after shared-header changes. Origins remain 521 pending, 9 library
and 64 authored functions /16948 bytes. These additions do not establish authored
identity. Two complete reference associations close, bringing absorbed reviews
to 196 across all 6945 terminal reviews.

## Spawn protocol

The complete spawn body copies all 84 parameter bytes, retains one actual PMR
movement record, assigns its real position and copies both identifiers, health,
initial health, phase and base pattern kind. The existing flags word remains
available alongside actual one-bit fields at bits 3 and 10; bitfield assignment
naturally preserves unrelated bits and narrows the original values.

The actual Session mode supplies the rank. Modes 0 through 3 use a narrowed
`1u << mode`, while modes 4 and above use rank 2. Negative modes lie outside the
defined C++ shift domain and are not claimed as accepted inputs. Timer at +288
receives integer assignment 2, updating its current/fractional value through the
existing real Timer protocol. It does not receive a mode assignment. The complete
48-byte counter copy, health >=1000 sticky flag, shared Session stage clamp and
its mutation are retained.

The call to Enemy::tick happens before the later pattern and identifier reads.
Its signed return is deliberately ignored here. Potential tick mutations therefore
remain observable in pattern adjustment and field +250. A retained nonzero +254
bypasses selector initialization. Otherwise the complete compressed table covers
all 110 selectors with native results 37, 33, 45, 41, 51, 50 and 49 and sets +258.
The table occupies 32 bytes at `0x004A8CCC`, followed by 110 selector bytes at
`0x004A8CEC`; the accepted comparison ends at `0x004A8D59` inclusive. Self-aliasing
input uses the ordinary saved-spawn assignment.

## Time-scale protocol

For slowdown <=0, sticky flag bit 16 decides whether the ordered animation walk
runs. Every resolved live animation receives positive zero; the existing handle
resolver owns stale/null behavior. State::tick supplies the full signed return.
The flag remains sticky and the inactive path does not resolve handles.

For positive or unordered slowdown, the function saves the real global clock,
computes `clock - clock * slowdown`, clamps values above 1 or below 0 and retains
IEEE unordered behavior. It updates the clock, resolves actual PMR animation
links in order, writes each live Animation slowdown, delegates State::tick,
restores the original clock value, sets sticky bit 16 and returns the delegated
signed result. No inferred exception/RAII restoration guarantee is added.
Animation::set_slowdown writes the actual float at +560.

Complete typed health/pattern setters and PMR iterator support also pass strict
native comparisons. Folded addresses are support evidence and receive no duplicate
unit credit. No reference free-function/raw-buffer/Services interface is imported.

## Semantic verification and boundaries

The owned O2/UBSan test uses production Enemy/ECL/EnemyState/Animation/Session
lifetimes, real PMR records and both complete production orchestration bodies.
It exercises 108 slowdown/clock/flag combinations including infinities, NaNs,
signed zero and clamps; ordered live/null/stale handles; clock restoration;
full signed return; flag retention and animation mutation boundaries.
Another 3300 spawn cases cover six nonnegative modes, five health boundaries
and every selector, with shared stage-clamp effects, post-tick mutations,
Timer value, identifier, counter and rank assertions. Self-aliased spawn and
retained selector fields have dedicated checks.

Whole EnemyState::tick is an explicit observational fixture in these tests.
Renderer resolution, Enemy retirement and virtual readers/destinations are also
bounded fixtures; unused routes abort. This establishes orchestration behavior,
not full State tick, renderer, runtime or whole-game acceptance.

## Whole EnemyState tick experiment

A private natural candidate covers the complete native `0x004A8260` body
(1260 bytes; 1280-byte comparison extent), all five facing modes, parent offsets,
separate regular/viewport handle behavior and four Timer transitions. Precise
floating-point compilation differs in constant lowering. Strict floating-point
compilation reproduces the complete extent but retains a missing NOP after the
Pattern tick call, shifting subsequent Timer code; early-exit displacements also
differ. Splitting genuine support into a separate translation unit did not close
this difference. The candidate remains nonexact and receives no partial credit.
Do not insert inert NOP shaping, shorten the extent or change a return ABI without
independent native evidence.

Native exports, candidate source/header versions, profiles, receipts and strict
diagnostics remain private under `.analysis/core079-*`. The 41 KB Enemy opcode
root, both whole variable readers, full State tick and runtime remain open.

## Final verification and storage

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

