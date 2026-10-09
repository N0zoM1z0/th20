# Complete Item update investigation

## CORE-114: complete activation, effect and retirement dependencies

Three whole private Item bodies now replay without differences: retirement
70 bytes at004C3880, effect344 at004C42C0 and activation400 at004C4420.
Activation includes381 code bytes, three alignment bytes and all four table
entries. Nine complete access/state contributions add290 bytes, including the
whole92-byte PlayerRecord selection contribution and its four-slot table.
Together twelve contributions compare1,104 bytes through55 independently
anchored relocations. These are private results, not canonical admission.

The actual storage candidates reuse complete maintained Item, Animation,
Context, PlayerRecord, Cursor, TaskInfo, Worker, EffectRequest and AnimationFile
values. Independent native constructors establish the0x13044 EffectInfo and
0x21104 StoneMenuInfo candidates, including their real arrays and containers.
The Stone factory independently allocates0x21104, constructs the value and
publishes it at005C6120 only after successful initialization. Its getter and
file+10 access are separate contributions; the latter shares an existing
physical getter head without implying that the receivers are the same type.
Effect initialization publishes through the Context setter, while the original
file lookup independently indexes pointer-sized entries at+10.

The native protocol preserves several details omitted by an injected service
environment:

- Activation stores state two before any random or ANM operation. Type thirteen
  consumes one random value modulo eight, then a second modulo four. Remainders
  zero through four select global PlayerRecord zero, independently of the Item's
  selected Context. Signed record division truncates toward zero before adding
  nine; other remainders select types nine through twelve directly.
- Record indices0/1/2/3 read fields0C/14/10/18. Case zero and default share the
  same actual source branch. The earlier private104-byte contribution kept two
  identical return branches and has37 complete differences against native92;
  the shared case/default scope explains the emission without inert shaping.
- Types nine through twelve bind scripts37 through40 using the current process
  Stone owner. Position copying follows binding, so a changed Item position is
  observed. Secondary Animation stop sets field28 to minus one and clears only
  the actual flag bit at49A.
- Effect types4/6/14/5/7 obtain file zero from the selected Context's actual
  EffectInfo, spawn script94 with stem `effect`, then reread type before choosing
  sound74 or48. Types one/two create the same effect and request the Item sound
  only when nonnegative. The returned effect handle is intentionally discarded;
  no attachment publication or extra validation is added.
- Retirement clears state before the original attachment retirement call,
  detaches the actual link with observer repair, then prepends it to its retained
  free-list owner. It does not destroy the Item or release its two Animations.

One consistent host graph runs these same whole bodies at C++20/O2 with ASan and
UBSan. It passes647 cases:576 independently computed random/record combinations,
ordinary activation, post-binding position changes, effect/sound ordering and
post-effect type changes, plus current/pending observer retirement. Actual Item,
Animation, record, Cursor, arrays, Worker, recursive guards and list lifetime
execute. Synthetic resource-free Effect/Stone/Sound startup and checked retirement,
captured original ANM/Sound/renderer-handle operations, and abort-only uncalled
Overlay lifetime remain explicit boundaries. Failed initial host builds retain
their logs; temporary host graphs/executables retire automatically.

The integer-zero effect/activation result candidates reproduce the complete
native EAX epilogues. Original declared return spelling is still inferred;
the public undefined void effect declaration is unchanged. Original Effect/Stone
loading, RTTI/uncalled virtual signatures, allocator/EH/startup/resource retirement,
full linkage and native game runtime remain unaccepted. No private owner/header,
canonical unit, authored origin, mapping or reference credit is imported.

Independent constructor-published three-slot table reads further separate storage
from virtual acceptance. EffectInfo uses the known TaskInfo enable/disable heads;
StoneMenuInfo's enable slot points instead to004E6230, a separate20-byte body.
The private synthetic Stone fixture inherits TaskInfo enable and is not a native
vtable match. Its original enable wrapper and both deleting/lifetime protocols
must be closed before coherent owner migration. Private nonvirtual byte identity
does not resolve that difference. Keep core114-owner-vtable-boundary.json.

