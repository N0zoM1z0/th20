#include "SoundInf.hpp"
#include <cstdint>

namespace th20 {

extern bool native_graphics_uses_preloaded_music_28fa0();
extern const char sound_command_name_571b14[];
extern std::uint8_t* native_stage_voice_flags_5c6108;

void play_front_dialogue_voice_4d9b50(std::int32_t selector, std::int32_t sound_id) {
    if (native_graphics_uses_preloaded_music_28fa0())
        process_sound.enqueue(4, 0, sound_command_name_571b14);
    process_sound.enqueue(2, selector, sound_command_name_571b14);
    native_stage_voice_flags_5c6108[0x36 + sound_id] = 1;
}

} // namespace th20
