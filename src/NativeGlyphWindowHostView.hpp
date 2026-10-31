#pragma once
#include <windows.h>
namespace th20 {
// Nonowning view of the original game window slot at 0x005B6758.
// The folded native 16B getter is already whole-exact as another owner;
// this interface only declares its real window acquisition call.
struct NativeWindowHostView {
    HWND current_window_40c300() const;
};
extern NativeWindowHostView native_window_host_5b6758;
}
