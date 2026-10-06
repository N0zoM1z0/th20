#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <mutex>

namespace th20 {

// REF-003: original array construction uses 22 elements of 48 bytes on x86;
// tracked depths occupy +0x420..+0x435 and the enable byte is at +0x436.
// The original tracked-entry, guard and global-lifetime protocols remain open.
class LockRegistry {
public:
    static constexpr std::size_t count = 22;

    void enable();
    void disable();
    bool enabled() const { return enabled_; }

private:
    std::array<std::recursive_mutex, count> locks_;
    std::array<std::uint8_t, count> depths_{};
    bool enabled_ = false;
};

static_assert(sizeof(void*) != 4 || sizeof(std::recursive_mutex) == 48);
static_assert(sizeof(void*) != 4 || sizeof(LockRegistry) == 0x438);

} // namespace th20
