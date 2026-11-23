# Laser mutation setter leaves — six strict exact C++ methods

**CORE/EXACT-1252 through CORE/EXACT-1257.** Six original Laser member
setters called by Enemy ECL opcodes 705–710 now have independent strict match
units in `config/match-units.toml`. All are natural C++ in
`src/LaserCommandMethods.cpp`; none uses inline assembly, byte patches or
padding.

| Exact ID | Native method | Address | Bytes | Original store |
| --- | --- | ---: | ---: | --- |
| 1252 | `Laser::set_handle` | `0x0049C500` | 25 | `Laser+0x8C` |
| 1253 | `Laser::set_parameter_vector_704` | `0x0049C800` | 40 | three Vector3 words at `Laser+0x704` |
| 1254 | `Laser::set_angle` | `0x0049C8C0` | 26 | `Laser+0x70` |
| 1255 | `Laser::set_parameter_field_714` | `0x0049C8E0` | 29 | `Laser+0x714` |
| 1256 | `Laser::set_field_7c` | `0x0049C900` | 26 | `Laser+0x7C` |
| 1257 | `Laser::set_speed` | `0x0049CB10` | 26 | `Laser+0x78` |

The vector and `+0x714` setters use direct typed C++ assignments. Their
locked MSVC i386 code reproduces the original three-word copy and scalar
`movss` store exactly. The remaining four scalar/handle methods are likewise
byte-for-byte exact. All six have zero relocations and total **172/172 exact
native bytes**.

Focused strict replay:

```text
LaserCommandMethods.cpp
  i386 COFF OK: build/gpt-web-laser-canonical/LaserCommandMethods.obj
  laser_set_handle: exact (25/25 bytes)
  laser_set_parameter_vector_704: exact (40/40 bytes)
  laser_set_angle: exact (26/26 bytes)
  laser_set_parameter_field_714: exact (29/29 bytes)
  laser_set_field_7c: exact (26/26 bytes)
  laser_set_speed: exact (26/26 bytes)
  Exact replay: 6/6 units, 1 cold objects
```

These are small leaf functions, not substitutes for the larger Enemy ECL
caller work. Their original callers are the inline Enemy opcode 705–710
fragments; see [the caller/source frontier](ENEMY_41967_705_710_LASER_MUTATIONS_SOURCE_FRONTIER.md).
The 41,967-byte `EnemyState::execute_opcode()` parent remains **NONEXACT**.
