# Enemy ECL opcodes 1002 and 1003 — state-store source frontier

The maintained natural-C++ `EnemyState::execute_opcode()` root now handles
native Enemy ECL opcodes **1002** and **1003**. These are inline case fragments
of the original 41,967-byte dispatcher at `0x0048C010`; they are not separate
native functions and receive no standalone function-byte or origin credit.
The parent remains **NONEXACT**.

## Locked native case map

The Japanese TH20 1.00a compressed selector table identifies:

| Opcode | Selector | Native interval | Bytes / instructions | Ordered direct calls |
| ---: | ---: | --- | ---: | --- |
| 1002 | 171 | `0x00496355..0x00496387` | 50 / 10 | `0x004AB080`, `0x00412730` |
| 1003 | 172 | `0x00496387..0x004963A2` | 27 / 6 | `0x004AB080` |

The independent root verifier pins the original branch hashes, selector bytes,
branch boundaries, instruction counts and ordered call targets.

## Reconstructed behavior

### Opcode 1002 — EnemyController field +0xE0

The native sequence reads integer operand 0 first, then loads the EnemyState's
current Context and resolves its EnemyController, then writes the full 32-bit
operand to `EnemyController::field_e0` (`EnemyController + 0xE0`). The C++ root
uses the existing `Context::enemy_controller()` owner accessor and the existing
field declaration. It deliberately does not cache the controller before the
operand read.

The maintained ASan/UBSan root test retargets the EnemyState Context during the
integer read and verifies that only the newly selected controller receives the
word. A separate injected operand exception confirms that neither controller
is modified when the read fails.

### Opcode 1003 — EnemyState field +0x278

The native sequence reads integer operand 0 and stores its full signed
32-bit value directly to `EnemyState + 0x278`. The C++ root preserves the direct
field write and does not route it through an invented setter. A second test
injects an operand exception and verifies the previous field value remains
unchanged.

## Origin and ownership boundary

These two cases are part of the existing Enemy dispatcher switch table. Their
native selector entries do not describe independently callable functions, so
no synthetic rows are added to `config/functions.csv` or
`config/function-origins.csv`. `EnemyController::field_e0` remains a neutral
observed storage name; this case alone does not establish a broader semantic
name or prove the origin of the enclosing controller type. Likewise, the
`+0x278` state write does not create a standalone accessor origin. The full
41,967-byte parent origin/exactness boundary remains open.

## Verification

`scripts/verify-enemy-state-dispatch-frontier.py` re-decodes both native cases
from the locked PE and checks the maintained source order. Its focused root
host executes the production dispatcher with **130 source units under
ASan/UBSan**. No full cold replay is required or claimed.
