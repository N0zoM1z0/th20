#include "EnemyController.hpp"
#include "Context.hpp"
#include "DiagnosticAllocator.hpp"
#include "EnemySpawn.hpp"

namespace th20 {
union EclOperand { std::int32_t integer; float real; };

// Instruction operands follow the fixed 16-byte header. Operand zero stores
// the padded script-name byte count; the script name begins at operand one,
// and default values follow the padded name payload.
#define SPAWN_INTEGER(ins, index) (reinterpret_cast<std::int32_t*>((ins) + 1)[index])
// The identity cast preserves the native MSVC outgoing float-slot reservation
// before the operand load at both float_argument_value call sites.
#define SPAWN_FLOAT(ins, index) static_cast<float>(reinterpret_cast<EclOperand*>((ins) + 1)[index].real)

int EnemyState::spawn_from_opcode() {
    if (context->enemy_controller()->count() >= context->enemy_controller()->capacity())
        return 0;
    auto* instruction = entity->current_instruction();
    auto words = (SPAWN_INTEGER(instruction, 0) + 4) / 4;
    EnemySpawn parameters;
    parameters.position.x = float_argument_value(1, SPAWN_FLOAT(instruction, words));
    parameters.position.y = float_argument_value(2, SPAWN_FLOAT(instruction, words + 1));
    if (instruction->opcode == 300 || instruction->opcode == 309 ||
        instruction->opcode == 321 || instruction->opcode == 311 || instruction->opcode == 304) {
        parameters.position.x = motion_110.position_x() + parameters.position.x;
        parameters.position.y = motion_110.position_y() + parameters.position.y;
    }
    if (instruction->opcode == 311 || instruction->opcode == 304 ||
        instruction->opcode == 312 || instruction->opcode == 305)
        parameters.flags_18 = 1;
    if ((flags.word_04 >> 3) & 1) {
        parameters.position.x *= -1.0f;
        parameters.flags_18 ^= 1;
    }
    parameters.health = integer_argument_value(3, SPAWN_INTEGER(instruction, words + 2));
    parameters.field_0c = integer_argument_value(4, SPAWN_INTEGER(instruction, words + 3));
    parameters.field_10 = integer_argument_value(5, SPAWN_INTEGER(instruction, words + 4));
    parameters.variables = counters;
    auto& enemy = *entity;
    parameters.field_50 = enemy.identifier_value();
    auto& controller = *context->enemy_controller();
    controller.create(reinterpret_cast<const char*>(&SPAWN_INTEGER(instruction, 1)),
                      parameters, ((flags.word_08 >> 2) & 1) ? entity : nullptr);
    return 0;
}

#undef SPAWN_INTEGER
#undef SPAWN_FLOAT


} // namespace th20
