#pragma once
#include "AnimationFile.hpp"
#include "Enemy.hpp"
#include "EnemyHandle.hpp"
#include "TaskInfo.hpp"
#include <memory_resource>
#include <array>
#include <string>
#include <vector>
namespace th20 {
using EnemyHandles = std::array<EnemyHandle,16>;
// Native construction zeros this four-byte aggregate. Its role is unknown.
struct EnemyDataWord { std::uint32_t value; };
struct EnemyData {
    EnemyCounters counters;
    std::uint32_t field_30, field_34, field_38, field_3c, field_40;
    EnemyHandles handles;
    EnemyDataWord field_84;
    std::uint32_t field_88;
    Timer timer_8c;
    std::uint32_t field_9c, field_a0;
    EnemyData();
};
struct EnemyController : TaskInfo {
    EnemyData data;
    std::pmr::vector<std::pmr::string> loaded_names;
    std::uint32_t field_c4, field_c8, field_cc;
    Timer timer_d0;
    std::uint32_t field_e0;
    AnimationFile* animation_files[8];
    EclLoader* loader;
    IntrusiveList<Enemy> enemies;
    std::uint32_t field_120, field_124;
    Identifier32 identifier_128;
    std::int32_t player_index;
    Context* context;
    EnemyController() noexcept;
    ~EnemyController() override;
    AnimationFile* animation_file(std::int32_t index);
    // A checked handle slot resolves through player 0.
    Enemy* selected(std::uint32_t index);
    Enemy* find(std::uint32_t identifier);
    std::int32_t count() const;
    std::int32_t capacity() const;
    Enemy* create(const char* name, const EnemySpawn& parameters, Enemy* parent);
    EclLoader* script_loader() const;
    std::uint32_t generation() const;
    std::uint32_t advance_generation();
};
// Actual process generation words; production initialization remains open.
extern std::uint32_t current_enemy_generation, previous_enemy_generation;
// Actual cdecl player/context lookup through the reconstructed process Session.
EnemyController* enemy_controller(std::int32_t index);
// Four process script words; original global initialization remains open.
extern std::int32_t enemy_script_globals[4];
#if defined(_M_IX86)
static_assert(sizeof(EnemyData)==0xa4);
static_assert(offsetof(EnemyData, handles)==0x44);
static_assert(offsetof(EnemyData, field_84)==0x84);
static_assert(sizeof(EnemyController)==0x134);
static_assert(offsetof(EnemyController,context)==0x130);
#endif
}
