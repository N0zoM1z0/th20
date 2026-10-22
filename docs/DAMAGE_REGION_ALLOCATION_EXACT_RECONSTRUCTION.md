# Damage-region allocation and lifecycle ownership

CORE/EXACT-131 accepts the complete 73-byte scalar DamageRegion factory at
`004BFE30`. The existing allocation template and user-provided constructor are
unchanged. Source presence, application origin, compiler emission and physical
coverage are reviewed separately.

## Native observations and compiler result

The attested Ghidra listing and complete locked-PE decoding show a 196-byte
ordinary allocation, a null branch, the shared initializer, the actual Region
constructor and a thiscall return that pops the diagnostic argument. The
independent pool constructor also uses stride 196 and count 256. Shape
configuration, collision, identifier and Context consumers establish the actual
Region storage; allocation size alone is not its layout oracle. See
[Region routing](EXACT_DAMAGE_REGION_RECONSTRUCTION.md) and
[controller lifetime](HIT_CONTROLLER_LIFECYCLE_RECONSTRUCTION.md).

Changing only `struct DamageRegion` to `class DamageRegion { public: ... }`
allows the existing shared `new T` body to emit the native 73-byte factory under
its recorded C++20/Od/Ob0/GS/Gy/Zl/SSE2/fp:precise/sdl/EHsc/Gd profile.
Public access, 196-byte storage, member initialization, noexcept construction
and translation-unit ownership are preserved. No explicit clear, alternative
constructor, inert local or type-specific allocation body is introduced.

The pinned compiler automatically emits the complete 31-byte thiscall
initializer. Its memset relocation reuses the established `00544760` entry;
the full helper aliases the already-covered `0040C080` implementation. The
factory's other relocations reuse ordinary new at `0054275D` and the previously
accepted complete Region constructor at `004BFFB0`. The factory's target fields
are not solved to choose any of these anchors.

The class/struct emission difference is a candidate-compiler observation,
corroborating the earlier [Node result](FUNCTION_CHAIN_ALLOCATION_EXACT_RECONSTRUCTION.md).
Original declaration spelling and a global game compiler profile remain
inferences. Typed COFF tags change consistently from U to V in affected
providers and consumers; this is not a storage or calling-convention change.

## Shared scalar release and physical deduplication

The full 97-byte Region release implementation at `00413B70` is already covered
by the canonical ECL intrusive-node release unit. That existing source, object,
symbol and physical mapping remain its canonical owner. A fresh Region-typed
support replay independently confirms the entire implementation with its eight
relocations; it adds no second unit, mapping or byte credit.

Null release returns without destruction or locking. Otherwise destruction
precedes acquisition of game recursive-lock slot one. Unsized scalar delete
executes under the guard, followed by unlocking and cookie verification. The
Region's implicit trivial destruction emits the complete five-byte empty cdecl
`std::destroy_at` body at the existing `0040C6B0` fold. The independently reviewed
ECL trivial-node destruction already establishes that role and anchor. Both the
five-byte destruction alias and 31-byte initializer receive zero duplicate
coverage. See [ECL lifetime](EXACT_ECL_RUNTIME_LIFETIME_RECONSTRUCTION.md).

## Independent origin and boundary review

The original `src/game/hit.cpp` diagnostic strings, HitCtrlInf RTTI and TaskInfo
base, actual 256-region pool, Context publication, scheduler priority 28,
identifier generation, shape consumers and active/free-list lifecycle establish
application ownership independently of byte matching. The custom allocator's
receiver/diagnostic callers and destroy-before-game-lock protocol establish its
application role; invoking new, destroy_at and SDK guards does not make the
whole allocator an SDK implementation.

The following 26 complete, now-authored exact functions contribute 6,221 bytes
to newly reviewed authored coverage. Of these, 6,148 bytes were already covered
physically, including the 97-byte ECL/Region release fold. Only the new 73-byte
factory increases physical coverage.

