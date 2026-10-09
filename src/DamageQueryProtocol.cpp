#include "Session.hpp"
#include "Player.hpp"
#include "DamageRegion.hpp"
#include "EnemyController.hpp"
#include "WeaponStoneInfo.hpp"
// Complete query consumers use the existing real owner storage. The whole
// HitCtrlInf query and original Item reward implementation remain open.
namespace th20 {
void PlayerRecord::add_score(std::uint64_t amount) {
    score+=amount/10;
    if (score>=1000000000u) score=999999999u;
}
void Session::add_score(std::uint32_t amount) {
    auto& values=table;
    auto& record=values.player(0);
    record.add_score(amount);
}
std::int32_t Timer::changed() const {return current!=previous?1:0;}
std::int32_t Timer::every(std::int32_t divisor) const {
    return current!=previous && current%divisor==0?1:0;
}
std::int32_t Player::frame_changed() {return timer_644.changed();}
Player* Context::player() {return static_cast<Player*>(object_04);}
PlayerShot* Player::find_shot(std::int32_t identifier) {
    auto& controller=shots;
    return controller.find(identifier);
}
PlayerShot* PlayerShotController::find(std::int32_t identifier) {
    if (!identifier) return nullptr;
    {
        auto& list=active;
        auto iterator=list.begin();
        auto* finish=list.end();
        for (;iterator.differs(finish);iterator.advance()) {
            auto* entry=iterator.get();
            if (entry->node_access()->state_14==static_cast<std::uint32_t>(identifier)) return entry->node_access();
        }
    }
    return nullptr;
}
PlayerShot* DamageRegion::player_shot() {
    auto* owner=context_value()->player();
    auto id=value_90;
    return owner->find_shot(id);
}
}

namespace th20 {
Enemy* EnemyController::find(std::uint32_t identifier) {
    if (!identifier) return nullptr;
    {
        auto& list=enemies;
        auto iterator=list.begin();
        auto* finish=list.end();
        for (;iterator.differs(finish);iterator.advance()) {
            auto* entry=iterator.get();
            if (entry->node_value()->state.identifier.get()==identifier) return entry->node_value();
        }
    }
    return nullptr;
}
EnemyHealth* Enemy::health_value() {return &state.health;}
void EnemyHealth::force_defeat() {flags.bits|=2;}
bool Enemy::reward_multiplier_enabled() {return (state.flags.word_04>>30)&1;}
void Enemy::set_damage_marker(std::uint32_t value) {state.flags.fields_08.damage_marked=value;}
}

namespace th20 {
std::uint32_t EnemyHandle::get() const {return value;}
void WeaponStoneInfo::record_damage(const Vector3* position,std::int32_t amount,std::int32_t type) {
    auto& value=counter;value.add_reward(position,amount,type);
}
}
