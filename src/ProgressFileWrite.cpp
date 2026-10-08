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
#include <ranges>

namespace th20 {
const char progress_file_staging_label[]="D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\score.cpp:252 char";
const char progress_file_write_error[]="error : スコアファイルが書き込めない\n";
const char progress_backup_filename[]="scoreth20bak.dat";
const char progress_current_filename[]="scoreth20.dat";
const char progress_save_end[]="Score.SaveThread end\n";

std::int32_t ProgressSaveManager::write(const char* filename, ProgressSnapshot* snapshot) {
    if (!snapshot->file_buffer) return -1;
    auto* staging=static_cast<std::uint8_t*>(process_allocator->allocate_bytes(
        0x200000, progress_file_staging_label));
    std::int32_t count=0;
    std::memcpy(staging+count, snapshot->file_buffer, sizeof(ProgressFileHeader));
    count+=sizeof(ProgressFileHeader);
    for (auto character : std::views::iota(0,2)) {
        for (auto index : std::views::iota(0,9)) {
            if (snapshot->profiles[character][index].header.magic==0x5243) {
                snapshot->profiles[character][index].field_0c=character;
                snapshot->profiles[character][index].field_10=index;
                auto& header=snapshot->profiles[character][index].header;
                header.checksum=header.calculate_checksum(sizeof(ProgressProfile));
                std::memcpy(staging+count, &snapshot->profiles[character][index], sizeof(ProgressProfile));
                count+=sizeof(ProgressProfile);
            }
        }
    }
    snapshot->fallback.field_0c=2;
    auto& fallback_header=snapshot->fallback.header;
    fallback_header.checksum=fallback_header.calculate_checksum(sizeof(ProgressProfile));
    std::memcpy(staging+count, &snapshot->fallback, sizeof(ProgressProfile));
    count+=sizeof(ProgressProfile);
    auto& metadata_header=snapshot->metadata.header;
    metadata_header.checksum=metadata_header.calculate_checksum(sizeof(ProgressMetadata));
    std::memcpy(staging+count, &snapshot->metadata, sizeof(ProgressMetadata));
    count+=sizeof(ProgressMetadata);
    auto* file_header=reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer);
    file_header->decoded_size=count-sizeof(ProgressFileHeader);
    auto* compressed=archive_compress(staging+sizeof(ProgressFileHeader),
        file_header->decoded_size, reinterpret_cast<std::int32_t*>(&file_header->compressed_size));
    file_header->file_size=file_header->compressed_size+sizeof(ProgressFileHeader);
    archive_encrypt(compressed, file_header->compressed_size, 0xac, 0x35, 16, file_header->compressed_size);
    std::filesystem::path path(window_state.user_data_directory);
    path/=filename;
    const auto narrow=path.string();
    const auto* output_path=narrow.c_str();
    if (open_game_output(output_path)) {
        report_log_error(&diagnostic_log, progress_file_write_error);
        if (compressed) TH20_RELEASE_BYTES_AND_RESET(compressed);
        if (staging) TH20_RELEASE_BYTES_AND_RESET(staging);
        return -1;
    }
    write_game_output(snapshot->file_buffer, sizeof(ProgressFileHeader));
    write_game_output(compressed, file_header->compressed_size);
    close_game_output();
    if (compressed) TH20_RELEASE_BYTES_AND_RESET(compressed);
    if (staging) TH20_RELEASE_BYTES_AND_RESET(staging);
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
