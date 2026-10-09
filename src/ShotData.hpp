#pragma once
#include "GameResourceIo.hpp"
#include <cstddef>
namespace th20 {
// Native serialized prefix: entry count at +2, 121 three-word damage rows
// at +0x28, followed by entry_count four-byte relocatable offset words.
// Header scalar meanings remain open; these are file words, not fake padding.
struct PlayerShotData {
    std::uint16_t field_00,entry_count;
    std::uint32_t header_words[9];
    std::int32_t damage_caps[121][3];
    // Native variable-sized resource tail; supported by MSVC/GCC as a flexible
    // array extension, with actual allocation extent supplied by resource I/O.
    std::uint32_t entry_offsets[];
};
static_assert(sizeof(PlayerShotData)==0x5d4);
static_assert(offsetof(PlayerShotData,damage_caps)==0x28);
std::int32_t signed_resource_offset(std::uint32_t input);
std::uint32_t relocated_resource_address(std::uint32_t offset,const void* base);
}
