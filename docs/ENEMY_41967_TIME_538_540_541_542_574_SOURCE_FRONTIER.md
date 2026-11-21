# CORE/RECON-1201 — Enemy timer, mode flags and runtime-time opcodes

The partial Enemy opcode root now routes five more original cases through
`src/EnemyStateTimeOpcode.cpp`:

`538, 540, 541, 542, 574`.

They are bounded inline branches of the 41,967B `EnemyState::execute_opcode`
parent, not standalone functions. The parent remains incomplete/NONEXACT and
receives no exact-byte or match-unit credit.

## Original native case boundaries

The original selector bytes at `0x004966B8 + (opcode - 300)` and absolute case
pointers in the table at `0x00496400` were decoded from the locked PE. The
verifier rechecks each selector, pointer, extent, final instruction boundary
and ordered direct E8 call target.

| Opcode | Original case | Bytes | x86 heads | Direct E8 targets in order |
| ---: | ---: | ---: | ---: | --- |
| 538 | `0x00494483` | 68 | 14 | `0x004AB080` |
| 540 | `0x004957BC` | 164 | 33 | `0x004AB080`, `0x004AB080` |
| 541 | `0x004958A2` | 33 | 9 | `0x004AAFB0`, `0x004292A0` |
| 542 | `0x0049598E` | 268 | 53 | `0x004AB080` × 4, `0x004640A0` × 3, `0x0049CC30` |
| 574 | `0x004963A2` | 61 | 14 | `0x0049CC30` |

Combined scope: **594 native bytes, 123 x86 heads and 14 direct E8 calls**.

## Recovered semantics

- **538** reads integer operand 0 and replaces only bit 11 of `flags.word_04`
  with the operand's low bit.
- **540** reads integer operands 0 then 1. It replaces only bit 12 of
  `flags.word_04`, stores operand 1 in `field_54`, copies `field_28` to
  `field_58`, clears bit 13 of `flags.word_04`, and clears bit 0 of
  `flags.word_00`. The write order is preserved.
- **541** reads float operand 0 and calls the actual global
  `default_timer_clock.set(value)`; it does not create a private clock or
  mutate any Enemy Timer directly.
- **542** reads all four integer operands in order before mode selection. It
  then calls the real `Session::mode()` separately for each conditional
  decision (up to three calls), chooses operand 0/1/2/3 for modes 0/1/2/other,
  and invokes the actual inherited `EclManager::subtract_time` on the live
  Enemy receiver. It subtracts from the current runtime's time, not from the
  EnemyState timers or health.
- **574** checks `flags.word_08` bit 6 first. If clear, it invokes the same
  current-runtime subtraction boundary with the native binary32 `1.0f`; if
  set, it performs no subtraction.

## Focused runtime evidence

The verifier compiles the new source as locked MSVC-compatible i386 COFF and
checks all five original CFG maps. Its ASan/UBSan host scenario verifies the
538/540 bit preservation and field writes, the actual `ClockScalar` setter,
all four 542 Session modes against the real current-runtime `time` field, and
both 574 flag branches. It links the actual `Session::mode`,
`ClockScalar::set` and `EclManager::subtract_time` implementations; there is
no fake time accumulator or synthetic clock owner.

Run:

```bash
scripts/repo-python scripts/verify-enemy-state-dispatch-frontier.py
```
