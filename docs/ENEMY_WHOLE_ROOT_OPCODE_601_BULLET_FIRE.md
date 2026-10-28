# CORE204: full native Enemy opcode 601 and real Bullet scalar owner

This checkpoint extends **the same complete 41,967-byte original Enemy
`execute_opcode()` source draft** at `0x0048C010`, not a standalone partial
opcode function. The original locked TH20 Japanese v1.00a Steamless target is
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The **complete native opcode 601 primary head** spans
`0x00492803..0x00492A53`: **593 bytes / 136 x86 instructions / 16 original
direct calls**. Its original PE bytes, original complete direct-call sites,
branch boundary and jump back into the overall root were independently
verified against the native case-path catalog; original SHA-256:
`d609387a30cbbf027daf25c6f822ba9b8624e1b61d37a14f679329d1d3275319`.
The complete branch instruction transcript is
`.analysis/core204-native-op601.asm` and its native audit/proof is
`.analysis/core204-native-601-audit.json`.

## Native call sequence and ownership

Original opcode 601 first reads only `integer_argument(0)` from the active
ECL. It calls the **separately byte-exact 305-byte**
`EnemyState::shared_shot` at `0x00498D10`, not the superficially similar
396-byte COW `writable_shot`. This distinction matters: an existing shared
`EtamaArgInf` is **not cloned**. The genuine `std::pmr::forward_list`
grows when needed and a null metadata owner is allocated, then an
actual two-pointer pair is returned (record pointer and `owner.get()`).

The original `EnemyQueuedRecord::vector_40.z` is compared to the *native
0.9f* constant at `0x0056FC00`, bit pattern `0x3F666666`, via `comiss`
and `jbe`. Only **strictly greater**, ordered values select
`record.vector_40 + record.vector_34` and force the resulting
`ShotParameters::position.z` to positive zero. The ordinary, equal,
negative and NaN/unordered paths use
`state.motion_110.position_ref() + record.vector_34`, preserving Z.
The record's genuine 40-byte `ShotParameters` has its x/y/z vector updated
in-place. No other source VM operands are read.

The caller then asks the **current live Context** for its real
`BulletController`, and executes the separately accepted complete
**26-byte `set_scalar_48(float)`** at `0x0049C740`, passing
`EnemyState::field_274` as raw float bits (native call site
`0x004929C9`). It fetches the current Context's BulletController again,
passes the same record's **borrowed `ShotParameters&`** and a *genuine
by-value copy of its `shared_ptr<EtamaArgInf>`* to the complete original
339-byte firing routine at `0x00481780`. This **339-byte routine is not yet
source/COFF exact**; the new complete-root fixture captures the actual
input interface and exception boundary without fabricating its body.

Finally, but **only if firing returns normally**, it queries the live
Context a third time and calls the genuine `set_scalar_48(0.0f)` again
(native site `0x00492A49`). If the firing callback changes the Enemy's
Context before return, the final reset applies to the **new** controller;
the old controller retains its earlier `field_274` value. If firing throws,
there is **no final reset**. Previous notes about a cached owner or COW on
601 would therefore be wrong.

## Same-root integration and direct evidence

The active entire-root source draft is
`.analysis/core204-enemy-dispatch-candidate.cpp`. Its 601 case executes
real `EnemyState::shared_shot` and real `BulletController::set_scalar_48`
source, plus real Vector3 and Motion position owners. Only the
unimplemented original 339-byte Bullet emitter is captured by
`fire_bullets_boundary`; the previous 600, 700/701, 609–612, 702/703,
711/713, 539/555 and other completed cases stay in the **same**
`enemy_draft::exercise_dispatch_candidate` function.

New private `.analysis/core204-op601-host-cases.inc` passes
**314 complete caller tests**: **266** normal ensure-only selection and
firing observations, **126** first-time shared metadata allocations,
**70** preserved shared aliases, **56** actual forward-list expansions,
**60** strict-relative/zero-Z versus **206** absolute-position cases
(including unordered NaN input), **133** late Context retargets,
**42** firing exceptions preserving the preceding scalar, and **6**
pre-selector ECL operand exceptions that prevent any shot emission or
scalar update. The tests assert real record value/position bits,
shared control-block lifetime, genuine input-pair receiver identity,
three owner resolution points, no extra VM reads, and complete other
Enemy state preservation. A discovered test-fixture error concerning a
newly expanded record's **actual constructed `vector_40.z`** was fixed:
expectations now read that real record, not a synthetic old-record input.
The fix is limited to the test, not the native algorithm.

The **full 85-translation-unit Enemy host** passes **43,439/43,439**
scenarios, retaining all **43,125 previous** cases, under *both* GCC 13
`-O2 -Wall -Wextra -Werror` with UBSan and the same with ASan+UBSan.
Only vptr instrumentation is disabled in the latter due unrelated
unlinked `WeaponStoneInfo` key-function RTTI; leak detection remains enabled.
Proof-bound source/recipe inputs, two successful host binaries and both
full logs are hashed in `.analysis/core204-enemy-whole-root-proof.json`.
The logs are `.analysis/core204-dispatch-host.log` and
`.analysis/core204-dispatch-host-asan.log`. All CORE203, CORE202, CORE201,
CORE200 and earlier original-input proofs and binaries remain preserved.

## Acceptance and next high-value work

This entire-root semantic integration changed **no maintained native
compiler source, header, profile or unit manifest**, so the affected native
cold build/replay scope for CORE204 is **zero**, not a full cold replay.
The previously accepted CORE/EXACT-203 scalar setter already passed its
own **6 objects / 35 complete affected strict native units** under locked
MSVC; no extra exact byte credit is claimed for opcode 601. The original
41,967-byte root and its switch/EH partition remain **machine-code nonexact**.
The root draft now covers **136 effective opcode values / 104 original
primary heads** of 174. Conservative authored exact remains **225
functions / 58,718 bytes**, with **1,020** mapped source-present entries,
**1,011** canonical strict units and 168 physical objects.

A high-value dependency to attack next is the original complete
**339-byte BulletController firing method** at `0x00481780`: its real
per-shot iteration, count/rows gate, `0x004818E0` subordinate emitter,
sound request, owned metadata and exception lifecycle need independent
original byte/ABI reconstruction. Nearby other original 602/603/604
queue-parameter ECL branches and the large remaining main-root heads are
also unresolved. Do not turn a small leaf into an unsupported claim that
the entire Bullet firing factory or 41,967-byte Enemy opcode dispatcher
is source/byte-exact.
