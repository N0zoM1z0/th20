#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {

// REF-007: three fixed records of eight signed bindings. Negative values disable
// pad actions; keyboard indexing and configuration validation remain elsewhere.
struct InputBindingSlots {
    std::int16_t slot0 = 0;
    std::int16_t slot1 = 0;
    std::int16_t slot2 = 0;
    std::int16_t slot3 = 0;
    std::int16_t slot4 = 0;
    std::int16_t slot5 = 0;
    std::int16_t slot6 = 0;
    std::int16_t slot7 = 0;
    InputBindingSlots();
};
struct InputBindings {
    InputBindingSlots pad, alternate_pad, keyboard;
    InputBindings();
};

static_assert(sizeof(InputBindingSlots) == 16);
static_assert(sizeof(InputBindings) == 48);
static_assert(offsetof(InputBindings, alternate_pad) == 16);
static_assert(offsetof(InputBindings, keyboard) == 32);

// Low nine option bits are constructed individually; bits 9..31 are retained.
// Unnamed option roles remain numbered until independent consumers identify them.
struct ConfigurationFlags {
    std::uint32_t bit0 : 1;
    std::uint32_t reference_rasterizer : 1;
    std::uint32_t disable_fog : 1;
    std::uint32_t disable_direct_input : 1;
    std::uint32_t preload_music : 1;
    std::uint32_t disable_vsync : 1;
    std::uint32_t disable_text_detection : 1;
    std::uint32_t bit7 : 1;
    std::uint32_t bit8 : 1;
    std::uint32_t retained : 23;
    ConfigurationFlags();
};

static_assert(sizeof(ConfigurationFlags) == 4);

} // namespace th20
