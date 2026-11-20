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
extern const float native_screen_rect_inner_width_384_56cda4;
extern const float native_screen_half_2_56c8d0;
extern const float native_screen_height_448_56d7c0;
extern const float native_screen_alpha_max_56cd9c;
extern const float native_pi_56e0f0;
extern const float native_polygon_radius32;
extern const float native_screen_negative_32_576360;
extern const float native_progress_mesh_radius_120_570ad0;
extern const float native_progress_mesh_alpha_fade_start_08_573160;
extern const float native_progress_mesh_alpha_fade_span_02_56fbf8;
extern const float native_progress_mesh_wave_amplitude_05_56e0ec;
extern const float native_progress_mesh_wave_period_60_56e048;
namespace {
constexpr std::int32_t progress_mesh_fade_start_frame = 60;
constexpr std::int32_t progress_mesh_lifetime_frames = 80;
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
    active_mesh->initialize(center.x-native_progress_mesh_radius_120_570ad0,
                            center.y-native_progress_mesh_radius_120_570ad0,
                            native_progress_mesh_radius_120_570ad0*2.0f,
                            native_progress_mesh_radius_120_570ad0*2.0f);

    const float view_x=static_cast<float>(window_state.mesh_view_x(view_index));
    const float view_y=static_cast<float>(window_state.mesh_view_y(view_index));
    center.x+=view_x;
    center.y+=view_y;

    Angle wave;
    auto* point=active_mesh->positions;
    auto* vertex=active_mesh->vertices;
    for (std::int32_t column=0;column<active_mesh->columns;++column) {
        for (std::int32_t row=0;row<active_mesh->rows;++row) {
            Vector3 radial_offset=*point-center;
            const float distance=bullet_velocity_magnitude(radial_offset);
            if (-((native_screen_rect_inner_width_384_56cda4+native_polygon_radius32)/
                  native_screen_half_2_56c8d0)+
                    static_cast<float>(window_state.mesh_view_x(view_index))<=point->x &&
                point->x<=((native_screen_rect_inner_width_384_56cda4+native_polygon_radius32)/
                  native_screen_half_2_56c8d0)+
                    static_cast<float>(window_state.mesh_view_x(view_index)) &&
                static_cast<float>(window_state.mesh_view_y(view_index)-32)<=point->y &&
                point->y<=native_screen_height_448_56d7c0+native_polygon_radius32+
                    static_cast<float>(window_state.mesh_view_y(view_index))) {
                if (native_progress_mesh_radius_120_570ad0<distance) {
                    vertex->channels.alpha=0;
                } else {
                    const float normalized_distance=distance/native_progress_mesh_radius_120_570ad0;
                    vertex->color=0xffffffffu;
                    if (native_progress_mesh_alpha_fade_start_08_573160<normalized_distance) {
                        vertex->channels.alpha=static_cast<std::uint8_t>(
                            static_cast<std::int32_t>(native_screen_alpha_max_56cd9c-
                                ((normalized_distance-native_progress_mesh_alpha_fade_start_08_573160)*
                                 native_screen_alpha_max_56cd9c)/native_progress_mesh_alpha_fade_span_02_56fbf8));
                    }

                    if (timer_44.greater_than(progress_mesh_fade_start_frame)) {
                        const std::int32_t current_frame=static_cast<std::int32_t>(timer_44);
                        const std::int32_t alpha=vertex->channels.alpha;
                        vertex->channels.alpha=static_cast<std::uint8_t>(
                            (alpha*(progress_mesh_lifetime_frames-current_frame))/20);
                    }

                    wave=(native_pi_56e0f0*native_screen_half_2_56c8d0)*normalized_distance;
                    const std::int32_t current_frame=static_cast<std::int32_t>(timer_44);
                    wave-=((static_cast<float>(current_frame)*native_pi_56e0f0)/
                           native_screen_half_2_56c8d0)/static_cast<float>(native_progress_mesh_wave_period_60_56e048);
                    radial_offset.x=scalar_math::sine(static_cast<float>(wave))*
                        normalized_distance*native_progress_mesh_wave_amplitude_05_56e0ec*radial_offset.x;
                    radial_offset.y=scalar_math::sine(static_cast<float>(wave))*
                        normalized_distance*native_progress_mesh_wave_amplitude_05_56e0ec*radial_offset.y;
                    vertex->position+=radial_offset;

                    const float displaced_left=-((native_screen_rect_inner_width_384_56cda4+
                        native_polygon_radius32)/native_screen_half_2_56c8d0)+
                        static_cast<float>(window_state.mesh_view_x(view_index));
                    if (displaced_left<=vertex->position.x) {
                        const float displaced_right=((native_screen_rect_inner_width_384_56cda4+
                            native_polygon_radius32)/native_screen_half_2_56c8d0)+
                            static_cast<float>(window_state.mesh_view_x(view_index));
                        if (displaced_right<vertex->position.x)
                            vertex->position.x=displaced_right;
                    } else {
                        vertex->position.x=-((native_screen_rect_inner_width_384_56cda4+
                            native_polygon_radius32)/native_screen_half_2_56c8d0)+
                            static_cast<float>(window_state.mesh_view_x(view_index));
                    }

                    const float displaced_top=static_cast<float>(window_state.mesh_view_y(view_index)-32);
                    if (displaced_top<=vertex->position.y) {
                        const float displaced_bottom=native_screen_height_448_56d7c0+
                            native_polygon_radius32+
                            static_cast<float>(window_state.mesh_view_y(view_index));
                        if (displaced_bottom<vertex->position.y)
                            vertex->position.y=displaced_bottom;
                    } else {
                        vertex->position.y=static_cast<float>(window_state.mesh_view_y(view_index))+
                            native_screen_negative_32_576360;
                    }
                    vertex->position.z=0.0f;
                    point->z=0.0f;
                }
            } else {
                vertex->channels.alpha=0;
            }
            ++point;
            ++vertex;
        }
    }

    active_mesh->update_strips();
    ++timer_44;
}
}
