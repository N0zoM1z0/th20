#include "WeaponStoneInfo.hpp"
#include "RenderMesh.hpp"
#include "DiagnosticAllocator.hpp"
#include "DiagnosticObjectFactories.hpp"
#include "EffectParameters.hpp"
#include "ParticleEffectInfoLookup26.hpp"
#include "ItemResourceOwners.hpp"
#include "Player.hpp"
#include "PlayerRecord.hpp"
#include "Session.hpp"
#include "Weapon.hpp"
#include "Animation.hpp"
#include "Angle.hpp"

namespace th20 {
extern const float native_pi_56e0f0;
extern const float native_negative_pi_56e0f8;
extern const float native_screen_half_2_56c8d0;
extern const float native_twenty_56ec8c;
extern const float native_twenty_four_56f7b4;
extern std::int32_t weapon_stone_progress_animation_callback(Animation*);

void WeaponStoneInfo::initialize_phase_effect() {
    const Vector3* source_position;
    if (player_record(0)->field_0c_value()==7)
        source_position=weapon_28->phase_position();
    else
        source_position=&player(0)->position_ref();
    const Vector3* selected_position=source_position;
    const Vector3 position=*selected_position;

    process_allocator->release_object(mesh);
    mesh=nullptr;
    mesh=process_allocator->allocate_object<RenderMesh,std::int32_t,std::int32_t,
        std::int32_t,std::int32_t>(
            "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\weaponstone.cpp:652 RenderMeshInf",
            12,12,0,view_index);
    timer_44=0;
    mesh->set_update_callback(weapon_stone_progress_animation_callback);

    EffectParameters parameters;
    Angle angle(0.0f);
    parameters.vector_00=position;
    parameters.enabled=player_record(0)->field_0c_value()!=7;
    parameters.scalar_1c=native_pi_56e0f0/native_twenty_56ec8c;
    parameters.color=0xffffc080u;
    for (std::int32_t index=0;index<24;++index) {
        parameters.scalar_18=angle;
        particle_effect_info_for_session_437520(0)->spawn_effect(6,parameters,nullptr);
        angle+=(native_pi_56e0f0*native_screen_half_2_56c8d0)/native_twenty_four_56f7b4;
    }

    parameters.scalar_1c=native_negative_pi_56e0f8/native_twenty_56ec8c;
    for (std::int32_t index=0;index<24;++index) {
        parameters.scalar_18=angle;
        particle_effect_info_for_session_437520(0)->spawn_effect(6,parameters,nullptr);
        angle-=(native_pi_56e0f0*native_screen_half_2_56c8d0)/native_twenty_four_56f7b4;
    }
}
}
