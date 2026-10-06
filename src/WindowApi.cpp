#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "WindowState.hpp"

extern "C" BOOL WINAPI WINNLSEnableIME(HWND, BOOL);

namespace th20 {

void bring_window_to_foreground(HWND__* window) {
    SetForegroundWindow(window);
}

void WindowState::restore_system_settings() {
    SystemParametersInfoW(0x11, window_state.saved_screen_saver, nullptr, 2);
    SystemParametersInfoW(0x55, window_state.saved_low_power, nullptr, 2);
    SystemParametersInfoW(0x56, window_state.saved_power_off, nullptr, 2);
    WINNLSEnableIME(nullptr, TRUE);
}

int is_japanese_user_locale() {
    const LCID locale = GetUserDefaultLCID();
    return locale == 0x411 ? 1 : 0;
}

} // namespace th20
