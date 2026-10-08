#pragma once

#include "ProgressProfile.hpp"

namespace th20 {

// TH20 disk prefix, independently consumed by parsing and the complete writer.
// Unknown bytes/words retain neutral names; default creation clears all44 bytes.
struct ProgressFileHeader {
    std::uint32_t magic, file_size, version;
    std::uint32_t spell_size, profile_size, metadata_size, snapshot_size;
    std::uint8_t field_1c[4];
    std::uint32_t field_20, compressed_size, decoded_size;
};
static_assert(sizeof(ProgressFileHeader)==44);
static_assert(offsetof(ProgressFileHeader, compressed_size)==0x24);
static_assert(offsetof(ProgressFileHeader, decoded_size)==0x28);

// ST record. Unknown byte-array roles retain neutral offset names. The name is
// initialized by the separate startup protocol, not by default construction.
struct ProgressMetadata {
    ProgressRecordHeader header;
    char name[10];
    std::uint8_t field_16[32]{}, field_36[32]{}, field_56[2]{}, field_58[8]{};
    std::int64_t field_60=0;
    std::uint8_t field_68[128]{}, field_e8[64]{};
    std::int32_t choices[16]={0,8,8,8,1,8,8,8,0,8,8,8,1,8,8,8};
    std::array<std::uint32_t,9> stones={0,0,0,0,0,0,0,0,9};
    std::array<std::uint32_t,9> used_stones{};
    std::uint8_t salt_1b0[32]{};
    std::uint8_t field_1d0=0, checksum=0, salt_1d2[32]{};

    ProgressMetadata();
    void initialize();
    std::uint32_t calculate_integrity() const;
    void update_integrity();
};

// The enclosing save manager releases these buffers. Snapshot construction
// initializes their slots and constructs eighteen profiles plus one fallback.
struct ProgressSnapshot {
    std::uint32_t file_size=0;
    std::uint8_t* file_buffer=nullptr;
    std::uint8_t* decoded_buffer=nullptr;
    ProgressProfile profiles[2][9];
    ProgressProfile fallback;
    ProgressMetadata metadata;

    ProgressSnapshot() noexcept;
};

static_assert(sizeof(ProgressMetadata)==0x1f8);
static_assert(offsetof(ProgressMetadata, name)==0xc);
static_assert(offsetof(ProgressMetadata, field_16)==0x16);
static_assert(offsetof(ProgressMetadata, field_60)==0x60);
static_assert(offsetof(ProgressMetadata, field_68)==0x68);
static_assert(offsetof(ProgressMetadata, choices)==0x128);
static_assert(offsetof(ProgressMetadata, stones)==0x168);
static_assert(offsetof(ProgressMetadata, used_stones)==0x18c);
static_assert(offsetof(ProgressMetadata, salt_1b0)==0x1b0);
static_assert(offsetof(ProgressMetadata, checksum)==0x1d1);
static_assert(offsetof(ProgressMetadata, salt_1d2)==0x1d2);
#if defined(_M_IX86)
static_assert(offsetof(ProgressSnapshot, profiles)==0x10);
static_assert(offsetof(ProgressSnapshot, fallback)==0x8a460);
static_assert(offsetof(ProgressSnapshot, metadata)==0x91f48);
static_assert(sizeof(ProgressSnapshot)==0x92140);
#endif

} // namespace th20
