#pragma once
// Original native 92B game-specific locked random-next and published byte.
// Non-owning, minimally observed 0x18B view; intermediate words unknown.
#include "Random.hpp"
#include <cstdint>
#include <cstddef>
namespace th20 {
struct NativeRendererRandomPulse {
    std::uint32_t unknown_00;
    RandomState random_04;
    std::uint32_t unknown_08,unknown_0c,unknown_10;
    std::uint32_t last_14;
    std::uint8_t random_byte_449d20();
};
static_assert(offsetof(NativeRendererRandomPulse,random_04)==4);
static_assert(offsetof(NativeRendererRandomPulse,last_14)==0x14);
}
