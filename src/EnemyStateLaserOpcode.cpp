#include "EnemyStateLaserOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "LaserParameters.hpp"
#include "Angle.hpp"

namespace th20 {

// The four branches are kept together because the original parent shares the
// same queued-shot COW protocol, command-vector copy, Context Laser owner and
// common Laser factory. Their native case bodies are inline in the 41,967B Boss.
bool execute_enemy_laser_opcode(EnemyState& state, std::int32_t opcode) {
    switch (opcode) {
    case 702: {
        LaserType0Parameters laser;
        const auto selector = state.integer_argument(0);
        auto selected = state.writable_shot(static_cast<std::uint32_t>(selector));
        auto& record = *selected.first;
        auto& metadata = *selected.second;

        laser.commands = metadata.commands;
        if (record.vector_40.z > 0.9f) {
            laser.position = record.vector_40 + record.vector_34;
            laser.position.z = 0.0f;
        } else {
            laser.position = state.position_ref() + record.vector_34;
        }
        laser.type = record.parameters.type;
        laser.color = record.parameters.color;
        laser.angle = normalize_angle(record.parameters.angle);
        laser.speed = record.parameters.speed;
        laser.field_14 = record.parameters.position.x;
        laser.length = record.parameters.position.y;
        laser.length_limit = record.parameters.position.z;
        laser.width = metadata.field_14;
        laser.flags = metadata.field_34 | 1u;
        laser.field_48 = metadata.sound;
        laser.field_4c = metadata.alternate_sound;
        laser.radial_offset = metadata.field_00;
        laser.view_index = static_cast<std::int32_t>(state.field_2e8);

        (void)state.context->laser_controller()->create_laser(0, &laser);
        return true;
    }
    case 703: {
        LaserType1Parameters laser;
        const auto selector = state.integer_argument(0);
        auto selected = state.writable_shot(static_cast<std::uint32_t>(selector));
        auto& record = *selected.first;
        auto& metadata = *selected.second;

        laser.commands = metadata.commands;
        if (record.vector_40.z > 0.9f) {
            laser.position = record.vector_40 + record.vector_34;
            laser.position.z = 0.0f;
        } else {
            laser.position = state.position_ref() + record.vector_34;
        }
        laser.type = record.parameters.type;
        laser.color = record.parameters.color;
        laser.angle = normalize_angle(record.parameters.angle);
        laser.growth_speed = record.parameters.speed;
        laser.length = record.parameters.position.x;
        laser.length_limit = record.parameters.position.y;
        laser.width = metadata.field_14;
        laser.delay = static_cast<std::int32_t>(metadata.field_24);
        laser.grow_time = static_cast<std::int32_t>(metadata.field_28);
        laser.sustain_time = static_cast<std::int32_t>(metadata.field_2c);
        laser.shrink_time = static_cast<std::int32_t>(metadata.field_30);
        laser.flags = metadata.field_34 | 2u;
        laser.sound = metadata.sound;
        laser.field_44 = metadata.alternate_sound;
        laser.radial_offset = metadata.field_00;
        // The original 703 branch reads integer operand 1 after the metadata
        // and parameter fields have been copied, preserving VM operand order.
        laser.handle = static_cast<std::uint32_t>(state.integer_argument(1));
        laser.view_index = static_cast<std::int32_t>(state.field_2e8);

        (void)state.context->laser_controller()->create_laser(1, &laser);
        return true;
    }
    case 711: {
        LaserType2Parameters laser;
        const auto selector = state.integer_argument(0);
        auto selected = state.writable_shot(static_cast<std::uint32_t>(selector));
        auto& record = *selected.first;
        auto& metadata = *selected.second;

        laser.commands = metadata.commands;
        if (record.vector_40.z > 0.9f) {
            laser.position = record.vector_40 + record.vector_34;
            laser.position.z = 0.0f;
        } else {
            laser.position = state.position_ref() + record.vector_34;
        }
        laser.type = record.parameters.type;
        laser.color = record.parameters.color;
        laser.angle = normalize_angle(record.parameters.angle);
        laser.speed = record.parameters.speed;
        laser.count = metadata.field_24;
        laser.width = metadata.field_14;
        laser.radial_offset = metadata.field_00;
        // The native type-2 constructor zeroes flags, then the case ORs bit 0.
        laser.flags.word = 1u;
        laser.sound = metadata.sound;
        laser.motion_sound = metadata.alternate_sound;
        laser.view_index = static_cast<std::int32_t>(state.field_2e8);

        (void)state.context->laser_controller()->create_laser(2, &laser);
        return true;
    }
    case 713: {
        LaserType3Parameters laser;
        const auto selector = state.integer_argument(0);
        auto selected = state.writable_shot(static_cast<std::uint32_t>(selector));
        auto& record = *selected.first;
        auto& metadata = *selected.second;

        laser.commands = metadata.commands;
        if (record.vector_40.z > 0.9f) {
            laser.position = record.vector_40 + record.vector_34;
            laser.position.z = 0.0f;
        } else {
            laser.position = state.position_ref() + record.vector_34;
        }
        laser.field_2c = record.parameters.color;
        laser.angle = normalize_angle(record.parameters.angle);
        laser.field_34 = metadata.field_24;
        laser.field_24 = metadata.field_14;
        laser.field_20 = record.parameters.position.z;
        laser.field_30 = metadata.field_00;
        laser.handle = static_cast<std::uint32_t>(state.integer_argument(1));
        laser.view_index = static_cast<std::int32_t>(state.field_2e8);

        (void)state.context->laser_controller()->create_laser(3, &laser);
        return true;
    }
    default:
        return false;
    }
}

} // namespace th20
