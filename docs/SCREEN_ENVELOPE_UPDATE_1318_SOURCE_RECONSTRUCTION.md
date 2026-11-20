# ScreenInf 1318B envelope update — typed C++ reconstruction frontier

The original callback at `0x004244C0` is the 1318-byte ScreenInf mode-0
frame update. Its source is now reconstructed as
`src/ScreenEnvelopeUpdate1318.cpp`. This is a substantial gameplay/update
body, not a synthetic wrapper or a leaf allocator.

## Recovered behavior and owners

1. The process-wide Screen stop flag returns native result `7`.
2. The real `GameController*` at `0x005BA828` gates the callback through
   `update_suppressed`, `animation_frozen`, and the original flag bits 4, 5,
   and 6. The suppressed path returns `1`.
3. The ScreenInf timer at `+0x30` is post-incremented. Its original
   `less_than`, `fraction`, and three integer conversions drive the
   attack/hold/release envelope and the completion result `7`.
4. The actual `GameRandom` stream at `0x005BA4C4` selects independent
   three-state X and Y shake modes. Each mode updates the four original
   camera channels.
5. Those channels are not invented globals: they are typed overlays of
   `Graphics::viewports[0/1/3/5].points[]`. The native Graphics owner is at
   `0x005C4D40`, the viewport array starts at `+0x278`, each
   `ViewportState` is `0x16C` bytes, and `points` starts at `+0x12C`.
   Therefore the original point-array addresses are `0x005C50E4`,
   `0x005C5250`, `0x005C5528`, and `0x005C5800` respectively.

## Immutable native evidence

- Original body: 1318 bytes, SHA-256
  `7b7f9e0966aca60704518d7e68d89fbcdd357b9d62613951d41a3b042079c2a4`.
- Ten native calls: GameController gates at `+0x29/+0x38`, Timer operations
  at `+0xA0/+0xB9/+0xCB/+0xF4/+0x121/+0x154`, and bounded random calls at
  `+0x1D1/+0x37A`.
- Forty-four original PE HIGHLOW fields. Their target families are the
  Screen stop flag, GameController pointer, camera scale, unsigned-to-double
  conversion bias, shared random stream, Graphics point-array base, the
  `1.0f` envelope constant, and the original negative-zero SIMD mask.
- `scripts/verify-screen-envelope-update1318-native.py` rechecks the full
  original hash, all ten physical call-site/target pairs, all forty-four
  HIGHLOW fields, and the four Graphics subobject offsets.

## Exactness boundary

The pinned native C++20 candidate currently compiles to **1320 bytes / 312
instructions**, versus the original **1318 bytes / 313 instructions**. It
has the ten expected call relocations and forty-four data relocations, but
its instruction encodings, floating conversion sequence, and compiler
private SIMD constant relocation are not yet whole-function exact. This
function is deliberately tracked as `reconstructed`, with **zero exact
byte credit** and no strict match unit. No assembly, hand padding, or
invented runtime storage is used. The remaining two-byte/encoding gap is an
open reconstruction task, not silently accepted as a match.

The adjacent 1040B mode-1 shake callback at `0x004249F0` is a separate
boundary and remains under active reconstruction.
