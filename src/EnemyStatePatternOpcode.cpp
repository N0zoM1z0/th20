#include "EnemyStatePatternOpcode.hpp"
#include "EnemyState.hpp"
#include "Enemy.hpp"
#include "Session.hpp"

namespace th20 {

bool execute_enemy_pattern_opcode(EnemyState& state, std::int32_t opcode) {
    switch (opcode) {
    case 506:
        state.pattern.clear_counts();
        break;
    case 507:
    case 567: {
        const auto kind = static_cast<std::uint32_t>(state.integer_argument(0));
        const auto value = static_cast<std::uint32_t>(state.integer_argument(1));
        if (opcode == 507)
            state.pattern.set_count(kind, value);
        else
            state.pattern.set_extra_count(kind, value);
        break;
    }
    case 572: {
        const auto kind = state.integer_argument(0);
        state.pattern.set_bomb_kind(kind);
        break;
    }
    case 568: {
        const auto duration = static_cast<std::uint32_t>(state.integer_argument(0));
        state.pattern.set_duration(duration);
        break;
    }
    case 508: {
        // Native reads float operand 1 before operand 0, then stores X/Y.
        const float y = state.float_argument(1);
        const float x = state.float_argument(0);
        state.pattern.set_radii(x, y);
        break;
    }
    case 509:
        // This two-player guard precedes every Enemy/Pattern owner access.
        if (session.field_70_is_two())
            break;
        [[fallthrough]];
    case 556: {
        const bool bomb_mark = state.entity->bomb_drop_disabled();
        const auto& origin = state.position_ref();
        state.pattern.drop(origin, bomb_mark);
        break;
    }
    case 510: {
        const auto kind = state.integer_argument(0);
        state.pattern.set_base_kind(kind);
        break;
    }
    default:
        return false;
    }
    return true;
}

} // namespace th20
