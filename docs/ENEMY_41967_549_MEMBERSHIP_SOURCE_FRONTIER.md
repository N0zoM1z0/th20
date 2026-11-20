# CORE/RECON-1156 — natural-C++ Enemy opcode 549 intrusive membership query

The maintained source now contains `execute_enemy_membership_opcode(EnemyState&, opcode)` in `src/EnemyStateMembershipOpcode.cpp` for original opcode 549. This is an inline case fragment inside the **41,967-byte** Enemy ECL dispatcher, not a standalone original function.

## Original native branch

The locked TH20 1.00a Steamless PE case is `0x00495D7F..0x00495DDE`: **95 bytes / 20 x86 instructions / 4 direct E8 calls**, SHA-256 `94b89a73ee263e02923ec465dfaada31723c147463a95e99b68fe07b02e77b87`.

| Native call site | Target | Role |
| --- | --- | --- |
| `0x00495D8B` | `0x00412730` | Context's cached EnemyController getter body |
| `0x00495D9E` | `0x004AB080` | `EnemyState::integer_argument(1)` |
| `0x00495DB6` | `0x0049BF00` | complete 244B `EnemyController::has_identifier` |
| `0x00495DCC` | `0x004AA9E0` | late `EnemyState::integer_argument_destination(0)` |

## Restored evaluation and write order

1. Read and cache the live `EnemyController*` from `state.context`.
2. Read integer operand 1.
3. Call the real `EnemyController::has_identifier(uint32_t)` on the cached owner. This is the full intrusive-list traversal with native iterator cleanup and full 32-bit Identifier32 comparison.
4. Only after the predicate returns, resolve integer destination 0.
5. Write the `bool` result as a full 32-bit `0` or `1`.

The order matters: operand evaluation may retarget Context, but the native predicate still runs on the previously cached EnemyController; destination resolution is deliberately late. The source does not substitute `find()`, an early destination lookup, or a fake membership service.

## Scoped verification and exactness boundary

`src/EnemyStateMembershipOpcode.cpp` compiles as i386 COFF under the pinned MSVC profile. `scripts/verify-enemy-membership-opcode-source.py` extracts the original 95B branch directly from the locked PE, checks all 20 instruction heads and four direct-call sites/targets, validates the source order, and confirms the compiled object references the real Context getter, EnemyState VM accessors and accepted 244B membership method. The complete 36B EnemyState→Enemy→EclRuntime integer reader and late destination chains are now `matching`, as are their float and supplied-value siblings; see [the 12-function argument forwarding boundary](ENEMY_ARGUMENT_FORWARDING_BOUNDARY.md).

This is a source fragment, not a standalone original function. No parent byte credit is added. The complete 41,967B Enemy dispatcher remains **SOURCE-ABSENT, NONEXACT**. No full cold replay was performed.
