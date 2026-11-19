# Timer unscaled fractional advance — exact 59B leaf

The original `0x00454110` function is a 59-byte / 17-instruction x86
`__thiscall` member with one `float` argument and `ret 4`. Its complete body
performs exactly three operations on the native 16-byte `Timer` layout:

1. `previous = current`
2. `current_fraction += delta`
3. `current = static_cast<std::int32_t>(current_fraction)`

`Timer::add_unscaled(float)` in `src/TimerUnscaledAdvance59.cpp` is the natural
C++ expression of that protocol. Its pinned MSVC x86 C++20 object is exactly
59/59 original bytes, with zero relocations. This is intentionally separate
from `Timer::add(float)`, which also initializes flags and applies the
configured clock scale. The original caller is `Animation::update` opcode 4,
which applies the negative signed integer operand to `timer_4c8`.

The method spelling is a semantic reconstruction label; original source
spelling and authored-versus-compiler origin remain unknown. It is one exact
leaf, not an exactness claim for the enclosing 39,470-byte Animation VM Boss.
