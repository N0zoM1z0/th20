#pragma once

#include "AnimationHandle.hpp"
#include <cstdint>

namespace th20 {
// The original native 44-byte handle test returns a full 32-bit integer,
// not an 8-bit bool. The handle resolver clears stale values on failure.
std::int32_t __fastcall bullet_animation_handle_valid(AnimationHandle& handle);
} // namespace th20
