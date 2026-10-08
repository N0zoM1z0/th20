#pragma once
#include <cstddef>
#include <cstdint>

namespace th20 {
// Common CR/ST disk prefix, independently used by parsing and checksums.
struct ProgressRecordHeader {
    std::uint16_t magic, version;
    std::uint32_t checksum, size;
    ProgressRecordHeader();
    // Sum bytes [8,extent) of the complete containing CR/ST record. The signed
    // extent and readable containing storage are supplied by the caller.
    std::uint32_t calculate_checksum(std::int32_t extent) const;
};
// The 60-element score array and 63-element practice array have natural
// eight-byte alignment. Their constructors leave compiler padding alone.
struct ProgressScore {
    std::int64_t score=0;
    std::uint8_t stage=0, continues=0;
    char name[10]{};
    std::int64_t timestamp=0;
    float slowdown=0;
};
struct PracticeScore {
    std::int64_t score;
    std::int8_t field_08, field_09;
    std::uint8_t field_0a[2];
    PracticeScore();
    bool available() const;
};
static_assert(sizeof(ProgressRecordHeader) == 12);
static_assert(sizeof(ProgressScore) == 40);
static_assert(offsetof(ProgressScore, timestamp) == 24);
static_assert(sizeof(PracticeScore) == 16);
} // namespace th20
