#pragma once
// An original AnimationPoolOwner member at byte offset 0x07D40E88 holds a
// native four-byte generation counter. The intervening owner's storage has
// not been reconstructed; this is a NON-OWNING view (never instantiated).
// Original 187B member and 72/75B renderer methods share this one C++ ABI.
#include "AnimationRuntimeOwner.hpp"
#include "AnimationHandle.hpp"
#include <cstdint>
#include <cstddef>
namespace th20 {
class Animation;
struct NativeGenerationPool {
    std::uint32_t value;
    std::uint32_t operator++(int ignored);
    void operator&=(std::uint32_t mask);
    bool slot_matches_449430(int input);
    std::uint32_t generation_bits_4493e0(int bits);
};
static_assert(sizeof(NativeGenerationPool)==4);
struct NativeRendererPoolRegister : AnimationPoolOwner {
    std::uint8_t original_unclassified_prefix[0x07D40E88];
    NativeGenerationPool generation_7d40e88;
    AnimationHandle register_44c8f0(Animation* anim);
};
static_assert(offsetof(NativeRendererPoolRegister,generation_7d40e88)==0x07D40E88);
}
