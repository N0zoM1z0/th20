#include "EclRuntime.hpp"
#include "DiagnosticAllocator.hpp"
namespace th20 {
EclScriptPosition::EclScriptPosition() : subroutine(0), offset(0) {}

EclRuntime::EclRuntime()
    : time(0), async_id(0), manager(nullptr), signal(0), rank(0), flags{} {}
EclManager::EclManager()
    : field_04(0), field_08(0), current_runtime(nullptr), loader(nullptr) {}
EclManager::~EclManager() { terminate_async(); }

// Valid clearing walks heap-owned async nodes. The sentinel is reset by the
// surrounding clear/reset lifecycle; its next pointer remains stale here.
void EclManager::terminate_async() {
    auto* link = runtimes.next_value();
    while (link) {
        auto* next = link->next_value();
        auto* runtime = link->node_value();
        process_allocator->release_object(runtime);
        process_allocator->release_object(link);
        link = next;
    }
}
std::int32_t EclManager::execute_opcode() { return 0; }
std::int32_t EclManager::read_integer(std::int32_t) { return 0; }
std::int32_t* EclManager::integer_destination(std::int32_t) { return nullptr; }
float EclManager::read_float(std::int32_t) { return 0; }
float* EclManager::float_destination(std::int32_t) { return nullptr; }
}
