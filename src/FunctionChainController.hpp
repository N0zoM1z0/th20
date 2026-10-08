#pragma once
#include "FunctionChain.hpp"
#include "LockRegistry.hpp"
#include "DiagnosticAllocator.hpp"

namespace th20 {
// Complete native owner storage; process construction and shutdown are open.
class FunctionChainController {
public:
    FunctionChainLink* current;
    FunctionChainList update_chain, draw_chain;
    std::uint32_t shutting_down;
    FunctionChainController();
    FunctionChainNode* create(FunctionChainCallback callback);
    void remove_unlocked(FunctionChainNode* node);
    void remove(FunctionChainNode* node);
    std::int32_t insert_update(FunctionChainNode* node, std::int32_t priority);
    std::int32_t insert_draw(FunctionChainNode* node, std::int32_t priority);
    std::int32_t update();
    std::int32_t draw();
};
extern FunctionChainController* process_chain;
FunctionChainNode* register_update(std::int32_t priority, FunctionChainCallback callback, void* userdata);
FunctionChainNode* register_update_disabled(std::int32_t priority, FunctionChainCallback callback, void* userdata);
FunctionChainNode* register_draw(std::int32_t priority, FunctionChainCallback callback, void* userdata);
FunctionChainNode* register_draw_disabled(std::int32_t priority, FunctionChainCallback callback, void* userdata);
#if defined(_M_IX86)
static_assert(sizeof(FunctionChainController)==56);
static_assert(offsetof(FunctionChainController,update_chain)==4);
static_assert(offsetof(FunctionChainController,draw_chain)==0x1c);
static_assert(offsetof(FunctionChainController,shutting_down)==0x34);
#endif
}
