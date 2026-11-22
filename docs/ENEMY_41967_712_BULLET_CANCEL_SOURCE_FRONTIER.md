# CORE/RECON-1250 — Enemy ECL opcode 712 rectangle bullet cancellation

The maintained source now contains
`execute_enemy_bullet_cancel_opcode(EnemyState&, opcode)` in
`src/EnemyStateBulletCancelOpcode.cpp` for original opcode 712. This is an
inline case fragment in the **41,967-byte** `EnemyState::execute_opcode()`
Boss, not a standalone original native function.

## Original native case proof

The immutable Japanese TH20 1.00a Steamless PE has selector index **164** for
opcode 712. Its branch is `0x0049540D..0x004954D1`: **196 bytes / 42 x86
instructions / 9 direct E8 calls**, SHA-256
`d7fe973dc2a13c2a161ca9e99220b46579422719db4eae024fac9edce9bfd0f9`.
The focused verifier extracts the branch from the locked PE, checks the full
executable SHA-256, decodes the selector and pins every E8 call-site address
and destination in original order.

| Original E8 site | Target | Native operation |
|---|---:|---|
| `0x00495413` | `0x00422E10` | Construct the 12-byte rectangle dimensions Vector3 |
| `0x00495420` | `0x004AAFB0` | Read float operand 0 |
| `0x00495433` | `0x004AAFB0` | Read float operand 1 |
| `0x00495455` | `0x0048BCE0` | Index EnemyState's EnemyAnimationLink vector at element 0 |
| `0x0049545C` | `0x0044CED0` | Resolve its AnimationHandle |
| `0x00495473` | `0x0040C300` | Read the Context's primary BulletController pointer |
| `0x00495484` | `0x00437930` | Read Animation Z rotation |
| `0x00495495` | `0x00499350` | Obtain the EnemyState's live Motion position reference |
| `0x004954C6` | `0x0047CC90` | Call the complete 707-byte rectangle-cancellation Boss |

The `0x0040C300` word getter is physically shared with the already mapped
16-byte `Identifier32::get` body; the Context role is expressed through the
typed `Context::bullet_controller()` source method, without duplicate
physical-byte credit. The 33-byte vector subscript target at `0x0048BCE0`
remains a separate native library leaf, not a new authored game-byte claim.

## Natural-C++ reconstruction and order

The source follows the original call order:

1. Construct a real `Vector3 dimensions`, then read float operands 0 and 1
   into X and Y. Its Z lane remains the constructor's zero value.
2. Resolve `state.animations[0].handle` through the real
   `AnimationHandle::resolve()` method.
3. Fetch the live BulletController from the current Context.
4. Read the resolved Animation's Z rotation.
5. Obtain `state.position_ref()` and call
   `cancel_in_rectangle(center, dimensions, direction, 1, 0)`.

No null fallback, cached animation transform, alternate controller lookup,
or synthetic geometry path is introduced. The source fragment is connected
to the maintained dispatcher in `EnemyStateExecuteOpcode.cpp`.

## Root-host execution

The maintained ASan/UBSan dispatcher host now executes the production opcode
712 helper and the actual **707-byte**
`BulletController::cancel_in_rectangle` Boss. That Boss uses the real
`geometry::rectangle_circle` implementation twice per eligible Bullet:
first against the user rectangle, then against the fixed **384×448** gameplay
viewport. The real active intrusive list, iterator lifetime, eligibility
gates, cancellation counter and effect-mode assignment are exercised.

The tests cover:

- VM-referenced float operands read in order 0 then 1.
- A `pi/2` animation rotation: a Bullet inside the rotated rectangle is
  cancelled while an axis-aligned-only candidate is not.
- Both accepted Bullet states (1 and 2), plus rejection of state 3 and
  nonzero `field_18`; only cancelled Bullets have their effect mode replaced.
- A candidate inside the user rectangle but outside the fixed gameplay
  viewport, rejected by the second native geometry test.
- An exception on the second float operand: animation-handle resolution and
  the 707-byte cancellation Boss are never entered.

Opcode 518 also now uses the real **242-byte**
`BulletController::cancel_all` and **19-byte** `active_list` methods in the
same root host, rather than false-returning controller stubs.

## Explicit host boundaries and exactness

The 51-byte `AnimationHandle::resolve`, 17-byte
`Animation::rotation_z_value`, 25-byte `EnemyState::position_ref`, 707-byte
`BulletController::cancel_in_rectangle`, 669-byte
`geometry::rectangle_circle`, 242-byte `BulletController::cancel_all` and
19-byte `BulletController::active_list` production bodies are linked. The
root fixture supplies the not-yet-reconstructed 456-byte
`AnimationPoolOwner::resolve_handle` lookup and the nonexact 662-byte
`Bullet::cancel` child as explicit test boundaries. Consequently the root
test proves the caller, geometric filtering and cancellation handoff; it does
not claim the complete Animation pool resolver or Bullet cancellation side
effects are restored.

Affected-only exact replays passed:

- `BulletRectangleCancellation.cpp`: **1/1** (707/707 bytes).
- `RectangleCollisions.cpp`: **12/12**, including the 669-byte rectangle-circle leaf.
- `BulletCollisionHandle.cpp`: **2/2**, including the 51-byte handle resolver.
- `AnimationGeometry.cpp`: **6/6**, including the 17-byte rotation getter.
- `BulletCancellation.cpp`: **2/2**, including 242-byte cancel-all and 19-byte active-list getter.

The maintained root verifier checks the original 196B/42-head/9-E8 branch,
all nine ordered natural-C++ COFF relocations, and runs the production helper
under ASan/UBSan. It compiles **35** locked-profile i386 COFF source units.
No full cold replay was run. This is an inline source fragment: no
`config/functions.csv` standalone function row or parent byte credit is
added. The 41,967-byte dispatcher remains incomplete and NONEXACT.
