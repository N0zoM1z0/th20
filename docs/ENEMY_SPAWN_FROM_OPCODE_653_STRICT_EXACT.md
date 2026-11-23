# EnemyState::spawn_from_opcode — 653-byte strict exact Boss

**CORE/RECON-1263.** The original Enemy opcode-spawn member at
`0x00496FB0..0x0049723D` is now a whole-function natural-C++ strict exact
match in `src/EnemyStateSpawnOpcode.cpp`.

| Native property | Verified result |
| --- | ---: |
| Function extent | 653 bytes |
| Decoded x86 instructions | 192 |
| Ordered direct E8 calls | 17 |
| COFF relocation fields | 19 |
| Ordinary bytes after relocation masking | 577 / 577 exact |
| Relocation destinations | 19 / 19 exact |

The complete original code hash is
`b31b80d7b732b8a975d436510768c1a84e9da6c8aa5c16a83ebb78376ca43c39`.
The canonical i386 COFF unit is `enemy_state_spawn_from_opcode`; its pinned
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` replay reproduces the
entire 653-byte body and every original relocation target. No function prefix
comparison, padding, assembly, or byte blob is involved.

## The last 14 bytes: natural compiler scheduling, not an opcode shim

Both native float-default argument sites reserve their outgoing stack slot
before loading the operand:

- X default: `push ecx` at `+0x86`, followed by `movss` at `+0x87`;
- Y default: `push ecx` at `+0xA5`, followed by `movss` at `+0xA6`.

The previous source expressed the same lvalue directly, and the pinned MSVC
compiler scheduled the `movss` before the slot reservation at both sites. The
source now applies an explicit identity `static_cast<float>` in the
`SPAWN_FLOAT` expression. This remains an ordinary C++ value conversion with
no runtime operation; it guides the compiler to emit the native reservation /
load / store order at both call sites. The complete function then matches
without changing its ABI, call graph, control flow, or behavior.

## Reconstructed behavior

The capacity check is first: if the current Context's EnemyController count is
at least its capacity, the function returns without reading the current
instruction or any operands. Otherwise it reads the current ECL instruction,
uses operand zero's byte count to skip the padded script-name payload, and
resolves the two default position operands through the original
`float_argument_value` path.

The position rules are kept distinct:

- opcodes 300, 309, 321, 311 and 304 add the current Enemy's `motion_110` X/Y;
- opcodes 311, 304, 312 and 305 set `flags_18`;
- `EnemyState::flags.word_04` bit 3 negates X and toggles `flags_18`.

It then resolves health, `field_0c` and `field_10` through integer operand
indexes 3, 4 and 5, copies the complete EnemyCounters block, publishes the
source Enemy identity into `field_50`, and calls the live Context
EnemyController's existing `create` method. `flags.word_08` bit 2 determines
whether the source Enemy is passed as the parent.

The 41,967-byte dispatcher routes native case-zero opcodes 300/301/304/305/321
to this member. Native case six handles 309/310/311/312 through the exact
`EnemyController::selected(0)` leaf and enters this same spawn Boss only when
the selected slot is empty. The 41,967-byte dispatcher itself remains
NONEXACT and receives no parent byte credit.

## Ownership and accounting

All 19 relocation fields and all 577 ordinary bytes are verified against the
locked Japanese 1.00a PE. The original source-owner/origin record remains
unknown, so this is a strict exact function reconstruction but is deliberately
not added to authored-origin `matches.csv` byte credit. The existing 653-byte
function inventory row is promoted to `matching` / `100.00`, and its exact
replay unit is maintained in `config/match-units.toml`.

## Maintained runtime coverage

The ASan/UBSan Enemy root host executes all eight original opcode routes
(300, 301, 304, 305, 309, 311, 312 and 321) through
`EnemyState::execute_opcode()`. It checks the case-six selected-slot guard
(both occupied suppression and empty-slot creation), the capacity early return
with zero operand reads, float-before-integer operand order, relative versus
absolute position, mirrored X, per-opcode flag XOR, health and both integer
fields, copied counters, source identity, parent linkage, and exception-before
creation behavior. The real `EnemyController::create()` and production typed
Enemy allocator specialization are linked; only the later `Enemy::apply_spawn`
Boss is a capture boundary in this fixture. The maintained root verifier now
executes **129 focused host source units** under ASan/UBSan and compiles **62
locked-profile i386 COFF units**.
