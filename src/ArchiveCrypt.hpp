#pragma once

#include <cstdint>

namespace th20 {

// REF-004: caller supplies the exact byte count, including embedded zeros if
// present. The wrapped sum feeds the archive parameter-table index; parameter
// selection and in-place decryption are separate unreconstructed contributions.
std::uint8_t archive_name_sum(const char* name, std::uint32_t size);

} // namespace th20
