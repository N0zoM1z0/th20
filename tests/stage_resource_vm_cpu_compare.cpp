#define wmain unused_native_cpu_compare_main
#include "../_reference/Touhou20/tests/native_cpu_compare.cpp"
#undef wmain

#include "StageResource.hpp"
#include "StageResourceScriptAdapters.hpp"
#include "ClockScalar.hpp"
#include "NativeCardHudAnimationView.hpp"
#include "NativeViewIndexOwner.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "RenderMesh.hpp"
#include "ScalarMath.hpp"
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

namespace th20 {
NativeViewIndexOwner test_view_index_owner{};
ViewportState source_camera_viewport{};
NativeViewIndexOwner* native_view_index_owner_5c0028 = &test_view_index_owner;
AnimationPoolOwner* current_animation_pool =
    reinterpret_cast<AnimationPoolOwner*>(&test_view_index_owner);

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
TransformMatrix::TransformMatrix() {}
ViewportState::ViewportState()
    : field_of_view(0), field_58(0), field_5c(0), viewport{}, field_f8(0),
      offset_x(0), offset_y(0), adjusted_viewport{} {}

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
        *reinterpret_cast<float*>(mapped_image_base + 0x16e0e8) = 200.0f;
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
                records[index].object.layer = static_cast<std::uint8_t>(random());
                records[index].object.flags = static_cast<std::uint8_t>(random());
                for (float& parameter : records[index].object.parameters)
                    parameter = finite();
                records[index].object.parameters[1] =
                    std::array<float, 8>{0.0f, -0.0f, 0.125f, -0.75f,
                                         3.1415927f, -3.1415927f, 19.0f,
                                         std::bit_cast<float>(0x7fc00000u)}[test % 8];
                records[index].object.parameters[2] =
                    std::array<float, 8>{0.0f, 3.0f, -3.0f, 100.0f,
                                         -100.0f, 6.2831855f, 1.0f,
                                         std::bit_cast<float>(0x7fc00000u)}[(test + index) % 8];
                std::memset(records[index].primitive_data, 0,
                            sizeof(records[index].primitive_data));
            }
            auto write_primitive = [&](unsigned object_index, unsigned offset,
                                       th20::StageResourcePrimitiveHeader primitive) {
                std::memcpy(records[object_index].primitive_data + offset,
                            &primitive, sizeof(primitive));
            };
            records[0].object.flags |= 1u;
            write_primitive(0, 0, {0, 12, 4, 0});
            write_primitive(0, 12, {1, 8, 5, 1});
            write_primitive(0, 20, {-1, 0, 0, 0});
            records[1].object.flags |= 1u;
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
        report << "},\n  \"scope\":\"Original 0x4751B0 versus maintained StageBackgroundScriptState; original parent update 0x472100 with fade/flag gates, Graphics::viewports[3] publication, empty object table in the parent fixture, and eight Animation early returns; original mesh boss 0x4722E0 over two live 3x3 grids in both mesh modes with phase/amplitude/alpha/interior-Z/Timer updates (native RenderMesh::initialize deliberately suppressed); original object boss 0x4739E0 over 12 variable-size primitive fixtures (8/12/16-byte advances, negative sentinels, Animation::is_active, object-flag clearing and rotation lock); Matrix4 identity leaf 0x472840 (128 cases) and Animation flag-clear leaf 0x472A10 (128 cases); camera modes 0..15; future-time interpolation; opcodes 1..22; unknown opcodes 23 and -1; opcode17 checks null-mesh reset with native allocation suppressed; opcode19 checks event writes and primitive/eight-inline traversal with Animation::update early-return gated; positive ANM binding, RenderMesh initialization/allocation/destruction, nontrivial Animation::update paths and full stage rendering remain outside this oracle\",\n  \"failure_examples\":[";
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
