// Complete native 123B color and 202B float array fill_n C++20 bodies.
// The genuine original native branch conditions are UNSIGNED: original jbe
// (not jle) at 2 sites each. Keep uint32_t count in these exact instances.
// These are STL/compiler-like instantiations, not authored-game code credit.
#include "EffectParameters.hpp"
#include <algorithm>
#include <cstdint>

template th20::PackedColor* std::fill_n<th20::PackedColor*, std::uint32_t, th20::PackedColor>(
    th20::PackedColor*, std::uint32_t, const th20::PackedColor&);
template float* std::fill_n<float*, std::uint32_t, float>(
    float*, std::uint32_t, const float&);
