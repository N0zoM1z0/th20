#include "ShotMetadata.hpp"

namespace th20 {

ShotMetadata::ShotMetadata() noexcept
    : field_00(0), field_14(0), field_18(0), field_1c(0), field_20(0),
      field_24(0), field_28(0), field_2c(0), field_30(0), field_34(0),
      field_38(0), field_3a(0), sound(21), alternate_sound(38), field_44(0),
      field_48(0), field_49(false) {
    auto& values = commands;
    values.resize(2);
}
ShotMetadata& ShotMetadata::operator=(ShotMetadata&&) = default;
ShotMetadata::~ShotMetadata() = default;

} // namespace th20
