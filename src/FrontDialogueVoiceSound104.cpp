#include "Graphics.hpp"
#include "NativeCardFinishViews.hpp"
#include "SoundInf.hpp"
#include <cstdint>

namespace th20 {

extern const char sound_command_name_571b14[];

struct NativeCardStageVoiceFlagsView {
    std::uint8_t* slot_411c10(std::int32_t index);
};

struct NativeCardStageVoiceOwnerView {
    NativeCardStageVoiceFlagsView* stage_voice_flags_640e0();
};

NativeCardStageVoiceFlagsView* NativeCardStageVoiceOwnerView::stage_voice_flags_640e0() {
    return reinterpret_cast<NativeCardStageVoiceFlagsView*>(
        reinterpret_cast<std::uint8_t*>(this) + 0x91f48);
}

std::uint8_t* NativeCardStageVoiceFlagsView::slot_411c10(std::int32_t index) {
    return reinterpret_cast<std::uint8_t*>(this) + index;
}

std::int32_t Graphics::play_front_dialogue_voice_4d9b50(
    std::int32_t selector, std::int32_t voice_id) {
    if (process_graphics.uses_preloaded_music())
        process_sound.enqueue(4, 0, sound_command_name_571b14);
    process_sound.enqueue(2, selector, sound_command_name_571b14);
    auto* selected_flags = reinterpret_cast<NativeCardStageVoiceFlagsView*>(
        reinterpret_cast<std::uint8_t*>(
            reinterpret_cast<NativeCardStageVoiceOwnerView*>(
                native_card_records_5c6108)->stage_voice_flags_640e0()) + 0x36);
    *selected_flags->slot_411c10(voice_id) = 1;
    return 0;
}

} // namespace th20
