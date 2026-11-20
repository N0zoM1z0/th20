#pragma once

#include "Vector2.hpp"
#include "Vector3.hpp"
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace th20 {

// Native 0x3C Laser-owned runtime geometry/state allocated by 0x004C7FD0.
struct LaserRuntimeState {
    Vector3 vector_00;
    Vector3 vector_0c;
    Vector2 vector_18;
    float field_20, field_24, field_28, field_2c;
    std::uint32_t field_30, field_34, field_38;

    LaserRuntimeState() noexcept;
};
static_assert(sizeof(LaserRuntimeState)==0x3c);
static_assert(std::is_trivially_destructible_v<LaserRuntimeState>);
static_assert(offsetof(LaserRuntimeState,vector_0c)==0x0c);
static_assert(offsetof(LaserRuntimeState,vector_18)==0x18);


} // namespace th20
