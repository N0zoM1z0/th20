#define wmain unused_native_cpu_compare_main
#include "../_reference/Touhou20/tests/native_cpu_compare.cpp"
#include <d3dx9math.h>
#undef wmain

#include "StageResource.hpp"
#include "AnimationFile.hpp"
#include "StageResourceDrawAdapters.hpp"
#include "StageResourceScriptAdapters.hpp"
#include "ClockScalar.hpp"
#include "NativeCardHudAnimationView.hpp"
#include "NativeViewIndexOwner.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "NativeAnimationResetHooksView.hpp"
#include "NativeGraphicsModeAction.hpp"
#include "Worker.hpp"
#include "RenderMesh.hpp"
#include "ScalarMath.hpp"
#include "StageResourceObjectVisibility.hpp"
#include "Viewport.hpp"

#include <algorithm>
#include <array>
#include <bit>
#include <cstdint>
#include <cstring>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <map>
#include <new>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
template<class R, class... A>
R cpu(std::uint32_t va, void* self, A... args) {
    using Function = R(__thiscall*)(void*, A...);
    return reinterpret_cast<Function>(mapped_image_base + va - 0x400000)(self, args...);
}
template<class R, class... A>
R cpu_cdecl(std::uint32_t va, A... args) {
    using Function = R(__cdecl*)(A...);
    return reinterpret_cast<Function>(mapped_image_base + va - 0x400000)(args...);
}

[[noreturn]] void outside_scope() {
    throw std::runtime_error("A dependency outside the StageResource VM state oracle scope was reached");
}

std::uint32_t source_clear_color = 0;
std::vector<std::uint32_t> stage_draw_state_trace;

void record_stage_draw_state(std::uint32_t event, std::uint32_t argument = 0) {
    stage_draw_state_trace.push_back(event);
    stage_draw_state_trace.push_back(argument);
}

std::vector<std::uint32_t> instruction(
    int opcode, std::vector<std::uint32_t> args = {}, int time = 0) {
    std::vector<std::uint32_t> code(2 + args.size());
    auto* header = reinterpret_cast<th20::StageResourceInstructionHeader*>(code.data());
    header->time = time;
    header->opcode = static_cast<std::int16_t>(opcode);
    header->size = static_cast<std::int16_t>(code.size() * 4);
    std::copy(args.begin(), args.end(), code.begin() + 2);
    return code;
}
}

extern "C" th20::Matrix4* __stdcall stage_test_d3dx_matrix_translation(
    th20::Matrix4* output, float x, float y, float z) {
    for (unsigned row = 0; row < 4; ++row)
        for (unsigned column = 0; column < 4; ++column)
            output->elements[row][column] = row == column ? 1.0f : 0.0f;
    output->elements[3][0] = x;
    output->elements[3][1] = y;
    output->elements[3][2] = z;
    return output;
}

extern "C" th20::Vector3* __stdcall stage_test_d3dx_vec3_project_array(
    th20::Vector3* output, std::uint32_t output_stride,
    const th20::Vector3* input, std::uint32_t input_stride,
    const th20::NativeViewport* viewport, const th20::Matrix4* projection,
    const th20::Matrix4* view, const th20::Matrix4* world, std::uint32_t count) {
    auto multiply = [](const th20::Matrix4& left, const th20::Matrix4& right) {
        th20::Matrix4 result{};
        for (unsigned row = 0; row < 4; ++row)
            for (unsigned column = 0; column < 4; ++column)
                for (unsigned inner = 0; inner < 4; ++inner)
                    result.elements[row][column] +=
                        left.elements[row][inner] * right.elements[inner][column];
        return result;
    };
    const auto world_view = multiply(*world, *view);
    const auto combined = multiply(world_view, *projection);
    auto* output_bytes = reinterpret_cast<std::uint8_t*>(output);
    const auto* input_bytes = reinterpret_cast<const std::uint8_t*>(input);
    for (std::uint32_t index = 0; index < count; ++index) {
        th20::Vector3 point;
        std::memcpy(&point, input_bytes + index * input_stride, sizeof(point));
        const auto& m = combined.elements;
        const float x = point.x * m[0][0] + point.y * m[1][0] +
                        point.z * m[2][0] + m[3][0];
        const float y = point.x * m[0][1] + point.y * m[1][1] +
                        point.z * m[2][1] + m[3][1];
        const float z = point.x * m[0][2] + point.y * m[1][2] +
                        point.z * m[2][2] + m[3][2];
        const float w = point.x * m[0][3] + point.y * m[1][3] +
                        point.z * m[2][3] + m[3][3];
        const float reciprocal_w = 1.0f / w;
        const th20::Vector3 projected{
            static_cast<float>(viewport->x) +
                (1.0f + x * reciprocal_w) * static_cast<float>(viewport->width) * 0.5f,
            static_cast<float>(viewport->y) +
                (1.0f - y * reciprocal_w) * static_cast<float>(viewport->height) * 0.5f,
            viewport->min_z + z * reciprocal_w * (viewport->max_z - viewport->min_z)};
        std::memcpy(output_bytes + index * output_stride, &projected, sizeof(projected));
    }
    return output;
}

extern "C" th20::Matrix4* __stdcall stage_test_d3dx_matrix_rotation_y(
    th20::Matrix4* output, float angle) {
    for (unsigned row = 0; row < 4; ++row)
        for (unsigned column = 0; column < 4; ++column)
            output->elements[row][column] = row == column ? 1.0f : 0.0f;
    const float cosine = std::cos(angle);
    const float sine = std::sin(angle);
    output->elements[0][0] = cosine;
    output->elements[0][2] = -sine;
    output->elements[2][0] = sine;
    output->elements[2][2] = cosine;
    return output;
}

extern "C" th20::Vector3* __stdcall stage_test_d3dx_vec3_transform_coord(
    th20::Vector3* output, const th20::Vector3* input,
    const th20::Matrix4* matrix) {
    const auto& m = matrix->elements;
    const float x = input->x * m[0][0] + input->y * m[1][0] +
                    input->z * m[2][0] + m[3][0];
    const float y = input->x * m[0][1] + input->y * m[1][1] +
                    input->z * m[2][1] + m[3][1];
    const float z = input->x * m[0][2] + input->y * m[1][2] +
                    input->z * m[2][2] + m[3][2];
    const float w = input->x * m[0][3] + input->y * m[1][3] +
                    input->z * m[2][3] + m[3][3];
    output->x = x / w;
    output->y = y / w;
    output->z = z / w;
    return output;
}

// Source-side D3DX calls share the exact same CPU test seam as the original
// PE import slots patched below; this keeps the test focused on owner logic.
extern "C" D3DXMATRIX* WINAPI D3DXMatrixRotationY(
    D3DXMATRIX* output, FLOAT angle) {
    return reinterpret_cast<D3DXMATRIX*>(
        stage_test_d3dx_matrix_rotation_y(
            reinterpret_cast<th20::Matrix4*>(output), angle));
}
extern "C" D3DXVECTOR3* WINAPI D3DXVec3TransformCoord(
    D3DXVECTOR3* output, const D3DXVECTOR3* input,
    const D3DXMATRIX* matrix) {
    return reinterpret_cast<D3DXVECTOR3*>(
        stage_test_d3dx_vec3_transform_coord(
            reinterpret_cast<th20::Vector3*>(output),
            reinterpret_cast<const th20::Vector3*>(input),
            reinterpret_cast<const th20::Matrix4*>(matrix)));
}

namespace th20 {
// The focused PE oracle supplies aligned scratch storage for native D3DX calls.
template<class T>
struct NativeDrawScratch {
    alignas(T) std::byte storage[sizeof(T)];
    T* get_first();
};
template<class T>
T* NativeDrawScratch<T>::get_first() {
    return reinterpret_cast<T*>(storage);
}
template D3DXVECTOR3* NativeDrawScratch<D3DXVECTOR3>::get_first();
template D3DXMATRIX* NativeDrawScratch<D3DXMATRIX>::get_first();
NativeViewIndexOwner test_view_index_owner{};
ViewportState source_camera_viewport{};
Graphics process_graphics{};
NativeViewIndexOwner* native_view_index_owner_5c0028 = &test_view_index_owner;
AnimationPoolOwner* current_animation_pool =
    reinterpret_cast<AnimationPoolOwner*>(&test_view_index_owner);
SpriteData stage_test_sprite_data{};

SpriteData::SpriteData() noexcept
    : file_id(0), texture_index(0), texture_id(0), left(0), top(0), right(0),
      bottom(0), extent_1c(0), extent_20(0), field_24(0), field_28(0),
      field_2c(0), field_30(0), field_34(0), u0(0), v0(0), u1(0), v1(0),
      extent_48(32.0f), extent_4c(64.0f), scale_50(1.0f), scale_54(1.0f) {}

SpriteData* Animation::sprite_data() {
    return &stage_test_sprite_data;
}

std::int32_t AnimationPoolOwner::draw(Animation* animation) {
    record_stage_draw_state(7, static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(animation)));
    return 0;
}

void AnimationPoolOwner::flush_draws() {
    record_stage_draw_state(1);
}

std::int32_t __fastcall graphics_enable_fog(Graphics* graphics) {
    record_stage_draw_state(2);
    return 0;
}
std::int32_t __fastcall graphics_disable_fog(Graphics* graphics) {
    record_stage_draw_state(3);
    return 0;
}
std::int32_t __fastcall graphics_enable_depth_writes(Graphics* graphics) {
    record_stage_draw_state(4);
    return 0;
}
std::int32_t __fastcall graphics_disable_depth_writes(Graphics* graphics) {
    record_stage_draw_state(5);
    return 0;
}
void NativeGraphicsModeAction::select_view_477520(int index) {
    record_stage_draw_state(6, static_cast<std::uint32_t>(index));
}

