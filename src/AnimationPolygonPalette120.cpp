// Original 120B/39-x86 palette method and two 31B tag forwarding helpers.
// They are a distinct original source compilation profile: /GS without /sdl
// emits the original no-cookie method. Three whole PE strict proofs required.
#include "NativePolygonSegmentSlot.hpp"
#include "EffectParameters.hpp"
#include "Vector3.hpp"
#include <cstdint>
namespace th20 {
struct NativePolygonColorFields {
    void forward_color_45ffc0(const PackedColor* value);
};
struct NativePolygonRadiusFields {
    void forward_radius_45ffa0(const float* value);
};
extern void __cdecl native_polygon_apply_color_45d430(
    void* owner, std::int32_t tag, const PackedColor* value);
extern void __cdecl native_polygon_apply_radius_45d360(
    void* owner, std::int32_t tag, const float* value);
// Actual original PE HIGHLOW uses a non-folded external 32.0f field.
// The verified consecutive original data definitions live in a separate
// translation unit so MSVC cannot substitute an __real@42000000 literal.
extern const float native_polygon_radius32;


// Whole original 120B/39-i386 palette method and both 31B/14-i386
// forwarding wrappers are strict exact. This distinct /GS, no-/sdl
// source profile reproduces the real original no-cookie ABI, all five
// palette E8 calls and one PE HIGHLOW 32.0f global target.
void NativePolygonColorFields::forward_color_45ffc0(const PackedColor* value) {
    native_polygon_apply_color_45d430(this, 0x3D, value);
}
void NativePolygonRadiusFields::forward_radius_45ffa0(const float* value) {
    native_polygon_apply_radius_45d360(this, 0x3E, value);
}
void NativePolygonSegmentSlot::initialize_palette_45fc90(std::uint32_t value) {
    auto* color_fields = reinterpret_cast<NativePolygonColorFields*>(
        reinterpret_cast<std::uint8_t*>(this)+0x1E8);
    PackedColor color(value);
    color_fields->forward_color_45ffc0(&color);
    {
        auto* color_fields_again = reinterpret_cast<NativePolygonColorFields*>(
            reinterpret_cast<std::uint8_t*>(this)+0x1E8);
        reinterpret_cast<PackedColor&>(
            reinterpret_cast<Vector3*>(color_fields_again)->operator[](0)) = 0u;
    }
    auto* radius_fields = reinterpret_cast<NativePolygonRadiusFields*>(
        reinterpret_cast<std::uint8_t*>(this)+0x2DC);
    float radius = native_polygon_radius32;
    radius_fields->forward_radius_45ffa0(&radius);
}

} // namespace th20
