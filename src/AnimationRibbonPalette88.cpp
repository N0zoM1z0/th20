// Complete original 88B/29-i386 ribbon segment palette and two 31B forwarding
// helpers, all under one ordinary C++20 source. Real color temporary scope
// naturally generates the original +0x2C NOP; genuine radius 32.f global.
#include "NativeRibbonPolygonGroup.hpp"
#include "EffectParameters.hpp"
#include <cstdint>
namespace th20 {
struct NativeRibbonColorFields { void forward_color_45dd20(const PackedColor*); };
struct NativeRibbonRadiusFields { void forward_radius_45dd00(const float*); };
extern void __cdecl native_polygon_apply_color_45d430(void*,std::int32_t,const PackedColor*);
extern void __cdecl native_polygon_apply_radius_45d360(void*,std::int32_t,const float*);
extern const float native_polygon_radius32;
void NativeRibbonColorFields::forward_color_45dd20(const PackedColor* color) {
    native_polygon_apply_color_45d430(this, 0x3C, color);
}
void NativeRibbonRadiusFields::forward_radius_45dd00(const float* radius) {
    native_polygon_apply_radius_45d360(this, 0x3C, radius);
}
void NativeRibbonSegment::initialize_palette_45ec10(std::uint32_t packed) {
    {
    auto* color_fields=reinterpret_cast<NativeRibbonColorFields*>(reinterpret_cast<std::uint8_t*>(this)+0x1E0);
    PackedColor color(packed);
    color_fields->forward_color_45dd20(&color);
    }
    auto* radius_fields=reinterpret_cast<NativeRibbonRadiusFields*>(reinterpret_cast<std::uint8_t*>(this)+0x2D0);
    float radius=native_polygon_radius32;
    radius_fields->forward_radius_45dd00(&radius);
}
}
