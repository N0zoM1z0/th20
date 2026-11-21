# CORE/RECON-1202 — Card spell and scaled-health opcode callers

Five original Enemy inline cases now route through
`src/EnemyStateCardOpcode.cpp`:

`523, 536, 537, 561, 562`.

They are bounded caller branches in the incomplete 41,967B Enemy root, not
standalone native functions. The parent remains NONEXACT and receives no new
match unit or byte credit.

## Original case CFGs

The selector bytes and absolute pointers were re-decoded from the locked PE
selector at `0x004966B8` and pointer table at `0x00496400`. The focused verifier
checks the selector, pointer, case extent, instruction boundary and direct E8
calls in original order.

| Opcode | Original case | Bytes | x86 heads | Direct E8 targets in order |
| ---: | ---: | ---: | ---: | --- |
| 523 | `0x004943C9` | 60 | 13 | `0x00411700`, `0x004878B0`, `0x0049C360` |
| 536 | `0x00494405` | 30 | 7 | `0x00411700`, `0x00497450` |
| 537 | `0x00494423` | 30 | 7 | `0x00411700`, `0x00497420` |
| 561 | `0x00494441` | 66 | 14 | `0x00411700`, `0x004AB080`, `0x0049CA10` |
| 562 | `0x00494398` | 49 | 11 | `0x004AB080`, `0x0049C360` |

Combined scope: **235 native bytes, 52 x86 heads and 11 direct E8 calls**.

## Restored caller behavior

- **523** obtains the actual Card from the current Context, calls the complete
  602B `Card::finish_spell()` leaf, then disables scaled-health mode through
  the actual `EnemyHealth::set_scaled_enabled(0)` leaf. The order is retained.
- **536** calls the real Card `request_flag_3()` setter.
- **537** calls the real Card `request_flag_4()` setter. That leaf sets bit 4
  before retiring its effect handle, including when the handle is zero.
- **561** caches the Card receiver before evaluating integer operand 0, then
  calls `Card::set_flag_8(value)`; only the low bit of the input replaces Card
  bit 8.
- **562** caches the `EnemyHealth` receiver before reading integer operand
  0, then calls `set_scaled_enabled(value)`, replacing only the scaled-mode
  bit with the low input bit.

The Context card getter at `0x00411700` is physically folded with the existing
17B `FunctionChainNode::shutdown_callback_value` getter. The 602B finish leaf,
Card request setters and EnemyHealth scaled-mode setter already have their own
source/match evidence; this caller adds no duplicate leaf credit.

## Focused runtime evidence

The focused verifier compiles the new fragment as locked MSVC-compatible
i386 COFF and rechecks all five original case maps. Its ASan/UBSan live-packet
host scenario uses the real Context/Card owner, real `Card::request_flag_3`,
`Card::request_flag_4`, `Card::set_flag_8`, and real
`EnemyHealth::set_scaled_enabled` implementations. It verifies flag-bit
preservation, the opcode-523 finish-before-health order, and the low-bit
semantics for 561/562.

Only two already independent leaves are fixture boundaries in this focused
host test: the separately exact 602B `Card::finish_spell()` is stubbed to
record its call (its UI/achievement/resource collaborators are outside this
caller test), and `AnimationHandle::retire()` is stubbed for Card's request-4
zero-handle boundary. The caller still uses natural C++ and the actual owner
methods; no assembly or synthetic byte sequences are used.

Run:

```bash
scripts/repo-python scripts/verify-enemy-state-dispatch-frontier.py
```