Renderer investigation retains the full constructor tail and bounded real value
constructors: existing40-byte records, three24-byte lists,0x600 pooled Animation
slots, real matrix and20/28-byte vertex values. The four-byte interval after the
second Animation remains unexplained; the reference calls it padding. Its original
type/ownership and the renderer interface still need independent evidence.
No raw receiver prefix, copied Worker storage, arbitrary padding or injected
Environment is introduced to compile the complete update.

Preserve current lifecycle-v2/access-v3 pairs, whole comparison reports,647-case
semantic receipt,32 frozen private inputs and all attested native exports.
Original lifecycle-v1/access-v2 source/header/receipt/SDK closures are verified
and archived before replaced products are retired. The initial failed access
build exposed missing self-contained Context/Timer includes; the corrected
header changes no body or layout, and both active pairs have fresh receipts.
Current production remains CORE111:761 units/147 objects/144535 disjoint bytes,
261 source files, authored87/27766 bytes, confirmed90, mappings775/fourteen whole
nonexact, reference238/all6945 terminal reviews and header-only claims.
CORE113 matching-head remote CI succeeded atc519b20, run37975687004.
Continue complete Item update and draw with actual renderer ownership, then
coherent source/ABI migration of these dependencies; do not count private byte
identity as owner or original-runtime acceptance.

All70 public tests pass in255.800 seconds; the full gate passes in
257.509 seconds. Temporary semantic executables/graphs and CI bytecode
caches retire automatically. Protected cleanup removes four replaced products
/150358 bytes after persisting its pre-deletion path/size/hash inventory and
verifying original closures. All761 existing-object results equal CORE111, and
261 source/294 canonical/32 private hashes remain unchanged after CI. Build9.4MiB
/analysis122MiB. Preserve core114-public-ci.log/completion receipt, cleanup receipt
and retirement plan; no unchanged-source cold rebuild is repeated.

## CORE-108: native control flow and dependencies

The complete update at 004C25A0 contains 4,757 code bytes through its return
at 004C3834. Fresh bounded Ghidra exports re-attest the locked Steamless file
and database. Independent PE decoding covers all 1,125 instructions; Ghidra's
listing contains 1,122. Three otherwise omitted unconditional jumps at
004C26D5, 004C283F and 004C3585 remain part of the complete code interval.
Every direct branch lands on an instruction head inside that interval.
Decompiler syntax and reference types remain hypotheses.

The reward switch at 004C323E reads fifteen pointers at 004C3838, selecting
thirteen distinct heads. Types 2/15 and 9/13 share destinations; type 14 uses
the default reward tail. A three-byte native alignment NOP follows the return,
then the complete sixty-byte table. The code/alignment/table interval spans
4,820 bytes through 004C3873; twelve subsequent CC bytes precede Item retirement.
A prospective compiler comparison must reconcile this whole contribution,
including all three omitted jumps and the table. Its COFF boundary remains
untested; comparing only a 4,757-byte prefix would not establish exactness.

Full native activation at 004C4420 similarly contains 381 code bytes, an
alignment NOP and a four-pointer table at 004C45A0: 400 bytes together through
004C45AF. Its return, all table destinations and complete helper bodies are
independently decoded. No new source, canonical unit, mapping, authored or
reference absorption credit follows from these native audits.

## Corrections to the reference frame hypothesis

Branch instructions establish ordered comparisons in both moving states.
For quiet NaNs with masked SSE exceptions, the following outcomes hold:

| Decision | Native branch | Unordered outcome |
| --- | --- | --- |
| State 1/4 forced collection from Player threshold | threshold greater than Player y | Falls through to Bomb/boss checks |
| State 1/2 bottom retirement | Item y greater than 16+448+8 | Does not retire at this comparison |
| State 1/2 side retirement | absolute Item x below 384/2+8 skips retirement | Skips retirement |

The reference's negated less-or-equal threshold test instead forces collection
on an unordered comparison. Its state-one negated inside-bounds tests retire
unordered coordinates, while native state one and state two use the same
ordered cull branches. Historical REF-031 statements about differing unordered
native cull states are superseded by this instruction audit. Reference trace
and fixture results retain their historical scope; they do not establish these
original branches or the game's numerical exception environment.

