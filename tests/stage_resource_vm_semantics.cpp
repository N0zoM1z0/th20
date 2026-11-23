#include "StageResource.hpp"
#include "StageResourceScriptAdapters.hpp"
#include "ClockScalar.hpp"
#include "Animation.hpp"
#include "Viewport.hpp"
#include "ClockScalar.hpp"

#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <vector>

namespace th20 {
StageResourceOwner* process_stage_resource = nullptr;
std::uint32_t test_clear_color = 0;
unsigned test_assign_calls = 0;
unsigned test_stop_calls = 0;
unsigned test_mesh_reset_calls = 0;
unsigned test_interrupt_calls = 0;
std::uint32_t test_interrupt_event = 0;

AnimationBase::AnimationBase() noexcept {}
Animation::Animation() noexcept : base() {}
Animation::~Animation() noexcept {}
AnimationHandle::AnimationHandle() noexcept : value(0) {}
TransformMatrix::TransformMatrix() {}
ViewportState::ViewportState()
    : field_of_view(0), field_58(0), field_5c(0), viewport{}, field_f8(0),
      offset_x(0), offset_y(0), adjusted_viewport{} {}

void stage_vm_assign_animation(StageBackgroundScriptState&, std::int32_t,
                               std::int32_t) { ++test_assign_calls; }
void stage_vm_stop_animation(Animation&) { ++test_stop_calls; }
void stage_vm_reset_meshes(StageBackgroundScriptState&) { ++test_mesh_reset_calls; }
void stage_vm_interrupt_animations(StageResourceOwner&, std::uint32_t event) {
    ++test_interrupt_calls;
    test_interrupt_event = event;
}
void stage_vm_set_clear_color(std::uint32_t color) { test_clear_color = color; }
void stage_vm_set_primary_rotation_flag(std::uint32_t value) {
    process_stage_resource->state_flags = (process_stage_resource->state_flags & ~16u) |
                                          ((value & 1u) << 4);
}
}

using namespace th20;

static std::vector<std::uint32_t> instruction(std::int16_t opcode,
                                               std::initializer_list<std::uint32_t> args,
                                               std::int32_t time = 0) {
    std::vector<std::uint32_t> words(2 + args.size());
    auto* header = reinterpret_cast<StageResourceInstructionHeader*>(words.data());
    header->time = time;
    header->opcode = opcode;
    header->size = static_cast<std::int16_t>(words.size() * 4);
    std::copy(args.begin(), args.end(), words.begin() + 2);
    return words;
}

static void append(std::vector<std::uint32_t>& code,
                   const std::vector<std::uint32_t>& part) {
    code.insert(code.end(), part.begin(), part.end());
}

static std::uint32_t bits(float value) { return std::bit_cast<std::uint32_t>(value); }

static void run(StageResourceOwner& owner, std::vector<std::uint32_t>& code,
                const float* rate = nullptr) {
    ClockScalar source_rate{};
    if (rate != nullptr) source_rate.set(*rate);
    timer_clock_sources[0] = rate != nullptr ? &source_rate : nullptr;
    owner.instructions = reinterpret_cast<const StageResourceInstructionHeader*>(code.data());
    owner.script_state.owner = &owner;
    owner.script_state.instruction_offset = 0;
    owner.script_state.timer.set(0);
    owner.script_state.execute_script();
    timer_clock_sources[0] = &default_timer_clock;
}

