#include "WeaponStoneInfo.hpp"
#include "Player.hpp"
#include "SoundInf.hpp"
#include "Weapon.hpp"
#include "Animation.hpp"

namespace th20 {
void __fastcall cancel_animation_handle(const AnimationHandle& handle);

void WeaponStoneInfo::complete_item_progress() {
    process_sound.request_effect_at(0x1c,player(0)->position_ref().x);
    initialize_progress_effect();
    if (handle_20!=0)
        cancel_animation_handle(handle_20);
    handle_20=animation_file->spawn("aura",0x1d,player(0)->position_ref(),0.0f,-1,nullptr);
    weapon_28->start_phase();
    phase=1;
}
}
