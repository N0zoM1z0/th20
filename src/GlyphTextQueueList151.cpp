// Original 151B native glyph-task list insertion under 56B queue bridge.
// SOURCE-PRESENT, NONEXACT: the real std::pmr::list function ownership is
// identified by nested 59/124B helpers. Original 151B _Emplace, 158B
// node-emplacement constructor and 118B guard cleanup are distinct real
// stages: modern C++20 emits 130B/143B for the first two (NONEXACT),
// while the third is WHOLE EXACT 118B plus five actual INT3 alignment bytes.
// The original constructors retain additional live std::_Unfancy calls.
#include <functional>
#include <list>
#include <memory>
#include <memory_resource>
#include <utility>
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
