# Enemy whole-root opcode 549 and corrected opcode 551 color identity (CORE179)

The sole target is Japanese TH20 v1.00a Steamless PE32, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The real Enemy dispatcher is still one **41,967-byte** root at `0x0048C010`,
with full native control tables, merged exits, data/EH and complete runtime
resources **not compiler-exact**. This checkpoint updates its single complete,
private source candidate, not fragments treated as independent functions.

## Independently decoded entire opcode 549 path

The native opcode **549** interval is **`0x00495D7F` through `0x00495DDE`
(end exclusive), 95 full native bytes / 20 instructions**. It calls exactly:

| Original call site | Native callee | Role |
| --- | --- | --- |
| `0x00495D8B` | `0x00412730` | actual `Context::enemy_controller()` getter |
| `0x00495D9E` | `0x004AB080` | `EnemyState::integer_argument(1)` |
| `0x00495DB6` | `0x0049BF00` | complete real `EnemyController::has_identifier` |
| `0x00495DCC` | `0x004AA9E0` | late `EnemyState::integer_argument_destination(0)` |

The **cached** EnemyController is selected from `EnemyState::context` at
+`0x2EC` **before** reading operand1. The predicate returns native `bool` in
AL, explicitly **zero-extended to a full 32-bit 0 or 1**. The output address
is evaluated only **after** the predicate returns, and the entire result word
is then written. Re-reading Context to choose the predicate receiver, calling
the pointer-returning `EnemyController::find`, or resolving the VM destination
early would alter the actual execution order.

[CORE/EXACT-178](ENEMY_COLOR_CONTAINS_NATIVE_RECONSTRUCTION.md) accepted
`EnemyController::has_identifier` as a complete **244/244-byte** original
function, including all 13 authentic iterator/EH/security relocations. The
private CORE179 host calls **this production method** on genuine intrusive
Enemy lists, including a real duplicate identifier and a high-bit identifier.
The nested actual `EnemyState→Enemy→EclRuntime` VM destination routing is
also executed, using only the final still-open EclManager destination token
as an explicit host boundary. No fake Enemy query or early-filter substitute
is introduced.

## Corrected 551 type: real PackedColor, not AnimationHandle

The earlier private CORE176 host labeled the four-byte color operand as an
`AnimationHandle`, because original opcode551 calls a shared 23-byte
constructor at `0x00425CC0`. Full-source ABI replay in CORE178 proved that
this **folded constructor is shared**, and does **not** identify the color
owner: the original 24-byte, uint32-returning assignment at `0x0045D650`
is distinct from the accepted 21-byte, void-returning handle writer at
`0x004117A0`. Its real naturally typed owner in the maintained source is
`PackedColor`; both complete methods compile byte exact without duplicating
the shared zero constructor.

CORE179 now uses **production `PackedColor` constructor and operator=** in the
same opcode551 case before constructing the real `FogValue`. The old
integer read order `0,1,2`, float read order `4,3`, blue/green/red/alpha
channel semantics, late borrowed `0x005C069C` BackGroundInf global identity
and original call boundary remain unchanged. All **170 old color/FogValue
scenarios** pass after this type correction. Complete native BackGroundInf
fog interpolation, startup/cleanup and Renderer owners remain external and
are explicitly **not** inferred from a shared constructor.

## Full 41KB root verification, including failures and retargeting

CORE176 had **37,649** whole-root passing host scenarios. CORE179 adds
**336** complete opcode549 cases: four actual Enemy intrusive-list topologies,
seven searched 32-bit IDs, two Context/controller retargeting choices, two
late result-target choices, and three outcomes (success, operand failure or
destination failure). The new private whole-root host passes
**37,985/37,985** in one freshly built **80-translation-unit** C++20 O2/UBSan
executable. This includes *every* previously tested movement/health/drop,
Card/clear/rank, FrontInf/Dialogue, 502/503 recursive animation, 516/575
Sound/Player, 517/518 Screen/message, 524/553 Game/Controller,
554 BulletController and 551 FogValue path in the same host.

During operand1 evaluation, the test deliberately retargets **both** the
original Context's EnemyController and the active EnemyState's Context and
EclManager owner. The query must still operate on the **original cached
Controller**, while destination0 must route through the **new live VM owner**.
The test uses complete before/after byte images of the real EnemyController,
linked Enemies, EnemyState and Context. Both iterator early-return and full
list-exhaustion paths must leave **zero intrusive iterator observers**.
Failure at the operand read must not call the predicate or destination;
failure while resolving the destination must not write the boolean result.
No silent clearing, false-positive match, or guessed index is permitted.

The full original opcode549 machine-code interval and native call SHA are
in `.analysis/core179-enemy-549-native-audit.json`; the private natural root,
full host, fixture and build recipe are `core179-enemy-dispatch-candidate.cpp`,
`core179-dispatch-host.cpp`, `core179-enemy-membership-host-cases.inc`,
`core179-fog-host-cases.inc` and `core179-dispatch-host-recipe.json`. The
private `core179-enemy-whole-root-proof.json` binds **96** actual source and
fixture input files to SHA-256, plus executable/log hashes, and confirms the
unaltered CORE176 candidate, host, fog fixture and log hashes. All **164**
accepted pinned-MSVC object/receipt pairs were independently verified.

## Exactness and outstanding work

This CORE179 stage changes **zero maintained C++ source files and zero
canonical exact units**. Exact credited whole-function coverage remains
**214 authored functions / 56,890 bytes, 1,000 physical strict units**.
The private semantic whole-root draft covers **121 effective opcode values /
92 primary heads**. The 41,967-byte native Enemy root is **still not exact**;
its 174-head compressed primary routing, four nested rank tables, shared
exit/data/EH, complete graphical and subsystem state are still unclosed.
The remaining high-value incomplete paths include 539, 548 and 555, as well
as native background/resource lifetimes. No runnable Windows game or
overall percent-complete byte claim follows from portable host tests.
