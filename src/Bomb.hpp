#pragma once
#include "AnimationHandle.hpp"
#include "Interpolation.hpp"
#include "Motion.hpp"
#include "Session.hpp"
#include "TaskInfo.hpp"

namespace th20 {
// Native BombBaseInf/BombInf storage and six/three virtual slots. Original
// start/update/character gameplay and ANM resource implementations remain open.
// Offset names preserve unresolved scalar roles; padding is implicit.
class Bomb {
public:
    virtual ~Bomb();
    virtual std::int32_t start(std::int32_t index);
    virtual std::int32_t update();
    virtual std::int32_t draw();
    virtual std::int32_t finish();
    // Query caller passes position/dimensions pointers. Native base ignores
    // both arguments; original parameter type spellings remain inferred.
    virtual std::int32_t event(const Vector3* position,const Vector2* dimensions);
    std::uint32_t field_04;
    Timer age,secondary_age;
    Motion motion;
    AnimationHandle handle_70,handle_74;
    std::uint32_t field_78,field_7c;
    IntegerInterpolation interpolation;
    AnimationHandle handle_ac;
    std::int32_t view_index;
    Context* context;
    Bomb();
    void select_context(std::int32_t index);
};
class BombController : public TaskInfo {
public:
    std::uint32_t field_10;
    Bomb* active_bomb;
    std::int32_t active_state;
    Timer age;
    std::uint32_t field_2c,field_30;
    std::int32_t view_index;
    Context* context;
    BombController() noexcept;
    ~BombController() override;
    std::int32_t initialize(std::int32_t index);
    void select_context(std::int32_t index);
    std::int32_t update();
    std::int32_t draw();
    std::int32_t event(const Vector3* position,const Vector2* dimensions);
    std::int32_t finish();
    static std::int32_t update_callback(void* owner);
    static std::int32_t draw_callback(void* owner);
};
BombController* bomb_controller(std::int32_t index);
BombController* create_bomb_controller(std::int32_t index);
void destroy_bomb_controller(std::int32_t index);
#if defined(_M_IX86)
static_assert(sizeof(Bomb)==0xb8);
static_assert(offsetof(Bomb,motion)==0x28);
static_assert(offsetof(Bomb,interpolation)==0x80);
static_assert(offsetof(Bomb,context)==0xb4);
static_assert(sizeof(BombController)==0x3c);
static_assert(offsetof(BombController,active_bomb)==0x14);
static_assert(offsetof(BombController,age)==0x1c);
static_assert(offsetof(BombController,context)==0x38);
#endif
}
