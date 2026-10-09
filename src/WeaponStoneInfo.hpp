#pragma once
#include "TaskInfo.hpp"
#include "Timer.hpp"
#include "AnimationFile.hpp"
#include "OverlayCounter.hpp"
namespace th20 {
struct Context;
struct Weapon;
struct RenderMesh;
class WeaponStoneInfo : public TaskInfo {
public:
    Timer timer_10;
    AnimationHandle handle_20;
    AnimationFile* animation_file;
    Weapon* weapon_28;
    Weapon* weapon_2c;
    Weapon* weapon_30;
    Weapon* weapon_34;
    OverlayCounter counter;
    RenderMesh* mesh;
    Timer timer_44;
    std::int32_t phase;
    Vector3 position;
    Timer timer_64;
    float radius;
    std::uint8_t byte_78;
    std::int32_t view_index;
    Context* context;
    WeaponStoneInfo();
    void record_damage(const Vector3*,std::int32_t,std::int32_t);
    ~WeaponStoneInfo() override;
    void enable() override;
    void disable() override;
    bool phase_one();
};
WeaponStoneInfo* weapon_stone_info(std::int32_t index);
#if defined(_M_IX86)
static_assert(sizeof(WeaponStoneInfo)==0x84);
static_assert(offsetof(WeaponStoneInfo,phase)==0x54);
static_assert(offsetof(WeaponStoneInfo,context)==0x80);
#endif
}
