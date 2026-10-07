#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <mutex>

namespace th20 {

// REF-003: original array construction uses 22 elements of 48 bytes on x86;
// tracked depths occupy +0x420..+0x435 and the enable byte is at +0x436.
// Tracking requires matched enter/leave calls and a stable enabled state.
// Slot indices belong to the native 0..21 domain. Global lifetime remains open.
class LockRegistry {
public:
    static constexpr std::size_t count = 22;

    LockRegistry();
    std::recursive_mutex& slot(std::size_t index);
    void enter_tracked(std::size_t index);
    void leave_tracked(std::size_t index);
    void enable();
    void disable();
    bool enabled() const { return enabled_; }

private:
    std::array<std::recursive_mutex, count> locks_;
    std::array<std::uint8_t, count> depths_{};
    bool enabled_ = false;
};

// Independently observed shared native object at 0x005C0240. Definition/startup
// is deferred; portable fixtures provide their own owned instance.
extern LockRegistry process_locks;

static_assert(sizeof(void*) != 4 || sizeof(std::recursive_mutex) == 48);
static_assert(sizeof(void*) != 4 || sizeof(LockRegistry) == 0x438);

} // namespace th20
