#pragma once
#include "TaskInfo.hpp"
#include "IntrusiveLink.hpp"
#include "Interpolation.hpp"
#include "Timer.hpp"
#include "AnimationFile.hpp"
#include "OverlayCounter.hpp"
namespace th20 {
struct StoneEnemyRecord;
struct StoneEnemyController {
    IntrusiveList<StoneEnemyRecord> records;
    Timer timer_18, timer_28;
    FloatInterpolation scalar_38;
    Interpolation<std::uint8_t> scalar_64;
    FloatInterpolation scalar_84;
    std::uint8_t byte_b0;
    StoneEnemyController();
    ~StoneEnemyController();
    std::uint8_t byte_b0_value();
};
extern StoneEnemyController* process_stone_enemies;
StoneEnemyController* stone_enemy_controller();
#if defined(_M_IX86)
static_assert(sizeof(StoneEnemyController)==0xb4);
static_assert(offsetof(StoneEnemyController,byte_b0)==0xb0);
#endif
struct Context;
class Weapon;
struct PlayerOption;
class RenderMesh;
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
    Weapon* passive_weapon();
    std::int32_t option_script_variant();
    void initialize_option_pair(PlayerOption* option, std::int32_t index);
    const Vector2* focused_offset(std::int32_t count, std::int32_t index);
    const Vector2* unfocused_offset(std::int32_t count, std::int32_t index);
};
WeaponStoneInfo* weapon_stone_info(std::int32_t index);
#if defined(_M_IX86)
static_assert(sizeof(WeaponStoneInfo)==0x84);
static_assert(offsetof(WeaponStoneInfo,phase)==0x54);
static_assert(offsetof(WeaponStoneInfo,context)==0x80);
#endif
}
