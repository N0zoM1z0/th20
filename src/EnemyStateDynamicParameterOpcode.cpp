#include "EnemyStateDynamicParameterOpcode.hpp"
#include "EnemyState.hpp"

namespace th20 {

bool execute_enemy_dynamic_parameter_opcode(EnemyState& state, std::int32_t opcode) {
    switch (opcode) {
    case 529:
        switch (state.field_50) {
        case 0: {
            const auto value = state.integer_argument(1);
            *state.integer_argument_destination(0) = value;
            break;
        }
        case 1: {
            const auto value = state.integer_argument(2);
            *state.integer_argument_destination(0) = value;
            break;
        }
        case 2: {
            const auto value = state.integer_argument(3);
            *state.integer_argument_destination(0) = value;
            break;
        }
        case 3: default: {
            const auto value = state.integer_argument(4);
            *state.integer_argument_destination(0) = value;
            break;
        }
        }
        break;
    case 530:
        switch (state.field_50) {
        case 0: {
            const auto value = state.float_argument(1);
            *state.float_argument_destination(0) = value;
            break;
        }
        case 1: {
            const auto value = state.float_argument(2);
            *state.float_argument_destination(0) = value;
            break;
        }
        case 2: {
            const auto value = state.float_argument(3);
            *state.float_argument_destination(0) = value;
            break;
        }
        case 3: default: {
            const auto value = state.float_argument(4);
            *state.float_argument_destination(0) = value;
            break;
        }
        }
        break;
    case 570:
        switch (state.field_50) {
        case 0: {
            const auto value = state.integer_argument(1);
            *state.integer_argument_destination(0) = value;
            break;
        }
        case 1: {
            const auto value = state.integer_argument(2);
            *state.integer_argument_destination(0) = value;
            break;
        }
        case 2: {
            const auto value = state.integer_argument(3);
            *state.integer_argument_destination(0) = value;
            break;
        }
        case 3: {
            const auto value = state.integer_argument(4);
            *state.integer_argument_destination(0) = value;
            break;
        }
        case 4: {
            const auto value = state.integer_argument(5);
            *state.integer_argument_destination(0) = value;
            break;
        }
        case 5: {
            const auto value = state.integer_argument(6);
            *state.integer_argument_destination(0) = value;
            break;
        }
        case 6: {
            const auto value = state.integer_argument(7);
            *state.integer_argument_destination(0) = value;
            break;
        }
        case 7: default: {
            const auto value = state.integer_argument(8);
            *state.integer_argument_destination(0) = value;
            break;
        }
        }
        break;
    case 571:
        switch (state.field_50) {
        case 0: {
            const auto value = state.float_argument(1);
            *state.float_argument_destination(0) = value;
            break;
        }
        case 1: {
            const auto value = state.float_argument(2);
            *state.float_argument_destination(0) = value;
            break;
        }
        case 2: {
            const auto value = state.float_argument(3);
            *state.float_argument_destination(0) = value;
            break;
        }
        case 3: {
            const auto value = state.float_argument(4);
            *state.float_argument_destination(0) = value;
            break;
        }
        case 4: {
            const auto value = state.float_argument(5);
            *state.float_argument_destination(0) = value;
            break;
        }
        case 5: {
            const auto value = state.float_argument(6);
            *state.float_argument_destination(0) = value;
            break;
        }
        case 6: {
            const auto value = state.float_argument(7);
            *state.float_argument_destination(0) = value;
            break;
        }
        case 7: default: {
            const auto value = state.float_argument(8);
            *state.float_argument_destination(0) = value;
            break;
        }
        }
        break;
    default:
        return false;
    }
    return true;
}

} // namespace th20