| Address | Body bytes | Application operation |
| --- | ---: | --- |
| 004C1030 | 2696 | Region collision routing |
| 004C0F50 | 22 | Region position reference |
| 004C0FE0 | 20 | Region Context getter |
| 004C1000 | 48 | Heap-identifier test |
| 004C1C50 | 290 | Rectangle configuration |
| 004C1D80 | 260 | Circle configuration |
| 004C2030 | 37 | Region position assignment |
| 004BFFB0 | 359 | Region construction |
| 004C03D0 | 164 | Region frame update |
| 004C1F30 | 138 | Region retirement |
| 004BFEE0 | 191 | HitCtrlInf construction |
| 004C2090 | 54 | Controller Context selection |
| 004C0C60 | 67 | Identifier generation advance |
| 004C1EB0 | 70 | Detach and pool return |
| 004C0B30 | 265 | Controller initialization/publication |
| 004C0E60 | 225 | Pool allocation and heap fallback |
| 004C0CB0 | 13 | Scheduler callback adapter |
| 004C1AE0 | 151 | Rectangle creation |
| 004C1B80 | 140 | Circle creation |
| 00478EC0 | 26 | Global Context/controller lookup |
| 004C0120 | 230 | Controller destruction |
| 004C0D00 | 264 | Identifier lookup |
| 004C02D0 | 248 | Controller frame traversal |
| 004BFDE0 | 73 | Controller scalar allocation |
| 00413B70 | 97 | Shared trivial-object scalar release |
| 004BFE30 | 73 | Region scalar allocation |

Complete PE decoding reconciles every direct branch with an instruction head
inside its full body and retains every return. Existing five-byte COFF alignment
tails on Region construction, controller construction/destruction and pool
construction remain compared. Older Ghidra function-membership omissions do not
shorten the canonical bodies. The entire 2,696-byte collision route is retained.

Global controller creation at `004C20D0` is also authored: its original
diagnostic, actual allocation, initialization and failure cleanup establish the
application protocol. It remains whole source82/native92 because the native
otherwise-unused pointer reset and branch partition remain unexplained. It
receives no exact unit or partial credit.

The 81-byte pool-array constructor at `004BFE80` is classified as compiler code:
the SDK aggregate has no user-written constructor body, and the compiler emits
the count/stride/vector-construction/EH sequence. All 86 contribution bytes,
including alignment, remain exact. The 19-byte `_Unchecked_end` at `004C0C40`
is SDK library code, corroborated by the pinned array header's `_Elems + _Size`
body and actual pool consumers. These two exclusions remain separate from
authored totals. Generic list-front origin remains pending.

## Verification and remaining scope

All 163 original object/receipt pairs are verified before the header edit.
Captured compiler include lists identify six actual affected objects. Each is
built once; all 57 previous affected units strictly replay, and 157 unaffected
objects retain their immutable receipts. Three generated string labels are
rebound only after preserving the original complete NUL payload, independently
checking its target literal and matching the fresh relocation role.

All 80 public tests pass in 294.135 seconds, including actual pool/heap
lifecycle, observer repair, shape routing and shared owner fixtures. No new
semantic body is introduced. Retirement removes 14 superseded object/receipt
products totaling 407,238 bytes after preserving their original SHA-bound inputs
and immutable receipts in a verified 259,711-byte archive. All 852 current units
then strictly replay from existing objects with all 326 protected hashes and the
frozen source unchanged; cleanup invokes no compiler. Existing profiles, extents,
targets and relocation roles are preserved for all 851 prior units.

The maintained graph contains 852 strict physical units, 163 objects and 164,237
disjoint comparison bytes. Source mappings remain 860, with eight mapped whole
functions nonexact. Confirmed origins are 152 authored and 36 excluded, with
6,740 candidates pending; authored exact coverage is 148 functions / 42,390
bytes. These reviewed-subset totals do not measure whole-game completion.

Private evidence includes `.analysis/core131-region-lifetime-native.asm`,
`core131-boundary-origin-audit.json`, `core131-admission-results.json`,
`core131-affected-results.json.gz` and the original SHA-bound input archive
`core131-pre-header-inputs.json.gz`. Current products and final validation are
recorded in [the handoff](RE_HANDOFF.md).

The whole 1,707-byte damage query remains unimplemented and unaccepted. Native
heap release before later query reads and the unconsumed visit counter remain
open; no inert counter or invented lifetime repair is added. Startup, complete
resource ownership, whole-game linkage and native playable behavior remain open.
