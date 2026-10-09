# Complete Item update investigation

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
