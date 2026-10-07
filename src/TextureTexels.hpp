#pragma once

#include <cstdint>

namespace th20 {

// Native x86 little-endian channel views; original struct tags are unknown.
struct Texel1555 { std::uint16_t blue : 5, green : 5, red : 5, alpha : 1; };
struct Texel4444 { std::uint16_t blue : 4, green : 4, red : 4, alpha : 4; };
struct Texel8332 { std::uint16_t blue : 2, green : 3, red : 3, alpha : 8; };
struct Texel8888 { std::uint8_t blue, green, red, alpha; };

static_assert(sizeof(Texel1555) == 2);
static_assert(sizeof(Texel4444) == 2);
static_assert(sizeof(Texel8332) == 2);
static_assert(sizeof(Texel8888) == 4);

// Null rgb returns without touching pixel or count. Otherwise both are valid;
// count may alias an rgb component, preserving the native update order.
void accumulate_texel1555(std::uint32_t* rgb, const Texel1555* pixel,
                          std::uint32_t& count);
void accumulate_texel4444(std::uint32_t* rgb, const Texel4444* pixel,
                          std::uint32_t& count);
void accumulate_texel8332(std::uint32_t* rgb, const Texel8332* pixel,
                          std::uint32_t& count);
void accumulate_texel8888(std::uint32_t* rgb, const Texel8888* pixel,
                          std::uint32_t& count);

} // namespace th20
