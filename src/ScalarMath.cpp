#include "ScalarMath.hpp"

#include <cmath>

namespace th20::scalar_math {

float sine(float value) {
    return static_cast<float>(std::sin(static_cast<double>(value)));
}

float cosine(float value) {
    return static_cast<float>(std::cos(static_cast<double>(value)));
}

float absolute(float value) {
    return static_cast<float>(std::fabs(static_cast<double>(value)));
}

float arcsine(float value) {
    return static_cast<float>(std::asin(static_cast<double>(value)));
}

float arccosine(float value) {
    return static_cast<float>(std::acos(static_cast<double>(value)));
}

float square_root(float value) {
    return static_cast<float>(std::sqrt(static_cast<double>(value)));
}

float arctangent(float y, float x) {
    return static_cast<float>(std::atan2(static_cast<double>(y), static_cast<double>(x)));
}

float floating_remainder(float value, float divisor) {
    return static_cast<float>(std::fmod(static_cast<double>(value), static_cast<double>(divisor)));
}

} // namespace th20::scalar_math
