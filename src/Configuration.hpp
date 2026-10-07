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

struct ConfigurationCounterPair { std::uint32_t first, second; };
struct ConfigurationByteFlag { std::uint8_t bit0:1, retained:7; };
struct Configuration {
    std::uint32_t version, size;
    InputBindings bindings[2];
    ConfigurationCounterPair values_68;
    std::uint16_t value_70, value_72;
    std::uint8_t alternate_pixel_format, value_75, value_76;
    std::int32_t saved_display_mode;
    std::uint8_t frame_skip, value_7d, value_7e, value_7f;
    std::uint8_t value_80, presentation_mode, scale_choice;
    ConfigurationByteFlag flag_83;
    ConfigurationFlags flags;
    std::int32_t saved_window_x, saved_window_y;
    std::uint32_t value_90;
    std::uint8_t value_94, value_95, value_96, value_97, value_98, value_99;
    std::uint8_t value_9a, value_9b, value_9c, value_9d, value_9e, value_9f;
    std::uint8_t value_a0, value_a1, value_a2, value_a3, value_a4;
    ConfigurationCounterPair values_a8;
    Configuration() noexcept;
};
static_assert(sizeof(Configuration)==0xb0);
static_assert(offsetof(Configuration,flags)==0x84);
static_assert(offsetof(Configuration,values_a8)==0xa8);

} // namespace th20