extern "C" void __fastcall stage_test_native_animation_pool_flush(
    AnimationPoolOwner*, void*) {
    record_stage_draw_state(1);
}
extern "C" std::int32_t __fastcall stage_test_native_animation_pool_draw(
    AnimationPoolOwner*, void*, Animation* animation) {
    record_stage_draw_state(7, static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(animation)));
    return 0;
}
extern "C" void __fastcall stage_test_native_select_view(
    NativeGraphicsModeAction*, void*, int index) {
    record_stage_draw_state(6, static_cast<std::uint32_t>(index));
}
extern "C" void __fastcall stage_test_native_inline_animation_draw(
    Animation* animation, void*) {
    record_stage_draw_state(7, static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(animation)));
}
extern "C" void __fastcall stage_test_native_set_clip(
    NativeGraphicsModeAction*, void*, int index) {
    record_stage_draw_state(8, static_cast<std::uint32_t>(index));
}

void stage_resource_select_viewport(std::int32_t index) {
    record_stage_draw_state(6, static_cast<std::uint32_t>(index));
}
void stage_resource_set_clip(std::int32_t index) {
    record_stage_draw_state(8, static_cast<std::uint32_t>(index));
}
void stage_resource_enable_fog() { record_stage_draw_state(2); }
void stage_resource_disable_fog() { record_stage_draw_state(3); }
void stage_resource_enable_depth_writes() { record_stage_draw_state(4); }
void stage_resource_disable_depth_writes() { record_stage_draw_state(5); }
const ViewportState& stage_resource_viewport(std::int32_t) {
    return source_camera_viewport;
}

void NativeViewIndexOwner::set_view_index(std::int32_t value) {
    view_index_6c4 = value;
}
Angle& Angle::operator-=(float input) {
    value = normalize_angle(value - input);
    return *this;
}
void RenderMesh::initialize(float x, float y, float width, float height) {
    cpu<void>(0x0049d850, this, x, y, width, height);
}
void stage_vm_publish_camera(const ViewportState& camera) {
    source_camera_viewport = camera;
    process_graphics.viewports[3] = camera;
}

AnimationBase::AnimationBase() noexcept {}
Animation::Animation() noexcept : base() {}
Animation::~Animation() noexcept {}
std::int32_t Animation::update() {
    if ((base.flags.word_1c & 1u) == 0) outside_scope();
    return 0;
}
void NativeHudAnimationView::set_vm_event_477450(std::int32_t event) {
    auto* animation = reinterpret_cast<Animation*>(this);
    animation->base.field_438 = event;
    (void)animation->update();
}
void Animation::stop() {
    base.field_28 = -1;
    base.flags.byte_02 &= 0xfeu;
}
AnimationHandle::AnimationHandle() noexcept : value(0) {}
Graphics::~Graphics() {}
Worker::Worker() noexcept {}
Worker::~Worker() {}
void stage_vm_assign_animation(StageBackgroundScriptState&, std::int32_t,
                               std::int32_t) { outside_scope(); }
void stage_vm_stop_animation(Animation& animation) { animation.stop(); }
void stage_vm_reset_meshes(StageBackgroundScriptState& state) {
    for (std::int32_t index = 0; index < 2; ++index) {
        if (state.fields_3294[9 + index] != 0) outside_scope();
        state.fields_3294[9 + index] = 0;
        state.fields_3294[11 + index] = std::bit_cast<std::uint32_t>(112.0f);
        state.fields_3294[13 + index] = std::bit_cast<std::uint32_t>(192.0f);
        state.fields_3294[15 + index] = 0xffffffffu;
        state.mesh_phase_x[index] = 0.0f;
        state.mesh_phase_y[index] = 0.0f;
        state.mesh_timers[index] = 0;
        native_view_index_owner_5c0028->set_view_index(index);
    }
}
void stage_vm_interrupt_animations(StageResourceOwner& owner, std::uint32_t event) {
    owner.interrupt_animations(static_cast<std::int32_t>(event));
}
void stage_vm_set_clear_color(std::uint32_t value) { source_clear_color = value; }
void stage_vm_set_primary_rotation_flag(std::uint32_t value) {
    process_stage_resource->set_primary_rotation_flag(value);
}
}

