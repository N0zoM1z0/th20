# CORE/RECON-1197 — EnemyPattern opcode cluster 506–510 / 556 / 567–568 / 572

The original 41,967B `EnemyState::execute_opcode()` at `0x0048C010` contains
nine independently routed EnemyPattern cases. They are now maintained as
natural C++ in `src/EnemyStatePatternOpcode.cpp` and called from the partial
whole-root entry `src/EnemyStateExecuteOpcode.cpp`.

This is an inline-case source fragment, not a separate original native
function. The 41,967B root remains incomplete and NONEXACT; no function match
unit or parent byte credit is created.

## Original primary heads and direct calls

The immutable PE selector byte at `0x004966B8 + (opcode - 300)` and the
corresponding absolute case pointer in the 174-entry table at `0x00496400`
were decoded directly. The bounded native CFGs terminate at the common parent
epilogue `0x004963DF`.

| Opcode | Original case | Bytes | x86 heads | Direct E8 targets in order |
| ---: | ---: | ---: | ---: | --- |
| 506 | `0x00491989` | 23 | 5 | `0x00497270` (`EnemyPattern::clear_counts`) |
| 507 | `0x004919A0` | 75 | 17 | `0x004AB080`, `0x004AB080`, `0x0049C7B0` (`set_count`) |
| 572 | `0x004919EB` | 48 | 11 | `0x004AB080`, `0x0049C4E0` (folded 22B `+0x08` setter) |
| 567 | `0x00491A1B` | 75 | 17 | `0x004AB080`, `0x004AB080`, `0x0049C780` (`set_extra_count`) |
| 568 | `0x00491A66` | 48 | 11 | `0x004AB080`, `0x0049C6F0` (`set_duration`) |
| 508 | `0x00491A96` | 101 | 21 | `0x004AAFB0`, `0x004AAFB0`, `0x0049C830` (`set_radii`) |
| 509 | `0x00491AFB` | 103 | 23 | `0x00488850`, `0x0049C0C0`, `0x00499350`, `0x0048BF10` (`drop`) |
| 556 | `0x00491B62` | 87 | 18 | `0x0049C0C0`, `0x00499350`, `0x0048BF10` (`drop`) |
| 510 | `0x00491BB9` | 61 | 13 | `0x004AB080`, `0x00411570` (`set_base_kind`) |

Combined scope: **621 original bytes, 136 x86 instruction heads and 23 direct E8 calls**. The focused verifier checks every original selector byte, pointer, case extent, instruction boundary and ordered E8 target.

## Restored C++ semantics

- **506** calls the real `EnemyPattern::clear_counts()`; it clears the count array, duration and Timer, but does not clear the extra-count array.
- **507 / 567** read integer operands 0 then 1 and call the existing unsigned `set_count` / `set_extra_count` leaf. The original kind-minus-one indexing and absence of an invented bounds check remain intact.
- **572** reads operand 0 and stores the bomb kind. Its 22B native setter at `0x0049C4E0` is physically folded with the existing `Cursor::set_count` leaf; the Enemy receiver is `EnemyState + 0x1A8`, and the native store is to pattern offset `+0x08`. No duplicate physical function row or exact-byte credit is introduced.
- **568** reads operand 0 and calls the real `set_duration`, including its Timer reset.
- **508** reads float operand 1 before operand 0, then calls `set_radii(x, y)` without normalizing or otherwise rewriting either float.
- **509** calls the real Session two-player predicate first. Only when it is false does it read the Enemy bomb-drop flag, obtain the current state position and call the existing exact `EnemyPattern::drop` protocol.
- **556** uses the same real drop path without the two-player guard.
- **510** reads operand 0 and calls the existing `EnemyPattern::set_base_kind` leaf.

The already accepted 239B `EnemyPattern::drop` and the existing Pattern setters are reused as real owners. Their code is not re-credited through this inline caller.

## Focused verification

Run:

```bash
scripts/repo-python scripts/verify-enemy-state-dispatch-frontier.py
```

The verifier checks the immutable whole-root hash, all nine original case
selector/pointer/extent/E8 maps, all 49 movement opcodes, and compiles the
movement, pattern and root translation units as locked MSVC-compatible i386
COFF. Its ASan/UBSan host scenario enters the actual partial root with live
ECL packets and exercises Pattern count clearing, raw and extra counts,
duration, bomb kind, radius operand order, base kind, Session-gated 509,
unconditional 556, drop origin/mark forwarding, movement and the special 560
same-tick return. Only the separately verified drop leaf is stubbed in this
focused host harness.
