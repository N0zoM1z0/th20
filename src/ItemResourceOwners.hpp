#pragma once
#include "AnimationFile.hpp"
#include "AnimationHandle.hpp"
#include "Cursor.hpp"
#include "Context.hpp"
#include "Timer.hpp"
#include "EffectParameters.hpp"
#include "TaskInfo.hpp"
#include "Worker.hpp"
#include <array>

namespace th20 {
// Native storage corroborated by constructors, array strides and deleting sizes.
// Original loading and resource-owning destruction remain undefined interfaces.
// Effect handle composition and original class names are source inferences.
struct EffectAnimationHandle {
    AnimationHandle handle;
    EffectAnimationHandle() noexcept;
    bool matches_value(std::uint32_t input);
    bool missing();
};
static_assert(sizeof(EffectAnimationHandle)==4);
class EffectInfo : public TaskInfo {
public:
    std::array<AnimationFile*,3> files;
    std::int32_t field_1c, handle_cursor, field_24;
    Worker worker;
    std::uint32_t ready;
    std::array<EffectAnimationHandle,1024> handles;
    std::array<EffectRequest,1024> requests;
    std::int32_t view_index;
    Context* context;
    EffectInfo();
    ~EffectInfo() override;
    AnimationFile* animation_file(std::int32_t index);
    std::int32_t select_handle_slot();
    std::uint32_t publish_handle(std::uint32_t handle);
    // Native scheduler returns void. The final pointer selects an existing
    // animation for the later deferred creator (null means spawn new).
    // Process 1024 animation handles and all 1024 scheduled effect requests.
    // The native frame tick returns 1, independently from queue_effect().
    std::int32_t process_queued_effects();
    void queue_effect(std::int32_t delay_frames, std::int32_t kind,
                      const EffectParameters& parameters, Animation* existing_animation);
    AnimationHandle spawn_effect(std::int32_t kind, const EffectParameters& parameters,
                                 Animation* existing_animation);
    // Alternate original effect spawn: flag-4 AnimationFile creation and
    // the same callback table, but no recursive Animation flag setting.
    AnimationHandle spawn_effect_variant(std::int32_t kind,
                                         const EffectParameters& parameters,
                                         Animation* existing_animation);
};
class StoneMenuInfo : public TaskInfo {
public:
    AnimationFile* file;
    std::int32_t visible;
    Timer age;
    Cursor category,selection;
    std::int32_t saved_selection;
    AnimationHandle handles[9];
    Vector3 selection_position;
    char names[88][256];
    char descriptions[88][5][256];
    std::int32_t state;
    std::uint8_t field_210f8;
    std::int32_t view_index;
    Context* context;
    StoneMenuInfo();
    ~StoneMenuInfo() override;
    void enable() override;
    AnimationFile* animation_file();
};
extern StoneMenuInfo* process_stone_menu;
StoneMenuInfo* stone_menu_info();
#if defined(_M_IX86)
static_assert(sizeof(EffectInfo)==0x13044);
static_assert(offsetof(EffectInfo,files)==0x10);
static_assert(offsetof(EffectInfo,field_1c)==0x1c);
static_assert(offsetof(EffectInfo,handle_cursor)==0x20);
static_assert(offsetof(EffectInfo,worker)==0x28);
static_assert(offsetof(EffectInfo,requests)==0x103c);
static_assert(sizeof(StoneMenuInfo)==0x21104);
static_assert(offsetof(StoneMenuInfo,category)==0x28);
static_assert(offsetof(StoneMenuInfo,names)==0xf4);
static_assert(offsetof(StoneMenuInfo,descriptions)==0x58f4);
static_assert(offsetof(StoneMenuInfo,state)==0x210f4);
#endif
}
