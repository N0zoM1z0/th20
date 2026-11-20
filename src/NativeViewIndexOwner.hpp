#pragma once
#include <cstddef>
#include <cstdint>
namespace th20 {
// Opaque native global owner used by several view-scoped controllers. Only
// the field at +0x6C4 is currently assigned a semantic role.
struct NativeViewIndexOwner {
    std::uint8_t unknown_000_6c4[0x6c4];
    std::int32_t view_index_6c4;
    void set_view_index(std::int32_t value);
};
static_assert(offsetof(NativeViewIndexOwner,view_index_6c4)==0x6c4);
extern NativeViewIndexOwner* native_view_index_owner_5c0028;
}
