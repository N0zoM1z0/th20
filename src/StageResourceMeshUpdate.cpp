#include "StageResource.hpp"
#include "Angle.hpp"
#include "RenderMesh.hpp"
#include "ScalarMath.hpp"

#include <bit>
#include <cstdint>

namespace th20 {
extern const float native_pi_56e0f0;
extern const float native_mesh_origin_x_56fa6c;
extern const float native_mesh_phase_column_56fa20;
extern const float native_mesh_phase_row_56fa24;
extern const float native_mesh_frame_x_56fa28;
extern const float native_mesh_frame_y_56fa30;
extern const float native_mesh_amplitude_24_56f7b4;
extern const float native_screen_height_128_56cd98;
extern const float native_screen_rect_inner_width_384_56cda4;
extern const float native_screen_height_448_56d7c0;

void __fastcall StageBackgroundFogOwner::update_meshes() {
    for (std::int32_t mesh_index = 0; mesh_index < 2; ++mesh_index) {
        auto* mesh = reinterpret_cast<RenderMesh*>(
            static_cast<std::uintptr_t>(fields_3294[9 + mesh_index]));
        if (mesh == nullptr || (mesh_mode != 1 && mesh_mode != 2))
            continue;

        mesh->initialize(native_mesh_origin_x_56fa6c, 0.0f,
                         native_screen_rect_inner_width_384_56cda4,
                         mesh_mode == 1 ? native_screen_height_128_56cd98 :
                                          native_screen_height_448_56d7c0);

        Angle phase_x;
        phase_x.value = mesh_phase_x[mesh_index];
        Angle phase_y;
        phase_y.value = mesh_phase_y[mesh_index];
        auto* vertex = mesh->vertices;
        auto* position = mesh->positions;
        for (std::int32_t column = 0; column < mesh->columns; ++column) {
            for (std::int32_t row = 0; row < mesh->rows; ++row) {
                vertex->channels.alpha = 0xc0;
                const float row_weight = native_mesh_amplitude_24_56f7b4 -
                    (static_cast<float>(row) * native_mesh_amplitude_24_56f7b4) /
                    static_cast<float>(mesh->rows - 1);
                if (column != 0 && row != 0 &&
                    column != mesh->columns - 1 && row != mesh->rows - 1) {
                    const Vector3 displacement{
                        scalar_math::sine(phase_x.value) * row_weight,
                        scalar_math::sine(phase_y.value) * row_weight,
                        0.0f};
                    vertex->position += displacement;
                    vertex->position.z = 0.0f;
                    position->z = 0.0f;
                }
                phase_x += native_pi_56e0f0 / native_mesh_phase_row_56fa24;
                ++vertex;
                ++position;
            }
            phase_y -= native_pi_56e0f0 / native_mesh_phase_column_56fa20;
        }

        phase_x.value = mesh_phase_x[mesh_index];
        phase_x += native_pi_56e0f0 / native_mesh_frame_x_56fa28;
        mesh_phase_x[mesh_index] = phase_x.value;
        phase_y.value = mesh_phase_y[mesh_index];
        phase_y += native_pi_56e0f0 / native_mesh_frame_y_56fa30;
        mesh_phase_y[mesh_index] = phase_y.value;
        if (mesh_mode == 2)
            ++mesh_timers[mesh_index];
    }
}

} // namespace th20
