#pragma once

#include "EclRuntime.hpp"
#include "EnemySpawn.hpp"
#include "EnemyState.hpp"
#include <functional>

namespace th20 {

struct EnemyFlags { std::uint32_t bits; };

// Native construction and initialization establish these subobjects.
// Destruction and the whole opcode dispatcher remain open.
struct Enemy : EclManager {
    EnemyFlags flags;
    IntrusiveLink<Enemy> controller_link;
    EnemyState state;
    EnemySpawn spawn_parameters;
    IntrusiveList<Enemy> children;
    IntrusiveLink<Enemy> parent_link;
    std::function<void(Enemy*)> callback;
    std::int32_t player_index;
    Context* context;

    Enemy() noexcept;
    EnemyHealth* health_value();
    bool reward_multiplier_enabled();
    void set_damage_marker(std::uint32_t value);
    ~Enemy() override;
    Enemy* parent();
    bool bomb_drop_disabled();
    Vector3& position_ref();
    std::int32_t execute_opcode() override;
    std::int32_t read_integer(std::int32_t index) override;
    std::int32_t* integer_destination(std::int32_t index) override;
    float read_float(std::int32_t index) override;
    float* float_destination(std::int32_t index) override;
    std::int32_t integer_argument(std::int32_t index);
    float float_argument(std::int32_t index);
    Identifier32 identifier_value();
    std::int32_t integer_argument_value(std::int32_t index, std::int32_t value);
    float float_argument_value(std::int32_t index, float value);
    void select_context(std::int32_t index);
    void configure_phase(std::uint32_t index, std::int32_t life,
                         std::int32_t time, const char* name);
    void configure_timeout(std::uint32_t index, const char* name);
    void initialize(std::int32_t index, const char* name);
    int tick();
    int apply_spawn(const EnemySpawn& parameters);
    // Whole native defeat/resource processing remains undefined.
    std::int32_t defeat();
};

#if defined(_M_IX86)
static_assert(sizeof(Enemy) == 0x428);
static_assert(offsetof(Enemy, controller_link) == 0x74);
static_assert(offsetof(Enemy, state) == 0x88);
static_assert(offsetof(Enemy, spawn_parameters) == 0x378);
static_assert(offsetof(Enemy, children) == 0x3cc);
static_assert(offsetof(Enemy, parent_link) == 0x3e4);
static_assert(offsetof(Enemy, callback) == 0x3f8);
static_assert(offsetof(Enemy, player_index) == 0x420);
static_assert(offsetof(Enemy, context) == 0x424);
#endif

} // namespace th20
