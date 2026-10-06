#include "DebugMemoryResource.hpp"

namespace th20 {

DebugMemoryResource::DebugMemoryResource() = default;

DebugMemoryResource::~DebugMemoryResource() = default;

bool DebugMemoryResource::do_is_equal(const std::pmr::memory_resource&) const noexcept {
    return true;
}

} // namespace th20
