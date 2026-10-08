#pragma once

#include <cstdint>

namespace th20 {

// REF-004: caller supplies the exact byte count, including embedded zeros if
// present. The wrapped sum feeds the archive parameter-table index; parameter
// selection is maintained by the shared archive owner.
std::uint8_t archive_name_sum(const char* name, std::uint32_t size);

// Original signed six-argument protocol. Valid archive parameters have positive
// even blocks and a copy limit covering each transformed block. Odd/small tails
// remain untouched. Returns the original pointer; scratch storage uses new[].
std::uint8_t* archive_decrypt(std::uint8_t* data, std::int32_t size,
    std::uint8_t key, std::uint8_t step, std::int32_t block, std::int32_t limit);

// Inverse permutation with the same signed parameters, retained tails and
// caller-owned input pointer. Scratch allocation and release use new[]/delete[].
std::uint8_t* archive_encrypt(std::uint8_t* data, std::int32_t size,
    std::uint8_t key, std::uint8_t step, std::int32_t block, std::int32_t limit);

} // namespace th20
