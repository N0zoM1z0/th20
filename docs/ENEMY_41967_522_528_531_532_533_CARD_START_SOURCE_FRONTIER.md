# CORE/RECON-1158 — Enemy shared Card Spell Start opcode family

The maintained source now contains `execute_enemy_card_start_opcode(EnemyState&, const EclInstruction&, opcode)` in `src/EnemyStateCardStartOpcode.cpp` for original Enemy opcodes **522, 528, 531, 532 and 533**. These five values share one original primary branch in the 41,967-byte Enemy dispatcher.

## Original native branch

The locked TH20 1.00a Steamless PE branch is `0x00494170..0x00494398`: **552 bytes / 114 x86 instructions / 13 direct E8 calls**, SHA-256 `0d723e73cdf35e9ae046f705434487b327ddf426ac2a9f9847b27916239d0307`. It terminates with the original jump to the common dispatcher epilogue at `0x004963DF`; the next primary branch begins at `0x00494398`.

The complete original direct-call map is checked by `scripts/verify-enemy-card-start-opcode-source.py`, including the real memset, three EnemyState integer reads, three separate Session mode reads, Context Card getter, 1,896B Card::start_spell, two EnemyHealth setters, shared health getter and Timer integer assignment.

## Natural-C++ source behavior

1. Accept only the five original opcodes. The shared branch is not split into five invented standalone native functions.
2. Read the fourth raw instruction word at `instruction+0x1C` as the encoded string length, and borrow the payload at `instruction+0x20`. This is not a VM operand read and the payload is not copied into `std::string`.
3. Construct the original zeroed 128-byte local and decode each byte using the rolling XOR key (`0x77`, initial step `7`, step increment `0x10`). The source intentionally adds no new length clamp; the native loop consumes the raw packet length.
4. Read integer operand 0, then re-read the actual `instruction.opcode`. Only opcodes 531/532/533 call `Session::mode`, separately, to apply `+mode`, `+mode-1`, or `+mode-2`. Opcodes 522/528 leave the index unchanged.
5. Cache the live `Context::card()` owner before reading integer operands 2 and 1, in that order. Call the real `Card::start_spell(index, decoded, duration, arg_3)`.
6. After Spell start, set EnemyHealth scaled mode to 1, read current health, copy it to scaled health, then assign zero to `timer_a8`.

The source retains the original owner boundaries and ordering; it does not substitute a synthetic Card service or combine the three Session mode calls into a cached value.

## Newly closed leaf boundaries

Focused cold replay of only the affected existing providers established:

- `Session.cpp`: **25/25 units exact**, including the 25B Session mode wrapper.
- `EnemyHealth.cpp`: **8/8 units exact**, including the 23B scaled-health and 36B scaled-mode setters.
- `Timer.cpp`: **21/21 units exact**, including the 26B integer assignment wrapper.
- `FunctionChain.cpp`: **14/14 units exact**, including the 17B `FunctionChainNode::shutdown_callback_value` getter. Its complete bytes are identical to the original `Context::card()` getter body used by this branch.
- `Identifier32.cpp`: **3/3 units exact**, including the 16B `Identifier32::get` body. Its complete bytes are identical to the original `EnemyHealth::get_health()` getter body used by this branch.

The 17B/16B getter identities are shared code-body aliases, not additional byte credit. `Context::card()` and `EnemyHealth::get_health()` are independently checked against those original bytes in the focused verifier.

## Remaining large dependency and parent boundary

The caller now has natural-C++ source and the owner/leaf paths are exact. The called `Card::start_spell` body at `0x00487C30` remains a separate **1,896B NONEXACT** Boss: the current source candidate is still short of the original and has unresolved callable/PMR lifetime contributions. No exactness is inferred for that callee or for the 41,967B Enemy parent.

`src/EnemyStateCardStartOpcode.cpp` compiles as i386 COFF. The focused verifier extracts the full 552B branch directly from the locked PE, checks all 114 instruction heads and 13 E8 site/target pairs, checks the natural-C++ operand/owner order, and byte-compares the typed getter/setter leaves. Only the affected Context, Session, EnemyHealth, Timer, FunctionChain and Identifier32 source providers were cold-built; no full cold replay was performed.
