#include "EnemyStateCardStartOpcode.hpp"
#include "EnemyState.hpp"
#include "EclRuntime.hpp"
#include "Context.hpp"
#include "Card.hpp"
#include "Session.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {

bool execute_enemy_card_start_opcode(EnemyState& state,
                                     const EclInstruction& instruction,
                                     std::int32_t opcode) {
    switch (opcode) {
    case 522:
    case 528:
    case 531:
    case 532:
    case 533:
        break;
    default:
        return false;
    }

    // The length is the fourth raw packet word, not a consuming VM read.
    const auto* packet = reinterpret_cast<const std::byte*>(&instruction);
    const auto string_length =
        *reinterpret_cast<const std::int32_t*>(packet + 0x1c);
    auto* input = reinterpret_cast<const std::uint8_t*>(packet + 0x20);

    // Preserve the native 128-byte zeroed local and byte-wise rolling XOR.
    char decoded[128]{};
    std::uint8_t key = 0x77;
    std::uint8_t step = 7;
    for (std::int32_t i = 0; i < string_length; ++i) {
        decoded[i] = static_cast<char>(*input++ ^ key);
        key = static_cast<std::uint8_t>(key + step);
        step = static_cast<std::uint8_t>(step + 0x10u);
    }

    // Read operand 0 before consulting the instruction's actual opcode word.
    auto index = static_cast<std::uint32_t>(state.integer_argument(0));
    switch (instruction.opcode) {
    case 531:
        index += static_cast<std::uint32_t>(session.mode());
        break;
    case 532:
        index = index + static_cast<std::uint32_t>(session.mode()) - 1u;
        break;
    case 533:
        index = index + static_cast<std::uint32_t>(session.mode()) - 2u;
        break;
    }

    // Cache the live Card owner before the remaining VM reads can retarget it.
    auto* receiver = state.context->card();
    const auto arg_3 = state.integer_argument(2);
    const auto duration = state.integer_argument(1);
    receiver->start_spell(static_cast<std::int32_t>(index), decoded,
                          duration, arg_3);

    state.health.set_scaled_enabled(1);
    auto* health = &state.health;
    health->set_scaled_health(state.health.get_health());
    state.timer_a8 = 0;
    return true;
}

} // namespace th20
