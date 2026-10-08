#include "EclRuntime.hpp"
#include "DiagnosticAllocator.hpp"
namespace th20 {
int EclManager::spawn(std::int32_t async_id, std::int32_t argument_skip) {
    auto* runtime = process_allocator->allocate_object<EclRuntime>("D:\\cygwin\\home\\zun\\prog\\th20\\src\\script\\sptcmd.cpp:1013 SptBaseInf");
    auto* link = process_allocator->allocate_object<IntrusiveLink<EclRuntime>>("D:\\cygwin\\home\\zun\\prog\\th20\\src\\script\\sptcmd.cpp:1014 LinkInf<SptBaseInf*>");
    runtime->manager = this;
    runtime->time = 0.0f;
    runtime->position.offset = -1;
    runtime->position.subroutine = -1;
    runtime->async_id = async_id;
    runtime->rank = current_runtime->rank;
    link->initialize(runtime);
    auto& head = runtimes;
    head.insert_after(link);
    auto* caller = current_runtime;
    int result = caller->call_into(runtime, argument_skip, 0);
    return result;
}
IntrusiveLink<EclRuntime>* EclManager::find_runtime(std::int32_t async_id) {
    auto* link = &runtimes;
    while (link) {
        auto* next = link->next_value();
        if (link->node_value()->async_id == async_id) return link;
        link = next;
    }
    return nullptr;
}
void EclManager::invalidate_async() {
    auto* link = runtimes.next_value();
    while (link) {
        auto* next = link->next_value();
        link->node_value()->position.offset = -1;
        link->node_value()->position.subroutine = -1;
        link = next;
    }
}
}
