#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {

// Actual 28-byte background fog value; original tag remains unknown.
struct FogValue {
    float near_distance, far_distance;
    float channels[4]; // Blue, green, red, alpha.
    std::uint32_t packed;
    FogValue();
    FogValue(float near_value, float far_value, float blue, float green,
             float red, float alpha);
    // Truncate each channel to int32, then retain its low byte. Channels must
    // have a representable int32 truncation; nonfinite/out-of-range conversion
    // is outside the portable C++ domain. There is no channel clamp.
    void pack();
    FogValue operator*(float factor) const;
    FogValue operator-(const FogValue& other) const;
    FogValue operator+(const FogValue& other) const;
};

static_assert(sizeof(FogValue) == 28);
static_assert(offsetof(FogValue, channels) == 8);
static_assert(offsetof(FogValue, packed) == 24);

} // namespace th20
