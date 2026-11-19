#include "Color3.hpp"
namespace th20 {
Color3::Color3() : blue(0), green(0), red(0) {}
Color3::Color3(std::uint8_t red_value,std::uint8_t green_value,std::uint8_t blue_value)
    : blue(blue_value),green(green_value),red(red_value) {}
}
