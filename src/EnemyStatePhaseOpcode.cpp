#include "EnemyStatePhaseOpcode.hpp"
#include "EnemyState.hpp"
#include "Enemy.hpp"
#include "Session.hpp"

namespace th20 {

bool execute_enemy_phase_opcode(EnemyState& state,
                                 const EclInstruction& instruction,
                                 std::int32_t opcode) {
    switch (opcode) {
    case 514: {
        const char* phase_name = reinterpret_cast<const char*>(&instruction) + 0x20;
        if (session.field_70_is_two() && (state.flags.word_04 & 0x80u)) {
            if (state.field_270 == 0) {
                if (session.clamped_field_1f4() == 7 &&
                    session.clamped_field_1fc() < 41) {
                    auto* receiver = state.entity;
                    const auto time = state.integer_argument(2);
                    const auto index = state.integer_argument(0);
                    receiver->configure_phase(static_cast<std::uint32_t>(index),
                                              0, time, "MBossDead");
                } else {
                    auto* receiver = state.entity;
                    const auto time = state.integer_argument(2);
                    const auto index = state.integer_argument(0);
                    receiver->configure_phase(static_cast<std::uint32_t>(index),
                                              0, time, "BossDead");
                }

                auto* receiver = state.entity;
                const auto timeout_index = state.integer_argument(0);
                receiver->configure_timeout(static_cast<std::uint32_t>(timeout_index),
                                            "BossEscapeSpell");
            } else {
                if (session.clamped_field_1f4() == 7 &&
                    session.clamped_field_1fc() < 41) {
                    auto* receiver = state.entity;
                    const auto time = state.integer_argument(2);
                    const auto index = state.integer_argument(0);
                    receiver->configure_phase(static_cast<std::uint32_t>(index),
                                              0, time, "MBossBDead");
                } else {
                    auto* receiver = state.entity;
                    const auto time = state.integer_argument(2);
                    const auto index = state.integer_argument(0);
                    receiver->configure_phase(static_cast<std::uint32_t>(index),
                                              0, time, "BossDead");
                }

                auto* receiver = state.entity;
                const auto timeout_index = state.integer_argument(0);
                receiver->configure_timeout(static_cast<std::uint32_t>(timeout_index),
                                            "BossEscapeSpell");
            }
        } else {
            const auto life = state.integer_argument(1);
            auto* receiver = state.entity;
            const auto time = state.integer_argument(2);
            const auto index = state.integer_argument(0);
            receiver->configure_phase(static_cast<std::uint32_t>(index), life,
                                      time, phase_name);
        }
        return true;
    }
    case 521: {
        // The original loads Enemy* before evaluating integer operand 0.
        auto* receiver = state.entity;
        const auto index = state.integer_argument(0);
        receiver->configure_timeout(static_cast<std::uint32_t>(index),
            reinterpret_cast<const char*>(&instruction) + 0x18);
        return true;
    }
    default:
        return false;
    }
}

} // namespace th20
