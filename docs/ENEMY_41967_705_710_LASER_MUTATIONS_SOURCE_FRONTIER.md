# Enemy ECL opcodes 705–710 — Laser mutation fragments

**CORE/RECON-1267.** All six inline Laser mutation cases are now represented by
natural C++ in `src/EnemyStateLaserOpcode.cpp`, dispatched from the production
`EnemyState::execute_opcode()` root, and exercised by the maintained
ASan/UBSan host. They remain inline fragments of the 41,967-byte parent; no
standalone function or whole-parent exactness is claimed.

## Original native branch map

The Japanese TH20 1.00a selector table maps the six opcodes to indexes
157–162. Their complete original case ranges total **724 bytes / 158 x86
instructions / 31 direct E8 calls plus one indirect virtual call**. Each case
ends at the original common dispatcher epilogue `0x004963DF`.

| Opcode | Selector | Native range | Bytes / instructions | Native action |
| ---: | ---: | --- | ---: | --- |
| 705 | 157 | `0x00495083..0x00495122` | 159 / 33 | resolve handle; read X/Y; copy Vector3 to Laser+`0x704` |
| 706 | 158 | `0x00495122..0x0049518F` | 109 / 24 | if found, read float and write Laser+`0x7C` |
| 707 | 159 | `0x0049518F..0x004951FC` | 109 / 24 | if found, read float and write Laser+`0x78` |
| 708 | 160 | `0x004951FC..0x00495269` | 109 / 24 | if found, read float and write Laser+`0x70` |
| 709 | 161 | `0x00495269..0x004952D6` | 109 / 24 | if found, read float and write Laser+`0x714` |
| 710 | 162 | `0x00494F52..0x00494FD3` | 129 / 29 | if found, virtual `erase(0,0)`, then clear handle |

The maintained verifier pins the PE identity, each selector and pointer-table
entry, complete branch extent, SHA-256, instruction count, ordered direct-call
targets and the opcode-710 indirect call site. The 710 virtual call loads the
Laser vtable slot at `+0x44`; the existing `Laser` declaration identifies
that slot as `erase`.

## Reconstructed behavior and operand order

- **705:** capture `Context::laser_controller()` before reading integer handle
  operand 0; resolve with `LaserController::find_laser`; construct a Vector3;
  read float operands 1 then 2; if the handle exists, set Z to zero and copy
  all three words to Laser+`0x704`. Unlike 706–709, a miss still consumes both
  float operands. The second-float exception occurs before the vector write.
- **706–709:** capture the controller, read handle operand 0 and resolve the
  Laser. A missing handle returns before reading float operand 1. A hit reads
  that float once and calls the corresponding native field setter: `+0x7C`,
  `+0x78`, `+0x70`, or `+0x714` respectively.
- **710:** capture controller, read handle and resolve. On a hit, invoke the
  actual virtual `Laser::erase(0,0)` first, then call `Laser::set_handle(0)`.
  The handle is therefore still the original value during erase. A miss does
  neither operation.

The source helpers preserve the distinct 705 float-read behavior and the
706–709 null guard before the float read. They do not collapse opcode 710 into
a handle-only clear or replace the virtual erase with a direct field store.

## Six strict-exact natural C++ setter leaves

The six small methods called by these inline branches now have individual
strict match units in `config/match-units.toml`. They are ordinary C++ methods
in `src/LaserCommandMethods.cpp`, with no assembly or byte patching:

| Native leaf | Address | Bytes | Store |
| --- | ---: | ---: | --- |
| `Laser::set_handle` | `0x0049C500` | 25 | `+0x8C` |
| `Laser::set_parameter_vector_704` | `0x0049C800` | 40 | three Vector3 words at `+0x704` |
| `Laser::set_angle` | `0x0049C8C0` | 26 | `+0x70` |
| `Laser::set_parameter_field_714` | `0x0049C8E0` | 29 | `+0x714` |
| `Laser::set_field_7c` | `0x0049C900` | 26 | `+0x7C` |
| `Laser::set_speed` | `0x0049CB10` | 26 | `+0x78` |

All **172/172 bytes** strictly replay against the locked PE with zero
relocations, in **6/6 units from one cold COFF object**. The vector and `+0x714`
setters use direct typed C++ assignments and reproduce their original native
bodies exactly; the scalar setters likewise replay byte-for-byte.
See also the [six-setter exactness frontier](LASER_MUTATION_SETTER_LEAVES_EXACT.md)
for the per-function match-unit IDs and replay receipt.

## Root-host regression coverage

The production root host executes the real mutation helper with actual
`LaserController::find_laser` list lookup and verifies:

- 705 Context capture before handle read, X/Y operand order, three-word
  `+0x704` update, miss still consuming both floats, and second-float exception
  before mutation;
- 706/707/708/709 updates to `+0x7C/+0x78/+0x70/+0x714`, and the shared
  missing-handle/float-exception guard behavior;
- 710 virtual erase arguments `(0,0)`, original handle still visible during
  erase, subsequent handle clear, and missing-handle no-op.

The independent verifier
[`verify-enemy-laser-mutation-opcodes-source.py`](../scripts/verify-enemy-laser-mutation-opcodes-source.py)
pins all six original inline branches, the six strict-exact setter leaves,
the production helper's 20 ordered COFF relocations, and the indirect
slot-`0x44` call. The maintained root suite runs **128 focused host source
units** under ASan/UBSan and compiles **62 locked-profile i386 COFF units**.
No full cold replay was run.

The shared `LaserController::find_laser` leaf and all seven Enemy caller
fragments 704–710 now have natural source and focused runtime coverage. The
complete 41,967-byte `EnemyState::execute_opcode()` parent remains
**NONEXACT**; no parent-byte credit is claimed.
