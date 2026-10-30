// Probe the original solo 123B palette separately from the accepted
// three-segment ribbon 88B / polygon 120B palette implementations.
#include "NativeRibbonSoloGroup.hpp"
#include "EffectParameters.hpp"
#include "Vector3.hpp"
#include <cstdint>
namespace th20 {
struct NativeRibbonSoloPaletteView { void initialize_palette_45dbf0(std::uint32_t); };
struct NativeRibbonColorFields { void forward_color_45dd20(const PackedColor*); };
struct NativeRibbonRadiusFields { void forward_radius_45dd00(const float*); };
extern const float native_polygon_radius32;
void NativeRibbonSoloPaletteView::initialize_palette_45dbf0(std::uint32_t value) {
    auto* color_fields = reinterpret_cast<NativeRibbonColorFields*>(
        reinterpret_cast<std::uint8_t*>(this) + 0x1E0);
    PackedColor color(value);
    color_fields->forward_color_45dd20(&color);
    {
        auto* color_fields_again = reinterpret_cast<NativeRibbonColorFields*>(
            reinterpret_cast<std::uint8_t*>(this) + 0x1E0);
        reinterpret_cast<PackedColor&>(
            reinterpret_cast<Vector3*>(color_fields_again)->operator[](0)) = 0x80FFFF80u;
    }
    auto* radius_fields = reinterpret_cast<NativeRibbonRadiusFields*>(
        reinterpret_cast<std::uint8_t*>(this) + 0x2D0);
    float radius = native_polygon_radius32;
    radius_fields->forward_radius_45dd00(&radius);
}
}
