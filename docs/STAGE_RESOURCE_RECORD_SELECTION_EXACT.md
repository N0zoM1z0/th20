# StageResource variable-record selector — whole 133-byte strict exact

**CORE/RECON-1269.** The locked target is the Japanese TH20 1.00a Steamless
PE32 (`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`).

The native function at **0x004773C0** is a 133-byte `__thiscall` taking one
signed 32-bit identifier. Its sole direct call is the existing
`Timer::operator=(int)` at **0x00423520**. The natural C++ implementation in
`src/StageResourceRecordSelection.cpp` strictly replays **133/133 bytes**,
including the original REL32 call field. No assembly, padding or synthetic
instruction sequence is used.

## Native record protocol

The native function loads a variable-length record stream from process
StageResource owner +`0x3330`. Each record prefix is 12 bytes:

| Offset | Native access | Maintained view |
| ---: | --- | --- |
| `+0x00` | signed 32-bit value; negative terminates | `timer_value` |
| `+0x04` | signed 16-bit kind, compared with `0x10` | `kind` |
| `+0x06` | signed 16-bit byte stride | `stride` |
| `+0x08` | 32-bit identifier | `identifier[0]` |

Nonmatching records advance by the signed stride, not by `sizeof(record)`.
The scan stops at the first record with a negative leading word. A matching
record must have kind `0x10` and the requested identifier.

On a match, the function writes the byte offset from the stream base to the
Background subobject's `+0x10` word (process owner +`0x20`), then assigns the
record's leading integer to the Background Timer at process owner +`0x10`
through the existing Timer assignment wrapper. If the negative sentinel is
reached without a match, both previously selected offset and Timer remain
unchanged.

The one-element `identifier[1]` source view is deliberate: the native
compiler's zero-indexed array address calculation is present in the original
133-byte body. This preserves the real source-level C++ code-generation shape;
it is not a claim that the original private declaration used this exact type
spelling.

## Opcode integration and tests

Enemy opcode 622 reads integer operand 0 before dereferencing the process
StageResource owner, then calls this complete leaf. The root host covers:

- skipping a nonmatching record using its signed stride;
- selecting a matching kind/identifier and updating the Timer through its real
  integer assignment protocol;
- reaching a negative sentinel with no match while preserving prior state;
- throwing during operand evaluation before touching the process owner.

The adjacent Enemy opcode cluster is also wired into the maintained root:

- 623 captures `Context::enemy_controller()` before reading the integer
  operand, then calls the real `EnemyController::set_field_84_bit_0` leaf;
- 624 and 631 read the three-entry member callback table at `0x0056FE8C`,
  install the selected callback at `EnemyState+0x2E0`, and set `+0x2D8` to 0/1;
- 625 and 626 read the two overlapping all-zero table views rooted at
  `0x0056FE98` and `0x0056FE9C`, writing distinct state words `+0x2DC` and
  `+0x2E4`.

The focused verifier pins selectors 140–144 and 149, all six native case
extents (337 bytes / 64 instruction heads / 9 ordered E8 calls), the 133-byte
leaf's native SHA-256/call map, the strict exact unit, and the ASan/UBSan root
host behavior. The enclosing **41,967-byte** `EnemyState::execute_opcode`
remains NONEXACT; the inline cases receive no separate whole-function byte
credit.

## Origin boundary

The StageResource subsystem association is supported by the process owner
record pointer at +`0x3330`, the native Timer/selection writes, and the call
from Enemy opcode 622. The original class tag, original source spelling, and
whether this physical function was authored game code, compiler output or a
shared helper are not established. `config/function-origins.csv` therefore
keeps origin **unknown**, subsystem `StageResource`, disposition `review`, and
confidence `unknown`. The exact C++ replay is not treated as authored-game
byte credit.
