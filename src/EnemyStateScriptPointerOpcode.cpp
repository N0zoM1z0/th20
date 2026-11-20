#include "EnemyStateScriptPointerOpcode.hpp"
#include "EnemyState.hpp"

namespace th20 {

bool execute_enemy_script_pointer_opcode(EnemyState& state,
                                          const EclInstruction& instruction,
                                          std::int32_t opcode) {
    if (opcode != 632)
        return false;

    // Read both ECL indexes before invoking the writable COW selector.
    const auto record_index = state.integer_argument(0);
    const auto command_index = state.integer_argument(1);
    auto selected = state.writable_shot(static_cast<std::uint32_t>(record_index));
    auto& metadata = *selected.second;

    const auto index = static_cast<std::uint32_t>(command_index);
    const std::uint32_t required_size = index + 1u;
    if (metadata.commands.size() < required_size)
        metadata.commands.resize(required_size);

    // The script is borrowed from the live ECL packet, not copied or allocated.
    // It points to the fourth trailing payload word at EclInstruction + 0x1C.
    metadata.commands[index].script =
        reinterpret_cast<const char*>(&instruction) + 0x1c;
    return true;
}

} // namespace th20
