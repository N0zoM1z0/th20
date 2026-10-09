#pragma once

#include "Motion.hpp"
#include "Vector2.hpp"
#include "Timer.hpp"
#include "IntrusiveLink.hpp"
#include "Identifier32.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {
struct DamageRegionFlags {
    union {
        std::uint32_t bits;
        struct {
            std::uint32_t active:1;
            std::uint32_t kind:3;
            std::uint32_t bit4:1;
            std::uint32_t bit5:1;
            std::uint32_t bit6:1;
            std::uint32_t reserved:25;
        } fields;
    };
};
// Opaque native owner, corroborated by allocation and dispatch consumers.
struct Context;
struct PlayerShot;
struct DamageRegion {
    IntrusiveLink<DamageRegion> link;
    DamageRegionFlags flags;
    float radius_a, radius_b, value_20;
    Angle angle;
    float angular_velocity;
    Vector2 dimensions;
    Motion motion;
    Timer timer;
    Identifier32 identifier;
    std::int32_t value_90, damage, value_98, value_9c, value_a0;
    Identifier32 target;
    std::int32_t cooldown, group;
    Identifier32 animation;
    std::int32_t value_b4, sides, value_bc;
    Context* context;

    DamageRegion() noexcept;
    PlayerShot* player_shot();
    void update();
    // Retirement detaches before clearing the identifier and conditionally
    // releases heap storage through the actual Context controller.
    void retire();
    void select_context(std::int32_t index);
    bool intersects(const Vector3* center,const Vector2* size,float direction,float radius);
    Vector3& position();
    Context* context_value();
    bool is_heap();
    std::uint32_t configure_rectangle(const Vector3&,float,float,float,std::int32_t,std::int32_t);
    std::uint32_t configure_circle(const Vector3&,float,float,std::int32_t,std::int32_t);
    void set_position(const Vector3&);
};

static_assert(sizeof(DamageRegionFlags) == 4);
static_assert(sizeof(void*) != 4 || sizeof(DamageRegion) == 196);
static_assert(sizeof(void*) != 4 || offsetof(DamageRegion, flags) == 0x14);
static_assert(sizeof(void*) != 4 || offsetof(DamageRegion, motion) == 0x34);
static_assert(sizeof(void*) != 4 || offsetof(DamageRegion, timer) == 0x7c);
static_assert(sizeof(void*) != 4 || offsetof(DamageRegion, identifier) == 0x8c);
static_assert(sizeof(void*) != 4 || offsetof(DamageRegion, context) == 0xc0);

} // namespace th20
