#include "SoundInf.hpp"
#include "SoundEffects.hpp"
#include "LockRegistry.hpp"
#include <cassert>
#include <cstdint>
#include <cstring>

namespace th20 {

LockRegistry process_locks;
std::int32_t range_check_calls = 0;
std::uintptr_t last_range_command_type = 0;

void native_verify_sound_queue_range_40c6b0(char*, const char* command_type) {
    ++range_check_calls;
    last_range_command_type = reinterpret_cast<std::uintptr_t>(command_type);
}

SoundEffectRequest::SoundEffectRequest() : id(0), count(0), pans{} {}
SoundCommand::SoundCommand() : type(0), argument(0), stage(0), name{} {}
SoundEffectChannel::SoundEffectChannel()
    : buffer(nullptr), cooldown(-1), definition(nullptr), id(0), pan(0), was_playing(0) {}
SoundInf::SoundInf() noexcept = default;
SoundInf::~SoundInf() = default;

} // namespace th20

int main() {
    using namespace th20;
    SoundInf sound;

    sound.enqueue(2, 17, "voice-a.wav");
    assert(sound.commands[0].type == 2);
    assert(sound.commands[0].argument == 17);
    assert(sound.commands[0].stage == 0);
    assert(std::strcmp(sound.commands[0].name, "voice-a.wav") == 0);

    sound.enqueue(4, 23, "voice-b.wav");
    assert(sound.commands[1].type == 4);
    assert(sound.commands[1].argument == 23);
    assert(std::strcmp(sound.commands[1].name, "voice-b.wav") == 0);

    for (std::uint32_t i = 0; i < 31; ++i) {
        sound.commands[i].type = 1;
        sound.commands[i].argument = static_cast<std::int32_t>(i);
    }
    sound.enqueue(7, 9, "queue-full.wav");
    assert(sound.commands[30].type == 1);
    assert(sound.commands[31].type == 0);
    assert(sound.commands[31].name[0] == '\0');

    sound.commands[4].type = 0;
    sound.enqueue(9, 11, "reused.wav");
    assert(sound.commands[4].type == 9);
    assert(sound.commands[4].argument == 11);
    assert(sound.commands[4].stage == 0);
    assert(std::strcmp(sound.commands[4].name, "reused.wav") == 0);

    assert(range_check_calls == 4);
    assert(last_range_command_type == 9);
    return 0;
}
