#include "GameRandom.hpp"

namespace th20 {

GameRandom::GameRandom(std::uint32_t stream_id) : id(stream_id) {}

std::uint32_t GameRandom::bounded(std::uint32_t count) {
    return count ? next() % count : 0;
}

float GameRandom::unit() {
    return static_cast<float>(next()) / (static_cast<float>(modulus) - 1.0f);
}

float GameRandom::signed_unit() {
    return static_cast<float>(next()) / (static_cast<float>(modulus) / 2.0f - 1.0f) - 1.0f;
}

} // namespace th20
