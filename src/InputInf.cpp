// Whole original 26-byte InputInf per-Player input source lookup.
// This RTTI-attested original class owns the live pointer table; no
// pointer-alias casts or fake 0x2E30-byte padding are needed.
#include "InputInf.hpp"

namespace th20 {
InputButtonState* InputInf::for_view(std::int32_t logical_index) {
    return active_buttons[logical_index];
}
// Original 49B native logical-view routing lookup. View 1 is a native
// disabled-routing sentinel; other views use the genuine +0x2E24 table.
std::int32_t InputInf::routing_for_view(std::int32_t view) const {
    return view == 1 ? -1 : routing_2e24[view];
}

// Original 27B direct 0x30-stride bindings pointer used in the
// independently decoded 3490B InputDevice polling method.
InputBindings* InputInf::bindings_for_view(std::int32_t view) {
    return &bindings[view];
}

// Two physically separate 26B native pad pointer / pointer-slot
// accessors. The array is the real DirectInputDevice8W*[4] at +0x2E14.
IDirectInputDevice8W* InputInf::pad_device(std::int32_t index) const {
    return pad_devices[index];
}

IDirectInputDevice8W** InputInf::pad_device_slot(std::int32_t index) {
    return &pad_devices[index];
}

} // namespace th20
