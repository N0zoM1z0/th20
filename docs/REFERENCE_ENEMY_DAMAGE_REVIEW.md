# Enemy damage, drops, defeat, cleanup and mesh review

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

## REF-039 — 2026-10-07

All **141** implementations in this coherent batch were individually read,
including nested lambdas, adapters and historical fixture endpoints. The 21
indexed files cover `enemy_cleanup`, `enemy_damage`, `enemy_damage_helpers`,
`enemy_defeat`, `enemy_drop` and `enemy_mesh`, their headers, adapters and CPU or
source cases. Relevant zero-definition value headers were also read. Original
CRLF body hashes and the pinned reference commit remain intact.

New decisions are **5 absorbed / 17 nonexact / 119 support**. Two previously
reviewed health/pattern reset bodies are independently revisited and upgraded
from nonexact to absorbed, without counting them as new reviews. The nine
`__fastcall` annotation errors on lines 5–13 of `enemy_defeat_cpu_cases.inc`
and the one on line 6 of `enemy_drop_phase_cpu_cases.inc` are manually
reconciled. All ten complete endpoint bodies were already indexed; no omitted
implementation or reference source change is involved.

Global coverage is **5,688 terminal / 1,256 pending** of 6,944 implementations;
parser-gap files are **86 complete / 27 pending**. Gameplay has **412 pending**.
Every implementation retains its own hash and decision in the review ledger.
The exhaustive review goal remains active.

## Independently rewritten native values

| Maintained member | Original address | Complete bytes |
| --- | --- | ---: |
| `EnemyHealth::EnemyHealth` | `0x004A3360` | 83 |
| `EnemyHealth::reset` | `0x004A7310` | 65 |
| `EnemyHealth::apply` | `0x004A3F80` | 123 |
| `EnemyHealth::record` | `0x004AA050` | 28 |
| `EnemyHealth::positive` | `0x004AB240` | 40 |
| `EnemyHealth::forced_end` | `0x004AB290` | 22 |
| `EnemyPattern::EnemyPattern` | `0x004A34A0` | 136 |
| `EnemyPattern::reset` | `0x004A7360` | 108 |
| `EnemyPattern::clear_counts` | `0x00497270` | 72 |

These nine complete natural C++ contributions add **677 disjoint bytes**.
All **175 canonical units / 50 cold objects / 12,236 complete bytes** replay
with zero differences against the locked Steamless target after the final
maintained source freeze. Source presence is 175, pending origins 114, library
4; confirmed authored 57 of 4,074 bytes remains unchanged. Original names and
authored/compiler/library identity are not established by these matches.

The native EnemyState constructor directly constructs the real 28-byte health
value at `+18C` and the 168-byte pattern value at `+1A8`. Health has six integer
words and a four-byte flags value. Reset clears health, field04, phase health
and accumulated damage, clears flag bit1, and preserves scale, threshold and
the other flags. The role of field04 and original declarations remain unknown.
Unsigned maintained storage preserves modulo32 accounting; required queries
and division interpret signed values. Scaled damage computes signed division
by seven after the wrapping subtraction/multiplication, then wraps the threshold
addition. Record changes only the accumulated damage word.

`positive` returns full integer 0/1, and `forced_end` returns the full unsigned
bit1 value. The original damage caller tests **EAX**, not just AL. Reference
boolean declarations and the retained `original<bool>` positive query are
insufficient to establish that ABI. The full 123-byte damage body contains a
second jump at `4A3FDD` omitted from Ghidra's listing. Direct PE decoding retains
it; an ordinary `if/else` with branch returns naturally reproduces the complete
flow. No target prefix, artificial local, assembly or fake branch is used.

Pattern has three header words, two real 16-element count arrays, duration at
`8C`, Timer at `90`, and radii at `A0/A4`. Native drop emission uses fifteen item
kinds, while clear/reset preserve the independently observed sixteen-slot array
width. Construction zero-initializes the arrays and constructs Timer; reset
explicitly clears the entire trivially copyable value, then assigns both radii
32 and Timer zero. Count clearing preserves the second array, header and radii,
and uses the real array fill and Timer assignment protocols.

