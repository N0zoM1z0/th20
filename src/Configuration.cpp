#include "Configuration.hpp"

namespace th20 {

InputBindingSlots::InputBindingSlots() = default;
InputBindings::InputBindings() {
    pad.slot0 = 0x0;
    pad.slot1 = 0x1;
    pad.slot2 = 0x2;
    pad.slot3 = 0x3;
    pad.slot4 = -1;
    pad.slot5 = -1;
    pad.slot6 = -1;
    pad.slot7 = -1;
    alternate_pad.slot0 = 0x0;
    alternate_pad.slot1 = 0x1;
    alternate_pad.slot2 = 0x5;
    alternate_pad.slot3 = 0xa;
    alternate_pad.slot4 = -1;
    alternate_pad.slot5 = -1;
    alternate_pad.slot6 = -1;
    alternate_pad.slot7 = -1;
    keyboard.slot0 = 0x5a;
    keyboard.slot1 = 0x58;
    keyboard.slot2 = 0x10;
    keyboard.slot3 = 0x1b;
    keyboard.slot4 = 0x26;
    keyboard.slot5 = 0x28;
    keyboard.slot6 = 0x25;
    keyboard.slot7 = 0x27;
}

ConfigurationFlags::ConfigurationFlags()
    : bit0(0), reference_rasterizer(0), disable_fog(0), disable_direct_input(0),
      preload_music(0), disable_vsync(0), disable_text_detection(0), bit7(1), bit8(0) {}

} // namespace th20
