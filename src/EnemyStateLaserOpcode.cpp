#include "EnemyStateLaserOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "LaserParameters.hpp"
#include "Angle.hpp"

namespace th20 {

// Native opcode 704 is a separate lookup/mutation fragment from the four
// queued-shot creation cases below. Keep its Context capture, handle lookup,
// Vector3 construction and VM operand order explicit in its own source helper.
bool execute_enemy_laser_lookup_opcode(EnemyState& state, std::int32_t opcode) {
    if (opcode != 704) return false;
    auto* const controller = state.context->laser_controller();
    const auto handle = state.integer_argument(0);
    auto* const laser = controller->find_laser(handle);
    Vector3 position;
    position.x = state.float_argument(1);
    position.y = state.float_argument(2);
    if (laser != nullptr) {
        position.z = 0.0f;
        laser->set_position(position);
    }
    return true;
}

// The four creation branches share the queued-shot COW protocol, command-
// vector copy, Context Laser owner and common Laser factory. Their native case
// bodies are inline in the 41,967B EnemyState::execute_opcode Boss.
bool execute_enemy_laser_mutation_opcode(EnemyState& state, std::int32_t opcode) {
    switch (opcode) {
    case 705: {
        auto* const controller = state.context->laser_controller();
        const auto handle = state.integer_argument(0);
        auto* const laser = controller->find_laser(handle);
        Vector3 value;
        value.x = state.float_argument(1);
        value.y = state.float_argument(2);
        if (laser != nullptr) {
            value.z = 0.0f;
            laser->set_parameter_vector_704(value);
        }
        return true;
    }
    case 706:
    case 707:
    case 708:
    case 709: {
        auto* const controller = state.context->laser_controller();
        const auto handle = state.integer_argument(0);
        auto* const laser = controller->find_laser(handle);
        if (laser == nullptr) return true;

        const float value = state.float_argument(1);
        switch (opcode) {
        case 706: laser->set_field_7c(value); break;
        case 707: laser->set_speed(value); break;
        case 708: laser->set_angle(value); break;
        case 709: laser->set_parameter_field_714(value); break;
        }
        return true;
    }
    case 710: {
        auto* const controller = state.context->laser_controller();
        const auto handle = state.integer_argument(0);
        auto* const laser = controller->find_laser(handle);
        if (laser != nullptr) {
            (void)laser->erase(0, 0);
            laser->set_handle(0);
        }
        return true;
    }
    default:
        return false;
    }
}

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
