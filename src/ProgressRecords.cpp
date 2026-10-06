#include "ProgressRecords.hpp"
namespace th20 {
ProgressRecordHeader::ProgressRecordHeader()
    : magic(0), version(0), checksum(0), size(0) {}
ProgressScore::ProgressScore()
    : score(0), stage(0), continues(0), name{}, timestamp(0), slowdown(0) {}
PracticeScore::PracticeScore()
    : score(0), field_08(0), field_09(0), field_0a{} {}
bool PracticeScore::available() const {
    return field_09 != 0 || field_08 != 0;
}
} // namespace th20
