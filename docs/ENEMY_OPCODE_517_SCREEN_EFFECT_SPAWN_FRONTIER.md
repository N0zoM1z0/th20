# Enemy ECL opcode 517 — ScreenInf creation fragment

Native jump-table case `0x43` (opcode 517) is restored as a small natural-C++
fragment in `src/EnemyStateScreenOpcode.cpp` and is wired through
`EnemyState::execute_opcode()`.

## Original case and operand order

- Selector index: `67`
- Native block: `0x00493F8E..0x00493FF1` (99 bytes, 25 instructions)
- Ordered native calls: `0x004AB080` three times, then `0x004250F0`
- Operand reads: integer argument 2, then 1, then 0
- Factory call: `screen_factory_4250f0(1, arg0, arg1, arg2, 0, 0, 0)`
- Return: the factory result is discarded and the opcode returns zero

The source uses three explicit locals so the native reverse operand-read order
is not hidden inside function-argument evaluation. The helper calls the actual
ScreenInf factory rather than constructing a stand-in owner.

## Existing callee reuse

`0x004250F0` is already the whole 81-byte `screen_factory_4250f0` C++ match,
including its original process allocator, diagnostic string, ScreenInf
initialization call and relocation destinations. Opcode 517 adds no duplicate
credit for that callee and is inline code within the 41,967-byte dispatcher, not
a separately accepted native function.

## Focused verification

`scripts/verify-enemy-state-dispatch-frontier.py` checks the locked PE selector
byte, jump-table pointer, 99-byte block boundary, all 25 instruction heads and
the ordered four-call map. Its ASan/UBSan root fixture dispatches opcode 517
with three distinct operands and verifies the factory receives mode 1, the
three operands in source order, and zero for the remaining factory arguments.
The helper and dispatcher are compiled as i386 COFF under the locked MSVC
profile. The parent dispatcher remains partial and NONEXACT.
