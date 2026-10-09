#include "Player.hpp"
#include "ShotData.hpp"
#include "Session.hpp"
#include "WeaponStoneInfo.hpp"
namespace th20 {
bool Player::focused_mode() {return focused?1:0;}
std::int32_t Player::damage_limit() {
    return weapon_stone_info(0)->phase_one() ?
        shot_data->damage_caps[player_record(0)->field_10_value()][2] :
        (focused_mode() ?
            shot_data->damage_caps[player_record(0)->field_10_value()][1] :
            shot_data->damage_caps[player_record(0)->field_14_value()][0]);
}
WeaponStoneInfo* weapon_stone_info(std::int32_t index) {
    return session.context(index).weapon_stone_info();
}
}
