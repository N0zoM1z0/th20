#pragma once

#include <cstddef>
#include <cstdint>
#include <memory_resource>
#include <stack>
#include <vector>

namespace th20 {

// Shared menu value owner. Native construction, iterator operations and
// stack adapters establish these containers independently of byte matching.
struct Cursor {
    std::int32_t current;
    std::int32_t previous;
    std::int32_t count;
    std::int32_t minimum;
    std::pmr::vector<std::int32_t> excluded;
    std::stack<std::int32_t> selection_history;
    std::stack<std::int32_t> count_history;
    std::int32_t wrapping;

    // Construction is source present; native EH emission remains unresolved.
    Cursor();
    ~Cursor();
    void snapshot();
    std::int32_t changed() const;
    std::int32_t selected(std::int32_t index) const;
    void set_count(std::int32_t value);
    void set_wrapping(std::int32_t value);
    void save();
    void restore();
};

#if defined(_MSC_VER) && defined(_M_IX86)
static_assert(sizeof(Cursor) == 0x4C);
static_assert(offsetof(Cursor, excluded) == 0x10);
static_assert(offsetof(Cursor, selection_history) == 0x20);
static_assert(offsetof(Cursor, count_history) == 0x34);
static_assert(offsetof(Cursor, wrapping) == 0x48);
#endif

} // namespace th20
