// Original native forwarding of option offsets through real Weapon
// virtual slots, without inventing a mock Weapon vtable or callback owner.
#include "WeaponStoneInfo.hpp"
#include "Weapon.hpp"
namespace th20 {
const Vector2* WeaponStoneInfo::focused_offset(std::int32_t count,std::int32_t index) {
    return weapon_2c->focused_offset(count,index);
}
const Vector2* WeaponStoneInfo::unfocused_offset(std::int32_t count,std::int32_t index) {
    return weapon_30->unfocused_offset(count,index);
}
} // namespace th20
