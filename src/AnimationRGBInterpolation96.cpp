#include "NativeAnimationColorConfigView.hpp"
#include "Animation.hpp"
#include "Color3.hpp"
#include "IntegerTriple.hpp"
namespace th20 {
void NativeAnimationColorConfigView::interpolate_primary_rgb_438d50(
        std::int32_t frames,std::int32_t curve,
        const Color3& start,const Color3& end) {
    const IntegerTriple from(start);
    const IntegerTriple to(end);
    IntegerTripleInterpolation* const interpolation=
        &reinterpret_cast<Animation*>(this)->base.interpolation_e0;
    interpolation->begin(frames,curve,from,to);
}
}
