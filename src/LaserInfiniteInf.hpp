#pragma once

#include "Animation.hpp"
#include "LaserParameters.hpp"

namespace th20 {

// Infinite-family vtable 0x005712E8; the factory allocates 0x1338 bytes.
class LaserInfiniteInf : public Laser {
public:
    LaserInfiniteInf() noexcept;
    std::int32_t initialize_laser(const void* input) override;
    std::int32_t cancel_rectangle(const Vector3& rectangle_center,
                                  const Vector3& rectangle_size,
                                  float rectangle_direction, std::int32_t mode,
                                  std::int32_t argument) override;
    std::int32_t cancel_circle(const Vector3& center, float radius,
                               std::int32_t mode, std::int32_t argument) override;
    std::int32_t erase(std::int32_t mode, std::int32_t argument) override;

    LaserType1Parameters parameters;
    std::uint32_t field_76c;
    Animation animation_0;
    Animation animation_1;
};

#if defined(_M_IX86)
static_assert(sizeof(LaserInfiniteInf)==0x1338);
static_assert(offsetof(LaserInfiniteInf,parameters)==0x6f8);
static_assert(offsetof(LaserInfiniteInf,field_76c)==0x76c);
static_assert(offsetof(LaserInfiniteInf,animation_0)==0x770);
static_assert(offsetof(LaserInfiniteInf,animation_1)==0xd54);
#endif

} // namespace th20