Original calls and independently decoded callees establish the memset, array
fill, Timer construction/assignment and 32.0 literal anchors before probing.
All nine ranges fully decode with closed branches and complete final returns.
Other newly emitted array helpers receive no additional exact credit. These
values supply no fabricated whole Enemy, Player, HUD or ANM owner.

Portable C++20/UBSan tests construct dirty guarded values, check adjacent storage,
and independently model 10,000 cases with widened arithmetic and complete byte
checks. They cover signed health edges, all relevant flags, wrapping damage,
reset preservation, sixteen count slots and both initialized/uninitialized Timer
assignment paths. Pattern constructor and reset deliberately have different
Timer/radius states.

## Complete reference diagnostics and unresolved owners

Ten actual reference production translation units were rebuilt after the final
maintained source freeze. Their full defined COFF inventories contain **219
functions / 73 static functions**. **26 complete comparisons across 22 mapped
bodies** all differ in length; no structural match is accepted. Comparisons
include the four native cleanup heads represented by one enum-driven reference
function and the two stage accessors represented by one merged free helper.
All older unrelated reference receipts require rebuilding before reuse.

The full damage source preserves phase ordering, pending damage, bonus/reduction
order, credit before division, health protection, script selection, forced end,
collision/graze, flash/cooldown and bomb switching. Explicit Services, raw owner
transport, checked arrays, indexed clocks and callbacks do not restore the
original member, allocator, vtable and lifetime protocols. Active damage queries,
replacement allocation, sound, defeat and player collision remain dependencies.
Life/time phases similarly depend on genuine PMR records, global reward owners,
HUD and the required active timeout notification. Their complete bodies remain
nonexact even though the accepted health value is now available.

Cleanup merges four original heads and still lacks actual ANM retirement,
observer and callback ownership. Drop consumes its initial random angle even
without positive counts, emits fifteen kinds, applies signed extra-count decay,
and finally clears sixteen slots; real Item allocation and virtual service
partition remain unclosed. Recursive defeat retains child/parent unlinking,
combo/reward/random ordering, death-script revival and the optional callback,
but its enclosing owner, effect and ECL lifetime protocols remain unresolved.

Mesh deformation uses the previous radius for geometry while updating the
stored radius, signed radial color weights, three-coordinate normalization,
phase increments, bounds, UV and strip updates. A zero radius can produce NaN;
negative weights clear alpha. Virtual renderer/window/ANM ownership and the
actual math/member partition prevent full-body acceptance.

## Retained oracle evidence and its limits

The historical CPU report records **1,254,134 cases / zero mismatches**, and the
frame report **7,682 assertions**. Both bind 105 of 105 current source hashes.
The selected damage/drop/phase/mesh/defeat groups sum to 194,864 recorded
comparisons, with overlapping checks; they are scoped prepared-object evidence.
The executed binary, compiler and startup environment are not independently
bound. No Windows oracle or report writer was executed during this review.

- The 6,000 full damage scenarios deliberately avoid active query, preview,
  replacement, sound and defeat calls. The timeout fixture permits only the
  original inactive early return. The 64 source scenarios record those additional
  boundaries and call order; they do not execute the original active bodies.
- The 8,192 drop scenarios patch the mapped Item endpoint `4C3C90`, record its
  eleven argument words and return null. Pattern/RNG bytes and call parameters
  are checked; actual item allocation is outside their domain.
- Phase configuration checks 136-byte records and real PMR allocation events.
  The underlying state-opcode implementations remain separately pending.
- The 1,024 mesh scenarios share original `49D850` initialization and `49DDC0`
  strip updates. They compare owner, vertex, position and strip bytes over finite
  and zero-radius inputs without independently validating the full renderer.
- The 4,096 recursive defeat scenarios patch nine named sound, ANM, effect,
  drop, reward and script endpoints. Fake tick controls revival through script
  parity; the callback records a change without freeing the retired object.
  Endpoint patch fixtures restore five mapped bytes/cache but do not restore
  page protection. They were only read, not run; original files/database stay
  untouched.

The historical resource report has 3,304 assertions and only **100/105** current
hashes. Enemy/frame implementation, CPU driver, resource test and frame test are
stale relative to that report. Reading them does not refresh its historical
result. GPU work is recorded, and full simulation/rendered gameplay is excluded.
Full enclosing owners, all remaining entity opcodes and whole-game equivalence
remain open. Continue the remaining coherent batches with individual decisions.
