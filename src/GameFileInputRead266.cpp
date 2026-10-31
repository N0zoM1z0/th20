// Original complete 266B game-owned persistent-input file reader.
// Borrow the actual 0x005AE060 HANDLE opened by 368B CP932 game opener.
// The native ReadFile BOOL/partial read count is not inspected or retried.
#include "DiagnosticAllocator.hpp"
#include "GameFileIo.hpp"
#include "Win32FileApi.hpp"
#include "LockRegistry.hpp"
#include "EclDiagnostic.hpp"
#include <cstdint>
#include <mutex>
namespace th20 {
void* read_game_input_bytes_410990(std::uint32_t length) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(2));
    if (game_file_handle==INVALID_HANDLE_VALUE) return nullptr;
    void* memory=process_allocator->allocate_bytes(
        static_cast<std::int32_t>(length),
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\filectrl.cpp:496 void");
    if (!memory) {
        CloseHandle(game_file_handle);
        return nullptr;
    }
    DWORD bytes_read;
    ReadFile(game_file_handle,memory,length,&bytes_read,nullptr);
    ecl_diagnostic_hint("Read ...\r\n");
    return memory;
}
}
