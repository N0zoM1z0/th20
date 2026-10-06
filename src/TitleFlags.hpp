#pragma once

#include <cstdint>

namespace th20 {

// Four UI state bits in Title at +0x58d4. Construction preserves upper bits.
struct TitleFlags {
    std::uint32_t music_pending : 1;
    std::uint32_t initial_menu : 1;
    std::uint32_t replay_read_cancelled : 1;
    std::uint32_t replay_read_finished : 1;
    std::uint32_t retained : 28;

    TitleFlags();
};

static_assert(sizeof(TitleFlags) == 4);

} // namespace th20
