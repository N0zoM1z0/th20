#pragma once
#include <array>
#include <cstddef>
#include <cstdint>

namespace th20 {
// REF-025: the disk header is an actual 48-byte value. Unknown fields retain
// their observed widths; alignment gaps are supplied by the compiler.
struct ReplayFileHeader {
    std::uint32_t magic;
    std::uint16_t version;
    std::uint8_t byte_06, byte_07, byte_08;
    std::uint32_t field_0c, field_10, field_14;
    std::uint8_t byte_18, byte_19;
    std::uint8_t field_1a[2];
    std::uint32_t header_size, user_size, stage_size, packed_size, unpacked_size;
    ReplayFileHeader();
};
static_assert(sizeof(ReplayFileHeader) == 0x30);
static_assert(offsetof(ReplayFileHeader, field_0c) == 0x0c);
static_assert(offsetof(ReplayFileHeader, packed_size) == 0x28);
} // namespace th20
