#pragma once
// Two original 2,884B particle Update child accessors, using real Animation
// member offsets. Zero added storage; source role names remain provisional.
#include "Animation.hpp"
#include <cstdint>
namespace th20 {
struct NativeParticleAnimationAccess : Animation {
    std::int32_t age_45d0a0() const;
    std::uint32_t& color_ref_45d0e0();
};
static_assert(sizeof(NativeParticleAnimationAccess)==sizeof(Animation));
}
