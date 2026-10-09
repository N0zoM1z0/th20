#include "SoundInf.hpp"
#include "SoundDeviceOwner.hpp"
#include "Graphics.hpp"
#include "DiagnosticAllocator.hpp"
#include "LockRegistry.hpp"
#include "SecureCrt.hpp"
#include <cstring>

namespace th20 {
extern void sound_log(const char*, ...);
SoundInf::~SoundInf() = default;

// Complete loading protocol. Original unchecked Win32/CRT statuses,
// global publication, storage retention and creation order remain visible.
void SoundInf::free_preload(std::int32_t index) {
    if (preloaded[index].allocation) {
        std::uint8_t* memory = preloaded[index].allocation;
        process_allocator->release_bytes(memory);
        preloaded[index].allocation = nullptr;
    }
}

std::int32_t SoundInf::preload(std::int32_t index, const char* name) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(2));
    if (preloaded.size() <= static_cast<std::size_t>(index)) preloaded.resize(index + 1);
    if (preloaded[index].allocation) {
        if (std::strcmp(name, track_names[index]) == 0) return 0;
    }
    strcpy_s(process_sound.track_names[index], 256, name);
    if (!process_graphics.uses_preloaded_music()) return 0;
    if (!device_owner) return 0;
    free_preload(index);
    sound_log("Streming BGM PreLoad %d\r\n", index);
    WCHAR path[MAX_PATH + 1];
    std::memset(path, 0, sizeof path);
    MultiByteToWideChar(932, 0, music_file, -1, path, MAX_PATH);
    HANDLE file = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        sound_log("error : bgmfile is not find %s\r\n", music_file);
        return -1;
    }
    std::int32_t track_index = find_track(name);
    SetFilePointer(file, track_formats[track_index].file_offset, nullptr, FILE_BEGIN);
    BYTE* memory = static_cast<BYTE*>(process_allocator->allocate_bytes(
        track_formats[track_index].preload_bytes, "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\sound.cpp:653 char"));
    if (!memory) {
        CloseHandle(file);
        sound_log("error : bgmfile is not find %s\r\n", music_file);
        return -1;
    }
    DWORD read_bytes;
    ReadFile(file, memory, track_formats[track_index].preload_bytes, &read_bytes, nullptr);
    CloseHandle(file);
    preloaded[index].format = &track_formats[track_index];
    preloaded[index].allocation = memory;
    preloaded[index].current = memory;
    preloaded[index].size = preloaded[index].format->preload_bytes;
    return 0;
}

std::int32_t SoundInf::load_track(std::int32_t index) {
    if (!device_owner) return -1;
    if (!process_graphics.configuration.value_75) return -1;
    if (!direct_sound) return -1;
    if (!process_graphics.uses_preloaded_music()) return reopen_track(track_names[index]);
    if (preloaded.size() <= static_cast<std::size_t>(index)) preloaded.resize(index + 1);
    if (!preloaded[index].allocation) return -1;
    strcpy_s(current_track, sizeof current_track, track_names[index]);
    sound_log("Streming BGM Load no %d\r\n", index);
    DWORD block_align = preloaded[index].format->format.nBlockAlign;
    DWORD sample_rate = preloaded[index].format->format.nSamplesPerSec;
    DWORD notification_size = sample_rate * 4 * block_align >> 4;
    notification_size -= notification_size % block_align;
    notification = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    notify_thread = CreateThread(nullptr, 0, sound_notification_thread,
        process_graphics.window_handle, 0, &notify_thread_id);
    HRESULT result = device_owner->create_memory_stream(&stream,
        preloaded[index].current, preloaded[index].size, preloaded[index].format,
        DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2, GUID_NULL, 16,
        notification_size, notification);
    if (result < 0) {
        sound_log("error : "
            "\x83\x58\x83\x67\x83\x8a\x81\x5b\x83\x7e\x83\x93\x83\x4f\x97\x70\x83\x54\x83\x45\x83\x93\x83\x68\x83\x6f\x83\x62\x83\x74\x83\x40\x82\xf0\x8d\xec\x90\xac\x8f\x6f\x97\x88\x82\xdc\x82\xb9\x82\xf1\x82\xc5\x82\xb5\x82\xbd"
            "\r\n");
        return -1;
    }
    sound_log("load comp\r\n");
    preloaded_index = index;
    return 0;
}
}
