# StoneEnemyRecord — native 0x34-byte list record

The 1,847-byte native Boss called by Enemy ECL opcode 1001 creates a record
through `StoneEnemyController::records`. The maintained record declaration is
`src/StoneEnemyRecord.hpp`; its constructor is natural C++ in
`src/StoneEnemyRecord.cpp` and strictly replays the complete original
76-byte constructor at `0x005119E0`.

## Owner and layout evidence

The original `StoneEnemyController` contains an `IntrusiveList` at offset zero.
The opcode-1001 call chain reaches the 0x34-byte allocation factory at
`0x00511870`, which zeroes the allocated block and invokes the constructor at
`0x005119E0`. The constructor's complete native call sequence establishes:

| Offset | Maintained member | Native evidence |
| ---: | --- | --- |
| `0x00` | `IntrusiveLink<StoneEnemyRecord> link` | five-pointer link constructor at `0x00418A10`, followed by `initialize(this)` at `0x0044A670` |
| `0x14` | `AnimationHandle handle_14` | constructor at `0x00425CC0` |
| `0x18` | `AnimationHandle handle_18` | constructor at `0x00425CC0` |
| `0x1C` | `Timer timer_1c` | constructor at `0x00422D90` |
| `0x2C` | `std::int32_t field_2c` | no store in the record constructor |
| `0x30` | `std::int32_t field_30` | no store in the record constructor |

The record is exactly `0x34` bytes on i386. The two trailing words are
intentionally left without member initializers: the allocation factory's
preceding zero-fill establishes their initial zero values, not this constructor.
The original record type spelling and the semantic roles of those trailing
words remain unknown; `StoneEnemyRecord` is a maintained descriptive alias.

## Strict constructor replay

The constructor preserves all five original direct calls and their order:

1. default-construct the intrusive link;
2. construct handle `+0x14`;
3. construct handle `+0x18`;
4. construct the 16-byte Timer at `+0x1C`;
5. call the actual link `initialize(this)` method.

`scripts/replay-exact-units.py --source src/StoneEnemyRecord.cpp` passes
**76/76 bytes in one fresh canonical COFF object**. The independent unit pins
the original PE identity, entry `0x005119E0`, full extent and all five ordered
relocations. The shared `IntrusiveLink.cpp` source also retains all **16/16**
existing strict units after its `initialize` declaration was correctly marked
`noexcept`; no unrelated byte or padding shaping was added.

The maintained Enemy root host constructs a real `StoneEnemyRecord` and checks
its self-node publication, null link observers, zero handles and zero Timer.
The full opcode-1001 / 1,847-byte Boss, record allocation factory, controller
record retirement and resource ownership remain separate open boundaries.

## Origin boundary

The constructor is classified as **authored / medium confidence**: its unique
allocation/call chain is rooted in the game-specific StoneEnemyController and
Enemy opcode-1001 path, and the record combines the game's intrusive-list,
AnimationHandle and Timer members. Strict byte identity alone is not used as
origin evidence. The maintained type spelling is inferred, and no authorship
claim is made for the generic IntrusiveLink, AnimationHandle or Timer leaves.
