#pragma once

#include "FunctionChain.hpp"

namespace th20 {

// REF-003: TaskInf RTTI, three virtual slots, flags and two callback nodes.
// Implicit construction preserves the observed defaults; its original code
// contribution and allocator-based deletion still require reconstruction.
class TaskInfo {
public:
    virtual ~TaskInfo();
    virtual void enable();
    virtual void disable();

    void enable_callbacks();
    void disable_callbacks();

    std::uint32_t flags = 2;
    FunctionChainNode* update_node = nullptr;
    FunctionChainNode* draw_node = nullptr;
};

static_assert(sizeof(void*) != 4 || sizeof(TaskInfo) == 16);

} // namespace th20
