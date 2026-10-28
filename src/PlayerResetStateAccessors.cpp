// Full native Player/Session state accessors in the Player reset call chain.
// Original std::clamp is proven by its actual codegen and one native call.
#include "Player.hpp"
#include "Session.hpp"
#include <algorithm>
namespace th20 {
std::int32_t PlayerTable::clamped_field_1e4() {
    field_1e4 = std::clamp(field_1e4, 0, 1);
    return field_1e4;
}
std::uint32_t Session::flag0_value() const { return flags.bits & 1u; }
void Player::clear_entity_flag2() { entity_flags.bits &= ~4u; }
} // namespace th20
