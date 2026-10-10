#include "Animation.hpp"
#include "ClockScalar.hpp"
#include "DiagnosticAllocator.hpp"
#include "Enemy.hpp"
#include "Session.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <vector>

namespace {
std::array<th20::Animation*, 3> animations{};
std::vector<unsigned> observed_handles;
unsigned ticks = 0;
float observed_clock = 0;
int tick_result = 0;
bool inspect_spawn = false;
th20::EnemySpawn expected_spawn;
int expected_difficulty = 0;
}

namespace th20 {
// Explicit unresolved boundaries: Enemy retirement/virtual variable readers,
// native renderer lookup and the complete nonexact EnemyState tick. Real Enemy,
// ECL/State/Animation/Session lifetimes and both accepted orchestration bodies
// execute production source; the fixtures observe calls and inputs only.
LockRegistry process_locks;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
DiagnosticAllocator allocator;
DiagnosticAllocator* process_allocator = &allocator;
const Matrix4 identity_matrix = [] { Matrix4 m; for (int i=0;i<4;++i) m.elements[i][i]=1; return m; }();
Enemy::~Enemy() = default;
int Enemy::execute_opcode() { std::abort(); }
int Enemy::read_integer(int) { std::abort(); }
int* Enemy::integer_destination(int) { std::abort(); }
float Enemy::read_float(int) { std::abort(); }
float* Enemy::float_destination(int) { std::abort(); }
void AnimationHandle::retire() { std::abort(); }
Animation* AnimationHandle::resolve() {
    observed_handles.push_back(value);
    if (value >= 1 && value <= animations.size() && animations[value-1])
        return animations[value-1];
    value = 0; return nullptr;
}
int EnemyState::tick() {
    ++ticks; observed_clock = default_timer_clock;
    if (inspect_spawn) {
        assert(entity && &entity->state == this);
        assert(std::memcmp(&entity->spawn_parameters, &expected_spawn, sizeof(expected_spawn)) == 0);
        assert(movements.size() == 1);
        assert(std::memcmp(&movements[0].motion.position, &expected_spawn.position, sizeof(Vector3)) == 0);
        assert(identifier_188.value == static_cast<unsigned>(expected_spawn.field_0c));
        assert(health.health == static_cast<unsigned>(expected_spawn.health));
        assert(health.field_04 == health.health && health.phase_health == health.health);
        assert(pattern.base_kind == expected_spawn.field_10);
        assert(field_50 == expected_difficulty && field_30 == 0);
        assert(identifier_04.value == expected_spawn.field_50.value);
        assert(timer_288.current == 2 && timer_288.current_fraction == 2.0f);
        assert(std::memcmp(&counters, &expected_spawn.variables, sizeof(counters)) == 0);
        // This mutation proves that spawn consumes the state after the real
        // delegated tick, rather than returning early or replacing its result.
        pattern.base_kind = -31;
        flags.word_04 |= 0x80u;
        identifier.value = 1;
    }
    return tick_result;
}
}

