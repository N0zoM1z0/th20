#include "ProgressSaveManager.hpp"
#include "ProgressFileNames.hpp"
#include "DiagnosticAllocator.hpp"
#include "DiagnosticLog.hpp"
#include "ArchiveCrypt.hpp"
#include "ArchiveLzss.hpp"
#include "GameFileIo.hpp"
#include "WindowState.hpp"
#include "EclDiagnostic.hpp"
#include "LockRegistry.hpp"
#include <cstring>
#include <filesystem>
#include "ProgressRanges.hpp"

namespace th20 {
const char progress_file_staging_label[]="D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\score.cpp:252 char";
const char progress_file_write_error[]="error : スコアファイルが書き込めない\n";
const char progress_backup_filename[]="scoreth20bak.dat";
const char progress_current_filename[]="scoreth20.dat";
const char progress_save_end[]="Score.SaveThread end\n";

std::int32_t ProgressSaveManager::write(const char* filename, ProgressSnapshot* snapshot) {
    if (!snapshot->file_buffer) return -1;
    auto* staging=static_cast<char*>(process_allocator->allocate_bytes(
        0x200000, progress_file_staging_label));
    std::int32_t count=0;
    std::memcpy(staging+count, snapshot->file_buffer, sizeof(ProgressFileHeader));
    count+=sizeof(ProgressFileHeader);
    for (auto character : ProgressCharacters::all) {
        for (auto index : ProgressProfiles::all) {
            if (snapshot->profiles[character][index].header.magic==0x5243) {
                snapshot->profiles[character][index].field_0c=character;
                snapshot->profiles[character][index].field_10=index;
                snapshot->profiles[character][index].header.checksum=
                    snapshot->profiles[character][index].header.calculate_checksum(sizeof(ProgressProfile));
                std::memcpy(staging+count, &snapshot->profiles[character][index], sizeof(ProgressProfile));
                count+=sizeof(ProgressProfile);
            }
        }
    }
    snapshot->fallback.field_0c=2;
    snapshot->fallback.header.checksum=snapshot->fallback.header.calculate_checksum(sizeof(ProgressProfile));
    std::memcpy(staging+count, &snapshot->fallback, sizeof(ProgressProfile));
    count+=sizeof(ProgressProfile);
    snapshot->metadata.header.checksum=snapshot->metadata.header.calculate_checksum(sizeof(ProgressMetadata));
    std::memcpy(staging+count, &snapshot->metadata, sizeof(ProgressMetadata));
    count+=sizeof(ProgressMetadata);
    const auto* payload_bytes=reinterpret_cast<const std::uint8_t*>(staging);
    reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->decoded_size=count-sizeof(ProgressFileHeader);
    auto* compressed=archive_compress(&payload_bytes[sizeof(ProgressFileHeader)],
        reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->decoded_size, reinterpret_cast<std::int32_t*>(&reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->compressed_size));
    reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->file_size=reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->compressed_size+sizeof(ProgressFileHeader);
    archive_encrypt(compressed, reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->compressed_size, 0xac, 0x35, 16, reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->compressed_size);
    {
        std::filesystem::path path(window_state.user_data_directory);
        path/=filename;
        const auto narrow=path.string();
        const auto* output_path=narrow.c_str();
        if (open_game_output(output_path)) {
            report_log_error(&diagnostic_log, progress_file_write_error);
            TH20_RELEASE_BYTES_AND_RESET(compressed);
            TH20_RELEASE_BYTES_AND_RESET(staging);
            return -1;
        }
        write_game_output(snapshot->file_buffer, sizeof(ProgressFileHeader));
        write_game_output(compressed, reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->compressed_size);
        close_game_output();
        TH20_RELEASE_BYTES_AND_RESET(compressed);
    }
    TH20_RELEASE_BYTES_AND_RESET(staging);
    return 0;
}

void ProgressSaveManager::save(void*) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(20));
    write(progress_backup_filename, &backup);
    write(progress_current_filename, &current);
    copy_current_to_backup();
    ecl_diagnostic_hint(progress_save_end);
}
} // namespace th20
