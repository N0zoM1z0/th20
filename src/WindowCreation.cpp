#define UNICODE
#define _UNICODE
#include <Windows.h>
#include <cstring>

#include "Graphics.hpp"
#include "WindowState.hpp"

namespace th20 {

LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

// The physical 0x004117A0 body folds with identical setters credited elsewhere.
void WindowState::set_window(HWND__* value) { window = value; }

// Registers the "BASE" class, restores the saved display mode and frame
// pacing, computes the layout and creates either a fullscreen popup, a
// desktop-sized popup (modes 8 and 9) or a framed window at the saved
// position. Returns nonzero when no window was created.
std::int32_t WindowState::create_window(HINSTANCE__* instance) {
    const wchar_t* title = is_japanese_user_locale()
        ? L"\u6771\u65B9\u9326\u4E0A\u4EAC\u3000\uFF5E Fossilized Wonder. ver 1.00c"
        : L"TH20 - Fossilized Wonder. ver 1.00c";
    WNDCLASSW window_class;
    std::memset(&window_class, 0, sizeof(window_class));
    window_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    window_class.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    window_class.hInstance = instance;
    window_class.lpfnWndProc = window_procedure;
    active = 1;
    cursor_latch = 0;
    window_class.lpszClassName = L"BASE";
    RegisterClassW(&window_class);
    set_display_mode(process_graphics.configuration.saved_display_mode);
    process_graphics.presentation.Windowed = display_mode() >= 3 ? 1 : 0;
    if (process_graphics.configuration.frame_skip == 0 &&
        process_graphics.configuration.presentation_mode == 2) {
        flags.bits.unlimited = 1;
    } else {
        flags.bits.unlimited = 0;
    }
    repeat[0].reset(15);
    repeat[1].reset(12);
    repeat[2].reset(12);
    repeat[3].reset(8);
    input_latch = 0;
    compute_layout(1);
    if (process_graphics.windowed() == 0) {
        const std::int32_t width = client_width;
        const std::int32_t height = client_height;
        set_window(CreateWindowExW(0, L"BASE", title, WS_POPUP | WS_VISIBLE, 0, 0, width, height,
                                   nullptr, nullptr, instance, nullptr));
    } else if (window_state.display_mode() != 8 && window_state.display_mode() != 9) {
        RECT rect = {0, 0, client_width, client_height};
        const DWORD style = WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
        AdjustWindowRectEx(&rect, style, FALSE, 0);
        window = CreateWindowExW(0, L"BASE", title, style,
                                 process_graphics.configuration.saved_window_x,
                                 process_graphics.configuration.saved_window_y,
                                 rect.right - rect.left, rect.bottom - rect.top,
                                 nullptr, nullptr, instance, nullptr);
        ShowWindow(window, SW_SHOW);
        InvalidateRect(window, nullptr, TRUE);
        UpdateWindow(window);
    } else {
        const DWORD style = WS_POPUP;
        window = CreateWindowExW(WS_EX_APPWINDOW, L"BASE", title, style, 0, 0, client_width,
                                 client_height, nullptr, nullptr, instance, nullptr);
        SetWindowLongW(window, GWL_STYLE, 0);
        ShowWindow(window, SW_SHOW);
        InvalidateRect(window, nullptr, TRUE);
        UpdateWindow(window);
    }
    GetWindowRect(window, &process_graphics.window_rectangle);
    process_graphics.window_handle = window;
    if (window == nullptr) {
        return 1;
    }
    return 0;
}

// Alt+Enter cycles fullscreen and windowed modes; maximizing a framed
// window switches it to the matching fullscreen size. Menu activation
// through the keyboard or mouse is swallowed.
LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message) {
    case WM_ERASEBKGND:
        return 1;
    case WM_PAINT:
        if (!window_state.flags.bits.bit7) {
            PAINTSTRUCT paint;
            HDC context = BeginPaint(window, &paint);
            HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
            FillRect(context, &paint.rcPaint, brush);
            DeleteObject(brush);
            EndPaint(window, &paint);
            window_state.flags.bits.bit7 = 1;
        }
        break;
        break;
    case WM_ACTIVATEAPP:
        window_state.active = wparam != 0;
        if (window_state.active) {
            window_state.cursor_latch = 0;
            SetWindowPos(window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        } else {
            window_state.cursor_latch = 1;
            SetWindowPos(window, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
        break;
    case WM_DISPLAYCHANGE:
        if (process_graphics.windowed() == 0) {
            Sleep(3000);
        }
        window_state.startup_status = 300;
        break;
        break;
    case WM_SYSCOMMAND:
        switch (wparam & 0xFFF0) {
        case SC_KEYMENU:
            return 1;
        case SC_MOUSEMENU:
            return 1;
        }
        break;
    case WM_SIZE:
        if (window_state.flags.bits.started) {
            switch (wparam) {
                break;
            case SIZE_MAXIMIZED:
                window_state.set_device_reset(1);
                switch (window_state.display_mode()) {
                case 3:
                    window_state.set_display_mode(0);
                    break;
                case 4:
                    window_state.set_display_mode(1);
                    break;
                case 5:
                default:
                    window_state.set_display_mode(2);
                    break;
                case 6:
                    window_state.set_display_mode(2);
                    break;
                }
                break;
            }
        }
        break;
    case WM_SYSKEYDOWN:
        switch (wparam) {
        case VK_RETURN:
            window_state.set_device_reset(1);
            switch (window_state.display_mode()) {
            case 3:
                window_state.set_display_mode(0);
                break;
            case 4:
                window_state.set_display_mode(1);
                break;
            case 5:
                window_state.set_display_mode(2);
                break;
            case 6:
                window_state.set_display_mode(2);
                break;
            case 7:
                window_state.set_display_mode(2);
                break;
            case 0:
                window_state.set_display_mode(3);
                break;
            case 1:
                window_state.set_display_mode(4);
                break;
            case 2:
                if (process_graphics.configuration.scale_choice == 4) {
                    window_state.set_display_mode(7);
                } else if (process_graphics.configuration.scale_choice == 3) {
                    window_state.set_display_mode(6);
                } else {
                    window_state.set_display_mode(5);
                }
                break;
            case 8:
            case 9:
                switch (process_graphics.configuration.scale_choice) {
                case 0:
                    window_state.set_display_mode(3);
                    break;
                case 1:
                    window_state.set_display_mode(4);
                    break;
                case 2:
                    window_state.set_display_mode(5);
                    break;
                case 3:
                    window_state.set_display_mode(6);
                    break;
                case 4:
                    window_state.set_display_mode(7);
                    break;
                case 5:
                    window_state.set_display_mode(5);
                    break;
                }
                break;
            }
            break;
        }
        break;
    case WM_SETCURSOR:
        if (process_graphics.windowed() == 0 || window_state.display_mode() == 8 ||
            window_state.display_mode() == 9) {
            if (window_state.cursor_latch) {
                SetCursor(LoadCursorW(nullptr, IDC_ARROW));
                do {
                } while (ShowCursor(TRUE) < 0);
            } else {
                do {
                } while (ShowCursor(FALSE) >= 0);
                SetCursor(nullptr);
            }
        } else {
            SetCursor(LoadCursorW(nullptr, IDC_ARROW));
            ShowCursor(TRUE);
        }
        return 1;
    case WM_CLOSE:
        process_graphics.flags.bits5_6 = 1;
        return 1;
    }
    return DefWindowProcW(window, message, wparam, lparam);
}

} // namespace th20
