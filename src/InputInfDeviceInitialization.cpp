#include "InputInf.hpp"
#include "Graphics.hpp"
#include "LockRegistry.hpp"
#include "EclDiagnostic.hpp"
#include <mutex>
namespace th20 {
// Entire original 465-byte signed device/route initialization boss.
// First tear down the old devices, hold real lock slot 15, initialize
// keyboard, discover DirectInput and XInput, and update persistent
// Graphics configuration through its actual two-DWORD route array.
std::int32_t InputInf::initialize_devices() {
    shutdown();
    std::lock_guard<std::recursive_mutex> lock(process_locks.slot(15));
    state_14 = 0;
    devices[state_14].initialize_keyboard(state_14);
    ++state_14;
    discover_directinput_devices();
    discover_xinput_devices();
    ecl_diagnostic_hint("Pad Num : %d\n", state_14);
    routing_2e24[0] = process_graphics.configuration.values_68.values[0];
    routing_2e24[1] = -1;
    if (routing_2e24[0] >= state_14)
        routing_2e24[0] = 0;
    if (routing_2e24[0] < 1) {
        if (routing_2e24[1] == 1) {
            if (state_14 > 2)
                routing_2e24[0] = 2;
        } else if (state_14 > 1) {
            routing_2e24[0] = 1;
        }
    }
    process_graphics.configuration.values_68.values[0] = routing_2e24[0];
    return 0;
}
}
