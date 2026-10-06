#include "SoundEffects.hpp"
#include <cstring>

namespace th20 {

SoundEffectRequest::SoundEffectRequest() {
    id = 0;
    count = 0;
    std::memset(pans, 0, sizeof pans);
}

SoundCommand::SoundCommand() {
    type = 0;
    argument = 0;
    stage = 0;
    std::memset(name, 0, sizeof name);
}

SoundEffectChannel::SoundEffectChannel() {
    buffer = nullptr;
    cooldown = -1;
    definition = nullptr;
    id = 0;
    pan = 0;
    was_playing = 0;
}

} // namespace th20
