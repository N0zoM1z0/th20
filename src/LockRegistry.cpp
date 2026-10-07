#include "LockRegistry.hpp"

namespace th20 {

LockRegistry::LockRegistry():depths_{},enabled_(false){}
std::recursive_mutex& LockRegistry::slot(std::size_t index) {
    auto& slots = locks_;
    return slots[index];
}
void LockRegistry::enter_tracked(std::size_t index) {
    if (enabled_) {
        auto& slots = locks_;
        slots[index].lock();
        auto& depths = depths_;
        std::uint8_t& depth = depths[index];
        ++depth;
    }
}
void LockRegistry::leave_tracked(std::size_t index) {
    if (enabled_) {
        auto& depths = depths_;
        std::uint8_t& depth = depths[index];
        --depth;
        auto& slots = locks_;
        slots[index].unlock();
    }
}

void LockRegistry::enable() {
    enabled_ = true;
}

void LockRegistry::disable() {
    enabled_ = false;
}

} // namespace th20