int wmain(int argc, wchar_t** argv) {
    try {
        if (argc != 3)
            throw std::runtime_error("Usage: stage_resource_vm_cpu_compare ORIGINAL.exe OUTPUT.json");
        const auto bytes = th20::read_file(argv[1]);
        if (sha256(bytes) != expected_sha) throw std::runtime_error("Original hash mismatch");
        const auto pe = th20::parse_pe(bytes);
        Mapping image(bytes, pe);
        mapped_image_base = image.address();
        *reinterpret_cast<void**>(mapped_image_base + 0x16c308) =
            reinterpret_cast<void*>(&stage_test_d3dx_vec3_project_array);
        *reinterpret_cast<void**>(mapped_image_base + 0x16c30c) =
            reinterpret_cast<void*>(&stage_test_d3dx_matrix_translation);
        *reinterpret_cast<void**>(mapped_image_base + 0x16c318) =
            reinterpret_cast<void*>(&stage_test_d3dx_vec3_transform_coord);
        *reinterpret_cast<void**>(mapped_image_base + 0x16c31c) =
            reinterpret_cast<void*>(&stage_test_d3dx_matrix_rotation_y);
        auto patch_return = [&](std::uint32_t address, std::uint8_t stack_bytes) {
            auto* code = reinterpret_cast<std::uint8_t*>(
                mapped_image_base + address - 0x400000);
            if (stack_bytes == 0) {
                code[0] = 0xC3;
            } else {
                code[0] = 0xC2;
                code[1] = stack_bytes;
                code[2] = 0;
            }
        };
        auto patch_jump = [&](std::uint32_t address, const void* target) {
            auto* code = reinterpret_cast<std::uint8_t*>(
                mapped_image_base + address - 0x400000);
            const auto target_address = static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(target));
            code[0] = 0xB8;
            std::memcpy(code + 1, &target_address, sizeof(target_address));
            code[5] = 0xFF;
            code[6] = 0xE0;
        };
        patch_jump(0x00443880,
                   reinterpret_cast<const void*>(&th20::stage_test_native_animation_pool_draw));
        patch_jump(0x004455C0,
                   reinterpret_cast<const void*>(&th20::stage_test_native_animation_pool_flush));
        patch_jump(0x0044C570,
                   reinterpret_cast<const void*>(&th20::stage_test_native_inline_animation_draw));
        patch_jump(0x0041DCE0,
                   reinterpret_cast<const void*>(&th20::stage_test_native_set_clip));
        patch_jump(0x00477520,
                   reinterpret_cast<const void*>(&th20::stage_test_native_select_view));
        patch_jump(0x004DDA60,
                   reinterpret_cast<const void*>(&th20::graphics_disable_fog));
        patch_jump(0x004DDAC0,
                   reinterpret_cast<const void*>(&th20::graphics_enable_fog));
        patch_jump(0x004DDF80,
                   reinterpret_cast<const void*>(&th20::graphics_disable_depth_writes));
        patch_jump(0x004DDFE0,
                   reinterpret_cast<const void*>(&th20::graphics_enable_depth_writes));
        auto* sprite_lookup = reinterpret_cast<std::uint8_t*>(
            mapped_image_base + 0x00437CD0 - 0x00400000);
        const auto sprite_address = reinterpret_cast<std::uint32_t>(
            &th20::stage_test_sprite_data);
        sprite_lookup[0] = 0xB8;
        std::memcpy(sprite_lookup + 1, &sprite_address, sizeof(sprite_address));
        sprite_lookup[5] = 0xC3;
        auto* native_zero = reinterpret_cast<float*>(mapped_image_base + 0x16e0e8);
        const float native_zero_original = *native_zero;
        *native_zero = 200.0f;
        // Isolate the mesh deformation body from RenderMesh initialization; the
        // source-side RenderMesh::initialize test seam is the same no-op.
        auto* mesh_initialize = reinterpret_cast<std::uint8_t*>(mapped_image_base + 0x9d850);
        mesh_initialize[0] = 0xc2;
        mesh_initialize[1] = 0x10;
        mesh_initialize[2] = 0x00;
        *reinterpret_cast<void**>(mapped_image_base + 0x1c0028) =
            &th20::test_view_index_owner;

        std::mt19937 random(0x4751b0);
        unsigned checks = 0, failed = 0;
        std::vector<std::string> failures;
        std::map<std::string, unsigned> groups;
        auto finite = [&]() {
            return float(static_cast<int>(random() % 200000) - 100000) / 127.0f;
        };
        auto bits = [&]() { return std::bit_cast<std::uint32_t>(finite()); };

        auto prepare = [&](th20::StageBackgroundScriptState& state) {
            state.instruction_offset = 0;
            state.camera_motion = 0;
            state.timer.previous = 0;
            state.timer.current = 0;
            state.timer.current_fraction = 0.0f;
            state.timer.flags = 0;
            for (auto* value = reinterpret_cast<float*>(&state.camera);
                 value != reinterpret_cast<float*>(&state.camera) + sizeof(state.camera) / 4;
                 ++value)
                *value = finite();
            auto interpolation = [&](auto& value) {
                for (auto* field = reinterpret_cast<float*>(&value);
                     field != reinterpret_cast<float*>(&value.timer); ++field)
                    *field = finite();
                value.mode = random() % 34;
                value.duration = 0;
                value.timer.previous = -1;
                value.timer.current = static_cast<std::int32_t>(random() % 100);
                value.timer.current_fraction = finite();
                value.timer.flags = random() % 8;
            };
            interpolation(state.direction_interpolation);
            interpolation(state.position_interpolation);
            interpolation(state.up_interpolation);
            interpolation(state.fog_interpolation);
            interpolation(state.fov_interpolation);
            for (auto& animation : state.animations) {
                animation.base.flags.byte_02 = static_cast<std::uint8_t>(random());
                animation.base.field_28 = static_cast<std::int32_t>(random());
            }
            for (auto& value : state.fields_3294) value = random();
        };

        auto compare = [&](const std::string& label,
                           std::vector<std::uint32_t> code,
                           const std::function<void(th20::StageBackgroundScriptState&)>& initialize,
                           unsigned ticks = 1) {
            alignas(th20::StageResourceOwner)
                std::uint8_t owner_storage[sizeof(th20::StageResourceOwner)]{};
            auto& owner = *::new (owner_storage) th20::StageResourceOwner{};
            owner.instructions = reinterpret_cast<const th20::StageResourceInstructionHeader*>(
                code.data());
            std::array<th20::Animation, 2> primitive_animations{};
            for (auto& animation : primitive_animations)
                animation.base.flags.word_1c = 1;
            th20::StageResourceFileHeader file{};
            file.animation_count = static_cast<std::int16_t>(primitive_animations.size());
            owner.primitive_animations = primitive_animations.data();
            owner.file = &file;
            th20::process_stage_resource = &owner;

            auto& state = owner.script_state;
            prepare(state);
            state.owner = &owner;
            initialize(state);
            // Native Animation::update returns immediately when this gate is set.
            // That isolates the event write and both owner traversal loops without
            // substituting the nontrivial 39KB animation VM.
            for (auto& animation : state.animations)
                animation.base.flags.word_1c = 1;
            if (label == "opcode_17") {
                state.fields_3294[9] = 0;
                state.fields_3294[10] = 0;
                for (unsigned index = 0; index < 2; ++index) {
                    state.mesh_timers[index].previous = static_cast<std::int32_t>(random());
                    state.mesh_timers[index].current = static_cast<std::int32_t>(random());
                    state.mesh_timers[index].current_fraction = finite();
                    state.mesh_timers[index].flags = random();
                    state.mesh_phase_x[index] = finite();
                    state.mesh_phase_y[index] = finite();
                }
            }
            const float rate_value = float(random() % 5) * 0.5f;
            const float* rate = random() % 6 ? &rate_value : nullptr;
            th20::ClockScalar source_rate{};
            if (rate != nullptr) source_rate.set(*rate);
            th20::timer_clock_sources[0] = rate != nullptr ? &source_rate : nullptr;
            *reinterpret_cast<const float**>(mapped_image_base + 0x1aefe0) = rate;
            *reinterpret_cast<void**>(mapped_image_base + 0x1c069c) = &owner;

            std::array<std::uint8_t, sizeof(state)> before{}, expected{};
            std::array<std::uint8_t, sizeof(th20::Animation) * 2> primitive_before{}, primitive_expected{};
            const auto initial_view_index = static_cast<std::int32_t>(random());
            th20::test_view_index_owner.view_index_6c4 = initial_view_index;
            for (unsigned tick = 0; tick < ticks; ++tick) {
                std::memcpy(before.data(), &state, sizeof(state));
                std::memcpy(primitive_before.data(), primitive_animations.data(), primitive_before.size());
                const auto initial_flags = random();
                const auto initial_color = random();
                owner.state_flags = initial_flags;
                th20::test_view_index_owner.view_index_6c4 = initial_view_index;
                *reinterpret_cast<std::uint32_t*>(mapped_image_base + 0x1c5b20) = initial_color;

                FloatingEnvironment::prepare();
                cpu<void>(0x004751b0, &state);
                std::memcpy(expected.data(), &state, sizeof(state));
                std::memcpy(primitive_expected.data(), primitive_animations.data(), primitive_expected.size());
                const auto expected_flags = owner.state_flags;
                const auto expected_view_index = th20::test_view_index_owner.view_index_6c4;
                const auto expected_color = *reinterpret_cast<std::uint32_t*>(
                    mapped_image_base + 0x1c5b20);

                std::memcpy(&state, before.data(), sizeof(state));
                std::memcpy(primitive_animations.data(), primitive_before.data(), primitive_before.size());
                owner.state_flags = initial_flags;
                th20::test_view_index_owner.view_index_6c4 = initial_view_index;
                source_clear_color = initial_color;
                FloatingEnvironment::prepare();
                state.execute_script();

                ++checks;
                ++groups[label];
                std::string why;
                for (unsigned index = 0; index < sizeof(state); ++index) {
                    const auto actual = reinterpret_cast<const std::uint8_t*>(&state)[index];
                    if (expected[index] != actual) {
                        std::ostringstream error;
                        error << " +0x" << std::hex << index
                              << " original=" << unsigned(expected[index])
                              << " source=" << unsigned(actual);
                        why = error.str();
                        break;
                    }
                }
                if (std::memcmp(primitive_animations.data(), primitive_expected.data(), primitive_expected.size()) != 0)
                    why += " primitive animation array";
                if (owner.state_flags != expected_flags) why += " rotation global";
                if (th20::test_view_index_owner.view_index_6c4 != expected_view_index) why += " view index global";
                if (source_clear_color != expected_color) why += " clear color global";
                if (!why.empty()) {
                    ++failed;
                    if (failures.size() < 30) {
                        failures.push_back(label + " tick" + std::to_string(tick) + why);
                        std::cerr << failures.back() << '\n';
                    }
                }
            }
            th20::timer_clock_sources[0] = &th20::default_timer_clock;
            th20::process_stage_resource = nullptr;
            *reinterpret_cast<const float**>(mapped_image_base + 0x1aefe0) = nullptr;
            *reinterpret_cast<void**>(mapped_image_base + 0x1c069c) = nullptr;
        };


        auto compare_owner_update = [&](unsigned test, std::uint32_t flags,
                                        std::int32_t fade_time, std::uint32_t mesh_mode) {
            alignas(th20::StageResourceOwner)
                std::uint8_t owner_storage[sizeof(th20::StageResourceOwner)]{};
            auto& owner = *::new (owner_storage) th20::StageResourceOwner{};
            auto code = instruction(0, {}, 100000);
            owner.instructions = reinterpret_cast<const th20::StageResourceInstructionHeader*>(
                code.data());
            std::array<th20::Animation, 2> primitive_animations{};
            for (auto& animation : primitive_animations)
                animation.base.flags.word_1c = 1;
            th20::StageResourceFileHeader file{};
            file.object_count = 0;
            file.animation_count = static_cast<std::int16_t>(primitive_animations.size());
            owner.primitive_animations = primitive_animations.data();
            owner.file = &file;
            owner.objects = nullptr;
            th20::process_stage_resource = &owner;

            auto& state = owner.script_state;
            prepare(state);
            state.owner = &owner;
            state.mesh_mode = mesh_mode;
            for (auto& animation : state.animations)
                animation.base.flags.word_1c = 1;
            alignas(th20::RenderMesh) std::uint8_t mesh_storage[2][sizeof(th20::RenderMesh)]{};
            alignas(th20::SpriteTexturedVertex) std::uint8_t vertex_storage[2][9 * sizeof(th20::SpriteTexturedVertex)]{};
            alignas(th20::Vector3) std::uint8_t position_storage[2][9 * sizeof(th20::Vector3)]{};
            alignas(th20::SpriteTexturedVertex) std::uint8_t strip_storage[2][2 * 6 * sizeof(th20::SpriteTexturedVertex)]{};
            std::array<std::array<th20::Animation, 2>, 2> strip_animations{};
            std::array<std::array<th20::Animation*, 2>, 2> strip_tables{};
            for (unsigned index = 0; index < 2; ++index) {
                *reinterpret_cast<std::int32_t*>(mesh_storage[index]) = 3;
                *reinterpret_cast<std::int32_t*>(mesh_storage[index] + 4) = 3;
                *reinterpret_cast<th20::Animation***>(mesh_storage[index] + 0x10) =
                    strip_tables[index].data();
                *reinterpret_cast<th20::SpriteTexturedVertex**>(mesh_storage[index] + 0x14) =
                    reinterpret_cast<th20::SpriteTexturedVertex*>(vertex_storage[index]);
                *reinterpret_cast<th20::Vector3**>(mesh_storage[index] + 0x18) =
                    reinterpret_cast<th20::Vector3*>(position_storage[index]);
                auto* vertices = reinterpret_cast<th20::SpriteTexturedVertex*>(vertex_storage[index]);
                auto* positions = reinterpret_cast<th20::Vector3*>(position_storage[index]);
                for (unsigned column = 0; column < 2; ++column) {
                    strip_tables[index][column] = &strip_animations[index][column];
                    strip_animations[index][column].geometry = strip_storage[index] +
                        column * 6 * sizeof(th20::SpriteTexturedVertex);
                }
                for (unsigned vertex_index = 0; vertex_index < 9; ++vertex_index) {
                    vertices[vertex_index].position.x = finite();
                    vertices[vertex_index].position.y = finite();
                    vertices[vertex_index].position.z = finite();
                    vertices[vertex_index].reciprocal_w = finite();
                    vertices[vertex_index].color = random();
                    vertices[vertex_index].u = finite();
                    vertices[vertex_index].v = finite();
                    positions[vertex_index].x = finite();
                    positions[vertex_index].y = finite();
                    positions[vertex_index].z = finite();
                }
                state.fields_3294[9 + index] = static_cast<std::uint32_t>(
                    reinterpret_cast<std::uintptr_t>(mesh_storage[index]));
                state.mesh_phase_x[index] = float(random() % 6284u) / 1000.0f - 3.1415927f;
                state.mesh_phase_y[index] = float(random() % 6284u) / 1000.0f - 3.1415927f;
                state.mesh_timers[index].previous = static_cast<std::int32_t>(random());
                state.mesh_timers[index].current = static_cast<std::int32_t>(random());
                state.mesh_timers[index].current_fraction = finite();
                state.mesh_timers[index].flags = random();
            }
            owner.frame_count = random();
            owner.state_flags = flags;
            owner.fade_timer.previous = fade_time - 1;
            owner.fade_timer.current = fade_time;
            owner.fade_timer.current_fraction = static_cast<float>(fade_time) + 0.25f;
            owner.fade_timer.flags = 1;

            const float rate_value = float(random() % 5) * 0.5f;
            th20::ClockScalar source_rate{rate_value};
            th20::timer_clock_sources[0] = &source_rate;
            *reinterpret_cast<const float**>(mapped_image_base + 0x1aefe0) = &rate_value;
            *reinterpret_cast<void**>(mapped_image_base + 0x1c069c) = &owner;

            std::array<std::uint8_t, sizeof(owner)> owner_before{}, owner_expected{};
            std::array<std::uint8_t, sizeof(primitive_animations)> primitive_before{}, primitive_expected{};
            std::array<std::uint8_t, sizeof(mesh_storage)> mesh_before{}, mesh_expected{};
            std::array<std::uint8_t, sizeof(vertex_storage)> vertices_before{}, vertices_expected{};
            std::array<std::uint8_t, sizeof(position_storage)> positions_before{}, positions_expected{};
            std::array<std::uint8_t, sizeof(strip_storage)> strips_before{}, strips_expected{};
            std::array<std::uint8_t, sizeof(strip_animations)> strip_animations_before{}, strip_animations_expected{};
            std::array<std::uint8_t, sizeof(th20::ViewportState)> viewport_before{}, viewport_expected{};
            for (unsigned index = 0; index < viewport_before.size(); ++index)
                viewport_before[index] = static_cast<std::uint8_t>(random());
            std::memcpy(&th20::source_camera_viewport, viewport_before.data(), viewport_before.size());
            std::memcpy(reinterpret_cast<void*>(mapped_image_base + 0x1c53fc),
                        viewport_before.data(), viewport_before.size());
            std::memcpy(owner_before.data(), &owner, sizeof(owner));
            std::memcpy(primitive_before.data(), primitive_animations.data(), primitive_before.size());
            std::memcpy(mesh_before.data(), mesh_storage, mesh_before.size());
            std::memcpy(vertices_before.data(), vertex_storage, vertices_before.size());
            std::memcpy(positions_before.data(), position_storage, positions_before.size());
            std::memcpy(strips_before.data(), strip_storage, strips_before.size());
            std::memcpy(strip_animations_before.data(), strip_animations.data(), strip_animations_before.size());

            for (unsigned tick = 0; tick < 3; ++tick) {
                std::memcpy(&owner, owner_before.data(), sizeof(owner));
                std::memcpy(primitive_animations.data(), primitive_before.data(), primitive_before.size());
                std::memcpy(mesh_storage, mesh_before.data(), mesh_before.size());
                std::memcpy(vertex_storage, vertices_before.data(), vertices_before.size());
                std::memcpy(position_storage, positions_before.data(), positions_before.size());
                std::memcpy(strip_storage, strips_before.data(), strips_before.size());
                std::memcpy(strip_animations.data(), strip_animations_before.data(), strip_animations_before.size());
                std::memcpy(reinterpret_cast<void*>(mapped_image_base + 0x1c53fc),
                            viewport_before.data(), viewport_before.size());
                owner.state_flags = flags;
                owner.fade_timer.previous = fade_time - 1;
                owner.fade_timer.current = fade_time;
                owner.fade_timer.current_fraction = static_cast<float>(fade_time) + 0.25f;
                owner.fade_timer.flags = 1;

                FloatingEnvironment::prepare();
                const auto expected_return = cpu<std::int32_t>(0x00472100, &owner);
                std::memcpy(owner_expected.data(), &owner, sizeof(owner));
                std::memcpy(primitive_expected.data(), primitive_animations.data(), primitive_expected.size());
                std::memcpy(mesh_expected.data(), mesh_storage, mesh_expected.size());
                std::memcpy(vertices_expected.data(), vertex_storage, vertices_expected.size());
                std::memcpy(positions_expected.data(), position_storage, positions_expected.size());
                std::memcpy(strips_expected.data(), strip_storage, strips_expected.size());
                std::memcpy(strip_animations_expected.data(), strip_animations.data(), strip_animations_expected.size());
                std::memcpy(viewport_expected.data(),
                            reinterpret_cast<const void*>(mapped_image_base + 0x1c53fc),
                            viewport_expected.size());
                std::memcpy(&owner, owner_before.data(), sizeof(owner));
                std::memcpy(primitive_animations.data(), primitive_before.data(), primitive_before.size());
                std::memcpy(mesh_storage, mesh_before.data(), mesh_before.size());
                std::memcpy(vertex_storage, vertices_before.data(), vertices_before.size());
                std::memcpy(position_storage, positions_before.data(), positions_before.size());
                std::memcpy(strip_storage, strips_before.data(), strips_before.size());
                std::memcpy(strip_animations.data(), strip_animations_before.data(), strip_animations_before.size());
                std::memcpy(&th20::source_camera_viewport, viewport_before.data(), viewport_before.size());
                owner.state_flags = flags;
                owner.fade_timer.previous = fade_time - 1;
                owner.fade_timer.current = fade_time;
                owner.fade_timer.current_fraction = static_cast<float>(fade_time) + 0.25f;
                owner.fade_timer.flags = 1;
                FloatingEnvironment::prepare();
                const auto source_return = owner.update();
                ++checks;
                ++groups["stage_owner_update"];
                std::string why;
                if (expected_return != source_return) why += " return";
                if (std::memcmp(&owner, owner_expected.data(), owner_expected.size()) != 0)
                    why += " owner bytes";
                if (std::memcmp(primitive_animations.data(), primitive_expected.data(), primitive_expected.size()) != 0)
                    why += " primitive animations";
                if (std::memcmp(mesh_storage, mesh_expected.data(), mesh_expected.size()) != 0)
                    why += " mesh records";
                if (std::memcmp(vertex_storage, vertices_expected.data(), vertices_expected.size()) != 0) {
                    for (unsigned index = 0; index < vertices_expected.size(); ++index) {
                        if (reinterpret_cast<const std::uint8_t*>(vertex_storage)[index] != vertices_expected[index]) {
                            std::ostringstream error;
                            const auto* original_bytes = vertices_expected.data() + index - (index % 4);
                            const auto* source_bytes = reinterpret_cast<const std::uint8_t*>(vertex_storage) + index - (index % 4);
                            std::uint32_t original_bits = 0, source_bits = 0;
                            std::memcpy(&original_bits, original_bytes, 4);
                            std::memcpy(&source_bits, source_bytes, 4);
                            error << " mesh vertices+0x" << std::hex << index
                                  << " original=" << unsigned(vertices_expected[index])
                                  << " source=" << unsigned(reinterpret_cast<const std::uint8_t*>(vertex_storage)[index])
                                  << " floatbits=" << original_bits << "/" << source_bits
                                  << std::dec << " floats=" << std::bit_cast<float>(original_bits)
                                  << "/" << std::bit_cast<float>(source_bits);
                            why += error.str();
                            break;
                        }
                    }
                }
                if (std::memcmp(position_storage, positions_expected.data(), positions_expected.size()) != 0)
                    why += " mesh positions";
                if (std::memcmp(strip_storage, strips_expected.data(), strips_expected.size()) != 0 ||
                    std::memcmp(strip_animations.data(), strip_animations_expected.data(), strip_animations_expected.size()) != 0)
                    why += " mesh strip publication";
                if (std::memcmp(&th20::source_camera_viewport, viewport_expected.data(), viewport_expected.size()) != 0)
                    why += " Graphics::viewports[3]";
                if (!why.empty()) {
                    ++failed;
                    if (failures.size() < 30) {
                        failures.push_back("stage_owner_update test" + std::to_string(test) +
                                           " tick" + std::to_string(tick) + why);
                        std::cerr << failures.back() << '\n';
                    }
                }
            }
            th20::timer_clock_sources[0] = &th20::default_timer_clock;
            th20::process_stage_resource = nullptr;
            *reinterpret_cast<const float**>(mapped_image_base + 0x1aefe0) = nullptr;
            *reinterpret_cast<void**>(mapped_image_base + 0x1c069c) = nullptr;
        };

        auto compare_object_update = [&](unsigned test) {
            alignas(th20::StageResourceOwner)
                std::uint8_t owner_storage[sizeof(th20::StageResourceOwner)]{};
            auto& owner = *::new (owner_storage) th20::StageResourceOwner{};
            th20::StageResourceFileHeader file{};
            file.object_count = static_cast<std::int16_t>(1 + (test % 3));
            owner.file = &file;

            struct ObjectWithPrimitives {
                th20::StageResourceObjectRecord object;
                std::byte primitive_data[32];
            };
            std::array<ObjectWithPrimitives, 3> records{};
            std::array<th20::StageResourceObjectRecord*, 3> object_table{};
            for (unsigned index = 0; index < records.size(); ++index) {
                object_table[index] = &records[index].object;
                records[index].object.identifier = static_cast<std::uint16_t>(index + 10);
                records[index].object.layer = static_cast<std::int8_t>(random());
                records[index].object.flags = static_cast<std::int8_t>(random());
                auto& parameters = records[index].object.parameters;
                parameters.projected_bounds_bypass =
                    std::bit_cast<std::uint32_t>(finite());
                parameters.rotation_y_velocity =
                    std::array<float, 8>{0.0f, -0.0f, 0.125f, -0.75f,
                                         3.1415927f, -3.1415927f, 19.0f,
                                         std::bit_cast<float>(0x7fc00000u)}[test % 8];
                parameters.rotation_y =
                    std::array<float, 8>{0.0f, 3.0f, -3.0f, 100.0f,
                                         -100.0f, 6.2831855f, 1.0f,
                                         std::bit_cast<float>(0x7fc00000u)}[(test + index) % 8];
                parameters.field_0c = finite();
                parameters.field_10 = finite();
                parameters.bounds_center = {finite(), finite(), finite()};
                parameters.bounds_extent = {finite(), finite(), finite()};
                std::memset(records[index].primitive_data, 0,
                            sizeof(records[index].primitive_data));
            }
            auto write_primitive = [&](unsigned object_index, unsigned offset,
                                       th20::StageResourcePrimitiveHeader primitive) {
                std::memcpy(records[object_index].primitive_data + offset,
                            &primitive, sizeof(primitive));
            };
            records[0].object.flags |= th20::StageResourceObjectRecord::has_active_animations_mask;
            write_primitive(0, 0, {0, 12, 4, 0});
            write_primitive(0, 12, {1, 8, 5, 1});
            write_primitive(0, 20, {-1, 0, 0, 0});
            records[1].object.flags |= th20::StageResourceObjectRecord::has_active_animations_mask;
            write_primitive(1, 0, {0, 16, 6, 2});
            write_primitive(1, 16, {-1, 0, 0, 0});
            write_primitive(2, 0, {-1, 0, 0, 0});
            owner.objects = object_table.data();

            std::array<th20::Animation, 3> primitive_animations{};
            for (unsigned index = 0; index < primitive_animations.size(); ++index) {
                primitive_animations[index].base.flags.word_1c = 1;
                primitive_animations[index].base.field_28 =
                    (test + index) % 3 == 0 ? -1 : static_cast<std::int32_t>(test + index);
            }
            owner.primitive_animations = primitive_animations.data();
            owner.state_flags = (test & 1u) ? 16u : 0u;
            const auto expected_flags = owner.state_flags;
            std::array<std::uint8_t, sizeof(records)> records_before{}, records_expected{};
            std::array<std::uint8_t, sizeof(primitive_animations)> animations_before{}, animations_expected{};
            std::memcpy(records_before.data(), records.data(), records_before.size());
            std::memcpy(animations_before.data(), primitive_animations.data(), animations_before.size());

            FloatingEnvironment::prepare();
            const auto expected_return = cpu<std::int32_t>(0x004739e0, &owner);
            std::memcpy(records_expected.data(), records.data(), records_expected.size());
            std::memcpy(animations_expected.data(), primitive_animations.data(), animations_expected.size());

            std::memcpy(records.data(), records_before.data(), records_before.size());
            std::memcpy(primitive_animations.data(), animations_before.data(), animations_before.size());
            owner.state_flags = expected_flags;
            FloatingEnvironment::prepare();
            const auto source_return = owner.update_objects();

            ++checks;
            ++groups["stage_object_update"];
            std::string why;
            if (expected_return != source_return) why += " return";
            if (std::memcmp(records.data(), records_expected.data(), records_expected.size()) != 0)
                why += " object records/primitive flags/rotation";
            if (std::memcmp(primitive_animations.data(), animations_expected.data(), animations_expected.size()) != 0)
                why += " primitive animations";
            if (!why.empty()) {
                ++failed;
                if (failures.size() < 30) {
                    failures.push_back("stage_object_update test" + std::to_string(test) + why);
                    std::cerr << failures.back() << '\n';
                }
            }
        };

        for (unsigned test = 0; test < 12; ++test) {
            compare_object_update(test);
        }

        auto compare_matrix_identity = [&](unsigned test) {
            th20::Matrix4 matrix{};
            for (unsigned row = 0; row < 4; ++row)
                for (unsigned column = 0; column < 4; ++column)
                    matrix.elements[row][column] = std::bit_cast<float>(bits());
            std::array<std::uint8_t, sizeof(matrix)> before{}, expected{};
            std::memcpy(before.data(), &matrix, before.size());

            FloatingEnvironment::prepare();
            auto* expected_return = cpu_cdecl<th20::Matrix4*>(0x00472840, &matrix);
            std::memcpy(expected.data(), &matrix, expected.size());

            std::memcpy(&matrix, before.data(), before.size());
            FloatingEnvironment::prepare();
            auto* source_return = th20::matrix_identity(&matrix);

            ++checks;
            ++groups["matrix_identity"];
            if (expected_return != source_return ||
                std::memcmp(&matrix, expected.data(), expected.size()) != 0) {
                ++failed;
                if (failures.size() < 30) {
                    failures.push_back("matrix_identity test" + std::to_string(test));
                    std::cerr << failures.back() << '\n';
                }
            }
        };

        auto compare_animation_flag_clear = [&](unsigned test) {
            th20::Animation animation{};
            auto* bytes = reinterpret_cast<std::uint8_t*>(&animation);
            for (unsigned index = 0; index < sizeof(animation); ++index)
                bytes[index] = static_cast<std::uint8_t>(random());
            std::array<std::uint8_t, sizeof(animation)> before{}, expected{};
            std::memcpy(before.data(), &animation, before.size());

            FloatingEnvironment::prepare();
            cpu<void>(0x00472a10, &animation);
            std::memcpy(expected.data(), &animation, expected.size());

            std::memcpy(&animation, before.data(), before.size());
            FloatingEnvironment::prepare();
            animation.clear_flag_02();

            ++checks;
            ++groups["animation_clear_flag_02"];
            if (std::memcmp(&animation, expected.data(), expected.size()) != 0) {
                ++failed;
                if (failures.size() < 30) {
                    failures.push_back("animation_clear_flag_02 test" + std::to_string(test));
                    std::cerr << failures.back() << '\n';
                }
            }
        };

        for (unsigned test = 0; test < 128; ++test) {
            compare_matrix_identity(test);
            compare_animation_flag_clear(test);
        }

        auto compare_stage_object_culling = [&](unsigned test) {
            th20::StageResourceObjectRecord object{};
            th20::ViewportState viewport{};
            th20::Matrix4 view{}, projection{};
            th20::matrix_identity(&view);
            th20::matrix_identity(&projection);
            const float jitter = static_cast<float>(static_cast<int>(test % 9) - 4) * 0.025f;
            view.elements[3][0] = jitter;
            view.elements[3][1] = -jitter;
            projection.elements[0][0] = 0.75f + static_cast<float>(test % 5) * 0.05f;
            projection.elements[1][1] = 0.8f + static_cast<float>(test % 4) * 0.05f;
            projection.elements[2][2] = 0.9f;
            std::memcpy(&viewport.view, &view, sizeof(view));
            std::memcpy(&viewport.projection, &projection, sizeof(projection));
            viewport.vector_00 = {0.0f, 0.0f, 0.0f};
            viewport.vector_3c = {jitter, 0.0f, 0.0f};
            viewport.viewport = {static_cast<std::uint32_t>(test % 3) * 16u,
                                 static_cast<std::uint32_t>(test % 2) * 8u,
                                 test % 2 ? 640u : 320u,
                                 test % 3 ? 480u : 240u, 0.0f, 1.0f};

            th20::Vector3 position{}, extent{}, instance_offset{};
            float max_distance_squared = 100.0f;
            std::int32_t bypass_bounds = 0;
            switch (test % 12) {
            case 0: position = {0.0f, 0.0f, 0.5f}; extent = {0.2f, 0.2f, 0.2f}; break;
            case 1: position = {2.0f, 0.0f, 0.5f}; extent = {0.1f, 0.1f, 0.1f}; break;
            case 2: position = {1.05f, 0.0f, 0.5f}; extent = {0.2f, 0.2f, 0.2f}; break;
            case 3: position = {0.0f, 0.0f, 2.0f}; extent = {0.1f, 0.1f, 0.1f}; break;
            case 4: position = {0.0f, 0.0f, -1.0f}; extent = {0.1f, 0.1f, 0.1f}; break;
            case 5: position = {0.5f, 0.0f, 0.5f}; extent = {0.1f, 0.1f, 0.1f}; max_distance_squared = 0.0f; break;
            case 6: position = {2.0f, 0.0f, 0.5f}; extent = {0.1f, 0.1f, 0.1f}; bypass_bounds = 1; break;
            case 7: position = {0.0f, 2.0f, 0.5f}; extent = {0.1f, 0.1f, 0.1f}; break;
            case 8: position = {0.0f, 0.0f, 0.5f}; extent = {2.0f, 2.0f, 2.0f}; break;
            case 9: position = {0.0f, 0.0f, 0.5f}; extent = {0.0f, 0.0f, 0.0f}; break;
            case 10: position = {0.0f, 0.0f, 0.5f}; extent = {0.1f, 0.1f, 0.1f}; instance_offset = {10.0f, 0.0f, 0.0f}; max_distance_squared = 100.0f; break;
            default: position = {-1.05f, 0.0f, 0.5f}; extent = {0.2f, 0.2f, 0.2f}; break;
            }
            if (test >= 12) {
                auto sample = [&]() { return static_cast<float>(static_cast<int>(random() % 6001u) - 3000) / 1000.0f; };
                position = {sample(), sample(), static_cast<float>(random() % 1001u) / 1000.0f};
                extent = {static_cast<float>(random() % 1000u) / 1000.0f,
                          static_cast<float>(random() % 1000u) / 1000.0f,
                          static_cast<float>(random() % 1000u) / 1000.0f};
                instance_offset = {sample() * 0.25f, sample() * 0.25f, sample() * 0.25f};
                max_distance_squared = test % 3 ? 100.0f : 0.5f;
                bypass_bounds = test % 5 == 0 ? 1 : 0;
            }
            object.parameters.projected_bounds_bypass =
                static_cast<std::uint32_t>(bypass_bounds);
            object.parameters.bounds_center = position;
            object.parameters.bounds_extent = extent;

            // The surrounding VM oracle uses 200 in this shared global to
            // suppress unrelated geometry paths; restore the PE's real zero
            // while this function's depth and edge clipping are compared.
            *native_zero = native_zero_original;
            FloatingEnvironment::prepare();
            const auto expected = cpu<std::int32_t>(0x00473b20, &object,
                &instance_offset, max_distance_squared, &viewport);
            FloatingEnvironment::prepare();
            const auto actual = object.is_outside_viewport(
                instance_offset, max_distance_squared, viewport);
            *native_zero = 200.0f;
            ++checks;
            ++groups["stage_object_viewport_culling"];
            if (expected != actual) {
                ++failed;
                if (failures.size() < 30) {
                    std::ostringstream error;
                    error << "stage_object_viewport_culling test" << test
                          << " expected=" << expected << " actual=" << actual;
                    failures.push_back(error.str());
                    std::cerr << failures.back() << '\n';
                }
            }
        };
        for (unsigned test = 0; test < 1024; ++test)
            compare_stage_object_culling(test);
        *native_zero = 200.0f;

        {
            constexpr std::size_t sparse_extent = 0x07D42000u;
            constexpr std::array<std::size_t, 3> page_offsets{
                0u, 0x06000E00u, 0x07D40E00u};
            auto* storage = static_cast<std::uint8_t*>(
                VirtualAlloc(nullptr, sparse_extent, MEM_RESERVE, PAGE_NOACCESS));
            if (!storage)
                throw std::runtime_error("cannot reserve sparse AnimationPool draw-reset fixture");
            for (const auto offset : page_offsets) {
                if (!VirtualAlloc(storage + offset, 0x1000, MEM_COMMIT, PAGE_READWRITE)) {
                    VirtualFree(storage, 0, MEM_RELEASE);
                    throw std::runtime_error("cannot commit sparse AnimationPool draw-reset page");
                }
            }
            std::array<std::array<std::uint8_t, 0x1000>, 3> before{}, expected{}, actual{};
            for (unsigned test = 0; test < 128; ++test) {
                for (std::size_t page = 0; page < page_offsets.size(); ++page) {
                    for (auto& byte : before[page])
                        byte = static_cast<std::uint8_t>(random());
                    std::memcpy(storage + page_offsets[page], before[page].data(), 0x1000);
                }
                FloatingEnvironment::prepare();
                cpu<void>(0x004750a0, storage);
                for (std::size_t page = 0; page < page_offsets.size(); ++page)
                    std::memcpy(expected[page].data(), storage + page_offsets[page], 0x1000);
                for (std::size_t page = 0; page < page_offsets.size(); ++page)
                    std::memcpy(storage + page_offsets[page], before[page].data(), 0x1000);
                FloatingEnvironment::prepare();
                reinterpret_cast<th20::NativeAnimationResetHooks*>(storage)
                    ->reset_after_stage_draw_4750a0();
                for (std::size_t page = 0; page < page_offsets.size(); ++page)
                    std::memcpy(actual[page].data(), storage + page_offsets[page], 0x1000);
                ++checks;
                ++groups["animation_pool_stage_draw_reset"];
                if (actual != expected) {
                    ++failed;
                    if (failures.size() < 30) {
                        failures.push_back("animation_pool_stage_draw_reset test" +
                                           std::to_string(test));
                        std::cerr << failures.back() << '\n';
                    }
                }
            }
            VirtualFree(storage, 0, MEM_RELEASE);
        }

        {
            struct ObjectFixture {
                th20::StageResourceObjectRecord object;
                std::uint8_t primitive_stream[96];
            };
            static_assert(offsetof(ObjectFixture, primitive_stream) == 0x30);

            constexpr std::size_t sparse_extent = 0x07D42000u;
            constexpr std::array<std::size_t, 3> page_offsets{
                0u, 0x06000E00u, 0x07D40E00u};
            auto* pool_storage = static_cast<std::uint8_t*>(
                VirtualAlloc(nullptr, sparse_extent, MEM_RESERVE, PAGE_NOACCESS));
            if (!pool_storage)
                throw std::runtime_error("cannot reserve sparse AnimationPool object-draw fixture");
            for (const auto offset : page_offsets) {
                if (!VirtualAlloc(pool_storage + offset, 0x1000,
                                  MEM_COMMIT, PAGE_READWRITE)) {
                    VirtualFree(pool_storage, 0, MEM_RELEASE);
                    throw std::runtime_error("cannot commit sparse AnimationPool object-draw page");
                }
            }

            auto write_primitive = [](ObjectFixture& fixture, std::size_t offset,
                                      std::int16_t type, std::int16_t size,
                                      std::int16_t animation_index,
                                      const th20::Vector3& position,
                                      float scale_x, float scale_y) {
                auto* header = reinterpret_cast<th20::StageResourcePrimitiveHeader*>(
                    fixture.primitive_stream + offset);
                header->type = type;
                header->size = size;
                header->script_index = 0;
                header->animation_index = animation_index;
                if (type == 0) {
                    auto* values = reinterpret_cast<float*>(
                        fixture.primitive_stream + offset + sizeof(*header));
                    values[0] = position.x;
                    values[1] = position.y;
                    values[2] = position.z;
                    values[3] = scale_x;
                    values[4] = scale_y;
                }
            };
            auto initialize_fixture = [&](th20::StageResourceOwner& owner,
                                          std::array<ObjectFixture, 3>& fixtures,
                                          std::array<th20::StageResourceObjectRecord*, 3>& table,
                                          std::array<th20::StageResourceInstanceRecord, 5>& instances,
                                          std::array<th20::Animation, 8>& animations,
                                          unsigned test) {
                owner.primitive_animations = animations.data();
                owner.objects = table.data();
                owner.instances = instances.data();
                owner.rendered[0] = 3 + test;
                owner.rendered[1] = 5 + test * 2;
                owner.rendered[2] = 7 + test * 3;
                constexpr std::array<float, 4> cull_distance_squared{
                    0.0f, 5000.0f, 10000.0f,
                    std::bit_cast<float>(0x7f7fffffu)};
                owner.script_state.fields_3294[8] =
                    std::bit_cast<std::uint32_t>(
                        cull_distance_squared[test & 3u]);

                for (unsigned index = 0; index < 8; ++index) {
                    owner.script_state.fields_3294[index] =
                        index < 2 || index == 3 ? 8u : 9u;
                    auto& inline_animation = owner.script_state.animations[index];
                    inline_animation.base.flags.bytes_00.animation_mode =
                        index & 1u ? 24u : 8u;
                    inline_animation.base.flags.word_04 = index & 1u ? 0x10u : 0u;
                    inline_animation.base.vector_38.y =
                        static_cast<float>(index) * 0.125f;
                }

                for (unsigned index = 0; index < animations.size(); ++index) {
                    auto* bytes = reinterpret_cast<std::uint8_t*>(&animations[index]);
                    for (unsigned byte = 0; byte < sizeof(animations[index]); ++byte)
                        bytes[byte] = static_cast<std::uint8_t>(random());
                    constexpr std::array<std::uint8_t, 12> animation_modes{
                        0, 3, 4, 5, 7, 8, 9, 23, 24, 25, 127, 255};
                    animations[index].base.flags.bytes_00.animation_mode =
                        animation_modes[(test + index) % animation_modes.size()];
                    animations[index].base.flags.word_04 =
                        index & 1u ? 0x10u : 0x20u;
                    animations[index].base.vector_38.y =
                        static_cast<float>(static_cast<int>(index) - 3) * 0.17f;
                }

                for (unsigned index = 0; index < fixtures.size(); ++index) {
                    fixtures[index] = {};
                    fixtures[index].object.identifier =
                        static_cast<std::uint16_t>(index + 1);
                    fixtures[index].object.layer =
                        static_cast<std::int8_t>(
                            index == 2 ? 9 : index == 1 ? -1 : 8);
                    fixtures[index].object.flags =
                        static_cast<std::uint8_t>(random());
                    fixtures[index].object.parameters.projected_bounds_bypass =
                        index == 0 && test % 7 == 0 ? 1u : 0u;
                    fixtures[index].object.parameters.bounds_center = {
                        index == 1 ? 0.25f : -0.15f, 0.0f, 0.5f};
                    fixtures[index].object.parameters.bounds_extent = {
                        0.35f, 0.3f, 0.25f};
                    fixtures[index].object.parameters.rotation_y =
                        index == 0 && test % 4 != 0 ?
                            (test & 1u ? 0.35f : -0.6f) : 0.0f;
                    table[index] = &fixtures[index].object;
                }

                write_primitive(fixtures[0], 0, 0, 28, 0,
                                {0.25f, 0.1f, 0.05f},
                                test & 1u ? 12.0f : 0.0f, 20.0f);
                constexpr std::array<std::int16_t, 4> unknown_primitive_kinds{
                    1, 2, 7, 0x7fff};
                constexpr std::array<std::int16_t, 4> unknown_primitive_sizes{
                    8, 12, 16, 20};
                const auto unknown_kind =
                    unknown_primitive_kinds[(test >> 2) & 3u];
                const auto unknown_size = unknown_primitive_sizes[test & 3u];
                write_primitive(fixtures[0], 28, unknown_kind, unknown_size,
                                7, {}, 0.0f, 0.0f);
                const std::size_t second_transform_offset =
                    28u + static_cast<std::size_t>(unknown_size);
                write_primitive(fixtures[0], second_transform_offset, 0, 28,
                                test % 3 == 0 ? 3 : 1,
                                {-0.2f, 0.05f, 0.1f}, 0.0f, 0.0f);
                constexpr std::array<std::int16_t, 3> negative_sentinels{
                    -1, -2, static_cast<std::int16_t>(0x8000)};
                write_primitive(fixtures[0], second_transform_offset + 28,
                                negative_sentinels[test % 3], 0, 0, {},
                                0.0f, 0.0f);

                write_primitive(fixtures[1], 0, 0, 28, 2,
                                {0.1f, 0.0f, 0.0f}, 8.0f, 10.0f);
                write_primitive(fixtures[1], 28, -1, 0, 0, {}, 0.0f, 0.0f);

                write_primitive(fixtures[2], 0, 0, 28, 4,
                                {0.0f, 0.1f, 0.0f}, 4.0f, 5.0f);
                write_primitive(fixtures[2], 28, -1, 0, 0, {}, 0.0f, 0.0f);

                auto random_visibility = [&]() {
                    const auto flags = static_cast<std::uint16_t>(random());
                    return th20::StageResourceInstanceFlagBits{
                        static_cast<std::uint16_t>(flags & 1u),
                        static_cast<std::uint16_t>(flags >> 1)};
                };
                instances[0] = {0, random_visibility(),
                                {0.05f, 0.0f, 0.0f}};
                instances[1] = {1, random_visibility(),
                                {test & 1u ? 100.0f : 0.0f, 0.0f, 0.0f}};
                instances[2] = {2, random_visibility(),
                                {0.0f, 0.0f, 0.0f}};
                instances[3] = {0, random_visibility(),
                                {-0.1f, 0.0f, 0.0f}};
                instances[4] = {-1, {}, {}};
            };

            auto& sprite = th20::stage_test_sprite_data;
            sprite.extent_48 = 32.0f;
            sprite.extent_4c = 64.0f;
            auto* previous_pool = th20::current_animation_pool;
            auto* native_pool_slot =
                reinterpret_cast<void**>(mapped_image_base + 0x1c0028);
            void* previous_native_pool = *native_pool_slot;
            *native_pool_slot = pool_storage;
            th20::current_animation_pool =
                reinterpret_cast<th20::AnimationPoolOwner*>(pool_storage);

            const float saved_native_zero = *native_zero;
            *native_zero = 0.0f;
            for (unsigned test = 0; test < 128; ++test) {
                alignas(th20::StageResourceOwner)
                    std::uint8_t owner_storage[sizeof(th20::StageResourceOwner)]{};
                auto& owner = *::new (owner_storage) th20::StageResourceOwner{};
                std::array<ObjectFixture, 3> fixtures{};
                std::array<th20::StageResourceObjectRecord*, 3> table{};
                std::array<th20::StageResourceInstanceRecord, 5> instances{};
                std::array<th20::Animation, 8> animations{};
                initialize_fixture(owner, fixtures, table, instances, animations, test);

                th20::ViewportState camera{};
                th20::matrix_identity(reinterpret_cast<th20::Matrix4*>(&camera.view));
                th20::matrix_identity(reinterpret_cast<th20::Matrix4*>(&camera.projection));
                camera.vector_00 = {};
                camera.vector_3c = {static_cast<float>(static_cast<int>(test % 7) - 3) * 0.01f,
                                    0.0f, 0.0f};
                camera.viewport = {0, 0, 640, 480, 0.0f, 1.0f};
                th20::source_camera_viewport = camera;
                th20::process_graphics.viewports[3] = camera;
                std::memcpy(reinterpret_cast<void*>(mapped_image_base + 0x1c53fc),
                            &camera, sizeof(camera));

                std::array<std::array<std::uint8_t, 0x1000>, 3> pool_before{},
                    pool_expected{}, pool_actual{};
                for (std::size_t page = 0; page < page_offsets.size(); ++page) {
                    for (auto& byte : pool_before[page])
                        byte = static_cast<std::uint8_t>(random());
                    std::memcpy(pool_storage + page_offsets[page],
                                pool_before[page].data(), 0x1000);
                }
                *reinterpret_cast<std::uint32_t*>(pool_storage + 0x6000E70) = 0;

                std::array<std::uint8_t, sizeof(owner)> owner_before{}, owner_expected{};
                std::array<std::uint8_t, sizeof(animations)> animation_before{},
                    animation_expected{};
                std::memcpy(owner_before.data(), &owner, sizeof(owner));
                std::memcpy(animation_before.data(), animations.data(),
                            animation_before.size());

                FloatingEnvironment::prepare();
                const std::int32_t layer =
                    std::array<std::int32_t, 8>{8, 9, 7, -1, -128, 127, 0, 8}[test & 7u];
                stage_draw_state_trace.clear();
                cpu<std::int32_t>(0x00474880, &owner, layer);
                const auto native_draw_state_trace = stage_draw_state_trace;
                std::memcpy(owner_expected.data(), &owner, sizeof(owner));
                std::memcpy(animation_expected.data(), animations.data(),
                            animation_expected.size());
                for (std::size_t page = 0; page < page_offsets.size(); ++page)
                    std::memcpy(pool_expected[page].data(),
                                pool_storage + page_offsets[page], 0x1000);

                std::memcpy(&owner, owner_before.data(), sizeof(owner));
                std::memcpy(animations.data(), animation_before.data(),
                            animation_before.size());
                for (std::size_t page = 0; page < page_offsets.size(); ++page)
                    std::memcpy(pool_storage + page_offsets[page],
                                pool_before[page].data(), 0x1000);
                *reinterpret_cast<std::uint32_t*>(pool_storage + 0x6000E70) = 0;

                FloatingEnvironment::prepare();
                stage_draw_state_trace.clear();
                owner.draw_objects_for_layer(layer);
                const auto source_draw_state_trace = stage_draw_state_trace;
                const bool draw_state_trace_mismatch =
                    source_draw_state_trace != native_draw_state_trace;
                ++checks;
                ++groups["stage_resource_object_draw_state_trace"];
                if (draw_state_trace_mismatch) {
                    ++failed;
                    if (failures.size() < 30) {
                        failures.push_back("stage_resource_object_draw_state_trace test" +
                                           std::to_string(test));
                        std::cerr << failures.back() << '\\n';
                    }
                }

                bool mismatch = std::memcmp(&owner, owner_expected.data(),
                                            sizeof(owner)) != 0 ||
                    std::memcmp(animations.data(), animation_expected.data(),
                                animation_expected.size()) != 0;
                for (std::size_t page = 0; page < page_offsets.size(); ++page) {
                    std::memcpy(pool_actual[page].data(),
                                pool_storage + page_offsets[page], 0x1000);
                    mismatch = mismatch || pool_actual[page] != pool_expected[page];
                }
                ++checks;
                ++groups["stage_resource_object_draw_474880"];
                if (mismatch) {
                    ++failed;
                    if (failures.size() < 30) {
                        failures.push_back("stage_resource_object_draw_474880 test" +
                                           std::to_string(test));
                        if (draw_state_trace_mismatch)
                            std::cerr << "full draw trace mismatch native="
                                      << native_draw_state_trace.size()
                                      << " source=" << source_draw_state_trace.size() << '\\n';
                        std::cerr << failures.back() << '\n';
                    }
                }
            }
            *native_zero = saved_native_zero;
            th20::current_animation_pool = previous_pool;
            *native_pool_slot = previous_native_pool;
            VirtualFree(pool_storage, 0, MEM_RELEASE);
        }

        for (unsigned test = 0; test < 128; ++test) {
            alignas(th20::Animation) std::array<std::uint8_t, sizeof(th20::Animation)> storage{};
            auto* animation = ::new (storage.data()) th20::Animation();
            auto* bytes = reinterpret_cast<std::uint8_t*>(animation);
            for (unsigned index = 0; index < sizeof(*animation); ++index)
                bytes[index] = static_cast<std::uint8_t>(random());
            std::array<std::uint8_t, sizeof(th20::Animation)> before{}, expected{};
            std::memcpy(before.data(), animation, before.size());
            const float angle = std::bit_cast<float>(bits());

            FloatingEnvironment::prepare();
            cpu<void>(0x004504c0, animation, angle);
            std::memcpy(expected.data(), animation, expected.size());
            std::memcpy(animation, before.data(), before.size());
            FloatingEnvironment::prepare();
            animation->set_rotation_y_forward(angle);
            ++checks;
            ++groups["animation_set_rotation_y"];
            if (std::memcmp(animation, expected.data(), expected.size()) != 0) {
                ++failed;
                if (failures.size() < 30) failures.push_back("animation_set_rotation_y test" + std::to_string(test));
            }

            std::memcpy(animation, before.data(), before.size());
            FloatingEnvironment::prepare();
            cpu<void>(0x004504f0, animation, angle);
            std::memcpy(expected.data(), animation, expected.size());
            std::memcpy(animation, before.data(), before.size());
            FloatingEnvironment::prepare();
            animation->set_rotation_y(angle);
            ++checks;
            ++groups["animation_set_rotation_y_body"];
            if (std::memcmp(animation, expected.data(), expected.size()) != 0) {
                ++failed;
                if (failures.size() < 30) failures.push_back("animation_set_rotation_y_body test" + std::to_string(test));
            }

            std::memcpy(animation, before.data(), before.size());
            FloatingEnvironment::prepare();
            cpu<void>(0x004777f0, animation, angle);
            std::memcpy(expected.data(), animation, expected.size());
            std::memcpy(animation, before.data(), before.size());
            FloatingEnvironment::prepare();
            animation->set_scale_x(angle);
            ++checks;
            ++groups["animation_set_scale_x"];
            if (std::memcmp(animation, expected.data(), expected.size()) != 0) {
                ++failed;
                if (failures.size() < 30) failures.push_back("animation_set_scale_x test" + std::to_string(test));
            }

            std::memcpy(animation, before.data(), before.size());
            FloatingEnvironment::prepare();
            cpu<void>(0x004777c0, animation, angle);
            std::memcpy(expected.data(), animation, expected.size());
            std::memcpy(animation, before.data(), before.size());
            FloatingEnvironment::prepare();
            animation->set_scale_y(angle);
            ++checks;
            ++groups["animation_set_scale_y"];
            if (std::memcmp(animation, expected.data(), expected.size()) != 0) {
                ++failed;
                if (failures.size() < 30) failures.push_back("animation_set_scale_y test" + std::to_string(test));
            }

            std::memcpy(animation, before.data(), before.size());
            FloatingEnvironment::prepare();
            const float expected_rotation = cpu<float>(0x00474d40, animation);
            FloatingEnvironment::prepare();
            const float actual_rotation = animation->rotation_y_value();
            ++checks;
            ++groups["animation_rotation_y_accessor"];
            if (std::bit_cast<std::uint32_t>(expected_rotation) !=
                std::bit_cast<std::uint32_t>(actual_rotation)) {
                ++failed;
                if (failures.size() < 30) failures.push_back("animation_rotation_y_accessor test" + std::to_string(test));
            }
        }

        for (unsigned test = 0; test < 128; ++test) {
            const float value = std::bit_cast<float>(bits());
            FloatingEnvironment::prepare();
            const float expected = cpu_cdecl<float>(0x00438540, value);
            FloatingEnvironment::prepare();
            const float actual = th20::normalize_angle(value);
            ++checks;
            ++groups["normalize_angle_438540"];
            if (std::bit_cast<std::uint32_t>(expected) !=
                std::bit_cast<std::uint32_t>(actual)) {
                ++failed;
                if (failures.size() < 30) failures.push_back("normalize_angle_438540 test" + std::to_string(test));
            }
        }

        for (unsigned test = 0; test < 6; ++test) {
            const std::uint32_t flags = test < 6 ?
                std::array<std::uint32_t, 6>{0u, 4u, 4u, 4u, 8u, 8u}[test] : random();
            const std::int32_t fade = test < 6 ?
                std::array<std::int32_t, 6>{0, 29, 30, 59, 60, 100}[test] :
                static_cast<std::int32_t>(random() % 130) - 20;
            compare_owner_update(test, flags, fade, test & 1u ? 1u : 2u);
        }

        for (unsigned motion = 0; motion < 16; ++motion)
            for (int time : {-1025, -1, 0, 1, 255, 510, 511, 512, 799, 800,
                             1023, 1024, 1999, 2000, 2047, 2048, 3071, 3072, 4799, 4800})
                for (unsigned flags = 0; flags < 8; ++flags) {
                    compare("camera_motion_" + std::to_string(motion), instruction(0),
                        [&](th20::StageBackgroundScriptState& state) {
                            state.camera_motion = static_cast<std::uint8_t>(motion);
                            state.motion_timer.previous = time - 3;
                            state.motion_timer.current = time;
                            state.motion_timer.current_fraction = float(time) + 0.25f;
                            state.motion_timer.flags = flags;
                            state.secondary_motion_timer.previous = time - 1;
                            state.secondary_motion_timer.current = time / 2;
                            state.secondary_motion_timer.current_fraction = float(time) / 2.0f;
                            state.secondary_motion_timer.flags = flags;
                        }, 3);
                }

        for (unsigned test = 0; test < 3000; ++test)
            compare("future_instruction_interpolation", instruction(0, {}, 100000),
                [&](th20::StageBackgroundScriptState& state) {
                    state.camera_motion = static_cast<std::uint8_t>(test % 16);
                    state.motion_timer.previous = -1;
                    state.motion_timer.current = static_cast<int>(test % 4800);
                    state.motion_timer.current_fraction = float(test % 4800) + 0.5f;
                    state.motion_timer.flags = test % 8;
                    for (auto* value : {&state.direction_interpolation,
                                        &state.position_interpolation,
                                        &state.up_interpolation})
                        value->duration = static_cast<int>(random() % 110) - 2;
                    state.fog_interpolation.duration = static_cast<int>(random() % 110) - 2;
                    state.fov_interpolation.duration = static_cast<int>(random() % 110) - 2;
                }, 3);

        for (int opcode : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, -1})
            for (unsigned test = 0; test < 400; ++test) {
                std::vector<std::uint32_t> args(11);
                for (auto& value : args) value = bits();
                if (opcode == 1) { args[0] = 52; args[1] = random() % 100; }
                if (opcode == 3 || opcode == 5 || opcode == 9 || opcode == 10 ||
                    opcode == 11 || opcode == 18 || opcode == 21) {
                    args[0] = random() % 110 - 2;
                    args[1] = random() % 34;
                }
                if (opcode == 12) args[0] = random() % 272;
                if (opcode == 14) {
                    args[0] = random() % 8;
                    args[1] = 0u - (test % 4 + 1);
                    args[2] = random();
                }
                auto code = instruction(opcode, args);
                const auto tail = instruction(0, {}, test % 2 ? 100000 : 0);
                code.insert(code.end(), tail.begin(), tail.end());
                compare("opcode_" + std::to_string(opcode), code,
                        [opcode](th20::StageBackgroundScriptState& state) {
                            if (opcode == 19) {
                                // The original Animation VM exits before any external
                                // dependencies when flags.word_1c bit 0 is set.
                                for (auto& animation : state.animations)
                                    animation.base.flags.word_1c |= 1u;
                            }
                        }, 3);
            }

        std::ofstream report(argv[2]);
        report << "{\n  \"status\":\"" << (failed ? "failed" : "passed")
               << "\",\n  \"checks\":" << checks << ",\n  \"failed\":" << failed
               << ",\n  \"groups\":{";
        bool comma = false;
        for (const auto& [label, count] : groups) {
            if (comma) report << ',';
            comma = true;
            report << th20::json_string(label) << ':' << count;
        }
        report << "},\n  \"scope\":\"Original 0x4751B0 versus maintained StageBackgroundScriptState; original parent update 0x472100 with fade/flag gates, Graphics::viewports[3] publication, empty object table in the parent fixture, and eight Animation early returns; original mesh boss 0x4722E0 over two live 3x3 grids in both mesh modes with phase/amplitude/alpha/interior-Z/Timer updates (native RenderMesh::initialize deliberately suppressed); original object boss 0x4739E0 over 12 variable-size primitive fixtures (8/12/16-byte advances, negative sentinels, Animation::is_active, object-flag clearing and rotation lock); Matrix4 identity leaf 0x472840 (128 cases), Animation flag-clear leaf 0x472A10 (128 cases), and StageResourceObjectRecord viewport culling boss 0x473B20 (1024 cases with two independently implemented D3DX import test seams); AnimationPool stage-draw reset boss 0x4750A0 (128 sparse-memory cases across three committed pages); Animation Y-rotation getter/setter and X/Y scale setters 0x474D40/0x4504C0/0x4504F0/0x4777F0/0x4777C0 (raw payload comparisons); angle normalization 0x438540 (128 raw-float cases); inline Animation layer helper 0x474780 and StageResource object-layer draw boss 0x474880 (128 cases across matching signed layers 8/9/-1 and unmatched layers 7/-128/127/0, with four cull-distance thresholds (zero, nominal, expanded and maximum finite), unknown positive primitive kinds 1/2/7/0x7fff, 8/12/16/20-byte record advances and negative sentinels -1/-2/INT16_MIN, comparing the complete native/source clip, fog, depth-write, viewport, AnimationPool draw and flush trace from the inline-animation prelude through final cleanup); camera modes 0..15; future-time interpolation; opcodes 1..22; unknown opcodes 23 and -1; opcode17 checks null-mesh reset with native allocation suppressed; opcode19 checks event writes and primitive/eight-inline traversal with Animation::update early-return gated; positive ANM binding, RenderMesh initialization/allocation/destruction, nontrivial Animation::update paths and full stage rendering remain outside this oracle\",\n  \"failure_examples\":[";
        for (unsigned index = 0; index < failures.size(); ++index) {
            if (index) report << ',';
            report << th20::json_string(failures[index]);
        }
        report << "]\n}\n";
        th20::process_stage_resource = nullptr;
        std::cout << "StageResource VM: " << checks << " checks, " << failed << " failures\n";
        return failed ? 1 : 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 2;
    }
}


namespace th20 {
StageResourcePrimitiveHeader* StageResourcePrimitiveHeader::advance(std::int32_t size) {
    return reinterpret_cast<StageResourcePrimitiveHeader*>(
        reinterpret_cast<std::byte*>(this) + size);
}
} // namespace th20
