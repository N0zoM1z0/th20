#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {

// REF-017: four-byte values constructed in Notice's seven-element array and
// secondary member. Native resolve clears a value when its lookup fails.
struct AnimationHandle {
    std::uint32_t value;

    AnimationHandle();
};

static_assert(sizeof(AnimationHandle) == 4);
static_assert(offsetof(AnimationHandle, value) == 0);

} // namespace th20
