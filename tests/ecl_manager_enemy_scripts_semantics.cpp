#include "ClockScalar.hpp"
#include "DiagnosticAllocator.hpp"
#include "Enemy.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <memory_resource>
#include <limits>
#include <vector>

namespace {
struct InstructionRecord {
    th20::EclInstruction header;
    std::array<std::uint32_t,32> arguments;
};
struct Program {
    std::array<std::uint32_t,4> subroutine_header{};
    std::array<InstructionRecord,4> instructions{};
    Program& operator=(std::initializer_list<InstructionRecord> values) {
        assert(values.size() <= instructions.size());
        instructions = {};
        std::copy(values.begin(), values.end(), instructions.begin());
        return *this;
    }
};
struct ScriptFile {
    std::array<std::uint32_t,9> header{};
    std::array<std::uint32_t,5> offsets{};
    std::array<char,32> names{};
    std::array<Program,5> programs{};
} script_file;
auto& programs = script_file.programs;
constexpr std::array<const char*,5> names{"main","task1","task2","task3","task4"};
std::vector<int> events;
th20::EclLoader test_loader;
unsigned movement_calls;
int movement_result, callback_result;
float movement_clock;
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
InstructionRecord instruction(int opcode,int time=0) {
    InstructionRecord v{};v.header.opcode=static_cast<std::int16_t>(opcode);
    v.header.time=time;v.header.length=sizeof(v);v.header.rank=15;return v;
}
InstructionRecord spawn_instruction(const char* name,int skip,int id=0,int opcode=15) {
    auto v=instruction(opcode);v.header.argument_count=static_cast<std::uint8_t>(skip+5);
    auto* payload=reinterpret_cast<unsigned char*>(v.arguments.data());
    v.arguments[0]=32;std::strcpy(reinterpret_cast<char*>(payload+4),name);
    v.arguments[9]=static_cast<std::uint32_t>(id);
    const std::array<char,4> from{'f','g','i','i'},to{'f','i','f','i'};
    const std::array<std::uint32_t,4> values{
        std::bit_cast<std::uint32_t>(1.25f),std::bit_cast<std::uint32_t>(-3.75f),
        static_cast<std::uint32_t>(-7),19};
    for(int i=0;i<4;++i) {
        auto* descriptor=payload+36+skip*4+i*8;
        descriptor[0]=from[i];descriptor[1]=to[i];std::memcpy(descriptor+4,&values[i],4);
    }
    return v;
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
// The link scalar factory remains a fixture, along
// with unused interpolation/frame routes and Enemy's outer retirement/movement.
// Actual Runtime allocation, both lifetimes, VM/call setup, loader activation,
// Manager spawn/find/invalidation/tick and the State script gate all execute.
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
template<> IntrusiveLink<EclRuntime>* DiagnosticAllocator::allocate_object<IntrusiveLink<EclRuntime>>(const char* label) {
    assert(std::strstr(label,"sptcmd.cpp:1014 LinkInf<SptBaseInf*>") != nullptr);
    events.push_back(200);return new IntrusiveLink<EclRuntime>;
}
void EclScriptInterpolation::set_tangent_start(const float&) {std::abort();}
void EclScriptInterpolation::set_tangent_end(const float&) {std::abort();}
void EclScriptInterpolation::reset_time() {std::abort();}
int ScriptStack::enter_frame(std::int32_t) {std::abort();}
}

namespace {
struct Manager : th20::EclManager {
    std::int32_t execute_opcode() override {events.push_back(100+current_runtime->async_id);return 0;}
};
}
int main() {
    using namespace th20;
    auto* old_resource=std::pmr::set_default_resource(&resource);
    script_file.header[0] = 0x54504353;
    script_file.header[1] = 1;
    script_file.header[4] = names.size();
    auto* bytes = reinterpret_cast<std::uint8_t*>(&script_file);
    auto* name_cursor = script_file.names.data();
    for (unsigned i=0; i<names.size(); ++i) {
        script_file.offsets[i] = reinterpret_cast<std::uint8_t*>(&programs[i]) - bytes;
        std::strcpy(name_cursor, names[i]);
        name_cursor += std::strlen(names[i]) + 1;
    }
    assert(test_loader.append(bytes) == 0);
    assert(test_loader.subroutine_count == names.size());
    for (unsigned i=0; i<names.size(); ++i) {
        assert(test_loader.records[i].header == reinterpret_cast<std::uint8_t*>(&programs[i]));
        assert(test_loader.instruction(i,0) == &programs[i].instructions[0].header);
    }
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
        programs[4]={instruction(1000),instruction(0,100000)};
        programs[0]={spawn_instruction("task4",0),instruction(1000),instruction(0,100000)};
        events.clear();assert(manager.tick(1)==0);
        assert((events==std::vector<int>{200,100,101,102}));assert((surviving(manager)==std::vector<int>{-1,1,2}));
        assert(manager.runtimes.next->node->time==0);events.clear();assert(manager.tick(1)==0);
        assert((events==std::vector<int>{99}));assert(manager.runtimes.next->node->time==1);
    }
    assert(resource.live.empty());
    // Real spawn includes sentinel-aware lookup, head insertion, rank copying,
    // all four numeric descriptor conversions and the native five-word frame.
    for(int skip:{0,1,3})for(int id:{std::numeric_limits<int>::min(),-1,0,17,std::numeric_limits<int>::max()}) {
        {
            Manager manager;ready(manager);add(manager,1,false);add(manager,2,false);
            manager.current_runtime=&manager.main;manager.main.rank=0xa5;manager.main.time=37;manager.main.async_id=-1;
            programs[0]={spawn_instruction("task4",skip)};
            programs[4]={instruction(1000),instruction(0,100000)};
            auto* old_head=manager.runtimes.next;events.clear();assert(manager.spawn(id,skip)==0);
            auto* link=manager.runtimes.next;auto* runtime=link->node;
            assert(link!=old_head && link->previous==&manager.runtimes && link->next==old_head && old_head->previous==link);
            assert(link->owner==nullptr && link->iterator==nullptr);
            assert(runtime->manager==&manager && runtime->async_id==id && runtime->rank==0xa5);
            assert(runtime->time==0 && runtime->position.subroutine==4 && runtime->position.offset==0);
            assert(runtime->signal==0 && runtime->flags.bits==0 && runtime->interpolators.empty());
            assert(runtime->stack.pointer==20 && runtime->stack.frame_base==0 && runtime->stack.words.size()>=9);
            assert(runtime->stack.words[0]==0 && runtime->stack.words[1]==4);
            for(int i=2;i<5;++i)assert(runtime->stack.words[i]==0xffffffffu);
            assert(runtime->stack.words[5]==std::bit_cast<unsigned>(1.25f));
            assert(runtime->stack.words[6]==static_cast<unsigned>(-3));
            assert(runtime->stack.words[7]==std::bit_cast<unsigned>(-7.0f));
            assert(runtime->stack.words[8]==19 && manager.current_runtime==&manager.main);
            assert(manager.main.time==37 && manager.main.position.offset==0 && manager.main.position.subroutine==0);
            assert(manager.find_runtime(id)==(id==-1?&manager.runtimes:link));
            assert(manager.find_runtime(1)==old_head && manager.find_runtime(2)==old_head->next);
            assert(manager.find_runtime(99)==nullptr && events==std::vector<int>{200});
        }
        assert(resource.live.empty());
    }
    // Lookup failure returns -1, retains the new current target and inserted
    // node, invalidates the caller, and leaves retirement to the owner lifecycle.
    {
        Manager manager;ready(manager);add(manager,1,false);
        programs[0]={spawn_instruction("missing",0)};auto* old_head=manager.runtimes.next;
        events.clear();assert(manager.spawn(27,0)==-1);auto* link=manager.runtimes.next;
        assert(link->next==old_head && link->node->async_id==27 && manager.current_runtime==link->node);
        assert(manager.main.position.offset==-1 && manager.main.position.subroutine==-1);
        assert(link->node->position.offset==0 && link->node->position.subroutine==-1);
        assert(link->node->stack.pointer==20 && manager.find_runtime(27)==link);
        assert(events==std::vector<int>{200});
    }
    assert(resource.live.empty());
    // Invalidation is allocation-free and never frees/detaches a node. The
    // embedded primary is excluded; both end words change on every child.
    for(unsigned count=0;count<=3;++count) {
        Manager manager;ready(manager);for(unsigned id=1;id<=count;++id)add(manager,id,false);
        const auto allocation_count=resource.live.size();auto* head=manager.runtimes.next;
        manager.current_runtime=count?head->node:&manager.main;auto* current=manager.current_runtime;
        events.clear();manager.invalidate_async();assert(events.empty() && resource.live.size()==allocation_count);
        assert(manager.runtimes.next==head && manager.current_runtime==current);
        assert(manager.main.position.subroutine==0 && manager.main.position.offset==0);
        for(auto* p=head;p;p=p->next)assert(p->node->position.offset==-1 && p->node->position.subroutine==-1 && p->previous->next==p);
    }
    assert(resource.live.empty());
    // VM opcode21 marks children while the primary still runs. Retirement is
    // ordered after the primary callback, preserving cached-next traversal.
    {
        Manager manager;ready(manager);add(manager,1,false);add(manager,2,false);
        programs[0]={instruction(21),instruction(1000),instruction(0,100000)};
        events.clear();resource.observe=true;assert(manager.tick(1)==0);resource.observe=false;
        assert((events==std::vector<int>{100,301,301,302,302}));
        assert(manager.runtimes.next==nullptr && manager.current_runtime==&manager.main);
        assert(manager.main.position.subroutine==0 && manager.main.time==1);
    }
    assert(resource.live.empty());
    // The VM's named-id spawn route supplies skip1 through real consuming
    // argument decoding; script index and async identifier remain independent.
    {
        Manager manager;ready(manager);
        programs[0]={spawn_instruction("task4",1,27,16),instruction(1000),instruction(0,100000)};
        programs[4]={instruction(1000),instruction(0,100000)};
        events.clear();assert(manager.tick(1)==0 && events==std::vector<int>({200,100}));
        auto* child=manager.runtimes.next->node;assert(child->async_id==27 && child->position.subroutine==4 && child->time==0);
        assert(child->stack.words[5]==std::bit_cast<unsigned>(1.25f) && child->stack.words[8]==19);
        events.clear();assert(manager.tick(1)==0 && events==std::vector<int>{127} && child->time==1);
    }
    assert(resource.live.empty());
    // Real find handles flag set/clear, signaling and offset-only ending.
    // Ending does not destroy a child until subsequent Manager traversal.
    {
        Manager manager;ready(manager);auto* first=add(manager,1,false);auto* second=add(manager,2,false);
        second->node->flags.bits=0x80000000u;
        auto set_flag=instruction(18),signal=instruction(20);
        set_flag.header.argument_count=1;set_flag.arguments[0]=2;
        signal.header.argument_count=2;signal.arguments[0]=2;signal.arguments[1]=static_cast<unsigned>(-7);
        programs[0]={set_flag,signal,instruction(1000),instruction(0,100000)};
        events.clear();assert(manager.tick(1)==0 && events==std::vector<int>({100,101,102}));
        assert(first->node->time==1 && second->node->time==1 && second->node->signal==-7);
        assert(second->node->flags.bits==0x80000001u);
        auto clear_flag=instruction(19),end=instruction(17);
        clear_flag.header.argument_count=1;clear_flag.arguments[0]=2;
        end.header.argument_count=1;end.arguments[0]=1;
        programs[0]={clear_flag,end,instruction(1000),instruction(0,100000)};manager.main.position.offset=0;
        const auto live_count=resource.live.size();events.clear();assert(manager.main.tick(1)==0);
        assert(first->node->position.offset==-1 && first->node->position.subroutine==1);
        assert(manager.runtimes.next==first && resource.live.size()==live_count && events==std::vector<int>{100});
        assert(second->node->flags.bits==0x80000000u && second->node->signal==-7);
        events.clear();resource.observe=true;assert(manager.tick(1)==0);resource.observe=false;
        assert(events==std::vector<int>({301,301}) && manager.runtimes.next==second);
        assert(second->previous==&manager.runtimes && second->node->time==2);
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
