#include "dialogue_owner_fixture.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "DiagnosticAllocator.hpp"
#include "Enemy.hpp"
#include "EnemyController.hpp"
#include "Session.hpp"
#include "WindowState.hpp"
#include <array>
#include <atomic>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <new>

namespace {
std::atomic<long> allocations;
}
void* operator new(std::size_t size) {
    if (void* p = std::malloc(size ? size : 1)) { ++allocations; return p; }
    throw std::bad_alloc();
}
void operator delete(void* p) noexcept { if (p) { --allocations; std::free(p); } }
void operator delete(void* p, std::size_t) noexcept { ::operator delete(p); }
void* operator new[](std::size_t size) { return ::operator new(size); }
void operator delete[](void* p) noexcept { ::operator delete(p); }
void operator delete[](void* p, std::size_t) noexcept { ::operator delete(p); }

namespace th20 {
// Native startup, scheduler/resource lifetimes and active Enemy defeat are
// outside this constructor fixture. Empty-list clear uses the real body.
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
TaskInfo::~TaskInfo() = default;
void TaskInfo::enable() { std::abort(); }
void TaskInfo::disable() { std::abort(); }
FrontInf::~FrontInf() = default;
void FrontInf::enable() { std::abort(); }
EnemyController::~EnemyController() = default;
EclManager::~EclManager() = default;
Enemy::~Enemy() = default;
std::int32_t EclManager::execute_opcode() { std::abort(); }
std::int32_t EclManager::read_integer(std::int32_t) { std::abort(); }
std::int32_t* EclManager::integer_destination(std::int32_t) { std::abort(); }
float EclManager::read_float(std::int32_t) { std::abort(); }
float* EclManager::float_destination(std::int32_t) { std::abort(); }
std::int32_t Enemy::execute_opcode() { std::abort(); }
std::int32_t Enemy::read_integer(std::int32_t) { std::abort(); }
std::int32_t* Enemy::integer_destination(std::int32_t) { std::abort(); }
float Enemy::read_float(std::int32_t) { std::abort(); }
float* Enemy::float_destination(std::int32_t) { std::abort(); }
std::int32_t Enemy::defeat() { std::abort(); }
AnimationFile* shared_text_animation_file;
std::uint32_t current_enemy_generation;
std::uint32_t previous_enemy_generation;
void ecl_diagnostic_hint(const char*, ...) {}
void AnimationFile::clear() {
    assert(!bytes && !templates && !sprites && !scripts && !textures);
}
Animation* AnimationHandle::resolve() {
    Animation* output;
    if (test::try_dialogue_resolve(*this, output)) return output;
    value = 0;
    return nullptr;
}
void AnimationHandle::retire() { test::record_dialogue_retirement(*this); }
}

