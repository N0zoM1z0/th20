#pragma once

#include <cstdint>

namespace th20 {

// The original does not clamp elapsed/duration. Zero duration returns one.
float easing(std::int32_t mode, float elapsed, float duration);

} // namespace th20
