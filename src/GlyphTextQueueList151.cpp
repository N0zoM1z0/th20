// Genuine glyph-task PMR list insertion and allocator construction.
// The native forwarding calls use the shared eight-byte identity leaf.
// Keep this function specialization out of line, as in the original
// list insertion, node construction and allocator-traits callers.
#include "NativeGlyphTaskAllocator.hpp"
#include <memory>
#include <utility>
template __declspec(noinline) std::function<void()>&&
std::forward<std::function<void()>>(std::function<void()>&) noexcept;

namespace th20 {
using NativeGlyphPendingTasks = std::pmr::list<std::function<void()>>;

// This natural source instantiates the actual list::insert/_Emplace and node
// allocation/transfer/cleanup graph. The original 151B body is a separate
// native template owner; no fake constructor, custom node, or raw iterator
// reinterpret-cast is introduced to pretend a precise original ABI match.
NativeGlyphPendingTasks::iterator glyph_task_list_insert(
    NativeGlyphPendingTasks& queue,
    NativeGlyphPendingTasks::const_iterator position,
    std::function<void()>& task) {
    return queue.emplace(position, std::move(*std::_Unfancy(&task)));
}

// The original 56B bridge forwards its existing function to the head of the
// pending list. Keeping this meaningful real list call visible also forces
// all nested MSVC PMR allocator/transfer helper implementations into the
// same translation unit, enabling independent complete function receipts.
void glyph_task_list_append(NativeGlyphPendingTasks& queue,
                            std::function<void()>& task) {
    glyph_task_list_insert(queue, queue.cend(), task);
}
} // namespace th20
