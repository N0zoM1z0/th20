#include "GameFileIo.hpp"
#include "Win32FileApi.hpp"
#include "LockRegistry.hpp"
#include "EclDiagnostic.hpp"
#include <filesystem>

namespace th20 {
const char file_output_error[]="error : %s write error %s\r\n";
const char file_output_open[]="%s open ...\r\n";
const char file_output_short[]="error : write error\r\n";
const char file_output_written[]="write ...\r\n";
const char file_output_closed[]="close ...\r\n";

std::int32_t open_game_output(const char* filename) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(2));
    std::filesystem::path path(filename);
    game_file_handle=CreateFileW(TH20_FILE_NATIVE_NAME(path), GENERIC_WRITE, FILE_SHARE_READ,
        nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (game_file_handle==INVALID_HANDLE_VALUE) {
        wchar_t* message=nullptr;
        FormatMessageW(0x1300, nullptr, GetLastError(), 0x400,
            reinterpret_cast<LPWSTR>(&message), 0, nullptr);
        ecl_diagnostic_hint(file_output_error, filename, message);
        LocalFree(message);
        return -1;
    }
    ecl_diagnostic_hint(file_output_open, filename);
    return 0;
}

std::int32_t write_game_output(const void* bytes, std::uint32_t size) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(2));
    if (game_file_handle==INVALID_HANDLE_VALUE) return -1;
    DWORD written;
    WriteFile(game_file_handle, bytes, size, &written, nullptr);
    if (size!=written) {
        CloseHandle(game_file_handle);
        ecl_diagnostic_hint(file_output_short);
        return -2;
    }
    ecl_diagnostic_hint(file_output_written);
    return 0;
}

std::int32_t close_game_output() {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(2));
    if (game_file_handle==INVALID_HANDLE_VALUE) return 0;
    CloseHandle(game_file_handle);
    ecl_diagnostic_hint(file_output_closed);
    return 0;
}
} // namespace th20
