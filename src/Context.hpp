#pragma once
#include "TaskInfo.hpp"
namespace th20 {
struct EnemyController;
struct PlayerRecord;
// Twelve independent context slots. Unresolved pointer roles retain offsets.
struct Context {
    TaskInfo* primary_owner;
    void* object_04;
    EnemyController* enemies;
    void* object_0c;
    void* object_10;
    void* object_14;
    void* object_18;
    void* object_1c;
    void* object_20;
    PlayerRecord* current_player;
    void* object_28;
    TaskInfo* overlay_owner;
    Context() noexcept;
    EnemyController* enemy_controller();
    PlayerRecord* player_record();
};
#if defined(_M_IX86)
static_assert(sizeof(Context)==0x30);
#endif
}