Other native ordering matters independently of these corrections:

- State five decrements delay modulo 32 bits, activates when negative and skips
  the normal animation/Timer/processed tail. Delayed state one creates its
  effect when delay becomes nonpositive and also skips that tail.
- Forced attraction reads the actual Context Player repeatedly and checks
  BombController state one with age less than sixty, then the process boss
  predicate. The selected Item Context and global reward Context zero are
  separate receivers.
- State-one velocity uses the process ClockScalar and owner speed scale;
  state two omits that owner scale. Attraction acceleration may overshoot
  twelve, and owner speed recovery may overshoot one. No extra clamp is native.
- Pickup and nearby attraction square two separate radius getter results.
  A getter or Context lookup must not be cached across original calls without
  evidence. Successful pickup dispatches rewards before sound 37 and retirement.
- Animation activity returns a full integer from the actual bit at Animation
  +49A. Both original VM calls precede handle-position forwarding, postfix Timer
  increment and the modulo processed counter. Early paths skip those operations.

## Genuine owner boundary and next work

The root has 57 distinct direct dependency heads. Existing physical canonical
heads cover vectors, ClockScalar, Timer, observer iteration, geometry and several
Context/Session lookups. Shared byte identity does not by itself assign a new
receiver type or establish a complete gameplay protocol.

Renderer selection at 004776A0 writes the genuine renderer's +6C4 field. Handle
position forwarding at 004502C0 reads the current process renderer again and
calls its original handle operation. Item retirement clears state, retires the
actual handle, detaches its link and prepends to its retained free-list owner.
The original ANM update at 0042B5D0 is a separate 39,470-byte VM boundary. The
sound receiver, game flag lookup and full Item/Record/Overlay reward operations
also remain unresolved; an injected Environment would change the native entry.

Additional bounded renderer evidence identifies four separately constructed
40-byte records, a 72-byte three-list aggregate and the 65,536-element pool at
stride 0x600. Existing real Worker, Animation, Matrix4 and vertex value owners
must be reused. Record field roles, intervening storage, the unexplained word
after the second Animation and the full ownership protocol remain open.
No raw prefix, copied worker bytes or arbitrary padding supplies that receiver.

The native root also computes local bounds whose results are not consumed by
its normal control flow, and calls Timer::at_least(32) without consuming the
result. Their original source context remains unresolved. Do not add inert
locals or ignored calls solely to reproduce emission. Native effect/activation
epilogues clear EAX; the proposed return type and consistent public declaration
need whole implementation/caller corroboration before any header migration.

Continue with the actual renderer storage/publication and original Item reward/
activation protocol before admitting the full update. The maintained CORE107
graph remains 756 units/145 objects/142,383 disjoint bytes and 256 source files;
85 authored exact functions/25,785 bytes, 770 mappings, fourteen whole nonexact
methods and 238 absorbed reference functions remain unchanged. Whole-game
linkage, resources and runtime are independent open gates.

Private evidence is core108-item-update-native.asm and its attestation,
core108-item-update-dispatch.json, core108-item-protocol-native.asm and its
attestation, the decompiler hypothesis and core108-native-audit.json.gz.
Completed writers must not overwrite their reports. Current canonical pairs,
source, native evidence and active query inputs remain protected; heavy work
is serial at reduced priority and no unchanged graph is cold-built for cleanup.

Protected retirement removes three regenerable bytecode files totaling 33,919
bytes and three empty directories. All 756 existing-object exact results stay
identical to CORE107, and all 256 source files and 290 canonical object/receipt
hashes are unchanged. All 69 public tests pass in 271.776 seconds. Temporary CI
caches retire automatically; build remains about 8.2 MiB and analysis 113 MiB.
No compiler trials are generated in this investigation. Normal-flow reachability
and actual current dependency names are retained in core108-normal-flow.json
and core108-dependency-owners.json.gz; cleanup is core108-cleanup.json.gz.
