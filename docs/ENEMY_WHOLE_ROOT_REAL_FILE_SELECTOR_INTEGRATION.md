# CORE191: real byte-exact resource selector in the entire Enemy boss host

The complete **41,967-byte** native `EnemyState::execute_opcode` at
`0x0048C010` remains **machine-code nonexact**. This checkpoint works inside
its *single whole-root source draft*, preserves all CORE188 tests and replaces
the old test-only `EnemyController::animation_file` stub with the **actual
production 151-byte** function accepted in CORE/EXACT-190. It is not a
standalone truncated ECL function and creates **no additional native exact
credit** beyond CORE190's 151/151-byte strict replay.

## Native entry and real call chain

The native resource selector `0x004AAE10` was independently accepted in
`src/EnemyResourceSelection.cpp`: it dispatches index 7 to the unresolved
Stage owner/global `0x005C069C`, index 0 through the independently exact
`BulletController::animation_file`, index 1 through `EffectInfo`, and all
other signed indexes into a checked `std::array<AnimationFile*,8>::at`.
Its original native bytes have **7 native relocation anchors** and the source
passed complete relocation-aware strict replay for **68/68 affected units
across 12 cold MSVC x86 objects**, as documented in
[the selector's separate exact acceptance](ENEMY_RESOURCE_SELECTOR_EXACT_RECONSTRUCTION.md).

The original opcode 555 caller at native `0x0048C3F4` is part of that same
41,967-byte boss. The whole-root private candidate now forwards to the real
production selector through a **host-only adapter** that retains the old
injected failure path for existing historical regression scenarios. When no
host failure hook is active, the adapter calls the **unmodified**
`EnemyController::animation_file`. There is no replacement implementation
in the host. Actual native pointer semantics matter: the outer opcode
selects an EnemyController from `EnemyState::context`, and the real selector
subsequently loads **that controller's own Context at `+0x130`** for its Bullet
and Effect branches. These can deliberately differ. An index-7 call reads the
live Stage global, independently of either Context. Invalid indexes reach the
actual checked array's exception path without executing the downstream
seven-argument animation VM producer.

## Newly exercised behavior

The new private `.analysis/core191-exact-selector-host-cases.inc` executes
**146 additional tests**: 36 direct calls to the actual selector, 110 complete
opcode-555 paths. They cover the real 0, 1, 2, 3, 5 and 7 index paths,
negative/overflowing indices and `std::out_of_range`, two independent
EnemyControllers and Contexts with nested re-selection, the stage getter's
exception propagation, preserved sound-first side effects, full unchanged
State/Controller/Context byte images, zero VM operand reads, and actual
four-argument AnimationFile wrapper calls. The original game Stage getter
`0x004AADF0` is still unimplemented; a **fixture-only**
`StageResourceOwner::animation_file` observes that boundary without claiming
native codegen or fabricating Stage layout. Downstream renderer/VM creation
is likewise an explicit fixture boundary. The real EffectInfo getter and
Context effect access are linked through their already recovered owner
interface; unrelated full EffectInfo lifecycle code is not needed to run this
specific caller contract.

Full host results under **GCC13 -O2 / -Wall / -Wextra / -Werror**:

- **40,638/40,638** entire-root semantic cases under UBSan: all previous
  40,492 cases plus 146 newly executing the actual production selector.
- **40,638/40,638** entire-root cases under ASan+UBSan, with leak detection.
  Only `vptr` instrumentation is excluded because unrelated unresolved
  `WeaponStoneInfo` virtual key-function RTTI is not linked into this
  private host. Other address and undefined-behavior checks remain enabled.

The successful logs are `.analysis/core191-dispatch-host.log` and
`.analysis/core191-dispatch-host-asan.log`; the new source, fixture and recipe
are `.analysis/core191-enemy-dispatch-candidate.cpp`,
`.analysis/core191-dispatch-host.cpp`,
`.analysis/core191-exact-selector-host-cases.inc`, and
`.analysis/core191-dispatch-host-recipe.json`. Complete input/output hashes,
including both `build/core191-dispatch-host*` binaries, are recorded in
`.analysis/core191-enemy-whole-root-proof.json`. Old CORE188/187 and prior
proof-bound artifacts remain intact.

## Exactness and cold replay scope

CORE191 modified **only ignored private host artifacts**, and none of the
canonical production source/header/compiler inputs. It therefore required
**zero new native cold-build/strict replay units**, with no full or unrelated
cold replay. The already admitted CORE190 native **151/151-byte** exact
function and its **68/68** affected units are unchanged. The current draft
covers **128 effective opcode values / 96 original primary heads** (of
174), not all machine-code branches. Full native switch partitions, EH,
missing primary heads, Stage owner/getter, Renderer VM and shared queued
selector remain important open targets.
