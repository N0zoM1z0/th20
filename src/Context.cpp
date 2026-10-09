#include "Context.hpp"
#include "WeaponStoneInfo.hpp"
namespace th20 {
WeaponStoneInfo* Context::weapon_stone_info() {return static_cast<WeaponStoneInfo*>(overlay_owner);}
Context::Context() noexcept
    : primary_owner(nullptr), object_04(nullptr), enemies(nullptr), object_0c(nullptr),
      card_owner(nullptr), object_14(nullptr), object_18(nullptr), object_1c(nullptr),
      object_20(nullptr), current_player(nullptr), hits(nullptr), overlay_owner(nullptr) {}
BulletController* Context::bullet_controller() {return primary_owner;}
void Context::set_bullet_controller(BulletController* value) {primary_owner=value;}
EnemyController* Context::enemy_controller() { return enemies; }
PlayerRecord* Context::player_record() { return current_player; }
Card* Context::card() { return card_owner; }
void Context::set_card(Card* value) { card_owner=value; }
HitCtrlInf* Context::hit_controller() { return hits; }
void Context::set_hit_controller(HitCtrlInf* value) { hits=value; }
BombController* Context::bomb_controller() {return object_18;}
void Context::set_bomb_controller(BombController* value) {object_18=value;}
}
