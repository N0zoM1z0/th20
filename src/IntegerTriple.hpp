#pragma once

#include <cstdint>

namespace th20 {

// Three signed components used by ANM color interpolation; original tag unknown.
struct IntegerTriple {
    std::int32_t first, second, third;
    IntegerTriple();
};

static_assert(sizeof(IntegerTriple) == 12);

} // namespace th20
