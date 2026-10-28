#pragma once

#include "BulletValues.hpp"
#include "TaskInfo.hpp"
#include <cstddef>
#include <memory_resource>
#include <vector>

namespace th20 {

// Four real dispatcher temporaries, with separate command-vector lifetimes.
// Neutral field names retain unresolved opcode-specific roles.
struct LaserType0Parameters {
    Vector3 position;
    float angle, length, field_14, length_limit, width, speed;
    std::uint32_t type, color;
    float radial_offset;
    std::uint32_t command_index, flags;
    std::pmr::vector<BulletCommand> commands;
    std::int32_t field_48, field_4c, view_index;
    LaserType0Parameters();
    ~LaserType0Parameters();
};
struct LaserType1Parameters {
    Vector3 position, velocity;
    float angle, angular_velocity, length_limit, length, width, growth_speed;
    std::int32_t delay, grow_time, sustain_time, shrink_time, sound, field_44;
    std::uint32_t handle;
    float radial_offset;
    std::uint32_t command_index, type, color, flags;
    std::pmr::vector<BulletCommand> commands;
    std::int32_t view_index;
    LaserType1Parameters();
    ~LaserType1Parameters();
};
struct CurveNode;
struct LaserType2Flags { std::uint32_t word; };
struct LaserType2Parameters {
    Vector3 position;
    float angle, width, speed;
    std::uint32_t type, color, count;
    float radial_offset;
    LaserType2Flags flags;
    std::pmr::vector<BulletCommand> commands;
    std::int32_t sound, motion_sound;
    std::uint32_t command_index;
    CurveNode* path;
    float time;
    std::uint32_t field_50, field_54;
    std::int32_t view_index;
    LaserType2Parameters();
    ~LaserType2Parameters();
};
struct LaserType3Parameters {
    Vector3 position, vector_0c;
    float angle, field_1c, field_20, field_24;
    std::uint32_t handle, field_2c;
    float field_30;
    std::uint32_t field_34, flags;
    std::pmr::vector<BulletCommand> commands;
    std::int32_t view_index;
    LaserType3Parameters();
    ~LaserType3Parameters();
};

class AnimationFile;
class Laser;
struct Context;

// Native LaserInf owns an observed list; individual Laser bodies are separate.
class LaserController : public TaskInfo {
public:
    IntrusiveList<Laser> active;
    std::uint32_t count;
    std::uint32_t next_handle;
    Vector3 cancel_position;
    Vector3 cancel_size;
    AnimationFile* file;
    std::uint32_t field_4c;
    std::int32_t view_index;
    Context* context;

