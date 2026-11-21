# CORE/RECON-1150 — natural-C++ source for Enemy ECL opcode 632 borrowed script pointer

The maintained source now contains `execute_enemy_script_pointer_opcode(EnemyState&, const EclInstruction&, opcode)` in `src/EnemyStateScriptPointerOpcode.cpp` for original opcode 632. This is an inline case fragment inside the **41,967-byte** Enemy ECL dispatcher, not a standalone original function.

## Original native case evidence

The locked TH20 1.00a Steamless PE audit `.analysis/core208-native-632-audit.json` confirms the original case interval `0x00493831..0x0049392D`: **252 bytes / 62 x86 instructions / 10 direct E8 calls**, SHA-256 `45cdbd018eea322e53dcffa4af1834acceeb26b2f9ba2aa72d6a17d41535f277`.

The original case calls `integer_argument(0)` and then `integer_argument(1)` before the writable queued metadata selector. It then ensures `index+1` real PMR BulletCommand entries and accesses the actual 44-byte element. The final original instruction sequence computes `4*3`, adds the live `EclInstruction* + 0x10`, and stores the resulting pointer at `BulletCommand::script` (`+0x28`).

## Restored borrowed-pointer semantics

The source accepts the parent's live `const EclInstruction&`; it does not call `current_instruction()` or invent another VM lookup. The stored value is exactly:

`reinterpret_cast<const char*>(&instruction) + 0x1c`

This points to the fourth 32-bit word of the trailing ECL payload. It is a borrowed pointer into the active packet, not a `std::string`, not a copy, and not `float_argument(3)`. The source reads both integer indexes before invoking `writable_shot`, performs unsigned `index+1` vector growth if necessary, and stores the pointer without changing any other command fields or the metadata cursor.

The pointer's lifetime remains owned by the live ECL packet. It must not be dereferenced after the packet expires; subsequent opcodes such as 609–612 may update other fields while preserving this script pointer, and another 632 can retarget it.

## Scoped verification and exactness boundary

`src/EnemyStateScriptPointerOpcode.cpp` compiles as i386 COFF under the pinned MSVC profile. `scripts/verify-enemy-script-pointer-opcode-source.py` checks the immutable original branch hash, 252B/62-instruction/10-E8 counts, original call-target multiset, both VM operand reads before COW, vector size/resize order and exact borrowed packet pointer expression.

This is a source fragment, not a separate native function. No `config/functions.csv` mapping or parent byte credit is added. The 41,967B Enemy root now has a partial C++ entry (CORE/RECON-1196); remaining inline cases and whole-root equivalence are still NONEXACT. No full cold replay was performed.
