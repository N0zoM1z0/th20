#include "HudGauge.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <new>
#include <stdexcept>
#include <tuple>

namespace {
th20::FrontInf* constructing;
th20::FrontInf* previous_front;
bool fail_diagnostic;
unsigned base_destructions, enable_calls, disable_calls;
}

namespace th20 {
// Native scheduler/resource lifetimes are separate from the tested storage
// protocol. These fixture methods preserve real owner types and virtual slots.
TaskInfo::~TaskInfo() { ++base_destructions; }
void TaskInfo::enable() { std::abort(); }
void TaskInfo::disable() { ++disable_calls; }
FrontInf::~FrontInf() = default;
void FrontInf::enable() { ++enable_calls; }
void ecl_diagnostic_hint(const char* format, ...) {
    assert(!std::strcmp(format, "initialize FrontInf\n"));
    assert(current_front == previous_front);
    assert(constructing->flags == 2 && constructing->field_158 == 0);
    assert(constructing->message_file == nullptr && constructing->dialogue == nullptr);
    assert(dynamic_cast<FrontInf*>(static_cast<TaskInfo*>(constructing)) == constructing);
    if (fail_diagnostic) throw std::runtime_error("Captured diagnostic failure");
}
}

namespace {
template<class T> using Image = std::array<unsigned char, sizeof(T)>;
template<class T> Image<T> image(const T& value) {
    Image<T> result;
    std::memcpy(result.data(), &value, sizeof(value));
    return result;
}
template<class T, class F, class V>
void patch(Image<T>& bytes, const T& owner, const F& field, const V& value) {
    static_assert(sizeof(F) == sizeof(V));
    auto offset = reinterpret_cast<const unsigned char*>(&field)
        - reinterpret_cast<const unsigned char*>(&owner);
    assert(offset >= 0 && std::size_t(offset) + sizeof(F) <= bytes.size());
    std::memcpy(bytes.data() + offset, &value, sizeof(F));
}
template<class T, class F> void zero(Image<T>& bytes, const T& owner, const F& field) {
    const auto offset = reinterpret_cast<const unsigned char*>(&field)
        - reinterpret_cast<const unsigned char*>(&owner);
    assert(offset >= 0 && std::size_t(offset) + sizeof(F) <= bytes.size());
    std::fill_n(bytes.data() + offset, sizeof(F), 0);
}
Image<th20::FrontInf> construction_model(const Image<th20::FrontInf>& before,
                                        const th20::FrontInf& front) {
    auto result = before;
    // Native constructors initialize these complete typed values. Padding,
    // front_file and the unknown upper FrontFlags bits retain their input bytes.
    std::apply([&](const auto&... field) { (zero(result, front, field), ...); },
        std::tie(front.update_node, front.draw_node, front.handles_10, front.handles_2c,
            front.handles_48, front.field_50, front.fields_54, front.field_6c,
            front.fields_70, front.field_88, front.fields_8c, front.handle_90,
            front.handles_94, front.handles_bc, front.handle_c8, front.handle_cc,
            front.handles_d0, front.handle_f8, front.handle_fc, front.handle_100,
            front.handle_104, front.handle_108, front.handle_10c, front.handle_110,
            front.handle_114, front.handle_118, front.field_11c, front.field_120,
            front.field_124, front.field_128, front.field_12c, front.field_130,
            front.field_134, front.field_138, front.handle_13c, front.timer_140,
            front.field_150, front.field_158, front.field_160, front.field_168,
            front.message_file, front.field_174, front.field_178, front.field_17c,
            front.field_180, front.gauges_184, front.timer_1a8, front.field_1b8,
            front.dialogue, front.message_bytes, front.field_1c4, front.field_1c8,
            front.field_1cc, front.boss_panels, front.field_2d0));
    patch(result, front, front.flags, std::uint32_t{2});
    const auto flag_offset = reinterpret_cast<const unsigned char*>(&front.front_flags)
        - reinterpret_cast<const unsigned char*>(&front);
    std::uint32_t original;
    std::memcpy(&original, before.data() + flag_offset, sizeof(original));
    patch(result, front, front.front_flags.bits, original & ~0x3fffu);
    // Portable vptr identity differs from MSVC. Real virtual dispatch and RTTI
    // are checked independently rather than comparing a target pointer value.
    std::memcpy(result.data(), &front, sizeof(void*));
    return result;
}
}

