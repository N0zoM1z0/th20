# CORE/RECON-1203 — Sound and dialogue-gate opcode callers

Two original inline cases now route through
`src/EnemyStateFrontendOpcode.cpp`: opcodes **516** and **519**. They are
bounded caller fragments in the incomplete 41,967B Enemy root, not standalone
native functions; the parent remains NONEXACT and receives no exact-byte
credit or new match unit.

## Original native CFGs

The immutable PE selector byte at `0x004966B8 + (opcode - 300)` and absolute
pointer in the table at `0x00496400` were decoded directly. The verifier
checks the exact selector, pointer, case extent, instruction boundary and
ordered direct E8 calls.

| Opcode | Original case | Bytes | x86 heads | Direct E8 targets in order |
| ---: | ---: | ---: | ---: | --- |
| 516 | `0x00493F3F` | 79 | 17 | `0x00499350`, `0x004AB080`, `0x00426EB0` |
| 519 | `0x0049407F` | 43 | 11 | `0x00478160`, `0x00499110` |

Combined scope: **122 native bytes, 28 x86 heads and five direct E8 calls**.

## Restored semantics

- **516** first resolves and caches `EnemyState::position_ref().x`, then reads
  integer operand 0, and finally calls the real global
  `process_sound.request_effect_at(id, x)`. The original 52B
  `SoundInf::request_effect_at` leaf performs the native coordinate-to-pan
  conversion and delegates to the existing SoundInf request manager. The
  operand read is not moved before the position lookup.
- **519** calls `current_front->has_dialogue()` first. Only if that returns
  nonzero does it call `current_front->dialogue_ready()`. It returns **-1**
  when a dialogue exists but is not ready; otherwise it returns zero. The
  root propagates this special return instead of normalizing it.

Both ECL argument/position and FrontInf methods already have separately
reconstructed source and native evidence. No physical leaf bytes are
re-credited here.

## Focused runtime evidence

The focused verifier checks both original CFG maps and compiles the new
fragment as locked MSVC-compatible i386 COFF. Its ASan/UBSan live-packet test
verifies that opcode 516 forwards the cached X coordinate and sound ID, and
that opcode 519 short-circuits the ready query when no dialogue exists,
returns -1 for an existing unready dialogue, and returns zero when ready.

The fixture stubs the already separately reconstructed
`SoundInf::request_effect_at` and `FrontInf::has_dialogue` /
`FrontInf::dialogue_ready` leaves to capture arguments and ready-state
outcomes. The maintained production fragment calls those real owner methods;
no new sound queue or dialogue owner is fabricated.

Run:

```bash
scripts/repo-python scripts/verify-enemy-state-dispatch-frontier.py
```
