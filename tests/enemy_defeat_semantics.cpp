#include "EnemyController.hpp"
#include "ItemResourceOwners.hpp"
#include "Player.hpp"
#include "Session.hpp"
#include "SoundInf.hpp"
#include "WeaponStoneInfo.hpp"
#include "Graphics.hpp"
#include "DiagnosticAllocator.hpp"
#include "Card.hpp"
#include "ClockScalar.hpp"
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
enum Step { sound=1,file_lookup,spawn,drop,stone,terminate,tick,callback };
struct Event { Step step; th20::Enemy* actor; };
std::vector<Event> events;
std::vector<th20::Enemy*> actors;
th20::Enemy* active;
std::function<void(Step)> hook;
unsigned throw_at;
int gate_after,expected_reward,expected_kind;
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
int wrapped_add(int first,int second) {
    const auto bits=(std::uint64_t(static_cast<unsigned>(first))+static_cast<unsigned>(second))&0xffffffffu;
    return bits<0x80000000u?static_cast<int>(bits):static_cast<int>(static_cast<std::int64_t>(bits)-0x100000000ll);
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
void OverlayCounter::add_reward(const Vector3* position,int amount,int kind) {
    assert(this==&selected_stone->counter && position==&active->state.motion_110.position);
    assert(amount==2000 && kind==expected_kind+9);note(::stone);
    process_stone_enemies->byte_b0=static_cast<std::uint8_t>(gate_after);
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
    th20::EclLoader script;
    World(){selected_file=&file;selected_stone=&overlay;th20::process_stone_enemies=&gate;}
};
void prepare(World& world) {
    using namespace th20;
    auto& a=world.actor;active=&a;actors={&a};events.clear();hook={};throw_at=0;
    a.children.reset(&a);a.parent_link.initialize(&a);
    a.context=&session.contexts[0];a.state.context=&session.contexts[1];a.state.entity=&a;
    a.loader=&world.script;a.current_runtime=&a.main;
    a.main.stack.reset();a.main.position.subroutine=-1;a.main.position.offset=-1;
    a.main.time=0;a.main.async_id=-1;a.main.manager=&a;a.main.signal=0;a.main.flags.bits=0;
    a.runtimes.initialize(&a.main);
    for(auto& context:session.contexts){context.enemies=&world.first;context.object_20=world.fx.get();context.object_04=world.player.get();context.current_player=&session.table.players[0];context.overlay_owner=&world.overlay;}
    session.contexts[1].enemies=&world.second;
    a.state.flags.word_00=0x10000;a.state.flags.word_04=0x4000;a.state.flags.word_08=0;
    a.state.field_250=-1;a.state.field_254=-1;a.state.field_258=1;a.state.field_26c=17;a.state.field_278=10;a.state.field_27c=-1;
    a.state.vector_6c={0,0,123};a.state.motion_110.position={1,0,-999};a.callback=nullptr;
    world.first.angle_128.value=91;world.second.angle_128.value=93;
    world.gate.byte_b0=0;world.fx->handle_cursor=1023;
    for(auto& entry:world.fx->handles)entry.handle.value=0;
    world.player->feedback.field_30=world.player->feedback.field_38=0;
    world.player->feedback.field_3c=5;
    auto& feedback_clock=static_cast<Timer&>(world.player->feedback);
    feedback_clock.previous=-9;feedback_clock.current=11;feedback_clock.current_fraction=11.5f;feedback_clock.flags=1;
    default_timer_clock.value=1.0f;timer_clock_sources[0]=&default_timer_clock;
    auto& record=session.table.players[0];record.field_44=999999;record.field_5c=9999;
    record.field_0c=2;record.field_14=3;record.field_10=5;record.field_18=7;
    record.field_64=995;record.field_68=996;record.field_6c=997;record.field_70=998;record.field_98=-1;
    gate_after=0;expected_reward=0;expected_kind=0;output_handle=0x12345678u;
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
        state.field_278=bases[scenarios%bases.size()];state.field_27c=script;
        if(marked)world.player->feedback.field_38=static_cast<unsigned>(count)-1u;
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
        if(script!=-1){patch(expected_actor,a,state.field_27c,-1);
            patch(expected_actor,a,a.main.position.subroutine,script);patch(expected_actor,a,a.main.position.offset,0);}
        if(marked){auto& record=session.table.players[0];patch(expected_record,record,record.field_44,wrapped_add_clamp(999999,expected_reward,1000000));
            if(!first_gate)patch(expected_record,record,record.field_5c,wrapped_add_clamp(9999,expected_reward,10000));
            patch(expected_feedback,world.player->feedback,world.player->feedback.field_30,static_cast<unsigned>(count));
            patch(expected_feedback,world.player->feedback,world.player->feedback.field_38,static_cast<unsigned>(count));
            patch(expected_feedback,world.player->feedback,world.player->feedback.field_3c,static_cast<unsigned>(count>5?count:5));
            auto& clock=static_cast<Timer&>(world.player->feedback);
            patch(expected_feedback,world.player->feedback,clock.previous,11);
            patch(expected_feedback,world.player->feedback,clock.current,28);
            patch(expected_feedback,world.player->feedback,clock.current_fraction,28.5f);
            if(!next_gate){
                int selection=expected_kind==4?static_cast<int>(last%8u):record.starting_configuration(expected_kind);
                int channel=selection>=0&&selection<8?selection/2:0;
                std::array<int*,4> fields{&record.field_64,&record.field_68,&record.field_6c,&record.field_70};
                int sum=wrapped_add(*fields[channel],expected_reward);int result=sum>=1000?1000:sum;
                patch(expected_record,record,*fields[channel],result);
                if(sum>=1000)patch(expected_record,record,record.field_98,channel);
            }}
        std::vector<Step> expected;if(audio)expected.push_back(sound);if(effect){expected.push_back(file_lookup);expected.push_back(spawn);}expected.push_back(drop);
        if(marked)expected.push_back(stone);
        if(script!=-1){expected.push_back(terminate);expected.push_back(tick);}
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
    const std::vector<Step> expected{sound,file_lookup,spawn,drop,stone,terminate,tick,callback};
    for(unsigned ordinal=1;ordinal<=expected.size();++ordinal) {
        prepare(world);auto& a=world.actor;a.state.field_250=5;a.state.field_254=37;a.state.flags.word_08=16;a.state.field_27c=17;
        expected_kind=1;expected_reward=10;gate_after=0;throw_at=ordinal;
        world.player->feedback.field_38=0xffffffffu;
        a.callback=[&](Enemy* actor){assert(actor==&a);active=actor;note(::callback);};
        bool threw=false;try{a.defeat();}catch(const std::runtime_error&){threw=true;}
        assert(threw && step_values()==std::vector<Step>(expected.begin(),expected.begin()+ordinal));
        assert(a.state.field_27c==(ordinal==8?-1:17) && !a.parent_link.iterator);
        auto& record=session.table.players[0];
        if(ordinal<=4)assert(world.player->feedback.field_38==0xffffffffu && record.field_44==999999 && record.field_98==-1);
        else {assert(world.player->feedback.field_38==0 && record.field_44==1000000 && record.field_5c==10000);
            assert(record.field_98==(ordinal==5?-1:1));}
    }
    std::puts("PASS 8 remaining interface failures: event prefixes, committed feedback/rewards and late caller writes.");
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
void feedback_protocol(World& world) {
    using namespace th20;
    auto& value=world.player->feedback;
    auto& clock=static_cast<Timer&>(value);
    constexpr std::array<unsigned,8> counters{0,1,9,10,0x7fffffffu,0x80000000u,0xfffffffeu,0xffffffffu};
    constexpr std::array<unsigned,5> maxima{0,1,0x7fffffffu,0x80000000u,0xffffffffu};
    auto signed_word=[](unsigned word)->std::int64_t {
        return word<0x80000000u?std::int64_t(word):std::int64_t(word)-0x100000000ll;
    };
    unsigned scenarios=0;
    for(unsigned flags:{0u,1u,7u,0xdeadbeefu,0xa5000006u})
    for(int initial:{-30,-1,0,29,30,100})for(int amount:{-40,-1,0,1,3,30,31,60})
    for(float scale:{-1.0f,0.5f,1.0f,2.0f})for(auto counter:counters)for(auto maximum:maxima) {
        clock.previous=-117;clock.current=initial;clock.current_fraction=static_cast<float>(initial)+0.5f;clock.flags=flags;
        value.field_30=0xfeedbabeu;value.field_34=0x12345678u;value.field_38=counter;value.field_3c=maximum;
        value.timer_10.current=113;value.timer_20.current=-119;value.enabled=0xc9;
        default_timer_clock.value=scale;timer_clock_sources[0]=scale<0?nullptr:&default_timer_clock;
        auto expected=image(value);
        const bool initialized=flags&1u;
        int previous=initialized?initial:0;
        float fraction=(initialized?static_cast<float>(initial)+0.5f:0.f)
            +static_cast<float>(amount)*(scale<0?1.f:scale);
        int current=static_cast<int>(fraction);
        if(current>30){current=30;fraction=30.f;previous=29;}
        auto count=static_cast<unsigned>((std::uint64_t(counter)+1u)&0xffffffffu);
        auto high=signed_word(maximum)<signed_word(count)?count:maximum;
        patch(expected,value,clock.previous,previous);patch(expected,value,clock.current,current);
        patch(expected,value,clock.current_fraction,fraction);patch(expected,value,clock.flags,(flags|1u)&~6u);
        patch(expected,value,value.field_30,count);patch(expected,value,value.field_38,count);patch(expected,value,value.field_3c,high);
        value.record_hit(amount);
        assert(image(value)==expected && value.count_value()==signed_word(count));
        ++scenarios;
    }
    default_timer_clock.value=1.f;timer_clock_sources[0]=&default_timer_clock;
    std::printf("PASS %u feedback cases: real Timer base, clocks, cap, unsigned wrap and signed maximum.\n",scenarios);
}
void reward_protocol() {
    using namespace th20;
    constexpr std::array<int,8> values{std::numeric_limits<int>::min(),-1,0,1,999,1000,1001,std::numeric_limits<int>::max()};
    constexpr std::array<int,7> amounts{std::numeric_limits<int>::min(),-1001,-1,0,1,1000,std::numeric_limits<int>::max()};
    constexpr std::array<int,8> choices{std::numeric_limits<int>::min(),-1,0,1,2,3,4,std::numeric_limits<int>::max()};
    constexpr std::array<int,14> kinds{std::numeric_limits<int>::min(),-99,-1,0,1,2,3,4,5,6,7,8,99,std::numeric_limits<int>::max()};
    using Update=void(PlayerRecord::*)(std::int32_t);
    constexpr std::array<Update,4> updates{&PlayerRecord::add_field_64,&PlayerRecord::add_field_68,&PlayerRecord::add_field_6c,&PlayerRecord::add_field_70};
    PlayerRecord record;unsigned scenarios=0;
    auto check=[&](int kind,int initial,int amount,int choice,bool direct) {
        record.field_64=3;record.field_68=5;record.field_6c=7;record.field_70=11;record.field_98=choice;
        int channel=direct?kind:kind>=0&&kind<8?kind/2:0;
        std::array<int*,4> fields{&record.field_64,&record.field_68,&record.field_6c,&record.field_70};
        *fields[channel]=initial;
        auto expected=image(record);int sum=wrapped_add(initial,amount);int result=sum>=1000?1000:sum;
        patch(expected,record,*fields[channel],result);
        if(sum>=1000 && choice<0)patch(expected,record,record.field_98,channel);
        if(direct)(record.*updates[channel])(amount);else record.add_reward(kind,amount);
        assert(image(record)==expected);++scenarios;
    };
    assert(record.reward_limit()==1000);
    for(auto initial:values)for(auto amount:amounts)for(auto choice:choices) {
        for(auto kind:kinds)check(kind,initial,amount,choice,false);
        for(int channel=0;channel<4;++channel)check(channel,initial,amount,choice,true);
    }
    std::printf("PASS %u reward cases: complete dispatcher, all channels, signed wrap, cap and first selection.\n",scenarios);
}
void indexed_selection(World& world) {
    using namespace th20;
    constexpr std::array<int,14> indices{std::numeric_limits<int>::min(),-99,-1,0,1,2,3,4,5,6,7,8,99,std::numeric_limits<int>::max()};
    EclLoader second;EclRuntime alternate;unsigned scenarios=0;
    for(int route=0;route<3;++route)for(bool main:{false,true})for(int index:indices) {
        prepare(world);auto& actor=world.actor;
        alternate.time=-9;alternate.position.subroutine=43;alternate.position.offset=51;alternate.rank=0xa7;
        actor.current_runtime=main?&actor.main:&alternate;
        EclLoader* selected=route==1?&second:&world.script;
        actor.loader=route==2?&second:selected;
        auto expected=image(actor);auto expected_alternate=image(alternate);
        auto first_loader=image(world.script);auto second_loader=image(second);
        patch(expected,actor,actor.loader,selected);
        if(main){patch(expected,actor,actor.main.time,0.f);
            patch(expected,actor,actor.main.position.subroutine,index);patch(expected,actor,actor.main.position.offset,0);}
        else {patch(expected_alternate,alternate,alternate.time,0.f);
            patch(expected_alternate,alternate,alternate.position.subroutine,index);patch(expected_alternate,alternate,alternate.position.offset,0);}
        int result=route==2?selected->select_index(&actor,index):actor.select_subroutine_index(index);
        assert(result==0 && image(actor)==expected && image(alternate)==expected_alternate);
        assert(image(world.script)==first_loader && image(second)==second_loader);
        assert(!std::signbit(actor.current_runtime->time));++scenarios;
    }
    world.actor.current_runtime=&world.actor.main;world.actor.loader=&world.script;
    std::printf("PASS %u indexed selection cases: main/alternate runtime, loader rebinding, full-width index and positive zero.\n",scenarios);
}
}
int main() {
    th20::process_locks.enable();
    {World world;
        world.player->feedback.field_30=3;world.player->feedback.field_38=7;
        assert(world.player->feedback.count_value()==7);
        feedback_protocol(world);reward_protocol();indexed_selection(world);
        matrix(world);failures(world);topology(world);
    }
    th20::process_locks.disable();
}
