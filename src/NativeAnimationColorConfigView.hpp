#pragma once
#include <cstdint>
namespace th20 {
class Color3;
// Borrowed Animation receiver for the two color-interpolation producers.
struct NativeAnimationColorConfigView {
    void interpolate_secondary_alpha_438bd0(std::int32_t frames, std::int32_t curve,
                                             std::uint8_t start, std::uint8_t end);
    void interpolate_rgb_438cc0(std::int32_t frames, std::int32_t curve,
                                const Color3& start, const Color3& end);
};
}
