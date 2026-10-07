#include "ArchiveLzss.hpp"
#include "DiagnosticAllocator.hpp"

namespace th20 {

std::uint8_t archive_dictionary[8192];
const char lzss_output_label[] = "D:\\cygwin\\home\\zun\\prog\\th20\\src\\pack\\LzssUtil.cpp:202 BYTE";

// Shared MSB-first token reader. Preserve the native fetch before the length
// check; exhausted input synthesizes zero bits without advancing the cursor.
#define ARCHIVE_FETCH_BYTE() \
    if (mask == 0x80) { \
        current_byte = *input; \
        if (input - compressed >= input_size) current_byte = 0; \
        else ++input; \
    }
#define ARCHIVE_NEXT_BIT() \
    mask >>= 1; \
    if (!mask) mask = 0x80;
#define ARCHIVE_READ_BITS(first_weight) \
    weight = first_weight; \
    value = 0; \
    while (weight) { \
        ARCHIVE_FETCH_BYTE() \
        if (current_byte & mask) value |= weight; \
        weight >>= 1; \
        ARCHIVE_NEXT_BIT() \
    }

std::uint8_t* archive_decompress(const std::uint8_t* compressed, std::int32_t size,
    std::uint8_t* output, std::int32_t output_size) {
    std::uint8_t mask = 0x80;
    std::uint32_t current_byte = 0;
    std::int32_t input_size = size;
    if (!output) {
        output = static_cast<std::uint8_t*>(process_allocator->allocate_bytes(output_size, lzss_output_label));
        if (!output) return nullptr;
    }
    const std::uint8_t* input = compressed;
    std::uint8_t* cursor = output;
    std::int32_t ring_cursor = 1;
    std::uint32_t weight, value;
    for (;;) {
        ARCHIVE_FETCH_BYTE()
        value = current_byte & mask;
        ARCHIVE_NEXT_BIT()
        if (value) {
            ARCHIVE_READ_BITS(0x80)
            *cursor = static_cast<std::uint8_t>(value);
            ++cursor;
            archive_dictionary[ring_cursor] = static_cast<std::uint8_t>(value);
            ring_cursor = (ring_cursor + 1) & 0x1fff;
        } else {
            ARCHIVE_READ_BITS(0x1000)
            std::int32_t offset = value;
            if (!offset) break;
            ARCHIVE_READ_BITS(8)
            std::int32_t count = value + 2;
            for (std::int32_t i = 0; i <= count; ++i) {
                std::uint32_t byte = archive_dictionary[(offset + i) & 0x1fff];
                *cursor = static_cast<std::uint8_t>(byte);
                ++cursor;
                archive_dictionary[ring_cursor] = static_cast<std::uint8_t>(byte);
                ring_cursor = (ring_cursor + 1) & 0x1fff;
            }
        }
    }
    return output;
}
#undef ARCHIVE_READ_BITS
#undef ARCHIVE_NEXT_BIT
#undef ARCHIVE_FETCH_BYTE

} // namespace th20
