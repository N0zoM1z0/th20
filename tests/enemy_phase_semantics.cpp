#include "Enemy.hpp"
#include <array>
#include <cassert>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <vector>

namespace {
struct CopyCall {
    char* destination;
    std::size_t capacity;
    const char* source;
};
std::vector<CopyCall> copies;
using Image = std::array<unsigned char, 136>;

Image initial_record() {
    Image result{};
    const std::int32_t absent = -1;
    std::memcpy(result.data(), &absent, 4);
    std::memcpy(result.data() + 4, &absent, 4);
    return result;
}

void model_name(Image& record, std::size_t offset, const char* name) {
    if (!name) {
        record[offset] = 0;
        return;
    }
    do {
        record[offset++] = static_cast<unsigned char>(*name);
    } while (*name++);
}
}

// Valid, nonoverlapping names are the fixture's explicit CRT boundary. Native
// invalid-parameter handling and oversized inputs are outside this test domain.
extern "C" int strcpy_s(char* destination, std::size_t capacity, const char* source) {
    assert(destination && source && capacity == 64);
    const auto length = std::strlen(source);
    assert(length < capacity);
    copies.push_back({destination, capacity, source});
    std::memcpy(destination, source, length + 1);
    return 0;
}

void check_enemy_phases(th20::Enemy& enemy) {
    static_assert(sizeof(th20::EnemyPhase) == 136);
    auto& phases = enemy.state.phases;
    assert(phases.empty());
    std::vector<Image> model;
    const auto verify = [&] {
        assert(phases.size() == model.size());
        for (std::size_t i = 0; i != model.size(); ++i)
            assert(std::memcmp(&phases[i], model[i].data(), model[i].size()) == 0);
    };
    const auto grow_model = [&](std::uint32_t index) {
        if (model.size() <= index) model.resize(index + 1, initial_record());
    };
    const auto configure = [&](std::uint32_t index, std::int32_t life,
                               std::int32_t time, const char* name) {
        grow_model(index);
        auto& expected = model[index];
        std::memcpy(expected.data(), &life, 4);
        if (life >= 0) {
            std::memcpy(expected.data() + 4, &time, 4);
            model_name(expected, 8, name);
            model_name(expected, 72, name);
        }
        copies.clear();
        enemy.configure_phase(index, life, time, name);
        assert(copies.size() == (life >= 0 && name ? 2u : 0u));
        if (!copies.empty()) {
            assert(copies[0].destination == phases[index].script);
            assert(copies[1].destination == phases[index].timeout_script);
            for (const auto& call : copies)
                assert(call.capacity == 64 && call.source == name);
        }
        verify();
    };
    const auto timeout = [&](std::uint32_t index, const char* name) {
        grow_model(index);
        model_name(model[index], 72, name);
        copies.clear();
        enemy.configure_timeout(index, name);
        assert(copies.size() == (name ? 1u : 0u));
        if (!copies.empty())
            assert(copies[0].destination == phases[index].timeout_script &&
                   copies[0].capacity == 64 && copies[0].source == name);
        verify();
    };

    std::array<char, 64> longest;
    longest.fill('P');
    longest.back() = 0;
    const std::array<const char*, 4> names{longest.data(), "", nullptr, "phase-entry"};
    const std::array<std::int32_t, 5> lives{
        std::numeric_limits<std::int32_t>::min(), -1, 0, 1,
        std::numeric_limits<std::int32_t>::max()};
    const std::array<std::int32_t, 3> times{
        std::numeric_limits<std::int32_t>::min(), 0,
        std::numeric_limits<std::int32_t>::max()};
    unsigned transitions = 0;
    for (std::uint32_t index : {0u, 3u, 1u, 17u, 0u, 31u})
        for (auto life : lives)
            for (auto time : times)
                for (const char* name : names) {
                    configure(index, life, time, name);
                    timeout(index, names[(transitions / 2 + 1) % names.size()]);
                    transitions += 2;
                }
    assert(transitions == 720);

    // Reuse dirty retained capacity: gaps must receive the observed full defaults
    // before a negative-life producer declines to write time or either name.
    const auto capacity = phases.capacity();
    phases.clear();
    model.clear();
    configure(2, -1, 123, nullptr);
    timeout(4, nullptr);
    assert(phases.capacity() == capacity);

    // Unsigned index+1 wraps to zero, so the non-null branch's checked access
    // throws before a CRT call. The unchecked null branch is outside this domain.
    copies.clear();
    bool threw = false;
    try {
        enemy.configure_timeout(std::numeric_limits<std::uint32_t>::max(), "timeout");
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw && copies.empty());
    verify();
    phases.clear();
}
