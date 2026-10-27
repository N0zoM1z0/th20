# Enemy opcode 553: true EnemyController field receiver (CORE/EXACT-171)

The sole target is the locked Japanese TH20 v1.00a Steamless PE32, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The native EnemyState dispatcher at **0x0048C010 (41,967 bytes)** remains
source-absent and **not** compiler exact. This batch reconstructs its complete
25-byte scalar dependency at **0x0049C490** and independently verifies opcode
553's actual owner/calling order, but grants no partial root exactness.

## Independent original control-flow and owner evidence

The opcode 553 head starts at **0x00495860**. The locked native instructions
first load `EnemyState::context` at State+`0x2EC`, call the real
`Context::enemy_controller()` at `0x00412730`, and cache that controller
pointer. Only then does the root read `EnemyState::integer_argument(0)`.
The full signed argument word is pushed to native `0x0049C490`, using the
already-cached receiver. The source-visible `Context` getter has an
independently supported physical-fold identity and must not be replaced with
`EnemyState` storage or fetched after a mutating operand callback.

The complete native callee is a **25-byte, zero-relocation x86 thiscall**
with one 4-byte argument and `RET 4`. It writes the argument unchanged to
`this+0x98`. The typed object is the already-established `EnemyController`
with a 16-byte `TaskInfo` base and native `EnemyData` at +0x10; the actual
`EnemyData::field_88` word occupies +0x98 in the locked 32-bit layout. A
pinned MSVC-x86 compile of the natural method
`void EnemyController::set_field_88(uint32_t value) { data.field_88 = value; }`
emits the **complete native 25 bytes exactly**, with no ignored fields,
truncated body, added padding, fake facade, or inline assembly. The native
layout identity is independently checked by an x86-only static assertion.
The field's broader gameplay meaning and original source spelling are not
inferred from a write alone.

## Protected provider-wide replay

The actual compiler `/showIncludes` receipts select **eleven** affected
translation-unit objects, carrying **65 previously exact whole units**.
After changing the real EnemyController header and EnemyData source, each
of the eleven affected providers is cold rebuilt into
`build/core171-canonical/`, retaining all original object/receipt pairs.
The new 25-byte unit and all previous units strictly replay **66/66 exact**,
covering **14,881 complete compared bytes**. All **22** old object/receipt
SHA-256 values are unchanged and the **153** unaffected canonical object
receipts remain valid.

Six MSVC-generated C-string COFF symbol labels changed in the final cold
build: four in the Dialogue constructor, one in Enemy creation, and one in
EnemyController construction. Every final label was reconciled against both
the original pre-change COFF's complete constant bytes and the original PE's
full constant bytes at their independently established addresses. All six
original/old/new literal extents agree, not merely the portions through NUL.
No native target relocation was solved from compared bytes. The final
relabel proof is `.analysis/core171-literal-reconciliation.json`, with
full per-unit results and protected identities in the private
`core171-final-exact-proof.json` and `core171-enemy-controller-affected.json`.

The real Enemy owner host test additionally checks **30** field-word
transitions across both high/low-bit values against the complete object
byte image. Every other byte is required to survive. The host runs on x64,
so it compares using the actual member address rather than falsely equating
host offsets with x86; the separately attested x86 object confirms +0x98.
The full Enemy creation/reset/clear test suite passes its existing publication,
4,636 clear scenarios, and other gameplay/state checks. This is portable
O2/UBSan corroboration, not original game runtime execution.

## Remaining large-root work

Production `EnemyState::execute_opcode()` still needs its complete actual
41,967-byte body, index/pointer/nested rank tables, exception metadata and
compiler contribution. Opcode 553 is a confirmed constituent path and exact
callee; its *whole-root host integration* must separately exercise the
pre-operand cached receiver and setter effects. Opcodes 524, 539, 548/549,
551 and 554/555 likewise remain nonexact as part of the large root. No
partial case address span is admitted as a standalone function.
