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

template<class T, unsigned Count>
T* PlayerValues<T,Count>::begin() { return values; }
template<class T, unsigned Count>
T* PlayerValues<T,Count>::end() { return values + Count; }

template PlayerOption* PlayerValues<PlayerOption,10>::begin();
template PlayerOption* PlayerValues<PlayerOption,12>::begin();
template PlayerOption* PlayerValues<PlayerOption,10>::end();
template PlayerOption* PlayerValues<PlayerOption,12>::end();
} // namespace th20
