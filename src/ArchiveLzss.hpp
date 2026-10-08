#pragma once

#include <cstdint>

namespace th20 {

// Process-shared native storage, used by both compression and decompression.
extern std::uint8_t archive_dictionary[8192];

struct ArchiveLzssNode {
    std::int32_t parent, left, right;
};
extern ArchiveLzssNode archive_lzss_nodes[8193];
static_assert(sizeof(ArchiveLzssNode) == 12);

// Input must include a readable guard byte after size. Tokens must fit output.
// Null output requests malloc storage, released with release_bytes(). The ring
// is retained across calls; the decoder resets only its local cursor to one.
std::uint8_t* archive_decompress(const std::uint8_t* compressed, std::int32_t size,
    std::uint8_t* output, std::int32_t output_size);

// Signed input extent and malloc-owned output. Failure preserves output_size
// and shared storage; success resets the shared ring/tree and reports complete
// bytes only, discarding the final partial byte. Use positive readable extents
// whose token output fits the native twice-input allocation. Zero input's
// terminator can overrun that allocation and is outside the tested domain.
std::uint8_t* archive_compress(const std::uint8_t* data, std::int32_t size,
    std::int32_t* output_size);

void archive_lzss_reset();
void archive_lzss_set_root(std::int32_t index);
std::int32_t archive_lzss_insert(std::int32_t index, std::int32_t* match);
std::int32_t archive_lzss_predecessor(std::int32_t index);
void archive_lzss_unlink(std::int32_t previous, std::int32_t replacement);
void archive_lzss_replace(std::int32_t previous, std::int32_t replacement);
void archive_lzss_remove(std::int32_t index);

} // namespace th20
