#include "WeaponStoneInfo.hpp"
#include "RenderMesh.hpp"
#include "PlayerRecord.hpp"
#include "Session.hpp"
#include "Player.hpp"
#include "Weapon.hpp"
#include "WindowState.hpp"
#include "DiagnosticAllocator.hpp"
#include "BulletVelocityMagnitude.hpp"
#include "Angle.hpp"
#include "ScalarMath.hpp"

namespace th20 {
namespace {
constexpr float progress_mesh_radius = 120.0f;
constexpr float progress_mesh_pi = 3.1415927410125732f;
constexpr float progress_mesh_alpha_max = 255.0f;
constexpr float progress_mesh_alpha_fade_start = 0.8f;
constexpr float progress_mesh_alpha_fade_span = 0.2f;
constexpr float progress_mesh_wave_amplitude = 0.5f;
constexpr std::int32_t progress_mesh_fade_start_frame = 60;
constexpr std::int32_t progress_mesh_lifetime_frames = 80;
constexpr std::int32_t progress_mesh_wave_period = 60;
}

void WeaponStoneInfo::update_progress_mesh() {
    RenderMesh* active_mesh=mesh;
    if (active_mesh==nullptr) return;

    if (timer_44.at_least(progress_mesh_lifetime_frames)) {
        process_allocator->release_object(active_mesh);
        mesh=nullptr;
        return;
    }

    const Vector3* source_position;
    if (player_record(0)->field_0c_value()==7)
        source_position=weapon_28->phase_position();
    else
        source_position=&player(0)->position_ref();

    Vector3 center=*source_position;
    active_mesh->initialize(center.x-progress_mesh_radius,
                            center.y-progress_mesh_radius,
                            progress_mesh_radius*2.0f,
                            progress_mesh_radius*2.0f);

    const float view_x=static_cast<float>(window_state.mesh_view_x(view_index));
    const float view_y=static_cast<float>(window_state.mesh_view_y(view_index));
    center.x+=view_x;
    center.y+=view_y;

    const float left=view_x-(384.0f+32.0f)/2.0f;
    const float right=view_x+(384.0f+32.0f)/2.0f;
    const float top=view_y-32.0f;
    const float bottom=view_y+448.0f+32.0f;
    const std::int32_t frame=static_cast<std::int32_t>(timer_44);
    const bool fading=timer_44.greater_than(progress_mesh_fade_start_frame);
    const float time_phase=((static_cast<float>(frame)*progress_mesh_pi)/2.0f)/
        static_cast<float>(progress_mesh_wave_period);

    auto* point=active_mesh->positions;
    auto* vertex=active_mesh->vertices;
    for (std::int32_t column=0;column<active_mesh->columns;++column) {
        for (std::int32_t row=0;row<active_mesh->rows;++row) {
            const Vector3 radial_offset=*point-center;
            const float distance=bullet_velocity_magnitude(radial_offset);

            if (point->x<left || point->x>right || point->y<top || point->y>bottom) {
                vertex->channels.alpha=0;
            } else if (!(distance<=progress_mesh_radius)) {
                vertex->channels.alpha=0;
            } else {
                const float normalized_distance=distance/progress_mesh_radius;
                vertex->color=0xffffffffu;
                if (normalized_distance>progress_mesh_alpha_fade_start) {
                    const float alpha=progress_mesh_alpha_max-
                        ((normalized_distance-progress_mesh_alpha_fade_start)*
                         progress_mesh_alpha_max)/progress_mesh_alpha_fade_span;
                    vertex->channels.alpha=static_cast<std::uint8_t>(
                        static_cast<std::int32_t>(alpha));
                }

                if (fading) {
                    const std::int32_t remaining=progress_mesh_lifetime_frames-frame;
                    const std::int32_t alpha=vertex->channels.alpha;
                    vertex->channels.alpha=static_cast<std::uint8_t>(
                        (alpha*remaining)/20);
                }

                Angle wave;
                wave=(progress_mesh_pi*2.0f)*normalized_distance;
                wave-=time_phase;
                const float radial_wave=scalar_math::sine(static_cast<float>(wave))*
                    normalized_distance*progress_mesh_wave_amplitude;
                const Vector3 displacement(radial_wave*radial_offset.x,
                                            radial_wave*radial_offset.y,0.0f);
                vertex->position+=displacement;

                if (vertex->position.x<left) vertex->position.x=left;
                else if (vertex->position.x>right) vertex->position.x=right;
                if (vertex->position.y<top) vertex->position.y=top;
                else if (vertex->position.y>bottom) vertex->position.y=bottom;
                vertex->position.z=0.0f;
                point->z=0.0f;
            }

            ++point;
            ++vertex;
        }
    }

    active_mesh->update_strips();
    ++timer_44;
}
}
