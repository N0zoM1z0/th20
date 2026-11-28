# Laser extended-command steppers (CLAUDE/EXACT-009)

Six Laser functions are strict exact in `src/LaserCommands.cpp`, 2,557
credited bytes:

| Address | Size | Function | Vtable use |
| --- | --- | --- | --- |
| `0x004C81F0` | 75 (+5 INT3) | `LaserExtendedCommands::LaserExtendedCommands()` | called by the Laser base constructor on `+0x90` |
| `0x004D58D0` | 438 | `advance_command1` | Line and Curve slot 21 (identical bodies fold) |
| `0x004D5710` | 440 | `LaserLineInf::advance_command10` | Line slot 22 |
| `0x004D5580` | 386 | `LaserCurveInf::advance_command2` | Curve slot 23 |
| `0x004D5310` | 609 | `LaserLineInf::advance_command3` | Line slot 24 |
| `0x004D50A0` | 609 | `LaserCurveInf::advance_command3` | Curve slot 24 |

The base Laser vtable (`0x005710BC`) holds the folded `return 0` stub
`0x00412540` in slots 20..32. Slots 21..24 are therefore non-pure base
virtuals returning 0, and each family overrides only the commands it uses.

The steppers follow the matched Bullet commands 1, 10, 2 and 3
(`src/BulletCommandVelocity.cpp`, `BulletCommand2.cpp`, `BulletCommand3.cpp`)
with the Laser fields: `field_7c` is the moving speed, `angle` (`+0x70`) is
a plain float, and the command bits are cleared in the low word of
`active_commands` (`+0x698`). Laser command 3 only adds the turn step,
without Bullet's seven-way switch. Its completion sound is
`LaserType0Parameters::field_4c` (`+0x744`) for Line and
`LaserType2Parameters::motion_sound` (`+0x738`) for Curve.

`Laser::commands` is now `LaserExtendedCommands` (24 slots). Its `at()` folds
with the exact Bullet accessor at `0x0047C680` (`index << 6`, no bounds
check). The native base constructor builds it through `0x004C81F0`.

Replay: `LaserParameters.hpp`, `LaserLineInf.hpp` and `LaserCurveInf.hpp`
changed. A source-filtered replay of their 27-source closure gives 60/60
exact units in 27 cold objects.

## Next leads

The four Laser vtables (Line `0x00571148`, Curve `0x00571214`, Infinite
`0x005712E8`, Beam `0x00571374`) still list about 35 unmatched virtuals in
`0x004C9000..0x004D8000`, including the large update/draw/initialize bodies
(Line slot 2 is 3,706B, Curve slot 2 is 3,817B, Curve slot 5 is 2,665B). The
Laser headers have small include closures (4 to 27 sources), so this family
is cheap to iterate.
