#pragma once
// Windows uses the actual locked SDK. Portable CPU checks fixture only these
// OS calls, retaining the native 32-bit DWORD width and the same argument order.
#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#define TH20_FILE_NATIVE_NAME(path) (path).c_str()
#else
#include <cstdint>
using DWORD=std::uint32_t;
using HANDLE=void*;
using LPWSTR=wchar_t*;
inline HANDLE const INVALID_HANDLE_VALUE=reinterpret_cast<HANDLE>(static_cast<std::intptr_t>(-1));
inline constexpr DWORD GENERIC_WRITE=0x40000000, FILE_SHARE_READ=1,
    CREATE_ALWAYS=2, FILE_ATTRIBUTE_NORMAL=0x80;
extern "C" {
HANDLE CreateFileW(const wchar_t*, DWORD, DWORD, void*, DWORD, DWORD, HANDLE);
int WriteFile(HANDLE, const void*, DWORD, DWORD*, void*);
int CloseHandle(HANDLE);
DWORD GetLastError();
DWORD FormatMessageW(DWORD, const void*, DWORD, DWORD, LPWSTR, DWORD, void*);
void* LocalFree(void*);
}
// std::filesystem::path has char storage on the portable host. Convert only
// at the wide OS fixture boundary; Windows already stores wchar_t natively.
#define TH20_FILE_NATIVE_NAME(path) (path).wstring().c_str()
#endif
