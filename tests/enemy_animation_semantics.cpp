#include "Animation.hpp"
#include "DiagnosticAllocator.hpp"
#include "Enemy.hpp"
#include <array>
#include <cassert>
#include <cstdlib>
#include <vector>
namespace {
th20::EclInstruction instruction{};
std::array<int, 6> integers{};
std::array<float, 6> reals{};
std::vector<int> reads;
th20::Animation* selected;
}
namespace th20 {
// Deliberate fixtures bound VM construction/default slots, startup, ECL reading
// and renderer lookup. The real VM lifetime has its own owned test.
// Production EnemyScript forwarding, state lifetime, dispatcher and every
// animation parameter body execute unchanged.
LockRegistry process_locks;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
DiagnosticAllocator allocator;
DiagnosticAllocator* process_allocator = &allocator;
const Matrix4 identity_matrix = [] { Matrix4 m; for (int i=0;i<4;++i) m.elements[i][i]=1; return m; }();
EclScriptPosition::EclScriptPosition() noexcept : subroutine(0), offset(0) {}
EclRuntime::EclRuntime() noexcept : time(0), async_id(0), manager(nullptr), signal(0), rank(0), flags{} {}
EclManager::EclManager() : field_04(0), field_08(0), current_runtime(nullptr), loader(nullptr) {}
EclManager::~EclManager() = default;
Enemy::~Enemy() = default;
int EclManager::execute_opcode() { std::abort(); }
int EclManager::read_integer(int) { std::abort(); }
int* EclManager::integer_destination(int) { std::abort(); }
float EclManager::read_float(int) { std::abort(); }
float* EclManager::float_destination(int) { std::abort(); }
int Enemy::read_integer(int) { std::abort(); }
int* Enemy::integer_destination(int) { std::abort(); }
float Enemy::read_float(int) { std::abort(); }
float* Enemy::float_destination(int) { std::abort(); }
int EnemyState::execute_opcode() { std::abort(); }
int ScriptStack::pop(int, void*, char) { std::abort(); }
// Activation is outside this animation fixture; the actual inherited Manager
// instruction lookup executes from EclCallSetup against the resolver below.
void EclManager::set_loader(EclLoader*) { std::abort(); }
void EclManager::select_subroutine(const char*) { std::abort(); }
void EclManager::set_offset(int) { std::abort(); }
void EclManager::set_time(float) { std::abort(); }
EclInstruction* EclRuntime::current() { reads.push_back(100); return &instruction; }
int EclRuntime::integer_argument(int i) { reads.push_back(i); return integers.at(i); }
float EclRuntime::float_argument(int i) { reads.push_back(10+i); return reals.at(i); }
int EclRuntime::integer_argument_value(int i, int value) { reads.push_back(300+i); return value+100; }
float EclRuntime::float_argument_value(int i, float value) { reads.push_back(400+i); return value+0.5f; }
Animation* AnimationHandle::resolve() {
    reads.push_back(200);
    if (value==7) return selected;
    value=0; return nullptr;
}
void AnimationHandle::retire() { std::abort(); }
}
int main() {
    using namespace th20;
    Enemy enemy;
    Animation animation;
    selected=&animation;
    enemy.current_runtime=&enemy.main;
    auto& state=enemy.state;
    state.entity=&enemy;
    assert(state.integer_argument_value(3, 7)==107);
    assert(state.float_argument_value(2, 1.25f)==1.75f);
    assert((reads==std::vector<int>{303,402}));
    state.identifier=0x12345678u;
    auto identifier=enemy.identifier_value();
    identifier=1;
    assert(state.identifier.value==0x12345678u && identifier.value==1);
    state.animations.resize(1);
    auto run=[&](int op, std::initializer_list<int> order) {
        instruction.opcode=static_cast<std::int16_t>(op);
        integers[0]=0;
        state.animations[0].handle=7;
        reads.clear(); state.change_animation();
        std::vector<int> expected{100,0,200}; expected.insert(expected.end(),order);
        assert(reads==expected);
    };
    reals={0,1.25f,2.5f,3.75f,4.5f,0};
    animation.base.vector_38={17,18,19};
    run(319,{11});
    assert(animation.base.vector_38.x==17 && animation.base.vector_38.y==18 && animation.base.vector_38.z==1.25f);
    assert(animation.base.flags.word_04 & 2);
    run(329,{12,11}); assert(animation.base.vector_50.x==1.25f && animation.base.vector_50.y==2.5f);
    run(335,{12,11}); assert(animation.base.vector_58.x==1.25f && animation.base.vector_58.y==2.5f);
    integers[1]=15; integers[2]=3;
    animation.base.vector_50={6,7};
    run(330,{14,13,2,1});
    auto& scale=animation.base.interpolation_1e0;
    assert(scale.start.x==6 && scale.start.y==7 && scale.end.x==3.75f && scale.end.y==4.5f);
    assert(scale.current.x==6 && scale.duration==15 && scale.mode==3 && scale.timer.current==0);
    animation.base.color_490=0xaf102030u;
    integers[1]=0x145; integers[2]=0x234; integers[3]=0x1ab;
    run(325,{3,2,1}); assert(animation.base.color_490==0xaf4534abu);
    integers[1]=19; integers[2]=4; integers[3]=299; integers[4]=0x111; integers[5]=-1;
    run(326,{3,4,5,2,1});
    auto& rgb=animation.base.interpolation_e0;
    assert(rgb.start.first==0xab && rgb.start.second==0x34 && rgb.start.third==0x45);
    assert(rgb.end.first==255 && rgb.end.second==17 && rgb.end.third==43);
    assert(rgb.current.first==0xab && rgb.duration==19 && rgb.mode==4 && rgb.timer.current==0);
    integers[1]=0x15a; run(327,{1}); assert(animation.base.color_490==0x5a4534abu);
    integers[1]=13; integers[2]=2; integers[3]=0x1fd;
    run(328,{3,2,1});
    assert(animation.base.interpolation_134.start==0x5a && animation.base.interpolation_134.end==0xfd);
    assert(animation.base.interpolation_134.current==0x5a && animation.base.interpolation_134.duration==13);
    animation.base.color_494=0x11223344u; integers[1]=0x1cc;
    run(331,{1}); assert(animation.base.color_494==0xcc223344u);
    integers[1]=20; integers[2]=5; integers[3]=77;
    animation.base.flags.color_mode=0; animation.base.flags.other_09_low=3; animation.base.flags.other_09_high=5;
    run(332,{3,2,1});
    assert(animation.base.interpolation_2f4.start==0xcc && animation.base.interpolation_2f4.end==77);
    assert(animation.base.flags.color_mode==1 && animation.base.flags.other_09_low==3 && animation.base.flags.other_09_high==5);
    animation.base.flags.color_mode=6; run(332,{3,2,1}); assert(animation.base.flags.color_mode==6);
    animation.vector_5bc={11,12,13};
    run(333,{13,14,2,1});
    auto& position=animation.base.interpolation_8c;
    assert(position.start.x==11 && position.start.y==12 && position.start.z==13);
    assert(position.end.x==3.75f && position.end.y==4.5f && position.end.z==0);
    assert(position.duration==20 && position.mode==5 && position.current.z==13);
    for (int layer=-1;layer!=61;++layer) {
        integers[1]=layer; animation.base.flags.other_0b=37; animation.base.flags.field_0c=93;
        animation.base.flags.word_04=0;
        run(336,{1});
        assert(animation.base.field_14==layer && animation.base.flags.other_0b==37);
        assert(animation.base.flags.layer_mode==(layer>=3 && layer<=19 ? 1 : layer>=20 && layer<=23 ? 2 : 0));
        assert(animation.base.flags.field_0c==((layer>=20 && layer<=36)||(layer>=45 && layer<=53) ? 1 : 93));
        animation.base.flags.field_0c=93; animation.base.flags.word_04=1u<<23;
        run(336,{1}); assert(animation.base.flags.field_0c==93);
    }
    integers[1]=0x1d6; animation.base.flags.field_00=0x7311;
    run(337,{1}); assert(animation.base.flags.field_00==0xd611);
    for (int op : {-1,318,320,321,322,323,324,334,338,1003}) run(op,{});
    // Growth occurs before handle lookup, including for a default opcode.
    instruction.opcode=320; integers[0]=4; reads.clear(); state.change_animation();
    assert(state.animations.size()==5 && state.animations[4].handle.value==0 && state.animations[4].parent==-1);
    assert((reads==std::vector<int>{100,0,200}));
    // A failed lookup clears the selected handle and stops all argument reads.
    instruction.opcode=333; integers[0]=0; state.animations[0].handle=99;
    reads.clear(); state.change_animation();
    assert(state.animations[0].handle.value==0 && (reads==std::vector<int>{100,0,200}));
}
