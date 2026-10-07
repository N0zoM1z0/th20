#pragma once

#include "BulletValues.hpp"
#include <cstddef>
#include <memory_resource>
#include <vector>

// Native shared-control RTTI establishes this original global struct name.
// Unknown operand roles stay neutral; commands are the real 44-byte values.
struct EtamaArgInf {
    float field_00;
    std::pmr::vector<th20::BulletCommand> commands;
    float field_14, field_18, field_1c, field_20;
    std::uint32_t field_24, field_28, field_2c, field_30, field_34;
    std::int16_t field_38, field_3a;
    std::int32_t sound, alternate_sound;
    std::uint32_t field_44;
    char field_48;
    bool field_49;
    EtamaArgInf() noexcept;
    EtamaArgInf(const EtamaArgInf&) = default;
    EtamaArgInf& operator=(const EtamaArgInf&) = default;
    EtamaArgInf& operator=(EtamaArgInf&&);
    ~EtamaArgInf();
};

namespace th20 {

// Preserve the semantic spelling without changing the RTTI-visible type.
using ShotMetadata = ::EtamaArgInf;

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
