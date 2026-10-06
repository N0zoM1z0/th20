#include "ReplayRecords.hpp"
namespace th20 {
ReplayFileHeader::ReplayFileHeader()
    : magic(0x72303274), version(1), byte_06(0), byte_07(0), byte_08(0),
      field_0c(0), field_10(0x100), field_14(0), byte_18(0), byte_19(0),
      field_1a{}, header_size(0), user_size(0), stage_size(0), packed_size(0),
      unpacked_size(0) {}
} // namespace th20
