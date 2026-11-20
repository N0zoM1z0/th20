# ScreenInf 221B hold update — strict native reconstruction

The original callback at `0x00424180` is the 221-byte ScreenInf hold update. The complete natural C++ implementation is `src/ScreenHoldUpdate221.cpp`.

## Recovered behavior

- When `field_2c` is zero, a nonzero duration and `Timer::at_most(duration)` gate update alpha as the truncated `fraction * 128 / duration` value. If the gate is false, the previous alpha is preserved.
- When `field_2c` is nonzero, `Timer::at_most(8)` is mandatory. Failure returns `7`; success computes `128 - trunc(fraction * 128 / 8)`.
- Both successful paths use the original Timer postfix increment and return `1`.

## Exactness evidence

The canonical unit `screen_hold_update_221` verifies the complete 221-byte body and all eight original relocations: two Timer `at_most` calls, two Timer fraction calls, two references to the 128.0f alpha constant, the 8.0f duration constant, and Timer postfix increment. The independent PE audit pins the original SHA-256, five physical E8 targets and three HIGHLOW fields.
