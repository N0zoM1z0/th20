# ScreenInf 180B fade-out update — strict native reconstruction

The original callback at `0x004240C0` is the 180-byte ScreenInf fade-out update. The complete natural C++ implementation is `src/ScreenFadeOutUpdate180.cpp`.

## Recovered behavior

- The shared Screen-stop flag immediately returns native result `7`.
- If the duration at `NativeScreenInf::field_1c` is nonzero, the Timer fractional value computes `255 - fraction * 255 / duration`; the result is truncated to signed integer and clamped at zero into `alpha_18`.
- The Timer is then checked with its original `at_least(duration)` operation. Expiration returns `7`; otherwise the original postfix increment runs and the callback returns `1`.
- A zero duration skips the alpha calculation and expires through the same native Timer boundary.

## Exactness evidence

The canonical unit `screen_fade_out_180` compiles the natural C++ function with the locked i386 MSVC profile and verifies the entire 180-byte function plus all six relocations: Screen-stop flag, Timer fraction, both references of the 255.0f alpha constant, Timer `at_least`, and Timer postfix increment. The original PE extent and physical E8/HIGHLOW fields are independently pinned by `scripts/verify-screen-fade-out-update180-native.py`.
