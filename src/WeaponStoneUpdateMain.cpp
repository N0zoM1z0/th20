#include "WeaponStoneInfo.hpp"
#include "GameController.hpp"
#include "HudGauge.hpp"
#include "Player.hpp"
#include "PlayerRecord.hpp"
#include "Session.hpp"
#include "Identifier32.hpp"
#include "Weapon.hpp"
#include "Bullet.hpp"
#include "BulletCollisionHandle.hpp"
#include "LaserParameters.hpp"

namespace th20 {
extern GameController* current_game_controller;
extern const float native_screen_alpha_128_56cd98;
extern const float native_twenty_four_56f7b4;

std::int32_t WeaponStoneInfo::update_main() {
    if (current_game_controller!=nullptr &&
        current_game_controller->flag_6_set()!=0 && phase!=0) {
        handle_20.interrupt(1);
        handle_20=0u;
        phase=0;
        weapon_28->end_phase();
    }

    if (current_game_controller==nullptr ||
        current_game_controller->update_node_enabled()==0 ||
        current_front==nullptr || current_front->has_dialogue()!=0) {
        if (current_front==nullptr) return 1;
        if (current_front->has_dialogue()==0) return 1;
        handle_20.retire();
        weapon_28->cancel_phase();
        return 1;
    }

    bool initial_cancellation;
    if (player_record(0)->field_0c_value()==5) initial_cancellation=false;
    else if (player_record(0)->field_0c_value()==7) initial_cancellation=false;
    else initial_cancellation=true;
    bool allow_cancellation=initial_cancellation;
    if (phase==2) {
        if (weapon_28->end_phase()==0) {
            radius=native_screen_alpha_128_56cd98;
            if (allow_cancellation) timer_64=60;
            goto phase_complete;
        }
        phase=1;
    }

    if (phase==1) {
        if (!bullet_animation_handle_valid(handle_20)) {
            handle_20=animation_file->spawn(
                "aura",0x1d,player(0)->position_ref(),0.0f,-1,nullptr);
        }
        handle_20.set_position_forward(player(0)->position_ref());

        if (weapon_28->update_phase()==0) goto update_weapons;
        weapon_28->end_phase();
        if (player_record(0)->field_0c_value()==6)
            allow_cancellation=false;
        if (allow_cancellation) timer_64=4;
        radius=native_twenty_four_56f7b4;
    } else {
        goto update_weapons;
    }

phase_complete:

    handle_20.interrupt(1);
    handle_20=0u;
    phase=0;
    initialize_phase_effect();
    player_record(0)->set_field_4c(0);

update_weapons:
    if (timer_64.greater_than(0) && allow_cancellation) {
        auto* bullets=bullet_controller(0);
        const Vector3& bullet_center=player(0)->position_ref();
        bullets->cancel_near_limited(bullet_center,radius,0,99999,0);

        auto* lasers=laser_controller(0);
        const Vector3& laser_center=player(0)->position_ref();
        lasers->cancel_near(laser_center,radius,0,1);
        timer_64--;
    }

    weapon_28->update_main();
    weapon_2c->update_focused();
    weapon_30->update_unfocused();
    weapon_34->update_passive();
    timer_10++;
    return 1;
}
}
