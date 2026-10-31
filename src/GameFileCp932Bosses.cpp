// Source-present game-owned Win32 CP932 file creation/read and write Bosses.
// Both original functions use mutex slot 2, a 0x20A-byte UTF16 filename
// staging buffer and actual UTF-8-independent Shift-JIS code page 932.
// Original whole exactness remains pending native MSVC stack/EH lowering.
#include "GameFileIo.hpp"
#include "Win32FileApi.hpp"
#include "LockRegistry.hpp"
#include "EclDiagnostic.hpp"
#include <cstdint>
#include <cstring>
#include <mutex>
namespace th20 {
std::int32_t open_game_input_cp932_410cf0(const char* filename) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(2));
    wchar_t converted[261];
    std::memset(converted,0,0x20a);
    MultiByteToWideChar(932,0,filename,-1,converted,0x104);
    game_file_handle=CreateFileW(converted,GENERIC_READ,FILE_SHARE_READ,
                                  nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,nullptr);
    if (game_file_handle==INVALID_HANDLE_VALUE) {
        wchar_t* error=nullptr;
        FormatMessageW(0x1300,nullptr,GetLastError(),0x400,
                       reinterpret_cast<LPWSTR>(&error),0,nullptr);
        ecl_diagnostic_hint("error : %s write error %s\r\n",filename,error);
        LocalFree(error);
        return -1;
    }
    ecl_diagnostic_hint("%s open ...\r\n",filename);
    return 0;
}
std::int32_t write_game_cp932_file_410e70(const char* filename,
                                          const void* bytes,std::uint32_t size) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(2));
    wchar_t converted[261];
    std::memset(converted,0,0x20a);
    MultiByteToWideChar(932,0,filename,-1,converted,0x104);
    HANDLE file=CreateFileW(converted,GENERIC_WRITE,FILE_SHARE_READ,
                            nullptr,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);
    if (file==INVALID_HANDLE_VALUE) {
        wchar_t* message=nullptr;
        FormatMessageW(0x1300,nullptr,GetLastError(),0x400,
                       reinterpret_cast<LPWSTR>(&message),0,nullptr);
        ecl_diagnostic_hint("error : %s write error %s\r\n",filename,message);
        LocalFree(message);
        return -1;
    }
    DWORD written;
    WriteFile(file,bytes,size,&written,nullptr);
    // Native post-WriteFile compares actual bytes and branches directly
    // to success, leaving the short-write failure as the first path.
    if (size!=written) {
        CloseHandle(file);
        ecl_diagnostic_hint("error : %s write error\r\n",filename);
        return -2;
    }
    CloseHandle(file);
    ecl_diagnostic_hint("%s write ...\r\n",filename);
    return 0;
}
}
