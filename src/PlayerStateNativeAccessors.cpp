// Native state-frame dependencies with complete locked-compiler comparisons.
// The state setter shares its physical head with an existing canonical owner.
#include "Player.hpp"
#include "GameController.hpp"
#include "InputState.hpp"
#include "PlayerRecord.hpp"
#include "MotionMath.hpp"
#include "ScalarMath.hpp"
#include "HudGauge.hpp"
#include <algorithm>

namespace th20 {
extern const float native_zero, native_pi, native_two, native_128;
void Player::set_state_value(std::int32_t value) { state = value; }
void Player::revive_after_bomb() {
    timer_644 = 60;
    set_state_value(1);
}
float Player::direction_from(const Vector3& target) {
    const float dx = target.x - position_ref().x;
    const float dy = target.y - position_ref().y;
    if (dy == native_zero && dx == native_zero) return native_pi / native_two;
    return scalar_math::arctangent(dy, dx);
}
void Player::set_position_xy(float x, float y) {
    fixed_position.x = static_cast<std::int32_t>(x * native_128);
    fixed_position.y = static_cast<std::int32_t>(y * native_128);
    position.x = static_cast<float>(fixed_position.x) / native_128;
    position.y = static_cast<float>(fixed_position.y) / native_128;
    set_option_field_fc(1);
}
std::uint32_t Player::entity_flag5() const { return (entity_flags.bits >> 5) & 1u; }
float Player::motion_scale_value() const { return field_20ec; }
void Player::set_extra_motion(const Vector3& value) { vector_20f0 = value; }
std::uint32_t GameController::flag_19_set() const { return (game_flags.bits >> 19) & 1u; }
std::uint32_t InputButtonState::replay_pressed_bits(std::uint32_t mask) const {
    return replay_pressed & mask;
}
std::int32_t PlayerRecord::consume_power(std::int32_t amount) {
    if (field_30 <= field_38) return false;
    field_30 -= amount;
    if (field_30 < field_38) field_30 = field_38;
    return (field_30 + amount) / field_38 != field_30 / field_38;
}
std::int32_t PlayerRecord::clamped_field_d4() {
    field_d4 = std::clamp(field_d4, 2, 10);
    return field_d4;
}
void PlayerRecord::set_field_cc_clamped(std::int32_t value) {
    field_cc = value;
    if (field_cc < 0) field_cc = 0;
    if (field_cc > clamped_field_d8()) field_cc = clamped_field_d8();
    if (current_front != nullptr)
        current_front->update_progress_handles_6c(
            clamped_field_cc(), clamped_field_d0(), clamped_field_d8());
}
void Angle::to_vector(Vector3& output, const Vector3* offset, float length) {
    polar(output, value, length);
    if (offset != nullptr) output += *offset;
}
void Animation::set_secondary_color(std::uint32_t value) { base.color_494 = value; }
} // namespace th20
