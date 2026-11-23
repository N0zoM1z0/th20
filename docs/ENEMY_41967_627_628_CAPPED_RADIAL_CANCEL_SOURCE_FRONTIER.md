# Enemy ECL opcodes 627/628 — capped Bullet and Laser radial cancellation

## Status and boundary

Native opcodes **627** and **628** are two adjacent inline cases that compose
the original capped Bullet radial-cancellation Boss and the Laser radial
cancellation Boss. Each is **182 bytes / 39 x86 instructions / 7 direct E8
calls**:

| Opcode | Selector index | Native extent | SHA-256 |
| --- | ---: | --- | --- |
| 627 | 145 | 0x00495580..0x00495636 | d96ea10c41ab59bb9c8ac91d7300ca628e526129df3fa781f2d655755f4c91e3 |
| 628 | 146 | 0x00495636..0x004956EC | 856fa32d1333be48c1b329ae6fc5e18aa4e0a36272ac575dcecbcc1dcb669080 |

Both native maps are pinned by the focused PE verifier, including each
selector pointer, exact extent, instruction count, SHA-256 and ordered call
sites/targets. The branches have the same gameplay argument contract; their
different register/stack code is preserved as separate native cases.

## Real leaf Bosses and native arguments

Each case reads float radius operand 0, resolves the live Context
BulletController, obtains the EnemyState position reference, and calls the
complete **401-byte** BulletController::cancel_near_limited Boss at
0x0047CF60. The native arguments are:

- mode 0;
- maximum cancellation count 0x1869f (**99,999**);
- effect bits 0.

The branch then re-reads the live Context for its LaserController, re-reads
the EnemyState position reference, and calls the complete **288-byte**
LaserController::cancel_near Boss at 0x004CAAD0 with mode 0 and argument
1.

The 401-byte capped Bullet Boss is already independently strict-exact in
src/BulletLimitedCancellation.cpp; the 288-byte Laser Boss is maintained
in src/LaserCancelNear.cpp. The new case source reuses those real functions.
It does not substitute the 320-byte uncapped Bullet cancel_near Boss used
by opcode 616.

## Natural C++ and live-owner semantics

execute_enemy_bullet_laser_cancel_opcode now handles 616, 627 and 628.
Opcode 616 keeps its uncapped Bullet path; 627/628 route through
cancel_near_limited(center, radius, 0, 0x1869f, 0). All three branches keep
the position argument as a live reference, cache the BulletController for
the in-flight Bullet traversal, and resolve Context/position again for the
following Laser phase.

## Root-host regression coverage

The maintained ASan/UBSan root host executes both opcodes through the actual
dispatcher and production helper. It uses the real 401-byte Bullet Boss,
real intrusive active-list traversal, real 288-byte Laser Boss and real
Context getters. Bullet::cancel and concrete Laser::cancel_circle remain
explicit capture boundaries.

The tests cover:

- Bullet states 1/2 versus excluded state 3;
- nonzero Bullet field_18 exclusion;
- native effect-mode field reset to zero and Bullet cancel mode zero;
- two eligible Bullets at the original and callback-retargeted live center;
- Context retargeting before Bullet traversal and re-resolution before Laser;
- Laser state-1 filtering, mode 0 / argument 1, and live center publication;
- radius operand exception before either Context/controller lookup or
  cancellation side effects.

The native verifier independently checks the 99,999 / effect / mode immediates
in both PE branches. The locked-profile COFF helper check preserves the
ordered float, Context, position, capped/uncapped Bullet, Context, position
and Laser calls. The maintained root verifier compiles 50 locked-profile
i386 COFF source units and runs 114 focused host source units under
ASan/UBSan.

The original 41,967-byte EnemyState::execute_opcode parent remains
**NONEXACT**; these are inline fragments, not standalone function units or
whole-parent byte credit. No full cold replay was run.
