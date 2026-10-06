#pragma once

#include <cstddef>
#include <cstdint>

struct IDirectSoundBuffer;

namespace th20 {

struct SoundEffectDefinition {
    std::int32_t id, file_index;
    std::int16_t volume, cooldown;
    std::uint32_t play_flags, retained_10;
};
static_assert(sizeof(SoundEffectDefinition) == 20);

struct SoundEffectRequest {
    std::int32_t id, count;
    std::int32_t pans[128];
    SoundEffectRequest();
};
static_assert(sizeof(SoundEffectRequest) == 0x208);

struct SoundCommand {
    std::int32_t type, argument, stage;
    char name[256];
    SoundCommand();
};
static_assert(sizeof(SoundCommand) == 0x10c);

struct SoundEffectChannel {
    IDirectSoundBuffer* buffer;
    std::int32_t cooldown;
    const SoundEffectDefinition* definition;
    std::int32_t id, pan, was_playing;
    SoundEffectChannel();
    void release();
};
static_assert(sizeof(void*) != 4 || sizeof(SoundEffectChannel) == 24);
static_assert(sizeof(void*) != 4 || offsetof(SoundEffectChannel, definition) == 8);

// Constructor contributions are exact, but authored versus compiler-generated
// origin remains open. These records do not initialize the enclosing SoundInf.

} // namespace th20
