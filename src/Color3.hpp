#pragma once
#include <cstdint>
namespace th20 {
// Three independently written ANM color channels; original type name is open.
struct Color3 {
    std::uint8_t blue, green, red;
    Color3();
};
static_assert(sizeof(Color3) == 3);
}
