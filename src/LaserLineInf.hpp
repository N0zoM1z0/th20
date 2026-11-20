#pragma once

#include "Animation.hpp"
#include "LaserParameters.hpp"

namespace th20 {

// Concrete Line laser layout corroborated by its native constructor and
// vtable. The three Animation subobjects are real independently-owned
// subobjects, not a byte-array size surrogate.
class LaserLineInf : public Laser {
public:
    LaserLineInf() noexcept;
    std::int32_t cancel_circle(const Vector3& center, float radius,
                               std::int32_t mode, std::int32_t argument) override;

    LaserType0Parameters parameters;
    Animation animation_0;
    Animation animation_1;
    Animation animation_2;
};

#if defined(_M_IX86)
static_assert(sizeof(LaserLineInf)==0x18f8);
static_assert(offsetof(LaserLineInf,parameters)==0x6f8);
static_assert(offsetof(LaserLineInf,animation_0)==0x74c);
static_assert(offsetof(LaserLineInf,animation_1)==0xd30);
static_assert(offsetof(LaserLineInf,animation_2)==0x1314);
#endif

} // namespace th20
