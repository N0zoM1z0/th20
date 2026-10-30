#pragma once
#include "AnimationCallback.hpp"
#include "AnimationHandle.hpp"
#include "Vector3.hpp"
#include "Timer.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
namespace th20 {
class Animation;
class NativeParticleGridGroup : public AnimationCallback {
public:
    std::array<AnimationHandle,200> colors_08;
    std::array<Vector3,200> positions_328;
    std::array<Vector3,200> vectors_c88;
    std::array<float,200> scalars_15e8;
    Vector3 extra_1908;
    Vector3 extra_1914;
    Vector3 extra_1920;
    // The physical 4-byte field is zeroed as float in the original ctor.
    // A pointer-like union view is provisional; C++17 MSVC /sdl requires
    // pointer-bearing class classification to emit the native autozero.
    union { float scalar_192c; void* provisional_pointer_192c; };
    Timer timer_1930;
    explicit NativeParticleGridGroup(Animation* owner);
    std::int32_t update() override;
    std::int32_t slot_0c() override;
    std::int32_t interrupt(std::int32_t event) override;
};
static_assert(offsetof(NativeParticleGridGroup,colors_08)==0x08);
static_assert(offsetof(NativeParticleGridGroup,positions_328)==0x328);
static_assert(offsetof(NativeParticleGridGroup,vectors_c88)==0xC88);
static_assert(offsetof(NativeParticleGridGroup,scalars_15e8)==0x15E8);
static_assert(offsetof(NativeParticleGridGroup,extra_1908)==0x1908);
static_assert(offsetof(NativeParticleGridGroup,scalar_192c)==0x192C);
static_assert(offsetof(NativeParticleGridGroup,timer_1930)==0x1930);
static_assert(sizeof(NativeParticleGridGroup)==0x1940);
}
