#pragma once
#include "TaskInfo.hpp"
namespace th20 {
struct EnemyController;
struct BulletController;
struct PlayerRecord;
struct Card;
class HitCtrlInf;
// Twelve independent context slots. Unresolved pointer roles retain offsets.
struct Context {
    BulletController* primary_owner;
    void* object_04;
    EnemyController* enemies;
    void* object_0c;
    Card* card_owner;
    void* object_14;
    void* object_18;
    void* object_1c;
    void* object_20;
    PlayerRecord* current_player;
    HitCtrlInf* hits;
    TaskInfo* overlay_owner;
    Context() noexcept;
    BulletController* bullet_controller();
    void set_bullet_controller(BulletController* value);
    EnemyController* enemy_controller();
    PlayerRecord* player_record();
    Card* card();
    void set_card(Card* value);
    HitCtrlInf* hit_controller();
    void set_hit_controller(HitCtrlInf* value);
};
#if defined(_M_IX86)
static_assert(sizeof(Context)==0x30);
#endif
}
