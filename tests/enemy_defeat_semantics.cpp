#include "EnemyController.hpp"
#include "ItemResourceOwners.hpp"
#include "Player.hpp"
#include "Session.hpp"
#include "SoundInf.hpp"
#include "WeaponStoneInfo.hpp"
#include "Graphics.hpp"
#include "DiagnosticAllocator.hpp"
#include "Card.hpp"
#include <array>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <limits>
#include <memory>
#include <stdexcept>
#include <vector>

namespace {
enum Step { sound=1,file_lookup,spawn,drop,feedback,stone,reward,terminate,reset,select_script,tick,callback };
struct Event { Step step; th20::Enemy* actor; };
std::vector<Event> events;
std::vector<th20::Enemy*> actors;
th20::Enemy* active;
std::function<void(Step)> hook;
unsigned throw_at;
int level,gate_after,expected_reward,expected_kind;
unsigned output_handle;
th20::AnimationFile* selected_file;
th20::WeaponStoneInfo* selected_stone;
void note(Step step) {
    events.push_back({step,active});
    if(throw_at && events.size()==throw_at)throw std::runtime_error("Captured native interface failure");
    if(hook)hook(step);
}
template<class T> auto image(const T& value) {
    std::array<unsigned char,sizeof(T)> result;std::memcpy(result.data(),&value,sizeof(value));return result;
}
template<class T,class V> void patch(std::array<unsigned char,sizeof(T)>& out,const T& owner,const V& member,const V& value) {
    auto offset=reinterpret_cast<const unsigned char*>(&member)-reinterpret_cast<const unsigned char*>(&owner);
    std::memcpy(out.data()+offset,&value,sizeof(value));
}
int wrapped_add_clamp(int first,int second,int limit) {
    const auto bits=(std::uint64_t(static_cast<unsigned>(first))+static_cast<unsigned>(second))&0xffffffffu;
    const auto signed_value=bits<0x80000000u?static_cast<std::int64_t>(bits):static_cast<std::int64_t>(bits)-0x100000000ll;
    return static_cast<int>(signed_value<0?0:signed_value>limit?limit:signed_value);
}
unsigned next_random(unsigned value) {return static_cast<unsigned>((std::uint64_t(value)*48271u)%2147483647u);}
int reward_value(int base,int multiplier) {
    auto bits=(std::uint64_t(static_cast<unsigned>(base))*static_cast<unsigned>(multiplier))&0xffffffffu;
    auto signed_value=bits<0x80000000u?static_cast<std::int64_t>(bits):static_cast<std::int64_t>(bits)-0x100000000ll;
    return static_cast<int>(signed_value/100);
}
}

