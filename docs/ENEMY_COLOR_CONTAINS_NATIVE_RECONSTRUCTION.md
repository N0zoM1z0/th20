# Enemy opcode 549 and 551: genuine list membership and packed-color types (CORE/EXACT-178)

All comparisons use only Japanese TH20 v1.00a Steamless PE32 (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`).
The original Enemy `execute_opcode` root at `0x0048C010` is still a single
**41,967-byte unimplemented, nonexact function**. This checkpoint adds two
**separately complete original callees** rather than treating any Enemy case
span as its own exact function.

## Corrected type and returned-value identity for opcode 551

Our first ABI hypothesis was demonstrably wrong: we temporarily changed
`AnimationHandle::operator=(uint32_t)` to return uint32 because the
opcode 551 case calls a 24-byte word setter. Before accepting that change,
we cold-compiled every affected unit: **53 providers / 354 previously exact
functions**. Those tests identified two genuine original functions:

* **`0x004117A0`, 21 bytes:** a **void-returning** four-byte setter,
  physically shared with `Identifier32::operator=`. The original Animation
  release and Item spawn callers really target this function.
* **`0x0045D650`, 24 bytes:** writes the 32-bit input and then explicitly
  returns that **same input in EAX**. Multiple original color-value producers
  call it, including Enemy opcode 551 at `0x00495C64`.

The earlier 53-object diagnostic products and the record of two failed
caller relocation comparisons are retained in private
`.analysis/core177-rejected-abi-assumption.json` and its protected scope.
The incorrect three-file ABI alteration was restored **without discarding
any previously committed work**. Original AnimationHandle's void-return
signature remains unmodified and its physically folded native target
unchanged. This explains why blindly believing the earlier candidate would
have silently misattributed two different functions to one type.

The repository already maintains the genuine **four-byte** `PackedColor`
value class for effects. A natural `PackedColor::operator=(uint32_t)` returning
`input` emits the **entire 24/24-byte** native `0x0045D650` function with **no
relocations** under the pinned MSVC 19.44.35211 x86 profile. Its new
zero-argument `PackedColor()` also compiles structurally identical to the
**23-byte** original four-byte zero constructor at `0x00425CC0`. That physical
constructor head was already accepted for `AnimationHandle` and shared scalar
values; **zero additional byte/unit credit** is taken for the alias.
The original PackedColor class spelling remains inferred; the data and
separate setter ABIs are independently corroborated.

The whole Enemy 551 case still needs a subsequent private host revision to
replace its historical AnimationHandle **semantic surrogate** with actual
PackedColor. The genuine late `BackGroundInf` global pointer at `0x005C069C`
is independently published in the original background initializer and
cleared by the matching native `shutdown BackGroundInf` destructor. The full
background interpolation/Renderer owner remains unresolved; no invented
background facade is used to gain whole-root byte credit.

## Complete native opcode 549 list-membership query

The root's opcode **549** obtains the true Context EnemyController before
reading `integer_argument(1)`, calls the original **`0x0049BF00`** predicate,
zero-extends its AL boolean result, then writes to the actual
`integer_argument_destination(0)`. The whole-root caller, which includes
output-destination evaluation after the predicate, is not independently
byte-exact and will be integrated separately.

`EnemyController::has_identifier(uint32_t)` is a distinct **244-byte**
original member, not the existing pointer-returning **251-byte**
`EnemyController::find` at `0x00498A80`. It short-circuits identifier zero,
iterates the genuine intrusive Enemy list starting at Controller+`0x108`,
compares full `Enemy::Identifier32` values and returns a **bool**. The actual
native routine includes SEH registration, x86 stack cookie, complete
`IntrusiveIterator<Enemy>` construction, traversal and destruction on both
successful and exhausted paths. Natural maintained source emits
**244/244 complete native bytes**, with **13 independently corroborated
relocations** covering the established iterator operations, Ghidra-observed
shared EH handler at `0x0056838D` and security cookie/check at
`0x005B25C0` / `0x005429EE`. No relocation target comes from reverse solving
the tested comparison field.

## Joint include-closure replay, resource preservation and tests

The two new methods change the real `EffectParameters.hpp/.cpp` and
`EnemyController.hpp` / `DamageQueryProtocol.cpp` owners. Actual original
compiler include closures select **14 affected providers / 85 previously
exact complete functions**. Every provider was cold-built under locked MSVC
into `build/core178-canonical/`; all **85 old + 2 new = 87/87** complete
strict units replay exactly, covering **16,836 compared bytes**. The
physically shared 23-byte PackedColor constructor is deliberately not an
additional unit. Compiler-local string label changes were reconciled only
after original and newly compiled complete COFF constant bytes and native PE
constant bytes agreed. All **28** protected original object/receipt SHA-256
values remain unchanged, and all **150** unmodified canonical providers retain
valid build receipts. Exact new authored coverage is **268 bytes**.

The production PackedColor host checks 28 combinations of dirty storage and
full-width signed-looking color words. The actual DamageQuery host exercises
10 membership/empty/duplicate/unlinked-list cases with whole owner and Enemy
object byte snapshots, including iterator observer cleanup. Both focused
public suites pass after enabling dead-section linking in the larger core
fixture; actually executed functions remain live, and original unresolved
resource APIs are **not** stubbed or credited as implemented.

Private reproducibility artifacts:
`.analysis/core178-combined-protected-scope.json`,
`core178-literal-reconciliation.json`, `core178-combined-final-replay.json`,
`core178-final-exact-proof.json` and the rejected-hypothesis CORE177 proof.

## Remaining work

Native exactness is established only for the **two whole callees**. The
41,967-byte Enemy root's opcode 549 and 551 caller paths, its 174-head primary
switch, nested tables, shared tails, exception metadata, background
resource/interpolation lifecycle, original executable startup and playable
whole-program linkage remain separate. Portable host tests do not establish
original Windows execution.