    LaserController() noexcept;
    ~LaserController() override;
    void select_context(std::int32_t index);
    std::int32_t cancel_all(std::int32_t mode, std::int32_t argument);
    std::int32_t reset_all_lasers();
    void register_laser(Laser* chosen);
    std::int32_t create_laser(std::int32_t type, const void* parameters);
};

LaserController* laser_controller(std::int32_t index);

static_assert(sizeof(LaserType2Flags) == 4);
#if defined(_M_IX86)
static_assert(sizeof(LaserController) == 0x58);
static_assert(offsetof(LaserController, active) == 0x10);
static_assert(offsetof(LaserController, cancel_position) == 0x30);
static_assert(offsetof(LaserController, file) == 0x48);
static_assert(offsetof(LaserController, context) == 0x54);
static_assert(sizeof(LaserType0Parameters) == 0x54);
static_assert(sizeof(LaserType1Parameters) == 0x74);
static_assert(sizeof(LaserType2Parameters) == 0x5c);
static_assert(sizeof(LaserType3Parameters) == 0x50);
static_assert(offsetof(LaserType0Parameters, commands) == 0x38);
static_assert(offsetof(LaserType1Parameters, commands) == 0x60);
static_assert(offsetof(LaserType2Parameters, flags) == 0x28);
static_assert(offsetof(LaserType2Parameters, commands) == 0x2c);
static_assert(offsetof(LaserType2Parameters, path) == 0x48);
static_assert(offsetof(LaserType3Parameters, field_30) == 0x30);
static_assert(offsetof(LaserType3Parameters, commands) == 0x3c);
#endif

// The four native beam vtables (571148, 571214, 5712E8, 571374) all
// contain 34 entries. The slots named below have independently observed
// consumers; unresolved slots remain abstract and have no invented behavior.
// Layout is deliberately partial until the complete Laser lifetimes are
// recovered. Its participating fields match the actual native offsets.
#if defined(_M_IX86)
#pragma pack(push, 4)
#endif
class Laser {
public:
    virtual void set_position(const Vector3&) = 0;         // slot 00
    virtual void point_at_distance(float, Vector3&) = 0;  // slot 04
    virtual void slot_08() = 0;
    virtual void set_parameter_flag(std::uint32_t) = 0;   // slot 0C
    virtual void slot_10() = 0;
    virtual std::int32_t initialize_laser(const void* parameters) = 0; // Native slot +0x14; returns negative on failure
    virtual void slot_18() = 0;
    virtual std::int32_t update() = 0;                    // slot 1C
    virtual std::int32_t draw() = 0;                      // slot 20
    virtual void slot_24() = 0;
    virtual void slot_28() = 0;
    virtual std::int32_t cancel_rectangle(const Vector3&, const Vector3&,
                                          float, std::int32_t, std::int32_t) = 0; // slot 2C
    virtual std::int32_t cancel_circle(const Vector3&, float,
                                       std::int32_t, std::int32_t) = 0; // slot 30
    virtual void slot_34() = 0;
    virtual void slot_38() = 0;
    virtual void slot_3c() = 0;
    virtual void slot_40() = 0;
    virtual std::int32_t erase(std::int32_t, std::int32_t) = 0; // slot 44
    virtual std::int32_t proximity(const Vector3&, float) = 0; // slot 48
    virtual std::int32_t cancel_all(std::int32_t) = 0;   // slot 4C
    virtual void slot_50() = 0;
    virtual void slot_54() = 0;
    virtual void slot_58() = 0;
    virtual void slot_5c() = 0;
    virtual void slot_60() = 0;
    virtual void slot_64() = 0;
    virtual void slot_68() = 0;
    virtual void slot_6c() = 0;
    virtual void slot_70() = 0;
    virtual void slot_74() = 0;
    virtual void slot_78() = 0;
    virtual void slot_7c() = 0;
    virtual void slot_80() = 0;
    virtual ~Laser();                                     // slot 84

    std::uint32_t field_04;
    IntrusiveLink<Laser> link;                            // +08
    // The large native body is not a dummy padding block: its timer,
    // motion and 24 x 64-byte extended-command layout can be checked against
    // native constructors and consumers, independently of this loop.
    std::uint32_t flags;
    std::int32_t state;
    std::uint32_t field_24;
    Timer age;
    Timer timer_38, timer_48;
    Vector3 position, velocity;
    float angle, field_74, speed, field_7c, field_80;
    std::uint32_t field_84, field_88, handle;
    ExtendedCommand commands[24];
    std::uint32_t command_index, field_694;
    std::uint64_t active_commands;
    std::uint32_t field_6a0, field_6a4, field_6a8;
    Timer timer_6ac, timer_6bc;
    std::uint32_t field_6cc, field_6d0, field_6d4;
    void* allocated_6d8;
    std::uint32_t field_6dc, field_6e0, field_6e4, field_6e8;
    std::int32_t view_index;
    Context* context;
    std::uint32_t field_6f4;
};
#if defined(_M_IX86)
#pragma pack(pop)
#endif

#if defined(_M_IX86)
static_assert(sizeof(Laser) == 0x6f8);
static_assert(offsetof(Laser, link) == 0x08);
static_assert(offsetof(Laser, commands) == 0x90);
static_assert(offsetof(Laser, active_commands) == 0x698);
static_assert(offsetof(Laser, timer_6ac) == 0x6ac);
static_assert(offsetof(Laser, context) == 0x6f0);
static_assert(offsetof(Laser, field_6cc) == 0x6cc);
#endif

} // namespace th20