namespace th20 {
// Explicit resource-free startup and still-unreconstructed VM/resource lifetimes.
// The fixture instantiates maintained Actor, State, Controller Data, Player,
// record, interpolation, list and handle owners. The captures below delimit
// unresolved native lifetimes and calls.
LockRegistry process_locks;
DiagnosticAllocator::DiagnosticAllocator():state_word_(0),resource_() {}
DiagnosticAllocator allocator;
DiagnosticAllocator* process_allocator=&allocator;
std::uint32_t current_enemy_generation=1,previous_enemy_generation=0;
GameRandom script_random(0);
SoundInf process_sound;
SoundInf::SoundInf() noexcept=default;
SoundInf::~SoundInf()=default;
Graphics process_graphics;
Graphics::~Graphics()=default;
const Matrix4 identity_matrix=[] {Matrix4 result;for(int i=0;i<4;++i)result.elements[i][i]=1;return result;}();
Card::~Card()=default;
TaskInfo::~TaskInfo()=default;
void TaskInfo::enable(){std::abort();}
void TaskInfo::disable(){std::abort();}
EclScriptPosition::EclScriptPosition() noexcept:subroutine(0),offset(0) {}
EclRuntime::EclRuntime() noexcept:time(0),async_id(0),manager(nullptr),signal(0),rank(0),flags{} {}
EclManager::EclManager():field_04(0),field_08(0),current_runtime(&main),loader(nullptr) {}
EclManager::~EclManager()=default;
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
Enemy::~Enemy()=default;
EnemyController::EnemyController() noexcept:field_c4(0),field_c8(0),field_cc(0),field_e0(0),animation_files{},loader(nullptr),field_120(0),field_124(0),player_index(0),context(nullptr) {}
EnemyController::~EnemyController()=default;
Player::~Player()=default;
void Player::enable(){std::abort();}
WeaponStoneInfo::~WeaponStoneInfo()=default;
void WeaponStoneInfo::enable(){std::abort();}
StoneEnemyController::~StoneEnemyController()=default;
StoneEnemyController* process_stone_enemies;
WeaponStoneInfo* weapon_stone_info(int index) {
    assert(index==0);return selected_stone;
}
EffectInfo::EffectInfo():files{},field_1c(0),handle_cursor(0),field_24(0),ready(0),view_index(0),context(nullptr) {}
EffectInfo::~EffectInfo()=default;
StoneMenuInfo::~StoneMenuInfo()=default;
void AnimationFile::clear(){assert(!bytes && !templates && !sprites && !scripts && !textures);}
int ScriptStack::pop(int,void*,char){std::abort();}
void EclManager::terminate_async(){active=static_cast<Enemy*>(this);note(terminate);}
void EclManager::reset(){active=static_cast<Enemy*>(this);note(::reset);}
std::int32_t EclManager::select_subroutine_index(std::int32_t index) {
    active=static_cast<Enemy*>(this);assert(index==active->state.field_27c);note(select_script);return 0;
}
int EclManager::tick(float delta){active=static_cast<Enemy*>(this);assert(delta==0 && !std::signbit(delta));note(::tick);return 0;}
void SoundInf::request_effect_at(int id,float x) {
    assert(this==&process_sound);bool found=false;
    for(auto* actor:actors)if(actor->state.field_250==id){active=actor;found=true;break;}
    assert(found && x==active->state.motion_110.position.x);note(sound);
}
AnimationFile* EnemyController::animation_file(int index) {
    assert(this==active->context->enemies && index==active->state.field_258);note(file_lookup);return selected_file;
}
AnimationHandle AnimationFile::spawn(const char* stem,int script,const Vector3& position,float rotation,int layer,Animation** output) {
    assert(this==selected_file && !stem && script==active->state.field_254);
    assert(&position==&active->state.motion_110.position && layer==-1 && !output && std::isfinite(rotation));
    note(::spawn);AnimationHandle result;result.value=output_handle;return result;
}
Animation* AnimationHandle::resolve(){std::abort();}
void EnemyPattern::drop(const Vector3& position,bool marked) {
    bool found=false;for(auto* actor:actors)if(this==&actor->state.pattern){active=actor;found=true;break;}
    assert(found && &position==&active->state.motion_110.position);
    assert(marked==bool(active->state.flags.word_08&32u));note(::drop);
}
void PlayerFeedback::record_hit(int value) {
    assert(value==active->state.field_26c);note(::feedback);field_30=static_cast<unsigned>(level);
}
void OverlayCounter::add_reward(const Vector3* position,int amount,int kind) {
    assert(this==&selected_stone->counter && position==&active->state.motion_110.position);
    assert(amount==2000 && kind==expected_kind+9);note(::stone);
    process_stone_enemies->byte_b0=static_cast<std::uint8_t>(gate_after);
}
void PlayerRecord::add_reward(int kind,int amount) {
    assert(this==&session.table.players[0] && amount==expected_reward);
    int selected=expected_kind;
    if(selected==4)selected=static_cast<int>(script_random.last%8u);
    else selected=starting_configuration(selected);
    assert(kind==selected);note(::reward);
}
}

