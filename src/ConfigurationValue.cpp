#include "Configuration.hpp"
namespace th20 {
Configuration::Configuration() noexcept
    : version(0x200002), size(sizeof(Configuration)), values_68{},
      value_70(600), value_72(600), alternate_pixel_format(0), value_75(1), value_76(1),
      saved_display_mode(8), frame_skip(0), value_7d(2), value_7e(100), value_7f(80),
      value_80(0), presentation_mode(2), scale_choice(0), flag_83{},
      saved_window_x(-2147483647-1), saved_window_y(-2147483647-1), value_90(1),
      value_94(0), value_95(0), value_96(0), value_97(0), value_98(0), value_99(0),
      value_9a(1), value_9b(0), value_9c(0), value_9d(0), value_9e(0), value_9f(0),
      value_a0(0), value_a1(0), value_a2(0), value_a3(0), value_a4(0), values_a8{} {}
}
