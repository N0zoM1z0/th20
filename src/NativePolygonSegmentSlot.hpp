#pragma once
// Real 0x3D4-byte polygon segment storage used by both exact group methods.
// The unknown bytes preserve native offsets and do not add executable code.
#include <cstdint>
namespace th20 {
struct NativePolygonSegmentSlot {
    alignas(4) std::uint8_t original_bytes[0x3D4];
    void initialize_palette_45fc90(std::uint32_t diffuse_color);
    // Original complete 827B/237-x86 dynamic update: whole native strict exact.
    void update_polygon_dynamics_45f670(float limit);
};
static_assert(sizeof(NativePolygonSegmentSlot)==0x3D4);
}
