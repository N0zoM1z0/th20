// Complete original 602-byte Card spell-finish gameplay and record scan.
// The same meaningful local stores the binary capture kind, then is reset
// to count completed records, reproducing the native EBP-8 lifetime.
// Record counts are genuine two-element 32-bit arrays, and each original
// record access performs its own lookup. The whole body is C++20 native exact.
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
    if (((spell_flags.bits>>1)&1u)!=0) {
        session.add_score(static_cast<std::uint32_t>(bonus));
        native_card_hud_5c06a4->report_spell_result_4b90e0(0,bonus);
        if (!native_card_play_5c60fc->is_paused_488800()) {
            // Capture kind is consumed before the same local is recycled for
            // the 113-record completion count, as observed in original x86.
            std::int32_t capture_progress = session.field_70_is_two()?1:0;
            auto* primary = reinterpret_cast<NativeSpellRecordArrayView*>(
                reinterpret_cast<std::uint8_t*>(native_primary_records_50fc50(native_card_records_5c6108))+0xB08);
            std::int32_t primary_spell_index = spell_index;
            primary->record_486e10(primary_spell_index)->increment_capture_488510(capture_progress);
            auto* secondary = reinterpret_cast<NativeSpellRecordArrayView*>(
                native_card_records_5c6108->secondary_488700()+0xB08);
            std::int32_t secondary_spell_index = spell_index;
            secondary->record_486e10(secondary_spell_index)->increment_capture_488510(capture_progress);
            capture_progress=0;
            for (int i=0;i<113;i++) {
                if ((*reinterpret_cast<std::int32_t(*)[2]>(reinterpret_cast<std::uint8_t*>(
                    reinterpret_cast<NativeSpellRecordArrayView*>(
                        native_card_records_5c6108->secondary_488700()+0xB08)->record_486e10(i))+0xC0))[0]!=0 ||
                    (*reinterpret_cast<std::int32_t(*)[2]>(reinterpret_cast<std::uint8_t*>(
                       reinterpret_cast<NativeSpellRecordArrayView*>(
                        native_card_records_5c6108->secondary_488700()+0xB08)->record_486e10(i))+0xC0))[1]!=0) {
                    ++capture_progress;
                }
            }
            if (capture_progress>=113) native_achievement_unlock_52f900(0x28);
        }
        process_sound.request_effect(0x2E,0);
    } else {
        native_card_hud_5c06a4->report_spell_result_4b90e0(1,0);
    }
    if (reinterpret_cast<NativeCardEndFlagView*>(this)->requires_extra_sound_488880()) {
        process_sound.request_effect(0x45,0);
    }
}
}
