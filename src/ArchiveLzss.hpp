#pragma once

#include <cstdint>

namespace th20 {

// Process-shared native storage, also used by the unreconstructed compressor.
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

void archive_lzss_reset();
void archive_lzss_set_root(std::int32_t index);
std::int32_t archive_lzss_insert(std::int32_t index, std::int32_t* match);
std::int32_t archive_lzss_predecessor(std::int32_t index);
void archive_lzss_unlink(std::int32_t previous, std::int32_t replacement);
void archive_lzss_replace(std::int32_t previous, std::int32_t replacement);
void archive_lzss_remove(std::int32_t index);

} // namespace th20
