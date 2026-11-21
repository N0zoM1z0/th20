# CORE/RECON-1198 — Enemy bounds, health, controller and state opcode cases

The partial natural-C++ `EnemyState::execute_opcode()` root now routes 18 more
original inline cases through `src/EnemyStateControlOpcode.cpp`:

`500, 501, 504, 505, 511, 512, 513, 515, 526, 535, 543, 544, 546, 547, 557, 558, 559, 566`.

They are not standalone native functions. The original 41,967B parent remains
incomplete and NONEXACT, with no parent byte credit or new function match unit.

## Immutable original case boundaries

Each selector byte and absolute case pointer was re-read from the locked PE's
704-byte selector at `0x004966B8` and 174-entry pointer table at `0x00496400`.
Case extents below end at the next original table target; all direct E8 targets
are checked in order by `scripts/verify-enemy-state-dispatch-frontier.py`.

| Opcode | Original case | Bytes | x86 heads | Direct E8 targets in order |
| ---: | ---: | ---: | ---: | --- |
| 500 | `0x00490B7B` | 140 | 28 | `0x004AAFB0`, `0x004AAFB0`, `0x0041CAF0`, `0x00497CC0` |
| 501 | `0x00490C07` | 49 | 11 | `0x004AAFB0`, `0x004AAFB0` |
| 504 | `0x004908D4` | 132 | 26 | `0x004AAFB0` × 4 |
| 505 | `0x00490958` | 32 | 6 | none |
| 511 | `0x00491BF6` | 239 | 49 | `0x004AB080`, `0x0045D650`, `0x0040C300`, `0x00411570`, `0x0040C300`, `0x0049C4E0`, `0x0040C300`, `0x0049C340` |
| 512 | `0x00491D39` | 295 | 60 | `0x004AB080`, `0x00412730`, `0x0049C4B0`, `0x00412730`, `0x0049C2E0`, `0x00412730`, `0x0049C2E0` |
| 513 | `0x00493B5B` | 25 | 6 | `0x00423520` |
| 515 | `0x00491E60` | 37 | 9 | `0x004AB080`, `0x00423520` |
| 526 | `0x00490978` | 72 | 12 | `0x004AAFB0` |
| 535 | `0x00491E85` | 37 | 9 | `0x004AB080`, `0x00423520` |
| 543 | `0x00495D20` | 68 | 14 | `0x004AB080` |
| 544 | `0x00495D64` | 27 | 6 | `0x004AB080` |
| 546 | `0x0048C211` | 27 | 6 | `0x004AB080` |
| 547 | `0x0048C22C` | 30 | 6 | `0x004AB080` |
| 557 | `0x00490D90` | 67 | 14 | `0x004AB080` |
| 558 | `0x00490DD3` | 27 | 6 | `0x004AAFB0` |
| 559 | `0x00490DEE` | 27 | 6 | `0x004AAFB0` |
| 566 | `0x00491CE5` | 84 | 18 | `0x004AB080`, `0x0045D650`, `0x0040C300`, `0x0049C340` |

Combined scope: **1,415 original bytes, 292 x86 heads and 42 direct E8 calls**.
The case heads are non-contiguous in the original boss; these figures describe
bounded inline CFGs, not a new parent or function extent.

## Recovered source behavior

- **500 / 501** write the two native bounds pairs in operand order. Opcode 500
  also performs the one-time `field_284` transition and increments the live
  Context `PlayerRecord::field_dc` through the existing 87B `add_field_dc` leaf.
- **504 / 505** set or clear only bit 1 of `flags.word_04`. Opcode 504 performs
  the flag update before reading its four float operands into `bounds_178`.
- **511** writes health, initial health, phase health, conditionally propagates
  the original bit-7 state into bit 14, then writes scaled health. The separate
  getter calls are retained instead of caching a value across native E8 sites.
- **566** writes health and scaled health only; it does not overwrite initial
  or phase health.
- **512** clears the controller's `field_84` bit first. It then either clears
  the previously selected handle and bit 7, or sets bit 7, publishes the live
  Enemy through `EnemyController::set_selected`, and stores the new index.
  Repeated Context getter calls and the negative-index branch are preserved.
- **513 / 515 / 535** use the real Timer assignment paths for `timer_a8`,
  `timer_288` and `timer_298`.
- **526** stores the supplied float and then squares the stored field.
- **543 / 557** replace only bits 15 / 12 with the low bit of the integer
  operand. **544 / 546 / 547** update the corresponding integer state fields.
  **558 / 559** store their float operands directly.

The health methods reuse existing folded physical leaves: `0x45D650` is the
24B first-word store also used by `PackedColor`, `0x40C300` is the 16B first-word
getter also used by `Identifier32`, `0x411570` and `0x49C4E0` are the folded
four-byte setters already seen in Pattern, and `0x49C340` is the existing
23B scaled-health setter. No duplicate function rows or byte credit are added.

The selection case uses the actual `Context`, `EnemyController`, `EnemyHandle`
and current `Enemy` identity. The focused host test constructs the real
`EnemyController`, calls the actual `set_field_84_bit_0` and `set_selected`
methods, verifies a positive selection stores the Enemy identifier, then
verifies a negative index clears the previously selected handle. It also tests
the real Context `PlayerRecord` path for opcode 500 and the health/timer/flag
mutations above.

## Focused verification

```bash
scripts/repo-python scripts/verify-enemy-state-dispatch-frontier.py
```

This verifies every original selector byte, pointer, bounded case extent and
ordered E8 target for all 18 cases; builds all four new C++ units as locked
MSVC-compatible i386 COFF; and runs the ASan/UBSan live-packet host test. The
whole 41,967B root remains NONEXACT and uncredited.
