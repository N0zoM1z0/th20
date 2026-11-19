#pragma once
#include <cstdint>
namespace th20 {
// Non-owning view: receiver is the real Animation object, with its
// IntegerInterpolation state at AnimationBase+0x134.
struct NativeAnimationFadeConfig86 {
    void interpolate_channel_438c60(std::int32_t frames, std::int32_t mode,
                                     std::uint8_t start, std::uint8_t end);
};
}
