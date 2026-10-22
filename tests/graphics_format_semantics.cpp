#include "Graphics.hpp"
#include "LockRegistry.hpp"

#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>

namespace th20 {
// Actual member construction and Worker retirement run on resource-absent owners.
// Native graphics startup, COM destruction and Renderer integration remain open.
LockRegistry process_locks;
Graphics::~Graphics() = default;
Graphics process_graphics;
}

namespace {
using Image = std::array<unsigned char,sizeof(th20::Graphics)>;
Image image(const th20::Graphics& graphics) {
    Image result;
    std::memcpy(result.data(),&graphics,sizeof(graphics));
    return result;
}
std::uint32_t next_word(std::uint32_t& state) {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}
}

int main() {
    using namespace th20;
    static_assert(sizeof(graphics_api::TextureFormat)==4);
    static_assert(sizeof(texture_api_formats)==36);
    for (unsigned i=0;i<9;++i)
        assert(static_cast<std::int32_t>(texture_api_formats[i])==(i?21:0));

    static Graphics other;
    std::array<std::uint64_t,16> device_tokens{};
    std::uint32_t state = 0x8d3e725bu;
    unsigned checked = 0;
    for (unsigned group=0;group<64;++group) {
        auto graphics_bits = next_word(state);
        auto configuration_bits = next_word(state);
        process_graphics.flags = std::bit_cast<GraphicsFlags>(graphics_bits);
        process_graphics.configuration.flags = std::bit_cast<ConfigurationFlags>(configuration_bits);
        process_graphics.device = group%3 ?
            reinterpret_cast<graphics_api::Device*>(&device_tokens[group%16]) : nullptr;
        other.device = group%5 ?
            reinterpret_cast<graphics_api::Device*>(&device_tokens[(group+7)%16]) : nullptr;
        const auto global_before = image(process_graphics), other_before = image(other);
        assert(process_graphics.get_device()==process_graphics.device);
        assert(other.get_device()==other.device);
        assert(process_graphics.texture_format_mode()==0);
        assert(other.texture_format_mode()==0);
        // The native constant-zero predicate makes selection an identity over
        // full input words. Values outside the table never index it on this path.
        for (unsigned low=0;low<1024;++low) {
            const std::uint32_t value = group*1024u+low;
            assert(select_texture_format(value)==value);
            ++checked;
        }
        for (unsigned extra=0;extra<128;++extra) {
            const auto value = next_word(state);
            assert(select_texture_format(value)==value);
            ++checked;
        }
        for (std::uint32_t value:{9u,255u,65536u,0x7fffffffu,0x80000000u,0xffffffffu})
            assert(select_texture_format(value)==value);
        assert(image(process_graphics)==global_before && image(other)==other_before);
    }
    process_graphics.device = other.device = nullptr;
    assert(checked==73728);
    std::cout << "73728 Graphics format cases passed: actual owner state, distinct receiver device pointers, "
                 "full-word identity and complete owner-image preservation. Native COM/startup remains external.\n";
}
