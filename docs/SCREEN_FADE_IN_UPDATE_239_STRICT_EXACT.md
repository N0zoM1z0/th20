# ScreenInf 239B fade-in update — strict native reconstruction

The original callback at `0x00424260` is the 239-byte ScreenInf fade-in update. The complete natural C++ implementation is `src/ScreenFadeInUpdate239.cpp`.

## Recovered behavior

- The shared Screen-stop flag returns `7` immediately.
- With a nonzero duration, `Timer::less_than(duration)` selects the active ramp; the alpha becomes the truncated `fraction * 255 / duration` value. Once the ramp has reached its end, alpha is set to `255`. Negative results are clamped to zero.
- The Timer is then checked against `duration + 2`. Completion returns `7`.
- Before completion, the callback respects the real global GameController pointer and `update_suppressed()` gate. It increments the Timer only when the controller is absent or updates are not suppressed, then returns `1`.

## Exactness evidence

The canonical unit `screen_fade_in_239` verifies all 239 bytes and all nine relocations: Screen-stop flag, Timer `less_than`/`fraction`/`at_least`/postfix increment, alpha 255 constant, both GameController global references, and the real update-suppression getter. The independent PE audit pins the native hash, five E8 targets and four HIGHLOW fields.
