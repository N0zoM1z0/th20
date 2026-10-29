// Original four-byte SprtID value operations from whole-native x86 proof.
#include "SprtID.hpp"

namespace th20 {
bool SprtID::operator==(std::uint32_t rhs) const { return value == rhs; }
std::uint32_t SprtID::operator&(std::uint32_t mask) const { return value & mask; }
void SprtID::operator=(std::uint32_t rhs) { value = rhs; }

// This reference-comparison member is independently a complete original
// 47-byte function called by SprtCtrlInf::getSprt(SprtID) at 0x0044CE8B.
bool SprtID::operator!=(const SprtID& rhs) const { return value != rhs.value; }
} // namespace th20
