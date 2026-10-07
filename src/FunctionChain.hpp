#pragma once

#include "IntrusiveLink.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {

struct FunctionChainNode;
using FunctionChainList = IntrusiveList<FunctionChainNode>;
using FunctionChainIterator = IntrusiveIterator<FunctionChainNode>;
using FunctionChainLink = IntrusiveLink<FunctionChainNode>;

// The x86 compile profile explicitly selects the default __cdecl convention.
using FunctionChainCallback = std::int32_t (*)(void*);

// Storage view and field operations; allocation, construction, destruction
// and dispatch ownership are still being reconstructed separately.
struct FunctionChainNode {
    std::int32_t priority;
    std::uint32_t flags;
    FunctionChainCallback callback;
    FunctionChainCallback before_insert;
    FunctionChainCallback on_shutdown;
    FunctionChainLink link;
    void* userdata;

    void set_callback(FunctionChainCallback value);
    void set_userdata(void* value);
    void set_owned();
    void enable();
    void disable();
    void set_before_insert(FunctionChainCallback value);
    void set_shutdown_callback(FunctionChainCallback value);
    void clear_callbacks();
};

static_assert(sizeof(void*) != 4 || sizeof(FunctionChainLink) == 20);
static_assert(sizeof(void*) != 4 || sizeof(FunctionChainNode) == 44);
static_assert(sizeof(void*) != 4 || offsetof(FunctionChainNode, callback) == 8);
static_assert(sizeof(void*) != 4 || offsetof(FunctionChainNode, link) == 20);
static_assert(sizeof(void*) != 4 || offsetof(FunctionChainNode, userdata) == 40);

} // namespace th20
