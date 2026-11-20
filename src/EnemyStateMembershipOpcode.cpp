#include "EnemyStateMembershipOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "EnemyController.hpp"

namespace th20 {

bool execute_enemy_membership_opcode(EnemyState& state, std::int32_t opcode) {
    if (opcode != 549)
        return false;

    // The native caches the live controller before the operand read. It then
    // runs the full intrusive-list predicate before resolving destination 0.
    auto* owner = state.context->enemy_controller();
    const auto identifier = state.integer_argument(1);
    const auto found = owner->has_identifier(static_cast<std::uint32_t>(identifier));
    auto* destination = state.integer_argument_destination(0);
    *destination = found ? 1 : 0;
    return true;
}

} // namespace th20
