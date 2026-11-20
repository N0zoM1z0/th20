#include "WeaponStoneInfo.hpp"
#include "PlayerRecord.hpp"
#include "Session.hpp"
#include "HudGauge.hpp"
#include "Weapon.hpp"

namespace th20 {


void WeaponStoneInfo::process_item_drop(std::int32_t amount) {
    if (current_front->has_dialogue()!=0)
        return;
    if (phase!=0)
        return;

    const std::int32_t interval=player_record(0)->field_2f_value()!=0 ? 15 : 10;
    if (player_record(0)->field_a4_value()!=0 &&
        player_record(0)->clamped_field_4c()%interval==interval-1) {
        ++amount;
        weapon_34->set_passive(1);
    }

    if (player_record(0)->clamped_field_4c()>=player_record(0)->clamped_field_50()) {
        if (phase==0) {
            player_record(0)->set_field_4c(player_record(0)->clamped_field_50());
            complete_item_progress();
        }
    } else {
        player_record(0)->add_field_4c_clamped(amount);
        if (player_record(0)->clamped_field_4c()>=player_record(0)->clamped_field_50()) {
            player_record(0)->set_field_4c(player_record(0)->clamped_field_50());
            complete_item_progress();
        }
    }
}
}
