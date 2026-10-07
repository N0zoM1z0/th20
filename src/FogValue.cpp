#include "FogValue.hpp"

namespace th20 {

FogValue::FogValue()
    : near_distance(0.0f), far_distance(0.0f), channels{}, packed(0) {}

FogValue::FogValue(float near_value, float far_value, float blue, float green,
                   float red, float alpha)
    : near_distance(near_value), far_distance(far_value),
      channels{blue, green, red, alpha}, packed(0) { pack(); }

void FogValue::pack() {
    reinterpret_cast<std::uint8_t*>(&packed)[0] =
        static_cast<std::uint8_t>(static_cast<std::int32_t>(channels[0]));
    reinterpret_cast<std::uint8_t*>(&packed)[1] =
        static_cast<std::uint8_t>(static_cast<std::int32_t>(channels[1]));
    reinterpret_cast<std::uint8_t*>(&packed)[2] =
        static_cast<std::uint8_t>(static_cast<std::int32_t>(channels[2]));
    reinterpret_cast<std::uint8_t*>(&packed)[3] =
        static_cast<std::uint8_t>(static_cast<std::int32_t>(channels[3]));
}

FogValue FogValue::operator*(float factor) const {
    return FogValue(near_distance * factor, far_distance * factor,
                    channels[0] * factor, channels[1] * factor,
                    channels[2] * factor, channels[3] * factor);
}

FogValue FogValue::operator-(const FogValue& other) const {
    return FogValue(near_distance - other.near_distance,
                    far_distance - other.far_distance,
                    channels[0] - other.channels[0], channels[1] - other.channels[1],
                    channels[2] - other.channels[2], channels[3] - other.channels[3]);
}

FogValue FogValue::operator+(const FogValue& other) const {
    return FogValue(near_distance + other.near_distance,
                    far_distance + other.far_distance,
                    channels[0] + other.channels[0], channels[1] + other.channels[1],
                    channels[2] + other.channels[2], channels[3] + other.channels[3]);
}

} // namespace th20
