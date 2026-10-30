// Original 57B Animation(+0x8C) VectorInterpolation six-arg forwarding.
#include "NativeAnimationInterpolationConfig.hpp"
namespace th20 {
void NativeAnimationInterpolationForwardView::configure_45d150(std::int32_t frames,
       const Vector3& from,const Vector3& tangent_first,
       const Vector3& to,const Vector3& tangent_last) {
    auto* interpolation=reinterpret_cast<NativeVectorInterpolationConfigView*>(
        reinterpret_cast<std::uint8_t*>(this)+offsetof(AnimationBase,interpolation_8c));
    interpolation->configure_45d190(frames,8,from,to,tangent_first,tangent_last);
}
}
