#pragma once
#include "Win32FileApi.hpp"
// Platform bindings only. Windows builds use the actual locked SDK; portable
// checks supply the same logical API records and capture the unresolved calls.
#if defined(_WIN32)
#include <mmsystem.h>
#include <dsound.h>
#include <cguid.h>
#else
#include <cstddef>
using BYTE = std::uint8_t;
using BOOL = std::int32_t;
using ULONG = std::uint32_t;
using HWND = void*;
using WCHAR = wchar_t;
using HRESULT = std::int32_t;
#define WINAPI
struct IDirectSound8;
inline constexpr int MAX_PATH=260;
inline constexpr DWORD FILE_BEGIN=0;
inline constexpr BOOL FALSE=0;
inline constexpr DWORD DSBCAPS_CTRLPOSITIONNOTIFY=0x100,
    DSBCAPS_GETCURRENTPOSITION2=0x10000;
#pragma pack(push,1)
struct WAVEFORMATEX {
    std::uint16_t wFormatTag, nChannels;
    std::uint32_t nSamplesPerSec, nAvgBytesPerSec;
    std::uint16_t nBlockAlign, wBitsPerSample, cbSize;
};
#pragma pack(pop)
struct _GUID {
    std::uint32_t Data1;
    std::uint16_t Data2,Data3;
    std::uint8_t Data4[8];
};
using GUID=_GUID;
extern "C" const GUID GUID_NULL;
extern "C" {
HANDLE CreateEventW(void*,BOOL,BOOL,const wchar_t*);
HANDLE CreateThread(void*,std::size_t,DWORD (*)(void*),void*,DWORD,DWORD*);
}
#endif
static_assert(sizeof(WAVEFORMATEX)==18);
static_assert(sizeof(GUID)==16);
