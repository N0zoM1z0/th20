#include "SoundEffects.hpp"
#include "SoundInf.hpp"
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

// Native absolute-position effect request: sound ID is preserved; x in game
// coordinates is converted to the effect request's signed integer pan.
void SoundInf::request_effect_at(std::int32_t id, float x) {
    request_effect(id, static_cast<std::int32_t>((x * 1000.0f) / 192.0f));
}

} // namespace th20
