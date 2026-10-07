#include "DiagnosticAllocator.hpp"
#include <cstdlib>
namespace th20 {

DiagnosticAllocator::~DiagnosticAllocator() = default;

void* DiagnosticAllocator::allocate_bytes(std::int32_t size, const char*) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(1));
    void* memory = std::malloc(size);
    return memory;
}
void DiagnosticAllocator::release_bytes(void* memory) {
    if (!memory) return;
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(1));
    std::free(memory);
}
template std::uint8_t* DiagnosticAllocator::allocate_array<std::uint8_t>(const char*, std::int32_t);
template void DiagnosticAllocator::release_array<std::uint8_t>(std::uint8_t*);

} // namespace th20