int main() {
    using namespace th20;
    unsigned cases = 0;
    alignas(FrontInf) std::array<unsigned char, sizeof(FrontInf)> prior_storage{};
    constructing = reinterpret_cast<FrontInf*>(prior_storage.data());
    previous_front = nullptr; current_front = nullptr; fail_diagnostic = false;
    auto* prior = ::new (prior_storage.data()) FrontInf;
    alignas(FrontInf) std::array<unsigned char, sizeof(FrontInf) + 64> storage;
    for (unsigned pattern = 0; pattern != 256; ++pattern) for (bool fail : {false,true}) {
        storage.fill(static_cast<unsigned char>(pattern));
        auto* data = storage.data() + 32;
        Image<FrontInf> before;
        std::memcpy(before.data(), data, before.size());
        constructing = reinterpret_cast<FrontInf*>(data);
        previous_front = pattern & 1u ? prior : nullptr;
        current_front = previous_front;
        fail_diagnostic = fail;
        const auto old_destructions = base_destructions;
        bool threw = false;
        FrontInf* front = nullptr;
        try { front = ::new (data) FrontInf; }
        catch (const std::runtime_error&) { threw = true; }
        assert(threw == fail);
        assert(std::all_of(storage.begin(), storage.begin()+32,
            [&](unsigned char byte) { return byte == pattern; }));
        assert(std::all_of(storage.end()-32, storage.end(),
            [&](unsigned char byte) { return byte == pattern; }));
        if (fail) {
            assert(current_front == previous_front && base_destructions == old_destructions + 1);
        } else {
            assert(front == constructing && current_front == front);
            assert(image(*front) == construction_model(before, *front));
            auto* base = static_cast<TaskInfo*>(front);
            const auto enabled = enable_calls, disabled = disable_calls;
            base->enable(); base->disable();
            assert(enable_calls == enabled+1 && disable_calls == disabled+1);
            front->~FrontInf();
            assert(base_destructions == old_destructions + 1);
            current_front = nullptr;
        }
        ++cases;
    }
    prior->~FrontInf(); current_front = nullptr;
    for (std::uint32_t seed = 0; seed != 512; ++seed) {
        alignas(FrontFlags) std::array<unsigned char, sizeof(FrontFlags)> bytes;
        const auto initial = seed * 0x9e3779b9u;
        std::memcpy(bytes.data(), &initial, sizeof(initial));
        auto* flags = ::new (bytes.data()) FrontFlags;
        assert(flags->bits == (initial & 0xffffc000u));
        flags->~FrontFlags();
        ++cases;
    }
    storage.fill(0);
    constructing = reinterpret_cast<FrontInf*>(storage.data()+32);
    fail_diagnostic = false; previous_front = nullptr; current_front = nullptr;
    auto* front = ::new (storage.data()+32) FrontInf;
    for (int value : {-2147483647-1,-37,-1,0,1,42,2147483647}) {
        auto expected = image(*front);
        patch(expected, *front, front->field_180, value);
        front->set_field_180(value);
        assert(image(*front) == expected); ++cases;
    }
    const std::uint32_t words[] = {0u,0x80000000u,0x3f000000u,0xbf800000u,
        0x7f800000u,0xff800000u,0x7fc12345u,0x7f7fffffu};
    for (int boss = 0; boss != 3; ++boss) for (int marker = 0; marker != 4; ++marker)
    for (auto word : words) for (int value : {-2147483647-1,-37,-1,0,1,42,2147483647}) {
        const auto fraction = std::bit_cast<float>(word);
        auto expected = image(*front);
        auto& gauge = front->boss_panels[boss].gauges[marker];
        patch(expected, *front, gauge.fraction, fraction);
        patch(expected, *front, gauge.value_04, static_cast<std::uint32_t>(value));
        front->set_boss_gauge(boss, marker, fraction, value);
        assert(image(*front) == expected); ++cases;
    }
    alignas(16) unsigned char opaque[32]{};
    for (Dialogue* pointer : {static_cast<Dialogue*>(nullptr),
                             reinterpret_cast<Dialogue*>(opaque),
                             reinterpret_cast<Dialogue*>(opaque+16)}) {
        front->dialogue = pointer;
        const auto expected = image(*front);
        assert(front->has_dialogue() == (pointer ? 1 : 0));
        assert(image(*front) == expected); ++cases;
    }
    front->dialogue = nullptr;
    front->~FrontInf(); current_front = nullptr;
    std::cout << "PASS " << cases << " FrontInf storage/publication/gauge scenarios; "
        "native resources and scheduler destruction remain fixture boundaries.\n";
}