int main() {
    using namespace th20;
    Enemy enemy;
    enemy.state.entity = &enemy;
    Animation first, last;
    animations = {&first, nullptr, &last};
    enemy.state.animations.resize(4);
    const float nan = std::numeric_limits<float>::quiet_NaN();
    const float inf = std::numeric_limits<float>::infinity();
    for (float slowdown : {-inf, -1.0f, -0.0f, 0.0f, 0.25f, 1.0f, 2.0f, inf, nan}) {
        for (float clock : {-2.0f, 0.0f, 0.5f, 1.0f, 2.0f, nan}) {
            for (unsigned retained : {0xa5000000u, 0xa5010000u}) {
                enemy.state.field_3c = slowdown;
                enemy.state.flags.word_04 = retained;
                enemy.state.animations[0].handle.value = 1;
                enemy.state.animations[1].handle.value = 2;
                enemy.state.animations[2].handle.value = 3;
                enemy.state.animations[3].handle.value = 999;
                first.field_560 = 17; last.field_560 = -9;
                first.base.flags.word_04 = 0xfedcba98u;
                last.base.flags.word_04 = 0x12345678u;
                default_timer_clock.value = clock;
                observed_handles.clear(); ticks = 0; tick_result = -73;
                const auto before = std::bit_cast<std::array<unsigned char,sizeof(EnemySpawn)>>(enemy.spawn_parameters);
                assert(enemy.tick() == -73 && ticks == 1);
                const bool slowed = !(slowdown <= 0);
                const bool resolve = slowed || (retained & 0x10000u);
                float expected = clock;
                if (slowed) {
                    expected = clock - clock * slowdown;
                    if (expected > 1) expected = 1;
                    else if (expected < 0) expected = 0;
                }
                assert((std::isnan(expected) && std::isnan(observed_clock)) ||
                       std::bit_cast<unsigned>(expected) == std::bit_cast<unsigned>(observed_clock));
                assert(std::bit_cast<unsigned>(clock) == std::bit_cast<unsigned>(default_timer_clock.value));
                assert(enemy.state.flags.word_04 == (retained | (slowed ? 0x10000u : 0u)));
                assert((std::bit_cast<std::array<unsigned char,sizeof(EnemySpawn)>>(enemy.spawn_parameters) == before));
                assert(first.base.flags.word_04 == 0xfedcba98u && last.base.flags.word_04 == 0x12345678u);
                if (resolve) {
                    assert((observed_handles == std::vector<unsigned>{1,2,3,999}));
                    assert(enemy.state.animations[1].handle.value == 0 && enemy.state.animations[3].handle.value == 0);
                    const float wanted = slowed ? slowdown : 0.0f;
                    assert(std::bit_cast<unsigned>(wanted) == std::bit_cast<unsigned>(first.field_560));
                    assert(std::bit_cast<unsigned>(wanted) == std::bit_cast<unsigned>(last.field_560));
                } else {
                    assert(observed_handles.empty() && first.field_560 == 17 && last.field_560 == -9);
                    assert(enemy.state.animations[1].handle.value == 2 && enemy.state.animations[3].handle.value == 999);
                }
            }
        }
    }
    enemy.state.animations.clear(); enemy.state.field_3c = 0;
    for (int mode : {0,1,2,3,4,5}) for (int health : {-7,0,999,1000,1001}) {
        for (int variant=0; variant<110; ++variant) {
            inspect_spawn = true; expected_difficulty = mode;
            session.table.field_1e0 = mode;
            session.table.field_1fc = variant % 3 == 0 ? -7 : variant % 3 == 1 ? 1234 : 55;
            EnemySpawn parameters;
            parameters.position = {1.25f,-2.5f,3.75f};
            parameters.field_0c = -123; parameters.field_10 = -456;
            parameters.health = health; parameters.flags_18 = static_cast<unsigned>(variant);
            parameters.flags_1c.bits = static_cast<unsigned>(variant+1);
            parameters.variables.field_00 = 0x87654321u;
            parameters.variables.field_10 = -12.5f;
            parameters.field_50.value = 0x1234abcdu;
            expected_spawn = parameters;
            enemy.state.field_20 = 2; enemy.state.field_24 = variant;
            enemy.state.field_254 = 0; enemy.state.field_258 = 0;
            enemy.state.flags.word_04 = 0xa5000000u;
            ticks = 0; tick_result = -99;
            default_timer_clock.value = 0.75f;
            assert(enemy.apply_spawn(parameters) == 0 && ticks == 1);
            assert(enemy.main.rank == (mode < 4 ? (1u << mode) : 2));
            const unsigned expected_flags = 0xa5000080u | ((parameters.flags_18 & 1u) << 3) |
                ((parameters.flags_1c.bits & 1u) << 10) | (health >= 1000 ? 0x4000u : 0u);
            assert(enemy.state.flags.word_04 == expected_flags);
            assert(enemy.state.pattern.base_kind == -31 && enemy.state.field_250 == 4);
            int expected_kind = 37;
            if (variant==5 || variant==25 || variant==53 || variant==94) expected_kind=33;
            else if (variant==15 || variant==109) expected_kind=45;
            else if (variant==10 || variant==56 || variant==99) expected_kind=41;
            else if (variant==30) expected_kind=51;
            else if (variant==35) expected_kind=50;
            else if (variant==40) expected_kind=49;
            assert(enemy.state.field_254 == expected_kind && enemy.state.field_258 == 1);
            assert(enemy.state.field_280 == (variant%3==0 ? 0 : variant%3==1 ? 999 : 55));
            assert(session.table.field_1fc == enemy.state.field_280);
        }
    }
    inspect_spawn = false;
    enemy.state.field_254 = 123; enemy.state.field_258 = -5;
    ticks = 0; assert(enemy.apply_spawn(enemy.spawn_parameters) == 0 && ticks == 1);
    assert(enemy.state.field_254 == 123 && enemy.state.field_258 == -5);
}
