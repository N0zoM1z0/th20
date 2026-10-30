// CORE/RECON-966: EXPERIMENTAL, NOT EXACT: full 2884B particle-grid Update.
// Source is tracked under probes, NOT src and NOT strict canonical tracking.
// Reproducible C++20 partial semantic reconstruction, 2953B/764 i386 output
// vs original 2884B/768 i386, despite matching 99 call/25 data reloc counts.
// DO NOT promote or claim authored original exact credit from this probe.
// This noncanonical draft uses a provisional int view of a historical
// std::array<float,200> field (original code accesses integer states 0/1/2)
// and provisional file/palette member origins; do not instantiate as runtime.
// Original body has 768 i386 instructions, 99 E8, 25 HIGHLOW; this is
// a typed semantic draft with unresolved native file/palette helper APIs.
#include "NativeParticleGridGroup.hpp"
#include "NativeAnimationInterpolationConfig.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "GameRandom.hpp"
#include "MotionMath.hpp"
#include <cstdint>
namespace th20 {
extern GameRandom native_polygon_random_5ba4c4;
extern const float native_particle_radius_300, native_particle_radius_150;
extern const float native_particle_radius_50, native_particle_radius_200;
extern const float native_particle_radius_20, native_particle_radius_100;
void normalize_vector3_45cf10(Vector3&,const Vector3&);
struct NativeParticleTimerGate { int changed_45d030(); };
struct NativeParticleAnimationFile : AnimationFile {
    AnimationHandle spawn_45d210(const char* stem, int script, const Vector3* pos,
                                float rotation, int special);
};
// Original 0x00437520 file-selection receiver and original 0x0045D100
// forwarding ABI still need identification independently from the PE.
NativeParticleAnimationFile* particle_effect_file_437520(int index);
std::uint32_t native_particle_effect_palette_45d100(NativeParticleAnimationFile* file,int subindex);
// Original 0x0045D0A0 is an Animation+0x4D8 Timer conversion by value.
int native_particle_age_limit_45d0a0(Animation* child);
struct NativeAnimationColorWordView { std::uint32_t& color_ref_45d0e0(); };

int NativeParticleGridGroup::update() {
    Vector3 basis, gradient, position, velocity, tangent;
    int processed = 0;
    int emission_index=0;
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
    if (reinterpret_cast<NativeParticleTimerGate*>(&timer_1930)->changed_45d030()) {
        if (timer_1930.less_than(50)) {
            emission_index=timer_1930 * 4;
            // Physical original particle handle creation 1/4.
            {
                NativeParticleAnimationFile* file=particle_effect_file_437520(0);
                std::uint32_t palette = native_particle_effect_palette_45d100(file,0);
                AnimationHandle handle=file->spawn_45d210("effect",0x95,nullptr,0.0f,0);
                *reinterpret_cast<AnimationHandle*>(&reinterpret_cast<Vector3*>(&colors_08)->operator[](emission_index+0))=handle;
            }
            // Physical original particle handle creation 2/4.
            {
                NativeParticleAnimationFile* file=particle_effect_file_437520(0);
                std::uint32_t palette = native_particle_effect_palette_45d100(file,0);
                AnimationHandle handle=file->spawn_45d210("effect",0x95,nullptr,0.0f,0);
                *reinterpret_cast<AnimationHandle*>(&reinterpret_cast<Vector3*>(&colors_08)->operator[](emission_index+1))=handle;
            }
            // Physical original particle handle creation 3/4.
            {
                NativeParticleAnimationFile* file=particle_effect_file_437520(0);
                std::uint32_t palette = native_particle_effect_palette_45d100(file,0);
                AnimationHandle handle=file->spawn_45d210("effect",0x95,nullptr,0.0f,0);
                *reinterpret_cast<AnimationHandle*>(&reinterpret_cast<Vector3*>(&colors_08)->operator[](emission_index+2))=handle;
            }
            // Physical original particle handle creation 4/4.
            {
                NativeParticleAnimationFile* file=particle_effect_file_437520(0);
                std::uint32_t palette = native_particle_effect_palette_45d100(file,0);
                AnimationHandle handle=file->spawn_45d210("effect",0x96,nullptr,0.0f,0);
                *reinterpret_cast<AnimationHandle*>(&reinterpret_cast<Vector3*>(&colors_08)->operator[](emission_index+3))=handle;
            }
            union { std::uint32_t word; AnimationColorChannels channels; } initial_color;
            initial_color.word = reinterpret_cast<NativeAnimationColorWordView*>(owner)->color_ref_45d0e0();
            {
                Animation* child=reinterpret_cast<AnimationHandle*>(&reinterpret_cast<Vector3*>(&colors_08)->operator[](emission_index+0))->resolve();
                if(child) {
                    child->set_packed_color(initial_color.word);
                    child->variables().field_00=owner->variables().field_00;
                }
            }
            {
                Animation* child=reinterpret_cast<AnimationHandle*>(&reinterpret_cast<Vector3*>(&colors_08)->operator[](emission_index+1))->resolve();
                if(child) {
                    child->set_packed_color(initial_color.word);
                    child->variables().field_00=owner->variables().field_00;
                }
            }
            {
                Animation* child=reinterpret_cast<AnimationHandle*>(&reinterpret_cast<Vector3*>(&colors_08)->operator[](emission_index+2))->resolve();
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
                Animation* child=reinterpret_cast<AnimationHandle*>(&reinterpret_cast<Vector3*>(&colors_08)->operator[](emission_index+3))->resolve();
                if(child) {
                    child->set_packed_color(initial_color.word);
                    child->variables().field_00=owner->variables().field_00;
                }
            }
        }
    }
    for (int index=0;index<200;++index) {
        Animation* child=reinterpret_cast<AnimationHandle*>(&reinterpret_cast<Vector3*>(&colors_08)->operator[](index))->resolve();
        if (!child) continue;
        child->set_slowdown(owner->slowdown());
        if (reinterpret_cast<std::int32_t&>(reinterpret_cast<Vector3*>(&scalars_15e8)->operator[](index))==0) {
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
            reinterpret_cast<std::int32_t&>(reinterpret_cast<Vector3*>(&scalars_15e8)->operator[](index))=1;
        } else {
            const int elapsed=native_particle_age_limit_45d0a0(child);
            if (owner->variables().field_00+1<=elapsed && reinterpret_cast<std::int32_t&>(reinterpret_cast<Vector3*>(&scalars_15e8)->operator[](index))==1) {
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
                reinterpret_cast<std::int32_t&>(reinterpret_cast<Vector3*>(&scalars_15e8)->operator[](index))=2;
            }
        }
        ++processed;
    }
    if (!processed) return -1;
    ++timer_1930;
    return 0;
}
}
