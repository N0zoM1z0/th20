#include "ScoreEntry.hpp"
#include "HudGauge.hpp"
#include "OverlayCounter.hpp"

#include <array>
#include <cassert>
#include <cstddef>
#include <new>

namespace {
template<class T, class Check>
void check_dirty_construction(Check check) {
    alignas(T) std::array<unsigned char, sizeof(T) + 8> storage;
    for (unsigned seed = 1; seed != 256; ++seed) {
        storage.fill(static_cast<unsigned char>(seed));
        auto* value = ::new(storage.data() + 4) T;
        check(*value, storage.data() + 4, static_cast<unsigned char>(seed));
        for (std::size_t i = 0; i != 4; ++i) {
            assert(storage[i] == seed);
            assert(storage[sizeof(T) + 4 + i] == seed);
        }
        value->~T();
    }
}
}

void check_display_values() {
    check_dirty_construction<th20::ScoreEntry>(
        [](const auto& entry, const unsigned char* bytes, unsigned char seed) {
            for (auto digit : entry.digits) assert(digit == 0);
            assert(entry.position.x == 0.0f && entry.position.y == 0.0f &&
                   entry.position.z == 0.0f);
            assert(entry.speed == 0.0f && entry.color == 0);
            assert(entry.age.previous == 0 && entry.age.current == 0 &&
                   entry.age.current_fraction == 0.0f && entry.age.flags == 0);
            assert(entry.value_30 == 0.0f && entry.value_34 == 0.0f);
            assert(entry.active == 0 && entry.length == 0 && entry.bonus == 0 &&
                   entry.multiplier == 0.0f);
            // Native construction leaves these two alignment bytes untouched.
            assert(bytes[0x3a] == seed && bytes[0x3b] == seed);
            for (std::size_t i = 0; i != sizeof(entry); ++i) {
                if (i != 0x3a && i != 0x3b) assert(bytes[i] == 0);
            }
        });
    check_dirty_construction<th20::HudGauge>(
        [](const auto& gauge, const unsigned char* bytes, unsigned char) {
            assert(gauge.fraction == 0.0f && gauge.value_04 == 0);
            for (std::size_t i = 0; i != sizeof(gauge); ++i) assert(bytes[i] == 0);
        });
    check_dirty_construction<th20::OverlayCounter>(
        [](const auto& counter, const unsigned char*, unsigned char) {
            assert(counter.current == 0 && counter.threshold == 1500);
        });
}
