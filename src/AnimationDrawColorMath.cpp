// Original game per-channel color combination from the 3159B renderer Boss.
// Both functions are separately whole original physical code bodies, not
// compiler library routines; exact source-level naming remains provisional.
#include <cstdint>

namespace th20 {
std::uint8_t __cdecl multiply_color_128_saturating(std::uint8_t a, std::uint8_t b) {
    std::uint32_t result = std::uint32_t(a) * std::uint32_t(b) >> 7;
    if (result >= 256) result = 255;
    return std::uint8_t(result);
}

std::uint8_t __cdecl multiply_color_255(std::uint8_t a, std::uint8_t b) {
    std::uint32_t result = std::uint32_t(a) * std::uint32_t(b) / 255;
    return std::uint8_t(result);
}
} // namespace th20
