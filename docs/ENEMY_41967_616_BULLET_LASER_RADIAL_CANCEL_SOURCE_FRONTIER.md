# Enemy ECL opcode 616 — paired Bullet/Laser radial cancellation

## Status and boundary

Opcode 616 is restored as natural C++ in `src/EnemyStateBulletLaserCancelOpcode.cpp`, routed through the maintained partial `EnemyState::execute_opcode` root and executed by its ASan/UBSan root host. It composes the existing Bullet and Laser cancellation Bosses rather than duplicating their traversals. This is an inline case in the original **41,967-byte** parent at `0x0048C010`, not a standalone native function. The parent remains **NONEXACT**, with no parent byte credit.

## Locked native branch

Target: Japanese TH20 1.00a Steamless `resources/th20.exe`, SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

- Opcode: `616`; compressed selector index `134`.
- Branch: `0x004954D1..0x00495580` (end-exclusive).
- Size: **175 bytes / 37 x86 instructions / 7 direct E8 calls**.
- Branch SHA-256: `f2ea21d098c1ea60855885898a57680558b066fdd2e610ba96fd7e91e1f16c84`.
- Final branch jump at `0x0049557B` targets common dispatcher epilogue `0x004963DF`.

| Call site | Target | Recovered role |
|---|---:|---|
| `0x004954D9` | `0x004AAFB0` | `EnemyState::float_argument(0)` — radius |
| `0x004954F0` | `0x0040C300` | `Context::bullet_controller()` shared +0 getter body |
| `0x00495501` | `0x00499350` | `EnemyState::position_ref()` |
| `0x00495529` | `0x0047D100` | `BulletController::cancel_near(center, radius, 0)` |
| `0x0049553A` | `0x0041CA90` | `Context::laser_controller()` shared +0x14 getter body |
| `0x0049554B` | `0x00499350` | re-read `EnemyState::position_ref()` |
| `0x00495575` | `0x004CAAD0` | `LaserController::cancel_near(center, radius, 0, 1)` |

## Recovered operation and aliasing

1. Read float argument 0 as `radius`.
2. Resolve `state.context->bullet_controller()`.
3. Obtain `state.position_ref()` and pass that `Vector3&`, radius and mode 0 to the real `BulletController::cancel_near` Boss.
4. After that Boss returns, resolve `state.context->laser_controller()` again.
5. Obtain `state.position_ref()` again and pass that reference, the same radius, mode 0 and virtual-cancel argument 1 to the real `LaserController::cancel_near` Boss.

Both centers are references to live `EnemyState::motion_110.position`, not snapshots. During Bullet traversal, a cancellation callback can mutate Enemy position, so subsequent distance checks observe the new center. The BulletController receiver remains cached for that traversal. Only after it returns does the Laser phase re-read both Context and Enemy position.

The root test proves this ordering: a Bullet cancellation callback changes Enemy position and retargets `EnemyState.context`. The in-flight Bullet traversal stays on the selected alternate BulletController while its aliased center follows the position mutation. The Laser phase then selects the newly current original LaserController and uses the new center. Tests assert controller counters, eligible/ineligible Bullet states, Laser state filtering and virtual circle-cancel arguments.

A radius-read exception occurs before either controller lookup or cancellation Boss. The root host checks that all cancellation counters remain unchanged.

## Real Bosses and explicit host boundaries

- `BulletController::cancel_near` at `0x0047D100`, **320 bytes**. The focused host links its real active-list traversal and `BulletDistance` predicate. `Bullet::cancel` is a test capture boundary that marks a selected Bullet cancelled and triggers the controlled retarget callback.
- `LaserController::cancel_near` at `0x004CAAD0`, **288 bytes**. The focused host links its real active-list traversal, cancel-position update and state-0/state-2 filter. A concrete test Laser subclass captures the real virtual `cancel_circle` dispatch and arguments; it does not claim to implement unseen concrete Laser cancellation children.

The controller owners and Context getters are production types and methods. No fake controller Boss or duplicate traversal is introduced.

## Focused verification

`scripts/verify-enemy-bullet-laser-cancel-opcode-source.py` checks the locked PE fingerprint, selector, branch extent and SHA-256, all 37 decoded instructions, seven ordered E8 call sites/targets and the common epilogue jump. It also checks natural source ordering and the Context/position accessors.

The maintained dispatcher verifier checks the locked-profile COFF relocation order:

`float_argument(0) → Context::bullet_controller → EnemyState::position_ref → BulletController::cancel_near → Context::laser_controller → EnemyState::position_ref → LaserController::cancel_near`

The production opcode helper and both real controller cancellation Bosses execute in the ASan/UBSan root host. Tests cover radius operand failure before side effects, live position aliasing during Bullet iteration, Context retargeting between Bullet and Laser phases, Bullet eligibility states 1/2 versus ineligible state 3, Laser eligibility states 0/2 versus state 1, and virtual circle-cancel arguments.

The maintained verifier passes **47 locked-profile i386 COFF source units** and **111 focused host source units** under ASan/UBSan. The 41,967B parent remains NONEXACT; no full cold replay or whole-parent byte credit is claimed.
