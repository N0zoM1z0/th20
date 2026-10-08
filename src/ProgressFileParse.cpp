#include "ProgressSaveManager.hpp"
#include "DiagnosticAllocator.hpp"
#include "ArchiveCrypt.hpp"
#include "ArchiveLzss.hpp"
#include "EclDiagnostic.hpp"
#include <cstring>

namespace th20 {

// Complete native NUL-terminated diagnostics, shared independently of local
// compiler literal numbering. These names do not assert original source names.
const char progress_file_init[] = "Init ScoreFile\n";
const char progress_file_header_label[] = "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\score.cpp:175 ScoreFileHeaderInf";
const char progress_file_version[] = "Attention : ScoreFile の Version が変わったので作り直しました\n";
const char progress_file_decoded_label[] = "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\score.cpp:201 ScoreChunkInf";
const char progress_file_data_error[] = "error ScoreFile Data Error\n";


std::uint32_t ProgressRecordHeader::calculate_checksum(std::int32_t extent) const {
    const auto* bytes=reinterpret_cast<const std::uint8_t*>(this)+8;
    std::uint32_t sum=0;
    for (std::int32_t index=0; index<extent-8; ++index) sum+=bytes[index];
    return sum;
}

std::int32_t ProgressSaveManager::parse(ProgressSnapshot* snapshot) {
    if (!snapshot->file_buffer) {
create_default:
        ecl_diagnostic_hint(progress_file_init);
        if (snapshot->file_buffer) TH20_RELEASE_BYTES_AND_RESET(snapshot->file_buffer);
        snapshot->file_buffer=static_cast<std::uint8_t*>(process_allocator->allocate_bytes(
            sizeof(ProgressFileHeader), progress_file_header_label));
        std::memset(snapshot->file_buffer, 0, sizeof(ProgressFileHeader));
        reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->magic=0x32304854;
        reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->version=4;
        reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->field_20=0x100;
        reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->spell_size=sizeof(ProgressSpell);
        reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->profile_size=sizeof(ProgressProfile);
        reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->metadata_size=sizeof(ProgressMetadata);
        reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->snapshot_size=sizeof(ProgressSnapshot);
    } else {
        if (reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->magic!=0x32304854 ||
            reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->version!=4 ||
            reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->compressed_size!=snapshot->file_size-static_cast<std::uint32_t>(sizeof(ProgressFileHeader)) ||
            reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->spell_size!=sizeof(ProgressSpell) ||
            reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->profile_size!=sizeof(ProgressProfile) ||
            reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->metadata_size!=sizeof(ProgressMetadata) ||
            reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->snapshot_size!=sizeof(ProgressSnapshot)) {
            ecl_diagnostic_hint(progress_file_version);
            goto create_default;
        }
        archive_decrypt(reinterpret_cast<std::uint8_t*>(&reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)[1]),
            reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->compressed_size,
            0xac,0x35,16,reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->compressed_size);
        auto* compressed=reinterpret_cast<std::uint8_t*>(&reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)[1]);
        snapshot->decoded_buffer=static_cast<std::uint8_t*>(process_allocator->allocate_bytes(
            reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->decoded_size<<2,
            progress_file_decoded_label));
        archive_decompress(compressed, reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->compressed_size,
            snapshot->decoded_buffer,reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->decoded_size);
        std::int32_t remaining=reinterpret_cast<ProgressFileHeader*>(snapshot->file_buffer)->decoded_size;
        auto* cursor=reinterpret_cast<ProgressRecordHeader*>(snapshot->decoded_buffer);
        while (remaining>0) {
            if (cursor->magic==0x5243) {
                if (cursor->version==1 && cursor->calculate_checksum(sizeof(ProgressProfile))==cursor->checksum &&
                    cursor->size==sizeof(ProgressProfile)) {
                    auto* profile=reinterpret_cast<ProgressProfile*>(cursor);
                    if (profile->field_0c!=2) {
                        snapshot->profiles[profile->field_0c][profile->field_10]=*profile;
                    } else snapshot->fallback=*profile;
                }
            } else if (cursor->magic==0x5453) {
                if (cursor->version==2 && cursor->calculate_checksum(sizeof(ProgressMetadata))==cursor->checksum &&
                    cursor->size==sizeof(ProgressMetadata)) {
                    snapshot->metadata=*reinterpret_cast<ProgressMetadata*>(cursor);
                }
            } else {
                ecl_diagnostic_hint(progress_file_data_error);
                break;
            }
            remaining-=cursor->size;
            if (remaining<0) {
                ecl_diagnostic_hint(progress_file_data_error);
                break;
            }
            cursor=reinterpret_cast<ProgressRecordHeader*>(reinterpret_cast<std::uint8_t*>(cursor)+cursor->size);
        }
    }
    return 0;
}
} // namespace th20
