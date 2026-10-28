// Original native forwarding of option offsets through real Weapon
// virtual slots, without inventing a mock Weapon vtable or callback owner.
#include "WeaponStoneInfo.hpp"
#include "Weapon.hpp"
#include "Player.hpp"
namespace th20 {
const Vector2* WeaponStoneInfo::focused_offset(std::int32_t count,std::int32_t index) {
    return weapon_2c->focused_offset(count,index);
}
const Vector2* WeaponStoneInfo::unfocused_offset(std::int32_t count,std::int32_t index) {
    return weapon_30->unfocused_offset(count,index);
}
// The explicit else preserves both native branches and their return ABI.
std::int32_t WeaponStoneInfo::option_script_variant() {
    if (player(0)->focused_mode()) {
        return weapon_2c->script_variant();
    } else {
        return weapon_30->script_variant();
    }
}

void WeaponStoneInfo::initialize_option_pair(PlayerOption* option, std::int32_t index) {
    weapon_2c->initialize_focused_option(option,index);
    weapon_30->initialize_unfocused_option(option,index);
}
} // namespace th20
