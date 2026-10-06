#pragma once

#include <cstdint>

namespace th20 {

// Native Pause uses mode values 0/1/2 and a separate practice bit.
// Construction retains the upper twenty-nine bits of the existing word.
struct PauseFlags {
    std::uint32_t mode : 2;
    std::uint32_t practice : 1;
    std::uint32_t retained : 29;
    PauseFlags();
};

static_assert(sizeof(PauseFlags) == 4);

} // namespace th20
