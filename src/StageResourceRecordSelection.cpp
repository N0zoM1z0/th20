#include "StageResource.hpp"

namespace th20 {

// Native 0x004773C0 walks the variable-length records at owner+0x3330.
// The original type/name is unknown; only this 12-byte instruction prefix and
// the ScriptState Timer/instruction-offset members are established by the native body.
void StageResourceOwner::select_record(std::int32_t identifier) {
    const auto* current =
        reinterpret_cast<const StageResourceInstructionHeader*>(instructions);
    while (current->time >= 0) {
        if (current->opcode == 0x10 && current->arguments[0] == identifier) {
            script_state.instruction_offset = static_cast<std::uint32_t>(
                reinterpret_cast<const std::byte*>(current) -
                reinterpret_cast<const std::byte*>(instructions));
            script_state.timer = *reinterpret_cast<const std::int32_t*>(
                reinterpret_cast<const std::byte*>(instructions) +
                script_state.instruction_offset);
            break;
        }
        current = reinterpret_cast<const StageResourceInstructionHeader*>(
            reinterpret_cast<const std::byte*>(current) + current->size);
    }
}

} // namespace th20
