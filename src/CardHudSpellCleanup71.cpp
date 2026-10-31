// Complete original 71B Card HUD two-animation closure, real 22B event bridge
// and 34B VM-update parameter setter. The view does NOT inherit from Animation;
// only the native Animation+0x438 and actual update() call are observed.
#include "NativeCardFinishViews.hpp"
#include "NativeCardHudAnimationView.hpp"
#include "Animation.hpp"
#include <array>
#include <cstdint>
namespace th20 {
void NativeHudAnimationView::finish_stage_488900() {
    set_vm_event_477450(3);
}
void NativeCardHudView::clear_spell_effects_488ab0() {
    (*reinterpret_cast<std::array<NativeHudAnimationView*,2>*>(
        reinterpret_cast<std::uint8_t*>(this)+0x88))[0]->finish_stage_488900();
    (*reinterpret_cast<std::array<NativeHudAnimationView*,2>*>(
        reinterpret_cast<std::uint8_t*>(this)+0x88))[1]->finish_stage_488900();
}
void NativeHudAnimationView::set_vm_event_477450(std::int32_t event) {
    *reinterpret_cast<std::uint32_t*>(
        reinterpret_cast<std::uint8_t*>(this)+0x438)=event;
    reinterpret_cast<Animation*>(this)->update();
}
}
