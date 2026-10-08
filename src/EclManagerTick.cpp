#include "EclRuntime.hpp"
#include "DiagnosticAllocator.hpp"
namespace th20 {
int EclManager::tick(float delta) {
    int primary = 1;
    auto* link = &runtimes;
    while (link) {
        auto* next = link->next_value();
        current_runtime = link->node_value();
        if (primary) {
            auto* runtime = current_runtime;
            if (runtime->tick(delta)) return -1;
            primary = 0;
        } else {
            auto* runtime = current_runtime;
            if (runtime->tick(delta)) {
                process_allocator->release_object(current_runtime);
                link->detach();
                process_allocator->release_object(link);
            }
        }
        link = next;
    }
    current_runtime = &main;
    return 0;
}
}
