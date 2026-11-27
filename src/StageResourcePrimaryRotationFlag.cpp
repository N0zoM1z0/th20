#include "StageResource.hpp"

namespace th20 {

void StageResourceOwner::set_primary_rotation_flag(std::uint32_t value) {
    state_flags_bits.primary_rotation = value;
}

} // namespace th20
