#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {

struct Animation;

// REF-017: four-byte values constructed in Notice's seven-element array and
// secondary member. Native resolve clears a value when its lookup fails.
struct AnimationHandle {
    std::uint32_t value;

    AnimationHandle() noexcept;
    // Native word assignment; the shared physical head is audited separately.
    void operator=(std::uint32_t input);
    Animation* resolve();
    Animation* find_child(std::int32_t identifier, std::int32_t ordinal);
    void interrupt(std::int32_t event);
    void interrupt_offset_7(std::int32_t event);
    void retire();
};

static_assert(sizeof(AnimationHandle) == 4);
static_assert(offsetof(AnimationHandle, value) == 0);

} // namespace th20
