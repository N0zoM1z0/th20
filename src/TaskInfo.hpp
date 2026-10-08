#pragma once

#include "FunctionChain.hpp"

namespace th20 {

// REF-003: TaskInf RTTI, three virtual slots, flags and two callback nodes.
// Construction clears the flag word before setting bit 1. Allocator-based
// deletion and process callback registration remain open.
struct TaskFlagWord { std::uint32_t bits; };

class TaskInfo {
public:
    TaskInfo() noexcept;
    virtual ~TaskInfo();
    virtual void enable();
    virtual void disable();

    void enable_callbacks();
    void disable_callbacks();

    union { std::uint32_t flags; TaskFlagWord flag_word; };
    FunctionChainNode* update_node;
    FunctionChainNode* draw_node;
};

static_assert(sizeof(void*) != 4 || sizeof(TaskInfo) == 16);

} // namespace th20
