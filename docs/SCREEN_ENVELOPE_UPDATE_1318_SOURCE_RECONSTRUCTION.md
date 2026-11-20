# ScreenInf 1318B envelope update — typed C++ reconstruction frontier

The original callback at `0x004244C0` is the 1318-byte ScreenInf mode-0 frame update. Its natural C++ source is `src/ScreenEnvelopeUpdate1318.cpp`. This is a substantial gameplay/update body, not a synthetic wrapper or a leaf allocator.

## Recovered behavior and owners

1. The process-wide Screen stop flag returns native result `7`.
2. The real `GameController*` at `0x005BA828` gates the callback through `update_suppressed`, `animation_frozen`, and the original flag bits 4, 5, and 6. Suppressed updates return `1` without advancing the ScreenInf timer.
3. The ScreenInf timer at `+0x30` is post-incremented after the controller gates. Its original `less_than`, `fraction`, and three integer-value reads drive the attack/hold/release envelope and completion result `7`.
4. The release phase uses the native unsigned-to-double conversion bias table at `0x0056CDD0`; the hold phase uses the original `1.0f` constant at `0x0056C8CC`.
5. The actual `GameRandom` stream at `0x005BA4C4` selects independent three-state X and Y shake modes.
6. The four camera lanes are actual `Graphics::viewports[0/1/3/5].points[]` fields. The Graphics owner is at `0x005C4D40`, the viewport array starts at `+0x278`, each `ViewportState` is `0x16C` bytes, and `points` starts at `+0x12C`. The scalar X/Y lane uses `viewports[3].points[view_40]`; scaled channels use the same view index in viewports 1, 0 and 5.
7. The Y zero/default path additionally clears the fixed `viewports[3].points[2].y` lane (`0x005C553C`), between the viewport-1 and viewport-0 writes. It is not the scalar Y coordinate at `0x005C552C`.

## Immutable native evidence

- Original body: 1318 bytes, SHA-256 `7b7f9e0966aca60704518d7e68d89fbcdd357b9d62613951d41a3b042079c2a4`.
- Ten native calls: GameController gates at `+0x29/+0x38`, Timer operations at `+0xA0/+0xB9/+0xCB/+0xF4/+0x121/+0x154`, and bounded random calls at `+0x1D1/+0x37A`.
- Forty-four original PE HIGHLOW fields. Their target families are the Screen stop flag, GameController pointer, camera scale, unsigned-to-double conversion bias, shared random stream, Graphics point-array base, the `1.0f` envelope constant, and the original negative-zero SIMD mask.
- `scripts/verify-screen-envelope-update1318-native.py` rechecks the full original hash, all ten physical call-site/target pairs, all forty-four HIGHLOW fields, and the four Graphics subobject offsets.

## Exactness boundary

The current natural C++20 candidate compiles to **1319 bytes / 313 instructions**, versus the original **1318 bytes / 313 instructions**. It has the ten expected call relocations and forty-four data relocations. Restoring the native `switch (bounded(3))` case order places the zero, positive, and negative X/Y blocks in the original sequence and removes the previous extra branch trampolines. Making the two release-phase double intermediates ordinary C++ locals also restores direct `cvtsd2ss` memory-source conversions and the original XMM0/XMM1 division order. The remaining differences are now one byte overall plus register allocation and statement ordering in the SSE conversion and repeated viewport address calculations. This function remains `reconstructed`, with **zero exact-byte credit** and no strict match unit. No assembly, hand padding, or invented runtime storage is used.

The exact helper boundaries used by this boss were rechecked with scoped canonical replay: Timer **21/21 units**, GameController **6/6 units**, and GameRandom **6/6 units**. In particular, the 40B/25B GameController gates, 22B Timer post-increment, 46B Timer comparison, 17B Timer fraction and 49B GameRandom bounded helper are all whole-function exact. This narrows the remaining reconstruction boundary to the 1318B boss itself rather than its existing callees.

The adjacent 1040B mode-1 shake callback at `0x004249F0` has now been restored as a whole-function exact natural C++ implementation in the separate `screen_shake_update_1040` unit.
