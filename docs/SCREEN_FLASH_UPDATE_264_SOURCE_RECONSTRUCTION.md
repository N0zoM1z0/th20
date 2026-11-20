# ScreenInf 264B flash update — typed C++ reconstruction frontier

The original callback at `0x00424350` is the 264-byte ScreenInf flash
update. Its natural C++ source is `src/ScreenFlashUpdate264.cpp`.

## Recovered behavior

- The flash alpha is the high byte of `NativeScreenInf::field_24`.
- The shared Screen stop flag returns native result `7` before Timer work.
- `Timer::less_than(field_1c)` selects the active fade interval.
- During the fade, `Timer::fraction()` is multiplied by the unsigned-alpha
  conversion and divided by the duration; the truncated result is subtracted
  from alpha and clamped at zero.
- Once the interval completes, alpha is cleared, the repeat count at `+0x20`
  is decremented, and the callback returns `7` if no repeats remain.
- A remaining repeat resets the actual Timer through its integer assignment
  operator. The common tail invokes the real Timer postfix increment and
  returns `1`.

## Immutable native evidence

`scripts/verify-screen-flash-update264-native.py` pins the original 264-byte
body by SHA-256, all four physical E8 call-site/target pairs, and both physical
PE HIGHLOW fields. The calls are Timer `less_than`, Timer `fraction`, Timer
integer assignment, and Timer postfix increment. The data relocations are
the process Screen-stop flag and the unsigned-to-double conversion table at
`0x0056CDD0`.

The natural C++20 candidate is **264 bytes** and has the expected four call
and two data relocations. It is not yet whole-function exact: the remaining
difference is the SSE register/temporary order around fraction/alpha
multiplication. It is recorded as `reconstructed`, with zero exact-byte
credit and no strict match unit. No assembly or hand padding is used.
