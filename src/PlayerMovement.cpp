// Complete authored C++ for native Player 555-byte movement/playfield clamp.
// NONEXACT: current pinned MSVC emits 561B/136 instructions versus original
// 555B/135 instructions. All original opcode kinds align, but an additional
// real SSE float temporary spill remains; do not credit original bytes.
// Native boundaries, clock source, clamps and gameplay are implemented whole.
// The final two world-coordinate divisions use the original shared native
// Player float 128 value at 0x0056CD98, not a compiler-private 128 literal.
// This strengthens actual physical relocation identity without claiming
// the remaining extra SSE spill or entire 555B original as byte exact.
#include "Player.hpp"
#include "ClockScalar.hpp"
#include <cstdint>

namespace th20 {
extern const float native_448, native_16, native_128;
void Player::apply_move_delta(std::int32_t x, std::int32_t y) {
    vector_20c4.x = static_cast<float>(x) * static_cast<float>(default_timer_clock);
    vector_20c4.y = static_cast<float>(y) * static_cast<float>(default_timer_clock);
    if (field_67c != 0) {
        vector_20d0 = vector_20c4;
    }
    point_20dc.x = static_cast<std::int32_t>(vector_20c4.x);
    point_20dc.y = static_cast<std::int32_t>(vector_20c4.y);
    {
        const std::int32_t delta = point_20dc.x;
        std::int32_t& current = fixed_position_ref().x;
        const std::int32_t before = current;
        current = static_cast<std::int32_t>(static_cast<std::uint32_t>(before) + static_cast<std::uint32_t>(delta));
    }
    {
        const std::int32_t delta = point_20dc.y;
        std::int32_t& current = fixed_position_ref().y;
        const std::int32_t before = current;
        current = static_cast<std::int32_t>(static_cast<std::uint32_t>(before) + static_cast<std::uint32_t>(delta));
    }
    if (movement_mode() == 0) {
        if (fixed_position_ref().x < -0x5C00)
            fixed_position_ref().x = -0x5C00;
        else if (fixed_position_ref().x > 0x5C00)
            fixed_position_ref().x = 0x5C00;
        if (fixed_position_ref().y < 0x1000)
            fixed_position_ref().y = 0x1000;
        else if (fixed_position_ref().y >
                 static_cast<std::int32_t>((native_448 - native_16) * native_128)) {
            // The original recomputes the native 448-16 and 128 float bound
            // after the comparison; this real local keeps that live result.
            const float upper = (native_448 - native_16) * native_128;
            fixed_position_ref().y = static_cast<std::int32_t>(upper);
        }
    }
    position_ref().x = static_cast<float>(fixed_position_ref().x) / native_128;
    position_ref().y = static_cast<float>(fixed_position_ref().y) / native_128;
}
}
