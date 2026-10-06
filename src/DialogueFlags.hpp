#pragma once

#include <cstdint>

namespace th20 {

// Four-byte member at Dialogue +0x104. Bit meanings remain provisional.
struct DialogueFlags {
    std::uint32_t flag_0 : 1;
    std::uint32_t flag_1 : 1;
    std::uint32_t bits_2_5 : 4;
    std::uint32_t flag_6 : 1;
    std::uint32_t retained : 25;

    DialogueFlags();
};

static_assert(sizeof(DialogueFlags) == 4);

} // namespace th20
