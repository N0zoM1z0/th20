#include "StageResource.hpp"

namespace th20 {

void StageResourceOwner::set_primary_rotation_flag(std::uint32_t value) {
    std::uint32_t* flags = &state_flags;
    *flags = (*flags & ~16u) | ((value & 1u) << 4);
}

} // namespace th20
