#include "ArchiveLzss.hpp"
#include <cstring>

namespace th20 {

ArchiveLzssNode archive_lzss_nodes[8193];

void archive_lzss_reset() {
    std::memset(archive_dictionary, 0, 8192);
    std::memset(archive_lzss_nodes, 0, sizeof(archive_lzss_nodes));
}
void archive_lzss_set_root(std::int32_t index) {
    archive_lzss_nodes[8192].right = index;
    archive_lzss_nodes[index].parent = 8192;
    archive_lzss_nodes[index].right = 0;
    archive_lzss_nodes[index].left = 0;
}
std::int32_t archive_lzss_predecessor(std::int32_t index) {
    std::int32_t cursor = archive_lzss_nodes[index].left;
    while (archive_lzss_nodes[cursor].right) cursor = archive_lzss_nodes[cursor].right;
    return cursor;
}
void archive_lzss_replace(std::int32_t previous, std::int32_t replacement) {
    std::int32_t parent = archive_lzss_nodes[previous].parent;
    if (archive_lzss_nodes[parent].left == previous) archive_lzss_nodes[parent].left = replacement;
    else archive_lzss_nodes[parent].right = replacement;
    archive_lzss_nodes[replacement] = archive_lzss_nodes[previous];
    archive_lzss_nodes[archive_lzss_nodes[replacement].left].parent = replacement;
    archive_lzss_nodes[archive_lzss_nodes[replacement].right].parent = replacement;
    archive_lzss_nodes[previous].parent = 0;
}
std::int32_t archive_lzss_insert(std::int32_t index, std::int32_t* match) {
    std::int32_t difference = 0;
    if (!index) return 0;
    std::int32_t cursor = archive_lzss_nodes[8192].right;
    std::int32_t best = 0;
    for (;;) {
        std::int32_t i;
        for (i = 0; i < 18; ++i) {
            difference = archive_dictionary[(index + i) & 0x1fff] - archive_dictionary[(cursor + i) & 0x1fff];
            if (difference) break;
        }
        if (i >= best) {
            best = i;
            *match = cursor;
            if (best >= 18) {
                archive_lzss_replace(cursor, index);
                return best;
            }
        }
        std::int32_t* branch;
        if (difference >= 0) branch = &archive_lzss_nodes[cursor].right;
        else branch = &archive_lzss_nodes[cursor].left;
        if (!*branch) {
            *branch = index;
            archive_lzss_nodes[index].parent = cursor;
            archive_lzss_nodes[index].right = 0;
            archive_lzss_nodes[index].left = 0;
            return best;
        }
        cursor = *branch;
    }
}
void archive_lzss_unlink(std::int32_t previous, std::int32_t replacement) {
    archive_lzss_nodes[replacement].parent = archive_lzss_nodes[previous].parent;
    if (archive_lzss_nodes[archive_lzss_nodes[previous].parent].right == previous)
        archive_lzss_nodes[archive_lzss_nodes[previous].parent].right = replacement;
    else archive_lzss_nodes[archive_lzss_nodes[previous].parent].left = replacement;
    archive_lzss_nodes[previous].parent = 0;
}
void archive_lzss_remove(std::int32_t index) {
    if (!archive_lzss_nodes[index].parent) return;
    if (!archive_lzss_nodes[index].right) archive_lzss_unlink(index, archive_lzss_nodes[index].left);
    else if (!archive_lzss_nodes[index].left) archive_lzss_unlink(index, archive_lzss_nodes[index].right);
    else {
        std::int32_t replacement = archive_lzss_predecessor(index);
        archive_lzss_remove(replacement);
        archive_lzss_replace(index, replacement);
    }
}

} // namespace th20
