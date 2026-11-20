#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include "Animation.hpp"
#include "LaserParameters.hpp"

namespace th20 {

// Original type-3 LaserBeamInf: native factory allocates 0x1D30 bytes and
// installs vtable 0x00571374. Its trailing 0x800-byte lanes are real
// zero-initialized storage, not opaque padding.
class LaserBeamInf : public Laser {
public:
    LaserBeamInf() noexcept;

    LaserType3Parameters parameters;
    Animation animation_0;
    float field_d2c;
    std::array<std::byte,0x800> field_d30;
    std::array<std::byte,0x800> field_1530;
};

#if defined(_M_IX86)
static_assert(sizeof(LaserBeamInf)==0x1d30);
static_assert(offsetof(LaserBeamInf,parameters)==0x6f8);
static_assert(offsetof(LaserBeamInf,animation_0)==0x748);
static_assert(offsetof(LaserBeamInf,field_d2c)==0xd2c);
static_assert(offsetof(LaserBeamInf,field_d30)==0xd30);
static_assert(offsetof(LaserBeamInf,field_1530)==0x1530);
#endif

} // namespace th20
