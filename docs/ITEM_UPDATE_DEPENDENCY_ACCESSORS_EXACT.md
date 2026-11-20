# ItemInf update dependency accessors — exact native C++ boundaries

The 4,757-byte `ItemInf` frame-update callback at `0x004C25A0` reads four scalar values from the current `Player` object's embedded `PlayerMotionParameters` block and writes the ItemInf speed-scale field. These are real owner methods, not synthetic offset wrappers.

| Native address | Natural owner method | Native field | Result |
|---|---|---|---|
| `0x004C4940` | `Player::motion_parameter_00_value()` | `Player + 0x2080` | 20/20 exact, no relocations |
| `0x004C4920` | `Player::motion_parameter_04_value()` | `Player + 0x2084` | 20/20 exact, no relocations |
| `0x004C4900` | `Player::motion_parameter_08_value()` | `Player + 0x2088` | 20/20 exact, no relocations |
| `0x004B8050` | `Player::motion_parameter_10_value()` | `Player + 0x2090` | 20/20 exact, no relocations |
| `0x004C4F70` | `ItemInf::set_speed_scale(float)` | `ItemInf + 0x49C860` | 29/29 exact, no relocations |

The four getters are implemented in `src/PlayerMotionParameterAccessors.cpp`; the setter is implemented in `src/Item.cpp`. Each has a separate canonical match unit and replay target. The native getter receiver is `Player*`, not `PlayerMotionParameters*`; this is why the C++ methods live on `Player` even though the fields are represented by the embedded `PlayerMotionParameters` member.

A further caller dependency at `0x004C4F00` is now named `BombController::active_for(int)`: the native predicate checks `active_state == 1` and `age.less_than(duration)`. Its natural C++ implementation is in `src/Bomb.cpp`, but currently compiles to 58 bytes versus the 72-byte native body, so it remains reconstructed with zero exact-byte credit.

This closes five small native boundaries directly used by the still-open 4,757-byte `ItemInf` update. The large update itself remains open; these helper matches are not counted as reconstruction of the boss.
