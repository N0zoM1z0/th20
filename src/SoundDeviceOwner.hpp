#pragma once
#include "SoundInf.hpp"

namespace th20 {
// Native factories access the actual DirectSound pointer at owner offset zero.
// Original initialization/retirement and factory implementation remain open.
struct SoundDeviceOwner {
    IDirectSound8* direct_sound;
    SoundDeviceOwner();
    ~SoundDeviceOwner();
    HRESULT create_memory_stream(StreamingSound**, BYTE*, ULONG, TrackFormat*,
        DWORD, GUID, DWORD, DWORD, HANDLE);
};
static_assert(sizeof(void*) != 4 || sizeof(SoundDeviceOwner) == 4);
}
