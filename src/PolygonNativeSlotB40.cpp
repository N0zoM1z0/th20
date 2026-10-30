// Native 19B thiscall accessor at 0x0045ECA0, observed in two original
// polygon-construction callers. The actual class identity outside +0xB40
// is provisional; only a field-address operation is represented here.
#include <cstddef>
#include <cstdint>
namespace th20 {
struct NativePolygonSlotB40 {
    std::uint8_t unresolved_prefix_b40[0xB40];
    std::uint32_t value_b40;
    std::uint32_t* value_address_45eca0();
};
static_assert(offsetof(NativePolygonSlotB40, value_b40) == 0xB40);
std::uint32_t* NativePolygonSlotB40::value_address_45eca0() {
    return &value_b40;
}
}
