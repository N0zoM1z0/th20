#define wmain unused_native_cpu_compare_main
#include "../_reference/Touhou20/tests/native_cpu_compare.cpp"
#undef wmain

#include "StageResource.hpp"
#include "StageResourceScriptAdapters.hpp"
#include "ClockScalar.hpp"
#include "ClockScalar.hpp"
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
StageResourceOwner* process_stage_resource = nullptr;

AnimationBase::AnimationBase() noexcept {}
Animation::Animation() noexcept : base() {}
Animation::~Animation() noexcept {}
AnimationHandle::AnimationHandle() noexcept : value(0) {}
TransformMatrix::TransformMatrix() {}
ViewportState::ViewportState()
    : field_of_view(0), field_58(0), field_5c(0), viewport{}, field_f8(0),
      offset_x(0), offset_y(0), adjusted_viewport{} {}

void stage_vm_assign_animation(StageBackgroundScriptState&, std::int32_t,
                               std::int32_t) { outside_scope(); }
void stage_vm_stop_animation(Animation& animation) {
    animation.base.field_28 = -1;
    animation.base.flags.byte_02 &= 0xfeu;
}
void stage_vm_reset_meshes(StageBackgroundScriptState&) { outside_scope(); }
void stage_vm_interrupt_animations(StageResourceOwner&, std::uint32_t) { outside_scope(); }
void stage_vm_set_clear_color(std::uint32_t value) { source_clear_color = value; }
void stage_vm_set_primary_rotation_flag(std::uint32_t value) {
    process_stage_resource->state_flags = (process_stage_resource->state_flags & ~16u) |
                                          ((value & 1u) << 4);
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
            auto& owner = *reinterpret_cast<th20::StageResourceOwner*>(owner_storage);
            owner.instructions = reinterpret_cast<const th20::StageResourceInstructionHeader*>(
                code.data());
            th20::process_stage_resource = &owner;

            alignas(th20::StageBackgroundScriptState)
                std::uint8_t state_storage[sizeof(th20::StageBackgroundScriptState)]{};
            std::memset(state_storage, 0xa5, sizeof(state_storage));
            auto& state = *reinterpret_cast<th20::StageBackgroundScriptState*>(state_storage);
            prepare(state);
            state.owner = &owner;
            initialize(state);

            const float rate_value = float(random() % 5) * 0.5f;
            const float* rate = random() % 6 ? &rate_value : nullptr;
            th20::ClockScalar source_rate{};
            if (rate != nullptr) source_rate.set(*rate);
            th20::timer_clock_sources[0] = rate != nullptr ? &source_rate : nullptr;
            *reinterpret_cast<const float**>(mapped_image_base + 0x1aefe0) = rate;
            *reinterpret_cast<void**>(mapped_image_base + 0x1c069c) = &owner;

            std::array<std::uint8_t, sizeof(state)> before{}, expected{};
            for (unsigned tick = 0; tick < ticks; ++tick) {
                std::memcpy(before.data(), &state, sizeof(state));
                const auto initial_flags = random();
                const auto initial_color = random();
                owner.state_flags = initial_flags;
                *reinterpret_cast<std::uint32_t*>(mapped_image_base + 0x1c5b20) = initial_color;

                FloatingEnvironment::prepare();
                cpu<void>(0x004751b0, &state);
                std::memcpy(expected.data(), &state, sizeof(state));
                const auto expected_flags = owner.state_flags;
                const auto expected_color = *reinterpret_cast<std::uint32_t*>(
                    mapped_image_base + 0x1c5b20);

                std::memcpy(&state, before.data(), sizeof(state));
                owner.state_flags = initial_flags;
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
                if (owner.state_flags != expected_flags) why += " rotation global";
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
        };

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

        for (int opcode : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 18, 20, 21, 22, 23, -1})
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
                        [](th20::StageBackgroundScriptState&) {}, 3);
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
        report << "},\n  \"scope\":\"Original 0x4751B0 versus maintained StageBackgroundScriptState; camera modes 0..15, future instruction interpolation, opcodes 1..16/18/20..23 and unknown; positive ANM binding, mesh opcode17, animation interrupt19 and full stage rendering remain outside this oracle\",\n  \"failure_examples\":[";
        for (unsigned index = 0; index < failures.size(); ++index) {
            if (index) report << ',';
            report << th20::json_string(failures[index]);
        }
        report << "]\n}\n";
        std::cout << "StageResource VM: " << checks << " checks, " << failed << " failures\n";
        return failed ? 1 : 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 2;
    }
}
