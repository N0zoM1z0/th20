// Exact original Card start flag/record/HUD state chain. The real Card owner,
// borrowed HUD and record views retain their independently observed ABI.
#include "Card.hpp"
#include "NativeCardStartFlagsView.hpp"
#include "NativeCardFinishViews.hpp"
#include "NativeCardSpellViews.hpp"
#include "NativeCardHudAnimationView.hpp"
#include <array>
#include <cstdint>
namespace th20 {
// This 4-byte view mirrors exactly the native Card+0x78 bit9 field. C++
// bitfield assignment preserves the original 42-byte read-modify-write ABI.
struct NativeCardBit9Field {
    std::uint32_t lower_nine:9, bit9:1, upper:22;
};
static_assert(sizeof(NativeCardBit9Field)==4);
void NativeCardStartFlagsView::clear_capture_effect_flag_4888c0() {
    reinterpret_cast<Card*>(this)->spell_flags.bits &= ~0x80u;
}
void NativeCardStartFlagsView::set_spell_flag9_488960(std::uint32_t value) {
    reinterpret_cast<NativeCardBit9Field*>(
        reinterpret_cast<std::uint8_t*>(this)+0x78)->bit9=value;
}
void NativeSpellRecordView::increment_attempt_488590(std::int32_t kind) {
    if (reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0xC8)[kind]<99999)
        ++reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0xC8)[kind];
}
void NativeHudAnimationView::start_stage_4888e0() {
    set_vm_event_477450(2);
}
void NativeCardHudView::start_spell_effects_488a60() {
    (*reinterpret_cast<std::array<NativeHudAnimationView*,2>*>(
        reinterpret_cast<std::uint8_t*>(this)+0x88))[0]->start_stage_4888e0();
    (*reinterpret_cast<std::array<NativeHudAnimationView*,2>*>(
        reinterpret_cast<std::uint8_t*>(this)+0x88))[1]->start_stage_4888e0();
}
}
