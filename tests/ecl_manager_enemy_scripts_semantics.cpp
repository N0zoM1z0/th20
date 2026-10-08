#include "ClockScalar.hpp"
#include "DiagnosticAllocator.hpp"
#include "Enemy.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <memory_resource>
#include <limits>
#include <vector>

namespace {
std::array<std::vector<th20::EclInstruction>,5> programs;
std::vector<int> events;
th20::EclLoader test_loader;
unsigned movement_calls;
int movement_result, callback_result;
float movement_clock;
bool spawn_requested;
th20::EnemyState* expected_state;
struct Resource : std::pmr::memory_resource {
    struct Record { void* pointer; std::size_t bytes, alignment; int id; th20::IntrusiveLink<th20::EclRuntime>* link; };
    std::vector<Record> live;
    bool observe = false;
    void* do_allocate(std::size_t bytes,std::size_t alignment) override {
        auto* p=std::pmr::new_delete_resource()->allocate(bytes,alignment);
        live.push_back({p,bytes,alignment,0,nullptr});return p;
    }
    void do_deallocate(void* p,std::size_t bytes,std::size_t alignment) override {
        auto found=std::find_if(live.begin(),live.end(),[=](const Record& r){return r.pointer==p;});
        assert(found!=live.end() && found->bytes==bytes && found->alignment==alignment);
        if(observe && found->id) {
            // Both real PMR members die before the still-connected link detaches.
            auto* link=found->link;assert(link && link->previous && link->previous->next==link);
            if(link->next) assert(link->next->previous==link);
            events.push_back(300+found->id);
        }
        live.erase(found);std::pmr::new_delete_resource()->deallocate(p,bytes,alignment);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {return this==&other;}
    void label(void* p,int id,th20::IntrusiveLink<th20::EclRuntime>* link) {
        auto found=std::find_if(live.begin(),live.end(),[=](const Record& r){return r.pointer==p;});assert(found!=live.end());found->id=id;found->link=link;
    }
} resource;
th20::EclInstruction instruction(int opcode,int time=0) {
    th20::EclInstruction v{};v.opcode=static_cast<std::int16_t>(opcode);v.time=time;v.length=sizeof(v);v.rank=15;return v;
}
void prepare(th20::EclRuntime& runtime,th20::EclManager& manager,int id,bool ended) {
    runtime.manager=&manager;runtime.async_id=id;runtime.rank=15;runtime.time=0;
    runtime.position.subroutine=id;runtime.position.offset=0;
    programs[id]={instruction(ended?1:1000),instruction(0,100000)};
}
th20::IntrusiveLink<th20::EclRuntime>* add(th20::EclManager& manager,int id,bool ended) {
    auto* runtime=new th20::EclRuntime;prepare(*runtime,manager,id,ended);
    runtime->stack.words.resize(3);runtime->interpolators.reserve(2);
    auto* link=new th20::IntrusiveLink<th20::EclRuntime>(runtime);
    auto* tail=&manager.runtimes;while(tail->next)tail=tail->next;
    tail->insert_after(link);
    resource.label(runtime->stack.words.data(),id,link);
    resource.label(runtime->interpolators.data(),id,link);return link;
}
void ready(th20::EclManager& manager,bool ended=false) {
    manager.reset();prepare(manager.main,manager,0,ended);manager.loader=&test_loader;
}
std::vector<int> surviving(const th20::EclManager& manager) {
    std::vector<int> ids;for(auto* p=manager.runtimes.next;p;p=p->next)ids.push_back(p->node->async_id);return ids;
}
}

namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0),resource_() {}
DiagnosticAllocator allocator;
DiagnosticAllocator* process_allocator=&allocator;
GameRandom script_random{0};
// Only unresolved spawn/loader/interpolation routes and Enemy's outer retirement,
// opcode root and movement body are fixtures. Production lifetimes, real VM tick,
// Manager traversal, State script gate, Timer step and typed release all execute.
Enemy::~Enemy()=default;
std::int32_t Enemy::execute_opcode() {events.push_back(100+current_runtime->async_id);return 0;}
std::int32_t Enemy::read_integer(std::int32_t) {std::abort();}
std::int32_t* Enemy::integer_destination(std::int32_t) {std::abort();}
float Enemy::read_float(std::int32_t) {std::abort();}
float* Enemy::float_destination(std::int32_t) {std::abort();}
int EnemyState::update_movements() {
    assert(this==expected_state);++movement_calls;events.push_back(movement_calls==1?10:20);
    if(movement_calls==1){default_timer_clock.value=movement_clock;return movement_result;}
    return callback_result;
}
int EclManager::spawn(std::int32_t id,std::int32_t skip) {
    assert(spawn_requested && id==-1 && skip==0);spawn_requested=false;
    auto* link=add(*this,4,false);link->detach();runtimes.insert_after(link);events.push_back(200);return 0;
}
IntrusiveLink<EclRuntime>* EclManager::find_runtime(std::int32_t) {std::abort();}
EclInstruction* EclLoader::instruction(std::int32_t routine,std::int32_t offset) {
    assert(routine>=0 && routine<static_cast<int>(programs.size()) && offset>=0);
    assert(offset%sizeof(EclInstruction)==0);return &programs[routine].at(offset/sizeof(EclInstruction));
}
int EclRuntime::call_into(EclRuntime*,std::int32_t,std::int32_t) {std::abort();}
void EclScriptInterpolation::set_tangent_start(const float&) {std::abort();}
void EclScriptInterpolation::set_tangent_end(const float&) {std::abort();}
void EclScriptInterpolation::reset_time() {std::abort();}
int ScriptStack::enter_frame(std::int32_t) {std::abort();}
std::int32_t ScriptStack::pointer_value() const {return pointer;}
std::int32_t ScriptStack::frame_value() const {return frame_base;}
void ScriptStack::set_pointer(std::int32_t value) {pointer=value;}
}

