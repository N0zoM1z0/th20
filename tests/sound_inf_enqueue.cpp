#include "SoundInf.hpp"
#include "SoundEffects.hpp"
#include "LockRegistry.hpp"
#include "EclDiagnostic.hpp"
#include <cassert>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace th20 {

LockRegistry process_locks;
std::int32_t range_check_calls = 0;
std::uintptr_t last_range_command_type = 0;
const char* last_range_format = nullptr;

void ecl_diagnostic_hint(const char* format, ...) {
    ++range_check_calls;
    last_range_format = format;
    std::va_list arguments;
    va_start(arguments, format);
    last_range_command_type = static_cast<std::uintptr_t>(va_arg(arguments, int));
    va_end(arguments);
}

SoundEffectRequest::SoundEffectRequest() : id(0), count(0), pans{} {}
SoundCommand::SoundCommand() : type(0), argument(0), stage(0), name{} {}
SoundEffectChannel::SoundEffectChannel()
    : buffer(nullptr), cooldown(-1), definition(nullptr), id(0), pan(0), was_playing(0) {}
SoundInf::SoundInf() noexcept = default;
SoundInf::~SoundInf() = default;

} // namespace th20

extern "C" int strcpy_s(char* destination, std::size_t capacity, const char* source) {
    if (!destination || !source || capacity == 0) return 22;
    const std::size_t length = std::strlen(source);
    if (length >= capacity) { destination[0] = '\0'; return 34; }
    std::memcpy(destination, source, length + 1);
    return 0;
}

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
    assert(sound.commands[1].stage == 0);
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
    assert(last_range_format != nullptr);
    assert(std::strcmp(last_range_format, "Sound Que Add %d\r\n") == 0);
    assert(last_range_command_type == 9);
    assert(process_locks.slot(11).try_lock());
    process_locks.slot(11).unlock();
    return 0;
}
