#include "InputInf.hpp"
#include "Graphics.hpp"
#include "EclDiagnostic.hpp"
namespace th20 {
extern InputButtonState* process_input_views[4];
extern InputButtonState process_button_states[4];
// Complete native InputInf startup (265B / 75 x86 instructions).
// Three true 16-byte binding subrecords must be assigned separately,
// matching the game's actual per-record MSVC copy order; whole
// InputBindings 48-byte assignment incorrectly compiles to rep movsd.
std::int32_t InputInf::start() {
    ecl_diagnostic_hint("start InputInf\n");
    state_10 = 0;
    for (std::int32_t i = 0; i < 2; ++i) {
        bindings[i].pad = process_graphics.configuration.bindings[i].pad;
        bindings[i].alternate_pad = process_graphics.configuration.bindings[i].alternate_pad;
        bindings[i].keyboard = process_graphics.configuration.bindings[i].keyboard;
    }
    initialize_devices();
    for (std::int32_t i = 0; i < 4; ++i)
        process_input_views[i] = &process_button_states[i];
    return 0;
}
}