namespace {
struct Manager : th20::EclManager {
    std::int32_t execute_opcode() override {events.push_back(100+current_runtime->async_id);return 0;}
};
}
int main() {
    using namespace th20;
    auto* old_resource=std::pmr::set_default_resource(&resource);
    // All async completion subsets with primary success/failure. Real VM opcode1
    // terminates; custom opcode1000 observes the Manager's current runtime.
    for(unsigned mask=0;mask<8;++mask)for(bool primary_failure:{false,true}) {
        {
            Manager manager;ready(manager,primary_failure);
            for(int id=1;id<=3;++id)add(manager,id,(mask>>(id-1))&1u);
            events.clear();resource.observe=true;
            assert(manager.tick(0.25f)==(primary_failure?-1:0));resource.observe=false;
            if(primary_failure) {
                assert(events.empty() && (surviving(manager)==std::vector<int>{1,2,3}));
                assert(manager.current_runtime==&manager.main && manager.main.position.offset==-1);
                for(auto* p=manager.runtimes.next;p;p=p->next)assert(p->node->time==0);
            } else {
                std::vector<int> expected{100},alive;
                for(int id=1;id<=3;++id)if((mask>>(id-1))&1u){expected.push_back(300+id);expected.push_back(300+id);}else{expected.push_back(100+id);alive.push_back(id);}
                assert(events==expected && surviving(manager)==alive);
                assert(manager.current_runtime==&manager.main && manager.main.time==0.25f);
                for(auto* p=manager.runtimes.next;p;p=p->next)assert(p->node->time==0.25f);
            }
        }
        assert(resource.live.empty());
    }
    // A distinct real primary object distinguishes failure retention from the
    // successful restoration of Manager.main; both are complete native routes.
    for(bool ended:{false,true}) {
        Manager manager;ready(manager);EclRuntime primary;prepare(primary,manager,0,ended);
        manager.runtimes.node=&primary;events.clear();assert(manager.tick(0.5f)==(ended?-1:0));
        assert(manager.current_runtime==(ended?&primary:&manager.main));
        assert(manager.main.time==0 && primary.time==(ended?0:0.5f));
        manager.runtimes.node=&manager.main;
    }
    assert(resource.live.empty());
    // Cached-next protocol defers a new node inserted by the real VM spawn opcode.
    {
        Manager manager;ready(manager);add(manager,1,false);add(manager,2,false);
        programs[0]={instruction(15),instruction(1000),instruction(0,100000)};
        spawn_requested=true;events.clear();assert(manager.tick(1)==0 && !spawn_requested);
        assert((events==std::vector<int>{200,100,101,102}));assert((surviving(manager)==std::vector<int>{4,1,2}));
        assert(manager.runtimes.next->node->time==0);events.clear();assert(manager.tick(1)==0);
        assert((events==std::vector<int>{104}));assert(manager.runtimes.next->node->time==1);
    }
    assert(resource.live.empty());
    // State gate, signed failures, movement-before-clock observation, real VM
    // failure, member-callback receiver/result and recursive bit26 protection.
    for(bool gated:{false,true})for(int moved:{0,-7,9})for(bool ended:{false,true})for(int callback:{0,-11,13}) {
        {
            Enemy enemy;ready(enemy,ended);auto& state=enemy.state;state.entity=&enemy;
            state.timer_a8.current=37;state.timer_a8.current_fraction=91.5f;state.timer_a8.flags=0xfedcba99u & ~6u;
            const unsigned retained=0xa1000080u;state.flags.word_04=retained|(gated?0x04000000u:0u);
            state.update_callback=&EnemyState::update_movements;expected_state=&state;
            movement_result=moved;callback_result=callback;movement_clock=0.375f;default_timer_clock.value=4;
            movement_calls=0;events.clear();int outcome=state.advance_scripts();
            int expected=gated?0:(moved||ended||callback?-1:0);assert(outcome==expected);
            assert(state.flags.word_04==(retained|0x04000000u));
            std::vector<int> expected_events;
            if(!gated){expected_events.push_back(10);if(!moved&&!ended){expected_events.push_back(100);expected_events.push_back(20);}}
            assert(events==expected_events);
            assert(state.timer_a8.current==37 && state.timer_a8.current_fraction==91.5f);
            if(!gated&&!moved&&!ended)assert(enemy.main.time==0.375f);
        }
        assert(resource.live.empty());
    }
    {
        Enemy enemy;ready(enemy);auto& state=enemy.state;state.entity=&enemy;expected_state=&state;
        state.update_callback=&EnemyState::advance_scripts;state.flags.word_04=0;
        movement_calls=0;movement_result=0;movement_clock=0.5f;events.clear();assert(state.advance_scripts()==0);
        assert(movement_calls==1 && (events==std::vector<int>{10,100}));
        state.flags.word_04=0;state.update_callback=nullptr;movement_calls=0;events.clear();assert(state.advance_scripts()==0);
        assert((events==std::vector<int>{10}));
    }
    assert(resource.live.empty());
    Timer timer;timer.flags=0xfefcba99u & ~6u;
    for(float value:{-3.0f,-0.0f,0.0f,0.25f,1.0f,4.0f,
                    std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),
                    std::numeric_limits<float>::quiet_NaN()}) {
        default_timer_clock.value=value;const auto before=timer.flags;
        assert(std::bit_cast<unsigned>(timer.step())==std::bit_cast<unsigned>(value));assert(timer.flags==before);
    }
    std::pmr::set_default_resource(old_resource);
}
