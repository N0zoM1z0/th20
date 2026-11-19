#include "NativeAnimationFadeConfig86.hpp"
#include "Animation.hpp"
#include <cstdint>
namespace th20 {
void NativeAnimationFadeConfig86::interpolate_channel_438c60(
    std::int32_t frames, std::int32_t mode, std::uint8_t start, std::uint8_t end) {
    const std::int32_t from = start;
    const std::int32_t to = end;
    IntegerInterpolation* const interpolation =
        &reinterpret_cast<Animation*>(this)->base.interpolation_134;
    interpolation->begin(frames, mode, from, to);
}
}
