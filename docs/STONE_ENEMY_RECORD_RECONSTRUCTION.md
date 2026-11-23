# StoneEnemyRecord — opcode-1001 record and UI creation path

The original Enemy ECL opcode **1001** enters a game-specific record-creation
path rooted in `StoneEnemyController`. The maintained natural-C++ source now
restores three complete native functions in `src/StoneEnemyRecord.cpp`:

| Native entry | Maintained function | Bytes | Exact result |
| ---: | --- | ---: | ---: |
| `0x005119E0` | `StoneEnemyRecord::StoneEnemyRecord` | 76 | 76/76 |
| `0x00511870` | `DiagnosticAllocator::allocate_object<StoneEnemyRecord>` | 129 | 129/129 |
| `0x00512F60` | `StoneEnemyController::add_record` | 69 | 69/69 |

All three replay from one fresh canonical i386 COFF object. The original
1,847-byte record/UI initializer at `0x00512FB0`, record retirement, and the
complete opcode-1001 branch integration remain open.

## Owner and record layout

The original `StoneEnemyController` contains an intrusive record list at offset
zero. Its record is exactly `0x34` bytes on i386:

| Offset | Maintained member | Native evidence |
| ---: | --- | --- |
| `0x00` | `IntrusiveLink<StoneEnemyRecord> link` | five-pointer link constructor at `0x00418A10`, then `initialize(this)` at `0x0044A670` |
| `0x14` | `EnemyHandle enemy_14` | four-byte constructor at `0x00425CC0`; the large initializer resolves this field through `EnemyHandle::resolve` |
| `0x18` | `AnimationHandle handle_18` | four-byte constructor at `0x00425CC0`; assigned from the native text/resource factory |
| `0x1C` | `Timer timer_1c` | 16-byte Timer constructor at `0x00422D90` |
| `0x2C` | `std::int32_t field_2c` | trailing word; original semantic role remains unknown |
| `0x30` | `std::int32_t field_30` | trailing word; original semantic role remains unknown |

The original record type spelling remains unknown; `StoneEnemyRecord` is a
maintained descriptive alias. The trailing words are not initialized by the
record constructor. The allocation template's original MSVC `/sdl`
class-auto-initialization zeroes the full object before calling the constructor.

## Exact constructor and allocator factory

The 76-byte constructor preserves the original order:

1. default-construct the intrusive link;
2. construct the `EnemyHandle` at `+0x14`;
3. construct the `AnimationHandle` at `+0x18`;
4. construct the Timer at `+0x1C`;
5. call the actual link `initialize(this)` method.

The 129-byte factory is the original
`DiagnosticAllocator::allocate_object<StoneEnemyRecord>` template
instantiation. The maintained declaration is a C++ `class`, so the locked
MSVC `/sdl` profile naturally emits the native class-auto-initialization call
to `0x0040C080` between `operator new(0x34)` and the record constructor. No
manual byte clearing, assembly, or padding is used to imitate this behavior.

`scripts/replay-exact-units.py --source src/StoneEnemyRecord.cpp` verifies all
three functions together: **3/3 exact units, 1 fresh canonical COFF object**.
The shared `IntrusiveLink.cpp` source also retains all **16/16** existing
strict units after its pure-store `initialize` method was correctly marked
`noexcept`.

## Record creation wrapper and origin boundary

The exact 69-byte `StoneEnemyController::add_record` wrapper preserves the
native sequence:

1. call the process `DiagnosticAllocator` at `0x005B8894` with the original
   source-diagnostic label at `0x00574240`;
2. append the newly constructed record's intrusive link to `records` using the
   real `IntrusiveList<StoneEnemyRecord>::append` at `0x00411EA0`;
3. call the large `StoneEnemyRecord::initialize` Boss at `0x00512FB0` with the
   two original integer parameters.

The source label is independently pinned by `config/source-diagnostics.csv`:
`D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\stoneenemy.cpp:76 StoneEnemyInf`.

Origin is kept separate from exactness:

- `DiagnosticAllocator::allocate_object<StoneEnemyRecord>` remains
  **unknown / CxxAllocator / pending**. It is a generic template instantiation;
  strict exactness does not make the template authored.
- `StoneEnemyRecord::StoneEnemyRecord` is **authored / medium confidence** as
  the constructor of a custom game-owned record reached only through the
  StoneEnemyController/opcode-1001 path. Its original spelling remains inferred.
- `StoneEnemyController::add_record` is **authored / medium confidence** from
  its source diagnostic, process allocator, owner-list append and large
  game-specific record initializer call. The maintained method spelling is
  descriptive, not claimed as original debug metadata.

The large `StoneEnemyRecord::initialize` function at `0x00512FB0` is 1,847
bytes and still contains substantial UI/resource logic: a borrowed EnemyHandle,
text/image creation, four player-specific branches, five level variants and
callback publication. Its complete natural-C++ body, resource lifetime and
controller retirement remain the next Boss frontier. No whole-function exact
credit is claimed for it or for the 41,967-byte Enemy dispatcher.
