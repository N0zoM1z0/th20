#include "StageResourceScriptAdapters.hpp"
#include "AnimationFile.hpp"
#include "DiagnosticAllocator.hpp"
#include "DiagnosticObjectFactories.hpp"
#include "Graphics.hpp"
#include "NativeViewIndexOwner.hpp"
#include "NativeCardHudAnimationView.hpp"
#include "RenderMesh.hpp"
#include <bit>
#include <cstdint>

namespace th20 {
extern const float native_zero_56e0e8;

void stage_vm_assign_animation(StageBackgroundScriptState& state,
                               std::int32_t index, std::int32_t script) {
    Animation& animation = state.animations[index];
    animation.release_resources();
    state.owner->animation_file_value->bind_animation(&animation, script);
}

void stage_vm_stop_animation(Animation& animation) {
    animation.stop();
}

void stage_vm_reset_meshes(StageBackgroundScriptState& state) {
    for (std::int32_t index = 0; index < 2; ++index) {
        auto* mesh = reinterpret_cast<RenderMesh*>(
            static_cast<std::uintptr_t>(state.fields_3294[9 + index]));
        process_allocator->release_object(mesh);
        state.fields_3294[9 + index] = 0;
        state.fields_3294[11 + index] = std::bit_cast<std::uint32_t>(112.0f);
        state.fields_3294[13 + index] = std::bit_cast<std::uint32_t>(192.0f);
        state.fields_3294[15 + index] = 0xffffffffu;
        state.mesh_phase_x[index] = 0.0f;
        state.mesh_phase_y[index] = 0.0f;
        state.mesh_timers[index] = 0;
        native_view_index_owner_5c0028->set_view_index(index);
        if (native_zero_56e0e8 < 112.0f) {
            auto* created = process_allocator->allocate_object<
                RenderMesh, std::int32_t, std::int32_t, std::int32_t, std::int32_t>(
                    "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\effect.cpp:430 SprtID",
                    17, state.mesh_mode == 1 ? 7 : 17, 0, index);
            state.fields_3294[9 + index] = static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(created));
        }
    }
}

void stage_vm_interrupt_animations(StageResourceOwner& owner, std::uint32_t event) {
    owner.interrupt_animations(static_cast<std::int32_t>(event));
}

void stage_vm_set_clear_color(std::uint32_t color) {
    process_graphics.clear_color = color;
}

void stage_vm_set_primary_rotation_flag(std::uint32_t value) {
    process_stage_resource->set_primary_rotation_flag(value);
}

} // namespace th20
