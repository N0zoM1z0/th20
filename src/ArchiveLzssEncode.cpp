#include "ArchiveLzss.hpp"
#include "DiagnosticAllocator.hpp"

namespace th20 {
const char lzss_compressed_label[] = "D:\\cygwin\\home\\zun\\prog\\th20\\src\\pack\\LzssUtil.cpp:57 BYTE";

// Shared MSB-first byte emission. Native discards the final partial byte.
// Native also updates an unobserved local sum. Its protocol owner is unresolved;
// no emission-only accumulator is introduced and this whole body is nonexact.
#define ARCHIVE_ADVANCE_OUTPUT() \
    mask >>= 1; \
    if (!mask) { \
        *output = static_cast<std::uint8_t>(pending); \
        ++output; \
        pending = 0; \
        mask = 0x80; \
    }
#define ARCHIVE_WRITE_BITS(value, first_weight) \
    weight = first_weight; \
    while (weight) { \
        if ((value) & weight) pending |= mask; \
        ARCHIVE_ADVANCE_OUTPUT() \
        weight >>= 1; \
    }
#define ARCHIVE_READ_SOURCE() \
    if (input - data >= size) byte = -1; \
    else { byte = *input; ++input; }

std::uint8_t* archive_compress(const std::uint8_t* data, std::int32_t size,
    std::int32_t* output_size) {
    std::uint8_t mask=0x80;
    std::uint32_t pending=0;
    auto* owned=static_cast<std::uint8_t*>(process_allocator->allocate_bytes(
        static_cast<std::int32_t>(static_cast<std::uint32_t>(size)<<1), lzss_compressed_label));
    if (!owned) return nullptr;
    const auto* input=data;
    auto* output=owned;
    *output_size=0;
    archive_lzss_reset();
    std::int32_t ring=1;
    std::int32_t index, byte;
    for (index=0; index<18; ++index) {
        ARCHIVE_READ_SOURCE()
        if (byte==-1) break;
        archive_dictionary[ring+index]=static_cast<std::uint8_t>(byte);
    }
    std::int32_t available=index;
    archive_lzss_set_root(ring);
    std::int32_t length=0;
    std::int32_t match=0;
    std::uint32_t weight;
    std::int32_t emitted;
    while (available>0) {
        if (length>available) length=available;
        if (length<=2) {
            emitted=1;
            pending |= mask;
            ARCHIVE_ADVANCE_OUTPUT()
            ARCHIVE_WRITE_BITS(archive_dictionary[ring], 0x80)
        } else {
            ARCHIVE_ADVANCE_OUTPUT()
            ARCHIVE_WRITE_BITS(match, 0x1000)
            ARCHIVE_WRITE_BITS(length-3, 8)
            emitted=length;
        }
        for (index=0; index<emitted; ++index) {
            archive_lzss_remove((ring+18)&0x1fff);
            ARCHIVE_READ_SOURCE()
            if (byte==-1) --available;
            else archive_dictionary[(ring+18)&0x1fff]=static_cast<std::uint8_t>(byte);
            ring=(ring+1)&0x1fff;
            if (available) length=archive_lzss_insert(ring,&match);
        }
    }
    ARCHIVE_ADVANCE_OUTPUT()
    ARCHIVE_WRITE_BITS(0, 0x1000)
    *output_size=static_cast<std::int32_t>(output-owned);
    return owned;
}
#undef ARCHIVE_READ_SOURCE
#undef ARCHIVE_WRITE_BITS
#undef ARCHIVE_ADVANCE_OUTPUT
} // namespace th20
