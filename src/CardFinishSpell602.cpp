// Complete source reconstruction of original Card spell-finish protocol.
// The original 602B method is NOT YET exact: local lifetimes, indexed-record
// accesses and control-flow lowering differ under pinned MSVC 19.44.
#include "Card.hpp"
#include "NativeCardFinishViews.hpp"
#include "Session.hpp"
#include "SoundInf.hpp"
#include "AnimationHandle.hpp"
#include <cstdint>
namespace th20 {
void Card::finish_spell() {
    if ((spell_flags.bits&1u)==0) return;
    native_card_ui_5c069c->mark_finished_4883a0();
    cancel_animation_handle(info_handles[0]);
    cancel_animation_handle(info_handles[1]);
    cancel_animation_handle(info_handles[2]);
    spell_flags.bits &= ~1u;
    background_handle.retire();
    spell_flags.bits &= ~0x20u;
    native_card_hud_5c06a4->clear_spell_effects_488ab0();
    effect_handle.retire();
    if (((spell_flags.bits>>1)&1u)==0) {
        native_card_hud_5c06a4->report_spell_result_4b90e0(1,0);
    } else {
        session.add_score(static_cast<std::uint32_t>(bonus));
        native_card_hud_5c06a4->report_spell_result_4b90e0(0,bonus);
        if (!native_card_play_5c60fc->is_paused_488800()) {
            std::uint32_t capture_kind = session.field_70_is_two()?1u:0u;
            auto* primary = reinterpret_cast<NativeSpellRecordArrayView*>(
                reinterpret_cast<std::uint8_t*>(native_primary_records_50fc50(native_card_records_5c6108))+0xB08);
            primary->record_486e10(spell_index)->increment_capture_488510(capture_kind);
            auto* secondary = reinterpret_cast<NativeSpellRecordArrayView*>(
                native_card_records_5c6108->secondary_488700()+0xB08);
            secondary->record_486e10(spell_index)->increment_capture_488510(capture_kind);
            int completed=0;
            for (int i=0;i<113;i++) {
                auto* entry = reinterpret_cast<NativeSpellRecordArrayView*>(
                    native_card_records_5c6108->secondary_488700()+0xB08)->record_486e10(i);
                if (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(entry)+0xC0)!=0 ||
                    *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(
                       reinterpret_cast<NativeSpellRecordArrayView*>(
                        native_card_records_5c6108->secondary_488700()+0xB08)->record_486e10(i))+0xC4)!=0) {
                    ++completed;
                }
            }
            if (completed>=113) native_achievement_unlock_52f900(0x28);
        }
        process_sound.request_effect(0x2E,0);
    }
    if (reinterpret_cast<NativeCardEndFlagView*>(this)->requires_extra_sound_488880()) {
        process_sound.request_effect(0x45,0);
    }
}
}
