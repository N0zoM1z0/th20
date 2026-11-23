#include "EnemyStateDialogueOpcode.hpp"
#include "LaserParameters.hpp"
#include "RenderMesh.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "AnimationHandleSetFlag0Recursive.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "EnemyController.hpp"
#include "AnimationFile.hpp"
#include "Animation.hpp"
#include "FogValue.hpp"
#include "StageResource.hpp"
#include "Context.hpp"
#include "DiagnosticAllocator.hpp"
#include "LockRegistry.hpp"
#include "EnemyStateMovementOpcode.hpp"
#include "EnemyStatePatternOpcode.hpp"
#include "EnemyStateControlOpcode.hpp"
#include "EnemyStateControllerManagementOpcode.hpp"
#include "EnemyStateTimeOpcode.hpp"
#include "EnemyStateCardOpcode.hpp"
#include "EnemyStateFrontendOpcode.hpp"
#include "HudGauge.hpp"
#include "SoundInf.hpp"
#include "SecureCrt.hpp"
#include "Card.hpp"
#include "ClockScalar.hpp"
#include "PlayerRecord.hpp"
#include "Session.hpp"
#include "GameController.hpp"
#include "Player.hpp"
#include "EnemyStateAnimationSpawnOpcode.hpp"
#include "EnemyStateCardStartOpcode.hpp"
#include "EnemyStateControllerSetterOpcode.hpp"
#include "EnemyStateFogOpcode.hpp"
#include "EnemyStateLaserOpcode.hpp"
#include "EnemyStateMembershipOpcode.hpp"
#include "EnemyStateMeshOpcode.hpp"
#include "EnemyStatePhaseOpcode.hpp"
#include "EnemyStateQueueCopyOpcode.hpp"
#include "EnemyStateQueuedParametersOpcode.hpp"
#include "EnemyStateScriptPointerOpcode.hpp"
#include "EnemyStateSharedQueuedParametersOpcode.hpp"
#include "EnemyStatePlayerAngleOpcode.hpp"
#include "EnemyStateBulletLaserCancelOpcode.hpp"
#include "EnemyStateShotCommandOpcode.hpp"
#include "EnemyStateShotFireOpcode.hpp"
#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <limits>
#include <initializer_list>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <new>
#include <vector>

namespace th20 {
GameRandom script_random(1);
DiagnosticAllocator* process_allocator = nullptr;
LockRegistry process_locks;
std::int32_t defeat_result = 0;
GameController* current_game_controller = nullptr;
Player* dispatch_test_player = nullptr;
alignas(BulletController) std::array<std::uint8_t, sizeof(BulletController)> bullet_controller_storage{};
alignas(BulletController) std::array<std::uint8_t, sizeof(BulletController)> alternate_bullet_controller_storage{};
alignas(LaserController) std::array<std::uint8_t, sizeof(LaserController)> laser_controller_storage{};
alignas(LaserController) std::array<std::uint8_t, sizeof(LaserController)> alternate_laser_controller_storage{};
BulletController* dispatch_test_bullets = nullptr;
BulletController* dispatch_test_bullets_alternate = nullptr;
LaserController* dispatch_test_lasers = nullptr;
LaserController* dispatch_test_lasers_alternate = nullptr;
std::int32_t game_controller_set_calls = 0;
std::uint32_t game_controller_last_value = 0;
std::int32_t card_finish_spell_calls = 0;
bool front_has_dialogue = false;
std::int32_t sound_effect_calls = 0;
std::int32_t sound_effect_id = -1;
float sound_effect_x = 0.0f;
std::array<std::int32_t,4> dispatch_order{};
std::int32_t dispatch_order_size = 0;
EnemyController* dispatch_test_enemy_controller = nullptr;
AnimationFile* dispatch_test_animation_file = nullptr;
std::int32_t animation_file_select_calls = 0;
std::int32_t animation_file_select_index = -1;
std::int32_t animation_spawn_calls = 0;
const char* animation_spawn_stem = reinterpret_cast<const char*>(1);
std::int32_t animation_spawn_script = -1;
Vector3 animation_spawn_position{};
float animation_spawn_rotation = 0.0f;
std::int32_t animation_spawn_layer = -1;
std::uint32_t animation_spawn_flags = 0xffffffffu;
Animation* dispatch_test_animation = nullptr;
std::uint32_t dispatch_test_animation_handle = 0;
std::int32_t animation_pool_resolve_calls = 0;
std::uint32_t animation_pool_resolve_last_handle = 0;
std::int32_t bullet_cancel_calls = 0;
std::int32_t bullet_cancel_mode = -1;
void (*dispatch_bullet_cancel_hook)(std::int32_t) = nullptr;
Animation** animation_spawn_output = reinterpret_cast<Animation**>(1);
bool dispatch_identifier_result = false;
std::int32_t dispatch_identifier_calls = 0;
std::uint32_t dispatch_identifier_value = 0;
std::int32_t fog_set_calls = 0;
std::int32_t fog_set_duration = 0;
std::int32_t fog_set_mode = 0;
FogValue fog_set_value{};
StageResourceOwner* process_stage_resource = nullptr;
extern const float native_progress_mesh_alpha_fade_span_02_56fbf8 = 0.2f;
extern const float native_negative_pi_56e0f8 = -3.1415927410125732f;
extern const float native_screen_half_2_56c8d0 = 2.0f;
extern const float native_screen_top_16_56cd90 = 16.0f;
extern const float native_two = 2.0f;
extern const float native_448 = 448.0f;
extern const float native_gameplay_width = 384.0f;
extern const float native_zero_56e0e8 = 0.0f;
extern const float native_speed_override_threshold = -990.0f;
extern const float native_one_56c8cc = 1.0f;
std::int32_t render_mesh_ctor_calls = 0;
std::int32_t render_mesh_dtor_calls = 0;
std::array<std::int32_t,4> render_mesh_ctor_arguments{};
bool mesh_owner_visible_during_float_read = false;
bool front_dialogue_ready = false;
std::int32_t front_dialogue_ready_calls = 0;
std::int32_t front_dialogue_command_calls = 0;
std::int32_t last_front_dialogue_command = 0;
std::int32_t laser_cancel_all_calls = 0;
struct DispatchLaserCapture {
    LaserController* receiver = nullptr;
    std::int32_t kind = -1, view_index = -1;
    Vector3 position{}, velocity{}, vector_0c{};
    float angle = 0.0f, length = 0.0f, field_14 = 0.0f, length_limit = 0.0f;
    float width = 0.0f, speed = 0.0f, radial_offset = 0.0f;
    float angular_velocity = 0.0f, growth_speed = 0.0f;
    float field_1c = 0.0f, field_20 = 0.0f, field_24 = 0.0f, field_30 = 0.0f;
    std::uint32_t type = 0, color = 0, flags = 0, handle = 0, count = 0;
    std::uint32_t field_2c = 0, field_34 = 0, command_index = 0;
    std::int32_t delay = 0, grow_time = 0, sustain_time = 0, shrink_time = 0;
    std::int32_t sound = 0, alternate_sound = 0, field_48 = 0, field_4c = 0;
    std::int32_t motion_sound = 0;
    std::vector<BulletCommand> commands;
};
DispatchLaserCapture dispatch_laser_capture;
std::int32_t dispatch_laser_create_calls = 0;
std::int32_t front_field_180_calls = 0;
std::int32_t front_field_180_value = 0;
std::int32_t front_stage_title_calls = 0;
std::int32_t front_boss_gauge_calls = 0;
std::int32_t front_boss_gauge_boss = -1;
std::int32_t front_boss_gauge_marker = -1;
float front_boss_gauge_fraction = 0.0f;
std::int32_t front_boss_gauge_value = 0;
std::int32_t animation_flags_add_calls = 0;
std::int32_t animation_flag0_set_calls = 0;
std::array<std::uint32_t,8> animation_flag0_set_handles{};
std::int32_t screen_factory_calls = 0;
std::int32_t screen_factory_mode = -1;
std::array<std::uint32_t,6> screen_factory_arguments{};
std::uint32_t current_enemy_generation = 1, previous_enemy_generation = 0;
std::int32_t dispatch_integer_read_calls = 0;
std::int32_t dispatch_integer_read_index = 0;
std::int32_t dispatch_integer_read_value = 0;
void (*dispatch_integer_read_hook)(std::int32_t) = nullptr;
std::int32_t dispatch_float_read_calls = 0;
std::array<std::int32_t,8> dispatch_float_read_indices{};
std::array<float,8> dispatch_float_read_values{};
std::array<std::int32_t,16> dispatch_integer_read_indices{};
std::array<std::int32_t,16> dispatch_integer_read_scripted_values{};
bool dispatch_integer_read_scripted = false;
std::int32_t dispatch_integer_throw_at = 0;
std::array<char,32> dispatch_read_kinds{};
std::array<std::int32_t,32> dispatch_read_indices{};
std::int32_t dispatch_read_trace_count = 0;
bool dispatch_read_trace_enabled = false;
std::int32_t dispatch_float_throw_at = 0;
void (*dispatch_float_read_hook)(std::int32_t) = nullptr;
EnemyQueuedRecord* dispatch_opcode619_record = nullptr;
ShotMetadata* dispatch_opcode619_original_metadata = nullptr;
bool dispatch_opcode619_cow_visible_before_float = false;
Context* dispatch_operand_original_context = nullptr;
Context* dispatch_operand_alternate_context = nullptr;
EnemyState* dispatch_operand_state = nullptr;
EnemyController* dispatch_operand_alternate_enemy_controller = nullptr;
BulletController* dispatch_operand_alternate_bullet_controller = nullptr;
void retarget_enemy_controller_during_integer_read(std::int32_t) {
    dispatch_operand_original_context->enemies = dispatch_operand_alternate_enemy_controller;
    dispatch_operand_state->context = dispatch_operand_alternate_context;
}
void retarget_context_player_during_first_float_read(std::int32_t) {
    if (dispatch_float_read_calls == 1)
        dispatch_operand_state->context = dispatch_operand_alternate_context;
}
void retarget_to_original_and_move_enemy_during_bullet_cancel(std::int32_t) {
    if (bullet_cancel_calls == 1) {
        dispatch_operand_state->context = dispatch_operand_original_context;
        dispatch_operand_state->motion_110.position = {30.0f,40.0f,0.0f};
    }
}
void retarget_bullet_controller_during_first_float_read(std::int32_t) {
    if (dispatch_float_read_calls == 1) {
        dispatch_operand_original_context->primary_owner = dispatch_operand_alternate_bullet_controller;
        dispatch_operand_state->context = dispatch_operand_alternate_context;
    }
}
void throw_during_integer_read(std::int32_t) { throw 553; }
void throw_during_second_integer_read(std::int32_t) {
    if (dispatch_integer_read_calls == 2) throw 557;
}
void observe_integer_read(std::int32_t) {}
void throw_during_mesh_float_read(std::int32_t) {
    mesh_owner_visible_during_float_read =
        dispatch_operand_state && dispatch_operand_state->mesh &&
        dispatch_operand_state->mesh->mesh == nullptr;
    throw 554;
}
void observe_float_read(std::int32_t) {}
void observe_opcode619_cow_before_float(std::int32_t index) {
    assert(index == -102);
    assert(dispatch_opcode619_record != nullptr);
    assert(dispatch_opcode619_original_metadata != nullptr);
    assert(dispatch_opcode619_record->owner.get() != dispatch_opcode619_original_metadata);
    assert(dispatch_opcode619_record->owner.use_count() == 1);
    assert(dispatch_opcode619_record->owner->field_00 == dispatch_opcode619_original_metadata->field_00);
    dispatch_opcode619_cow_visible_before_float = true;
}
void throw_during_float_read(std::int32_t) {
    if (dispatch_float_read_calls == dispatch_float_throw_at) throw 554;
}
bool pattern_drop_called = false;
bool pattern_drop_bomb_mark = false;
Vector3 pattern_drop_origin{};
std::int32_t enemy_script_globals[4]{};
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
RenderMesh::RenderMesh(std::int32_t columns_value, std::int32_t rows_value,
                       std::int32_t surface, std::int32_t view)
    : columns(columns_value), rows(rows_value), root(), strip_handles(nullptr),
      strips(nullptr), vertices(nullptr), positions(nullptr), view_index(view),
      context(nullptr) {
    ++render_mesh_ctor_calls;
    render_mesh_ctor_arguments = {columns_value, rows_value, surface, view};
}
RenderMesh::~RenderMesh() { ++render_mesh_dtor_calls; }
Enemy::~Enemy() = default;
EnemyController::~EnemyController() = default;
BulletController::~BulletController() = default;
void BulletController::enable() {}
std::int32_t Bullet::cancel(std::int32_t mode) {
    ++bullet_cancel_calls;
    bullet_cancel_mode = mode;
    state = 4;
    if (dispatch_bullet_cancel_hook) dispatch_bullet_cancel_hook(mode);
    return 0;
}
std::int32_t LaserController::cancel_all(std::int32_t, std::int32_t) {
    assert(this == dispatch_test_lasers);
    ++laser_cancel_all_calls;
    return 0;
}
LaserController::~LaserController() = default;
class DispatchTestLaser final : public Laser {
public:
    std::int32_t circle_calls = 0;
    Vector3 circle_center{};
    float circle_radius = 0.0f;
    std::int32_t circle_mode = -1, circle_argument = -1, circle_result = 0;

