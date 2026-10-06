#include "EffectParameters.hpp"
#include "Interpolation.hpp"
#include <bit>
#include <cassert>
#include <cstring>
#include <initializer_list>
#include <limits>
#include <new>

void check_effect_values() {
    for (unsigned pattern : {0u, 0x55u, 0xa5u, 0xffu}) {
        alignas(th20::EffectParameters) unsigned char bytes[sizeof(th20::EffectParameters)];
        std::memset(bytes, pattern, sizeof(bytes));
        const auto* value = ::new(bytes) th20::EffectParameters;
        assert(value->enabled == 1 && value->color.value == 0);
        for (unsigned i = 0; i < sizeof(bytes); ++i)
            assert(bytes[i] == (i == 40 ? 1 : i >= 41 && i < 44 ? pattern : 0));
        alignas(th20::ByteInterpolation) unsigned char interpolation[32];
        std::memset(interpolation, pattern, sizeof(interpolation));
        ::new(interpolation) th20::ByteInterpolation;
        for (unsigned i = 0; i < sizeof(interpolation); ++i)
            assert(interpolation[i] == (i >= 5 && i < 8 ? pattern : 0));
        alignas(th20::SelectionPulse) unsigned char pulse[8];
        std::memset(pulse, pattern, sizeof(pulse));
        ::new(pulse) th20::SelectionPulse;
        for (unsigned i = 0; i < sizeof(pulse); ++i)
            assert(pulse[i] == (i >= 1 && i < 4 ? pattern : 0));
    }
    for (std::uint32_t color : {0u, 0xffffffffu, 0x80000000u, 0x7fc00001u, 0xff123456u})
        assert(th20::PackedColor(color).value == color);
    th20::EffectRequest request;
    assert(request.type == -1 && request.original_parameters == nullptr);
    assert(request.animation == nullptr && request.delay == 0 && request.parameters.enabled == 1);

    th20::ByteInterpolation byte;
    byte.tangent_start = 19;
    byte.tangent_end = 97;
    for (unsigned from = 0; from < 256; ++from) {
        const auto first = static_cast<std::uint8_t>(from), last = static_cast<std::uint8_t>(255 - from);
        byte.timer.flags = 0xa5a50007u;
        byte.begin(-11, 17, first, last);
        assert(byte.start == first && byte.end == last && byte.current == first);
        assert(byte.duration == -11 && byte.mode == 17);
        assert(byte.tangent_start == 19 && byte.tangent_end == 97);
        assert(byte.timer.previous == -1 && byte.timer.current == 0 && byte.timer.current_fraction == 0);
        assert(byte.timer.flags == 0xa5a50007u);
    }
    byte.start = 7;
    byte.end = 11;
    byte.begin(60, 4, byte.end, byte.start);
    assert(byte.start == 11 && byte.end == 11 && byte.current == 11);

    th20::FloatInterpolation scalar;
    scalar.tangent_start = 2;
    scalar.tangent_end = -3;
    for (std::uint32_t bits : {0u, 0x80000000u, 0x7f800000u, 0xff800000u, 0x7fc00001u, 0x7f800001u}) {
        const auto from = std::bit_cast<float>(bits), to = std::bit_cast<float>(bits ^ 0x80000000u);
        scalar.begin(0, std::numeric_limits<int>::min(), from, to);
        assert(std::bit_cast<std::uint32_t>(scalar.start) == bits);
        assert(std::bit_cast<std::uint32_t>(scalar.current) == bits);
        assert(std::bit_cast<std::uint32_t>(scalar.end) == (bits ^ 0x80000000u));
        assert(scalar.duration == 0 && scalar.mode == std::numeric_limits<int>::min());
        assert(scalar.tangent_start == 2 && scalar.tangent_end == -3);
    }
}
