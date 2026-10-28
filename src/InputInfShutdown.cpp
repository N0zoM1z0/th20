#include "InputInf.hpp"
#include "GraphicsApi.hpp"
#include "EclDiagnostic.hpp"
#include "LockRegistry.hpp"
#include <mutex>

namespace th20 {

// Native 50-byte global DirectInput interface teardown: release the real
// interface at this+0x1C and clear only after the COM Release completes.
void InputInf::release_direct_input() {
    if (direct_input_1c != nullptr) {
        direct_input_1c->Release();
        direct_input_1c = nullptr;
    }
}
// Complete 466-byte shutdown of the 12 real input devices and four
// DirectInput pads under the native recursive lock slot 15. COM
// Unacquire/Release are real IDirectInputDevice8W interface methods.
std::int32_t InputInf::shutdown() {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(15));
    state_14 = 0;
    for (std::int32_t i = 0; i < 12; ++i)
        devices[i].reset_header();
    if (direct_device_2e10 != nullptr) {
        ecl_diagnostic_hint("DirectInput Release\n");
        direct_device_2e10->Unacquire();
        if (direct_device_2e10 != nullptr) {
            direct_device_2e10->Release();
            direct_device_2e10 = nullptr;
        }
    }
    for (std::int32_t i = 0; i < 4; ++i) {
        if (pad_devices[i] != nullptr) {
            ecl_diagnostic_hint("DirectInput(Pad) Release\n");
            pad_devices[i]->Unacquire();
            if (pad_devices[i] != nullptr) {
                pad_devices[i]->Release();
                pad_devices[i] = nullptr;
            }
        }
    }
    ecl_diagnostic_hint("DirectInput Device Release\n");
    release_direct_input();
    return 0;
}
} // namespace th20
