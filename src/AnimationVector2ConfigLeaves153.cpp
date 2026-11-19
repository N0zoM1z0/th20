#include "NativeAnimationVector2ConfigView.hpp"
#include "Animation.hpp"
namespace th20 {
void NativeAnimationVector2ConfigView::interpolate_secondary_scale_438db0(
        std::int32_t frames, std::int32_t curve,
        const Vector2& from, const Vector2& to) {
    Vector2Interpolation* interpolation=
        &reinterpret_cast<Animation*>(this)->base.interpolation_220;
    interpolation->begin(frames,curve,from,to);
}
void NativeAnimationVector2ConfigView::interpolate_primary_scale_438df0(
        std::int32_t frames, std::int32_t curve,
        const Vector2& from, const Vector2& to) {
    Vector2Interpolation* interpolation=
        &reinterpret_cast<Animation*>(this)->base.interpolation_1e0;
    interpolation->begin(frames,curve,from,to);
}
void NativeAnimationVector2ConfigView::interpolate_uv_scale_438e30(
        std::int32_t frames, std::int32_t curve,
        const Vector2& from, const Vector2& to) {
    Vector2Interpolation* interpolation=
        &reinterpret_cast<Animation*>(this)->base.interpolation_260;
    interpolation->begin(frames,curve,from,to);
}
}
