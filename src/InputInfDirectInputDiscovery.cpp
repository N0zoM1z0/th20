// Complete original 726B InputInf DirectInput device creation pipeline.
#include "InputInf.hpp"
#include "WindowState.hpp"
#include "GraphicsApi.hpp"
#include "DiagnosticLog.hpp"
#include "Graphics.hpp"
namespace th20 {
extern InputInf* process_input_inf;
extern const char original_directinput_create_error[];
extern const char original_keyboard_create_error[];
extern const char original_keyboard_format_error[];
extern const char original_keyboard_cooperative_error[];
extern const char original_directinput_started[];
extern IDirectInputDevice8W* most_recent_pad_device;
BOOL CALLBACK original_directinput_enumerate_devices(const DIDEVICEINSTANCEW*, void*);
BOOL CALLBACK original_directinput_pad_object_callback(const DIDEVICEOBJECTINSTANCEW*, void*);
std::int32_t InputInf::discover_directinput_devices() {
    HINSTANCE instance = window_state.instance_handle();
    HRESULT status = DirectInput8Create(instance,
        0x800, IID_IDirectInput8W,
        reinterpret_cast<void**>(direct_input_handle_slot()), nullptr);
    if (FAILED(status)) {
        set_direct_input_handle(nullptr);
        report_log_error(&diagnostic_log, original_directinput_create_error);
        return -1;
    }
    IDirectInput8W* dinput = direct_input_handle();
    if (FAILED(dinput->CreateDevice(GUID_SysKeyboard, &direct_device_2e10, nullptr))) {
        release_direct_input();
        report_log_error(&diagnostic_log, original_keyboard_create_error);
        return -1;
    }
    if (FAILED(direct_device_2e10->SetDataFormat(&c_dfDIKeyboard))) {
        if (direct_device_2e10 != nullptr) {
            direct_device_2e10->Release();
            direct_device_2e10 = nullptr;
        }
        release_direct_input();
        report_log_error(&diagnostic_log, original_keyboard_format_error);
        return -1;
    }
    status = direct_device_2e10->SetCooperativeLevel(
        window_state.window_handle(),
        DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    if (FAILED(status)) {
        if (direct_device_2e10 != nullptr) {
            direct_device_2e10->Release();
            direct_device_2e10 = nullptr;
        }
        release_direct_input();
        report_log_error(&diagnostic_log, original_keyboard_cooperative_error);
        return -1;
    }
    direct_device_2e10->Acquire();
    report_log_error(&diagnostic_log, original_directinput_started);
    direct_input_handle()->EnumDevices(DI8DEVCLASS_GAMECTRL,
       original_directinput_enumerate_devices, nullptr, DIEDFL_ATTACHEDONLY);
    for (std::int32_t i=0; i<4; ++i) {
        if (pad_devices[i] != nullptr) {
            most_recent_pad_device = pad_devices[i];
            pad_devices[i]->EnumObjects(original_directinput_pad_object_callback, nullptr, DIDFT_ALL);
            devices[state_14].initialize_directinput(i, state_14);
            ++state_14;
        }
    }
    return 0;
}
} // namespace th20
