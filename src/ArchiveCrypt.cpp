#include "ArchiveCrypt.hpp"

namespace th20 {

std::uint8_t archive_name_sum(const char* name, std::uint32_t size) {
    const char* cursor = name;
    std::uint8_t sum = 0;
    while (size--) {
        sum = static_cast<std::uint8_t>(sum + static_cast<std::uint8_t>(*cursor));
        ++cursor;
    }
    return sum;
}

} // namespace th20
