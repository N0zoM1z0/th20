#pragma once
// Real 0x3D4-byte polygon segment storage used by both exact group methods.
// The unknown bytes preserve native offsets and do not add executable code.
#include <cstdint>
namespace th20 {
struct NativePolygonSegmentSlot {
    alignas(4) std::uint8_t original_bytes[0x3D4];
    void initialize_palette_45fc90(std::uint32_t diffuse_color);
};
static_assert(sizeof(NativePolygonSegmentSlot)==0x3D4);
}
