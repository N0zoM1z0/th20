#pragma once
#include <cstdint>
namespace th20 {
// Two borrowed Animation-like HUD receivers. This is an ABI view, not an
// invented Animation subclass or a duplicated/vtable-owning object.
struct NativeHudAnimationView {
    void start_stage_4888e0();
    void finish_stage_488900();
    void set_vm_event_477450(std::int32_t value);
};
}
