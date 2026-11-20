#include "EnemyStateAnimationSpawnOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "EnemyController.hpp"
#include "AnimationFile.hpp"
#include "SoundInf.hpp"
#include "CollisionGeometry.hpp"

namespace th20 {

extern SoundInf process_sound;
extern const float native_progress_mesh_alpha_fade_span_02_56fbf8;
extern const float native_negative_pi_56e0f8;
extern const float native_screen_half_2_56c8d0;

bool execute_enemy_animation_spawn_opcode(EnemyState& state, std::int32_t opcode) {
    if (opcode != 555)
        return false;

    if (state.field_250 >= 0) {
        // Motion::position_x is the same 16B first-float getter body as the
        // original folded ClockScalar conversion at 0x004292E0.
        const float x = state.motion_110.position_x();
        const auto sound = state.field_250;
        process_sound.request_effect_at(sound, x);
    }

    if (state.field_254 >= 0) {
        const float distance = geometry::squared_distance_xy(
            state.vector_6c, state.position_ref());
        // Use the original PE constants, not newly synthesized float literals.
        const float direction =
            native_progress_mesh_alpha_fade_span_02_56fbf8 *
                native_progress_mesh_alpha_fade_span_02_56fbf8 > distance
            ? native_negative_pi_56e0f8 / native_screen_half_2_56c8d0
            : geometry::direction_xy(state.vector_6c, state.position_ref());

        auto* owner = state.context->enemy_controller();
        auto* file = owner->animation_file(state.field_258);
        auto& position = state.position_ref();
        const auto script = state.field_254;
        (void)file->spawn(nullptr, script, position, direction, 3, nullptr);
    }
    return true;
}

} // namespace th20
