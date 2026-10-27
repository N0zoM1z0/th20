# Enemy whole-root opcode 517/518: ScreenInf creation and message cleanup (CORE170)

The locked target is Japanese TH20 v1.00a Steamless PE32, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete **41,967-byte** EnemyState opcode dispatcher at `0x0048C010`
remains unaccepted as native byte exact, including its main and nested jump
tables and EH contribution. This is a whole-root semantic checkpoint that
retains the CORE169 complete candidate and all previously passing cases.

## Two complete original case intervals

Both original intervals are directly bounded and independently decoded from
the hash-attested PE, with their actual call addresses and native instruction
counts preserved in `.analysis/core170-enemy-517-518-native-audit.json`:

| Opcode | Original interval (end exclusive) | Full bytes | Instructions |
| --- | --- | ---: | ---: |
| 517 | `0x00493F8E`–`0x00493FF1` | **99** | 25 |
| 518 | `0x00493FF1`–`0x0049407F` | **142** | 31 |

Their shared dispatcher successor and return code belong to the enclosing
root; neither interval is a function-level exact contribution.

## Opcode 517: genuine ScreenInf and seven-argument factory

The original code evaluates **`integer_argument(2)`**, then **`(1)`**, then
**`(0)`**, storing each full signed word separately. It calls the genuine
`0x004250F0` factory as:

```cpp
request_screen_factory_boundary(1, first, second, third, 0, 0, 0);
```

The first argument **1** and final three **0** words are constants; the source
order and stack order are independently confirmed from every call instruction
and push before `0x00493FE4`. The factory's return value is intentionally
**ignored** by the native case.

Independent native analysis confirms that `0x004250F0` is a complete
**81-byte ScreenInf allocation factory**, not Stage, SoundInf or a fabricated
service: its actual diagnostic constant at `0x0056D768` is
`D:\cygwin\home\zun\prog\th20\src\core\screen.cpp:580 ScreenInf`.
The factory uses the existing allocator at `0x005B8894`, requests an actual
**0x44-byte** owner through the `0x00422D40` allocation/constructor helper,
returns null on a failed allocation, otherwise writes the seventh argument at
owner+`0x40` before calling `0x00423BF0`. That initializer has a full
**637-byte** native body and a ten-way selector over modes 0..9; opcode 517
supplies mode 1. Its callback/scheduler and memory ownership are not yet
reconstructed. A host-captured call preserves the complete observable
seven-argument contract without pretending the pending allocator/initializer
ran or claiming its allocation-failure behavior.

## Opcode 518: four successive genuinely typed owners

The actual native order is:

1. Evaluate `integer_argument(0)` then load **current** `FrontInf` global at
   `0x005C06A4` and call message dispatch `0x004B9740`
2. Reload `state.context` at State+`0x2EC`, obtain the actual first field
   `Context::bullet_controller()` and invoke `BulletController::cancel_all(0)`
   at `0x0047CB90` (its return count is unused)
3. Reload `state.context`, obtain the actual +`0x14` LaserController pointer
   and call `LaserController::cancel_all(0, 0)` at `0x004C9490` (return unused)
4. Reload `state.context` again, obtain its +`0x08` `EnemyController*` and call
   the existing **whole strict-exact** `EnemyController::clear` at `0x004A4A20`

These Context fields are independently accepted typed owners, not arbitrary
source offsets assigned to guessed services. Crucially, the three context
reads happen **after** the preceding external operation; no single cached
Context should replace them. The current FrontInf is loaded *after* the
argument read, so an operand callback can select a different message owner.

The 626-byte real FrontInf message body and complete Bullet/Laser cancellation
remain unresolved native resource interfaces, so the private host captures
their calls without constructing a fake Renderer/Stage facade. It executes the
**real** `EnemyController::clear()` on an intentionally empty actual intrusive
list and observes its Timer increment. Existing separate Enemy clear tests
exercise nonempty real lists; this new host does not falsely claim full
resource/message execution.

## Complete whole-root host and failure ordering

CORE170 retains the previous **36,802** scenarios, the now-complete private
502/503 flag paths, the real 516/575 source callees, and all earlier natural
whole-root cases. It adds **379** independent checks:

- **343** Screen cases (7³ complete three-word operands) checking index read
  order 2→1→0 and all seven argument values at the factory boundary
- **3** integer operand exceptions at each intermediate read, plus **1**
  injected factory-boundary exception after all reads. Neither establishes
  that original null-allocation behavior throws
- **28** message/clear cases (7 message codes × 2 global Front retargeting
  choices × 2 discarded Bullet/Laser return patterns) checking the exact
  Front→Bullet→Laser→Enemy sequence, three live Context retargets and real
  `EnemyController::clear` Timer advancement
- **4** injected exceptions after the operand, Front message, Bullet or Laser
  operation, proving no later owner call or Enemy clear is performed

All **37,181/37,181** whole-root tests pass with 78 real C++ source
translation units, `g++-13 -O2 -fsanitize=undefined` and nonrecovering
sanitizer errors, retaining `-Wall -Wextra -Werror`. Host fixtures are bounded
resource/startup captures; native game rendering, screen allocation, original
Win32/COM and complete full-dispatch byte identity remain unproved.

## Reproducibility, safe scope and remaining work

Ignored private evidence files (under `.analysis/`, not tracked reconstructed
production code) include `core170-enemy-517-518-native-audit.json`,
`core170-enemy-dispatch-candidate.cpp`, `core170-dispatch-host.cpp`,
`core170-screen-message-host-cases.inc`, `core170-dispatch-host-recipe.json`,
`core170-dispatch-host.log` and `core170-whole-enemy-root-proof.json`.
The proof records all 90 source/fixture SHA-256 bindings, preserves CORE169
inputs, attests the original native bytes, verifies the 78 source providers,
and checks **all 164 unchanged canonical object receipts**.

The private draft now covers **116 effective opcode values / 87 native primary
heads** (the prior CORE169 graph had 114/85). This changes **zero** tracked
production units or exactness claims. Authored exactness remains **208 complete
functions / 56,444 original bytes**, with **994 strict units**.

The major open work is the full 41,967-byte dispatcher emission, its 174-head
primary and four nested tables, exception metadata, true Renderer/ScreenInf
owners, pending 626-byte FrontInf message body, sound/laser/bullet resources,
and remaining state opcodes including 524, 539, 548/549, 551 and 553..555.
See [full root architecture](CORE_ENEMY_DISPATCH_LAYOUT.md),
[502/503 verified visibility paths](ENEMY_VISIBILITY_OPCODE_502_503_RECONSTRUCTION.md)
and [earlier 516/575 real callee integration](ENEMY_WHOLE_ROOT_516_575_INTEGRATION.md).
