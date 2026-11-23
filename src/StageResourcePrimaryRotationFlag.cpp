#include "StageResource.hpp"

namespace th20 {

void StageResourceOwner::set_primary_rotation_flag(std::uint32_t value) {
    state_flags = (state_flags & ~16u) | ((value & 1u) << 4);
}

} // namespace th20
