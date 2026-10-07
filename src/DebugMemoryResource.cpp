#include "DebugMemoryResource.hpp"
#include "LockRegistry.hpp"
#include <new>

namespace th20 {

DebugMemoryResource::DebugMemoryResource() = default;

DebugMemoryResource::~DebugMemoryResource() = default;

bool DebugMemoryResource::do_is_equal(const std::pmr::memory_resource&) const noexcept {
    return true;
}

void* DebugMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(1));
    void* memory = ::operator new(bytes, static_cast<std::align_val_t>(alignment));
    return memory;
}
void DebugMemoryResource::do_deallocate(void* memory, std::size_t, std::size_t alignment) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(1));
    ::operator delete(memory, static_cast<std::align_val_t>(alignment));
}

} // namespace th20
