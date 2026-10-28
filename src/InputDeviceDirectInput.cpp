// Entire original 218-byte InputDevice DirectInput pad registration.
#include "InputState.hpp"
#include "WindowState.hpp"
#include "Graphics.hpp"
#include "InputInf.hpp"
#include "DiagnosticLog.hpp"
#include "GraphicsApi.hpp"

namespace th20 {
extern InputInf* process_input_inf;
extern const char original_directinput_pad_attached_message[];
BOOL CALLBACK original_directinput_device_object(const DIDEVICEOBJECTINSTANCEW*, void*);

void InputDevice::initialize_directinput(std::int32_t physical, std::int32_t logical) {
    IDirectInputDevice8W* device = process_input_inf->pad_device(physical);
    if (device) {
        device->SetDataFormat(&c_dfDIJoystick2);
        device->SetCooperativeLevel(window_state.window_handle(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
        process_graphics.input_device_caps.dwSize = sizeof(DIDEVCAPS);
        device->GetCapabilities(&process_graphics.input_device_caps);
        direct_input = device;
        device->EnumObjects(original_directinput_device_object, nullptr, DIDFT_ALL);
        report_log_error(&diagnostic_log, original_directinput_pad_attached_message);
        kind = 1;
        xinput_index = -1;
        logical_index = logical;
    }
}
}
