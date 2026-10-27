#include "ProgressStorage.hpp"
#include "GameRandom.hpp"
#include "LockRegistry.hpp"

namespace th20 {
extern GameRandom progress_random;

std::uint8_t ProgressMetadata::calculate_integrity() const {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(20));
    const auto* cursor = &field_58[0];
    std::uint8_t sum = 0;
    // The native x86 traversal compares addresses as signed 32-bit values.
    while (static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(cursor)) <
           static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(this) +
               offsetof(ProgressMetadata, field_1d0))) {
        sum += *cursor;
        ++cursor;
    }
    return sum;
}

void ProgressMetadata::update_integrity() {
    checksum=calculate_integrity();
    auto& first=salt_1b0[progress_random.next()%32];
    ++first;
    ++checksum;
    field_1d0+=2;
    auto& second=salt_1d2[progress_random.next()%32];
    ++second;
}
} // namespace th20
