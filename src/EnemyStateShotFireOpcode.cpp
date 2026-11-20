#include "EnemyStateShotFireOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "Bullet.hpp"

namespace th20 {

bool execute_enemy_shot_fire_opcode(EnemyState& state, std::int32_t opcode) {
    switch (opcode) {
    case 600: {
        const auto selector = state.integer_argument(0);
        auto selected = state.writable_shot(static_cast<std::uint32_t>(selector));
        auto& record = *selected.first;
        auto& metadata = *selected.second;

        // These value lifetimes are native: ShotParameters is copied into the
        // record; a fresh EtamaArgInf move-assigns the PMR owner, preserving
        // its default sound IDs and its two value-initialized commands.
        record.parameters = ShotParameters{};
        metadata = ShotMetadata{};

        record.vector_34.x = 0.0f;
        record.vector_34.y = 0.0f;
        record.vector_40.x = 0.0f;
        record.vector_40.y = 0.0f;
        record.vector_40.z = 0.0f;
        // vector_34.z at +0x3C is deliberately not reset.
        record.field_30 = 0;
        return true;
    }
    case 601: {
        const auto selector = state.integer_argument(0);
        auto selected = state.shared_shot(static_cast<std::uint32_t>(selector));
        auto& record = *selected.first;

        if (record.vector_40.z > 0.9f) {
            record.parameters.position = record.vector_40 + record.vector_34;
            record.parameters.position.z = 0.0f;
        } else {
            record.parameters.position = state.position_ref() + record.vector_34;
        }

        // The original intentionally queries the live Context three times.
        // Do not cache the controller: fire callbacks may retarget Context,
        // and the final zero reset must affect the post-fire current owner.
        state.context->bullet_controller()->set_scalar_48(state.field_274);
        state.context->bullet_controller()->fire(record.parameters, record.owner);
        state.context->bullet_controller()->set_scalar_48(0.0f);
        return true;
    }
    default:
        return false;
    }
}

} // namespace th20
