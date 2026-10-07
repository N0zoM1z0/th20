#pragma once

#include "BulletValues.hpp"
#include <cstddef>
#include <memory_resource>
#include <vector>

namespace th20 {

// The queued shared owner points to this value. Unknown operand roles stay
// neutral; command storage uses the same real 44-byte BulletCommand records.
struct ShotMetadata {
    float field_00;
    std::pmr::vector<BulletCommand> commands;
    float field_14, field_18, field_1c, field_20;
    std::uint32_t field_24, field_28, field_2c, field_30, field_34;
    std::int16_t field_38, field_3a;
    std::int32_t sound, alternate_sound;
    std::uint32_t field_44;
    char field_48;
    bool field_49;
    ShotMetadata() noexcept;
    ShotMetadata(const ShotMetadata&) = default;
    ShotMetadata& operator=(const ShotMetadata&) = default;
    ShotMetadata& operator=(ShotMetadata&&);
    ~ShotMetadata();
};

#if defined(_M_IX86)
static_assert(sizeof(ShotMetadata) == 0x4c);
static_assert(offsetof(ShotMetadata, commands) == 4);
static_assert(offsetof(ShotMetadata, field_14) == 0x14);
static_assert(offsetof(ShotMetadata, field_38) == 0x38);
static_assert(offsetof(ShotMetadata, sound) == 0x3c);
static_assert(offsetof(ShotMetadata, field_48) == 0x48);
static_assert(offsetof(ShotMetadata, field_49) == 0x49);
#endif

} // namespace th20
