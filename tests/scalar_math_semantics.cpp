#include "ScalarMath.hpp"

#include <cassert>
#include <cmath>

void check_scalar_math() {
    namespace math = th20::scalar_math;
    constexpr float pi = 3.1415927410125732f;
    assert(math::sine(0.0f) == 0.0f && !std::signbit(math::sine(0.0f)));
    assert(math::sine(-0.0f) == 0.0f && std::signbit(math::sine(-0.0f)));
    assert(math::cosine(0.0f) == 1.0f && math::cosine(-0.0f) == 1.0f);
    assert(math::square_root(-0.0f) == 0.0f && std::signbit(math::square_root(-0.0f)));
    assert(math::arctangent(-0.0f, 1.0f) == 0.0f &&
           std::signbit(math::arctangent(-0.0f, 1.0f)));
    assert(math::arctangent(0.0f, -0.0f) == pi);
    assert(math::arctangent(-0.0f, -0.0f) == -pi);

    for (unsigned i = 0; i <= 4095; ++i) {
        // Every square fits exactly in binary32's integer range.
        assert(math::square_root(static_cast<float>(i * i)) == static_cast<float>(i));
    }
    for (int i = -256; i <= 256; ++i) {
        const float angle = static_cast<float>(i) * (pi / 32.0f);
        const float sine = math::sine(angle), cosine = math::cosine(angle);
        assert(std::abs(sine * sine + cosine * cosine - 1.0f) <= 0.00000024f);
        assert(math::sine(-angle) == -sine);
        assert(math::cosine(-angle) == cosine);
    }
    for (int i = 1; i <= 128; ++i) {
        const float value = static_cast<float>(i);
        assert(math::arctangent(value, value) == pi / 4.0f);
        assert(math::arctangent(-value, value) == -pi / 4.0f);
        assert(std::abs(math::arctangent(value, -value) - pi * 0.75f) < 0.000001f);
        assert(std::abs(math::arctangent(-value, -value) + pi * 0.75f) < 0.000001f);
    }
    assert(std::abs(math::sine(pi / 6.0f) - 0.5f) < 0.000001f);
    assert(std::abs(math::cosine(pi / 3.0f) - 0.5f) < 0.000001f);
}
