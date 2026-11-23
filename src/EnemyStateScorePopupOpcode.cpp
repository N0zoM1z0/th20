#include "EnemyStateScorePopupOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "ItemRewardPopupQueue.hpp"
#include "Session.hpp"

namespace th20 {

bool execute_enemy_score_popup_opcode(EnemyState& state, std::int32_t opcode) {
    if (opcode != 630)
        return false;

    const auto amount = state.integer_argument(0);
    session.add_score(static_cast<std::uint32_t>(amount));

    auto* queue = state.context->item_reward_popup_queue();
    auto& position = state.position_ref();
    queue->enqueue(&position, -1, static_cast<std::uint32_t>(amount));
    return true;
}

} // namespace th20
