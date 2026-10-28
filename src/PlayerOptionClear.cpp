// Complete native Player option-handle interruption/retirement sweep.
// The two index instantiations share one original linker-folded 23-byte body.
#include "Player.hpp"
namespace th20 {
void __fastcall cancel_animation_handle_mode2(const AnimationHandle& handle);

template<class T, unsigned Count>
T& PlayerValues<T,Count>::at(std::int32_t index) { return values[index]; }

void Player::clear_option_animations() {
    entity_flags.bits &= ~2u;
    for (std::int32_t i = 0; i < 10; ++i) {
        cancel_animation_handle_mode2(options.at(i).handle_dc);
        cancel_animation_handle_mode2(options.at(i).handle_e0);
    }
    for (std::int32_t i = 0; i < 12; ++i) {
        cancel_animation_handle_mode2(secondary_options.at(i).handle_dc);
        cancel_animation_handle_mode2(secondary_options.at(i).handle_e0);
    }
    field_20e8 = 0;
}
} // namespace th20
