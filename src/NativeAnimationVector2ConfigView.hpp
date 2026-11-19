#pragma once
#include "Vector2.hpp"
#include <cstdint>
namespace th20 {
// Borrowed Animation receiver: the three original Vector2 interpolation
// members are already present in AnimationBase at +0x1E0, +0x220, +0x260.
struct NativeAnimationVector2ConfigView {
    void interpolate_secondary_scale_438db0(std::int32_t frames, std::int32_t curve,
                                            const Vector2& from, const Vector2& to);
    void interpolate_primary_scale_438df0(std::int32_t frames, std::int32_t curve,
                                          const Vector2& from, const Vector2& to);
    void interpolate_uv_scale_438e30(std::int32_t frames, std::int32_t curve,
                                    const Vector2& from, const Vector2& to);
};
}
