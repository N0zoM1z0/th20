#include "ProgressSaveManager.hpp"
#include "ProgressFileNames.hpp"
#include "WindowState.hpp"
#include "EclFileLoader.hpp"
#include "EclDiagnostic.hpp"
#include "LockRegistry.hpp"
#include <filesystem>

namespace th20 {
const char progress_load_end[]="Score.LoadThread end\n";

void ProgressSaveManager::load(void*) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(20));
    std::filesystem::path path(window_state.user_data_directory);
    path/=progress_backup_filename;
    auto narrow=path.string();
    const auto* input_path=narrow.c_str();
    backup.file_buffer=read_game_resource(input_path,
        reinterpret_cast<std::int32_t*>(&backup.file_size), 1);
    backup.metadata.initialize();
    for (std::int32_t character=0; character<2; ++character) {
        for (std::int32_t index=0; index<10; ++index) {
            // Native visits physical Profile storage, revisiting row1[0] and
            // ending at fallback. Start from the complete Snapshot byte view;
            // no out-of-array profiles[character][9] subscript is formed.
            auto* profile=reinterpret_cast<ProgressProfile*>(
                reinterpret_cast<std::uint8_t*>(&backup)+offsetof(ProgressSnapshot,profiles)+
                character*sizeof(backup.profiles[0])+index*sizeof(ProgressProfile));
            profile->initialize();
        }
    }
    parse(&backup);
    path=window_state.user_data_directory;
    path/=progress_current_filename;
    narrow=path.string();
    input_path=narrow.c_str();
    current.file_buffer=read_game_resource(input_path,
        reinterpret_cast<std::int32_t*>(&current.file_size), 1);
    current.metadata.initialize();
    for (std::int32_t character=0; character<2; ++character) {
        for (std::int32_t index=0; index<10; ++index) {
            auto* profile=reinterpret_cast<ProgressProfile*>(
                reinterpret_cast<std::uint8_t*>(&current)+offsetof(ProgressSnapshot,profiles)+
                character*sizeof(current.profiles[0])+index*sizeof(ProgressProfile));
            profile->initialize();
        }
    }
    merge_current();
    ecl_diagnostic_hint(progress_load_end);
}
} // namespace th20
