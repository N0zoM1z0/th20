#pragma once
#include <cstdint>
namespace th20 {
// Three independently written ANM color channels; original type name is open.
struct Color3 {
    std::uint8_t blue, green, red;
    Color3();
    // Native ANM RGB constructor receives red, green, blue and stores BGR.
    Color3(std::uint8_t red, std::uint8_t green, std::uint8_t blue);
};
static_assert(sizeof(Color3) == 3);
}
