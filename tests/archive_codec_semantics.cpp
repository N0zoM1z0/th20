#include "ArchiveCrypt.hpp"
#include "ArchiveLzss.hpp"
#include "DiagnosticAllocator.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <vector>

namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;

// Owned fixture lifetime for the otherwise undefined native startup constructor.
// This does not supply or claim a production reconstruction of 0x0041F5B0.
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
}

namespace {
using Byte = std::uint8_t;

struct Tokens {
    std::vector<Byte> bytes;
    unsigned used = 0;
    void bits(unsigned value, unsigned count) {
        for (unsigned i = count; i != 0; --i) {
            if (used % 8 == 0) bytes.push_back(0);
            bytes.back() |= ((value >> (i - 1)) & 1u) << (7 - used % 8);
            ++used;
        }
    }
    void literal(Byte value) { bits(1, 1); bits(value, 8); }
    void reference(unsigned offset, unsigned count) {
        assert(offset > 0 && offset < 8192 && count >= 3 && count <= 18);
        bits(0, 1); bits(offset, 13); bits(count - 3, 4);
    }
    void end() { bits(0, 1); bits(0, 13); }
};

// Independent logical bit reader: exhausted bits are zero. It does not use the
// maintained fetch macros, cursor code or ring storage.
std::vector<Byte> decode_model(const Tokens& tokens, std::array<Byte, 8192>& ring) {
    std::size_t bit = 0;
    unsigned cursor = 1;
    auto read = [&](unsigned count) {
        unsigned value = 0;
        while (count--) {
            value *= 2;
            if (bit < tokens.bytes.size() * 8)
                value += (tokens.bytes[bit / 8] >> (7 - bit % 8)) & 1;
            ++bit;
        }
        return value;
    };
    std::vector<Byte> result;
    for (;;) {
        if (read(1)) {
            auto byte = static_cast<Byte>(read(8));
            result.push_back(byte); ring[cursor] = byte;
            cursor = (cursor + 1) % ring.size();
        } else {
            unsigned offset = read(13);
            if (!offset) return result;
            unsigned count = read(4) + 3;
            for (unsigned i = 0; i < count; ++i) {
                Byte byte = ring[(offset + i) % ring.size()];
                result.push_back(byte); ring[cursor] = byte;
                cursor = (cursor + 1) % ring.size();
            }
        }
    }
}

void decoder() {
    th20::archive_lzss_reset();
    std::array<Byte, 8192> ring{};
    std::vector<Tokens> streams(5);
    for (Byte b : {'A', 'B', 'C', 'D'}) streams[0].literal(b);
    streams[0].end();
    streams[1].reference(1, 4); streams[1].end();
    streams[2].literal('X'); streams[2].reference(1, 18); streams[2].end();
    for (unsigned i = 0; i < 9000; ++i) streams[3].literal(static_cast<Byte>(i * 37));
    streams[3].reference(8191, 18); streams[3].end();
    streams[4].end();
    for (const auto& stream : streams) {
        auto expected = decode_model(stream, ring);
        auto input = stream.bytes;
        auto size = static_cast<std::int32_t>(input.size());
        input.push_back(0xFF); // Readable guard, deliberately not zero.
        std::vector<Byte> output(expected.size() + 16, 0xCE);
        Byte* result = th20::archive_decompress(input.data(), size, output.data() + 8, 0);
        assert(result == output.data() + 8);
        assert(std::equal(expected.begin(), expected.end(), result));
        for (unsigned i = 0; i < 8; ++i) {
            assert(output[i] == 0xCE);
            assert(output[output.size() - 1 - i] == 0xCE);
        }
        assert(std::equal(ring.begin(), ring.end(), th20::archive_dictionary));
    }
    std::array<Byte, 2> exhausted{0x80, 0xFF};
    std::array<Byte, 4> output{0xCE, 0xCE, 0xCE, 0xCE};
    th20::archive_decompress(exhausted.data(), 1, output.data() + 1, 0);
    assert(output[0] == 0xCE && output[1] == 0 && output[2] == 0xCE);
    Byte guard = 0xFF;
    th20::archive_decompress(&guard, 0, output.data(), 0);
    assert(output[0] == 0xCE);

    Tokens owned;
    owned.literal('a'); owned.literal('b'); owned.literal('c'); owned.end();
    owned.bytes.push_back(0xFF);
    Byte* allocated = th20::archive_decompress(owned.bytes.data(),
        static_cast<std::int32_t>(owned.bytes.size() - 1), nullptr, 3);
    assert(allocated && std::memcmp(allocated, "abc", 3) == 0);
    th20::process_allocator->release_bytes(allocated);
    assert(th20::archive_decompress(nullptr, 0, nullptr, -1) == nullptr);
}

void crypt() {
    for (int block : {8, 16, 128, 256}) {
        for (int size : {0, 1, 2, 7, 17, 129, 257, 515}) {
            for (int limit : {block, block * 2, block * 4}) {
                std::vector<Byte> original(size + 16, 0xD7);
                for (int i = 0; i < size; ++i) original[i + 8] = static_cast<Byte>(i * 73 + 19);
                auto expected = original;
                int tail = size % block < block / 4 ? size % block : 0;
                int remaining = size - tail - (size % 2);
                unsigned key = 0xF3;
                int consumed = 0;
                for (int start = 0; start < remaining && start < limit; start += block) {
                    int count = std::min(block, remaining - start);
                    for (int parity : {count - 1, count - 2}) {
                        for (int index = parity; index >= 0; index -= 2) {
                            expected[8 + start + index] = original[8 + consumed++] ^ key;
                            key = (key + 0xAD) & 255;
                        }
                    }
                }
                assert(consumed <= std::min(size, limit));
                auto actual = original;
                auto result = th20::archive_decrypt(actual.data() + 8, size, 0xF3, 0xAD, block, limit);
                assert(result == actual.data() + 8 && actual == expected);
            }
        }
    }
}

void allocation() {
    // A nested real guard verifies recursive use of the shared slot, including
    // when the registry's separate tracking switch is disabled.
    std::lock_guard<std::recursive_mutex> guard(th20::process_locks.slot(1));
    assert(!th20::process_locks.enabled());
    auto* bytes = static_cast<Byte*>(th20::process_allocator->allocate_bytes(37, "fixture"));
    assert(bytes); std::memset(bytes, 0xA5, 37);
    th20::process_allocator->release_bytes(bytes);
    th20::process_allocator->release_bytes(nullptr);
    auto* array = th20::process_allocator->allocate_array<Byte>("fixture", 19);
    assert(array); std::memset(array, 0xBC, 19);
    TH20_RELEASE_ARRAY_AND_RESET(array);
    assert(!array);
    th20::process_allocator->release_array<Byte>(nullptr);

    th20::DebugMemoryResource resource;
    for (std::size_t alignment : {64, 256}) {
        void* memory = resource.allocate(37, alignment);
        assert(reinterpret_cast<std::uintptr_t>(memory) % alignment == 0);
        std::memset(memory, 0xA7, 37);
        resource.deallocate(memory, 37, alignment);
    }
    assert(resource.is_equal(*std::pmr::new_delete_resource()));
}

void tree() {
    using th20::archive_lzss_nodes;
    th20::archive_dictionary[7] = 0xAF;
    archive_lzss_nodes[8192] = {2, 3, 4};
    th20::archive_lzss_reset();
    assert(th20::archive_dictionary[7] == 0 && archive_lzss_nodes[8192].right == 0);
    th20::archive_lzss_set_root(20);
    assert(archive_lzss_nodes[8192].right == 20 && archive_lzss_nodes[20].parent == 8192);
    for (int i = 0; i < 18; ++i) {
        th20::archive_dictionary[20 + i] = 80;
        th20::archive_dictionary[100 + i] = 40;
        th20::archive_dictionary[200 + i] = 120;
        th20::archive_dictionary[300 + i] = 60;
        th20::archive_dictionary[400 + i] = 80;
    }
    std::int32_t match = 0x1234;
    assert(th20::archive_lzss_insert(0, &match) == 0 && match == 0x1234);
    assert(th20::archive_lzss_insert(100, &match) == 0 && match == 20);
    assert(th20::archive_lzss_insert(200, &match) == 0 && match == 20);
    assert(th20::archive_lzss_insert(300, &match) == 0 && match == 100);
    assert(th20::archive_lzss_predecessor(20) == 300);
    assert(th20::archive_lzss_insert(400, &match) == 18 && match == 20);
    assert(archive_lzss_nodes[20].parent == 0 && archive_lzss_nodes[8192].right == 400);
    assert(archive_lzss_nodes[100].parent == 400 && archive_lzss_nodes[200].parent == 400);
    th20::archive_lzss_remove(400);
    assert(archive_lzss_nodes[8192].right == 300 && archive_lzss_nodes[400].parent == 0);
    assert(archive_lzss_nodes[100].parent == 300 && archive_lzss_nodes[200].parent == 300);
    th20::archive_lzss_remove(300); // Two-child replacement whose predecessor is a leaf.
    assert(archive_lzss_nodes[8192].right == 100);
    th20::archive_lzss_remove(100); // Single right child.
    assert(archive_lzss_nodes[8192].right == 200 && archive_lzss_nodes[200].parent == 8192);
    th20::archive_lzss_remove(200); // Final leaf; slot zero receives the sentinel parent.
    assert(archive_lzss_nodes[8192].right == 0 && archive_lzss_nodes[0].parent == 8192);
    th20::archive_lzss_set_root(500);
    archive_lzss_nodes[500].left = 600;
    archive_lzss_nodes[600] = {500, 0, 0};
    th20::archive_lzss_remove(500); // Single left child.
    assert(archive_lzss_nodes[8192].right == 600);
    th20::archive_lzss_remove(500); // Already unlinked: no changes.
    assert(archive_lzss_nodes[8192].right == 600);
}
}

int main() {
    th20::DiagnosticAllocator allocator;
    th20::process_allocator = &allocator;
    allocation(); crypt(); decoder(); tree();
    th20::process_allocator = nullptr;
}
