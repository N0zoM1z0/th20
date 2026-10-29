#pragma once

#include <cstdint>

namespace th20 {
// The original four-byte game handle is named SprtID in native RTTI.
// Keep it separate from the existing public AnimationHandle interface while
// its original source-level aliasing/ownership is still being reconciled.
struct SprtID {
    std::uint32_t value;
    bool operator==(std::uint32_t rhs) const;
    std::uint32_t operator&(std::uint32_t mask) const;
    void operator=(std::uint32_t rhs);
    bool operator==(const SprtID& rhs) const;
    bool operator!=(const SprtID& rhs) const;
};
static_assert(sizeof(SprtID) == 4);
} // namespace th20
