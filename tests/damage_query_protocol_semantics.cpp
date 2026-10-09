#include "EnemyController.hpp"
#include "DamageRegion.hpp"
#include <limits>
#include <cstdio>
// Reuse the existing actual construction/archive fixture. Its Player/Overlay
// destructor and activation bindings abort. ECL lifetime below is a fixture.
#define main unused_player_resource_main
#include "player_shot_data_semantics.cpp"
#undef main
namespace th20 {
std::uint32_t current_enemy_generation=1,previous_enemy_generation=0;
EclScriptPosition::EclScriptPosition() noexcept:subroutine(0),offset(0) {}
EclRuntime::EclRuntime() noexcept:time(0),async_id(0),manager(nullptr),signal(0),rank(0),flags{} {}
EclManager::EclManager():field_04(0),field_08(0),current_runtime(&main),loader(nullptr) {}
EclManager::~EclManager()=default;
Enemy::~Enemy()=default;
EnemyController::~EnemyController()=default;
int EclManager::execute_opcode(){std::abort();}
int EclManager::read_integer(int){std::abort();}
int* EclManager::integer_destination(int){std::abort();}
float EclManager::read_float(int){std::abort();}
float* EclManager::float_destination(int){std::abort();}
int Enemy::execute_opcode(){std::abort();}
int Enemy::read_integer(int){std::abort();}
int* Enemy::integer_destination(int){std::abort();}
float Enemy::read_float(int){std::abort();}
float* Enemy::float_destination(int){std::abort();}
int EnemyState::execute_opcode(){std::abort();}
struct RewardObservation { Vector3 position;int amount,type;unsigned calls; };
RewardObservation reward;
void OverlayCounter::add_reward(const Vector3* position,int amount,int type) {
    reward.position=*position;reward.amount=amount;reward.type=type;++reward.calls;
}
}
void exercise_protocols(th20::Player& player,th20::WeaponStoneInfo& overlay) {
    using namespace th20;
    PlayerRecord record;
    for (auto initial:{std::uint64_t(0),std::uint64_t(999999998),std::uint64_t(999999999),std::uint64_t(1000000000),~std::uint64_t(0)})
        for (auto delta:{std::uint64_t(0),std::uint64_t(1),std::uint64_t(9),std::uint64_t(10),std::uint64_t(20),~std::uint64_t(0)}) {
            record.score=initial;record.field_08=0x12345678;
            auto expected=initial+delta/10; if(expected>=1000000000)expected=999999999;
            record.add_score(delta);assert(record.score==expected && record.field_08==0x12345678);
        }
    session.table.players[0].score=0;session.table.players[1].score=47;
    session.add_score(~std::uint32_t(0));assert(session.table.players[0].score==429496729 && session.table.players[1].score==47);
    for (int previous:{-101,-1,0,1,101}) for(int current:{-101,-1,0,1,101}) {
        auto& timer=player.timer_644;timer.previous=previous;timer.current=current;
        assert(timer.changed()==(current!=previous) && player.frame_changed()==(current!=previous));
        for(int divisor:{-7,-1,1,7})assert(timer.every(divisor)==(current!=previous && current%divisor==0));
        if(current==previous)assert(timer.every(0)==0); // Native short circuit.
    }
    auto& shots=player.shots;
    assert(!shots.find(1));
    for(int i=0;i<256;++i) {
        auto& shot=shots.pool.slots[i];shot.state_14=static_cast<unsigned>(i+1);
        shot.link.node=&shot;shots.active.append(&shot.link);
    }
    for(int i=0;i<256;++i)assert(player.find_shot(i+1)==&shots.pool.slots[i]);
    assert(!shots.find(0) && !shots.find(257) && !shots.find(-2));
    shots.pool.slots[254].state_14=1;assert(shots.find(1)==&shots.pool.slots[0]);
    shots.pool.slots[255].state_14=~std::uint32_t(0);assert(shots.find(-1)==&shots.pool.slots[255]);
    Context isolated;isolated.object_04=&player;
    assert(isolated.player()==&player);DamageRegion region;region.context=&isolated;region.value_90=-1;
    assert(region.player_shot()==&shots.pool.slots[255]);region.value_90=257;assert(!region.player_shot());
    for(auto& shot:shots.pool.slots)assert(!shot.link.iterator); // Every return clears observers.
    while(shots.active.next) { shots.active.next->detach(); }
    assert(shots.active.tail==&shots.active);
    EnemyController controller;Enemy a,b,c;
    a.state.identifier.value=17;b.state.identifier.value=~std::uint32_t(0);c.state.identifier.value=17;
    controller.enemies.append(&a.controller_link);controller.enemies.append(&b.controller_link);controller.enemies.append(&c.controller_link);
    assert(controller.find(17)==&a && controller.find(~std::uint32_t(0))==&b);
    assert(!controller.find(0) && !controller.find(18));
    assert(!a.controller_link.iterator && !b.controller_link.iterator && !c.controller_link.iterator);
    a.controller_link.detach();assert(controller.find(17)==&c);
    b.controller_link.detach();c.controller_link.detach();assert(!controller.find(17));
    assert(a.health_value()==&a.state.health);
    for(unsigned flags:{0u,1u,2u,~0u,0x80000001u}) {
        a.state.health.flags.bits=flags;a.health_value()->force_defeat();assert(a.state.health.flags.bits==(flags|2));
        a.state.flags.word_04=flags;assert(a.reward_multiplier_enabled()==bool((flags>>30)&1));
        for(unsigned value:{0u,1u,2u,3u,~0u}) {
            a.state.flags.word_08=flags;a.set_damage_marker(value);
            assert(a.state.flags.word_08==((flags&~16u)|((value&1u)<<4)));
        }
    }
    EnemyHandle handle;handle.value=0xf1234567;assert(handle.get()==0xf1234567);
    Vector3 point;point.x=-1;point.y=2;point.z=3;
    for(int amount:{-10,0,1,1234567}) {
        auto before=reward.calls;overlay.record_damage(&point,amount,13);
        assert(reward.calls==before+1 && reward.amount==amount && reward.type==13 && reward.position.x==-1 && reward.position.y==2 && reward.position.z==3);
    }
}

int main() {
    using namespace th20;
    DiagnosticAllocator allocator;process_allocator=&allocator;
    auto* player=::new(::operator new(sizeof(Player))) Player;
    auto* overlay=::new(::operator new(sizeof(WeaponStoneInfo))) WeaponStoneInfo;
    exercise_protocols(*player,*overlay);
    std::destroy_at(&player->animation);player->TaskInfo::~TaskInfo();::operator delete(player);
    overlay->TaskInfo::~TaskInfo();::operator delete(overlay);
    std::puts("Actual query consumers: full shot/enemy searches, score width/cap, frame/period gating and flag preservation passed. ECL/startup/reward lifetime boundaries remain fixtures; whole query is uncalled.");
}