    void slot_08() override {}
    void set_parameter_flag(std::uint32_t) override {}
    void slot_10() override {}
    std::int32_t initialize_laser(const void*) override { return 0; }
    void slot_18() override {}
    std::int32_t update() override { return 0; }
    std::int32_t draw() override { return 0; }
    void slot_24() override {}
    void slot_28() override {}
    std::int32_t cancel_rectangle(const Vector3&, const Vector3&, float,
                                  std::int32_t, std::int32_t) override { return 0; }
    std::int32_t cancel_circle(const Vector3& center, float radius,
                               std::int32_t mode, std::int32_t argument) override {
        ++circle_calls;
        circle_center = center;
        circle_radius = radius;
        circle_mode = mode;
        circle_argument = argument;
        return circle_result;
    }
    void slot_34() override {}
    void cancel_segments(const std::uint8_t*, std::int32_t) override {}
    void slot_3c() override {}
    void slot_40() override {}
    std::int32_t erase(std::int32_t, std::int32_t) override { return 0; }
    std::int32_t proximity(const Vector3&, float) override { return 0; }
    std::int32_t cancel_all(std::int32_t) override { return 0; }
    void slot_50() override {}
    void slot_54() override {}
    void slot_58() override {}
    void slot_5c() override {}
    void slot_60() override {}
    void slot_64() override {}
    void slot_68() override {}
    void slot_6c() override {}
    void slot_70() override {}
    void slot_74() override {}
    void slot_78() override {}
    void slot_7c() override {}
    void slot_80() override {}
};
std::int32_t LaserController::create_laser(std::int32_t kind, const void* parameters) {
    assert(this == dispatch_test_lasers || this == dispatch_test_lasers_alternate);
    ++dispatch_laser_create_calls;
    dispatch_laser_capture = DispatchLaserCapture{};
    dispatch_laser_capture.receiver = this;
    dispatch_laser_capture.kind = kind;
    switch (kind) {
    case 0: {
        const auto& p = *static_cast<const LaserType0Parameters*>(parameters);
        dispatch_laser_capture.position = p.position;
        dispatch_laser_capture.angle = p.angle;
        dispatch_laser_capture.length = p.length;
        dispatch_laser_capture.field_14 = p.field_14;
        dispatch_laser_capture.length_limit = p.length_limit;
        dispatch_laser_capture.width = p.width;
        dispatch_laser_capture.speed = p.speed;
        dispatch_laser_capture.type = p.type;
        dispatch_laser_capture.color = p.color;
        dispatch_laser_capture.radial_offset = p.radial_offset;
        dispatch_laser_capture.command_index = p.command_index;
        dispatch_laser_capture.flags = p.flags;
        dispatch_laser_capture.field_48 = p.field_48;
        dispatch_laser_capture.field_4c = p.field_4c;
        dispatch_laser_capture.view_index = p.view_index;
        dispatch_laser_capture.commands.assign(p.commands.begin(), p.commands.end());
        break;
    }
    case 1: {
        const auto& p = *static_cast<const LaserType1Parameters*>(parameters);
        dispatch_laser_capture.position = p.position;
        dispatch_laser_capture.velocity = p.velocity;
        dispatch_laser_capture.angle = p.angle;
        dispatch_laser_capture.angular_velocity = p.angular_velocity;
        dispatch_laser_capture.length_limit = p.length_limit;
        dispatch_laser_capture.length = p.length;
        dispatch_laser_capture.width = p.width;
        dispatch_laser_capture.growth_speed = p.growth_speed;
        dispatch_laser_capture.delay = p.delay;
        dispatch_laser_capture.grow_time = p.grow_time;
        dispatch_laser_capture.sustain_time = p.sustain_time;
        dispatch_laser_capture.shrink_time = p.shrink_time;
        dispatch_laser_capture.sound = p.sound;
        dispatch_laser_capture.alternate_sound = p.field_44;
        dispatch_laser_capture.handle = p.handle;
        dispatch_laser_capture.radial_offset = p.radial_offset;
        dispatch_laser_capture.command_index = p.command_index;
        dispatch_laser_capture.type = p.type;
        dispatch_laser_capture.color = p.color;
        dispatch_laser_capture.flags = p.flags;
        dispatch_laser_capture.view_index = p.view_index;
        dispatch_laser_capture.commands.assign(p.commands.begin(), p.commands.end());
        break;
    }
    case 2: {
        const auto& p = *static_cast<const LaserType2Parameters*>(parameters);
        dispatch_laser_capture.position = p.position;
        dispatch_laser_capture.angle = p.angle;
        dispatch_laser_capture.width = p.width;
        dispatch_laser_capture.speed = p.speed;
        dispatch_laser_capture.type = p.type;
        dispatch_laser_capture.color = p.color;
        dispatch_laser_capture.count = p.count;
        dispatch_laser_capture.radial_offset = p.radial_offset;
        dispatch_laser_capture.flags = p.flags.word;
        dispatch_laser_capture.sound = p.sound;
        dispatch_laser_capture.motion_sound = p.motion_sound;
        dispatch_laser_capture.command_index = p.command_index;
        dispatch_laser_capture.view_index = p.view_index;
        dispatch_laser_capture.commands.assign(p.commands.begin(), p.commands.end());
        break;
    }
    case 3: {
        const auto& p = *static_cast<const LaserType3Parameters*>(parameters);
        dispatch_laser_capture.position = p.position;
        dispatch_laser_capture.vector_0c = p.vector_0c;
        dispatch_laser_capture.angle = p.angle;
        dispatch_laser_capture.field_1c = p.field_1c;
        dispatch_laser_capture.field_20 = p.field_20;
        dispatch_laser_capture.field_24 = p.field_24;
        dispatch_laser_capture.handle = p.handle;
        dispatch_laser_capture.field_2c = p.field_2c;
        dispatch_laser_capture.field_30 = p.field_30;
        dispatch_laser_capture.field_34 = p.field_34;
        dispatch_laser_capture.flags = p.flags;
        dispatch_laser_capture.view_index = p.view_index;
        dispatch_laser_capture.commands.assign(p.commands.begin(), p.commands.end());
        break;
    }
    default:
        assert(false);
    }
    return 0;
}
std::int32_t Enemy::defeat() { return defeat_result; }
void EnemyPattern::drop(const Vector3& origin, bool bomb_mark) {
    pattern_drop_called = true;
    pattern_drop_bomb_mark = bomb_mark;
    pattern_drop_origin = origin;
}
std::int32_t Enemy::read_integer(std::int32_t index) {
    if (!dispatch_integer_read_hook) return 0;
    const auto call = dispatch_integer_read_calls++;
    dispatch_integer_read_index = index;
    if (call < static_cast<std::int32_t>(dispatch_integer_read_indices.size()))
        dispatch_integer_read_indices[call] = index;
    if (dispatch_read_trace_enabled && dispatch_read_trace_count < static_cast<std::int32_t>(dispatch_read_kinds.size())) {
        dispatch_read_kinds[dispatch_read_trace_count] = 'i';
        dispatch_read_indices[dispatch_read_trace_count++] = index;
    }
    dispatch_integer_read_hook(index);
    if (dispatch_integer_throw_at == call + 1) throw 609;
    return dispatch_integer_read_scripted
        ? dispatch_integer_read_scripted_values[call] : dispatch_integer_read_value;
}
float Enemy::read_float(std::int32_t index) {
    if (!dispatch_float_read_hook) return 0.0f;
    const auto call = dispatch_float_read_calls++;
    if (call < static_cast<std::int32_t>(dispatch_float_read_indices.size()))
        dispatch_float_read_indices[call] = index;
    if (dispatch_read_trace_enabled && dispatch_read_trace_count < static_cast<std::int32_t>(dispatch_read_kinds.size())) {
        dispatch_read_kinds[dispatch_read_trace_count] = 'f';
        dispatch_read_indices[dispatch_read_trace_count++] = index;
    }
    dispatch_float_read_hook(index);
    return call < static_cast<std::int32_t>(dispatch_float_read_values.size())
        ? dispatch_float_read_values[call] : 0.0f;
}
void GameController::set_field_34(std::uint32_t value) {
    assert(this == current_game_controller);
    ++game_controller_set_calls;
    game_controller_last_value = value;
}
Player::~Player() = default;
void Player::enable() {}
Enemy* selected_test_enemy = nullptr;
std::array<Enemy*,16> dispatch_find_enemies{};
std::array<std::uint32_t,8> dispatch_find_identifiers{};
std::int32_t dispatch_find_calls = 0;
EnemyController* dispatch_find_receiver = nullptr;
std::uint32_t dispatch_find_identifier = 0;
Enemy* EnemyController::find(std::uint32_t identifier) {
    ++dispatch_find_calls;
    dispatch_find_receiver = this;
    dispatch_find_identifier = identifier;
    if (dispatch_find_calls <= static_cast<std::int32_t>(dispatch_find_identifiers.size()))
        dispatch_find_identifiers[static_cast<std::size_t>(dispatch_find_calls - 1)] = identifier;
    for (auto* candidate : dispatch_find_enemies) {
        if (candidate && candidate->state.identifier.get() == identifier)
            return candidate;
    }
    return selected_test_enemy && selected_test_enemy->state.identifier.get() == identifier
        ? selected_test_enemy : nullptr;
}
bool EnemyController::has_identifier(std::uint32_t identifier) {
    assert(this == dispatch_test_enemy_controller);
    ++dispatch_identifier_calls;
    dispatch_identifier_value = identifier;
    return identifier != 0 && dispatch_identifier_result;
}
AnimationFile* EnemyController::animation_file(std::int32_t index) {
    assert(this == dispatch_test_enemy_controller);
    ++animation_file_select_calls;
    animation_file_select_index = index;
    if (dispatch_order_size < static_cast<std::int32_t>(dispatch_order.size()))
        dispatch_order[dispatch_order_size++] = 2;
    return dispatch_test_animation_file;
}
AnimationFile::AnimationFile()
    : id(0), filename(), stem(), bytes(nullptr), templates(nullptr),
      texture_count(0), script_count(0), sprite_count(0), sprites(nullptr),
      scripts(nullptr), textures(nullptr), stage(0), field_60(0), field_64(0),
      field_68(0), field_6c(0) {}
AnimationFile::~AnimationFile() = default;
AnimationBase::AnimationBase() noexcept = default;
Animation::Animation() noexcept = default;
Animation::~Animation() noexcept = default;
AnimationHandle AnimationFile::spawn(const char* expected_stem, std::int32_t script,
    const Vector3* position, float rotation, std::int32_t layer,
    std::uint32_t flags, Animation** output) {
    assert(this == dispatch_test_animation_file);
    ++animation_spawn_calls;
    animation_spawn_stem = expected_stem;
    animation_spawn_script = script;
    animation_spawn_position = position ? *position : Vector3{};
    animation_spawn_rotation = rotation;
    animation_spawn_layer = layer;
    animation_spawn_flags = flags;
    animation_spawn_output = output;
    if (dispatch_order_size < static_cast<std::int32_t>(dispatch_order.size()))
        dispatch_order[dispatch_order_size++] = 3;
    return AnimationHandle{};
}
void StageResourceOwner::set_fog(std::int32_t duration, std::int32_t mode,
                                 const FogValue& value) {
    assert(this == process_stage_resource);
    ++fog_set_calls;
    fog_set_duration = duration;
    fog_set_mode = mode;
    fog_set_value = value;
}
void AnimationHandle::retire() {}
Card::~Card() = default;
void Card::finish_spell() { ++card_finish_spell_calls; }
SoundInf process_sound;
SoundEffectRequest::SoundEffectRequest() : id(0), count(0), pans{} {}
SoundCommand::SoundCommand() : type(0), argument(0), stage(0), name{} {}
SoundEffectChannel::SoundEffectChannel()
    : buffer(nullptr), cooldown(-1), definition(nullptr), id(0), pan(0), was_playing(0) {}
SoundInf::SoundInf() noexcept = default;
SoundInf::~SoundInf() = default;
extern "C" int strcpy_s(char* destination, std::size_t capacity, const char* source) {
    if (!destination || !source || capacity == 0) return 22;
    const std::size_t length = std::strlen(source);
    if (length >= capacity) { destination[0] = '\0'; return 34; }
    std::memcpy(destination, source, length + 1);
    return 0;
}
void SoundInf::request_effect_at(std::int32_t id, float x) {
    if (dispatch_order_size < static_cast<std::int32_t>(dispatch_order.size()))
        dispatch_order[dispatch_order_size++] = 1;
    ++sound_effect_calls;
    sound_effect_id = id;
    sound_effect_x = x;
}
FrontInf* current_front = nullptr;
void FrontInf::set_dialogue_command_4b9740(std::int32_t command) {
    ++front_dialogue_command_calls;
    last_front_dialogue_command = command;
}
AnimationPoolOwner test_animation_pool;
AnimationPoolOwner* current_animation_pool = &test_animation_pool;
struct NativeScreenInf;
NativeScreenInf* screen_factory_4250f0(std::int32_t mode,
    std::uint32_t p1, std::uint32_t p2, std::uint32_t p3, std::uint32_t p4,
    std::int32_t priority, std::uint32_t view) {
    ++screen_factory_calls;
    screen_factory_mode = mode;
    screen_factory_arguments = {p1, p2, p3, p4,
        static_cast<std::uint32_t>(priority), view};
    return nullptr;
}
HudGauge::HudGauge() = default;
FrontBossPanel::FrontBossPanel() noexcept = default;
FrontFlags::FrontFlags() noexcept = default;
FrontInf::FrontInf() : TaskInfo() {}
FrontInf::~FrontInf() = default;
void FrontInf::enable() {}
std::int32_t FrontInf::has_dialogue() { return front_has_dialogue ? 1 : 0; }
void FrontInf::show_stage_title() { ++front_stage_title_calls; }
void FrontInf::set_field_180(std::int32_t value) {
    ++front_field_180_calls;
    front_field_180_value = value;
    field_180 = value;
}
void FrontInf::set_boss_gauge(std::int32_t boss, std::int32_t marker,
                              float fraction, std::int32_t value) {
    ++front_boss_gauge_calls;
    front_boss_gauge_boss = boss;
    front_boss_gauge_marker = marker;
    front_boss_gauge_fraction = fraction;
    front_boss_gauge_value = value;
}
std::int32_t FrontInf::dialogue_ready() {
    ++front_dialogue_ready_calls;
    return front_dialogue_ready ? 1 : 0;
}
bool execute_enemy_phase_opcode(EnemyState&, const EclInstruction&, std::int32_t) { return false; }
bool execute_enemy_card_start_opcode(EnemyState&, const EclInstruction&, std::int32_t) { return false; }
bool execute_enemy_shot_fire_opcode(EnemyState&, std::int32_t) { return false; }
int execute_enemy_animation_secondary_opcode(EnemyState&) { return 0; }
int execute_enemy_animation_state_opcode(EnemyState&) { return 0; }
int execute_enemy_animation_effect_flag2_opcode(EnemyState&) { return 0; }
int execute_enemy_animation_effect_spawn_opcode(EnemyState&) { return 0; }
int execute_enemy_animation_effect_flag2_handle_opcode(EnemyState&) { return 0; }
int execute_enemy_animation_effect_rotate_opcode(EnemyState&) { return 0; }
int execute_enemy_animation_spawn_mapped(EnemyState&) { return 0; }
int execute_enemy_animation_spawn_primary_from_field(EnemyState&) { return 0; }
int execute_enemy_animation_link_offset_opcode(EnemyState&) { return 0; }
int execute_enemy_animation_link_parent_opcode(EnemyState&) { return 0; }
int execute_enemy_animation_state_selectors_opcode(EnemyState&) { return 0; }
int execute_enemy_animation_flags_opcode(EnemyState&, std::int32_t) { return 0; }
int execute_enemy_has_selected_identifier_opcode(EnemyState&) { return 0; }
int execute_enemy_effect_position_request_opcode(EnemyState&) { return 0; }
int execute_enemy_effect_position_spawn_opcode(EnemyState&) { return 0; }
int execute_enemy_effect_spawn_and_update_opcode(EnemyState&) { return 0; }
int execute_enemy_set_found_flag_bit_9_opcode(EnemyState&) { return 0; }
int execute_enemy_animation_flags_add_opcode(EnemyState&) { ++animation_flags_add_calls; return 0; }
Animation* AnimationPoolOwner::resolve_handle(std::uint32_t handle) {
    ++animation_pool_resolve_calls;
    animation_pool_resolve_last_handle = handle;
    return handle == dispatch_test_animation_handle ? dispatch_test_animation : nullptr;
}
void AnimationPoolOwner::retire_handle(std::uint32_t) {}
void AnimationPoolOwner::interrupt_handle(std::uint32_t, std::int32_t) {}
int EnemyState::spawn_from_opcode() { return 0; }
int EnemyState::spawn_animation() { return 0; }
void EnemyState::change_animation() {}
void TH20_FASTCALL set_animation_handle_flag0_recursively(AnimationHandle* handle) {
    if (animation_flag0_set_calls < static_cast<std::int32_t>(animation_flag0_set_handles.size()))
        animation_flag0_set_handles[animation_flag0_set_calls] = handle->value;
    ++animation_flag0_set_calls;
}
}

