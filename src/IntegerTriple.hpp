#pragma once

#include <cstdint>

namespace th20 {

// Three signed components used by ANM color interpolation; original tag unknown.
struct IntegerTriple {
    std::int32_t first, second, third;
    IntegerTriple();
    // Native construction accepts the last component first.
    IntegerTriple(std::int32_t third, std::int32_t second, std::int32_t first);
    IntegerTriple operator+(IntegerTriple other) const;
    IntegerTriple operator-(IntegerTriple other) const;
    // Each product must have a representable int32 truncation.
    IntegerTriple operator*(float factor) const;
};

static_assert(sizeof(IntegerTriple) == 12);

} // namespace th20
