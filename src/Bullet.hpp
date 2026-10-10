#pragma once
#include "TaskInfo.hpp"
#include "Angle.hpp"
#include "BulletValues.hpp"
#include "AnimationHandle.hpp"
#include "IntrusiveLink.hpp"
#include "Interpolation.hpp"
#include "ShotMetadata.hpp"
#include "Context.hpp"
#include <memory>
namespace th20 {
// EXACT-078: native BulletInf and its typed 2001-entry pool. Offset names
// retain unresolved roles; alignment gaps are supplied by actual members.
struct AnimationFile;
struct BulletStyle;
// Native +88 is packed color consumed by effect parameters, not an ANM id.
// Its zero-construction head folds with other independent four-byte values.
struct BulletColor {
    std::uint32_t value;
    BulletColor();
};
struct BulletFlags { std::uint32_t bits; };
struct BulletCommandFlags { std::uint64_t bits; };
struct BulletExtendedCommands {
    ExtendedCommand slots[14];
    BulletExtendedCommands() noexcept;
};
struct Bullet {
    IntrusiveLink<Bullet> link;
    BulletFlags flags;
    std::int32_t field_18;
    Animation* animation;
    float speed,field_24;
    std::uint32_t index,field_2c,command_index;
    std::int32_t cancel_script;
    std::uint32_t field_38,field_3c,field_40,draw_group;
    float scale;
    std::int16_t field_4c,field_4e;
    std::int32_t state;
    std::uint32_t field_54;
    BulletStyle* style;
    AnimationHandle animation_handle;
    Bullet* draw_next;
    Vector3 position,velocity;
    Vector2 size;
    Angle angle;
    BulletColor color;
    BulletCommandFlags command_flags;
    std::shared_ptr<ShotMetadata> metadata;
    BulletExtendedCommands commands;
    VectorInterpolation interpolation_420;
    FloatInterpolation interpolation_474;
    Timer timer_4a0,timer_4b0,timer_4c0;
    std::uint32_t field_4d0,field_4d4;
    Timer timer_4d8,timer_4e8,timer_4f8,timer_508;
    std::uint32_t field_518;
    std::int32_t view_index;
    Context* context;
    std::int32_t type() const;
    std::int32_t color_index() const;
    Bullet();
    ~Bullet();
};
struct BulletPool {
    Bullet slots[2001];
    BulletPool();
    ~BulletPool();
    Bullet* begin();
    Bullet* end();
};
struct BulletHandles {
    AnimationHandle slots[2001];
    BulletHandles() noexcept;
};
struct BulletController final : TaskInfo {
    Bullet* next_bullet;
    Bullet* draw_heads[6];
    Bullet* draw_tails[6];
    std::int32_t bullet_count;
    float field_48;
    Vector2 vector_4c,vector_54;
    BulletPool pool;
    BulletHandles handles;
    IntrusiveList<Bullet> free,active;
    std::uint32_t age,item_counter,field_286d84,cancel_counter;
    AnimationFile* file;
    std::uint32_t field_286d90,field_286d94,field_286d98;
    std::int32_t view_index;
    Context* context;
    BulletController() noexcept;
    // Whole callback registration and controller retirement remain open.
    ~BulletController() override;
    void enable() override;
    void disable() override;
    void select_context(std::int32_t index);
    std::int32_t count();
};
BulletController* bullet_controller(std::int32_t index);
#if defined(_M_IX86)
static_assert(sizeof(Bullet)==0x528);
static_assert(offsetof(Bullet,command_flags)==0x90);
static_assert(offsetof(Bullet,color)==0x88);
static_assert(offsetof(Bullet,style)==0x58);
static_assert(offsetof(Bullet,metadata)==0x98);
static_assert(offsetof(Bullet,commands)==0xa0);
static_assert(offsetof(Bullet,interpolation_420)==0x420);
static_assert(offsetof(Bullet,context)==0x520);
static_assert(sizeof(BulletController)==0x286da8);
static_assert(offsetof(BulletController,pool)==0x60);
static_assert(offsetof(BulletController,handles)==0x284e08);
static_assert(offsetof(BulletController,free)==0x286d4c);
static_assert(offsetof(BulletController,context)==0x286da0);
#endif
}