namespace {
struct World {
    th20::Enemy actor;
    th20::EnemyController first,second;
    th20::AnimationFile file;
    std::unique_ptr<th20::EffectInfo> fx=std::make_unique<th20::EffectInfo>();
    std::unique_ptr<th20::Player> player=std::make_unique<th20::Player>();
    th20::WeaponStoneInfo overlay;
    th20::StoneEnemyController gate;
    World(){selected_file=&file;selected_stone=&overlay;th20::process_stone_enemies=&gate;}
};
void prepare(World& world) {
    using namespace th20;
    auto& a=world.actor;active=&a;actors={&a};events.clear();hook={};throw_at=0;
    a.children.reset(&a);a.parent_link.initialize(&a);
    a.context=&session.contexts[0];a.state.context=&session.contexts[1];a.state.entity=&a;
    for(auto& context:session.contexts){context.enemies=&world.first;context.object_20=world.fx.get();context.object_04=world.player.get();context.current_player=&session.table.players[0];context.overlay_owner=&world.overlay;}
    session.contexts[1].enemies=&world.second;
    a.state.flags.word_00=0x10000;a.state.flags.word_04=0x4000;a.state.flags.word_08=0;
    a.state.field_250=-1;a.state.field_254=-1;a.state.field_258=1;a.state.field_26c=17;a.state.field_278=10;a.state.field_27c=-1;
    a.state.vector_6c={0,0,123};a.state.motion_110.position={1,0,-999};a.callback=nullptr;
    world.first.angle_128.value=91;world.second.angle_128.value=93;
    world.gate.byte_b0=0;world.fx->handle_cursor=1023;
    for(auto& entry:world.fx->handles)entry.handle.value=0;
    world.player->feedback.field_30=0;
    auto& record=session.table.players[0];record.field_44=999999;record.field_5c=9999;
    record.field_0c=2;record.field_14=3;record.field_10=5;record.field_18=7;
    level=0;gate_after=0;expected_reward=0;expected_kind=0;output_handle=0x12345678u;
    script_random.seed(1);
}
std::vector<Step> step_values(){std::vector<Step> out;for(auto e:events)out.push_back(e.step);return out;}
void matrix(World& world) {
    using namespace th20;unsigned scenarios=0;
    constexpr std::array<int,10> multipliers{100,150,200,250,300,400,500,600,700,800};
    constexpr std::array<int,7> bases{std::numeric_limits<int>::min(),-17,0,1,17,std::numeric_limits<int>::max(),306783379};
    constexpr float pi=3.1415927410125732f;
    for(bool audio:{false,true})for(bool effect:{false,true})for(bool marked:{false,true})for(bool no_drop:{false,true})
    for(int count:{0,3,9,15})for(unsigned seed:{1u,2u,3u,4u,5u})for(int first_gate:{0,1})for(int next_gate:{0,1})
    for(int script:{-1,17})for(bool preserve:{false,true})for(bool has_callback:{false,true}) {
        prepare(world);auto& a=world.actor;auto& state=a.state;
        state.field_250=audio?5:-1;state.field_254=effect?37:-1;
        state.flags.word_08=(marked?16u:0u)|(no_drop?32u:0u);state.flags.word_04|=preserve?0x8000000u:0u;
        state.field_278=bases[scenarios%bases.size()];state.field_27c=script;level=count;
        int position_case=static_cast<int>(scenarios%4);if(position_case==0)state.motion_110.position.x=0;
        if(position_case==2)state.motion_110.position.x=0.2f;
        if(position_case==3)state.motion_110.position={0,1,-999};
        float direction=position_case==0?-pi/2.f:position_case==3?pi/2.f:0.f;
        world.gate.byte_b0=static_cast<std::uint8_t>(first_gate);gate_after=next_gate;script_random.seed(seed);
        const unsigned first=next_random(seed);expected_kind=static_cast<int>(first%5u);
        const unsigned last=marked?(expected_kind==4 && !next_gate?next_random(first):first):seed;
        expected_reward=reward_value(state.field_278,multipliers[count>=10?9:count]);
        if(has_callback)a.callback=[&](Enemy* actor){assert(actor==&a);active=actor;note(::callback);};
        auto expected_actor=image(a);auto expected_first=image(world.first);auto expected_second=image(world.second);
        auto expected_record=image(session.table.players[0]);auto expected_feedback=image(world.player->feedback);
        patch(expected_first,world.first,world.first.angle_128.value,direction);
        if(script!=-1)patch(expected_actor,a,state.field_27c,-1);
        if(marked){auto& record=session.table.players[0];patch(expected_record,record,record.field_44,wrapped_add_clamp(999999,expected_reward,1000000));
            if(!first_gate)patch(expected_record,record,record.field_5c,wrapped_add_clamp(9999,expected_reward,10000));
            patch(expected_feedback,world.player->feedback,world.player->feedback.field_30,static_cast<unsigned>(count));}
        std::vector<Step> expected;if(audio)expected.push_back(sound);if(effect){expected.push_back(file_lookup);expected.push_back(spawn);}expected.push_back(drop);
        if(marked){expected.push_back(feedback);expected.push_back(stone);if(!next_gate)expected.push_back(reward);}
        if(script!=-1){expected.push_back(terminate);expected.push_back(reset);expected.push_back(select_script);expected.push_back(tick);}
        const bool ended=script!=-1&&preserve;if(has_callback&&!ended)expected.push_back(callback);
        assert(a.defeat()==(ended?0:1));
        assert(step_values()==expected && image(a)==expected_actor && image(world.first)==expected_first && image(world.second)==expected_second);
        assert(image(session.table.players[0])==expected_record && image(world.player->feedback)==expected_feedback);
        assert(script_random.last==last && world.gate.byte_b0==(marked?next_gate:first_gate));
        assert(world.fx->handle_cursor==(effect?0:1023) && world.fx->handles[1023].handle.value==(effect?output_handle:0));
        for(auto* actor:actors)assert(!actor->parent_link.iterator);
        ++scenarios;
    }
    std::printf("PASS %u whole defeat matrix cases: real owners, publication, counters, RNG, script return and callback order.\n",scenarios);
}
void failures(World& world) {
    using namespace th20;
    const std::vector<Step> expected{sound,file_lookup,spawn,drop,feedback,stone,reward,terminate,reset,select_script,tick,callback};
    for(unsigned ordinal=1;ordinal<=expected.size();++ordinal) {
        prepare(world);auto& a=world.actor;a.state.field_250=5;a.state.field_254=37;a.state.flags.word_08=16;a.state.field_27c=17;
        expected_kind=1;expected_reward=10;level=0;gate_after=0;throw_at=ordinal;
        a.callback=[&](Enemy* actor){assert(actor==&a);active=actor;note(::callback);};
        bool threw=false;try{a.defeat();}catch(const std::runtime_error&){threw=true;}
        assert(threw && step_values()==std::vector<Step>(expected.begin(),expected.begin()+ordinal));
        assert(a.state.field_27c==(ordinal==12?-1:17) && !a.parent_link.iterator);
    }
    std::puts("PASS 12 whole defeat interface failures: exact event prefixes and late caller writes.");
}
void topology(World& world) {
    using namespace th20;
    for(int action=0;action<5;++action) {
        prepare(world);Enemy child,next,alternate;
        std::array<Enemy*,3> extras{&child,&next,&alternate};
        for(unsigned i=0;i<extras.size();++i){auto* e=extras[i];e->parent_link.initialize(e);e->children.reset(e);e->context=world.actor.context;e->state.field_250=10+static_cast<int>(i);e->state.field_254=-1;e->state.field_27c=-1;e->state.flags.word_08=0;e->state.motion_110.position={1,0,0};actors.push_back(e);}
        world.actor.children.append(&child.parent_link);world.actor.children.append(&next.parent_link);
        child.callback=[&](Enemy*){
            assert(!child.parent_link.owner);
            if(action==1)next.parent_link.detach();
            if(action==2)child.parent_link.node=&alternate;
            if(action==3)throw std::runtime_error("Captured recursive callback failure");
            if(action==4)next.state.flags.word_04|=0x8000000u;
        };
        bool threw=false;try{world.actor.defeat();}catch(const std::runtime_error&){threw=true;}
        assert(threw==(action==3));
        assert(bool(child.state.flags.word_04&512u)==(action!=2&&action!=3));
        assert(bool(alternate.state.flags.word_04&512u)==(action==2));
        assert(bool(next.state.flags.word_04&512u)==(action!=1&&action!=3));
        for(auto* e:actors){assert(!e->parent_link.iterator);e->parent_link.detach();}
        assert(!world.actor.children.next);
    }
    std::puts("PASS 5 recursive topology cases: pending detach, post-call node reload, unwind and live flags.");
}
}
int main() {
    th20::process_locks.enable();
    {World world;matrix(world);failures(world);topology(world);}
    th20::process_locks.disable();
}
