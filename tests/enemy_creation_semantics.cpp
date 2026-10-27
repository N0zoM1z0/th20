#include "EnemyController.hpp"
#include "Context.hpp"
#include "DiagnosticAllocator.hpp"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <array>
#include <limits>
#include <stdexcept>
#include <vector>
#include <cstdio>
#include <cmath>

void check_enemy_phases(th20::Enemy& enemy);

namespace {
th20::Context context;
std::vector<std::unique_ptr<th20::Enemy>> allocated;
std::vector<int> events;
const char* expected_name;
th20::EnemySpawn* expected_parameters;
th20::EnemyController* lookup_controller = nullptr;
th20::Enemy* resolved_enemy = nullptr;
unsigned lookup_calls = 0, find_calls = 0;
}

namespace th20 {
// Deliberate fixtures supply VM construction/default slots, production startup,
// pool/context selection, subroutine lookup and the spawn-application boundary.
// Actual Controller/Task construction, creation, initialization, state/reset,
// generation, lists and selection run unchanged; the VM lifetime has its own test.
LockRegistry process_locks;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
DiagnosticAllocator allocator;
DiagnosticAllocator* process_allocator = &allocator;
std::uint32_t current_enemy_generation = 1, previous_enemy_generation = 0;
EclScriptPosition::EclScriptPosition() noexcept : subroutine(0), offset(0) {}
EclRuntime::EclRuntime() noexcept : time(0), async_id(0), manager(nullptr), signal(0), rank(0), flags{} {}
EclManager::EclManager() : field_04(0), field_08(0), current_runtime(&main), loader(nullptr) {}
EclManager::~EclManager() = default;
Enemy::~Enemy() = default;
TaskInfo::~TaskInfo() = default;
void TaskInfo::enable() { std::abort(); }
void TaskInfo::disable() { std::abort(); }
EnemyController::~EnemyController() = default;
int EclManager::execute_opcode() { std::abort(); }
int EclManager::read_integer(int) { std::abort(); }
int* EclManager::integer_destination(int) { std::abort(); }
float EclManager::read_float(int) { std::abort(); }
float* EclManager::float_destination(int) { std::abort(); }
int Enemy::read_integer(int) { std::abort(); }
float Enemy::read_float(int) { std::abort(); }
// Explicit Session and whole-list-find observation boundaries. Destination,
// checked-slot and handle-resolution bodies are the real production source.
std::int32_t enemy_script_globals[4] = {};
EnemyController* enemy_controller(std::int32_t index) {
    assert(index == 0); ++lookup_calls; return lookup_controller;
}
Enemy* EnemyController::find(std::uint32_t identifier) {
    ++find_calls;
    return resolved_enemy && resolved_enemy->state.identifier.value == identifier
        ? resolved_enemy : nullptr;
}
int EnemyState::execute_opcode() { std::abort(); }
int ScriptStack::pop(int, void*, char) { std::abort(); }
void Enemy::select_context(int index) {
    events.push_back(1);
    assert(current_runtime == &main && main.time == 0 && main.position.subroutine == -1);
    assert(main.stack.words.empty() && main.stack.words.capacity() >= 256);
    assert(main.stack.pointer == 0 && main.stack.frame_base == 0);
    player_index = index; this->context = &::context;
    state.context = &::context; state.field_2e8 = static_cast<std::uint32_t>(index);
}
template<> Enemy* DiagnosticAllocator::allocate_object<Enemy>(const char* label) {
    assert(std::strcmp(label, "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\enemy.cpp:69 EnemyInf") == 0);
    events.push_back(0);
    allocated.push_back(std::make_unique<Enemy>());
    return allocated.back().get();
}
int Enemy::apply_spawn(const EnemySpawn& parameters) {
    events.push_back(3); assert(&parameters == expected_parameters);
    assert(state.entity == this && state.identifier.value == previous_enemy_generation);
    assert(state.movements.size() == 1 && state.animations.size() == 1);
    assert(children.node == this && parent_link.node == this && !callback);
    assert(loader == ::context.enemies->loader && main.position.subroutine == 1);
    assert(main.position.offset == 0 && main.time == 0);
    spawn_parameters = parameters; return 0;
}
}

