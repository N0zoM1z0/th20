#include "EnemyStateAnimationSpawnOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "EnemyController.hpp"
#include "AnimationFile.hpp"
#include "SoundInf.hpp"
#include "CollisionGeometry.hpp"

namespace th20 {

extern SoundInf process_sound;
constexpr float enemy_nearby_spawn_pi = 3.1415927410125732f;

bool execute_enemy_animation_spawn_opcode(EnemyState& state, std::int32_t opcode) {
    if (opcode != 555)
        return false;

    if (state.field_250 >= 0) {
        const float x = state.motion_110.position_x();
        const auto sound = state.field_250;
        process_sound.request_effect_at(sound, x);
    }

    if (state.field_254 >= 0) {
        const float distance = geometry::squared_distance_xy(
            state.vector_6c, state.position_ref());
        const float direction = 0.2f * 0.2f > distance
            ? -enemy_nearby_spawn_pi / 2.0f
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
