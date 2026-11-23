# StageResource instruction-stream selector — whole 133-byte strict exact

**CORE/RECON-1269.** The locked target is the Japanese TH20 1.00a Steamless
PE32 (`resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`).

The native function at **0x004773C0** is a 133-byte `__thiscall` taking one
signed 32-bit identifier. Its sole direct call is the existing
`Timer::operator=(int)` at **0x00423520**. The natural C++ implementation in
`src/StageResourceRecordSelection.cpp` strictly replays **133/133 bytes**,
including the original REL32 call field. No assembly, padding or synthetic
instruction sequence is used.

## Native instruction protocol

The native function loads a variable-length instruction stream from the
Background instruction pointer at +`0x3330`. Each instruction prefix is 12 bytes:

| Offset | Native access | Maintained view |
| ---: | --- | --- |
| `+0x00` | signed 32-bit value; negative terminates | `time` |
| `+0x04` | signed 16-bit opcode, compared with `0x10` | `opcode` |
| `+0x06` | signed 16-bit byte size | `size` |
| `+0x08` | 32-bit identifier | `arguments[0]` |

Nonmatching instructions advance by the signed instruction size, not by the
12-byte prefix size. The scan stops at the first instruction with a negative
time word. A matching instruction must have opcode `0x10` and the requested
first argument.

On a match, the function writes the byte offset from the stream base to the
ScriptState `instruction_offset` at process owner +`0x20`, then assigns the
instruction's time word to the ScriptState Timer at process owner +`0x10`
through the existing Timer assignment wrapper. If the negative sentinel is
reached without a match, the previous instruction offset and Timer remain
unchanged.

The one-element `arguments[1]` source view is deliberate: the native
compiler's zero-indexed array address calculation is present in the original
133-byte body. This preserves the real source-level C++ code-generation shape;
it is not a claim that the original private declaration used this exact type
spelling.

## Enclosing ScriptState / Background layout

The instruction stream is consumed by the original 8,572-byte interpreter at
`0x004751B0`. Its receiver is the 0x3310-byte ScriptState subobject at
Background+`0x10`. The maintained `StageBackgroundScriptState` view now pins
its independently observed members, including Timer at +`0x00`, instruction
offset at +`0x10`, camera-motion timers, three Vector interpolations, Fog and
FOV interpolations, the 0x16C-byte camera at +`0x204`, Background back-pointer
at +`0x370`, eight 0x5E4-byte Animation objects at +`0x374`, the 17-word state
block at +`0x3294`, and mesh state through +`0x330F`. Its full size is
**0x3310**.

The enclosing neutral `StageResourceOwner` view now covers the complete
0x336C-byte Background object: ScriptState +`0x10`, instruction pointer
+`0x3330`, AnimationFile pointer +`0x3334`, rendered counters +`0x3338`,
state flags +`0x3344`, fade Timer +`0x3348`, stage/frame fields +`0x3358` /
+`0x335C`, original data +`0x3360`, data size +`0x3364`, and additional draw
owner +`0x3368`. This is a layout reconstruction, not a claim that the game's
original class or member identifiers have been recovered.

## Opcode integration and tests

Enemy opcode 622 reads integer operand 0 before dereferencing the process
StageResource owner, then calls this complete leaf. The root host covers:

- skipping a nonmatching instruction using its signed instruction size;
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
instruction pointer at +`0x3330`, the native ScriptState Timer/cursor writes, and the call
from Enemy opcode 622. The native owner layout is now represented as a complete `0x336c`-byte
`StageResourceOwner`, with a `0x3310`-byte `StageBackgroundScriptState` at
`+0x10`. The first eight bytes of the instruction header and the ScriptState
Timer/cursor offsets are independently used by both the selector and the
8,572-byte instruction interpreter at `0x004751B0`. The original class tag,
source spelling, and whether this physical function was authored game code,
compiler output or a shared helper are not established. `config/function-origins.csv` therefore
keeps origin **unknown**, subsystem `StageResource`, disposition `review`, and
confidence `unknown`. The exact C++ replay is not treated as authored-game
byte credit.
