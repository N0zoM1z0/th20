// Whole native InputDevice input frame at 0x00421B00: keyboard,
// DirectInput, XInput and shared input-history update.
// SOURCE-PRESENT / NONEXACT: there is no strict canonical unit for this boss.
#include "InputState.hpp"
#include "InputInf.hpp"
#include "Graphics.hpp"
#include "GraphicsApi.hpp"
#include "LockRegistry.hpp"
#include <Xinput.h>
#include <cstring>
#include <mutex>

namespace th20 {
extern InputInf* process_input_inf;
// Storage owners for these original global variables have not yet been
// reconstructed. Both addresses were independently read from the PE.
extern std::uint8_t keyboard_input_enabled; // 0x005B67C0
extern const std::uint32_t xinput_button_masks[]; // 0x005AE220

std::uint32_t InputDevice::poll() {
    std::uint32_t flags = 0;
    std::uint32_t initial_flags = 0;
    std::memset(raw, 0, sizeof(raw));
    std::lock_guard<std::recursive_mutex> lock(process_locks.slot(15));

    const std::int32_t secondary_view =
        process_input_inf->routing_for_view(1) == logical_index;
    const InputBindings& bindings = *process_input_inf->bindings_for_view(secondary_view);

    switch (kind) {
    case 0: {
        if (keyboard_input_enabled != 0) {
            GetKeyboardState(raw);
            if (initial_flags != flags)
                process_input_inf->set_last_input_kind(kind);
            if (kind == 0) {
                flags |= (raw[bindings.keyboard.slot4] & 0x80) ? 0x10u : 0;
                flags |= (raw[bindings.keyboard.slot5] & 0x80) ? 0x20u : 0;
                flags |= (raw[bindings.keyboard.slot6] & 0x80) ? 0x40u : 0;
                flags |= (raw[bindings.keyboard.slot7] & 0x80) ? 0x80u : 0;
                flags |= (raw[bindings.keyboard.slot0] & 0x80) ? 0x1u : 0;
                flags |= (raw[bindings.keyboard.slot1] & 0x80) ? 0x4u : 0;
                flags |= (raw[bindings.keyboard.slot2] & 0x80) ? 0x8u : 0;
                flags |= (raw[bindings.keyboard.slot3] & 0x80) ? 0x100u : 0;
                flags |= (raw[VK_RETURN] & 0x80) ? 0x80000u : 0;
                flags |= (raw[VK_HOME] & 0x80) ? 0x40000u : 0;
                flags |= (raw['P'] & 0x80) ? 0x40000u : 0;
                flags |= (raw[VK_END] & 0x80) ? 0x200000u : 0;
                flags |= (raw['R'] & 0x80) ? 0x200000u : 0;
                flags |= (raw[VK_NUMPAD8] & 0x80) ? 0x10u : 0;
                flags |= (raw[VK_NUMPAD2] & 0x80) ? 0x20u : 0;
                flags |= (raw[VK_NUMPAD4] & 0x80) ? 0x40u : 0;
                flags |= (raw[VK_NUMPAD6] & 0x80) ? 0x80u : 0;
                flags |= (raw[VK_NUMPAD7] & 0x80) ? 0x50u : 0;
                flags |= (raw[VK_NUMPAD9] & 0x80) ? 0x90u : 0;
                flags |= (raw[VK_NUMPAD1] & 0x80) ? 0x60u : 0;
                flags |= (raw[VK_NUMPAD3] & 0x80) ? 0xA0u : 0;
            }
        }
    } break;
    case 2: {
        XINPUT_STATE state;
        std::memset(&state, 0, sizeof(state));
        const DWORD xinput_status = XInputGetState(xinput_index, &state);
        if (xinput_status == ERROR_SUCCESS) {
            std::uint32_t pad_bits = state.Gamepad.wButtons;
            if (state.Gamepad.bLeftTrigger >= 0x1E) pad_bits |= 0x10000;
            if (state.Gamepad.bRightTrigger >= 0x1E) pad_bits |= 0x20000;
            if (state.Gamepad.sThumbLY >= 0x1EA9) pad_bits |= 1;
            if (state.Gamepad.sThumbLY <= -0x1EA9) pad_bits |= 2;
            if (state.Gamepad.sThumbLX >= 0x1EA9) pad_bits |= 8;
            if (state.Gamepad.sThumbLX <= -0x1EA9) pad_bits |= 4;

            if (pad_bits & 1) flags |= 0x10;
            if (pad_bits & 2) flags |= 0x20;
            if (pad_bits & 4) flags |= 0x40;
            if (pad_bits & 8) flags |= 0x80;
            if (pad_bits & xinput_button_masks[bindings.alternate_pad.slot0]) flags |= 1;
            if (pad_bits & xinput_button_masks[bindings.alternate_pad.slot1]) flags |= 4;
            if (pad_bits & xinput_button_masks[bindings.alternate_pad.slot2]) flags |= 8;
            if (pad_bits & xinput_button_masks[bindings.alternate_pad.slot3]) flags |= 0x100;

            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) raw[0] = 0x80;
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) raw[1] = 0x80;
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) raw[2] = 0x80;
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) raw[3] = 0x80;
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) raw[8] = 0x80;
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) raw[9] = 0x80;
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) raw[4] = 0x80;
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) raw[5] = 0x80;
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) raw[10] = 0x80;
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) raw[11] = 0x80;
            if (state.Gamepad.bLeftTrigger >= 0x1E) raw[6] = 0x80;
            if (state.Gamepad.bRightTrigger >= 0x1E) raw[7] = 0x80;
            if (initial_flags != flags)
                process_input_inf->set_last_input_kind(kind);
        }
    } break;
    case 1: {
        // The original exits without committing a new button history when
        // a Poll or GetDeviceState failure reaches the guard cleanup.
        initial_flags = flags;
        HRESULT status = direct_input->Poll();
        if (FAILED(status)) {
            std::int32_t attempts = 0;
            status = direct_input->Acquire();
            do {
                if (status != DIERR_INPUTLOST)
                    return flags;
                status = direct_input->Acquire();
                ++attempts;
            } while (attempts < 400);
            return flags;
        }

        DIJOYSTATE2 joystick;
        std::memset(&joystick, 0, sizeof(joystick));
        status = direct_input->GetDeviceState(sizeof(joystick), &joystick);
        if (FAILED(status))
            return flags;

        map_input_byte(&flags, bindings.pad.slot0, 1, joystick.rgbButtons);
        map_input_byte(&flags, bindings.pad.slot1, 4, joystick.rgbButtons);
        map_input_byte(&flags, bindings.pad.slot3, 0x100, joystick.rgbButtons);
        map_input_byte(&flags, bindings.pad.slot2, 8, joystick.rgbButtons);

        flags |= joystick.lX > static_cast<std::int16_t>(process_graphics.configuration.value_70) ? 0x80u : 0;
        flags |= joystick.lX < -static_cast<std::int16_t>(process_graphics.configuration.value_70) ? 0x40u : 0;
        flags |= joystick.lY > static_cast<std::int16_t>(process_graphics.configuration.value_72) ? 0x20u : 0;
        flags |= joystick.lY < -static_cast<std::int16_t>(process_graphics.configuration.value_72) ? 0x10u : 0;
        for (std::int32_t i = 0; i < 32; ++i) {
            if (joystick.rgbButtons[i] != 0)
                raw[i] = 0x80;
        }
        if (initial_flags != flags)
            process_input_inf->set_last_input_kind(kind);
    } break;
    }

    buttons.previous = buttons.current;
    buttons.current = flags;
    buttons.update();
    return flags;
}
} // namespace th20
