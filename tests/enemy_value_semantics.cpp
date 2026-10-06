#include "EnemyMovement.hpp"
#include "EnemySpawn.hpp"

#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <new>

namespace {
template<class T> void check_construction(unsigned char pattern) {
    // Guard both ends of dirty placement storage; construction must initialize
    // every byte of these padding-free native values without adjacent writes.
    alignas(T) std::array<unsigned char, sizeof(T) + 2 * alignof(T)> storage;
    storage.fill(pattern);
    auto* value = ::new (storage.data() + alignof(T)) T;
    for (unsigned i = 0; i != alignof(T); ++i) {
        assert(storage[i] == pattern);
        assert(storage[alignof(T) + sizeof(T) + i] == pattern);
    }
    for (unsigned i = 0; i != sizeof(T); ++i)
        assert(storage[alignof(T) + i] == 0);
    value->~T();
}
}

void check_enemy_values() {
    for (unsigned char pattern : {0x5a, 0xa5, 0xff}) {
        check_construction<th20::EnemySpawn>(pattern);
        check_construction<th20::EnemyMotionInterpolation>(pattern);
        check_construction<th20::Vector2Interpolation>(pattern);
        check_construction<th20::EnemyMovement>(pattern);
    }

    // The embedded 48-byte variable block is independently resettable. Dirty
    // integer and float representations must not affect the other spawn words.
    th20::EnemySpawn spawn;
    spawn.position.x = -42.0f;
    spawn.health = 1700;
    spawn.flags_1c.bits = 0x80000001u;
    spawn.field_50.value = 0xfedcba98u;
    std::array<unsigned char, 84> before, after;
    std::memcpy(before.data(), &spawn, before.size());
    const std::array<std::uint32_t, 12> dirty{
        1, 0xffffffffu, 0x80000000u, 17,
        0x80000000u, 0x7fc12345u, 0x7f800000u, 0xff800000u,
        0x3f800000u, 0xbf800000u, 0x7fa12345u, 0xffffffffu};
    auto* bytes = reinterpret_cast<unsigned char*>(&spawn);
    std::memcpy(bytes + offsetof(th20::EnemySpawn, variables),
                dirty.data(), sizeof(spawn.variables));
    spawn.variables.reset();
    std::memcpy(after.data(), &spawn, after.size());
    assert(before == after);
}
