// Original 2,884B particle-grid virtual Update at 0x0045C360.
// Full game-owned C++ logic, SOURCE-PRESENT NONEXACT. The original has
// 768 i386 instructions, 99 E8 calls and 25 PE HIGHLOW fields; current
// pinned-MSVC 2969B/763-instruction body preserves 99 REL32/25 DIR32.
// Session -> Context -> EffectInfo -> AnimationFile -> spawn is the actual
// resource chain, with the original four independently observed calls.
// The native loop stage words are int32_t at +0x15E8; the 200 handles
// and stage values use their real C++ array owners. The remaining frame,
// x87/SSE argument lifetimes and some source/ABI details are not exact.
#include "NativeParticleGridGroup.hpp"
#include "NativeAnimationInterpolationConfig.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "ItemResourceOwners.hpp"
#include "ParticleEffectInfoLookup26.hpp"
#include "NativeParticleSpawnFileView.hpp"
#include "NativeParticleAnimationAccess.hpp"
#include "GameRandom.hpp"
#include "MotionMath.hpp"
#include <cstdint>
namespace th20 {
extern GameRandom native_polygon_random_5ba4c4;
extern const float native_particle_radius_300, native_particle_radius_150;
extern const float native_particle_radius_50, native_particle_radius_200;
extern const float native_particle_radius_20, native_particle_radius_100;
void normalize_vector3_45cf10(Vector3&,const Vector3&);

int NativeParticleGridGroup::update() {
    Vector3 basis, gradient, position, velocity, tangent;
    int processed = 0;
    int emission_index=0;
    int effect_index=0;
    Animation* const owner=animation;
    Vector3 center=owner->vector_5bc_ref();
    extra_1920=center;
    extra_1914=center;
    extra_1908=center;
    polar(tangent, owner->rotation_z_value(), native_particle_radius_300);
    tangent.z=0.0f;
    extra_1914+=tangent;
    const float direction=owner->rotation_z_value()+owner->variables().field_28;
    polar(tangent,direction,native_particle_radius_150);
    tangent.z=0.0f;
    extra_1908+=tangent;
    if (timer_1930.time.changed()) {
        if (timer_1930.time.less_than(50)) {
            emission_index=timer_1930.time * 4;
            // Physical original particle handle creation 1/4.
            {
                EffectInfo* effects = particle_effect_info_for_session_437520(effect_index);
                auto* file = reinterpret_cast<NativeParticleSpawnFileView*>(effects->animation_file(0));
                AnimationHandle handle=file->spawn_45d210("effect",0x95,nullptr,0.0f,effect_index);
                colors_08[emission_index+0]=handle;
            }
            // Physical original particle handle creation 2/4.
            {
                EffectInfo* effects = particle_effect_info_for_session_437520(effect_index);
                auto* file = reinterpret_cast<NativeParticleSpawnFileView*>(effects->animation_file(0));
                AnimationHandle handle=file->spawn_45d210("effect",0x95,nullptr,0.0f,effect_index);
                colors_08[emission_index+1]=handle;
            }
            // Physical original particle handle creation 3/4.
            {
                EffectInfo* effects = particle_effect_info_for_session_437520(effect_index);
                auto* file = reinterpret_cast<NativeParticleSpawnFileView*>(effects->animation_file(0));
                AnimationHandle handle=file->spawn_45d210("effect",0x95,nullptr,0.0f,effect_index);
                colors_08[emission_index+2]=handle;
            }
            // Physical original particle handle creation 4/4.
            {
                EffectInfo* effects = particle_effect_info_for_session_437520(effect_index);
                auto* file = reinterpret_cast<NativeParticleSpawnFileView*>(effects->animation_file(0));
                AnimationHandle handle=file->spawn_45d210("effect",0x96,nullptr,0.0f,effect_index);
                colors_08[emission_index+3]=handle;
            }
            union { std::uint32_t word; AnimationColorChannels channels; } initial_color;
            initial_color.word = reinterpret_cast<NativeParticleAnimationAccess*>(owner)->color_ref_45d0e0();
            {
                Animation* child=colors_08[emission_index+0].resolve();
                if(child) {
                    child->set_packed_color(initial_color.word);
                    child->variables().field_00=owner->variables().field_00;
                }
            }
            {
                Animation* child=colors_08[emission_index+1].resolve();
                if(child) {
                    child->set_packed_color(initial_color.word);
                    child->variables().field_00=owner->variables().field_00;
                }
            }
            {
                Animation* child=colors_08[emission_index+2].resolve();
                if(child) {
                    child->set_packed_color(initial_color.word);
                    child->variables().field_00=owner->variables().field_00;
                }
            }
            // Original immutable native fourth-emitter color transform:
            // three low-order channels receive unsigned byte(300-channel).
            initial_color.channels.red = static_cast<std::uint8_t>(300 - initial_color.channels.red);
            initial_color.channels.green = static_cast<std::uint8_t>(300 - initial_color.channels.green);
            initial_color.channels.blue = static_cast<std::uint8_t>(300 - initial_color.channels.blue);
            {
                Animation* child=colors_08[emission_index+3].resolve();
                if(child) {
                    child->set_packed_color(initial_color.word);
                    child->variables().field_00=owner->variables().field_00;
                }
            }
        }
    }
    for (int index=0;index<200;++index) {
        Animation* child=colors_08[index].resolve();
        if (!child) continue;
        child->set_slowdown(owner->slowdown());
        if (stages_15e8[index]==0) {
            position=extra_1914;
            polar(tangent,native_polygon_random_5ba4c4.radians(),
                  native_polygon_random_5ba4c4.unit()*native_particle_radius_150);
            tangent.z=0.0f;
            position+=tangent;
            gradient=extra_1908;
            polar(tangent,native_polygon_random_5ba4c4.radians(),
                  native_polygon_random_5ba4c4.unit()*native_particle_radius_50);
            tangent.z=0.0f;
            gradient+=tangent;
            basis=gradient-position;
            normalize_vector3_45cf10(velocity,basis);
            basis=extra_1920-gradient;
            normalize_vector3_45cf10(tangent,basis);
            velocity+=tangent;
            normalize_to_length(velocity,velocity,
                native_polygon_random_5ba4c4.unit()*native_particle_radius_200+
                native_particle_radius_200);
            basis=gradient-position;
            normalize_to_length(tangent,basis,
                native_polygon_random_5ba4c4.unit()*native_particle_radius_100+
                native_particle_radius_100);
            reinterpret_cast<NativeAnimationInterpolationForwardView*>(child)->configure_45d150(
                static_cast<int>(owner->variables().field_00),position,tangent,gradient,velocity);
            positions_328[index]=gradient;
            vectors_c88[index]=velocity;
            stages_15e8[index]=1;
        } else {
            const int elapsed=reinterpret_cast<NativeParticleAnimationAccess*>(child)->age_45d0a0();
            if (owner->variables().field_00+1<=elapsed && stages_15e8[index]==1) {
                gradient=owner->vector_5bc_ref();
                polar(tangent,native_polygon_random_5ba4c4.radians(),
                    native_polygon_random_5ba4c4.unit()*native_particle_radius_20);
                tangent.z=0.0f;
                gradient+=tangent;
                polar(tangent,native_polygon_random_5ba4c4.radians(),
                    native_polygon_random_5ba4c4.unit()*native_particle_radius_20);
                tangent.z=0.0f;
                reinterpret_cast<NativeAnimationInterpolationForwardView*>(child)->configure_45d150(
                    static_cast<int>(owner->variables().field_00),
                    positions_328[index],vectors_c88[index],gradient,tangent);
                stages_15e8[index]=2;
            }
        }
        ++processed;
    }
    if (!processed) return -1;
    ++timer_1930.time;
    return 0;
}
}
