# ScreenInf 1040B mode-1 shake callback — typed C++ reconstruction frontier

The original callback at `0x004249F0` is the 1040-byte ScreenInf mode-1 shake update. Its natural C++ source is `src/ScreenShakeUpdate1040.cpp`. It is separate from the 1318B mode-0 envelope callback at `0x004244C0`.

## Recovered behavior

- The process Screen-stop flag short-circuits with native result `7`.
- The ScreenInf Timer at `+0x30` is post-incremented before the duration check. `Timer::at_least(field_1c)` ends the effect with result `7`.
- `fraction()` interpolates between the signed integer endpoints at `+0x20` and `+0x24` over duration `+0x1C`.
- Two successive calls to `GameRandom::bounded(3)` select independent horizontal and vertical signs/zeroing.
- The scalar offsets are `Graphics::viewports[3].points[0].x/y`.
- The scaled camera channels are `Graphics::viewports[1/0/5].points[NativeScreenInf::view_40].x/y`; the per-screen view index is not zero-filled or replaced by a synthetic channel.
- The vertical default path clears `viewports[1].points[view_40].y`, `viewports[3].points[2].y` (`0x005C553C`), and the matching indexed Y channels in viewports 0 and 5. The extra viewport-3 point-2 clear is distinct from the scalar Y coordinate at `0x005C552C`.
- The actual Graphics base/viewport/points layout is shared with the 1318B callback: `Graphics @ 0x005C4D40`, `viewports @ +0x278`, `ViewportState stride 0x16C`, `points @ +0x12C`.

## Immutable native boundary

`scripts/verify-screen-shake-update1040-native.py` checks the whole 1040B native extent, all five physical E8 call-site/target pairs, all thirty-five physical HIGHLOW field/target pairs, and the four viewport subobject addresses. The five calls are Timer postfix increment, Timer `at_least`, Timer `fraction`, and two bounded random calls. The data fields cover the stop flag, random stream, scale, sign-mask constant and camera point lanes.

The natural C++20 candidate currently compiles to **1036 bytes**, with the expected **five call and thirty-five data relocations**. It is not yet whole-function exact; the remaining four-byte and SSE register-order differences in the envelope interpolation still need to be reconciled. It remains tracked as `reconstructed`, with zero exact-byte credit. It uses real `NativeScreenInf`, `GameRandom`, and `Graphics` owners; no synthetic channel storage, assembly or padding is introduced.
