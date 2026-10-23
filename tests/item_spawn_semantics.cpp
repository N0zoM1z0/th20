#include "Item.hpp"
#include "AnimationReleaseObserver.hpp"
#include "Session.hpp"
#include "GameRandom.hpp"
#include "Bullet.hpp"
#include "Weapon.hpp"
#include "WeaponStoneInfo.hpp"
#include "Player.hpp"
#include "DiagnosticObjectFactories.hpp"
#include "FunctionChainController.hpp"
#include "EnemyPattern.hpp"
#include <bit>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <limits>
#include <memory>
#include <vector>

namespace {
struct Event { th20::AnimationFile* file; th20::Animation* animation; int script; th20::Item* effect; };
std::vector<Event> events;
th20::ItemInf* tested_owner;
th20::BulletController* switch_controller;
bool switch_file, switch_context;
unsigned calls, releases;
std::function<void(th20::Item&)> effect_hook;
}
namespace th20 {
// Fixture startup and explicit unresolved gameplay interfaces. The complete
// primary spawn, all Item values/pools, RNG and binding wrapper are real.
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
FunctionChainController* process_chain;
GameRandom script_random(0);
DiagnosticAllocator::DiagnosticAllocator():state_word_(0),resource_() {}
const Matrix4 identity_matrix=[] {
    Matrix4 result; for(int i=0;i<4;++i)result.elements[i][i]=1; return result;
}();
std::int32_t ItemInf::update_callback(void*) {std::abort();}
std::int32_t ItemInf::draw_callback(void*) {std::abort();}
std::int32_t ItemInf::second_draw_callback(void*) {std::abort();}
// These fixtures retire only synthetic owners with no original resources.
// Genuine member destructors run automatically after the checked boundary.
BulletController::~BulletController() {
    assert(!update_node && !draw_node && !file && !free.next && !active.next);
    for(auto& b:pool)assert(!b.animation && !b.metadata && !b.link.owner);
}
void BulletController::enable() {std::abort();}
WeaponStoneInfo::~WeaponStoneInfo() {
    assert(!update_node && !draw_node && !animation_file && !mesh);
    assert(!weapon_28 && !weapon_2c && !weapon_30 && !weapon_34);
}
void WeaponStoneInfo::enable() {std::abort();}
Player::~Player() {std::abort();}
void Player::enable() {std::abort();}
void AnimationFile::clear() {
    assert(!bytes && !templates && !sprites && !scripts && !textures);
}
void AnimationFile::bind_animation(Animation* animation,std::int32_t script,Animation* parent) {
    assert(!parent); events.push_back({this,animation,script,nullptr}); ++calls;
    animation->base.color_490=0xabcdef01u;
    if(switch_file && calls==1)tested_owner->context->set_bullet_controller(switch_controller);
}
std::int32_t Item::spawn_effect() {
    events.push_back({nullptr,nullptr,0,this});
    if(switch_context)tested_owner->select_context(1);
    if(effect_hook)effect_hook(*this);
    return 0;
}
// The original thirty-slot virtual surface is never invoked by this protocol.
// Explicit abort-only fixture definitions supply its host vtable; no original
// virtual gameplay behavior or full-link claim is made.
void Weapon::reset(){std::abort();}
void Weapon::initialize_main(){std::abort();}
void Weapon::shoot_main(int,int,int){std::abort();}
void Weapon::shoot_focused(int,int,int){std::abort();}
void Weapon::shoot_unfocused(int,int,int){std::abort();}
const Vector2* Weapon::focused_offset(int,int){std::abort();}
const Vector2* Weapon::unfocused_offset(int,int){std::abort();}
void Weapon::activate_main(){std::abort();}
void Weapon::activate_focused(){std::abort();}
void Weapon::activate_unfocused(){std::abort();}
void Weapon::initialize_focused_option(PlayerOption*,int){std::abort();}
void Weapon::initialize_unfocused_option(PlayerOption*,int){std::abort();}
void Weapon::update_focused_option(PlayerOption*,int){std::abort();}
void Weapon::update_unfocused_option(PlayerOption*,int){std::abort();}
void Weapon::initialize_passive(){std::abort();}
void Weapon::update_main(){std::abort();}
void Weapon::update_focused(){std::abort();}
void Weapon::update_unfocused(){std::abort();}
void Weapon::update_passive(){std::abort();}
int Weapon::script_variant(){std::abort();}
void Weapon::start_phase(){std::abort();}
int Weapon::update_phase(){std::abort();}
int Weapon::end_phase(){std::abort();}
int Weapon::cancel_phase(){std::abort();}
const Vector3* Weapon::phase_position(){std::abort();}
int Weapon::shot_script_index(){std::abort();}
bool Weapon::phase_active(){std::abort();}
bool Weapon::unfocused_shooting(){std::abort();}
bool Weapon::focused_shooting(){std::abort();}
bool Weapon::passive_active(){std::abort();}
}
namespace {
using namespace th20;
constexpr int scripts[16][2]={{-1,-1},{115,137},{116,138},{117,139},{118,140},
    {119,141},{120,142},{121,143},{122,144},{123,-1},{124,-1},{125,-1},{126,-1},{127,-1},{128,-1},{-1,-1}};
void reset(ItemInf& owner) {
    events.clear();calls=0;switch_file=false;switch_context=false;
    effect_hook={};
    // No ANM resources are installed by the capture-only dependency. No live
    // iterator may survive this original whole-pool byte initialization.
    for(auto& item:owner.pool) {
        assert(!item.link.iterator && !item.animation.geometry && !item.secondary_animation.geometry);
        assert(!item.animation.callback && !item.secondary_animation.callback);
    }
    owner.initialize_pool();owner.select_context(0);tested_owner=&owner;
    player_record(0)->field_a5=0;player_record(0)->field_2f=0;
    player_table().field_1e0=0;owner.special_count=0;
}
Item* spawn(ItemInf& owner,int type,const Vector3& pos,int delay=7) {
    return owner.spawn(type,pos,0x12345678u,0.3f,2.5f,delay,0x76543210u,-7);
}
void timer_zero(const Timer& timer) {
    assert(timer.current==0 && timer.previous==-1 && timer.current_fraction==0 && (timer.flags&1));
}
void ordinary(ItemInf& owner,AnimationFile& file) {
    for(int type:{0,1,2,3,4,5,6,7,8,14}) {
        reset(owner);owner.select_context(1);
        auto& first=owner.pool[0];first.angle=77;first.generation=88;
        first.attachment.value=99;first.timer.flags=5;
        Vector3 p(200,17,99);auto* item=spawn(owner,type,p);
        assert(item==&first && item->link.owner==&owner.active && owner.active.next==&item->link);
        assert(owner.ordinary_free.front()==&owner.pool[1].link && item->free_list==&owner.ordinary_free);
        assert(item->state==1 && item->type==(type==14?6:type) && !item->draw_state);
        assert(item->position.x==192 && item->position.y==17 && !item->position.z);
        assert(!item->velocity.z && std::abs(std::hypot(item->velocity.x,item->velocity.y)-2.5f)<1e-5f);
        assert(!item->speed && !item->attraction_speed && item->angle==77 && item->generation==88);
        assert(item->delay==7 && item->extra==0x76543210u && item->sound==-7);
        assert(item->view_index==1 && item->context==&session.context(1));
        assert(!item->attachment.value && item->animation.base.color_490==0x12345678u);
        assert(item->secondary_animation.base.color_490==0xabcdef01u);
        timer_zero(item->timer);assert(item->timer.flags==5);
        const int mapped=type==14?6:type;
        assert(events.size()==2 && events[0].file==&file && events[1].file==&file);
        assert(events[0].animation==&item->animation && events[1].animation==&item->secondary_animation);
        assert(events[0].script==scripts[mapped][0] && events[1].script==scripts[mapped][1]);
    }
    for(float x:{-200.f,-192.f,-191.5f,192.f,200.f,
                 -std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity(),
                 std::bit_cast<float>(0x7fc12345u)}) {
        reset(owner);Vector3 p(x,2,3);auto* item=spawn(owner,0,p);
        const float expected=x<=-192.f?-192.f:(x>=192.f?192.f:x);
        assert(std::bit_cast<unsigned>(item->position.x)==std::bit_cast<unsigned>(expected));
    }
    reset(owner);owner.ordinary_free.front()->node=nullptr;
    Vector3 p(1,2,3);assert(!spawn(owner,2,p) && owner.spawn_counter==1 && events.empty());
    assert(owner.ordinary_free.front()==&owner.pool[0].link && !owner.active.next);
    reset(owner);const auto random=script_random.last;
    assert(!spawn(owner,16,p) && !spawn(owner,99,p) && !owner.spawn_counter);
    assert(events.empty() && script_random.last==random);
}
void specials(ItemInf& owner) {
    Vector3 p(300,2,9);
    for(int type=9;type<=13;++type) for(int threshold:{-1,0,255,256,511,512,1023,1024})
    for(int count:{0,-2,std::numeric_limits<int>::max()}) {
        reset(owner);owner.special_count=threshold;owner.spawn_counter=count;owner.generation=73;
        owner.select_context(1);auto& first=owner.pool[512];first.link.node=nullptr;
        first.attachment.value=12;first.timer.flags=5;
        {
            IntrusiveIterator<Item> iterator(&first.link);
            auto* item=spawn(owner,type,p);
            assert(item==&first && !iterator.current && iterator.pending==&owner.pool[513].link);
            assert(!item->link.iterator && item->link.owner==&owner.active);
            const int next=static_cast<int>(static_cast<unsigned>(count)+1u);
            const int divisor=threshold>=1024?32:threshold>=512?16:threshold>=256?8:4;
            const int offset=threshold>=1024?16:threshold>=512?8:threshold>=256?4:0;
            assert(item->delay==next%divisor+offset && owner.spawn_counter==next);
            assert(item->generation==73 && item->state==5 && item->type==type && !item->draw_state);
            assert(item->position.x==300 && item->position.y==2 && !item->position.z);
            assert(!item->velocity.z && item->angle==0.3f && item->speed==2.5f);
            assert(item->extra==0x76543210u && item->sound==-7 && item->view_index==1);
            assert(item->context==&session.context(1) && item->free_list==&owner.special_free);
            assert(item->attachment.value==12 && events.empty() && owner.special_count==threshold);
            timer_zero(item->timer);assert(item->timer.flags==5);
        }
    }
    reset(owner);
    for(int i=0;i<1024;++i)assert(spawn(owner,9,p)==&owner.pool[512+i]);
    assert(!owner.special_free.front());assert(!spawn(owner,9,p) && owner.spawn_counter==1025);
    reset(owner);
    for(int i=0;i<512;++i)assert(spawn(owner,2,p)==&owner.pool[i]);
    assert(!owner.ordinary_free.front());
    // Empty ordinary head violates the native precondition; never manufacture
    // a safe return by calling the original protocol after exhaustion.
}
void points(ItemInf& owner) {
    Vector3 p(1,2,3);reset(owner);owner.select_context(1);owner.point_counter=8;
    assert(!spawn(owner,15,p) && owner.point_counter==9 && owner.spawn_counter==1);
    assert(spawn(owner,15,p)==&owner.pool[0] && !owner.point_counter && owner.pool[0].type==2);
    assert(owner.spawn_counter==2 && events.size()==2 && events[0].script==116);
    for(int mode:{1,2,-2,std::numeric_limits<int>::max()}) {
        reset(owner);owner.point_counter=8;player_table().field_1e0=mode;
        int expected=static_cast<int>(8u+static_cast<unsigned>(mode)+1u);
        auto* item=spawn(owner,15,p);
        assert((item!=nullptr)==(expected>=10));
        assert(owner.point_counter==(expected>=10?0:expected) && owner.spawn_counter==1);
    }
    reset(owner);owner.point_counter=std::numeric_limits<int>::max();
    assert(!spawn(owner,15,p) && owner.point_counter==std::numeric_limits<int>::min());
}
float sample(unsigned raw,unsigned modulus) {
    return static_cast<float>(raw)/(static_cast<float>(modulus)/2.f-1.f)-1.f;
}
void bonuses(ItemInf& owner,Weapon& weapon) {
    Vector3 p(20,30,40);
    for(bool extended:{false,true}) {
        reset(owner);owner.select_context(1);weapon.passive=0;
        player_record(0)->field_a5=2;player_record(0)->field_2f=extended?7:0;
        player_record(1)->field_a5=0;player_record(1)->field_2f=0;
        owner.bonus_counter=extended?12:8;script_random.seed(1);
        auto* item=spawn(owner,1,p,0);
        assert(item==&owner.pool[1] && owner.bonus_counter==(extended?14:10));
        assert(weapon.passive==1 && !weapon.active && owner.spawn_counter==2);
        assert(script_random.last==182605794u);
        auto& child=owner.pool[0];
        assert(child.position.y==sample(48271,script_random.modulus)*16.f+p.y);
        assert(child.position.x==sample(182605794,script_random.modulus)*16.f+p.x);
        assert(!child.position.z && child.delay==16 && item->delay==0);
        assert(owner.active.next==&item->link && item->link.next==&child.link);
        assert(events.size()==5 && events[2].effect==item);
        assert(events[0].animation==&child.animation && events[1].animation==&child.secondary_animation);
        assert(events[3].animation==&item->animation && events[4].animation==&item->secondary_animation);
        assert(child.extra==item->extra && child.animation.base.color_490==item->animation.base.color_490);
    }
    reset(owner);player_record(0)->field_a5=1;owner.bonus_counter=8;script_random.seed(1);
    auto* item=spawn(owner,1,p,std::numeric_limits<int>::max());
    assert(item==&owner.pool[1] && owner.pool[0].delay==std::numeric_limits<int>::min()+15);
    reset(owner);player_record(0)->field_a5=1;owner.bonus_counter=std::numeric_limits<int>::max();
    script_random.seed(1);assert(spawn(owner,1,p) && owner.bonus_counter==std::numeric_limits<int>::min());
    assert(script_random.last==1 && owner.spawn_counter==1);
}
struct PatternRandom {
    std::uint32_t state;
    explicit PatternRandom(std::uint32_t seed):state(seed%2147483647u) {
        if(!state)state=1;
    }
    std::uint32_t next() {
        state=static_cast<std::uint32_t>(std::uint64_t(state)*48271u%2147483647u);
        return state;
    }
    float radians() {return (float(next())/(float(2147483647u)/2.f-1.f)-1.f)*3.1415927410125732f;}
    float unit() {return float(next())/(float(2147483647u)-1.f);}
};
std::int64_t signed_bits(std::uint32_t word) {
    return word<0x80000000u?word:std::int64_t(word)-0x100000000LL;
}
struct PatternSpawn {int type;float x,y;};
std::vector<PatternSpawn> model_pattern(const EnemyPattern& pattern,const Vector3& origin,
                                      bool bomb_mark,PatternRandom& random) {
    constexpr float pi=3.1415927410125732f;
    std::vector<PatternSpawn> result;
    const int first=pattern.bomb_kind&&!bomb_mark?pattern.bomb_kind:pattern.base_kind;
    if(first)result.push_back({first,origin.x,origin.y});
    float angle=random.radians();
    for(unsigned i=0;i<15;++i) {
        std::uint32_t bits=pattern.counts[i];
        const auto extra=signed_bits(pattern.extra_counts[i]);
        const auto duration=signed_bits(pattern.duration);
        if(duration && pattern.timer.current<duration && extra>0) {
            const auto low=static_cast<std::uint32_t>(std::uint64_t(
                static_cast<std::uint32_t>(pattern.timer.current))*pattern.extra_counts[i]);
            const auto product=signed_bits(low);
            assert(!(product==-2147483648LL && duration==-1));
            bits=static_cast<std::uint32_t>(std::uint64_t(bits)+pattern.extra_counts[i]-product/duration);
        }
        const auto count=signed_bits(bits);
        assert(count<=64);
        for(std::int64_t n=0;n<count;++n) {
            const float scale=random.unit()*.5f+.5f;
            const float x=static_cast<float>(std::cos(angle))*pattern.radius_x;
            const float y=static_cast<float>(std::sin(angle))*pattern.radius_y;
            result.push_back({int(i)+1,x*scale+origin.x,y*scale+origin.y});
            angle=(pi/2.f+angle)+random.radians()/4.f;
            while(angle>pi)angle-=2.f*pi;
            while(angle<-pi)angle+=2.f*pi;
        }
    }
    return result;
}
void check_pattern_items(ItemInf& owner,const std::vector<PatternSpawn>& spawns) {
    std::vector<Item*> emitted;
    unsigned ordinary_index=0,special_index=512,attempts=0;
    int points=8;
    for(const auto& expected:spawns) {
        if(expected.type>=16)continue;
        ++attempts;
        int type=expected.type;
        const bool special=type>=9&&type<=13;
        if(type==15) {
            if(++points<10)continue;
            points=0;type=2;
        }
        if(type==14)type=6;
        auto* item=&owner.pool[special?special_index++:ordinary_index++];
        emitted.push_back(item);
        const float x=special?expected.x:std::clamp(expected.x,-192.f,192.f);
        assert(item->type==type && item->state==(special?5:1));
        assert(std::abs(item->position.x-x)<0.0002f && std::abs(item->position.y-expected.y)<0.0002f);
        assert(item->position.z==0 && item->velocity.z==0 && item->extra==0 && item->sound==-1);
        assert(std::abs(std::hypot(item->velocity.x,item->velocity.y)-2.2f)<0.00001f);
        assert(item->delay==(special?int(attempts%4):0));
        if(!special)assert(item->animation.base.color_490==0xffffffffu);
    }
    assert(owner.spawn_counter==int(attempts) && owner.point_counter==points);
    auto* node=owner.active.next;
    for(auto it=emitted.rbegin();it!=emitted.rend();++it) {
        assert(node==&(*it)->link);node=node->next;
    }
    assert(!node);
}
void patterns(ItemInf& owner) {
    unsigned scenarios=0;
    for(unsigned seed:{1u,37u,0xfffffffeu})for(unsigned duration:{0u,4u,0xfffffffdu})
    for(int time:{-4,-1,0,3,4})for(bool bomb_mark:{false,true})
    for(int base:{0,2,9})for(int bomb:{0,14}) {
        reset(owner);session.context(0).set_item_controller(&owner);owner.point_counter=8;
        EnemyPattern pattern;
        pattern.base_kind=base;pattern.bomb_kind=bomb;pattern.duration=duration;
        pattern.radius_x=53;pattern.radius_y=-27;
        pattern.timer.current=time;pattern.timer.previous=31;
        pattern.timer.current_fraction=-15.5f;pattern.timer.flags=0xf3;
        pattern.counts.fill(1);pattern.counts[14]=2;pattern.counts[15]=0x7fffffffu;
        for(unsigned i=0;i<16;++i)pattern.extra_counts[i]=i%5==0?2u:0x80000000u;
        Vector3 origin(211,42,73);
        PatternRandom random(seed);
        const auto expected=model_pattern(pattern,origin,bomb_mark,random);
        auto image=pattern;image.counts.fill(0);image.base_kind=0;
        script_random.seed(seed);pattern.drop(origin,bomb_mark);
        assert(script_random.last==random.state && !std::memcmp(&pattern,&image,sizeof(pattern)));
        check_pattern_items(owner,expected);++scenarios;
    }
    // A low-word product wrap can leave a small positive emission count.
    reset(owner);owner.point_counter=8;EnemyPattern wrapped;
    wrapped.counts[1]=0xc0000000u;wrapped.extra_counts[1]=0x40000001u;
    wrapped.duration=5;wrapped.timer.current=4;
    Vector3 origin(7,8,9);PatternRandom random(123);
    auto expected=model_pattern(wrapped,origin,false,random);
    script_random.seed(123);wrapped.emit_items(origin);
    assert(script_random.last==random.state && expected.size()==1);
    check_pattern_items(owner,expected);
    reset(owner);owner.point_counter=8;EnemyPattern empty;
    empty.counts[15]=0xffffffffu;empty.extra_counts[15]=0x7fffffffu;
    script_random.seed(19);PatternRandom zero_random(19);zero_random.next();
    empty.emit_items(origin);
    assert(!owner.spawn_counter && !owner.active.next && script_random.last==zero_random.state);
    assert(empty.counts[15]==0 && empty.extra_counts[15]==0x7fffffffu);
    // Callbacks change the borrowed origin and later fields, but the current
    // kind's count remains cached. Each item looks up the current player again.
    auto second=std::make_unique<ItemInf>();reset(*second);reset(owner);
    session.context(0).set_item_controller(&owner);session.context(1).set_item_controller(second.get());
    EnemyPattern live;live.base_kind=2;live.counts[1]=2;
    Vector3 borrowed(1,2,3);unsigned effects=0;
    effect_hook=[&](Item& item) {
        if(++effects==1) {
            assert(&item==&owner.pool[0] && item.position.x==1);
            live.player=1;borrowed.x=20;live.counts[1]=3;
            live.base_kind=99;script_random.next();
        } else if(effects==2) {
            assert(&item==&second->pool[0] && item.position.x==20);
            live.counts[1]=0;live.counts[3]=2;borrowed.x=30;
        }
        assert(live.base_kind==99);
    };
    script_random.seed(71);live.drop(borrowed,true);effect_hook={};
    PatternRandom live_random(71);for(int i=0;i<12;++i)live_random.next();
    assert(effects==6 && owner.spawn_counter==1 && second->spawn_counter==5);
    assert(script_random.last==live_random.state && live.base_kind==0 && live.player==1);
    for(auto count:live.counts)assert(!count);
    for(unsigned i=0;i<5;++i) {
        assert(second->pool[i].type==(i<3?2:4));
        assert(second->pool[i].position.x==(i?30:20));
    }
    session.context(0).set_item_controller(&owner);session.context(1).set_item_controller(&owner);
    std::printf("Enemy drop integration passed: %u independent count/LCG/pool models, low-word wrap, zero-count RNG and live origin/count/player callbacks.\n",scenarios+3);
}
void ordering(ItemInf& owner,BulletController& first,BulletController& second,
              AnimationFile& file0,AnimationFile& file1) {
    Vector3 p(1,2,3);reset(owner);session.context(0).set_bullet_controller(&first);
    switch_controller=&second;switch_file=true;
    auto* item=spawn(owner,2,p);
    assert(events.size()==2 && events[0].file==&file0 && events[1].file==&file1);
    assert(item->context==&session.context(0) && item->animation.base.color_490==0x12345678u);
    reset(owner);session.context(0).set_bullet_controller(&first);switch_context=true;
    item=spawn(owner,2,p,0);
    assert(item->context==&session.context(0) && owner.context==&session.context(1));
    assert(events.size()==3 && events[0].effect==item);
    assert(events[1].file==&file1 && events[2].file==&file1);
    reset(owner);session.context(0).set_bullet_controller(&first);
    script_random.seed(37);owner.spawn_many(&p,3,3);
    assert(owner.spawn_counter==3 && events.size()==9 && calls==6);
    for(int i=0;i<3;++i)assert(owner.pool[i].type==3 && owner.pool[i].animation.base.color_490==0xffffffffu);
}
}
int main() {
    using namespace th20;
    DiagnosticAllocator allocator;process_allocator=&allocator;
    FunctionChainController scheduler;process_chain=&scheduler;process_locks.enable();
    session.context(0).current_player=&session.table.players[0];
    session.context(1).current_player=&session.table.players[1];
    AnimationFile file0,file1;
    auto first=std::make_unique<BulletController>();auto second=std::make_unique<BulletController>();
    first->file=&file0;second->file=&file1;
    session.context(0).set_bullet_controller(first.get());session.context(1).set_bullet_controller(second.get());
    Weapon weapon;assert(!weapon.stone_id && !weapon.field_08 && !weapon.role && weapon.field_10==1);
    assert(!weapon.active && !weapon.passive && !weapon.timer_14.flags && !weapon.timer_24.flags);
    WeaponStoneInfo overlay;overlay.weapon_34=&weapon;session.context(0).overlay_owner=&overlay;
    auto owner=std::make_unique<ItemInf>();
    ordinary(*owner,file1);specials(*owner);points(*owner);bonuses(*owner,weapon);
    ordering(*owner,*first,*second,file0,file1);
    patterns(*owner);
    for(auto& item:owner->pool)
        for(auto* animation:{&item.animation,&item.secondary_animation})
            new th20_test::AnimationReleaseObserver(animation,releases);
    const auto before=releases;owner.reset();assert(releases-before==3072);
    session.context(0).set_item_controller(nullptr);session.context(1).set_item_controller(nullptr);
    session.context(0).overlay_owner=nullptr;overlay.weapon_34=nullptr;
    session.context(0).set_bullet_controller(nullptr);session.context(1).set_bullet_controller(nullptr);
    session.context(0).current_player=nullptr;session.context(1).current_player=nullptr;
    first->file=nullptr;second->file=nullptr;first.reset();second.reset();
    process_locks.disable();process_chain=nullptr;process_allocator=nullptr;
    std::puts("Complete primary Item spawn passed: real pools/lists/observer lifetime, signed counters and special delays, ordinary clamp including NaN, global bonus recursion and Y-before-X real RNG, real Weapon storage/lifetime, captured unresolved effect/parent binding, two separate file reads and actual bulk spawn. No original ANM VM/effect/virtual gameplay/runtime claim.");
}
