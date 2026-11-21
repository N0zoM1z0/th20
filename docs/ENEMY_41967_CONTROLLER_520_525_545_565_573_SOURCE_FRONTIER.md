# CORE/RECON-1200 — EnemyController selection and clear opcode callers

The partial 41,967B EnemyState opcode root now routes five original inline
cases through `src/EnemyStateControllerManagementOpcode.cpp`:

`520, 525, 545, 565, 573`.

These are not standalone native functions. The parent remains incomplete and
NONEXACT, with no whole-root byte credit or new function match unit. The
important progress is that the original call boundaries now reach the real,
previously restored large `EnemyController` list-clear implementations.

## Original case CFGs

The original selector byte and absolute pointer were decoded from the locked
PE selector at `0x004966B8` and 174-entry pointer table at `0x00496400`. Each
bounded case ends at the next distinct table target. The verifier checks the
selector, pointer, extent, final instruction boundary and ordered E8 targets.

| Opcode | Original case | Bytes | x86 heads | Direct E8 targets in order |
| ---: | ---: | ---: | ---: | --- |
| 520 | `0x004940AA` | 133 | 30 | `0x00412730`, `0x00485660`, `0x00412730`, `0x00485660`, `0x00412730`, `0x00485660` |
| 525 | `0x00491EAA` | 30 | 7 | `0x00412730`, `0x004A4A20` |
| 545 | `0x00491EC8` | 66 | 14 | `0x00412730`, `0x004AB080`, `0x004A4810` |
| 565 | `0x00491F0A` | 30 | 7 | `0x00412730`, `0x004A4C20` |
| 573 | `0x00491F28` | 30 | 7 | `0x00412730`, `0x004A4E30` |

Combined scope: **289 native bytes, 65 x86 heads and 17 direct E8 calls**.

## Restored caller semantics and reused large leaves

- **520** asks the live Context's EnemyController for selected slots 0, 1 and
  2 in order. It returns **-1 immediately** on the first non-null selection;
  otherwise it returns zero. The root propagates this return instead of
  normalizing every handled opcode to zero.
- **525** gets the live EnemyController and calls the full native
  `EnemyController::clear()` implementation at `0x004A4A20` (501B).
- **545** caches the live EnemyController before reading integer operand 0,
  then calls the full `clear_matching(value)` implementation at `0x004A4810`
  (521B). This retains the native owner/operand evaluation order.
- **565** calls the distinct `clear_variant_565()` implementation at
  `0x004A4C20` (514B), which also clears the per-Enemy script subroutine field.
- **573** calls the distinct `clear_variant_573()` implementation at
  `0x004A4E30` (526B), which skips an Enemy whose state bit 30 is set.

These large clear bodies already have complete native/source ownership and
strict matching evidence under CORE/EXACT-152. This caller integration does
not duplicate their physical byte or match-unit credit.

## Focused host evidence

`scripts/verify-enemy-state-dispatch-frontier.py` compiles the new caller as
locked MSVC-compatible i386 COFF and checks all five original case CFGs and
ordered E8 targets. Its ASan/UBSan live-packet scenario exercises all three
selected slots and the -1 return, the no-selection zero return, then links a
real Enemy into the actual EnemyController intrusive list and runs the real
501B/521B/514B/526B clear methods through the dispatcher. It checks list-member
state reset, Pattern reset, vector reset, the 565 script-field reset, 573's
bit-30 skip and the controller Timer increments.

The fixture intentionally stubs only the external `Enemy::defeat`,
`AnimationHandle::retire`, and identifier-to-Enemy `find` boundary; the list
traversal, selection handle resolution, controller clear methods, Session and
Context owner access are real maintained C++.
