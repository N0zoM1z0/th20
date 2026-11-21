# CORE/RECON-1199 — indexed ECL parameter copy cases 529 / 530 / 570 / 571

The partial natural-C++ `EnemyState::execute_opcode()` root now routes four
indexed parameter-copy cases through `src/EnemyStateDynamicParameterOpcode.cpp`.
They use the actual `EnemyState`/`Enemy`/`EclRuntime` source and destination
forwarding methods; no fake register file, copied packet, or synthetic helper
boundary is introduced.

These are inline cases, not standalone native functions. The original 41,967B
parent remains incomplete and NONEXACT, with no parent byte credit or new
function match unit.

## Original dispatch and bounded CFG evidence

The original selector bytes and 174-entry absolute case pointers are decoded
from the locked PE's 704-byte selector at `0x004966B8` and pointer table at
`0x00496400`. Each bounded body ends at the next distinct original case head.

| Opcode | Selector | Original case | Bytes | x86 heads | Direct E8 targets in order |
| ---: | ---: | ---: | ---: | ---: | --- |
| 529 | 78 | `0x00491F46` | 212 | 47 | `0x004AB080`, `0x004AA9E0` × 4 |
| 530 | 79 | `0x0049201A` | 231 | 47 | `0x004AAFB0`, `0x004AA980` × 4 |
| 570 | 115 | `0x00492101` | 392 | 87 | `0x004AB080`, `0x004AA9E0` × 8 |
| 571 | 116 | `0x00492289` | 427 | 87 | `0x004AAFB0`, `0x004AA980` × 8 |

Combined scope: **1,262 original bytes, 268 x86 instruction heads and 48
ordered direct E8 calls**. The focused verifier checks all four selector bytes,
case pointers, extents, instruction boundaries and full ordered call maps.

## Recovered source behavior

- **529** copies one of integer operands 1–4 to the writable integer
  destination encoded by operand 0. `state.field_50` selects the source
  operand; values 0, 1, 2 select operands 1, 2, 3, and value 3/default selects
  operand 4.
- **530** is the corresponding float copy, with the same four-way selection.
- **570** is the eight-way integer copy. `field_50` values 0–6 select operands
  1–7 and 7/default selects operand 8.
- **571** is the corresponding eight-way float copy.

Every branch retains its own source read followed by its own destination
resolution/write. The destination is not cached across branches or replaced
with a direct field assignment: operand 0's ECL reference bit and negative
manager-variable encoding are passed through the existing
`EnemyState::integer_argument_destination` / `float_argument_destination`
forwarding boundary to the real `Enemy::integer_destination` /
`float_destination` mappings.

## Focused verification

```bash
scripts/repo-python scripts/verify-enemy-state-dispatch-frontier.py
```

The ASan/UBSan host test supplies live ECL packets with operand 0 marked as a
reference and mapped to the actual `EnemyCounters::field_00` integer and
`field_10` float destinations. It exercises all four selector values for 529
and 530, and all eight selector values for 570 and 571, verifying that each
branch writes the correct selected source value. The same verifier checks the
original four CFG/E8 maps and compiles the dynamic-parameter source as locked
MSVC-compatible i386 COFF.