int main() {
    using namespace th20;
    using namespace th20::test;
    DiagnosticAllocator allocator;
    process_allocator = &allocator;
    std::array<std::uint8_t, 16> script{};
    unsigned constructions = 0, failures = 0, callbacks = 0, ready_reads = 0;
    DialogueOwnerFixture fixture;
    const std::vector<DialogueEvent> expected{
        {'s',20},{'s',20},{'i',7},{'r',0},{'r',0},{'r',1},{'r',1},
        {'s',21},{'s',21},{'i',7},{'r',2},{'r',2},{'r',3},{'r',3},
        {'r',0},{'r',1},{'r',2},{'r',3},
        {'r',0},{'r',1},{'r',2},{'r',3},{'b',0},{'l',0}};
    for (unsigned pattern = 0; pattern != 256; ++pattern) for (bool mutate : {false,true}) {
        const auto baseline = allocations.load();
        auto* input = pattern & 1u ? script.data() : nullptr;
        auto* d = fixture.construct(static_cast<unsigned char>(pattern), input, -1, mutate);
        fixture.check_guards(static_cast<unsigned char>(pattern));
        assert(fixture.events() == expected && d->script == input && d->state == 0);
        for (const auto* timer : {&d->timer_04,&d->timer_14,&d->timer_24}) {
            assert(timer->previous == -1 && timer->current == 0 && timer->current_fraction == 0);
            assert(timer->flag_bits.initialized == 1 && timer->flag_bits.mode == 0);
        }
        for (const auto& h : d->portraits) assert(h.value == 0);
        for (const auto& h : d->portrait_overlays) assert(h.value == 0);
        assert(!d->handle_54.value && !d->handle_68.value && !d->handle_6c.value && !d->handle_70.value);
        assert(d->handle_58.value == 0x200 && d->handle_5c.value == 0x201);
        assert(d->handle_60.value == 0x202 && d->handle_64.value == 0x203);
        assert(d->field_74 == 0 && d->field_78 == 0 && d->field_c8 == 0);
        assert(d->cursor.current == 0 && d->cursor.previous == 0 && d->cursor.count == 999);
        assert(d->cursor.minimum == 0 && d->cursor.wrapping == 1);
        assert(d->cursor.excluded.empty() && d->cursor.selection_history.empty());
        assert(d->cursor.count_history.empty());
        assert(d->ready_state == 0 && d->field_110 == 0 && d->field_114 == 0);
        assert(d->field_108 == (mutate ? 432 : 0) && d->field_10c == (mutate ? 567 : 0));
        for (auto value : d->fields_118) assert(value == 0);
        for (const auto& p : d->positions) assert(p.x == 16 && p.y == 0 && p.z == 0);
        assert(d->text_position.x == 384 && d->text_position.y == 640 && d->text_position.z == 0);
        assert(d->text_width == 320 && d->field_138 == 0 && d->field_13c == 0);
        std::uint32_t flags;
        std::memcpy(&flags, &d->flags, sizeof(flags));
        assert(flags == ((pattern * 0x01010101u) & ~0x7Fu));
        for (unsigned i = 0; i < 4; ++i) {
            auto& a = fixture.animation(i);
            assert(a.field_578 == 0x15 && a.field_579 == 0x15);
            assert(a.base.flags.word_04 == ((0xABCDEF00u + i) & ~0x400u));
            auto& child = fixture.animation(1);
            child.vector_5bc = Vector3(20.0f, 40.0f, 3.0f);
            const float child_scale = (pattern & 1u) ? 1.5f : 0.5f;
            child.base.vector_50.x = child_scale;
            window_state.scale = (pattern % 3u == 0) ? 1.0f : ((pattern % 3u == 1) ? 2.0f : 4.0f);
            d->handle_6c.value = 0x200u;
            d->field_114 = static_cast<std::int32_t>(i); // modes 0,1,2 and fallthrough 3
            assert(a.field_5dc && a.field_5dc(&a) == 0);
            fixture.check_follow(d, &a);
            float offset = 0.0f;
            if (i == 0) offset = -36.0f;
            else if (i == 1) offset = (child_scale < 1.0f)
                ? (child_scale + 0.125f) * 32.0f - 8.0f : 24.0f;
            else if (i == 2) offset = (child_scale + 0.125f) * 16.0f - 8.0f;
            const float ratio = 2.0f / window_state.scale;
            fixture.check_position(20.0f * ratio + offset, 40.0f * ratio, 3.0f);
            ++callbacks;
        }
        // Child identity is a real intrusive-tree traversal. A valid animation
        // handle with no matching child does not update the destination.
        if (pattern % 64u == 0) {
            auto& a = fixture.animation(0);
            const auto old_identifier = fixture.animation(1).base.field_440;
            fixture.animation(1).base.field_440 = 0x1234;
            const auto before = a.vector_5bc;
            const auto count = fixture.events().size();
            assert(a.field_5dc(&a) == 0);
            assert(fixture.events().size() == count + 1);
            assert(a.vector_5bc.x == before.x && a.vector_5bc.y == before.y &&
                   a.vector_5bc.z == before.z);
            fixture.animation(1).base.field_440 = old_identifier;
        }
        // Invalid lookups clear the handle and never move the target animation.
        if (pattern % 32u == 0) {
            d->handle_6c.value = 0xDEADBEEFu;
            auto& a = fixture.animation(0);
            const auto before = a.vector_5bc;
            const auto event_count = fixture.events().size();
            assert(a.field_5dc(&a) == 0);
            assert(d->handle_6c.value == 0 && fixture.events().size() == event_count);
            assert(a.vector_5bc.x == before.x && a.vector_5bc.y == before.y &&
                   a.vector_5bc.z == before.z);
        }
        for (auto ready : {-2147483647-1,-1,0,1,0x100,2147483647}) {
            d->ready_state = ready;
            assert(d->ready() == ready && fixture.front().dialogue_ready() == ready);
            assert(fixture.front().dialogue_value() == d);
            ++ready_reads;
        }
        // Exercise full native retirement order, including both array rows.
        for (unsigned i = 0; i < 4; ++i) {
            d->portraits[i].value = 0x1000 + i;
            d->portrait_overlays[i].value = 0x1100 + i;
        }
        d->handle_54.value = 0x1200;
        d->handle_68.value = 0x1201;
        d->handle_6c.value = 0x1202;
        d->handle_70.value = 0x1203; // Native destructor never retires this field.
        d->cursor.excluded.push_back(13);
        d->cursor.selection_history.push(29);
        d->cursor.count_history.push(31);
        {
            auto retirement = fixture.events();
            fixture.destroy();
        for (unsigned i = 0; i < 4; ++i) {
            retirement.push_back({'d', static_cast<std::int32_t>(0x1000 + i)});
            retirement.push_back({'d', static_cast<std::int32_t>(0x1100 + i)});
        }
            for (std::int32_t handle : {0x1200, 0x200, 0x201, 0x202, 0x203, 0x1201, 0x1202})
                retirement.push_back({'d', handle});
            assert(fixture.events() == retirement);
        }
        assert(allocations.load() == baseline);
        ++constructions;
    }
    for (unsigned pattern : {0u,0x55u,0xAAu,0xFFu}) for (int stage = 0; stage < 6; ++stage) {
        const auto baseline = allocations.load();
        bool caught = false;
        try { fixture.construct(static_cast<unsigned char>(pattern), script.data(), stage); }
        catch (const DialogueFailure& failure) { assert(failure.stage == stage); caught = true; }
        assert(caught && !fixture.subject() && allocations.load() == baseline);
        fixture.check_guards(static_cast<unsigned char>(pattern));
        ++failures;
    }
    auto* first = fixture.construct(0, script.data());
    {
        DialogueOwnerFixture second_fixture;
        auto* second = second_fixture.construct(0, script.data());
        auto& animation = fixture.animation(0);
        // The original callback reads the current FrontInf at invocation time.
        assert(current_front == &second_fixture.front());
        second->handle_6c.value = 0x200u;
        second_fixture.animation(1).vector_5bc = Vector3(10.0f, 20.0f, 3.0f);
        second_fixture.animation(1).base.vector_50.x = 1.0f;
        window_state.scale = 2.0f;
        assert(animation.field_5dc(&animation) == 0);
        second_fixture.check_follow(second, &animation);
        assert(first != second);
        ++callbacks;
    }
    fixture.destroy();
    std::cout << "Dialogue: " << constructions << " dirty constructions, " << failures
              << " unwind failures, " << callbacks << " live callbacks, "
              << ready_reads << " full-width ready reads passed\n";
}