int main() {
    StageResourceOwner owner{};
    process_stage_resource = &owner;
    auto& state = owner.script_state;

    // Opcode 2 writes the current position and the native delta vector, then
    // the future-time terminator advances the ScriptState timer once.
    {
        std::vector<std::uint32_t> code;
        append(code, instruction(2, {bits(12.0f), bits(-4.0f), bits(7.5f)}));
        append(code, instruction(0, {}, 100));
        run(owner, code);
        assert(state.camera.vector_00.x == 12.0f);
        assert(state.camera.vector_00.y == -4.0f);
        assert(state.camera.vector_00.z == 7.5f);
        assert(state.camera.final_vector.x == 12.0f);
        assert(state.camera.final_vector.y == -4.0f);
        assert(state.camera.final_vector.z == 7.5f);
        assert(state.timer.current == 1);
    }

    // Opcode 1 replaces both timer and byte cursor; the jump target is then
    // executed as a real instruction, not treated as a record index.
    {
        std::vector<std::uint32_t> code;
        append(code, instruction(1, {24, 55}));
        append(code, instruction(0, {}));
        append(code, instruction(2, {bits(3.0f), bits(4.0f), bits(5.0f)}));
        append(code, instruction(0, {}, 1000));
        run(owner, code);
        assert(state.timer.current == 56);
        assert(state.camera.vector_00.x == 3.0f);
        assert(state.instruction_offset == 44);
    }

    // Position interpolation advances by the explicit rate pointer, while
    // preserving the native per-axis values and shared Timer state.
    {
        std::vector<std::uint32_t> code;
        append(code, instruction(3, {4, 0, bits(8.0f), bits(4.0f), bits(-4.0f)}));
        append(code, instruction(0, {}, 1000));
        const float rate = 0.5f;
        state.camera.vector_00 = {0.0f, 0.0f, 0.0f};
        run(owner, code, &rate);
        assert(state.position_interpolation.timer.current == 0);
        assert(state.position_interpolation.timer.current_fraction == 0.5f);
        assert(state.camera.vector_00.x != 0.0f);
    }

    // Packed fog channels retain blue/green/red/alpha order and the original
    // packed color word; fog interpolation starts from the live camera value.
    {
        std::vector<std::uint32_t> code;
        append(code, instruction(8, {0x80402010u, bits(100.0f), bits(900.0f)}));
        append(code, instruction(0, {}, 1000));
        run(owner, code);
        assert(state.camera.fog.near_distance == 100.0f);
        assert(state.camera.fog.far_distance == 900.0f);
        assert(state.camera.fog.packed == 0x80402010u);

        code.clear();
        append(code, instruction(9, {6, 0, 0x10203040u, bits(200.0f), bits(700.0f)}));
        append(code, instruction(0, {}, 1000));
        run(owner, code);
        assert(state.fog_interpolation.start.near_distance == 100.0f);
        assert(state.fog_interpolation.end.near_distance == 200.0f);
        assert(state.fog_interpolation.end.packed == 0x10203040u);
    }

    // Camera mode 1 updates offset/target/up and advances its own Timer.
    {
        std::vector<std::uint32_t> code;
        append(code, instruction(12, {1}));
        append(code, instruction(0, {}, 1000));
        run(owner, code);
        assert(state.camera_motion == 1);
        assert(state.motion_timer.current == 1);
        state.update_camera_motion(nullptr);
        assert(state.motion_timer.current == 2);
        assert(state.camera.vector_3c.x != 0.0f || state.camera.vector_3c.z != 0.0f);
        assert(state.camera.vector_48.x != 0.0f || state.camera.vector_48.z != 0.0f);
    }

    // The remaining state and adapter opcodes keep their exact ordering and
    // update only their native owner words.
    {
        std::vector<std::uint32_t> code;
        append(code, instruction(13, {0xff123456u}));
        append(code, instruction(14, {0, static_cast<std::uint32_t>(-2), 0xabcdef01u}));
        append(code, instruction(17, {1}));
        append(code, instruction(19, {5}));
        append(code, instruction(20, {bits(-3.0f)}));
        append(code, instruction(21, {8, 0, bits(1.5f)}));
        append(code, instruction(22, {1}));
        append(code, instruction(0, {}, 1000));
        state.animations[0].base.flags.byte_02 = 0xff;
        run(owner, code);
        assert(test_clear_color == 0xff123456u);
        assert(state.animations[0].base.flags.byte_02 == 0xfe);
        assert(test_mesh_reset_calls == 1);
        assert(test_interrupt_calls == 1 && test_interrupt_event == 12);
        assert(state.fields_3294[8] == bits(9.0f));
        assert(state.fov_interpolation.duration == 8);
        assert((owner.state_flags & 16u) != 0);
    }

    // Unknown opcodes consume their signed size without changing state.
    {
        std::vector<std::uint32_t> code;
        append(code, instruction(0x7fff, {0xdeadbeefu, 0x12345678u}));
        append(code, instruction(0, {}, 1000));
        const auto before = state.camera.vector_00;
        run(owner, code);
        assert(state.camera.vector_00.x == before.x);
        assert(state.camera.vector_00.y == before.y);
        assert(state.camera.vector_00.z == before.z);
    }

    process_stage_resource = nullptr;
    return 0;
}
