#pragma once
#include "GameResourceIo.hpp"
#include <cstddef>
namespace th20 {
// Native serialized prefix: entry count at +2, 121 three-word damage rows
// at +0x28, followed by entry_count four-byte relocatable offset words.
// Remaining header scalar meanings remain open; these are file words, not fake padding.
struct PlayerShotData {
    std::uint16_t field_00,entry_count;
    // Observed native Player reset reads these four original file scalars as
    // IEEE-754 float, at +0x10 through +0x1C, without conversion.
    std::uint32_t header_words_04_0c[3];
    float normal_speed;
    float focused_speed;
    float lateral_speed;
    float diagonal_speed;
    std::uint32_t header_words_20_24[2];
    std::int32_t damage_caps[121][3];
    // Native variable-sized resource tail; supported by MSVC/GCC as a flexible
    // array extension, with actual allocation extent supplied by resource I/O.
    std::uint32_t entry_offsets[];
};
static_assert(sizeof(PlayerShotData)==0x5d4);
static_assert(offsetof(PlayerShotData,damage_caps)==0x28);
static_assert(offsetof(PlayerShotData,normal_speed)==0x10);
static_assert(offsetof(PlayerShotData,diagonal_speed)==0x1c);
std::int32_t signed_resource_offset(std::uint32_t input);
std::uint32_t relocated_resource_address(std::uint32_t offset,const void* base);
}
