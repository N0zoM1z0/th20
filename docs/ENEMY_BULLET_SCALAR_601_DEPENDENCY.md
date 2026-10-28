# CORE/EXACT-203 — real BulletController scalar and original Enemy opcode 601

The locked TH20 Japanese Steamless v1.00a target remains SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The genuine complete **26-byte** `BulletController` member at
`0x0049C740` reads its single IEEE-754 float argument and stores the exact
bits at `BulletController+0x48`. It is accepted as maintained natural
C++20 `BulletController::set_scalar_48(float)` in
`src/BulletController.cpp`, with the actual `BulletController` layout and
member declaration in `src/Bullet.hpp`. The original source spelling is
inferred, not a recovered symbol. The whole 26-byte function contains **no
relocations**, no branches and no fabricated padding. The locked MSVC
19.44.35211 x86 `/Od /Ob0` profile emits **26/26 identical original
bytes**, digest
`7a3f9012e1a27c31a8a8622aaf33762796f4856e7ce0384ba3ea06138ccf4212`.

Independent original PE call sites `0x004929C9` and `0x00492A49` establish
that the caller is the original **593-byte Enemy opcode 601** primary head
`0x00492803..0x00492A53`, inside the complete still-nonexact **41,967-byte**
`EnemyState::execute_opcode` at `0x0048C010`. The native 601 branch also
uses the independently exact 305-byte ensure-only queued record/metadata
selector, the real Context BulletController owner, and later bullet-generation
calls; its own full control flow, ordered operands and downstream effects
must be independently integrated and tested. No 601 source/codegen or
41,967-byte root credit is claimed by accepting this 26-byte callee.

The actual `Bullet.hpp` include-closure from the existing compiler receipts
selects exactly **six** source providers. The shared BulletController object
moves from `build/core185-canonical/BulletController.obj` to
`build/core203-canonical/BulletController.obj` in the canonical manifest
for **all its previous same-source units**, not a duplicate TU. One original
BulletController constructor debug literal changed its MSVC-private `$SG`
symbol from `$SG79801` to `$SG79803`; original PE target `0x0056FC68`,
relocation offset/type and string bytes remain fixed. The complete
source-scoped reduced-priority strict native cold replay passed **35/35
old and new canonical units across exactly six cold objects**. Original
sizes, native bytes and all other relocation targets remain unchanged.
The complete scope/log/source/object/receipt hashes are privately protected
at `.analysis/core203-affected-replay.log` and
`.analysis/core203-bullet-scalar-exact-proof.json`. No full cold replay ran.

This checkpoint adds **one full authored function / 26 original bytes**,
bringing confirmed authored exact to **225 functions / 58,718 bytes**, with
**1,020 source-present mappings / 1,011 canonical units / 168 physical
comparison objects**, covering **183,109** compared original bytes.
The last entire Enemy source-draft host CORE202 still has **135 effective
opcode values / 103 original primary heads**, passing **43,125/43,125**
GCC O2/UBSan and ASan+UBSan scenarios. The new 26-byte callee has not yet
been integrated into that private host's complete opcode 601 branch.
A high-value continuation is to decode and reconstruct **the entire
593-byte native 601 case**, including both real scalar setter calls,
actual owned queued values and downstream BulletController operations.