int main() {
    using namespace th20;

    alignas(GameController) std::array<std::uint8_t, sizeof(GameController)> game_storage{};
    current_game_controller = reinterpret_cast<GameController*>(game_storage.data());
    DiagnosticAllocator dispatch_allocator;
    process_allocator = &dispatch_allocator;
    Player player_fixture;
    Player alternate_player_fixture;
    dispatch_test_player = &player_fixture;

    Animation dispatch_animation;
    dispatch_test_animation = &dispatch_animation;
    dispatch_test_animation_handle = 0x12345678u;
    dispatch_animation.base.vector_38.z = 1.57079632679f;
    // The native SoundInf queue scans exactly slots 0..30, publishes into
    // the first empty record, and leaves the final 32nd record untouched.
    for (auto& command : process_sound.commands) {
        command.type = 0;
        command.argument = -7;
        command.stage = 9;
        std::memset(command.name, 'x', sizeof command.name);
    }
    process_sound.enqueue(2, 17, "dummy");
    assert(process_sound.commands[0].type == 2);
    assert(process_sound.commands[0].argument == 17);
    assert(process_sound.commands[0].stage == 0);
    assert(std::strcmp(process_sound.commands[0].name, "dummy") == 0);
    assert(process_sound.commands[1].type == 0);
    assert(process_locks.slot(11).try_lock());
    process_locks.slot(11).unlock();

    process_sound.commands[0].type = 4;
    process_sound.commands[1].type = 6;
    process_sound.commands[2].type = 8;
    process_sound.enqueue(3, 29, "front-voice.wav");
    assert(process_sound.commands[3].type == 3);
    assert(process_sound.commands[3].argument == 29);
    assert(process_sound.commands[3].stage == 0);
    assert(std::strcmp(process_sound.commands[3].name, "front-voice.wav") == 0);

    for (std::size_t i = 0; i < 31; ++i) {
        process_sound.commands[i].type = static_cast<std::int32_t>(i + 1);
    }
    process_sound.commands[31].type = 0;
    process_sound.commands[31].argument = 0x12345678;
    process_sound.enqueue(7, 41, "must-not-use-slot-31.wav");
    assert(process_sound.commands[31].type == 0);
    assert(process_sound.commands[31].argument == 0x12345678);
    assert(process_locks.slot(11).try_lock());
    process_locks.slot(11).unlock();
    Enemy enemy;
    Enemy found_enemy;
    Enemy found_enemy2;
    Context context;
    PlayerRecord player_record;
    EnemyController controller;
    EnemyController alternate_controller;
    Context alternate_context;
    AnimationFile test_animation_file;
    StageResourceOwner stage_resource{};
    dispatch_test_enemy_controller = &controller;
    dispatch_test_animation_file = &test_animation_file;
    process_stage_resource = &stage_resource;
    dispatch_test_bullets = ::new (static_cast<void*>(bullet_controller_storage.data())) BulletController();
    dispatch_test_bullets_alternate = ::new (static_cast<void*>(alternate_bullet_controller_storage.data())) BulletController();
    dispatch_test_lasers = ::new (static_cast<void*>(laser_controller_storage.data())) LaserController();
    dispatch_test_lasers_alternate = ::new (static_cast<void*>(alternate_laser_controller_storage.data())) LaserController();
    auto* alternate_player = &alternate_player_fixture;
    context.object_04 = dispatch_test_player;
    alternate_context.object_04 = alternate_player;
    session.contexts[0].object_04 = dispatch_test_player;
    context.current_player = &player_record;
    context.enemies = &controller;
    context.primary_owner = dispatch_test_bullets;
    alternate_context.enemies = &alternate_controller;
    alternate_context.primary_owner = dispatch_test_bullets_alternate;
    alternate_context.object_14 = dispatch_test_lasers_alternate;
    session.contexts[0].primary_owner = dispatch_test_bullets;
    context.object_14 = dispatch_test_lasers;
    session.contexts[0].object_14 = dispatch_test_lasers;
    enemy.state.context = &context;
    session.contexts[0].enemies = &controller;
    dispatch_operand_original_context = &context;
    dispatch_operand_alternate_context = &alternate_context;
    dispatch_operand_state = &enemy.state;
    dispatch_operand_alternate_enemy_controller = &alternate_controller;
    dispatch_operand_alternate_bullet_controller = dispatch_test_bullets_alternate;
    selected_test_enemy = &enemy;
    Card card;
    context.card_owner = &card;
    FrontInf front;
    current_front = &front;
    enemy.state.context = &context;
    enemy.state.identifier = 0x12345678u;
    found_enemy.state.identifier = 0x00000324u;
    found_enemy.state.motion_110.position = {12.0f,34.0f,56.0f};
    EclLoader loader;
    alignas(16) std::array<std::uint8_t, 16 + 16 + 16 * 4> packet{};
    loader.records.push_back({"root-test", packet.data()});
    loader.subroutine_count = 1;
    enemy.loader = &loader;
    enemy.main.manager = &enemy;
    enemy.main.position.subroutine = 0;
    enemy.main.position.offset = 0;
    enemy.current_runtime = &enemy.main;
    enemy.state.entity = &enemy;
    enemy.state.movements.resize(1);

    auto set_packet = [&](std::int16_t opcode,
                          std::initializer_list<std::uint32_t> args,
                          std::uint16_t references = 0) {
        std::array<std::uint32_t,16> words{};
        assert(args.size() <= words.size());
        std::copy(args.begin(), args.end(), words.begin());
        auto* ins = reinterpret_cast<EclInstruction*>(packet.data() + 16);
        std::memset(ins, 0, sizeof(EclInstruction) + sizeof(words));
        ins->opcode = opcode;
        ins->length = static_cast<std::uint16_t>(sizeof(EclInstruction) + sizeof(words));
        ins->references = references;
        ins->argument_count = static_cast<std::uint8_t>(words.size());
        std::memcpy(ins + 1, words.data(), sizeof(words));
    };
    auto bits = [](float value) { std::uint32_t out; std::memcpy(&out,&value,4); return out; };

    // The 1,457-byte native 609-612 branch now runs through the real root
    // dispatcher, the production writable-shot COW selector and the real
    // PMR BulletCommand vector. The four opcodes differ in explicit/cursor
    // indexing and base/extended operand layouts.
    const auto run_shot_command_case = [&](std::int32_t opcode,
                                           std::uint32_t command_index,
                                           std::uint32_t cursor_before,
                                           std::size_t initial_size,
                                           bool expect_extended,
                                           bool expect_cursor_mode,
                                           bool expect_cow) {
        enemy.state.queued.clear();
        auto& selected_record = enemy.state.queued.emplace_front();
        enemy.state.queued.emplace_front(); // selected_record is now index 1
        selected_record.owner = std::make_shared<ShotMetadata>();
        auto* original_metadata = selected_record.owner.get();
        original_metadata->commands.resize(initial_size);
        for (std::size_t i = 0; i < initial_size; ++i) {
            auto& command = original_metadata->commands[i];
            command.flags = 0xaabb0000u + static_cast<std::uint32_t>(i);
            command.opcode = 0xbeef0000u + static_cast<std::uint32_t>(i);
            command.operand_10 = 100 + static_cast<std::int32_t>(i);
            command.operand_14 = 200 + static_cast<std::int32_t>(i);
            command.operand_18 = 300 + static_cast<std::int32_t>(i);
            command.operand_1c = 400 + static_cast<std::int32_t>(i);
            command.operand_00 = 500.0f + static_cast<float>(i);
            command.operand_04 = 600.0f + static_cast<float>(i);
            command.operand_08 = 700.0f + static_cast<float>(i);
            command.operand_0c = 800.0f + static_cast<float>(i);
            command.script = "preserved command";
        }
        original_metadata->field_30 = cursor_before;
        std::shared_ptr<ShotMetadata> shared_owner;
        if (expect_cow) shared_owner = selected_record.owner;

        const std::size_t integer_count = expect_extended ? 6u : 4u;
        std::array<std::uint32_t,8> integer_values{};
        integer_values[0] = 1u;
        if (!expect_cursor_mode) integer_values[1] = command_index;
        const std::size_t operand_start = expect_cursor_mode ? 1u : 2u;
        const std::array<std::uint32_t,6> payload_values{
            0x11112222u, 0x33334444u, 0x55556666u,
            0x77778888u, 0x9999aaaau, 0xbbbbccccu
        };
        for (std::size_t i = 0; i < integer_count; ++i)
            integer_values[operand_start + i] = payload_values[i];
        const std::array<float,4> float_values{{
            -0.0f, 1.25f, -2.5f, 9.75f
        }};
        dispatch_integer_read_calls = 0;
        dispatch_integer_read_index = 0;
        dispatch_integer_read_indices = {};
        dispatch_integer_read_scripted_values = {};
        dispatch_integer_read_scripted = true;
        dispatch_integer_throw_at = 0;
        dispatch_integer_read_hook = &observe_integer_read;
        for (std::size_t i = 0; i < integer_values.size(); ++i)
            dispatch_integer_read_scripted_values[i] = static_cast<std::int32_t>(integer_values[i]);
        dispatch_float_read_calls = 0;
        dispatch_float_read_indices = {};
        dispatch_float_read_values = {};
        dispatch_float_read_hook = &observe_float_read;
        for (std::size_t i = 0; i < float_values.size(); ++i)
            dispatch_float_read_values[i] = float_values[i];
        dispatch_float_throw_at = 0;
        dispatch_read_trace_count = 0;
        dispatch_read_kinds = {};
        dispatch_read_indices = {};
        dispatch_read_trace_enabled = true;

        std::array<std::uint32_t,12> reference_words{};
        reference_words.fill(static_cast<std::uint32_t>(-101));
        const std::size_t float_count = expect_extended ? 4u : 2u;
        const std::size_t first_float = (expect_cursor_mode ? 1u : 2u) + integer_count;
        for (std::size_t i = 0; i < float_count; ++i)
            reference_words[first_float + i] = bits(-101.0f);
        set_packet(opcode, {
            reference_words[0], reference_words[1], reference_words[2], reference_words[3],
            reference_words[4], reference_words[5], reference_words[6], reference_words[7],
            reference_words[8], reference_words[9], reference_words[10], reference_words[11]
        }, 0x0fffu);

        assert(enemy.state.execute_opcode() == 0);
        dispatch_read_trace_enabled = false;
        dispatch_integer_read_hook = nullptr;
        dispatch_float_read_hook = nullptr;
        dispatch_integer_read_scripted = false;

        const std::size_t expected_integer_count = 1u + (expect_cursor_mode ? 0u : 1u) + integer_count;
        assert(dispatch_integer_read_calls == static_cast<std::int32_t>(expected_integer_count));
        assert(dispatch_float_read_calls == static_cast<std::int32_t>(float_count));
        assert(dispatch_read_trace_count == static_cast<std::int32_t>(expected_integer_count + float_count));
        for (std::size_t i = 0; i < expected_integer_count; ++i) {
            assert(dispatch_read_kinds[i] == 'i' && dispatch_read_indices[i] == -101);
        }
        for (std::size_t i = 0; i < float_count; ++i) {
            const auto at = expected_integer_count + i;
            assert(dispatch_read_kinds[at] == 'f' && dispatch_read_indices[at] == -101);
        }

        auto* metadata = selected_record.owner.get();
        assert(metadata != nullptr);
        assert((metadata != original_metadata) == expect_cow);
        if (expect_cow) {
            assert(selected_record.owner != shared_owner);
            assert(selected_record.owner.use_count() == 1);
            assert(shared_owner.use_count() == 1);
            assert(shared_owner->field_30 == cursor_before);
            assert(shared_owner->commands.size() == initial_size);
        } else {
            assert(selected_record.owner.get() == original_metadata);
        }

        const std::size_t target_index = expect_cursor_mode ? cursor_before : command_index;
        assert(metadata->commands.size() == std::max(initial_size, target_index + 1u));
        const auto& command = metadata->commands[target_index];
        assert(command.flags == integer_values[operand_start]);
        assert(command.opcode == integer_values[operand_start + 1]);
        assert(command.operand_10 == static_cast<std::int32_t>(integer_values[operand_start + 2]));
        assert(command.operand_14 == static_cast<std::int32_t>(integer_values[operand_start + 3]));
        if (expect_extended) {
            assert(command.operand_18 == static_cast<std::int32_t>(integer_values[operand_start + 4]));
            assert(command.operand_1c == static_cast<std::int32_t>(integer_values[operand_start + 5]));
        } else if (target_index < initial_size) {
            assert(command.operand_18 == 300 + static_cast<std::int32_t>(target_index));
            assert(command.operand_1c == 400 + static_cast<std::int32_t>(target_index));
        } else {
            assert(command.operand_18 == 0 && command.operand_1c == 0);
        }
        assert(bits(command.operand_00) == bits(float_values[0]));
        assert(bits(command.operand_04) == bits(float_values[1]));
        if (expect_extended) {
            assert(bits(command.operand_08) == bits(float_values[2]));
            assert(bits(command.operand_0c) == bits(float_values[3]));
        } else if (target_index < initial_size) {
            assert(bits(command.operand_08) == bits(700.0f + static_cast<float>(target_index)));
            assert(bits(command.operand_0c) == bits(800.0f + static_cast<float>(target_index)));
        } else {
            assert(command.operand_08 == 0.0f && command.operand_0c == 0.0f);
        }
        if (target_index < initial_size)
            assert(command.script && std::strcmp(command.script, "preserved command") == 0);
        else
            assert(command.script == nullptr);
        assert(metadata->field_30 == (expect_cursor_mode ? cursor_before + 1u : command_index + 1u));
        assert(metadata->field_24 == 0 && metadata->field_28 == 0 &&
               metadata->field_2c == 0 && metadata->field_34 == 0);
    };

    run_shot_command_case(609, 3, 17, 2, false, false, false);
    run_shot_command_case(610, 1, 17, 4, true, false, true);
    run_shot_command_case(611, 0, 3, 2, false, true, false);
    run_shot_command_case(612, 1, 1, 3, true, true, false);

    // An exception in the second float read preserves the resize and every
    // earlier field write but does not commit the metadata command cursor.
    enemy.state.queued.clear();
    auto& partial_record = enemy.state.queued.emplace_front();
    partial_record.owner = std::make_shared<ShotMetadata>();
    partial_record.owner->commands.resize(2);
    partial_record.owner->field_30 = 17;
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_scripted_values = {};
    dispatch_integer_read_scripted = true;
    dispatch_integer_throw_at = 0;
    dispatch_integer_read_hook = &observe_integer_read;
    dispatch_integer_read_scripted_values[0] = 0;
    dispatch_integer_read_scripted_values[1] = 4;
    dispatch_integer_read_scripted_values[2] = 0x11112222;
    dispatch_integer_read_scripted_values[3] = 0x33334444;
    dispatch_integer_read_scripted_values[4] = 0x55556666;
    dispatch_integer_read_scripted_values[5] = 0x77778888;
    dispatch_integer_read_scripted_values[6] = 0x9999aaaa;
    dispatch_integer_read_scripted_values[7] = 0xbbbbcccc;
    dispatch_float_read_calls = 0;
    dispatch_float_read_values = {-0.0f, 1.25f, -2.5f, 9.75f};
    dispatch_float_read_hook = &throw_during_float_read;
    dispatch_float_throw_at = 2;
    set_packet(610, {
        static_cast<std::uint32_t>(-101), static_cast<std::uint32_t>(-101),
        static_cast<std::uint32_t>(-101), static_cast<std::uint32_t>(-101),
        static_cast<std::uint32_t>(-101), static_cast<std::uint32_t>(-101),
        static_cast<std::uint32_t>(-101), static_cast<std::uint32_t>(-101),
        bits(-101.0f), bits(-101.0f), bits(-101.0f), bits(-101.0f)
    }, 0x0fffu);
    bool shot_command_threw = false;
    try { enemy.state.execute_opcode(); }
    catch (int value) { shot_command_threw = value == 554; }
    dispatch_integer_read_hook = nullptr;
    dispatch_float_read_hook = nullptr;
    dispatch_integer_read_scripted = false;
    dispatch_integer_throw_at = 0;
    dispatch_float_throw_at = 0;
    assert(shot_command_threw);
    assert(dispatch_integer_read_calls == 8 && dispatch_float_read_calls == 2);
    assert(partial_record.owner->commands.size() == 5);
    assert(partial_record.owner->commands[4].flags == 0x11112222u);
    assert(partial_record.owner->commands[4].opcode == 0x33334444u);
    assert(partial_record.owner->commands[4].operand_10 == 0x55556666);
    assert(partial_record.owner->commands[4].operand_14 == 0x77778888);
    assert(bits(partial_record.owner->commands[4].operand_00) == bits(-0.0f));
    assert(partial_record.owner->commands[4].operand_04 == 0.0f);
    assert(partial_record.owner->field_30 == 17);

    // Native opcode 614 copies a complete EnemyQueuedRecord through the
    // production forward_list helper and the real 119B copy-assignment leaf.
    // This is not a ShotParameters-only copy or a metadata COW operation.
    const auto queued_record_at = [&](std::uint32_t index) -> EnemyQueuedRecord& {
        auto it = enemy.state.queued.begin();
        std::advance(it, static_cast<std::ptrdiff_t>(index));
        return *it;
    };
    enemy.state.queued.clear();
    enemy.state.queued.emplace_front();
    enemy.state.queued.emplace_front();
    enemy.state.queued.emplace_front();
    auto& queue_destination = queued_record_at(0);
    auto& queue_middle = queued_record_at(1);
    auto& queue_source = queued_record_at(2);

    auto old_destination_owner = std::make_shared<ShotMetadata>();
    old_destination_owner->field_00 = 11.0f;
    old_destination_owner->commands.resize(1);
    old_destination_owner->commands[0].opcode = 0x11110000u;
    queue_destination.owner = old_destination_owner;
    queue_destination.parameters.type = 0x01020304u;
    queue_destination.parameters.color = 0x11121314u;
    queue_destination.parameters.position = {1.0f,2.0f,3.0f};
    queue_destination.parameters.angle = 4.0f;
    queue_destination.parameters.angle_step = 5.0f;
    queue_destination.parameters.speed = 6.0f;
    queue_destination.parameters.speed_step = 7.0f;
    queue_destination.parameters.count = 8;
    queue_destination.parameters.rows = 9;
    queue_destination.field_30 = 10;
    queue_destination.vector_34 = {11.0f,12.0f,13.0f};
    queue_destination.vector_40 = {14.0f,15.0f,16.0f};

    auto source_owner = std::make_shared<ShotMetadata>();
    source_owner->field_00 = 91.25f;
    source_owner->field_14 = 92.5f;
    source_owner->field_24 = 0x24242424u;
    source_owner->commands.resize(2);
    source_owner->commands[0].opcode = 0xabcdef01u;
    source_owner->commands[1].flags = 0x76543210u;
    queue_source.owner = source_owner;
    queue_source.parameters.type = 0x12345678u;
    queue_source.parameters.color = 0x87654321u;
    queue_source.parameters.position = {-1.25f,2.5f,-3.75f};
    queue_source.parameters.angle = 0.125f;
    queue_source.parameters.angle_step = -0.25f;
    queue_source.parameters.speed = 8.5f;
    queue_source.parameters.speed_step = -9.75f;
    queue_source.parameters.count = 321;
    queue_source.parameters.rows = 17;
    queue_source.field_30 = 0xfedcba98u;
    queue_source.vector_34 = {21.0f,22.0f,23.0f};
    queue_source.vector_40 = {-31.0f,-32.0f,-33.0f};
    queue_middle.field_30 = 0x55667788u;

    dispatch_integer_read_calls = 0;
    dispatch_integer_read_hook = &observe_integer_read;
    set_packet(614, {0,2});
    assert(enemy.state.execute_opcode() == 0);
    dispatch_integer_read_hook = nullptr;
    assert(dispatch_integer_read_calls == 0);
    assert(std::distance(enemy.state.queued.begin(), enemy.state.queued.end()) == 3);
    assert(queue_destination.owner == source_owner && queue_source.owner == source_owner);
    assert(source_owner.use_count() == 3);
    assert(old_destination_owner.use_count() == 1);
    assert(queue_destination.parameters.type == 0x12345678u);
    assert(queue_destination.parameters.color == 0x87654321u);
    assert(queue_destination.parameters.position.x == -1.25f &&
           queue_destination.parameters.position.y == 2.5f &&
           queue_destination.parameters.position.z == -3.75f);
    assert(queue_destination.parameters.angle == 0.125f &&
           queue_destination.parameters.angle_step == -0.25f);
    assert(queue_destination.parameters.speed == 8.5f &&
           queue_destination.parameters.speed_step == -9.75f);
    assert(queue_destination.parameters.count == 321 && queue_destination.parameters.rows == 17);
    assert(queue_destination.field_30 == 0xfedcba98u);
    assert(queue_destination.vector_34.x == 21.0f &&
           queue_destination.vector_34.y == 22.0f &&
           queue_destination.vector_34.z == 23.0f);
    assert(queue_destination.vector_40.x == -31.0f &&
           queue_destination.vector_40.y == -32.0f &&
           queue_destination.vector_40.z == -33.0f);
    assert(source_owner->field_00 == 91.25f && source_owner->field_14 == 92.5f);
    assert(source_owner->commands.size() == 2);
    assert(source_owner->commands[0].opcode == 0xabcdef01u);
    assert(source_owner->commands[1].flags == 0x76543210u);
    assert(queue_middle.field_30 == 0x55667788u);

    // Same-index copy is genuine self-assignment and does not change the
    // metadata owner's reference count or any source field.
    const auto source_owner_count = source_owner.use_count();
    set_packet(614, {2,2});
    assert(enemy.state.execute_opcode() == 0);
    assert(source_owner.use_count() == source_owner_count);
    assert(queue_source.field_30 == 0xfedcba98u);

    // Destination growth is performed before source lookup/copy. Existing
    // source index 2 is copied into newly appended destination index 5.
    set_packet(614, {5,2});
    assert(enemy.state.execute_opcode() == 0);
    assert(std::distance(enemy.state.queued.begin(), enemy.state.queued.end()) == 6);
    auto& grown_destination = queued_record_at(5);
    assert(grown_destination.owner == source_owner);
    assert(grown_destination.parameters.type == 0x12345678u);
    assert(grown_destination.field_30 == 0xfedcba98u);
    assert(source_owner.use_count() == 4);

    // Source growth also uses the original forward_list resize path. The
    // newly created source record is default-initialized and copied whole.
    auto& old_index_one = queued_record_at(1);
    auto old_index_one_owner = std::make_shared<ShotMetadata>();
    old_index_one.owner = old_index_one_owner;
    old_index_one.parameters.type = 0xaabbccddu;
    set_packet(614, {1,8});
    assert(enemy.state.execute_opcode() == 0);
    assert(std::distance(enemy.state.queued.begin(), enemy.state.queued.end()) == 9);
    assert(old_index_one.owner == nullptr);
    assert(old_index_one.parameters.type == 0u);
    assert(old_index_one.field_30 == 0u);
    assert(old_index_one.vector_34.x == 0.0f && old_index_one.vector_40.z == 0.0f);
    assert(old_index_one_owner.use_count() == 1);

    // Both operands are read before any list mutation. Force the second
    // referenced operand to throw after the first resolves to index 0; the
    // two-node queue and its complete record images must remain untouched.
    enemy.state.queued.clear();
    enemy.state.queued.emplace_front();
    enemy.state.queued.emplace_front();
    auto& exception_destination = queued_record_at(0);
    auto& exception_source = queued_record_at(1);
    exception_destination.parameters.type = 0x13572468u;
    exception_destination.field_30 = 0x24681357u;
    exception_source.parameters.type = 0xabcdef01u;
    exception_source.field_30 = 0x10fedcbau;
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_indices = {};
    dispatch_integer_read_scripted_values = {};
    dispatch_integer_read_scripted_values[0] = 0;
    dispatch_integer_read_scripted_values[1] = 8;
    dispatch_integer_read_scripted = true;
    dispatch_integer_read_hook = &throw_during_second_integer_read;
    set_packet(614, {static_cast<std::uint32_t>(-101),
                     static_cast<std::uint32_t>(-101)}, 0x3);
    bool queue_copy_threw = false;
    try { enemy.state.execute_opcode(); }
    catch (int value) { queue_copy_threw = value == 557; }
    dispatch_integer_read_hook = nullptr;
    dispatch_integer_read_scripted = false;
    assert(queue_copy_threw);
    assert(dispatch_integer_read_calls == 2);
    assert(dispatch_integer_read_indices[0] == -101 &&
           dispatch_integer_read_indices[1] == -101);
    assert(std::distance(enemy.state.queued.begin(), enemy.state.queued.end()) == 2);
    assert(exception_destination.parameters.type == 0x13572468u);
    assert(exception_destination.field_30 == 0x24681357u);
    assert(exception_source.parameters.type == 0xabcdef01u);
    assert(exception_source.field_30 == 0x10fedcbau);

    // The four large Laser branches now execute their production helper with
    // real LaserType0/1/2/3 temporary constructors, the real writable-shot
    // selector, and a capture-only create_laser factory boundary.
    std::shared_ptr<ShotMetadata> laser_shared_original;
    const auto prepare_laser_shot = [&](bool use_vector40, bool share_owner) -> EnemyQueuedRecord* {
        enemy.state.queued.clear();
        auto& record = enemy.state.queued.emplace_front();
        record.owner = std::make_shared<ShotMetadata>();
        auto& metadata = *record.owner;
        metadata.commands.resize(2);
        metadata.commands[0].operand_00 = 1.25f;
        metadata.commands[0].operand_10 = 0x101;
        metadata.commands[0].opcode = 0x202;
        metadata.commands[0].flags = 0x303;
        metadata.commands[1].operand_04 = -2.5f;
        metadata.commands[1].operand_14 = 0x404;
        metadata.commands[1].opcode = 0x505;
        metadata.commands[1].flags = 0x606;
        metadata.field_00 = 1.75f;
        metadata.field_14 = 2.5f;
        metadata.field_24 = 3;
        metadata.field_28 = 4;
        metadata.field_2c = 5;
        metadata.field_30 = 6;
        metadata.field_34 = 0x10;
        metadata.sound = 7;
        metadata.alternate_sound = 8;
        record.parameters.type = 9;
        record.parameters.color = 10;
        record.parameters.position = {11.0f,12.0f,13.0f};
        record.parameters.angle = 0.5f;
        record.parameters.speed = 14.0f;
        record.vector_34 = {1.0f,2.0f,3.0f};
        record.vector_40 = use_vector40
            ? Vector3{10.0f,20.0f,1.0f} : Vector3{10.0f,20.0f,0.9f};
        enemy.state.motion_110.position = {100.0f,200.0f,300.0f};
        enemy.state.field_2e8 = 6;
        if (share_owner) laser_shared_original = record.owner;
        else laser_shared_original.reset();
        return &record;
    };

    auto* laser_record = prepare_laser_shot(true, false);
    dispatch_laser_create_calls = 0;
    set_packet(702, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(dispatch_laser_create_calls == 1 && dispatch_laser_capture.kind == 0);
    assert(dispatch_laser_capture.receiver == dispatch_test_lasers);
    assert(dispatch_laser_capture.position.x == 11.0f &&
           dispatch_laser_capture.position.y == 22.0f &&
           dispatch_laser_capture.position.z == 0.0f);
    assert(dispatch_laser_capture.angle == 0.5f);
    assert(dispatch_laser_capture.length == 12.0f && dispatch_laser_capture.field_14 == 11.0f);
    assert(dispatch_laser_capture.length_limit == 13.0f && dispatch_laser_capture.width == 2.5f);
    assert(dispatch_laser_capture.speed == 14.0f);
    assert(dispatch_laser_capture.type == 9 && dispatch_laser_capture.color == 10);
    assert(dispatch_laser_capture.radial_offset == 1.75f && dispatch_laser_capture.flags == 0x11u);
    assert(dispatch_laser_capture.field_48 == 7 && dispatch_laser_capture.field_4c == 8);
    assert(dispatch_laser_capture.view_index == 6);
    assert(dispatch_laser_capture.commands.size() == 2);
    assert(dispatch_laser_capture.commands[0].opcode == 0x202 &&
           dispatch_laser_capture.commands[0].flags == 0x303);
    assert(dispatch_laser_capture.commands[0].operand_00 == 1.25f &&
           dispatch_laser_capture.commands[0].operand_10 == 0x101);
    assert(dispatch_laser_capture.commands[1].operand_04 == -2.5f &&
           dispatch_laser_capture.commands[1].operand_14 == 0x404);
    assert(laser_record->owner.use_count() == 1);

    // Opcode 703 takes the fallback position path, performs COW on a shared
    // metadata owner, reads handle operand 1 late, and then resolves the
    // current Context LaserController after that operand read.
    laser_record = prepare_laser_shot(false, true);
    dispatch_laser_create_calls = 0;
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_value = 0x12345678;
    dispatch_integer_read_hook = &retarget_enemy_controller_during_integer_read;
    dispatch_operand_original_context = &context;
    dispatch_operand_alternate_context = &alternate_context;
    dispatch_operand_state = &enemy.state;
    dispatch_operand_alternate_enemy_controller = &alternate_controller;
    set_packet(703, {0,static_cast<std::uint32_t>(-101),0,0,0,0,0,0}, 2);
    assert(enemy.state.execute_opcode() == 0);
    dispatch_integer_read_hook = nullptr;
    assert(dispatch_integer_read_calls == 1 && dispatch_integer_read_index == -101);
    assert(context.enemies == &alternate_controller && enemy.state.context == &alternate_context);
    assert(dispatch_laser_create_calls == 1 && dispatch_laser_capture.kind == 1);
    assert(dispatch_laser_capture.receiver == dispatch_test_lasers_alternate);
    assert(dispatch_laser_capture.position.x == 101.0f &&
           dispatch_laser_capture.position.y == 202.0f &&
           dispatch_laser_capture.position.z == 303.0f);
    assert(dispatch_laser_capture.angle == 0.5f && dispatch_laser_capture.growth_speed == 14.0f);
    assert(dispatch_laser_capture.length == 11.0f && dispatch_laser_capture.length_limit == 12.0f);
    assert(dispatch_laser_capture.width == 2.5f && dispatch_laser_capture.radial_offset == 1.75f);
    assert(dispatch_laser_capture.delay == 3 && dispatch_laser_capture.grow_time == 4);
    assert(dispatch_laser_capture.sustain_time == 5 && dispatch_laser_capture.shrink_time == 6);
    assert(dispatch_laser_capture.sound == 7 && dispatch_laser_capture.alternate_sound == 8);
    assert(dispatch_laser_capture.flags == 0x12u && dispatch_laser_capture.handle == 0x12345678u);
    assert(dispatch_laser_capture.view_index == 6 && dispatch_laser_capture.commands.size() == 2);
    assert(dispatch_laser_capture.commands[0].operand_00 == 1.25f &&
           dispatch_laser_capture.commands[0].operand_10 == 0x101);
    assert(dispatch_laser_capture.commands[1].operand_04 == -2.5f &&
           dispatch_laser_capture.commands[1].operand_14 == 0x404);
    assert(laser_record->owner != laser_shared_original);
    assert(laser_shared_original->field_34 == 0x10 && laser_shared_original->commands.size() == 2);
    context.enemies = &controller;
    enemy.state.context = &context;

    laser_record = prepare_laser_shot(true, false);
    dispatch_laser_create_calls = 0;
    set_packet(711, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(dispatch_laser_create_calls == 1 && dispatch_laser_capture.kind == 2);
    assert(dispatch_laser_capture.receiver == dispatch_test_lasers);
    assert(dispatch_laser_capture.position.x == 11.0f &&
           dispatch_laser_capture.position.y == 22.0f &&
           dispatch_laser_capture.position.z == 0.0f);
    assert(dispatch_laser_capture.angle == 0.5f && dispatch_laser_capture.speed == 14.0f);
    assert(dispatch_laser_capture.type == 9 && dispatch_laser_capture.color == 10);
    assert(dispatch_laser_capture.count == 3 && dispatch_laser_capture.width == 2.5f);
    assert(dispatch_laser_capture.radial_offset == 1.75f && dispatch_laser_capture.flags == 1u);
    assert(dispatch_laser_capture.sound == 7 && dispatch_laser_capture.motion_sound == 8);
    assert(dispatch_laser_capture.view_index == 6 && dispatch_laser_capture.commands.size() == 2);
    assert(dispatch_laser_capture.commands[0].operand_00 == 1.25f &&
           dispatch_laser_capture.commands[0].operand_10 == 0x101);

    laser_record = prepare_laser_shot(false, false);
    dispatch_laser_create_calls = 0;
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_value = 0x87654321;
    dispatch_integer_read_hook = &retarget_enemy_controller_during_integer_read;
    dispatch_operand_original_context = &context;
    dispatch_operand_alternate_context = &alternate_context;
    dispatch_operand_state = &enemy.state;
    dispatch_operand_alternate_enemy_controller = &alternate_controller;
    set_packet(713, {0,static_cast<std::uint32_t>(-101),0,0,0,0,0,0}, 2);
    assert(enemy.state.execute_opcode() == 0);
    dispatch_integer_read_hook = nullptr;
    assert(dispatch_integer_read_calls == 1 && dispatch_integer_read_index == -101);
    assert(context.enemies == &alternate_controller && enemy.state.context == &alternate_context);
    assert(dispatch_laser_create_calls == 1 && dispatch_laser_capture.kind == 3);
    assert(dispatch_laser_capture.receiver == dispatch_test_lasers_alternate);
    assert(dispatch_laser_capture.position.x == 101.0f &&
           dispatch_laser_capture.position.y == 202.0f &&
           dispatch_laser_capture.position.z == 303.0f);
    assert(dispatch_laser_capture.angle == 0.5f);
    assert(dispatch_laser_capture.field_2c == 10u && dispatch_laser_capture.field_34 == 3u);
    assert(dispatch_laser_capture.field_24 == 2.5f && dispatch_laser_capture.field_20 == 13.0f);
    assert(dispatch_laser_capture.field_30 == 1.75f);
    assert(dispatch_laser_capture.handle == 0x87654321u);
    assert(dispatch_laser_capture.flags == 0u && dispatch_laser_capture.view_index == 6);
    assert(dispatch_laser_capture.commands.size() == 2);
    assert(dispatch_laser_capture.commands[1].operand_04 == -2.5f &&
           dispatch_laser_capture.commands[1].operand_14 == 0x404);
    context.enemies = &controller;
    enemy.state.context = &context;

    // The late 703 handle operand is read after the COW selection and all
    // metadata copies. A thrown VM read must skip the factory call while
    // preserving the detached metadata owner and the original shared value.
    laser_record = prepare_laser_shot(false, true);
    auto* original_laser_metadata = laser_shared_original.get();
    dispatch_laser_create_calls = 0;
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_hook = &throw_during_integer_read;
    set_packet(703, {0,static_cast<std::uint32_t>(-101),0,0,0,0,0,0}, 2);
    bool laser_handle_threw = false;
    try { enemy.state.execute_opcode(); }
    catch (int value) { laser_handle_threw = value == 553; }
    dispatch_integer_read_hook = nullptr;
    assert(laser_handle_threw);
    assert(dispatch_integer_read_calls == 1 && dispatch_integer_read_index == -101);
    assert(dispatch_laser_create_calls == 0);
    assert(laser_record->owner.get() != original_laser_metadata);
    assert(laser_record->owner.use_count() == 1);
    assert(laser_shared_original.use_count() == 1);
    assert(original_laser_metadata->field_34 == 0x10);
    assert(original_laser_metadata->commands.size() == 2);
    assert(laser_record->owner->field_34 == 0x10);
    assert(laser_record->owner->commands.size() == 2);

    // Native opcode 621 releases the previous EnemyMeshOwner before reading
    // either operand, then conditionally allocates the 17x17 RenderMesh only
    // for a strictly positive radius. Both allocator template paths and the
    // EnemyMeshOwner destructor are the maintained production implementations.
    enemy.state.field_2e8 = 9;
    render_mesh_ctor_calls = 0;
    render_mesh_dtor_calls = 0;
    set_packet(621, {bits(5.5f),0x89abcdefu,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.mesh != nullptr && enemy.state.mesh->mesh != nullptr);
    assert(enemy.state.mesh->radius == 5.5f);
    assert(enemy.state.mesh->current_radius == 16.0f);
    assert(enemy.state.mesh->color == 0x89abcdefu);
    assert(enemy.state.mesh->phase_x.value == 0.0f && enemy.state.mesh->phase_y.value == 0.0f);
    assert(render_mesh_ctor_calls == 1 && render_mesh_dtor_calls == 0);
    assert((render_mesh_ctor_arguments == std::array<std::int32_t,4>{17,17,0,9}));
    assert(enemy.state.mesh->mesh->columns == 17 && enemy.state.mesh->mesh->rows == 17);
    assert(enemy.state.mesh->mesh->view_index == 9);

    // Equality with zero takes the no-renderer branch. Replacing the owner
    // destroys the prior real EnemyMeshOwner and its RenderMesh before the
    // newly allocated owner is populated.
    set_packet(621, {bits(0.0f),0x76543210u,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.mesh != nullptr && enemy.state.mesh->mesh == nullptr);
    assert(enemy.state.mesh->radius == 0.0f && enemy.state.mesh->current_radius == 16.0f);
    assert(enemy.state.mesh->color == 0x76543210u);
    assert(render_mesh_ctor_calls == 1 && render_mesh_dtor_calls == 1);

    // A negative radius also skips the factory. The old owner is still
    // retired first, and the new owner keeps the signed negative radius.
    set_packet(621, {bits(-3.0f),0x10203040u,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.mesh != nullptr && enemy.state.mesh->mesh == nullptr);
    assert(enemy.state.mesh->radius == -3.0f && enemy.state.mesh->color == 0x10203040u);
    assert(render_mesh_ctor_calls == 1 && render_mesh_dtor_calls == 1);

    // The native order publishes a new owner before float operand 0. A
    // throwing operand leaves that fresh, default-initialized owner published
    // and does not reach the integer color read or conditional RenderMesh.
    dispatch_operand_state = &enemy.state;
    mesh_owner_visible_during_float_read = false;
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_hook = &throw_during_mesh_float_read;
    set_packet(621, {bits(-101.0f),0x55667788u,0,0,0,0,0,0}, 1);
    bool mesh_float_threw = false;
    try { enemy.state.execute_opcode(); }
    catch (int value) { mesh_float_threw = value == 554; }
    dispatch_float_read_hook = nullptr;
    assert(mesh_float_threw && mesh_owner_visible_during_float_read);
    assert(dispatch_float_read_calls == 1 && dispatch_float_read_indices[0] == -101);
    assert(enemy.state.mesh != nullptr && enemy.state.mesh->mesh == nullptr);
    assert(enemy.state.mesh->radius == 0.0f && enemy.state.mesh->color == 0u);
    assert(render_mesh_ctor_calls == 1 && render_mesh_dtor_calls == 1);

    // A throwing integer color operand occurs after the radius write but
    // before the conditional RenderMesh allocation.
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_hook = &throw_during_integer_read;
    set_packet(621, {bits(7.25f),static_cast<std::uint32_t>(-101),0,0,0,0,0,0}, 2);
    bool mesh_integer_threw = false;
    try { enemy.state.execute_opcode(); }
    catch (int value) { mesh_integer_threw = value == 553; }
    dispatch_integer_read_hook = nullptr;
    assert(mesh_integer_threw);
    assert(dispatch_integer_read_calls == 1 && dispatch_integer_read_index == -101);
    assert(enemy.state.mesh != nullptr && enemy.state.mesh->mesh == nullptr);
    assert(enemy.state.mesh->radius == 7.25f && enemy.state.mesh->current_radius == 16.0f);
    assert(enemy.state.mesh->color == 0u);
    assert(render_mesh_ctor_calls == 1 && render_mesh_dtor_calls == 1);

    process_allocator->release_object(enemy.state.mesh);
    enemy.state.mesh = nullptr;
    assert(render_mesh_dtor_calls == 1);

    // Native opcode 620 updates the real queued record's vector_40, not
    // ShotMetadata. The ensure-only shared_shot selector must preserve an
    // already-shared metadata owner while the two VM float operands are read
    // and the original -990.0f sentinel selects the Z lane.
    enemy.state.queued.clear();
    auto& queued_record_620 = enemy.state.queued.emplace_front();
    auto metadata_owner_620 = std::make_shared<ShotMetadata>();
    queued_record_620.owner = metadata_owner_620;
    queued_record_620.vector_40 = {11.0f,22.0f,33.0f};
    auto* const metadata_pointer_620 = metadata_owner_620.get();
    assert(metadata_owner_620.use_count() == 2);
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {-990.0f,4.25f};
    dispatch_float_read_hook = &observe_float_read;
    set_packet(620, {0,bits(-101.0f),bits(-102.0f),0,0,0,0,0}, 6);
    assert(enemy.state.execute_opcode() == 0);
    dispatch_float_read_hook = nullptr;
    assert(dispatch_float_read_calls == 2);
    assert(dispatch_float_read_indices[0] == -101 && dispatch_float_read_indices[1] == -102);
    assert(queued_record_620.vector_40.x == -990.0f);
    assert(queued_record_620.vector_40.y == 4.25f);
    assert(queued_record_620.vector_40.z == 1.0f);
    assert(queued_record_620.owner.get() == metadata_pointer_620);
    assert(metadata_owner_620.use_count() == 2);

    // Values strictly below the native sentinel clear vector_40.z.
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {-991.0f,5.5f};
    dispatch_float_read_hook = &observe_float_read;
    set_packet(620, {0,bits(-101.0f),bits(-102.0f),0,0,0,0,0}, 6);
    assert(enemy.state.execute_opcode() == 0);
    dispatch_float_read_hook = nullptr;
    assert(queued_record_620.vector_40.x == -991.0f);
    assert(queued_record_620.vector_40.y == 5.5f);
    assert(queued_record_620.vector_40.z == 0.0f);
    assert(queued_record_620.owner.get() == metadata_pointer_620);
    assert(metadata_owner_620.use_count() == 2);

    // COMISS followed by JBE treats an unordered X comparison as the
    // threshold-selected path. Preserve that native NaN behavior explicitly.
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {
        std::numeric_limits<float>::quiet_NaN(),6.5f};
    dispatch_float_read_hook = &observe_float_read;
    set_packet(620, {0,bits(-101.0f),bits(-102.0f),0,0,0,0,0}, 6);
    assert(enemy.state.execute_opcode() == 0);
    dispatch_float_read_hook = nullptr;
    assert(std::isnan(queued_record_620.vector_40.x));
    assert(queued_record_620.vector_40.y == 6.5f);
    assert(queued_record_620.vector_40.z == 1.0f);
    assert(queued_record_620.owner.get() == metadata_pointer_620);
    assert(metadata_owner_620.use_count() == 2);

    // A second-operand exception occurs after the X write but before Y/Z.
    // The shared metadata owner is neither cloned nor replaced.
    queued_record_620.vector_40 = {31.0f,32.0f,33.0f};
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {123.0f,456.0f};
    dispatch_float_throw_at = 2;
    dispatch_float_read_hook = &throw_during_float_read;
    set_packet(620, {0,bits(-101.0f),bits(-102.0f),0,0,0,0,0}, 6);
    bool queued_vector_second_float_threw = false;
    try { enemy.state.execute_opcode(); }
    catch (int value) { queued_vector_second_float_threw = value == 554; }
    dispatch_float_read_hook = nullptr;
    dispatch_float_throw_at = 0;
    assert(queued_vector_second_float_threw);
    assert(dispatch_float_read_calls == 2);
    assert(dispatch_float_read_indices[0] == -101 && dispatch_float_read_indices[1] == -102);
    assert(queued_record_620.vector_40.x == 123.0f);
    assert(queued_record_620.vector_40.y == 32.0f);
    assert(queued_record_620.vector_40.z == 33.0f);
    assert(queued_record_620.owner.get() == metadata_pointer_620);
    assert(metadata_owner_620.use_count() == 2);
    enemy.state.queued.clear();
    metadata_owner_620.reset();

    // Native opcode 618 reads selector/direction/length first, then obtains
    // the shared queued record, constructs a temporary Vector3, computes the
    // polar XY pair and publishes only those two lanes. The existing Z lane
    // and shared metadata owner must remain untouched.
    enemy.state.queued.clear();
    auto& queued_record_618 = enemy.state.queued.emplace_front();
    auto metadata_owner_618 = std::make_shared<ShotMetadata>();
    queued_record_618.owner = metadata_owner_618;
    queued_record_618.vector_34 = {11.0f,22.0f,33.0f};
    queued_record_618.vector_40 = {44.0f,55.0f,66.0f};
    auto* const metadata_pointer_618 = metadata_owner_618.get();
    const float pi_half_618 = std::acos(-1.0f) * 0.5f;
    dispatch_integer_read_calls = 0;
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {pi_half_618,2.0f};
    dispatch_float_read_hook = &observe_float_read;
    dispatch_read_trace_count = 0;
    dispatch_read_kinds = {};
    dispatch_read_indices = {};
    dispatch_read_trace_enabled = true;
    set_packet(618, {0,bits(-101.0f),bits(-102.0f),0,0,0,0,0}, 6);
    assert(enemy.state.execute_opcode() == 0);
    dispatch_read_trace_enabled = false;
    dispatch_float_read_hook = nullptr;
    assert(dispatch_integer_read_calls == 0); // selector 0 is an immediate operand
    assert(dispatch_float_read_calls == 2);
    assert(dispatch_float_read_indices[0] == -101 && dispatch_float_read_indices[1] == -102);
    assert(dispatch_read_trace_count == 2);
    assert(dispatch_read_kinds[0] == 'f' && dispatch_read_indices[0] == -101);
    assert(dispatch_read_kinds[1] == 'f' && dispatch_read_indices[1] == -102);
    assert(std::fabs(queued_record_618.vector_34.x) < 0.00001f);
    assert(std::fabs(queued_record_618.vector_34.y - 2.0f) < 0.00001f);
    assert(queued_record_618.vector_34.z == 33.0f);
    assert(queued_record_618.vector_40.x == 44.0f &&
           queued_record_618.vector_40.y == 55.0f &&
           queued_record_618.vector_40.z == 66.0f);
    assert(queued_record_618.owner.get() == metadata_pointer_618);
    assert(metadata_owner_618.use_count() == 2);

    // Both VM float reads precede shared_shot. If the second operand throws,
    // the queue must remain empty and no metadata owner may be allocated.
    enemy.state.queued.clear();
    dispatch_integer_read_calls = 0;
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {pi_half_618,2.0f};
    dispatch_float_throw_at = 2;
    dispatch_float_read_hook = &throw_during_float_read;
    dispatch_read_trace_count = 0;
    dispatch_read_kinds = {};
    dispatch_read_indices = {};
    dispatch_read_trace_enabled = true;
    set_packet(618, {0,bits(-101.0f),bits(-102.0f),0,0,0,0,0}, 6);
    bool queued_polar_second_float_threw = false;
    try { enemy.state.execute_opcode(); }
    catch (int value) { queued_polar_second_float_threw = value == 554; }
    dispatch_read_trace_enabled = false;
    dispatch_float_read_hook = nullptr;
    dispatch_float_throw_at = 0;
    assert(queued_polar_second_float_threw);
    assert(dispatch_integer_read_calls == 0 && dispatch_float_read_calls == 2);
    assert(dispatch_read_trace_count == 2);
    assert(dispatch_read_kinds[0] == 'f' && dispatch_read_indices[0] == -101);
    assert(dispatch_read_kinds[1] == 'f' && dispatch_read_indices[1] == -102);
    assert(enemy.state.queued.empty());
    assert(metadata_owner_618.use_count() == 1);
    metadata_owner_618.reset();

    // Native opcode 619 writes ShotMetadata::field_00 (the radial offset
    // consumed by BulletEmitter/Laser creation). Its original order is
    // selector read, writable-shot COW, pair get<0>, pair get<1>, then the
    // single float read and metadata write. Use queue index one to exercise
    // the real forward-list selector as well as shared-owner cloning.
    enemy.state.queued.clear();
    auto& queued_record_619 = enemy.state.queued.emplace_front();
    enemy.state.queued.emplace_front(); // queued_record_619 is now index 1
    auto metadata_owner_619 = std::make_shared<ShotMetadata>();
    metadata_owner_619->field_00 = 1.25f;
    metadata_owner_619->field_14 = 2.5f;
    metadata_owner_619->field_24 = 0x12345678u;
    queued_record_619.owner = metadata_owner_619;
    queued_record_619.vector_34 = {11.0f,22.0f,33.0f};
    queued_record_619.vector_40 = {44.0f,55.0f,66.0f};
    auto* const original_metadata_619 = metadata_owner_619.get();
    assert(metadata_owner_619.use_count() == 2);
    dispatch_opcode619_record = &queued_record_619;
    dispatch_opcode619_original_metadata = original_metadata_619;
    dispatch_opcode619_cow_visible_before_float = false;
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_indices = {};
    dispatch_integer_read_scripted_values = {};
    dispatch_integer_read_scripted_values[0] = 1;
    dispatch_integer_read_scripted = true;
    dispatch_integer_throw_at = 0;
    dispatch_integer_read_hook = &observe_integer_read;
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {3.25f};
    dispatch_float_throw_at = 0;
    dispatch_float_read_hook = &observe_opcode619_cow_before_float;
    dispatch_read_trace_count = 0;
    dispatch_read_kinds = {};
    dispatch_read_indices = {};
    dispatch_read_trace_enabled = true;
    set_packet(619, {static_cast<std::uint32_t>(-101),bits(-102.0f),0,0,0,0,0,0}, 3);
    assert(enemy.state.execute_opcode() == 0);
    dispatch_read_trace_enabled = false;
    dispatch_integer_read_hook = nullptr;
    dispatch_integer_read_scripted = false;
    dispatch_float_read_hook = nullptr;
    assert(dispatch_integer_read_calls == 1 && dispatch_integer_read_indices[0] == -101);
    assert(dispatch_float_read_calls == 1 && dispatch_float_read_indices[0] == -102);
    assert(dispatch_read_trace_count == 2);
    assert(dispatch_read_kinds[0] == 'i' && dispatch_read_indices[0] == -101);
    assert(dispatch_read_kinds[1] == 'f' && dispatch_read_indices[1] == -102);
    assert(dispatch_opcode619_cow_visible_before_float);
    assert(queued_record_619.owner.get() != original_metadata_619);
    assert(queued_record_619.owner.use_count() == 1);
    assert(metadata_owner_619.get() == original_metadata_619 && metadata_owner_619.use_count() == 1);
    assert(metadata_owner_619->field_00 == 1.25f);
    assert(queued_record_619.owner->field_00 == 3.25f);
    assert(queued_record_619.owner->field_14 == 2.5f);
    assert(queued_record_619.owner->field_24 == 0x12345678u);
    assert(queued_record_619.vector_34.x == 11.0f &&
           queued_record_619.vector_34.y == 22.0f &&
           queued_record_619.vector_34.z == 33.0f);
    assert(queued_record_619.vector_40.x == 44.0f &&
           queued_record_619.vector_40.y == 55.0f &&
           queued_record_619.vector_40.z == 66.0f);
    dispatch_opcode619_record = nullptr;
    dispatch_opcode619_original_metadata = nullptr;
    enemy.state.queued.clear();
    metadata_owner_619.reset();

    // A throwing float read happens after writable_shot has cloned shared
    // metadata, but before field_00 is assigned. The clone itself is a
    // native-visible side effect and must not be rolled back by the throw.
    auto& queued_record_619_throw = enemy.state.queued.emplace_front();
    enemy.state.queued.emplace_front();
    auto metadata_owner_619_throw = std::make_shared<ShotMetadata>();
    metadata_owner_619_throw->field_00 = 7.5f;
    metadata_owner_619_throw->field_14 = 9.5f;
    queued_record_619_throw.owner = metadata_owner_619_throw;
    auto* const original_metadata_619_throw = metadata_owner_619_throw.get();
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_indices = {};
    dispatch_integer_read_scripted_values = {};
    dispatch_integer_read_scripted_values[0] = 1;
    dispatch_integer_read_scripted = true;
    dispatch_integer_throw_at = 0;
    dispatch_integer_read_hook = &observe_integer_read;
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {12.5f};
    dispatch_float_throw_at = 1;
    dispatch_float_read_hook = &throw_during_float_read;
    dispatch_read_trace_count = 0;
    dispatch_read_kinds = {};
    dispatch_read_indices = {};
    dispatch_read_trace_enabled = true;
    set_packet(619, {static_cast<std::uint32_t>(-101),bits(-102.0f),0,0,0,0,0,0}, 3);
    bool queued_metadata_float_threw = false;
    try { enemy.state.execute_opcode(); }
    catch (int value) { queued_metadata_float_threw = value == 554; }
    dispatch_read_trace_enabled = false;
    dispatch_integer_read_hook = nullptr;
    dispatch_integer_read_scripted = false;
    dispatch_float_read_hook = nullptr;
    dispatch_float_throw_at = 0;
    assert(queued_metadata_float_threw);
    assert(dispatch_integer_read_calls == 1 && dispatch_integer_read_indices[0] == -101);
    assert(dispatch_float_read_calls == 1 && dispatch_float_read_indices[0] == -102);
    assert(dispatch_read_trace_count == 2);
    assert(dispatch_read_kinds[0] == 'i' && dispatch_read_indices[0] == -101);
    assert(dispatch_read_kinds[1] == 'f' && dispatch_read_indices[1] == -102);
    assert(queued_record_619_throw.owner.get() != original_metadata_619_throw);
    assert(queued_record_619_throw.owner.use_count() == 1);
    assert(metadata_owner_619_throw.get() == original_metadata_619_throw);
    assert(metadata_owner_619_throw.use_count() == 1);
    assert(queued_record_619_throw.owner->field_00 == 7.5f);
    assert(metadata_owner_619_throw->field_00 == 7.5f);
    assert(queued_record_619_throw.owner->field_14 == 9.5f);
    enemy.state.queued.clear();
    metadata_owner_619_throw.reset();

    // Native opcode 633 decrements the selected queued record's +0x30 word
    // after writable-shot COW and both pair extractions. The x86 branch uses
    // unsigned wrap for SUB, then a signed post-decrement JGE test and a
    // second store of zero for negative results.
    auto run_opcode633_counter_case = [&](std::uint32_t initial, std::uint32_t expected) {
        enemy.state.queued.clear();
        auto& queued_record_633 = enemy.state.queued.emplace_front();
        enemy.state.queued.emplace_front(); // selected record is index 1
        auto metadata_owner_633 = std::make_shared<ShotMetadata>();
        metadata_owner_633->field_00 = 4.5f;
        metadata_owner_633->field_14 = 8.5f;
        queued_record_633.owner = metadata_owner_633;
        queued_record_633.field_30 = initial;
        auto* const original_metadata_633 = metadata_owner_633.get();
        assert(metadata_owner_633.use_count() == 2);
        dispatch_integer_read_calls = 0;
        dispatch_integer_read_indices = {};
        dispatch_integer_read_scripted_values = {};
        dispatch_integer_read_scripted_values[0] = 1;
        dispatch_integer_read_scripted = true;
        dispatch_integer_throw_at = 0;
        dispatch_integer_read_hook = &observe_integer_read;
        dispatch_float_read_calls = 0;
        dispatch_float_read_indices = {};
        dispatch_float_read_values = {};
        dispatch_float_read_hook = nullptr;
        dispatch_read_trace_count = 0;
        dispatch_read_kinds = {};
        dispatch_read_indices = {};
        dispatch_read_trace_enabled = true;
        set_packet(633, {static_cast<std::uint32_t>(-101),0,0,0,0,0,0,0}, 1);
        assert(enemy.state.execute_opcode() == 0);
        dispatch_read_trace_enabled = false;
        dispatch_integer_read_hook = nullptr;
        dispatch_integer_read_scripted = false;
        assert(dispatch_integer_read_calls == 1 && dispatch_integer_read_indices[0] == -101);
        assert(dispatch_float_read_calls == 0);
        assert(dispatch_read_trace_count == 1);
        assert(dispatch_read_kinds[0] == 'i' && dispatch_read_indices[0] == -101);
        assert(queued_record_633.field_30 == expected);
        assert(queued_record_633.owner.get() != original_metadata_633);
        assert(queued_record_633.owner.use_count() == 1);
        assert(metadata_owner_633.get() == original_metadata_633);
        assert(metadata_owner_633.use_count() == 1);
        assert(queued_record_633.owner->field_00 == 4.5f);
        assert(queued_record_633.owner->field_14 == 8.5f);
        assert(metadata_owner_633->field_00 == 4.5f);
        enemy.state.queued.clear();
        metadata_owner_633.reset();
    };
    run_opcode633_counter_case(2u, 1u);
    run_opcode633_counter_case(0u, 0u);
    run_opcode633_counter_case(0x80000000u, 0x7fffffffu);
    run_opcode633_counter_case(0x80000001u, 0u);

    // The selector operand precedes writable_shot. If it throws, neither the
    // COW clone nor the counter decrement may occur.
    enemy.state.queued.clear();
    auto& queued_record_633_throw = enemy.state.queued.emplace_front();
    enemy.state.queued.emplace_front();
    auto metadata_owner_633_throw = std::make_shared<ShotMetadata>();
    queued_record_633_throw.owner = metadata_owner_633_throw;
    queued_record_633_throw.field_30 = 5u;
    auto* const original_metadata_633_throw = metadata_owner_633_throw.get();
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_indices = {};
    dispatch_integer_read_scripted = false;
    dispatch_integer_throw_at = 0;
    dispatch_integer_read_hook = &throw_during_integer_read;
    dispatch_read_trace_count = 0;
    dispatch_read_kinds = {};
    dispatch_read_indices = {};
    dispatch_read_trace_enabled = true;
    set_packet(633, {static_cast<std::uint32_t>(-101),0,0,0,0,0,0,0}, 1);
    bool opcode633_selector_threw = false;
    try { enemy.state.execute_opcode(); }
    catch (int value) { opcode633_selector_threw = value == 553; }
    dispatch_read_trace_enabled = false;
    dispatch_integer_read_hook = nullptr;
    assert(opcode633_selector_threw);
    assert(dispatch_integer_read_calls == 1 && dispatch_integer_read_indices[0] == -101);
    assert(dispatch_read_trace_count == 1);
    assert(dispatch_read_kinds[0] == 'i' && dispatch_read_indices[0] == -101);
    assert(queued_record_633_throw.field_30 == 5u);
    assert(queued_record_633_throw.owner.get() == original_metadata_633_throw);
    assert(metadata_owner_633_throw.use_count() == 2);
    enemy.state.queued.clear();
    metadata_owner_633_throw.reset();

    // Native opcode 632 borrows the fourth trailing ECL payload word as a
    // BulletCommand::script pointer. Both indexes are read before writable
    // metadata COW; only then may PMR command growth and pointer publication
    // occur. The pointed-to bytes remain owned by this instruction packet.
    enemy.state.queued.clear();
    auto& queued_record_632 = enemy.state.queued.emplace_front();
    enemy.state.queued.emplace_front(); // selected record is index 1
    auto metadata_owner_632 = std::make_shared<ShotMetadata>();
    metadata_owner_632->commands.resize(1);
    metadata_owner_632->commands[0].flags = 0xaabbccdd;
    metadata_owner_632->commands[0].opcode = 0x11223344;
    metadata_owner_632->commands[0].operand_10 = 0x55667788;
    metadata_owner_632->commands[0].script = "original command script";
    queued_record_632.owner = metadata_owner_632;
    auto* const original_metadata_632 = metadata_owner_632.get();
    auto* const original_command_632 = &metadata_owner_632->commands[0];
    std::shared_ptr<ShotMetadata> shared_metadata_632 = metadata_owner_632;
    assert(metadata_owner_632.use_count() == 3);
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_indices = {};
    dispatch_integer_read_scripted_values = {};
    dispatch_integer_read_scripted_values[0] = 1;
    dispatch_integer_read_scripted_values[1] = 2;
    dispatch_integer_read_scripted = true;
    dispatch_integer_throw_at = 0;
    dispatch_integer_read_hook = &observe_integer_read;
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_hook = nullptr;
    dispatch_read_trace_count = 0;
    dispatch_read_kinds = {};
    dispatch_read_indices = {};
    dispatch_read_trace_enabled = true;
    set_packet(632, {static_cast<std::uint32_t>(-101),
                     static_cast<std::uint32_t>(-102),0,0,0,0,0,0}, 0x0fffu);
    auto* const instruction_632 = reinterpret_cast<EclInstruction*>(packet.data() + 16);
    auto* const borrowed_script_632 = reinterpret_cast<const char*>(instruction_632) + 0x1c;
    std::memcpy(const_cast<char*>(borrowed_script_632), "borrowed-script", 16);
    assert(enemy.state.execute_opcode() == 0);
    dispatch_read_trace_enabled = false;
    dispatch_integer_read_hook = nullptr;
    dispatch_integer_read_scripted = false;
    assert(dispatch_integer_read_calls == 2);
    assert(dispatch_integer_read_indices[0] == -101 && dispatch_integer_read_indices[1] == -102);
    assert(dispatch_float_read_calls == 0);
    assert(dispatch_read_trace_count == 2);
    assert(dispatch_read_kinds[0] == 'i' && dispatch_read_indices[0] == -101);
    assert(dispatch_read_kinds[1] == 'i' && dispatch_read_indices[1] == -102);
    assert(queued_record_632.owner.get() != original_metadata_632);
    assert(queued_record_632.owner.use_count() == 1);
    assert(metadata_owner_632.get() == original_metadata_632);
    assert(metadata_owner_632.use_count() == 2);
    assert(metadata_owner_632->commands.size() == 1);
    assert(metadata_owner_632->commands[0].script == original_command_632->script);
    assert(metadata_owner_632->commands[0].flags == 0xaabbccddu);
    assert(metadata_owner_632->commands[0].opcode == 0x11223344u);
    assert(queued_record_632.owner->commands.size() == 3);
    assert(queued_record_632.owner->commands[0].script == original_command_632->script);
    assert(queued_record_632.owner->commands[0].flags == 0xaabbccddu);
    assert(queued_record_632.owner->commands[0].opcode == 0x11223344u);
    assert(queued_record_632.owner->commands[0].operand_10 == 0x55667788);
    assert(queued_record_632.owner->commands[2].script == borrowed_script_632);
    assert(std::strcmp(queued_record_632.owner->commands[2].script, "borrowed-script") == 0);
    assert(queued_record_632.owner->commands[2].flags == 0);
    assert(queued_record_632.owner->commands[2].opcode == 0);
    enemy.state.queued.clear();
    shared_metadata_632.reset();
    metadata_owner_632.reset();

    // If the second index read throws, COW, PMR growth and script publication
    // must not have started: the native branch reads both operands first.
    enemy.state.queued.clear();
    auto& queued_record_632_throw = enemy.state.queued.emplace_front();
    enemy.state.queued.emplace_front();
    auto metadata_owner_632_throw = std::make_shared<ShotMetadata>();
    metadata_owner_632_throw->commands.resize(1);
    metadata_owner_632_throw->commands[0].script = "before throw";
    queued_record_632_throw.owner = metadata_owner_632_throw;
    auto* const original_metadata_632_throw = metadata_owner_632_throw.get();
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_indices = {};
    dispatch_integer_read_scripted = false;
    dispatch_integer_throw_at = 0;
    dispatch_integer_read_hook = &throw_during_second_integer_read;
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_hook = nullptr;
    dispatch_read_trace_count = 0;
    dispatch_read_kinds = {};
    dispatch_read_indices = {};
    dispatch_read_trace_enabled = true;
    set_packet(632, {static_cast<std::uint32_t>(-101),
                     static_cast<std::uint32_t>(-102),0,0,0,0,0,0}, 0x0fffu);
    bool opcode632_second_index_threw = false;
    try { enemy.state.execute_opcode(); }
    catch (int value) { opcode632_second_index_threw = value == 557; }
    dispatch_read_trace_enabled = false;
    dispatch_integer_read_hook = nullptr;
    assert(opcode632_second_index_threw);
    assert(dispatch_integer_read_calls == 2);
    assert(dispatch_integer_read_indices[0] == -101 && dispatch_integer_read_indices[1] == -102);
    assert(dispatch_read_trace_count == 2);
    assert(dispatch_read_kinds[0] == 'i' && dispatch_read_indices[0] == -101);
    assert(dispatch_read_kinds[1] == 'i' && dispatch_read_indices[1] == -102);
    assert(queued_record_632_throw.owner.get() == original_metadata_632_throw);
    assert(metadata_owner_632_throw.use_count() == 2);
    assert(metadata_owner_632_throw->commands.size() == 1);
    assert(std::strcmp(metadata_owner_632_throw->commands[0].script, "before throw") == 0);
    enemy.state.queued.clear();
    metadata_owner_632_throw.reset();

    // Native opcode 617 computes atan2(player.y-target_y, player.x-target_x)
    // and writes float destination zero. It deliberately obtains Context's
    // Player twice: the first position reference survives operand 1, while a
    // Context retarget during that read supplies the second Player for Y.
    dispatch_test_player->position = {10.0f,20.0f,0.0f};
    alternate_player->position = {100.0f,200.0f,0.0f};
    enemy.state.context = &context;
    enemy.main.stack.reset();
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {2.0f,50.0f};
    dispatch_float_read_hook = &retarget_context_player_during_first_float_read;
    dispatch_read_trace_count = 0;
    dispatch_read_kinds = {};
    dispatch_read_indices = {};
    dispatch_read_trace_enabled = true;
    set_packet(617, {bits(0.0f),bits(-101.0f),bits(-102.0f),0,0,0,0,0}, 7);
    assert(enemy.state.execute_opcode() == 0);
    dispatch_read_trace_enabled = false;
    dispatch_float_read_hook = nullptr;
    enemy.state.context = &context;
    assert(dispatch_float_read_calls == 2);
    assert(dispatch_float_read_indices[0] == -101 && dispatch_float_read_indices[1] == -102);
    assert(dispatch_read_trace_count == 2);
    assert(dispatch_read_kinds[0] == 'f' && dispatch_read_kinds[1] == 'f');
    assert(dispatch_read_indices[0] == -101 && dispatch_read_indices[1] == -102);
    std::uint32_t player_angle_bits_617 = enemy.main.stack.local(0);
    float player_angle_617 = 0.0f;
    std::memcpy(&player_angle_617, &player_angle_bits_617, sizeof(player_angle_617));
    const float expected_player_angle_617 = std::atan2(150.0f,8.0f);
    assert(std::fabs(player_angle_617 - expected_player_angle_617) < 0.00001f);

    // Unlike Player::direction_to, native opcode 617 calls atan2 directly:
    // the coincident point therefore writes atan2(0,0) == 0, not pi/2.
    dispatch_test_player->position = {7.0f,9.0f,0.0f};
    enemy.main.stack.reset();
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {7.0f,9.0f};
    dispatch_float_read_hook = &observe_float_read;
    set_packet(617, {bits(0.0f),bits(-101.0f),bits(-102.0f),0,0,0,0,0}, 7);
    assert(enemy.state.execute_opcode() == 0);
    dispatch_float_read_hook = nullptr;
    std::uint32_t zero_vector_angle_bits_617 = enemy.main.stack.local(0);
    float zero_vector_angle_617 = 1.0f;
    std::memcpy(&zero_vector_angle_617, &zero_vector_angle_bits_617, sizeof(zero_vector_angle_617));
    assert(zero_vector_angle_617 == 0.0f);

    // The second operand exception occurs after both position references but
    // before atan2/destination publication; the previous local remains intact.
    enemy.main.stack.reset();
    enemy.main.stack.local(0) = bits(123.0f);
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {2.0f,50.0f};
    dispatch_float_throw_at = 2;
    dispatch_float_read_hook = &throw_during_float_read;
    dispatch_read_trace_count = 0;
    dispatch_read_kinds = {};
    dispatch_read_indices = {};
    dispatch_read_trace_enabled = true;
    set_packet(617, {bits(0.0f),bits(-101.0f),bits(-102.0f),0,0,0,0,0}, 7);
    bool player_angle_second_operand_threw = false;
    try { enemy.state.execute_opcode(); }
    catch (int value) { player_angle_second_operand_threw = value == 554; }
    dispatch_read_trace_enabled = false;
    dispatch_float_read_hook = nullptr;
    dispatch_float_throw_at = 0;
    assert(player_angle_second_operand_threw);
    assert(dispatch_float_read_calls == 2);
    assert(dispatch_read_trace_count == 2);
    assert(dispatch_read_kinds[0] == 'f' && dispatch_read_kinds[1] == 'f');
    assert(enemy.main.stack.local(0) == bits(123.0f));
    enemy.state.context = &context;

    // Native opcode 616 composes the complete Bullet and Laser radial
    // cancellation Bosses. The radius is read before the first Context lookup.
    // A Bullet::cancel callback retargets Context and mutates Enemy position:
    // the in-flight Bullet boss keeps its cached controller and live center
    // reference, while the following Laser pass re-reads both Context and
    // position and therefore observes the new values.
    assert(dispatch_test_bullets->active.front() == nullptr);
    assert(dispatch_test_bullets_alternate->active.front() == nullptr);
    assert(dispatch_test_lasers->active.front() == nullptr);
    assert(dispatch_test_lasers_alternate->active.front() == nullptr);
    Bullet bullet_at_initial_center;
    Bullet bullet_at_retargeted_center;
    Bullet bullet_left_at_old_center;
    Bullet bullet_wrong_state;
    bullet_at_initial_center.state = 1;
    bullet_at_initial_center.position = {10.0f,20.0f,0.0f};
    bullet_at_initial_center.size.x = 2.0f;
    bullet_at_retargeted_center.state = 2;
    bullet_at_retargeted_center.position = {30.0f,40.0f,0.0f};
    bullet_at_retargeted_center.size.x = 2.0f;
    bullet_left_at_old_center.state = 1;
    bullet_left_at_old_center.position = {10.0f,20.0f,0.0f};
    bullet_left_at_old_center.size.x = 2.0f;
    bullet_wrong_state.state = 3;
    bullet_wrong_state.position = {30.0f,40.0f,0.0f};
    bullet_wrong_state.size.x = 2.0f;
    dispatch_test_bullets_alternate->active.append(&bullet_at_initial_center.link);
    dispatch_test_bullets_alternate->active.append(&bullet_at_retargeted_center.link);
    dispatch_test_bullets_alternate->active.append(&bullet_left_at_old_center.link);
    dispatch_test_bullets_alternate->active.append(&bullet_wrong_state.link);

    DispatchTestLaser laser_state_zero;
    DispatchTestLaser laser_state_one;
    DispatchTestLaser laser_state_two;
    DispatchTestLaser laser_wrong_context;
    laser_state_zero.state = 0;
    laser_state_zero.circle_result = 2;
    laser_state_one.state = 1;
    laser_state_one.circle_result = 100;
    laser_state_two.state = 2;
    laser_state_two.circle_result = 3;
    laser_wrong_context.state = 0;
    laser_wrong_context.circle_result = 50;
    laser_state_zero.link.initialize(&laser_state_zero);
    laser_state_one.link.initialize(&laser_state_one);
    laser_state_two.link.initialize(&laser_state_two);
    laser_wrong_context.link.initialize(&laser_wrong_context);
    dispatch_test_lasers->active.append(&laser_state_zero.link);
    dispatch_test_lasers->active.append(&laser_state_one.link);
    dispatch_test_lasers->active.append(&laser_state_two.link);
    dispatch_test_lasers_alternate->active.append(&laser_wrong_context.link);

    dispatch_test_bullets->cancel_counter = 0;
    dispatch_test_bullets_alternate->cancel_counter = 0;
    bullet_cancel_calls = 0;
    bullet_cancel_mode = -1;
    dispatch_test_lasers->cancel_position = {-1.0f,-2.0f,-3.0f};
    dispatch_test_lasers_alternate->cancel_position = {-4.0f,-5.0f,-6.0f};
    enemy.state.context = &context;
    enemy.state.motion_110.position = {10.0f,20.0f,0.0f};
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {5.0f};
    dispatch_float_read_hook = &retarget_context_player_during_first_float_read;
    dispatch_bullet_cancel_hook = &retarget_to_original_and_move_enemy_during_bullet_cancel;
    dispatch_read_trace_count = 0;
    dispatch_read_kinds = {};
    dispatch_read_indices = {};
    dispatch_read_trace_enabled = true;
    set_packet(616, {bits(-101.0f),0,0,0,0,0,0,0}, 1);
    assert(enemy.state.execute_opcode() == 0);
    dispatch_read_trace_enabled = false;
    dispatch_float_read_hook = nullptr;
    dispatch_bullet_cancel_hook = nullptr;
    assert(dispatch_float_read_calls == 1 && dispatch_float_read_indices[0] == -101);
    assert(dispatch_read_trace_count == 1 && dispatch_read_kinds[0] == 'f');
    assert(dispatch_read_indices[0] == -101);
    assert(enemy.state.context == &context);
    assert(enemy.state.motion_110.position.x == 30.0f && enemy.state.motion_110.position.y == 40.0f && enemy.state.motion_110.position.z == 0.0f);

    // The BulletController receiver was resolved from the alternate Context
    // after operand zero and remains cached across the first Bullet callback.
    // Its center is a live reference: the second Bullet follows the callback's
    // position change, while a later Bullet at the old center is now outside.
    assert(dispatch_test_bullets->cancel_counter == 0);
    assert(dispatch_test_bullets_alternate->cancel_counter == 2);
    assert(bullet_cancel_calls == 2 && bullet_cancel_mode == 0);
    assert(bullet_at_initial_center.state == 4);
    assert(bullet_at_retargeted_center.state == 4);
    assert(bullet_left_at_old_center.state == 1);
    assert(bullet_wrong_state.state == 3);

    // The LaserController receiver and position are independently re-read
    // after Bullet cancellation, so the restored original Context and new
    // Enemy position are used. Native arguments are mode 0 / argument 1.
    assert(dispatch_test_lasers->cancel_position.x == 30.0f && dispatch_test_lasers->cancel_position.y == 40.0f && dispatch_test_lasers->cancel_position.z == 0.0f);
    assert(dispatch_test_lasers_alternate->cancel_position.x == -4.0f && dispatch_test_lasers_alternate->cancel_position.y == -5.0f && dispatch_test_lasers_alternate->cancel_position.z == -6.0f);
    assert(laser_state_zero.circle_calls == 1 && laser_state_one.circle_calls == 0);
    assert(laser_state_two.circle_calls == 1 && laser_wrong_context.circle_calls == 0);
    assert(laser_state_zero.circle_center.x == 30.0f && laser_state_zero.circle_center.y == 40.0f && laser_state_zero.circle_center.z == 0.0f);
    assert(laser_state_two.circle_center.x == 30.0f && laser_state_two.circle_center.y == 40.0f && laser_state_two.circle_center.z == 0.0f);
    assert(laser_state_zero.circle_radius == 5.0f && laser_state_two.circle_radius == 5.0f);
    assert(laser_state_zero.circle_mode == 0 && laser_state_zero.circle_argument == 1);
    assert(laser_state_two.circle_mode == 0 && laser_state_two.circle_argument == 1);

    // A radius read exception occurs before either Context/controller lookup,
    // so neither cancellation Boss nor either controller counter may change.
    const auto bullet_cancel_calls_before_616_throw = bullet_cancel_calls;
    const auto bullet_counter_before_616_throw = dispatch_test_bullets_alternate->cancel_counter;
    const auto laser_zero_calls_before_616_throw = laser_state_zero.circle_calls;
    const auto laser_two_calls_before_616_throw = laser_state_two.circle_calls;
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_throw_at = 1;
    dispatch_float_read_hook = &throw_during_float_read;
    dispatch_read_trace_count = 0;
    dispatch_read_kinds = {};
    dispatch_read_indices = {};
    dispatch_read_trace_enabled = true;
    set_packet(616, {bits(-101.0f),0,0,0,0,0,0,0}, 1);
    bool opcode616_radius_threw = false;
    try { enemy.state.execute_opcode(); }
    catch (int value) { opcode616_radius_threw = value == 554; }
    dispatch_read_trace_enabled = false;
    dispatch_float_read_hook = nullptr;
    dispatch_float_throw_at = 0;
    assert(opcode616_radius_threw);
    assert(dispatch_float_read_calls == 1 && dispatch_float_read_indices[0] == -101);
    assert(dispatch_read_trace_count == 1 && dispatch_read_kinds[0] == 'f' && dispatch_read_indices[0] == -101);
    assert(bullet_cancel_calls == bullet_cancel_calls_before_616_throw);
    assert(dispatch_test_bullets_alternate->cancel_counter == bullet_counter_before_616_throw);
    assert(laser_state_zero.circle_calls == laser_zero_calls_before_616_throw);
    assert(laser_state_two.circle_calls == laser_two_calls_before_616_throw);

    dispatch_test_bullets_alternate->active.remove(&bullet_at_initial_center.link);
    dispatch_test_bullets_alternate->active.remove(&bullet_at_retargeted_center.link);
    dispatch_test_bullets_alternate->active.remove(&bullet_left_at_old_center.link);
    dispatch_test_bullets_alternate->active.remove(&bullet_wrong_state.link);
    dispatch_test_lasers->active.remove(&laser_state_zero.link);
    dispatch_test_lasers->active.remove(&laser_state_one.link);
    dispatch_test_lasers->active.remove(&laser_state_two.link);
    dispatch_test_lasers_alternate->active.remove(&laser_wrong_context.link);
    enemy.state.context = &context;

    // Native opcodes 627/628 compose the real 401B capped Bullet radial
    // cancellation Boss and the 288B Laser radial cancellation Boss. Both
    // branches use the same radius, controller re-lookup and live-position
    // sequence; the Bullet call has mode 0, maximum 0x1869f, effects 0.
    auto run_limited_radial_cancel_case = [&](std::int32_t opcode) {
        assert(dispatch_test_bullets->active.front() == nullptr);
        assert(dispatch_test_bullets_alternate->active.front() == nullptr);
        assert(dispatch_test_lasers->active.front() == nullptr);
        assert(dispatch_test_lasers_alternate->active.front() == nullptr);
        Bullet limited_first;
        Bullet limited_second;
        Bullet limited_old_center;
        Bullet limited_field_excluded;
        Bullet limited_state_excluded;
        limited_first.state = 1;
        limited_first.position = {10.0f,20.0f,0.0f};
        limited_first.size.x = 2.0f;
        limited_first.flags.fields.effect_mode = 3;
        limited_second.state = 2;
        limited_second.position = {30.0f,40.0f,0.0f};
        limited_second.size.x = 2.0f;
        limited_second.flags.fields.effect_mode = 2;
        limited_old_center.state = 1;
        limited_old_center.position = {10.0f,20.0f,0.0f};
        limited_old_center.size.x = 2.0f;
        limited_field_excluded.state = 1;
        limited_field_excluded.position = {30.0f,40.0f,0.0f};
        limited_field_excluded.size.x = 2.0f;
        limited_field_excluded.field_18 = 1;
        limited_state_excluded.state = 3;
        limited_state_excluded.position = {30.0f,40.0f,0.0f};
        limited_state_excluded.size.x = 2.0f;
        dispatch_test_bullets_alternate->active.append(&limited_first.link);
        dispatch_test_bullets_alternate->active.append(&limited_second.link);
        dispatch_test_bullets_alternate->active.append(&limited_old_center.link);
        dispatch_test_bullets_alternate->active.append(&limited_field_excluded.link);
        dispatch_test_bullets_alternate->active.append(&limited_state_excluded.link);

        DispatchTestLaser limited_laser_zero;
        DispatchTestLaser limited_laser_one;
        DispatchTestLaser limited_laser_two;
        DispatchTestLaser limited_laser_wrong_context;
        limited_laser_zero.state = 0;
        limited_laser_zero.circle_result = 2;
        limited_laser_one.state = 1;
        limited_laser_one.circle_result = 100;
        limited_laser_two.state = 2;
        limited_laser_two.circle_result = 3;
        limited_laser_wrong_context.state = 0;
        limited_laser_wrong_context.circle_result = 50;
        limited_laser_zero.link.initialize(&limited_laser_zero);
        limited_laser_one.link.initialize(&limited_laser_one);
        limited_laser_two.link.initialize(&limited_laser_two);
        limited_laser_wrong_context.link.initialize(&limited_laser_wrong_context);
        dispatch_test_lasers->active.append(&limited_laser_zero.link);
        dispatch_test_lasers->active.append(&limited_laser_one.link);
        dispatch_test_lasers->active.append(&limited_laser_two.link);
        dispatch_test_lasers_alternate->active.append(&limited_laser_wrong_context.link);

        dispatch_test_bullets->cancel_counter = 0;
        dispatch_test_bullets_alternate->cancel_counter = 0;
        bullet_cancel_calls = 0;
        bullet_cancel_mode = -1;
        dispatch_test_lasers->cancel_position = {-1.0f,-2.0f,-3.0f};
        dispatch_test_lasers_alternate->cancel_position = {-4.0f,-5.0f,-6.0f};
        context.primary_owner = dispatch_test_bullets;
        alternate_context.primary_owner = dispatch_test_bullets_alternate;
        context.object_14 = dispatch_test_lasers;
        alternate_context.object_14 = dispatch_test_lasers_alternate;
        enemy.state.context = &context;
        enemy.state.motion_110.position = {10.0f,20.0f,0.0f};
        dispatch_operand_original_context = &context;
        dispatch_operand_alternate_context = &alternate_context;
        dispatch_operand_state = &enemy.state;
        dispatch_float_read_calls = 0;
        dispatch_float_read_indices = {};
        dispatch_float_read_values = {5.0f};
        dispatch_float_throw_at = 0;
        dispatch_float_read_hook = &retarget_context_player_during_first_float_read;
        dispatch_bullet_cancel_hook = &retarget_to_original_and_move_enemy_during_bullet_cancel;
        dispatch_read_trace_count = 0;
        dispatch_read_kinds = {};
        dispatch_read_indices = {};
        dispatch_read_trace_enabled = true;
        set_packet(opcode, {bits(-101.0f),0,0,0,0,0,0,0}, 1);
        assert(enemy.state.execute_opcode() == 0);
        dispatch_read_trace_enabled = false;
        dispatch_float_read_hook = nullptr;
        dispatch_bullet_cancel_hook = nullptr;
        assert(dispatch_float_read_calls == 1 && dispatch_float_read_indices[0] == -101);
        assert(dispatch_read_trace_count == 1);
        assert(dispatch_read_kinds[0] == 'f' && dispatch_read_indices[0] == -101);
        assert(enemy.state.context == &context);
        assert(enemy.state.motion_110.position.x == 30.0f &&
               enemy.state.motion_110.position.y == 40.0f &&
               enemy.state.motion_110.position.z == 0.0f);
        assert(dispatch_test_bullets->cancel_counter == 0);
        assert(dispatch_test_bullets_alternate->cancel_counter == 2);
        assert(bullet_cancel_calls == 2 && bullet_cancel_mode == 0);
        assert(limited_first.state == 4 && limited_second.state == 4);
        assert(limited_old_center.state == 1);
        assert(limited_field_excluded.state == 1 && limited_field_excluded.field_18 == 1);
        assert(limited_state_excluded.state == 3);
        assert(limited_first.flags.fields.effect_mode == 0);
        assert(limited_second.flags.fields.effect_mode == 0);
        assert(dispatch_test_lasers->cancel_position.x == 30.0f &&
               dispatch_test_lasers->cancel_position.y == 40.0f &&
               dispatch_test_lasers->cancel_position.z == 0.0f);
        assert(dispatch_test_lasers_alternate->cancel_position.x == -4.0f &&
               dispatch_test_lasers_alternate->cancel_position.y == -5.0f &&
               dispatch_test_lasers_alternate->cancel_position.z == -6.0f);
        assert(limited_laser_zero.circle_calls == 1);
        assert(limited_laser_one.circle_calls == 0);
        assert(limited_laser_two.circle_calls == 1);
        assert(limited_laser_wrong_context.circle_calls == 0);
        assert(limited_laser_zero.circle_radius == 5.0f &&
               limited_laser_two.circle_radius == 5.0f);
        assert(limited_laser_zero.circle_mode == 0 &&
               limited_laser_zero.circle_argument == 1);
        assert(limited_laser_two.circle_mode == 0 &&
               limited_laser_two.circle_argument == 1);

        dispatch_test_bullets_alternate->active.remove(&limited_first.link);
        dispatch_test_bullets_alternate->active.remove(&limited_second.link);
        dispatch_test_bullets_alternate->active.remove(&limited_old_center.link);
        dispatch_test_bullets_alternate->active.remove(&limited_field_excluded.link);
        dispatch_test_bullets_alternate->active.remove(&limited_state_excluded.link);
        dispatch_test_lasers->active.remove(&limited_laser_zero.link);
        dispatch_test_lasers->active.remove(&limited_laser_one.link);
        dispatch_test_lasers->active.remove(&limited_laser_two.link);
        dispatch_test_lasers_alternate->active.remove(&limited_laser_wrong_context.link);
        enemy.state.context = &context;
    };
    run_limited_radial_cancel_case(627);
    run_limited_radial_cancel_case(628);

    // Both capped-cancellation opcodes read the radius before looking up any
    // Context owner. A throwing radius leaves both Bullet and Laser lists,
    // controller counters and cancel positions untouched.
    {
        Bullet untouched_limited_bullet;
        untouched_limited_bullet.state = 1;
        untouched_limited_bullet.position = {10.0f,20.0f,0.0f};
        untouched_limited_bullet.size.x = 2.0f;
        DispatchTestLaser untouched_limited_laser;
        untouched_limited_laser.state = 0;
        untouched_limited_laser.link.initialize(&untouched_limited_laser);
        dispatch_test_bullets->active.append(&untouched_limited_bullet.link);
        dispatch_test_lasers->active.append(&untouched_limited_laser.link);
        dispatch_test_bullets->cancel_counter = 0;
        dispatch_test_lasers->cancel_position = {-1.0f,-2.0f,-3.0f};
        bullet_cancel_calls = 0;
        dispatch_float_read_calls = 0;
        dispatch_float_read_indices = {};
        dispatch_float_throw_at = 1;
        dispatch_float_read_hook = &throw_during_float_read;
        dispatch_read_trace_count = 0;
        dispatch_read_kinds = {};
        dispatch_read_indices = {};
        dispatch_read_trace_enabled = true;
        set_packet(628, {bits(-101.0f),0,0,0,0,0,0,0}, 1);
        bool opcode628_radius_threw = false;
        try { enemy.state.execute_opcode(); }
        catch (int value) { opcode628_radius_threw = value == 554; }
        dispatch_read_trace_enabled = false;
        dispatch_float_read_hook = nullptr;
        dispatch_float_throw_at = 0;
        assert(opcode628_radius_threw);
        assert(dispatch_float_read_calls == 1 && dispatch_float_read_indices[0] == -101);
        assert(dispatch_read_trace_count == 1);
        assert(dispatch_read_kinds[0] == 'f' && dispatch_read_indices[0] == -101);
        assert(bullet_cancel_calls == 0 && dispatch_test_bullets->cancel_counter == 0);
        assert(untouched_limited_bullet.state == 1);
        assert(untouched_limited_laser.circle_calls == 0);
        assert(dispatch_test_lasers->cancel_position.x == -1.0f &&
               dispatch_test_lasers->cancel_position.y == -2.0f &&
               dispatch_test_lasers->cancel_position.z == -3.0f);
        dispatch_test_bullets->active.remove(&untouched_limited_bullet.link);
        dispatch_test_lasers->active.remove(&untouched_limited_laser.link);
    }

    // Native opcode 712 reads both dimensions before resolving animation
    // link zero, then obtains the live Context BulletController, rotation and
    // Enemy position before calling the complete 707B cancellation Boss.
    // The rotated geometry distinguishes the animation's Z angle from an
    // axis-aligned rectangle, while state/field gates exercise the real list.
    enemy.state.animations.clear();
    enemy.state.animations.emplace_back();
    enemy.state.animations[0].handle.value = dispatch_test_animation_handle;
    enemy.state.motion_110.position = {100.0f,100.0f,0.0f};
    Bullet rotated_inside;
    Bullet rotated_inside_state2;
    Bullet axis_outside;
    Bullet inactive_state;
    Bullet excluded_field;
    rotated_inside.state = 1;
    rotated_inside.field_18 = 0;
    rotated_inside.position = {100.0f,108.0f,0.0f};
    rotated_inside.size.x = 0.5f;
    rotated_inside.scale = 1.0f;
    rotated_inside.flags.fields.effect_mode = 3;
    rotated_inside_state2.state = 2;
    rotated_inside_state2.field_18 = 0;
    rotated_inside_state2.position = {100.0f,106.0f,0.0f};
    rotated_inside_state2.size.x = 0.5f;
    rotated_inside_state2.scale = 1.0f;
    rotated_inside_state2.flags.fields.effect_mode = 2;
    axis_outside.state = 1;
    axis_outside.field_18 = 0;
    axis_outside.position = {108.0f,100.0f,0.0f};
    axis_outside.size.x = 0.5f;
    axis_outside.scale = 1.0f;
    axis_outside.flags.fields.effect_mode = 1;
    inactive_state.state = 3;
    inactive_state.field_18 = 0;
    inactive_state.position = {100.0f,100.0f,0.0f};
    inactive_state.size.x = 0.5f;
    inactive_state.scale = 1.0f;
    inactive_state.flags.fields.effect_mode = 2;
    excluded_field.state = 1;
    excluded_field.field_18 = 1;
    excluded_field.position = {100.0f,100.0f,0.0f};
    excluded_field.size.x = 0.5f;
    excluded_field.scale = 1.0f;
    excluded_field.flags.fields.effect_mode = 3;
    dispatch_test_bullets->active.append(&rotated_inside.link);
    dispatch_test_bullets->active.append(&rotated_inside_state2.link);
    dispatch_test_bullets->active.append(&axis_outside.link);
    dispatch_test_bullets->active.append(&inactive_state.link);
    dispatch_test_bullets->active.append(&excluded_field.link);
    const auto cancel_counter_before_712 = dispatch_test_bullets->cancel_counter;
    animation_pool_resolve_calls = 0;
    bullet_cancel_calls = 0;
    bullet_cancel_mode = -1;
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {20.0f,4.0f};
    dispatch_float_read_hook = &observe_float_read;
    set_packet(712, {bits(-101.0f),bits(-102.0f),0,0,0,0,0,0}, 3);
    assert(enemy.state.execute_opcode() == 0);
    dispatch_float_read_hook = nullptr;
    assert(dispatch_float_read_calls == 2);
    assert(dispatch_float_read_indices[0] == -101 && dispatch_float_read_indices[1] == -102);
    assert(animation_pool_resolve_calls == 1);
    assert(animation_pool_resolve_last_handle == dispatch_test_animation_handle);
    assert(enemy.state.animations[0].handle.value == dispatch_test_animation_handle);
    assert(bullet_cancel_calls == 2 && bullet_cancel_mode == 1);
    assert(dispatch_test_bullets->cancel_counter == cancel_counter_before_712 + 2);
    assert(rotated_inside.state == 4 && rotated_inside_state2.state == 4);
    assert(axis_outside.state == 1 && inactive_state.state == 3 && excluded_field.state == 1);
    assert(rotated_inside.flags.fields.effect_mode == 0);
    assert(rotated_inside_state2.flags.fields.effect_mode == 0);
    assert(axis_outside.flags.fields.effect_mode == 1);
    assert(inactive_state.flags.fields.effect_mode == 2);
    assert(excluded_field.flags.fields.effect_mode == 3);
    rotated_inside.link.detach();
    rotated_inside_state2.link.detach();
    axis_outside.link.detach();
    inactive_state.link.detach();
    excluded_field.link.detach();

    // If the second VM dimension read throws, the animation handle lookup and
    // the 707B controller Boss are not entered. This pins the two-operand
    // prefix as an observable native exception boundary.
    animation_pool_resolve_calls = 0;
    bullet_cancel_calls = 0;
    const auto cancel_counter_before_712_throw = dispatch_test_bullets->cancel_counter;
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {20.0f,4.0f};
    dispatch_float_throw_at = 2;
    dispatch_float_read_hook = &throw_during_float_read;
    set_packet(712, {bits(-101.0f),bits(-102.0f),0,0,0,0,0,0}, 3);
    bool bullet_cancel_dimension_threw = false;
    try { enemy.state.execute_opcode(); }
    catch (int value) { bullet_cancel_dimension_threw = value == 554; }
    dispatch_float_read_hook = nullptr;
    dispatch_float_throw_at = 0;
    assert(bullet_cancel_dimension_threw);
    assert(dispatch_float_read_calls == 2);
    assert(dispatch_float_read_indices[0] == -101 && dispatch_float_read_indices[1] == -102);
    assert(animation_pool_resolve_calls == 0 && bullet_cancel_calls == 0);
    assert(dispatch_test_bullets->cancel_counter == cancel_counter_before_712_throw);

    // The user rectangle can intersect a bullet outside the fixed 384x448
    // gameplay viewport. The second original geometry test must reject it.
    Bullet outside_viewport;
    outside_viewport.state = 1;
    outside_viewport.field_18 = 0;
    outside_viewport.position = {100.0f,-2.0f,0.0f};
    outside_viewport.size.x = 0.5f;
    outside_viewport.scale = 1.0f;
    outside_viewport.flags.fields.effect_mode = 2;
    dispatch_test_bullets->active.append(&outside_viewport.link);
    enemy.state.motion_110.position = {100.0f,5.0f,0.0f};
    animation_pool_resolve_calls = 0;
    bullet_cancel_calls = 0;
    set_packet(712, {bits(20.0f),bits(4.0f),0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(animation_pool_resolve_calls == 1);
    assert(bullet_cancel_calls == 0);
    assert(dispatch_test_bullets->cancel_counter == cancel_counter_before_712_throw);
    assert(outside_viewport.state == 1);
    assert(outside_viewport.flags.fields.effect_mode == 2);
    outside_viewport.link.detach();
    enemy.state.motion_110.position = {100.0f,100.0f,0.0f};

    front_field_180_calls = 0;
    front_boss_gauge_calls = 0;
    enemy.state.health.field_04 = 200;
    enemy.state.field_270 = 2;
    set_packet(527, {3, bits(100.0f), 0x76543210u, 0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(front_boss_gauge_calls == 1);
    assert(front_boss_gauge_boss == 2 && front_boss_gauge_marker == 3);
    assert(front_boss_gauge_fraction == 0.5f);
    assert(front_boss_gauge_value == 0x76543210);
    set_packet(534, {0x87654321u,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(front_field_180_calls == 1);
    assert(static_cast<std::uint32_t>(front.field_180) == 0x87654321u);

    front_stage_title_calls = 0;
    set_packet(548, {});
    assert(enemy.state.execute_opcode() == 0);
    assert(front_stage_title_calls == 1);

    // Opcode 324 resolves an Enemy by identifier and copies its XY position;
    // when no Enemy matches, the exact fallback is this EnemyState's XY.
    enemy.state.motion_110.position = {1.0f,2.0f,3.0f};
    selected_test_enemy = &found_enemy;
    set_packet(324, {bits(-9981.0f),bits(-9980.0f),0x00000324u,0,0,0,0,0}, 3);
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.counters.field_10 == 12.0f);
    assert(enemy.state.counters.field_14 == 34.0f);
    selected_test_enemy = nullptr;
    set_packet(324, {bits(-9981.0f),bits(-9980.0f),0x00000324u,0,0,0,0,0}, 3);
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.counters.field_10 == 1.0f);
    assert(enemy.state.counters.field_14 == 2.0f);
    selected_test_enemy = &enemy;

    enemy.state.field_1c = 0x12345678;
    enemy.state.field_280 = -19;
    enemy.state.flags.word_04 = 0xa5a5f00du;
    set_packet(569, {});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.field_1c == 0x12345678);
    assert(enemy.state.field_280 == -19);
    assert(enemy.state.flags.word_04 == 0xa5a5f00du);

    enemy.state.flags.word_04 = 0xa5000000u;
    set_packet(424, {1,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.flags.word_04 == 0xa5000008u);

    enemy.state.field_44 = 0;
    set_packet(448, {7,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.field_44 == 7);

    enemy.state.field_44 = 0;
    enemy.state.movements[0].motion.position = {1.0f,2.0f,0.0f};
    enemy.state.motion_110.position = {0.0f,0.0f,0.0f};
    set_packet(400, {bits(12.5f),bits(-7.25f),0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.movements[0].motion.position.x == 12.5f);
    assert(enemy.state.movements[0].motion.position.y == -7.25f);

    enemy.state.flags.word_04 = 0;
    set_packet(404, {bits(0.5f),bits(12.5f),0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(static_cast<float>(enemy.state.movements[0].motion.angle_1c) == 0.5f);
    assert(enemy.state.movements[0].motion.value_18 == 12.5f);

    defeat_result = 1;
    set_packet(560, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 1);
    defeat_result = 0;

    enemy.state.pattern.counts.fill(9);
    enemy.state.pattern.extra_counts.fill(7);
    enemy.state.pattern.duration = 99;
    set_packet(506, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    for (const auto value : enemy.state.pattern.counts) assert(value == 0);
    assert(enemy.state.pattern.duration == 0);

    set_packet(507, {1,17,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.pattern.counts[0] == 17);
    set_packet(567, {2,23,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.pattern.extra_counts[1] == 23);
    set_packet(568, {77,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.pattern.duration == 77);
    set_packet(572, {4,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.pattern.bomb_kind == 4);
    set_packet(508, {bits(-3.5f),bits(9.25f),0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.pattern.radius_x == -3.5f);
    assert(enemy.state.pattern.radius_y == 9.25f);
    set_packet(510, {6,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.pattern.base_kind == 6);

    session.field_70 = 2;
    enemy.state.pattern.counts[0] = 123;
    pattern_drop_called = false;
    set_packet(509, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.pattern.counts[0] == 123);
    assert(!pattern_drop_called);

    session.field_70 = 1;
    enemy.state.flags.word_08 = 1u << 5;
    enemy.state.motion_110.position = {3.0f,4.0f,5.0f};
    pattern_drop_called = false;
    set_packet(509, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(pattern_drop_called && pattern_drop_bomb_mark);
    assert(pattern_drop_origin.x == 3.0f && pattern_drop_origin.y == 4.0f && pattern_drop_origin.z == 5.0f);

    session.field_70 = 2;
    enemy.state.flags.word_08 = 0;
    pattern_drop_called = false;
    set_packet(556, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(pattern_drop_called && !pattern_drop_bomb_mark);

    enemy.state.field_284 = 0;
    player_record.field_dc = 0;
    set_packet(500, {bits(1.25f),bits(2.5f),0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.bounds_5c.x == 1.25f && enemy.state.bounds_5c.y == 2.5f);
    assert(enemy.state.field_284 == 1 && player_record.field_dc == 1);
    set_packet(501, {bits(-4.0f),bits(8.0f),0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.bounds_64.x == -4.0f && enemy.state.bounds_64.y == 8.0f);

    enemy.state.flags.word_04 = 0x8000u;
    set_packet(504, {bits(10.0f),bits(20.0f),bits(30.0f),bits(40.0f),0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.flags.word_04 == 0x8002u);
    assert(enemy.state.bounds_178.x == 10.0f && enemy.state.bounds_178.y == 20.0f);
    assert(enemy.state.bounds_178.width == 30.0f && enemy.state.bounds_178.height == 40.0f);
    set_packet(505, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.flags.word_04 == 0x8000u);

    enemy.state.flags.word_04 = 0x80u;
    set_packet(511, {123,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.health.health == 123 && enemy.state.health.field_04 == 123);
    assert(enemy.state.health.phase_health == 123 && enemy.state.health.scaled_health == 861);
    assert((enemy.state.flags.word_04 & 0x4080u) == 0x4080u);
    set_packet(566, {11,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.health.health == 11 && enemy.state.health.scaled_health == 77);
    assert(enemy.state.health.field_04 == 123 && enemy.state.health.phase_health == 123);

    controller.data.field_84.value = 0xabcd0001u;
    enemy.state.flags.word_04 = 0x8000u;
    set_packet(512, {3,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(controller.data.field_84.value == 0xabcd0000u);
    assert(controller.data.handles[3].value == 0x12345678u);
    assert(enemy.state.field_270 == 3 && (enemy.state.flags.word_04 & 0x80u));
    set_packet(512, {0xffffffffu,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(controller.data.handles[3].value == 0);
    assert((enemy.state.flags.word_04 & 0x80u) == 0);

    enemy.state.timer_a8 = 8;
    set_packet(513, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && static_cast<std::int32_t>(enemy.state.timer_a8) == 0);
    set_packet(515, {55,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && static_cast<std::int32_t>(enemy.state.timer_288) == 55);
    set_packet(535, {66,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && static_cast<std::int32_t>(enemy.state.timer_298) == 66);
    set_packet(526, {bits(-2.5f),0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && enemy.state.field_274 == 6.25f);
    enemy.state.flags.word_04 = 0xa5a50008u;
    set_packet(552, {0xffffffffu,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.flags.word_04 == 0xa5a50008u);
    set_packet(552, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.flags.word_04 == 0xa5a50000u);

    set_packet(557, {1,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && (enemy.state.flags.word_00 & 0x1000u));
    set_packet(558, {bits(7.25f),0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && enemy.state.field_38 == 7.25f);
    set_packet(559, {bits(-1.5f),0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && enemy.state.field_4c == -1.5f);

    // The 88/502 aliases still enter the separate native OR-flag helper.
    animation_flags_add_calls = 0;
    set_packet(502, {0x00000020u,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && animation_flags_add_calls == 1);
    set_packet(88, {0x00000020u,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && animation_flags_add_calls == 2);

    // Opcode 503 clears only the low fourteen bits. It restores flag zero
    // on every current handle only when bit five is inactive afterward.
    enemy.state.animations.resize(2);
    enemy.state.animations[0].handle.value = 0x11111111u;
    enemy.state.animations[1].handle.value = 0x22222222u;
    enemy.state.flags.word_00 = 0xa5ff3fffu;
    animation_flag0_set_calls = 0;
    set_packet(503, {0x00001000u,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.flags.word_00 == 0xa5ff2fffu);
    assert(animation_flag0_set_calls == 0);

    enemy.state.flags.word_00 = 0xa5ff3fffu;
    animation_flag0_set_calls = 0;
    set_packet(503, {0x80004020u,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.flags.word_00 == 0xa5ff3fdfu);
    assert(animation_flag0_set_calls == 2);
    assert(animation_flag0_set_handles[0] == 0x11111111u);
    assert(animation_flag0_set_handles[1] == 0x22222222u);

    set_packet(518, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);

    // An already-inactive bit five still triggers the native restoration walk.
    enemy.state.flags.word_00 = 0xa5ff3fdfu;
    animation_flag0_set_calls = 0;
    set_packet(503, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.flags.word_00 == 0xa5ff3fdfu);
    assert(animation_flag0_set_calls == 2);
    enemy.state.animations.clear();

    // Native opcode 517 reads operands 2/1/0 in that order, then passes
    // them as ScreenInf factory parameters 1/2/3 with all trailing values 0.
    screen_factory_calls = 0;
    screen_factory_mode = -1;
    screen_factory_arguments = {};
    set_packet(517, {0x11u,0x22u,0x33u,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(screen_factory_calls == 1 && screen_factory_mode == 1);

    front_dialogue_command_calls = 0;
    laser_cancel_all_calls = 0;
    Bullet dialogue_cancel_bullet;
    dialogue_cancel_bullet.state = 1;
    dispatch_test_bullets->active.append(&dialogue_cancel_bullet.link);
    bullet_cancel_calls = 0;
    bullet_cancel_mode = -1;
    set_packet(518, {123,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(front_dialogue_command_calls == 1);
    assert(last_front_dialogue_command == 123);
    assert(bullet_cancel_calls == 1 && bullet_cancel_mode == 0);
    assert(dialogue_cancel_bullet.state == 4);
    assert(laser_cancel_all_calls == 1);
    dialogue_cancel_bullet.link.detach();

    // Opcode 524 preserves the original full signed input in EnemyState while
    // delegating the unsigned word to the published GameController owner.
    game_controller_set_calls = 0;
    game_controller_last_value = 0;
    enemy.state.field_280 = 17;
    enemy.state.field_284 = 9;
    set_packet(524, {0x87654321u,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(game_controller_set_calls == 1);
    assert(game_controller_last_value == 0x87654321u);
    assert(static_cast<std::uint32_t>(enemy.state.field_280) == 0x87654321u);
    assert(enemy.state.field_284 == 0);

    // Opcode 575 saves Player zero before the integer operand and forwards the
    // full 32-bit word through the real Player lookup and bit-10 setter.
    player_fixture.entity_flags.bits = 0;
    set_packet(575, {0x80000001u,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(session.contexts[0].object_04 == dispatch_test_player);
    assert(player_fixture.entity_flags.fields.bit_10 == 1);
    assert((screen_factory_arguments == std::array<std::uint32_t,6>{
        0x11u,0x22u,0x33u,0u,0u,0u}));

    set_packet(543, {1,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && (enemy.state.flags.word_04 & 0x8000u));
    set_packet(544, {9,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && enemy.state.field_30 == 9);
    set_packet(546, {10,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && enemy.state.field_34 == 10);
    set_packet(547, {11,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && enemy.state.field_264 == 11);

    // Opcode 563 has two state-dependent update protocols. The first adds
    // the newly read positive field_284; the second adds the newly read value
    // minus one. Other prior states do not evaluate operand zero.
    player_record.field_dc = 10;
    enemy.state.field_284 = 0;
    set_packet(563, {7,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.field_284 == 7 && player_record.field_dc == 17);
    enemy.state.field_284 = 1;
    set_packet(563, {6,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.field_284 == 6 && player_record.field_dc == 22);
    enemy.state.field_284 = 9;
    set_packet(563, {99,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.field_284 == 9 && player_record.field_dc == 22);

    session.table.field_1fc = 5;
    enemy.state.field_280 = 5;
    enemy.state.field_284 = 4;
    player_record.field_e0 = 3;
    set_packet(564, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(player_record.field_e0 == 7 && enemy.state.field_284 == 0);
    enemy.state.field_284 = 6;
    enemy.state.field_280 = 4;
    set_packet(564, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(player_record.field_e0 == 7 && enemy.state.field_284 == 6);

    // Opcode 520 returns -1 on the first selected handle among slots 0..2.
    for (std::uint32_t selected_slot = 0; selected_slot < 3; ++selected_slot) {
        for (auto& handle : controller.data.handles) handle.value = 0;
        controller.data.handles[selected_slot].value = enemy.state.identifier.get();
        set_packet(520, {0,0,0,0,0,0,0,0});
        assert(enemy.state.execute_opcode() == -1);
    }
    for (auto& handle : controller.data.handles) handle.value = 0;
    set_packet(520, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);

    // Drive the already exact 501B/521B/514B/526B controller clear leaves
    // over a real linked Enemy, keeping its Animation list empty so the only
    // stubbed leaf is the external animation-handle retirement boundary.
    controller.enemies.prepend(&enemy.controller_link);
    enemy.state.flags.word_00 = 0;
    enemy.state.flags.word_04 = 0;
    enemy.state.field_284 = 42;
    enemy.state.field_27c = 8;
    enemy.state.field_30 = 17;
    enemy.state.vector_6c = {5.0f,6.0f,0.0f};
    enemy.state.pattern.radius_x = 4.0f;
    enemy.state.pattern.radius_y = 9.0f;
    const auto timer_before_clear = controller.data.timer_8c.current;
    set_packet(525, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(controller.data.timer_8c.current == timer_before_clear + 1);
    assert(enemy.state.field_284 == 0 && enemy.state.vector_6c.x == 0.0f && enemy.state.vector_6c.y == 192.0f);
    assert(enemy.state.pattern.radius_x == 32.0f && enemy.state.pattern.radius_y == 32.0f);
    assert(enemy.state.flags.word_04 & 0x200u);

    enemy.state.field_284 = 43;
    enemy.state.vector_6c = {7.0f,8.0f,0.0f};
    set_packet(545, {17,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(controller.data.timer_8c.current == timer_before_clear + 2);
    assert(enemy.state.field_284 == 0 && enemy.state.vector_6c.x == 0.0f && enemy.state.vector_6c.y == 192.0f);

    enemy.state.field_284 = 44;
    enemy.state.field_27c = 9;
    set_packet(565, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(controller.data.timer_8c.current == timer_before_clear + 3);
    assert(enemy.state.field_284 == 0 && enemy.state.field_27c == -1);

    enemy.state.flags.word_04 |= 1u << 30;
    enemy.state.field_284 = 45;
    set_packet(573, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(controller.data.timer_8c.current == timer_before_clear + 4);
    assert(enemy.state.field_284 == 45);
    enemy.state.flags.word_04 &= ~(1u << 30);
    set_packet(573, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(controller.data.timer_8c.current == timer_before_clear + 5);
    assert(enemy.state.field_284 == 0);

    set_packet(539, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(dispatch_test_lasers->active.next_value() == nullptr);

    enemy.state.flags.word_04 = 0xa5000000u;
    set_packet(538, {1,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.flags.word_04 == 0xa5000800u);
    set_packet(538, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.flags.word_04 == 0xa5000000u);

    enemy.state.flags.word_04 = 0xffffffffu;
    enemy.state.flags.word_00 = 0xffffffffu;
    enemy.state.field_28 = 91;
    set_packet(540, {0,12,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.field_54 == 12 && enemy.state.field_58 == 91);
    assert((enemy.state.flags.word_04 & 0x3000u) == 0);
    assert((enemy.state.flags.word_00 & 1u) == 0);

    set_packet(541, {bits(0.75f),0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(static_cast<float>(default_timer_clock) == 0.75f);

    const std::int32_t mode_amounts[4] = {10,20,30,40};
    for (std::int32_t mode = 0; mode < 4; ++mode) {
        session.table.field_1e0 = mode;
        enemy.main.time = 100.0f;
        set_packet(542, {10,20,30,40,0,0,0,0});
        assert(enemy.state.execute_opcode() == 0);
        assert(enemy.main.time == 100.0f - static_cast<float>(mode_amounts[mode]));
    }
    session.table.field_1e0 = 0;
    enemy.main.time = 50.0f;
    enemy.state.flags.word_08 = 0x40u;
    set_packet(574, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && enemy.main.time == 50.0f);
    enemy.state.flags.word_08 = 0;
    assert(enemy.state.execute_opcode() == 0 && enemy.main.time == 49.0f);

    enemy.state.health.flags.bits = 0xffffffffu;
    const auto finish_calls_before = card_finish_spell_calls;
    set_packet(523, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(card_finish_spell_calls == finish_calls_before + 1);
    assert((enemy.state.health.flags.bits & 1u) == 0);
    card.spell_flags.bits = 0;
    set_packet(536, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(card.spell_flags.bits & 8u);
    set_packet(537, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(card.spell_flags.bits & 16u);
    card.spell_flags.bits = 0xffffffffu;
    set_packet(561, {1,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(card.spell_flags.bits == 0xffffffffu);
    set_packet(561, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(card.spell_flags.bits == 0xfffffeffu);
    set_packet(562, {1,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.health.flags.bits == 0xffffffffu);
    set_packet(562, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.health.flags.bits == 0xfffffffeu);

    enemy.state.motion_110.position = {96.0f,0.0f,0.0f};
    set_packet(516, {7,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(sound_effect_calls == 1 && sound_effect_id == 7 && sound_effect_x == 96.0f);

    front_has_dialogue = false;
    front_dialogue_ready_calls = 0;
    set_packet(519, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(front_dialogue_ready_calls == 0);
    front_has_dialogue = true;
    front_dialogue_ready = false;
    assert(enemy.state.execute_opcode() == -1);
    assert(front_dialogue_ready_calls == 1);
    front_dialogue_ready = true;
    assert(enemy.state.execute_opcode() == 0);
    assert(front_dialogue_ready_calls == 2);

    for (std::int32_t selector = 0; selector < 4; ++selector) {
        enemy.state.field_50 = selector;
        set_packet(529, {static_cast<std::uint32_t>(-9985),101,102,103,104,0,0,0,0}, 1);
        assert(enemy.state.execute_opcode() == 0);
        assert(enemy.state.counters.field_00 == static_cast<std::uint32_t>(101 + selector));
    }
    for (std::int32_t selector = 0; selector < 4; ++selector) {
        enemy.state.field_50 = selector;
        set_packet(530, {bits(-9981.0f),bits(1.25f),bits(2.25f),bits(3.25f),bits(4.25f),0,0,0,0}, 1);
        assert(enemy.state.execute_opcode() == 0);
        assert(enemy.state.counters.field_10 == 1.25f + selector);
    }
    for (std::int32_t selector = 0; selector < 8; ++selector) {
        enemy.state.field_50 = selector;
        set_packet(570, {static_cast<std::uint32_t>(-9985),201,202,203,204,205,206,207,208}, 1);
        assert(enemy.state.execute_opcode() == 0);
        assert(enemy.state.counters.field_00 == static_cast<std::uint32_t>(201 + selector));
    }
    for (std::int32_t selector = 0; selector < 8; ++selector) {
        enemy.state.field_50 = selector;
        set_packet(571, {bits(-9981.0f),bits(11.5f),bits(12.5f),bits(13.5f),bits(14.5f),bits(15.5f),bits(16.5f),bits(17.5f),bits(18.5f)}, 1);
        assert(enemy.state.execute_opcode() == 0);
        assert(enemy.state.counters.field_10 == 11.5f + selector);
    }

    // Opcode 549 resolves Context/EnemyController before operand 1 and writes
    // the bool result only after the exact membership leaf returns.
    dispatch_identifier_calls = 0;
    dispatch_identifier_result = true;
    enemy.main.stack.words.clear();
    set_packet(549, {0,0x12345678u,0,0,0,0,0,0}, 1);
    assert(enemy.state.execute_opcode() == 0);
    assert(dispatch_identifier_calls == 1);
    assert(dispatch_identifier_value == 0x12345678u);
    assert(enemy.main.stack.local(0) == 1u);
    dispatch_identifier_result = false;
    enemy.main.stack.words.clear();
    set_packet(549, {0,0,0,0,0,0,0,0}, 1);
    assert(enemy.state.execute_opcode() == 0);
    assert(dispatch_identifier_calls == 2 && dispatch_identifier_value == 0u);
    assert(enemy.main.stack.local(0) == 0u);

    // Opcode 800 finds the requested Enemy through the Context controller,
    // retires its async runtimes, resets its main runtime, then selects the
    // inline script name at EclInstruction+0x18 through the real EclLoader.
    found_enemy.loader = &loader;
    found_enemy.state.entity = &found_enemy;
    found_enemy.reset();
    found_enemy.main.time = 9.5f;
    found_enemy.main.position.subroutine = 7;
    found_enemy.main.position.offset = 12;
    found_enemy.main.async_id = 88;
    found_enemy.main.signal = 19;
    found_enemy.main.flags.bits = 0xa5a5a5a5u;
    found_enemy.main.stack.words.push_back(0x12345678u);
    found_enemy.main.stack.pointer = 4;
    found_enemy.main.stack.frame_base = 4;
    selected_test_enemy = &found_enemy;
    dispatch_find_calls = 0;
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_value = 0x324;
    dispatch_integer_read_hook = &retarget_enemy_controller_during_integer_read;
    set_packet(800, {static_cast<std::uint32_t>(-101),0,0,0,0,0,0,0}, 1);
    auto* opcode800_instruction = reinterpret_cast<EclInstruction*>(packet.data() + 16);
    std::memcpy(reinterpret_cast<std::uint8_t*>(opcode800_instruction) + 0x18,
                "root-test", sizeof("root-test"));
    assert(enemy.state.execute_opcode() == 0);
    assert(dispatch_integer_read_calls == 1 && dispatch_integer_read_index == -101);
    assert(dispatch_find_calls == 1 && dispatch_find_receiver == &controller);
    assert(dispatch_find_identifier == 0x324u);
    assert(context.enemies == &alternate_controller && enemy.state.context == &alternate_context);
    assert(found_enemy.loader == &loader && found_enemy.current_runtime == &found_enemy.main);
    assert(found_enemy.main.manager == &found_enemy);
    assert(found_enemy.main.position.subroutine == 0 && found_enemy.main.position.offset == 0);
    assert(found_enemy.main.time == 0.0f && found_enemy.main.async_id == -1);
    assert(found_enemy.main.signal == 0 && found_enemy.main.flags.bits == 0xa5a5a5a4u);
    assert(found_enemy.main.stack.words.empty());
    assert(found_enemy.main.stack.pointer == 0 && found_enemy.main.stack.frame_base == 0);
    assert(found_enemy.runtimes.next_value() == nullptr);
    dispatch_integer_read_hook = nullptr;
    context.enemies = &controller;
    enemy.state.context = &context;

    // A missing identifier still consumes the operand and performs the lookup,
    // but does not reset or redirect the target Enemy's current runtime.
    selected_test_enemy = nullptr;
    dispatch_find_calls = 0;
    found_enemy.main.time = 77.0f;
    set_packet(800, {0x324u,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(dispatch_find_calls == 1 && dispatch_find_receiver == &controller);
    assert(dispatch_find_identifier == 0x324u && found_enemy.main.time == 77.0f);

    // Opcode 801 uses operand 2 as an Enemy identifier, then independently
    // re-reads the selected Enemy's position before resolving each output
    // destination. Both VM destinations are real ScriptStack local slots.
    selected_test_enemy = &found_enemy;
    found_enemy.state.motion_110.position = {12.0f,34.0f,56.0f};
    enemy.main.stack.reset();
    dispatch_find_calls = 0;
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_value = 0x324;
    dispatch_integer_read_hook = &retarget_enemy_controller_during_integer_read;
    set_packet(801, {bits(0.0f),bits(4.0f),static_cast<std::uint32_t>(-101),0,0,0,0,0}, 7);
    assert(enemy.state.execute_opcode() == 0);
    assert(dispatch_integer_read_calls == 1 && dispatch_integer_read_index == -101);
    assert(dispatch_find_calls == 1 && dispatch_find_receiver == &controller);
    assert(dispatch_find_identifier == 0x324u);
    assert(enemy.main.stack.local(0) == bits(12.0f));
    assert(enemy.main.stack.local(4) == bits(34.0f));
    assert(context.enemies == &alternate_controller && enemy.state.context == &alternate_context);
    dispatch_integer_read_hook = nullptr;
    context.enemies = &controller;
    enemy.state.context = &context;
    selected_test_enemy = &enemy;

    // Opcode 802 walks the three selected Enemy slots, skips the current
    // player slot and any negative-life phase, and restarts only eligible
    // targets using the borrowed script stored in each real EnemyPhase.
    loader.records.clear();
    loader.records.push_back({"phase-a", packet.data()});
    loader.records.push_back({"phase-b", packet.data()});
    loader.records.push_back({"root-test", packet.data()});
    loader.subroutine_count = 3;
    found_enemy.loader = &loader;
    found_enemy.state.entity = &found_enemy;
    found_enemy.state.phases.resize(1);
    found_enemy.state.phases[0].life = 9;
    std::strcpy(found_enemy.state.phases[0].script, "phase-a");
    found_enemy.main.time = 9.0f;
    found_enemy.main.position.subroutine = 4;
    found_enemy.main.position.offset = 8;
    found_enemy.main.async_id = 7;
    found_enemy2.loader = &loader;
    found_enemy2.state.entity = &found_enemy2;
    found_enemy2.state.identifier = 0x1002u;
    found_enemy2.reset();
    found_enemy2.state.phases.resize(1);
    found_enemy2.state.phases[0].life = -1;
    std::strcpy(found_enemy2.state.phases[0].script, "phase-b");
    found_enemy2.main.time = 77.0f;
    found_enemy2.main.position.subroutine = 5;
    found_enemy2.main.position.offset = 6;
    found_enemy2.main.async_id = 10;
    enemy.state.phases.resize(1);
    enemy.state.phases[0].life = 9;
    std::strcpy(enemy.state.phases[0].script, "root-test");
    enemy.state.field_270 = 1;
    enemy.main.time = 55.0f;
    enemy.main.position.subroutine = 0;
    enemy.main.position.offset = 0;
    enemy.main.async_id = 12;
    controller.data.handles[0].value = found_enemy.state.identifier.get();
    controller.data.handles[1].value = enemy.state.identifier.get();
    controller.data.handles[2].value = found_enemy2.state.identifier.get();
    dispatch_find_enemies = {};
    dispatch_find_enemies[0] = &found_enemy;
    dispatch_find_enemies[1] = &enemy;
    dispatch_find_enemies[2] = &found_enemy2;
    dispatch_find_calls = 0;
    dispatch_find_identifiers = {};
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_hook = &observe_integer_read;
    dispatch_integer_read_value = 0;
    selected_test_enemy = nullptr;
    set_packet(802, {static_cast<std::uint32_t>(-101),0,0,0,0,0,0,0}, 1);
    assert(enemy.state.execute_opcode() == 0);
    assert(dispatch_integer_read_calls == 1 && dispatch_integer_read_index == -101);
    assert(dispatch_find_calls == 3 && dispatch_find_receiver == &controller);
    assert(dispatch_find_identifiers[0] == found_enemy.state.identifier.get());
    assert(dispatch_find_identifiers[1] == enemy.state.identifier.get());
    assert(dispatch_find_identifiers[2] == found_enemy2.state.identifier.get());
    assert(found_enemy.main.position.subroutine == 0 && found_enemy.main.position.offset == 0);
    assert(found_enemy.main.time == 0.0f && found_enemy.main.async_id == -1);
    assert(found_enemy.current_runtime == &found_enemy.main);
    assert(found_enemy2.main.time == 77.0f);
    assert(found_enemy2.main.position.subroutine == 5 && found_enemy2.main.position.offset == 6);
    assert(found_enemy2.main.async_id == 10);
    assert(enemy.main.time == 55.0f);
    assert(enemy.main.position.subroutine == 0 && enemy.main.position.offset == 0);
    assert(enemy.main.async_id == 12);

    // A nonnegative phase with an empty inline script still follows the
    // native non-null array-address gate: it retires/reset the target and
    // calls EclManager::select with the empty string, which resolves to -1.
    found_enemy2.state.phases[0].life = 0;
    found_enemy2.state.phases[0].script[0] = 0;
    found_enemy2.main.time = 88.0f;
    found_enemy2.main.position.subroutine = 5;
    found_enemy2.main.position.offset = 6;
    found_enemy2.main.async_id = 10;
    dispatch_find_calls = 0;
    dispatch_find_identifiers = {};
    dispatch_integer_read_calls = 0;
    set_packet(802, {static_cast<std::uint32_t>(-101),0,0,0,0,0,0,0}, 1);
    assert(enemy.state.execute_opcode() == 0);
    assert(dispatch_integer_read_calls == 1 && dispatch_integer_read_index == -101);
    assert(dispatch_find_calls == 3);
    assert(found_enemy2.main.time == 0.0f);
    assert(found_enemy2.main.position.subroutine == -1);
    assert(found_enemy2.main.position.offset == 0);
    assert(found_enemy2.main.async_id == -1);
    assert(found_enemy2.current_runtime == &found_enemy2.main);
    dispatch_integer_read_hook = nullptr;
    dispatch_find_enemies = {};
    selected_test_enemy = &enemy;

    // Opcode 553 writes the complete unsigned word through the real
    // EnemyController setter. Its receiver is cached before VM operand 0.
    controller.data.field_88 = 0x12345678u;
    set_packet(553, {0x87654321u,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(controller.data.field_88 == 0x87654321u);

    controller.data.field_88 = 0x11223344u;
    alternate_controller.data.field_88 = 0x55667788u;
    dispatch_integer_read_calls = 0;
    dispatch_integer_read_value = static_cast<std::int32_t>(0x89abcdefu);
    dispatch_integer_read_hook = &retarget_enemy_controller_during_integer_read;
    set_packet(553, {static_cast<std::uint32_t>(-101),0,0,0,0,0,0,0}, 1);
    assert(enemy.state.execute_opcode() == 0);
    assert(dispatch_integer_read_calls == 1 && dispatch_integer_read_index == -101);
    assert(controller.data.field_88 == 0x89abcdefu);
    assert(alternate_controller.data.field_88 == 0x55667788u);
    assert(context.enemies == &alternate_controller && enemy.state.context == &alternate_context);
    dispatch_integer_read_hook = nullptr;
    context.enemies = &controller;
    enemy.state.context = &context;

    controller.data.field_88 = 0x76543210u;
    dispatch_integer_read_hook = &throw_during_integer_read;
    set_packet(553, {static_cast<std::uint32_t>(-101),0,0,0,0,0,0,0}, 1);
    bool opcode553_threw = false;
    try { (void)enemy.state.execute_opcode(); }
    catch (int value) { opcode553_threw = value == 553; }
    assert(opcode553_threw && controller.data.field_88 == 0x76543210u);
    dispatch_integer_read_hook = nullptr;

    // Opcode 554 caches the real BulletController before reading Y then X.
    // Its production 39-byte setter may change only the two Vector2 words.
    dispatch_test_bullets->vector_4c = {1.25f,2.5f};
    dispatch_test_bullets_alternate->vector_4c = {3.75f,4.5f};
    std::vector<std::uint8_t> bullet_owner_before(sizeof(BulletController));
    std::vector<std::uint8_t> alternate_bullet_before(sizeof(BulletController));
    std::memcpy(bullet_owner_before.data(), dispatch_test_bullets, bullet_owner_before.size());
    std::memcpy(alternate_bullet_before.data(), dispatch_test_bullets_alternate, alternate_bullet_before.size());
    set_packet(554, {bits(12.5f),bits(-7.25f),0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(dispatch_test_bullets->vector_4c.x == 12.5f);
    assert(dispatch_test_bullets->vector_4c.y == -7.25f);
    const auto* bullet_owner_base = reinterpret_cast<const std::uint8_t*>(dispatch_test_bullets);
    const auto vector_offset = static_cast<std::size_t>(
        reinterpret_cast<const std::uint8_t*>(&dispatch_test_bullets->vector_4c) - bullet_owner_base);
    const auto* bullet_owner_after = bullet_owner_base;
    const auto* alternate_bullet_after = reinterpret_cast<const std::uint8_t*>(dispatch_test_bullets_alternate);
    for (std::size_t i=0; i<bullet_owner_before.size(); ++i) {
        if (i < vector_offset || i >= vector_offset + sizeof(Vector2))
            assert(bullet_owner_before[i] == bullet_owner_after[i]);
        assert(alternate_bullet_before[i] == alternate_bullet_after[i]);
    }

    // Retarget both the original Context slot and EnemyState::context during
    // the first (Y) read. The original cached BulletController must still be
    // the only owner modified, and the VM references expose Y-before-X.
    dispatch_test_bullets->vector_4c = {5.0f,6.0f};
    dispatch_test_bullets_alternate->vector_4c = {7.0f,8.0f};
    dispatch_float_read_calls = 0;
    dispatch_float_read_indices = {};
    dispatch_float_read_values = {-7.25f,12.5f};
    dispatch_float_read_hook = &retarget_bullet_controller_during_first_float_read;
    set_packet(554, {bits(-102.0f),bits(-101.0f),0,0,0,0,0,0}, 3);
    assert(enemy.state.execute_opcode() == 0);
    assert(dispatch_float_read_calls == 2);
    assert(dispatch_float_read_indices[0] == -101 && dispatch_float_read_indices[1] == -102);
    assert(dispatch_test_bullets->vector_4c.x == 12.5f);
    assert(dispatch_test_bullets->vector_4c.y == -7.25f);
    assert(dispatch_test_bullets_alternate->vector_4c.x == 7.0f);
    assert(dispatch_test_bullets_alternate->vector_4c.y == 8.0f);
    assert(context.primary_owner == dispatch_test_bullets_alternate);
    assert(enemy.state.context == &alternate_context);
    dispatch_float_read_hook = nullptr;
    context.primary_owner = dispatch_test_bullets;
    enemy.state.context = &context;

    // Either operand exception prevents the native setter from running.
    for (std::int32_t throw_at=1; throw_at<=2; ++throw_at) {
        dispatch_test_bullets->vector_4c = {21.0f,22.0f};
        dispatch_test_bullets_alternate->vector_4c = {31.0f,32.0f};
        dispatch_float_read_calls = 0;
        dispatch_float_throw_at = throw_at;
        dispatch_float_read_hook = &throw_during_float_read;
        set_packet(554, {bits(-102.0f),bits(-101.0f),0,0,0,0,0,0}, 3);
        bool opcode554_threw = false;
        try { (void)enemy.state.execute_opcode(); }
        catch (int value) { opcode554_threw = value == 554; }
        assert(opcode554_threw);
        assert(dispatch_test_bullets->vector_4c.x == 21.0f);
        assert(dispatch_test_bullets->vector_4c.y == 22.0f);
        assert(dispatch_test_bullets_alternate->vector_4c.x == 31.0f);
        assert(dispatch_test_bullets_alternate->vector_4c.y == 32.0f);
    }
    dispatch_float_read_hook = nullptr;
    context.primary_owner = dispatch_test_bullets;
    enemy.state.context = &context;

    // Opcode 551 reads integers 0/1/2 then floats 4/3, builds the actual
    // FogValue (B,G,R,A byte lanes) and publishes it through the live Stage.
    fog_set_calls = 0;
    set_packet(551, {17u,2u,0xa1b2c3d4u,bits(4.5f),bits(9.25f),0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(fog_set_calls == 1 && fog_set_duration == 17 && fog_set_mode == 2);
    assert(fog_set_value.near_distance == 4.5f && fog_set_value.far_distance == 9.25f);
    assert(fog_set_value.channels[0] == 0xd4 && fog_set_value.channels[1] == 0xc3);
    assert(fog_set_value.channels[2] == 0xb2 && fog_set_value.channels[3] == 0xa1);
    assert(fog_set_value.packed == 0xa1b2c3d4u);

    // Opcode 555 has two independent signed gates. It may request sound only,
    // spawn only, both in order, or neither; the spatial path uses layer 3.
    sound_effect_calls = 0;
    animation_file_select_calls = 0;
    animation_spawn_calls = 0;
    dispatch_order_size = 0;
    enemy.state.field_250 = -1;
    enemy.state.field_254 = -1;
    set_packet(555, {});
    assert(enemy.state.execute_opcode() == 0);
    assert(sound_effect_calls == 0 && animation_spawn_calls == 0);

    enemy.state.field_250 = 23;
    enemy.state.field_254 = -1;
    enemy.state.motion_110.position.x = 12.5f;
    set_packet(555, {});
    assert(enemy.state.execute_opcode() == 0);
    assert(sound_effect_calls == 1 && sound_effect_id == 23 && sound_effect_x == 12.5f);
    assert(animation_file_select_calls == 0 && animation_spawn_calls == 0);

    enemy.state.field_250 = -1;
    enemy.state.field_254 = 42;
    enemy.state.field_258 = 6;
    enemy.state.vector_6c = {1.0f,2.0f,0.0f};
    enemy.state.motion_110.position = {1.1f,2.1f,0.0f};
    set_packet(555, {});
    assert(enemy.state.execute_opcode() == 0);
    assert(animation_file_select_calls == 1 && animation_file_select_index == 6);
    assert(animation_spawn_calls == 1 && animation_spawn_script == 42);
    assert(animation_spawn_stem == nullptr && animation_spawn_output == nullptr);
    assert(animation_spawn_layer == 3);
    assert(animation_spawn_position.x == 1.1f && animation_spawn_position.y == 2.1f);
    assert(animation_spawn_rotation == native_negative_pi_56e0f8 / native_screen_half_2_56c8d0);

    sound_effect_calls = 0;
    animation_file_select_calls = 0;
    animation_spawn_calls = 0;
    dispatch_order_size = 0;
    enemy.state.field_250 = 19;
    enemy.state.field_254 = 44;
    enemy.state.field_258 = 3;
    enemy.state.vector_6c = {0.0f,0.0f,0.0f};
    enemy.state.motion_110.position = {3.0f,4.0f,0.0f};
    set_packet(555, {});
    assert(enemy.state.execute_opcode() == 0);
    assert(sound_effect_calls == 1 && sound_effect_id == 19 && sound_effect_x == 3.0f);
    assert(animation_file_select_calls == 1 && animation_file_select_index == 3);
    assert(animation_spawn_calls == 1 && animation_spawn_script == 44);
    assert(animation_spawn_layer == 3 && animation_spawn_flags == 0u && animation_spawn_output == nullptr);
    assert(dispatch_order_size == 3);
    assert((dispatch_order == std::array<std::int32_t,4>{1,2,3,0}));
    assert(std::abs(animation_spawn_rotation - 0.9272952f) < 0.00001f);

    dispatch_test_lasers_alternate->~LaserController();
    dispatch_test_lasers->~LaserController();
    dispatch_test_bullets_alternate->~BulletController();
    dispatch_test_bullets->~BulletController();

    std::cout << "PASS root dispatch: Enemy bullet rectangle cancel 712 (real AnimationHandle resolve/rotation and 707B BulletController cancel boss), Enemy queue copy 614 (full typed record assignment, shared metadata ownership, destination/source PMR growth and second-operand exception order), Enemy bullet plus Laser radial cancel 616 (real 320B BulletController and 288B LaserController cancel_near Bosses, live Context/position retargeting), Enemy player angle 617 (two live Context/Player position reads, atan2 and VM destination writeback), Enemy shared queued polar 618 (operand order, ensure-only record, polar Vector3 XY transform and Z preservation), Enemy shared queued parameters 620 (ensure-only shared record, std::pair extraction, ordered X/Y writes and NaN-compatible threshold), Enemy queued metadata radial offset 619 (writable-shot COW, ordered pair extraction and throw-visible clone), Enemy queued-record decrement 633 (writable COW and signed post-decrement clamp), Enemy opcode 632 borrowed script pointer (two indexes before COW, real PMR growth and packet-owned pointer), Enemy paired capped radial cancel 627/628 (real 401B Bullet and 288B Laser Bosses, 99,999 limit and live Context/position retargeting), Enemy mesh 621 (real allocator/owner release, positive-radius RenderMesh factory and operand-failure order), Laser 702/703/711/713 (real parameter temporaries, writable-shot COW and late Context selection), shot commands 609/610/611/612 (real writable-shot COW and PMR command vector), script select 800, selected position writeback 801, phase-selected script restarts 802, movement 400/404/424/448, animation flags 502/503, ScreenInf opcode 517 and dialogue cleanup 518 (real Bullet cancel-all traversal), global-owner opcodes 524/575, front gauge/title 527/534/548, selected-Enemy position 324, laser reset 539, bit flag 552, membership 549, fog 551, controller setters 553/554, animation/sound 555, reserved opcode 569, pattern 506-510/556/567/568/572, bounds/health/controller/state 500-559/563/564/566, controller selection/clear 520/525/545/565/573, timer/mode/time 538/539/540/541/542/574, card/health 523/536/537/561/562, sound queue enqueue plus dialogue 516/518/519, dynamic parameter copies 529/530/570/571 and special 560 return\n";
}
