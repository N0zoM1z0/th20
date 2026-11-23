#include "LaserParameters.hpp"

namespace th20 {

#if defined(_M_IX86)
static_assert(offsetof(LaserController, active) == 0x10);
static_assert(offsetof(Laser, handle) == 0x8c);
#endif

// Native 0x00498FF0 is the shared handle lookup used by Laser ECL opcodes
// 704-710. Keep the second node_value() call on the match path: the original
// reads the link's Laser pointer once for the +0x8C comparison and again for
// the returned pointer, before destroying the iterator.
Laser* LaserController::find_laser(std::int32_t handle) {
    auto iterator = active.begin();
    auto* const last = active.end();
    for (; iterator.differs(last); iterator.advance()) {
        auto* const link = iterator.get();
        if (link->node_value()->handle == static_cast<std::uint32_t>(handle))
            return link->node_value();
    }
    return nullptr;
}

} // namespace th20
