#pragma once
// Native VectorInterpolation (84B) config and Animation+0x8C forwarding.
// The original current/Timer offsets come from actual typed Interpolation.
#include "Interpolation.hpp"
#include "Animation.hpp"
#include <cstddef>
#include <cstdint>
namespace th20 {
struct NativeVectorInterpolationConfigView : VectorInterpolation {
    void configure_45d190(std::int32_t duration_value, std::int32_t mode_value,
        const Vector3& from, const Vector3& to,
        const Vector3& tangent_first, const Vector3& tangent_last);
};
static_assert(sizeof(NativeVectorInterpolationConfigView)==sizeof(VectorInterpolation));
static_assert(offsetof(AnimationBase,interpolation_8c)==0x8C);
struct NativeAnimationInterpolationForwardView {
    void configure_45d150(std::int32_t frames, const Vector3& from,
        const Vector3& tangent_first, const Vector3& to,
        const Vector3& tangent_last);
};
}
