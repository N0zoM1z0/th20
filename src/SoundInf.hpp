#pragma once
#include "Win32SoundApi.hpp"
#include <array>
#include <memory_resource>
#include <vector>
#include "SoundEffects.hpp"

namespace th20 {
// Complete native storage. Unnamed scalars retain observed offsets;
// original startup and resource-owning retirement remain undefined interfaces.
// All fields have native storage evidence; there is no appended service context.
struct SoundDeviceOwner;
class StreamingSound;
struct TrackFormat {
    char name[16];
    std::uint32_t file_offset, preload_bytes, loop_start, total_bytes;
    WAVEFORMATEX format;
};
static_assert(sizeof(TrackFormat) == 52);
struct PreloadedTrack {
    TrackFormat* format;
    std::uint8_t* allocation;
    std::uint8_t* current;
    std::uint32_t size;
};
static_assert(sizeof(void*) != 4 || sizeof(PreloadedTrack) == 16);
extern const SoundEffectDefinition sound_effect_definitions[90];
struct SoundInf {
    IDirectSound8* direct_sound = nullptr;
    IDirectSoundBuffer* silent_buffer = nullptr;
    HWND window = nullptr;
    SoundDeviceOwner* device_owner = nullptr;
    DWORD notify_thread_id = 0;
    HANDLE notify_thread = nullptr;
    std::uint32_t field_18 = 0;
    std::array<SoundEffectRequest, 12> requests;
    std::pmr::vector<PreloadedTrack> preloaded;
    std::int32_t preloaded_index = 0;
    TrackFormat* track_formats = nullptr;
    char current_track[256]{};
    std::array<SoundEffectChannel, 90> effects;
    IDirectSoundBuffer* source_buffers[72]{nullptr};
    std::uint32_t duplicate_counts[72]{};
    char queued_track[256]{};
    std::array<SoundCommand, 32> commands;
    char track_names[16][256]{{}};
    char music_file[256]{};
    StreamingSound* stream = nullptr;
    std::uint32_t field_57c8 = 0;
    HANDLE notification = nullptr;
    std::uint32_t field_57d0 = 0, field_57d4 = 0, field_57d8 = 0;
    std::int32_t music_level = 0, effect_level = 0;
    std::uint32_t field_57e4 = 0;
    SoundInf() noexcept;
    ~SoundInf();
    void request_effect(std::int32_t id, std::int32_t pan);
    void request_effect_at(std::int32_t id, float x);
    void enqueue(std::int32_t type, std::int32_t argument, const char* name);
    std::int32_t ready() const;
    std::int32_t poll();
    std::int32_t preload(std::int32_t, const char*);
    std::int32_t load_track(std::int32_t);
    std::int32_t find_track(const char*);
    void stop_stream();
    void fade_out(float);
    void free_preload(std::int32_t);
    std::int32_t reopen_track(const char*);
};
extern SoundInf process_sound;
DWORD WINAPI sound_notification_thread(void*);
#if defined(_M_IX86)
static_assert(sizeof(SoundInf) == 0x57e8);
static_assert(offsetof(SoundInf, requests) == 0x1c);
static_assert(offsetof(SoundInf, preloaded) == 0x187c);
static_assert(offsetof(SoundInf, effects) == 0x1994);
static_assert(offsetof(SoundInf, commands) == 0x2544);
static_assert(offsetof(SoundInf, stream) == 0x57c4);
#endif
}
