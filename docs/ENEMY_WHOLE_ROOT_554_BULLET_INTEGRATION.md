# Whole Enemy dispatcher: opcode 554 genuine BulletInf integration (CORE175)

The original target is Japanese TH20 v1.00a Steamless PE32, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This is a new, complete-case expansion of the single **41,967-byte** Enemy
`execute_opcode` source candidate at `0x0048C010`, retaining and building on
CORE173's fully tested 524/553, 502/503, 516/575 and 517/518 paths. It does
**not** create or accept an independently exact case-fragment function.

## Full original native opcode 554 path and source owners

The original opcode 554 interval spans **`0x004961D5` through
`0x0049623F` (end exclusive)**: **106 actual bytes / 22 instructions**,
including the actual jump to the shared Enemy root exit. Its full decoded
instructions and SHA-256 are in the ignored private
`.analysis/core175-enemy-554-native-audit.json`. The original native call
sequence is `0x0040C300`, `0x004AAFB0`, `0x004AAFB0`, `0x00486480`.

The first call reads the **real Context's first pointer slot**, the already
reconstructed `Context::bullet_controller()`, from the live Context obtained
through State+`0x2EC`. The original root **caches this receiver before
reading float arguments**. It then calls `EnemyState::float_argument(1)` for
Y, followed by `float_argument(0)` for X. The final call passes `(X,Y)` to
`BulletController::set_vector_4c(float,float)` at `0x00486480`, not to a
Renderer or fake EnemyState method.

[CORE/EXACT-174](ENEMY_OPCODE_554_BULLET_VECTOR_RECONSTRUCTION.md) independently
restored the complete actual **39/39-byte** callee with zero relocations and
the genuine native BulletInf `vector_4c` at owner+`0x4C` and +`0x50`. The
host uses the **real** production method and entire real BulletController
with its actual 2001-slot bullet pool; no synthesized owner is substituted.

## Complete root host regression and failure ordering

The prior CORE173 private root fixture passes **37,347** cases. CORE175 adds
**132** further scenarios and the freshly built complete host passes
**37,479/37,479** in one 79-source translation unit `g++-13 -O2
-Wall -Wextra -Werror -fsanitize=undefined -fno-sanitize-recover=all`
executable. New cases comprise **128** combinations (eight independent raw
binary32 patterns for X, eight for Y and two receiver-retargeting modes),
plus **four** injected failures at the first/second operand read. Every
successful case records the original Y-then-X read order and verifies the
complete byte images of *both* instantiated BulletController owners, as well
as the live EnemyState and Context where applicable.

The operand callback can change the active Context's BulletController pointer
and retarget `EnemyState::context` after the **first** float argument read.
The original receiver already cached in the root must still receive the
complete X/Y bits, even when those inputs include signed zero, positive
infinity, maximum finite float and a quiet NaN payload. The alternate owner,
all other native Bullet owner fields, and every unrelated Enemy/Context byte
remain unmodified. Throwing from either operand prevents any call to the
real setter. No null-check, zeroing or imaginary fallback is introduced.

The private complete-root recipe and proof are
`.analysis/core175-dispatch-host-recipe.json`,
`core175-enemy-dispatch-candidate.cpp`, `core175-dispatch-host.cpp`,
`core175-bullet-vector-host-cases.inc`, `core175-dispatch-host.log`, and
`core175-enemy-whole-host-proof.json`. The proof records **93** source and
fixture SHA-256 identities and the executable/log hashes. Protected previous
CORE173 private candidate, host, fixture and completed log hashes are still
identical. All **164** existing pinned canonical object receipts were
independently checked and are valid.

## Scope and remaining large-root blockers

The private semantic draft now covers **119 effective opcode values / 90
original primary heads**. CORE175 changes **zero maintained production C++
files, unit mappings, exactness claims, or native game assets**. The exact
registry remains **212 complete authored functions / 56,622 bytes** and **998
strict canonical units**. Full Enemy root byte matching is **still open**:
the 174-head primary routing, compressed index, four nested rank tables,
shared compiler data/EH and numerous actual unreconstructed owners remain.
The next high-value paths are opcodes 539, 548/549, 551, 555 and native VM/
Renderer integration. Full original game startup/linkage and playability are
not claimed by this portable host.
