#include "Item.hpp"
#include "ItemResourceOwners.hpp"
#include "GameRandom.hpp"
#include "Session.hpp"
#include "SoundInf.hpp"

namespace th20 {
extern GameRandom script_random;

void Item::retire() {
    state=0;
    attachment.retire();
    link.detach();
    auto& available=*free_list;
    available.prepend(&link);
}

std::int32_t Item::spawn_effect() {
    if(type==4 || type==6 || type==14 || type==5 || type==7) {
        auto* effects=context->effect_info();
        auto* file=effects->animation_file(0);
        file->spawn("effect",94,position,0.0f,-1,0);
        if(type==4 || type==5) process_sound.request_effect(74,0);
        else process_sound.request_effect(48,0);
    } else if(type==1 || type==2) {
        auto* effects=context->effect_info();
        auto* file=effects->animation_file(0);
        file->spawn("effect",94,position,0.0f,-1,0);
        if(sound>=0) process_sound.request_effect(sound,0);
    }
    return 0;
}

std::int32_t Item::activate() {
    state=2;
    if(type==13) {
        if(script_random.next()%8<=4) {
            auto* record=player_record(0);
            auto index=script_random.next()%4;
            type=record->starting_configuration(index)/2+9;
        } else {
            type=script_random.next()%4+9;
        }
    }
    switch(type) {
    case 9: {
        auto* file=stone_menu_info()->animation_file();
        file->bind_animation(&animation,37);
        break;
    }
    case 10: {
        auto* file=stone_menu_info()->animation_file();
        file->bind_animation(&animation,38);
        break;
    }
    case 11: {
        auto* file=stone_menu_info()->animation_file();
        file->bind_animation(&animation,39);
        break;
    }
    case 12: {
        auto* file=stone_menu_info()->animation_file();
        file->bind_animation(&animation,40);
        break;
    }
    }
    auto& visible_animation=animation;
    visible_animation.set_position(position);
    secondary_animation.stop();
    return 0;
}
}