namespace {
std::function<int(th20::Enemy&)> clear_defeat_capture;
std::function<void(th20::AnimationHandle&)> clear_retire_capture;
template<class T> auto clear_image(const T& value) {
    std::array<unsigned char,sizeof(T)> out;
    std::memcpy(out.data(),&value,sizeof(value));return out;
}
template<class T,class V> void clear_patch(std::array<unsigned char,sizeof(T)>& image,
    const T& owner,const V& member,const V& value) {
    const auto offset=reinterpret_cast<const unsigned char*>(&member)-reinterpret_cast<const unsigned char*>(&owner);
    std::memcpy(image.data()+offset,&value,sizeof(value));
}
void invoke_clear(th20::EnemyController& controller,int variant,int selector) {
    switch(variant) {
    case 0:controller.clear();break;
    case 1:controller.clear_matching(selector);break;
    case 2:controller.clear_variant_565();break;
    case 3:controller.clear_variant_573();break;
    default:std::abort();
    }
}
void check_enemy_clear_protocol() {
    using namespace th20;
    unsigned scenarios=0;
    for(int variant=0;variant<4;++variant)for(unsigned bits=0;bits<128;++bits)
    for(int selector:{-1,7,9})for(unsigned count:{0u,1u,3u}) {
        EnemyController controller;Enemy enemy;
        controller.enemies.append(&enemy.controller_link);
        auto& state=enemy.state;
        state.flags.word_00=0x80000000u|((bits&1u)?32u:0u)|((bits&2u)?128u:0u)
            |((bits&4u)?1024u:0u)|((bits&32u)?256u:0u);
        state.flags.word_04=0x10000u|((bits&8u)?64u:0u)|((bits&16u)?128u:0u)
            |((bits&64u)?0x40000000u:0u);
        state.field_30=7;state.field_27c=31;state.field_284=29;state.vector_6c={11,13,17};
        std::memset(static_cast<void*>(&state.pattern),0x5a,sizeof(state.pattern));
        state.animations.resize(count);
        for(unsigned i=0;i<count;++i)state.animations[i].handle.value=i?0xffffffffu:0u;
        auto* storage=state.animations.data();auto capacity=state.animations.capacity();
        controller.data.timer_8c=23;
        const auto owner_before=clear_image(controller);auto enemy_expected=clear_image(enemy);
        const unsigned old04=state.flags.word_04;
        const bool eligible=((bits&31u)==0 || (bits&32u))
            && (variant!=1 || selector==7) && (variant!=3 || !(bits&64u));
        unsigned defeated=0,retired=0;
        EnemyPattern reset_expected;
        std::memset(static_cast<void*>(&reset_expected),0,sizeof(reset_expected));
        reset_expected.radius_x=reset_expected.radius_y=32;
        reset_expected.timer.previous=-1;reset_expected.timer.flags=1;
        clear_defeat_capture=[&](Enemy& actual) {
            assert(&actual==&enemy && eligible);++defeated;
            assert(!std::memcmp(&state.pattern,&reset_expected,sizeof(reset_expected)));
            assert(state.vector_6c.x==0 && state.vector_6c.y==192 && state.vector_6c.z==17);
            assert(state.field_284==0 && state.field_27c==(variant==2?-1:31));
            assert(state.flags.word_04==old04 && state.animations.size()==count);
            assert(controller.data.timer_8c.current==23 && enemy.controller_link.iterator);
            state.flags.word_04^=0x100000u;return 0x100;
        };
        clear_retire_capture=[&](AnimationHandle& handle) {
            assert(defeated==1 && state.animations.size()==count);
            assert(&handle==&state.animations[retired].handle);
            assert(handle.value==(retired?0xffffffffu:0u));
            assert(controller.data.timer_8c.current==23);++retired;handle.value=0;
        };
        invoke_clear(controller,variant,selector);
        assert(defeated==unsigned(eligible) && retired==(eligible?count:0));
        assert(state.animations.size()==(eligible?0:count));
        assert(state.animations.data()==storage && state.animations.capacity()==capacity);
        if(eligible) {
            clear_patch(enemy_expected,enemy,state.pattern,reset_expected);
            clear_patch(enemy_expected,enemy,state.vector_6c.x,0.f);
            clear_patch(enemy_expected,enemy,state.vector_6c.y,192.f);
            clear_patch(enemy_expected,enemy,state.field_284,0);
            if(variant==2)clear_patch(enemy_expected,enemy,state.field_27c,-1);
            clear_patch(enemy_expected,enemy,state.flags.word_04,(old04^0x100000u)|0x200u);
            // The standard vector's opaque control object has separate size,
            // storage and capacity assertions; all other Enemy bytes are modeled.
            clear_patch(enemy_expected,enemy,state.animations,state.animations);
        }
        assert(clear_image(enemy)==enemy_expected);
        auto owner_expected=owner_before;
        Timer expected_timer=controller.data.timer_8c;
        assert(expected_timer.previous==23 && expected_timer.current==24 && expected_timer.current_fraction==24.f);
        clear_patch(owner_expected,controller,controller.data.timer_8c,expected_timer);
        assert(clear_image(controller)==owner_expected);
        assert(!enemy.controller_link.iterator);enemy.controller_link.detach();++scenarios;
    }
    // Native defeat and retirement are explicit resource boundaries. Reentrant
    // callbacks may detach current/pending nodes, append a later node, replace
    // animation records, or throw; the actual observer/list implementation runs.
    for(int variant=0;variant<4;++variant)for(int action=0;action<6;++action) {
        EnemyController controller;Enemy first,second,third,added;
        std::array<Enemy*,4> actors{&first,&second,&third,&added};
        for(auto* e:actors){e->state.field_30=7;e->state.animations.resize(1);e->state.animations[0].handle.value=31;}
        controller.enemies.append(&first.controller_link);controller.enemies.append(&second.controller_link);controller.enemies.append(&third.controller_link);
        controller.data.timer_8c=23;std::vector<Enemy*> order;unsigned retirements=0;
        clear_defeat_capture=[&](Enemy& actor) {
            order.push_back(&actor);
            if(&actor==&first) {
                if(action==0)first.controller_link.detach();
                if(action==1)second.controller_link.detach();
                if(action==2){first.controller_link.detach();second.controller_link.detach();}
                if(action==3)controller.enemies.append(&added.controller_link);
                if(action==4){first.state.animations.resize(2);first.state.animations[1].handle.value=99;}
                if(action==5)throw std::runtime_error("Captured whole defeat failure");
            }
            return 1;
        };
        clear_retire_capture=[&](AnimationHandle& handle){++retirements;handle.value=0;};
        bool threw=false;try{invoke_clear(controller,variant,7);}catch(const std::runtime_error&){threw=true;}
        std::vector<Enemy*> expected{&first};
        if(action!=5){if(action!=1&&action!=2)expected.push_back(&second);expected.push_back(&third);if(action==3)expected.push_back(&added);}
        assert(order==expected && threw==(action==5));
        assert(retirements==(action==5?0u:unsigned(expected.size())+(action==4?1u:0u)));
        assert(controller.data.timer_8c.current==(action==5?23:24));
        for(auto* e:actors){assert(!e->controller_link.iterator);e->controller_link.detach();}
        ++scenarios;
    }
    for(int variant=0;variant<4;++variant) {
        EnemyController controller;Enemy enemy;controller.enemies.append(&enemy.controller_link);
        enemy.state.field_30=7;enemy.state.animations.resize(3);enemy.state.flags.word_04=0x10000;
        controller.data.timer_8c=23;unsigned retired=0;
        clear_defeat_capture=[](Enemy&){return 1;};
        clear_retire_capture=[&](AnimationHandle& handle){if(++retired==2)throw std::runtime_error("Captured retirement failure");handle.value=0;};
        bool threw=false;try{invoke_clear(controller,variant,7);}catch(const std::runtime_error&){threw=true;}
        assert(threw && retired==2 && enemy.state.animations.size()==3);
        assert(enemy.state.flags.word_04==0x10000 && controller.data.timer_8c.current==23 && !enemy.controller_link.iterator);
        enemy.controller_link.detach();++scenarios;
    }
    clear_defeat_capture={};clear_retire_capture={};
    std::printf("Owned Enemy clear passed: %u filter/order/topology/exception scenarios.\n",scenarios);
}
}
namespace th20 {
std::int32_t Enemy::defeat(){assert(clear_defeat_capture);return clear_defeat_capture(*this);}
void AnimationHandle::retire(){assert(clear_retire_capture);clear_retire_capture(*this);}
}

