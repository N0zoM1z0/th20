#include "LockRegistry.hpp"

namespace th20 {

void LockRegistry::enable() {
    enabled_ = true;
}

void LockRegistry::disable() {
    enabled_ = false;
}

} // namespace th20
