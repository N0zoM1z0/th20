#pragma once

#include "Vector3.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {

// Actual four-byte packed color value; original type spelling remains unknown.
struct PackedColor {
    std::uint32_t value;
    explicit PackedColor(std::uint32_t value = 0);
};

struct SelectionPulse {
    std::uint8_t enabled;
    float radius;
    SelectionPulse();
};

// Named neutral scalar lanes are interpreted differently by individual effects.
struct EffectParameters {
    Vector3 vector_00, vector_0c;
    float scalar_18, scalar_1c;
    PackedColor color;
    float scalar_24;
    std::uint8_t enabled;
    Vector3 vector_2c;
    EffectParameters();
};

struct Animation;
struct EffectRequest {
    std::int32_t type;
    const EffectParameters* original_parameters;
    Animation* animation;
    std::int32_t delay;
    EffectParameters parameters;
    EffectRequest();
};

static_assert(sizeof(PackedColor) == 4);
static_assert(sizeof(SelectionPulse) == 8);
static_assert(offsetof(SelectionPulse, radius) == 4);
static_assert(sizeof(EffectParameters) == 56);
static_assert(offsetof(EffectParameters, color) == 32);
static_assert(offsetof(EffectParameters, enabled) == 40);
static_assert(offsetof(EffectParameters, vector_2c) == 44);
static_assert(sizeof(void*) != 4 || sizeof(EffectRequest) == 72);
static_assert(sizeof(void*) != 4 || offsetof(EffectRequest, parameters) == 16);

} // namespace th20
