// Original immutable PE RTTI .?AVInputInf@@, vtable 0x0056D4D0.
// Owns 12 real InputDevice records and four InputBindings records.
// Members at 0x2E10..0x2E38 independently observed in native constructor.
#pragma once
#include "TaskInfo.hpp"
#include "InputState.hpp"
#include "Configuration.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
struct IDirectInput8W;
namespace th20 {
class InputInf : public TaskInfo {
public:
    // Native noexcept constructor is 261B with five real trailing CC bytes.
    InputInf() noexcept;
    // Entire original 265B InputInf startup config/binding publication.
    std::int32_t start();
    // Complete original 465B device initialization is separately strict
    // exact. Its device discovery callees also have independent exact units.
    std::int32_t initialize_devices();
    // Both original whole device discovery functions are independently
    // exact: DirectInput 726B and XInput 170B. Do not imply exactness
    // for the distinct 3,490B InputDevice polling frame.
    std::int32_t discover_directinput_devices();
    std::int32_t discover_xinput_devices();
    // Whole 120B native virtual destructor, five actual CC alignment
    // bytes and a distinct compiler-generated 49B scalar deleting wrapper.
    ~InputInf() override;
    // Entire original 466B input-device/pad shutdown and 50B native
    // DirectInput interface release; actual original COM pointer slots.
    std::int32_t shutdown();
    void release_direct_input();
    std::uint32_t state_10;
    // Native signed comparisons of the number of discovered devices.
    std::int32_t state_14;
    std::uint32_t state_18;
    // Folded physical 22B state setter also used by an interpolation instance.
    void set_last_input_kind(std::int32_t kind);
    // Original native COM input interface at +0x1C; the separate
    // 50B release member invokes its real vtable Release slot.
    IDirectInput8W* direct_input_1c;
    // The native vector constructor uses each 0x3D4-byte device's true
    // default constructor, not a std::array wrapper helper.
    InputDevice devices[12];
    // Native main keyboard device at +0x2E10 and four pad devices
    // at +0x2E14; both are independently dereferenced through the
    // real IDirectInputDevice8W vtable by original shutdown code.
    IDirectInputDevice8W* direct_device_2e10;
    IDirectInputDevice8W* pad_devices[4];
    std::int32_t routing_2e24[3];
    // Signed indices into the independent process_input_views[] pointer table;
    // the original Player frame uses these values as scaled array subscripts.
    std::int32_t view_indices_2e30[2];
    InputBindings bindings[4];
    // Whole original 26B signed selector: returns a view index, not a pointer.
    std::int32_t for_view(std::int32_t logical_index);
    // The entire original 3490B device polling frame calls both of these
    // authentic input-owner address/routing methods.
    std::int32_t routing_for_view(std::int32_t view) const;
    InputBindings* bindings_for_view(std::int32_t view);
    // Whole original COM pad pointer and pointer-slot getters.
    IDirectInputDevice8W* pad_device(std::int32_t index) const;
    IDirectInputDevice8W** pad_device_slot(std::int32_t index);
    // Original COM interface getters/setter at +0x1C. Only the pointer
    // slot getter is a NEW physical 17B game body. Other methods fold to
    // already exact physical getters/setters, no duplicate byte credit.
    IDirectInput8W* direct_input_handle() const;
    IDirectInput8W** direct_input_handle_slot();
    void set_direct_input_handle(IDirectInput8W* value);
};
#if defined(_M_IX86)
static_assert(sizeof(TaskInfo) == 0x10);
static_assert(sizeof(InputDevice) == 0x3d4);
static_assert(sizeof(InputBindings) == 0x30);
static_assert(offsetof(InputInf, devices) == 0x20);
static_assert(offsetof(InputInf, direct_input_1c) == 0x1c);
static_assert(offsetof(InputInf, direct_device_2e10) == 0x2e10);
static_assert(offsetof(InputInf, pad_devices) == 0x2e14);
static_assert(offsetof(InputInf, routing_2e24) == 0x2e24);
static_assert(offsetof(InputInf, view_indices_2e30) == 0x2e30);
static_assert(offsetof(InputInf, bindings) == 0x2e38);
// Original constructor initializes members through the end of bindings
// at +0x2EF8. This is an attested prefix, NOT proof that the full original
// manager has no further fields. Do not insert unobserved padding.
static_assert(sizeof(InputInf) >= 0x2ef8);
#endif
} // namespace th20
