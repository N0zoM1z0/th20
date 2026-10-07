#pragma once

#include <cstddef>
#include <memory_resource>

namespace th20 {

// REF-003: custom four-slot PMR vtable and a pointer-sized receiver.
// Aligned allocation and deallocation serialize through shared mutex slot 1.
// Equality always returns true. Process-global resource startup remains open.
class DebugMemoryResource final : public std::pmr::memory_resource {
public:
    DebugMemoryResource();
    ~DebugMemoryResource() override;

private:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* memory, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};

static_assert(sizeof(DebugMemoryResource) == sizeof(void*));

} // namespace th20
