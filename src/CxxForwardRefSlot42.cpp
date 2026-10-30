// Complete original 42-byte, pointer-sized C++ forwarding slot constructor
// at 0x0045ECC0. The original type/standard-library template identity is
// unknown; this nominal class preserves the observed reference/forwarding ABI.
// Authorship is not attributed to game code without independent evidence.
#include <cstdint>
#include <utility>
namespace th20 {
struct NativeForwardedRefSlot {
    std::uint32_t* pointer;
    explicit NativeForwardedRefSlot(std::uint32_t& value);
};

NativeForwardedRefSlot::NativeForwardedRefSlot(std::uint32_t& value)
    : pointer(&std::forward<std::uint32_t&>(
          std::forward<std::uint32_t&>(value))) {}
} // namespace th20
