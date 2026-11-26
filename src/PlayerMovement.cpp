// Native Player movement and playfield clamp at 0x004FFA10.
// The C++14 unit profile preserves integer conversion across the getter call;
// world-coordinate locals retain each float result until its destination lookup.
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
            // The native clamp recomputes the bound after the comparison.
            fixed_position_ref().y = static_cast<std::int32_t>((native_448 - native_16) * native_128);
        }
    }
    const float world_x = static_cast<float>(fixed_position_ref().x) / native_128;
    position_ref().x = world_x;
    const float world_y = static_cast<float>(fixed_position_ref().y) / native_128;
    position_ref().y = world_y;
}
}
