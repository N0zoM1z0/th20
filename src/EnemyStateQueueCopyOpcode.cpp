#include "EnemyStateQueueCopyOpcode.hpp"
#include "EnemyState.hpp"
#include <iterator>

namespace th20 {

bool execute_enemy_queue_copy_opcode(EnemyState& state, std::int32_t opcode) {
    if (opcode != 614)
        return false;

    // Both VM operands are evaluated before the forward_list is mutated.
    const auto destination_index =
        static_cast<std::uint32_t>(state.integer_argument(0));
    const auto source_index =
        static_cast<std::uint32_t>(state.integer_argument(1));
    auto& queue = state.queued;

    const std::uint32_t destination_required = destination_index + 1u;
    auto destination_end = queue.end();
    auto destination_begin = queue.begin();
    if (static_cast<std::uint32_t>(std::distance(destination_begin, destination_end))
        < destination_required) {
        queue.resize(destination_required);
    }

    const std::uint32_t source_required = source_index + 1u;
    auto source_end = queue.end();
    auto source_begin = queue.begin();
    if (static_cast<std::uint32_t>(std::distance(source_begin, source_end))
        < source_required) {
        queue.resize(source_required);
    }

    auto destination = queue.begin();
    std::advance(destination, static_cast<std::ptrdiff_t>(destination_index));
    auto source = queue.begin();
    std::advance(source, static_cast<std::ptrdiff_t>(source_index));

    // The original is a full typed 76-byte record copy assignment, not swap,
    // raw memcpy, or ShotParameters-only assignment. The accepted 119B method
    // copies the shared_ptr owner and both vectors as part of the record.
    *destination = *source;
    return true;
}

} // namespace th20
