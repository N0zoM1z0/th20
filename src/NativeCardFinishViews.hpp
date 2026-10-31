#pragma once
// Non-owning native UI, play-state and record-owner views for Card::finish_spell.
// Only the observed member offsets and call ABIs are assumed; the UI owner,
// archive and achievement subsystem layouts remain under investigation.
#include "NativeCardSpellViews.hpp"
#include <cstdint>
namespace th20 {
struct AnimationHandle;
struct NativeCardHudView {
    void start_spell_effects_488a60();
    void clear_spell_effects_488ab0();
    void report_spell_result_4b90e0(std::int32_t mode, std::int32_t capture_bonus);
};
struct NativeCardPlayView {
    std::int32_t is_paused_488800() const;
};
struct NativeCardEndFlagView {
    std::uint32_t requires_extra_sound_488880();
};
extern NativeCardUiDirtyView* native_card_ui_5c069c;
extern NativeCardHudView* native_card_hud_5c06a4;
extern NativeCardPlayView* native_card_play_5c60fc;
extern NativeCardRecordArchive* native_card_records_5c6108;
extern NativeCardRecordArchive* __fastcall native_primary_records_50fc50(NativeCardRecordArchive*);
extern void* __cdecl native_achievement_unlock_52f900(std::uint32_t);
void __fastcall cancel_animation_handle(const AnimationHandle& handle);
}
