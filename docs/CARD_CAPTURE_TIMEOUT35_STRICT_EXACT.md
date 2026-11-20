# Card 60-frame capture threshold — 35B whole native C++ exact

The original `0x004887D0..0x004887F2` (35 bytes) reads the actual
`Card::age` Timer at receiver `+0x24`, calls the native
`Timer::at_least(60)` at `0x004235C0`, and returns an **integer** result.
Its original `movzx eax, al` establishes the 32-bit zero-extension ABI;
modeling this wrapper as `bool` erroneously produced a 32-byte body.

`src/CardCaptureTimeout35.cpp` now expresses this logic as a real Timer
member operation and returns `std::int32_t` using a non-allocating Card
receiver view. Pinned MSVC 19.44 x86 `/Od /Ob0 /GS /Gy /Zl /sdl`
emits all 35 native bytes, including the genuine stack-local Timer pointer,
with one E8 operand at `+0x18` to the independently known `0x004235C0`.
The whole original function was compared, not an arbitrary prefix.

The original 123B Card capture-state handler at `0x00487BB0` is this
function's sole native caller. That parent must be reconstructed and
validated independently. The 35B unit has an individual canonical
strict relocation replay, and neither copied native bytes nor inert
compiler-shaping code is involved.
