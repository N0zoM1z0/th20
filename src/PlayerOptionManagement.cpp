// Exact native Player option count, shared 10/12-slot iteration, and
// PlayerShotController bit-zero update. Original option index storage is typed.
#include "Player.hpp"

namespace th20 {
std::int32_t Player::active_option_count() const {
    return static_cast<std::int32_t>(field_680);
}

void PlayerShotController::set_flag0(std::uint32_t flag) {
    flags_1255c.bit0_view.bit0 = flag;
}

void Player::set_option_field_fc(std::int32_t value) {
    for (auto& option : options) option.field_fc = value;
    for (auto& option : secondary_options) option.field_fc = value;
}

// Original two-bit Player movement-mode getter at 0x004FF870.
std::uint32_t Player::movement_mode() const {
    return entity_flags.mode_6_view.mode;
}

// The native 75-byte setter returns the actual *assigned bitfield value*.
// Returning the assignment expression preserves MSVC's original single
// temporary state word, rather than reloading the field or fabricating data.
std::uint32_t Player::set_movement_mode(std::uint32_t value) {
    timer_2070 = 0;
    return entity_flags.mode_6_view.mode = value;
}

// The original 90-byte method updates only the twelve secondary options;
// the previously exact set_option_field_fc updates both option arrays.
void Player::set_secondary_option_field_fc(std::int32_t value) {
    auto& items = secondary_options;
    auto* current = items.begin();
    auto* end = items.end();
    for (; current != end; ++current) {
        PlayerOption* entry = current;
        entry->field_fc = value;
    }
}

template<class T, unsigned Count>
T* PlayerValues<T,Count>::begin() { return values; }
template<class T, unsigned Count>
T* PlayerValues<T,Count>::end() { return values + Count; }

template PlayerOption* PlayerValues<PlayerOption,10>::begin();
template PlayerOption* PlayerValues<PlayerOption,12>::begin();
template PlayerOption* PlayerValues<PlayerOption,10>::end();
template PlayerOption* PlayerValues<PlayerOption,12>::end();
} // namespace th20
