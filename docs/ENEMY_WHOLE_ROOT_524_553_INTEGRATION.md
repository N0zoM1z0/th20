# Enemy complete-root opcode 524/553 host integration (CORE173)

The sole locked target is Japanese TH20 v1.00a Steamless PE32, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint extends the **complete**, private **41,967-byte** Enemy opcode
dispatcher candidate at `0x0048C010`, not a source-accepted partial function.
The dispatcher remains **not byte exact**, with its jump tables, shared tails,
exception support and many opcode paths unresolved.

## Two independently audited original case intervals

| Opcode | Original native path | Complete path bytes | Instructions |
| --- | --- | ---: | ---: |
| 524 | `0x00495727`–`0x00495773` (end exclusive) | **76** | **14** |
| 553 | `0x00495860`–`0x004958A2` (end exclusive) | **66** | **14** |

The original contiguous bytes, instruction boundaries, exact call sites and
SHA-256 of both intervals are recorded in
`.analysis/core173-enemy-524-553-native-audit.json`. Their successor belongs
to the **enclosing** Enemy root; 76 and 66 are **not** new separately accepted
function bodies. Each path is added as a natural `case` to a **copy** of the
prior complete CORE170 host candidate, preserving the original candidate and
all previous test resources and source identities.

### Opcode 524: operand before global Game selection

Native order: `EnemyState::integer_argument(0)` at `0x004AB080`; fetch the
*current* process GameController pointer at **`0x005BA828`**; call genuine
`GameController::set_field_34` at **`0x0049C940`** with the already read whole
integer. Afterwards write that **original** integer to State+`0x280` and zero
State+`0x284`. The real Game method calls actual `PlayerTable::set_field_1fc`
at `0x0049C970` through process `Session` at `0x005BA568`, offset **+0x88**.
PlayerTable clamps the signed integer to `[0,999]`; Game+`0x34` retains all
original 32 bits. These two production dependencies were admitted by separate
whole-function exact replay in [CORE/EXACT-172](ENEMY_OPCODE_524_GAME_SESSION_RECONSTRUCTION.md).

The private test captures **only** the unresolved Game pointer publication,
not the Game implementation. During integer argument evaluation, it can change
the published pointer from one real Game object to another; the subsequent call
must go to the **newly published** object. Snapshot checks cover the complete
EnemyState, both complete Games and the complete process Session, allowing
only the original state's two explicit fields, the chosen Game word and the
real PlayerTable word to change. Failure of the operand read leaves all these
objects untouched and never performs the Game lookup.

### Opcode 553: Context receiver before operand evaluation

The native path first gets the real `Context::enemy_controller()` at
`0x00412730` through State+`0x2EC` and caches that receiver. Only then does it
call `EnemyState::integer_argument(0)` and call the native 25-byte
`EnemyController::set_field_88` at **`0x0049C490`**. The full callee was
reconstructed in [CORE/EXACT-171](ENEMY_OPCODE_553_CONTROLLER_FIELD_RECONSTRUCTION.md)
and writes the preserved argument to genuine EnemyController+`0x98`.

The host's operand callback deliberately changes **both** the original
Context's controller pointer and the State's Context pointer. The original
**cached** EnemyController alone must receive the full argument word;
complete owner, Context and EnemyState byte snapshots reject unintended
mutations. If operand evaluation throws, neither Controller is modified.
This distinction from opcode 524's **late** owner lookup is intentional and
confirmed by the original native call sequence.

## Entire root replay and protected provenance

The existing CORE170 private whole-root exercise had **37,181** passing
scenarios. CORE173 adds **166**: 80 full owner-retargeting/state scenarios
and 4 operand failures for opcode 524, plus 80 controller-retargeting/state
scenarios and 2 failures for opcode 553. All **37,347/37,347** scenarios pass
in one freshly compiled `g++-13 -O2 -Wall -Wextra -Werror -fsanitize=undefined
-fno-sanitize-recover=all` host with 79 actual source/fixture translation
units, including the real `GameController.cpp`, `Session.cpp`, and
`EnemyData.cpp`. The previous 502/503 recursive Animation, 516/575 actual
SoundInf/Player, 517/518 screen/message and every previous phase/clear/rank/
HUD/Dialogue path remain in the **same executable**.

`.analysis/core173-whole-enemy-root-proof.json` binds all **92** actual
source/fixture/private input paths to SHA-256, the executable and log hashes,
all the native case audit bytes, and protected earlier CORE170 evidence.
All **164** current canonical pinned-MSVC object build receipts remain valid;
there is **no change to reconstructed production source or exact-unit graph**
in this CORE173 checkpoint. The private draft adds two effective opcodes and
two native primary heads: **118 effective values / 89 primary heads**.

Unreconstructed OS/Game publication, Screen allocation, actual Renderer
lookup, original DirectSound queue, and some Front/Bullet/Laser resource
bodies remain explicit host boundaries. None is declared finished by these
portable behavior tests. Production Enemy opcode dispatch is still undefined;
there is **no partial root byte credit**. Authored exact count remains
**211 complete functions / 56,583 bytes**, with **997** strict exact units.

Further priorities: original paths 539, 548/549, 551, 554/555, and resolving
the full root's 174-head primary index plus its four nested rank tables,
shared compiler-owned EH and data contributions. The host must remain a
single complete-root candidate throughout.
