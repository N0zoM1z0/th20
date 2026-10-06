#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {

struct FunctionChainNode;
struct FunctionChainList;
struct FunctionChainIterator;

// REF-002: pointer slots checked against link initialization and mutations.
struct FunctionChainLink {
    FunctionChainNode* node;
    FunctionChainLink* next;
    FunctionChainLink* previous;
    FunctionChainList* owner;
    FunctionChainIterator* iterator;

    explicit FunctionChainLink(FunctionChainNode* value = nullptr);
    void insert_after(FunctionChainLink* added);
    void insert_before(FunctionChainLink* added);
};

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