int main() {
    using namespace th20;
    EnemyController controller;
    assert(controller.flags == 2 && !controller.update_node && !controller.draw_node);
    assert(controller.loaded_names.empty() && controller.loaded_names.capacity() == 0);
    assert(controller.field_c4 == 0 && controller.field_c8 == 0 && controller.field_cc == 0);
    assert(controller.field_e0 == 0 && controller.field_120 == 0 && controller.field_124 == 0);
    assert(controller.angle_128.value == 0 && controller.player_index == 0 && !controller.context);
    assert(!controller.loader && controller.enemies.tail == &controller.enemies);
    assert(!controller.enemies.node && !controller.enemies.next && !controller.enemies.previous);
    assert(!controller.enemies.owner && !controller.enemies.iterator);
    for (auto* file : controller.animation_files) assert(file == nullptr);
    assert(previous_enemy_generation == 1 && current_enemy_generation == 2);
    // Dirty placement construction verifies that actual constructors clear
    // retained flag bits/pointers and cannot depend on pre-zeroed host storage.
    constexpr std::size_t guard = 16;
    alignas(TaskInfo) std::array<unsigned char, sizeof(TaskInfo)+2*guard> task_storage;
    task_storage.fill(0xa5);
    auto* dirty_task = std::construct_at(reinterpret_cast<TaskInfo*>(task_storage.data()+guard));
    assert(dirty_task->flags == 2 && !dirty_task->update_node && !dirty_task->draw_node);
    std::destroy_at(dirty_task);
    alignas(EnemyController) std::array<unsigned char, sizeof(EnemyController)+2*guard> controller_storage;
    controller_storage.fill(0xa5);
    current_enemy_generation = 0xffffffffu;
    auto* dirty_controller = std::construct_at(reinterpret_cast<EnemyController*>(controller_storage.data()+guard));
    assert(dirty_controller->flags == 2 && !dirty_controller->update_node && !dirty_controller->draw_node);
    assert(dirty_controller->loaded_names.empty() && dirty_controller->loaded_names.capacity() == 0);
    assert(dirty_controller->field_c4 == 0 && dirty_controller->field_c8 == 0 && dirty_controller->field_cc == 0);
    assert(dirty_controller->field_e0 == 0 && dirty_controller->field_120 == 0 && dirty_controller->field_124 == 0);
    assert(dirty_controller->player_index == 0 && !dirty_controller->context && !dirty_controller->loader);
    assert(dirty_controller->enemies.tail == &dirty_controller->enemies);
    for (auto* file : dirty_controller->animation_files) assert(file == nullptr);
    for (const auto& handle : dirty_controller->data.handles) assert(handle.value == 0);
    assert(previous_enemy_generation == 0xffffffffu && current_enemy_generation == 1);
    std::destroy_at(dirty_controller); // Controller disposal is still a fixture.
    for (std::size_t i=0;i<guard;++i) {
        assert(task_storage[i] == 0xa5 && task_storage[sizeof(TaskInfo)+guard+i] == 0xa5);
        assert(controller_storage[i] == 0xa5 && controller_storage[sizeof(EnemyController)+guard+i] == 0xa5);
    }
    // Real Data and handle constructors initialize every owned scalar/slot.
    assert(controller.data.field_30 == 0 && controller.data.field_34 == 0);
    assert(controller.data.field_38 == 0 && controller.data.field_3c == 0);
    assert(controller.data.field_40 == 0 && controller.data.field_84.value == 0);
    assert(controller.data.field_88 == 0 && controller.data.field_9c == 0 && controller.data.field_a0 == 0);
    assert(controller.data.counters.field_00 == 0 && controller.data.counters.field_2c == 0.0f);
    for (const auto& handle : controller.data.handles) assert(handle.value == 0);
    EclLoader loader;
    assert(loader.subroutine_index("entry") == -1);
    loader.records = {{"alpha", nullptr}, {"entry", nullptr}, {"zeta", nullptr}};
    loader.subroutine_count = 3;
    assert(loader.subroutine_index("alpha") == 0 && loader.subroutine_index("entry") == 1);
    assert(loader.subroutine_index("zeta") == 2 && loader.subroutine_index("before") == -1);
    assert(loader.subroutine_index("0") == -1 && loader.subroutine_index("zz") == -1);
    context.enemies = &controller;
    controller.loader = &loader;
    controller.player_index = 2;
    controller.data.field_88 = 32;
    assert(controller.capacity() == 32 && controller.count() == 0);
    controller.data.field_88 = 0xffffffffu; controller.field_124 = 0x80000000u;
    assert(controller.capacity() == -1 && controller.count() == (-2147483647-1));
    controller.data.field_88 = 32; controller.field_124 = 0;
    current_enemy_generation = 0x1ffff;
    assert(controller.generation() == 0x1ffff);
    assert(controller.advance_generation() == 0x1ffff);
    assert(previous_enemy_generation == 0x1ffff && current_enemy_generation == 0x20001);
    current_enemy_generation = 0xffffffff;
    controller.player_index = -1;
    controller.advance_generation(); assert(current_enemy_generation == 0xffff0001);
    controller.player_index = 2;
    current_enemy_generation = 0x20005;
    EnemySpawn parameters;
    parameters.health = 900;
    expected_parameters = &parameters;
    expected_name = "entry";
    events.clear();
    Enemy* first = controller.create(expected_name, parameters, nullptr);
    assert((events == std::vector<int>{0,1,3}));
    assert(controller.count() == 1 && first->state.identifier.value == 0x20005);
    assert(controller.enemies.next == &first->controller_link && controller.enemies.tail == &first->controller_link);
    assert(!first->parent_link.owner && first->spawn_parameters.health == 900);
    events.clear();
    Enemy* second = controller.create(expected_name, parameters, first);
    assert((events == std::vector<int>{0,1,3}));
    assert(controller.count() == 2 && second->state.identifier.value == 0x20006);
    assert(controller.enemies.next == &second->controller_link && second->controller_link.next == &first->controller_link);
    assert(controller.enemies.tail == &first->controller_link);
    assert(first->children.next == &second->parent_link && first->children.tail == &second->parent_link);
    assert(second->parent() == first);
    // Original pointers alias storage; writes preserve signed word bits and
    // unrelated counters. This uses real Enemy/State/Data/Movement lifetimes.
    lookup_controller = &controller;
    controller.data.handles[0].value = second->state.identifier.value;
    resolved_enemy = second;
    lookup_calls = find_calls = 0;
    auto* selected_int = first->integer_destination(-9943);
    assert(selected_int == reinterpret_cast<std::int32_t*>(&second->state.counters.field_00));
    assert(lookup_calls == 4 && find_calls == 2); // both resolutions are retained
    *selected_int = std::numeric_limits<std::int32_t>::min();
    assert(second->state.counters.field_00 == 0x80000000u && first->state.counters.field_00 == 0);
    assert(first->integer_destination(-9949) == reinterpret_cast<std::int32_t*>(&controller.data.field_38));
    assert(first->integer_destination(-9926) == reinterpret_cast<std::int32_t*>(&controller.data.counters.field_00));
    for (int i = 0; i != 4; ++i) {
        auto* word = first->integer_destination(-9895 + i);
        assert(word == &enemy_script_globals[i]); *word = -100 - i;
    }
    auto* selected_float = first->float_destination(-9939);
    assert(selected_float == &second->state.counters.field_10);
    *selected_float = -17.25f;
    assert(second->state.counters.field_10 == -17.25f && first->state.counters.field_10 == 0.0f);
    assert(first->float_destination(-9935) == &first->state.counters.field_20);
    assert(first->float_destination(-9922) == &controller.data.counters.field_10);
    first->state.movements.emplace_back();
    const std::array<float*,4> coordinates{
        &first->state.movements[0].motion.position.x, &first->state.movements[0].motion.position.y,
        &first->state.movements[1].motion.position.x, &first->state.movements[1].motion.position.y};
    for (int i = 0; i != 4; ++i) {
        auto* coordinate = first->float_destination(-9995 + i);
        assert(coordinate == coordinates[i]); *coordinate = 37.0f + i;
    }
    // Stale and absent selections fall back to self; a stale handle is retained.
    resolved_enemy = nullptr;
    assert(first->integer_destination(-9943) == reinterpret_cast<std::int32_t*>(&first->state.counters.field_00));
    assert(first->float_destination(-9939) == &first->state.counters.field_10);
    assert(controller.data.handles[0].value == second->state.identifier.value);
    lookup_controller = nullptr; lookup_calls = find_calls = 0;
    assert(controller.selected(0) == nullptr && lookup_calls == 1 && find_calls == 0);
    for (std::uint32_t index : {16u, std::numeric_limits<std::uint32_t>::max()}) {
        lookup_calls = 0; bool threw = false;
        try { controller.selected(index); } catch (const std::out_of_range&) { threw = true; }
        assert(threw && lookup_calls == 0);
    }
    controller.data.handles[15].value = second->state.identifier.value;
    lookup_controller = &controller; resolved_enemy = second;
    assert(controller.selected(15) == second); // actual maximum valid slot
    // Actual publication runs the maintained by-value Enemy identifier, getter,
    // checked slot and handle assignment bodies. Only final list-find remains
    // the explicit lookup capture above. All unrelated owner bytes must survive.
    const auto first_id=first->state.identifier.value,second_id=second->state.identifier.value;
    unsigned publication_cases=0;
    for(unsigned index=0;index<16;++index)for(unsigned id:{0u,1u,0x80000000u,0xffffffffu})
    for(Enemy* target:{static_cast<Enemy*>(nullptr),first,second}) {
        first->state.identifier.value=id;second->state.identifier.value=id^0x12345678u;
        controller.data.field_84.value=0xa5a5a5a5u;
        std::array<unsigned char,sizeof(EnemyController)> expected;
        std::memcpy(expected.data(),&controller,sizeof(controller));
        const auto flag_offset=reinterpret_cast<unsigned char*>(&controller.data.field_84)-reinterpret_cast<unsigned char*>(&controller);
        const unsigned flag=(0xa5a5a5a5u&~1u)|(id&1u);
        std::memcpy(expected.data()+flag_offset,&flag,4);
        const auto offset=reinterpret_cast<unsigned char*>(&controller.data.handles[index])-reinterpret_cast<unsigned char*>(&controller);
        const unsigned identifier=target?target->state.identifier.value:0u;
        std::memcpy(expected.data()+offset,&identifier,4);
        std::array<unsigned char,sizeof(Enemy)> first_image,second_image;
        std::memcpy(first_image.data(),first,sizeof(Enemy));std::memcpy(second_image.data(),second,sizeof(Enemy));
        controller.set_field_84_bit_0(id);controller.set_selected(index,target);
        assert(!std::memcmp(expected.data(),&controller,sizeof(controller)));
        assert(!std::memcmp(first_image.data(),first,sizeof(Enemy)) && !std::memcmp(second_image.data(),second,sizeof(Enemy)));
        resolved_enemy=identifier?target:nullptr;lookup_calls=find_calls=0;
        assert(controller.selected(index)==resolved_enemy && lookup_calls==2 && find_calls==1);
        ++publication_cases;
    }
    // Native Enemy opcode 553 calls this real EnemyController +0x98
    // setter. Test the complete owner image: every byte except data.field_88
    // must survive, even for high-bit signed-looking input words.
    unsigned state_field_cases = 0;
    for (unsigned original : {0u,1u,0x80000000u,0xffffffffu,0xA5A55A5Au})
        for (unsigned value : {0u,1u,2u,0x12345678u,0x80000000u,0xffffffffu}) {
            controller.data.field_88 = original;
            std::array<unsigned char,sizeof(EnemyController)> expected;
            std::memcpy(expected.data(),&controller,sizeof(controller));
            const auto field_offset = reinterpret_cast<unsigned char*>(&controller.data.field_88) -
                reinterpret_cast<unsigned char*>(&controller);
            // Host x64 offset legitimately differs from the separately
            // verified native MSVC x86 +0x98 member layout.
            std::memcpy(expected.data()+field_offset,&value,sizeof(value));
            controller.set_field_88(value);
            assert(controller.data.field_88 == value);
            assert(std::memcmp(expected.data(),&controller,sizeof(controller)) == 0);
            ++state_field_cases;
        }
    assert(state_field_cases == 30);
    for(unsigned index:{16u,0x7fffffffu,0x80000000u,0xffffffffu})
    for(Enemy* target:{static_cast<Enemy*>(nullptr),first,second}) {
        std::array<unsigned char,sizeof(EnemyController)> before;
        std::memcpy(before.data(),&controller,sizeof(controller));bool threw=false;
        try {controller.set_selected(index,target);}catch(const std::out_of_range&){threw=true;}
        assert(threw && !std::memcmp(before.data(),&controller,sizeof(controller)));++publication_cases;
    }
    for(unsigned value:{0u,1u,306783378u,306783379u,0x80000000u,0xffffffffu}) {
        EnemyHealth health;std::array<unsigned,7> expected{9,17,23,31,41,47,0xf3};
        health.health=9;health.field_04=17;health.phase_health=23;
        health.scaled_health=31;health.threshold=41;health.damage=47;health.flags.bits=0xf3;
        expected[0]=value;
        health.set_health(value);assert(health.get_health()==value);
        expected[3]=static_cast<unsigned>(std::uint64_t(value)*7u);
        health.set_scaled_health(health.get_health());
        assert(!std::memcmp(&health,expected.data(),sizeof(health)));
    }
    first->state.identifier.value=first_id;second->state.identifier.value=second_id;
    controller.data.handles[0].value=second_id;controller.data.handles[15].value=second_id;
    lookup_controller=&controller;resolved_enemy=second;
    std::printf("Owned Enemy publication passed: %u slot/whole-owner/exception cases, full-width identifiers and scaled-health wrap.\n",publication_cases);
    unsigned integer_count = 0, float_count = 0;
    for (int index = -10000; index <= -9800; ++index) {
        integer_count += first->integer_destination(index) != nullptr;
        float_count += first->float_destination(index) != nullptr;
    }
    assert(integer_count == 19 && float_count == 24);
    for (int index : {0, 1, -1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()}) {
        assert(first->integer_destination(index) == nullptr && first->float_destination(index) == nullptr);
    }
    lookup_controller = nullptr; resolved_enemy = nullptr;
    // Reset retains independent flags/rank while clearing active script storage.
    first->main.flags.bits = 0xa5; first->main.rank = 0x7e;
    first->main.stack.words.assign(300, 0x12345678);
    first->main.stack.pointer = 123; first->main.stack.frame_base = 44;
    first->main.interpolators.resize(2);
    first->main.signal = 19;
    first->reset();
    assert(first->main.flags.bits == 0xa4 && first->main.rank == 0x7e && first->main.signal == 0);
    assert(first->main.async_id == -1 && first->main.manager == first && first->main.interpolators.empty());
    assert(first->main.position.subroutine == -1 && first->main.position.offset == -1);
    assert(first->main.stack.words.empty() && first->main.stack.words.capacity() >= 300);
    assert(first->runtimes.node == &first->main && !first->runtimes.next);
    assert(loader.select(first, "missing") == 0 && first->main.position.subroutine == -1);
    assert(first->main.position.offset == 0 && first->main.time == 0);
    check_enemy_phases(*first);
    second->parent_link.detach(); second->controller_link.detach(); first->controller_link.detach();
    assert(controller.enemies.tail == &controller.enemies && !controller.enemies.next);
    assert(first->children.tail == &first->children && !first->children.next);
    allocated.clear();
    check_enemy_clear_protocol();
    EnemyController angle_owner;
    unsigned angle_cases=0;
    constexpr float pi=3.1415927410125732f;
    for(float input:{-1000.f,-100.f,-7.f,-pi,-1.f,-0.f,0.f,1.f,pi,7.f,100.f,1000.f,
        std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::quiet_NaN()}) {
        auto expected=clear_image(angle_owner);float normalized=input;
        if(input>pi)for(int i=0;i<34 && normalized>pi;++i)normalized-=2.f*pi;
        else if(input<-pi)for(int i=0;i<34 && normalized<-pi;++i)normalized=2.f*pi+normalized;
        clear_patch(expected,angle_owner,angle_owner.angle_128.value,normalized);
        angle_owner.set_angle_128(input);
        assert(clear_image(angle_owner)==expected);++angle_cases;
    }
    std::printf("Owned Enemy Controller angle passed: %u float/whole-owner cases.\n",angle_cases);

}
