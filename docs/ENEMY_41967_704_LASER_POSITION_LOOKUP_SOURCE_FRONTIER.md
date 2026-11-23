# Enemy ECL opcode 704 — Laser handle position lookup fragment

**CORE/RECON-1266.** Native opcode 704 now executes a natural C++ source
fragment through the maintained `EnemyState::execute_opcode` root. It reuses
the restored `LaserController::find_laser` leaf and the real virtual
`Laser::set_position` interface. This is an inline branch of the 41,967-byte
Enemy dispatcher, not a standalone native function and not parent exact-byte
credit.

## Locked native evidence

The original Japanese TH20 1.00a branch is selector index **156** and spans
`0x00494FD3..0x00495083`: **176 bytes / 37 x86 instructions / six direct E8
calls plus one conditional virtual call**. Its SHA-256 is:

`e348b0806a20d6a2fb48e480d00ac785d21a6845be8374e2217965e34fd079df`

| Native call site | Target | Recovered operation |
| --- | --- | --- |
| `0x00494FDF` | `0x0041CA90` | capture the current Context LaserController |
| `0x00494FF2` | `0x004AB080` | read integer handle operand 0 |
| `0x0049500A` | `0x00498FF0` | resolve the Laser by handle |
| `0x0049501B` | `0x00422E10` | construct a zeroed Vector3 temporary |
| `0x00495028` | `0x004AAFB0` | read float operand 1 into X |
| `0x0049503B` | `0x004AAFB0` | read float operand 2 into Y |
| `0x00495077` | indirect vcall | invoke the Laser's `set_position` slot only on a hit |

The branch then jumps to the original common dispatcher epilogue. Its order
is significant: the controller is captured before the handle read; the Laser
lookup completes before Vector3 construction and both float reads; and the
virtual setter occurs only after both float operands have succeeded. A miss
still consumes both float operands but skips the setter.

## Natural C++ and root-host behavior

`src/EnemyStateLaserOpcode.cpp::execute_enemy_laser_lookup_opcode` is a
separate production helper, called directly from
`EnemyState::execute_opcode`. It captures `state.context->laser_controller()`,
reads `integer_argument(0)`, calls `find_laser`, constructs `Vector3`, reads
`float_argument(1)` then `float_argument(2)`, and invokes the actual virtual
`Laser::set_position` only when lookup succeeds. The Vector3 constructor
supplies the native zero Z lane; the explicit `position.z = 0.0f` on the hit
path preserves the native pre-vcall store.

The maintained ASan/UBSan root host uses two real intrusive Laser lists and
checks:

- Context retargeting during the handle read does not change the already
  captured controller;
- Context retargeting during the first float read does not change the
  already resolved Laser;
- both float operands are consumed on a missing handle, with no virtual call;
- a throwing handle read prevents Vector3/float work and the setter;
- a throwing second float occurs after lookup but before the setter;
- the active intrusive lists are cleaned up after the scenarios.

The independent verifier
[`scripts/verify-enemy-laser-lookup-opcode-source.py`](../scripts/verify-enemy-laser-lookup-opcode-source.py)
pins the locked PE identity, selector, branch extent/hash, six E8 targets,
conditional vcall and ordered natural-C++ COFF relocations. The maintained
root verifier runs **129 focused host source units** under ASan/UBSan and
compiles **62 locked-profile i386 COFF units**; no full cold replay is used.

Opcode 704 and sibling Laser caller fragments 705–710 and 714 now all have
natural C++ source and focused root coverage. The six small setter leaves
called by 705–710 strictly replay 172/172 bytes; see the [705–710 mutation
frontier](ENEMY_41967_705_710_LASER_MUTATIONS_SOURCE_FRONTIER.md). Opcode
714's virtual flag behavior is documented in the [714 flag frontier](ENEMY_41967_714_LASER_PARAMETER_FLAG_SOURCE_FRONTIER.md).
The complete 41,967-byte `EnemyState::execute_opcode` parent remains
**NONEXACT**. No inline parent byte credit is claimed.
