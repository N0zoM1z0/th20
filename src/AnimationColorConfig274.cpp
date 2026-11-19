#include "NativeAnimationColorConfigView.hpp"
#include "Animation.hpp"
#include "Color3.hpp"
#include "IntegerTriple.hpp"
namespace th20 {
void NativeAnimationColorConfigView::interpolate_secondary_alpha_438bd0(
        std::int32_t frames,std::int32_t curve,std::uint8_t start,std::uint8_t end) {
    const std::int32_t from=start;
    const std::int32_t to=end;
    IntegerInterpolation* const interpolation=
        &reinterpret_cast<Animation*>(this)->base.interpolation_2f4;
    interpolation->begin(frames,curve,from,to);
    if (!reinterpret_cast<Animation*>(this)->base.flags.bits_09.color_mode)
        reinterpret_cast<Animation*>(this)->base.flags.bits_09.color_mode=1;
}
void NativeAnimationColorConfigView::interpolate_rgb_438cc0(
        std::int32_t frames,std::int32_t curve,const Color3& start,const Color3& end) {
    const IntegerTriple from(start);
    const IntegerTriple to(end);
    IntegerTripleInterpolation* const interpolation=
        &reinterpret_cast<Animation*>(this)->base.interpolation_2a0;
    interpolation->begin(frames,curve,from,to);
    if (!reinterpret_cast<Animation*>(this)->base.flags.bits_09.color_mode)
        reinterpret_cast<Animation*>(this)->base.flags.bits_09.color_mode=1;
}
}
