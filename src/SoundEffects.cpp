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

// Original SoundEffectChannel setter: 22B native game field assignment,
// physically folded with the already exact EnemyPattern scalar setter.
void SoundEffectChannel::set_cooldown(std::int32_t value) {
    cooldown = value;
}

// Complete original 320-byte SoundInf request queue / cooldown manager.
// Preserve the true 12-slot array, signed ID sentinel, and 60-pan queue cap.
// The original MSVC std::array ABI explicitly calls _Unchecked_begin/end
// to obtain raw request pointers; no synthetic iterator state is added.
void SoundInf::request_effect(std::int32_t id, std::int32_t pan) {
    std::int32_t cooldown = sound_effect_definitions[id].volume;
    std::uint32_t index = 0;
    auto& queue = requests;
    auto* current = queue._Unchecked_begin();
    auto* end = queue._Unchecked_end();
    for (; current != end; ++current) {
        SoundEffectRequest& request = *current;
        if (request.id < 0) break;
        if (request.id == id) {
            if (request.count < 60 && request.count >= 0) {
                request.pans[request.count] = pan;
                ++request.count;
            }
            return;
        }
        ++index;
    }
    if (static_cast<std::int32_t>(index) >= 12) return;
    requests.at(index).id = id;
    requests[index].pans[0] = pan;
    requests[index].count = 1;
    effects[id].set_cooldown(cooldown);
}

// Native absolute-position effect request: sound ID is preserved; x in game
// coordinates is converted to the effect request's signed integer pan.
void SoundInf::request_effect_at(std::int32_t id, float x) {
    request_effect(id, static_cast<std::int32_t>((x * 1000.0f) / 192.0f));
}

} // namespace th20
