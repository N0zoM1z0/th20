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
namespace th20 {
class InputInf : public TaskInfo {
public:
    // Native noexcept constructor is 261B with five real trailing CC bytes.
    InputInf() noexcept;
    // Whole 120B native virtual destructor, five actual CC alignment
    // bytes and a distinct compiler-generated 49B scalar deleting wrapper.
    ~InputInf() override;
    // The independent original 466B device/pad shutdown remains NONEXACT.
    std::int32_t shutdown();
    std::uint32_t state_10, state_14, state_18, state_1c;
    // The native vector constructor uses each 0x3D4-byte device's true
    // default constructor, not a std::array wrapper helper.
    InputDevice devices[12];
    std::uint32_t field_2e10, field_2e14;
    std::uint32_t retained_2e18[3];
    std::int32_t routing_2e24[3];
    InputButtonState* active_buttons[2];
    InputBindings bindings[4];
    // Entire original 26B accessor, native thiscall receiver and int index.
    InputButtonState* for_view(std::int32_t logical_index);
};
#if defined(_M_IX86)
static_assert(sizeof(TaskInfo) == 0x10);
static_assert(sizeof(InputDevice) == 0x3d4);
static_assert(sizeof(InputBindings) == 0x30);
static_assert(offsetof(InputInf, devices) == 0x20);
static_assert(offsetof(InputInf, field_2e10) == 0x2e10);
static_assert(offsetof(InputInf, retained_2e18) == 0x2e18);
static_assert(offsetof(InputInf, routing_2e24) == 0x2e24);
static_assert(offsetof(InputInf, active_buttons) == 0x2e30);
static_assert(offsetof(InputInf, bindings) == 0x2e38);
// Original constructor initializes members through the end of bindings
// at +0x2EF8. This is an attested prefix, NOT proof that the full original
// manager has no further fields. Do not insert unobserved padding.
static_assert(sizeof(InputInf) >= 0x2ef8);
#endif
} // namespace th20
