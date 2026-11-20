#include "HudGauge.hpp"
#include "Animation.hpp"
namespace th20 {
extern const float native_progress_marker_spacing_56fd48;
extern const std::int32_t native_progress_script_frames_570780[3];
extern const std::int32_t native_progress_script_frames_57078c[3];
void __fastcall interrupt_animation_mode2(Animation* animation);
void __fastcall interrupt_animation_mode3(Animation* animation);
void __fastcall interrupt_animation_mode5(Animation* animation) {
    animation->interrupt(5);
}
void Animation::interrupt_offset_7(std::int32_t event) {
    interrupt(event+7);
}
void FrontInf::update_progress_handles_50(std::int32_t active_count,
                                          std::int32_t script_index,
                                          std::int32_t filled_count) {
    if (*progress_handles_50.slot(0)==nullptr) return;
    Vector3 offset(0.0f,0.0f,0.0f);
    offset.x=static_cast<float>(7-filled_count)*native_progress_marker_spacing_56fd48;
    std::uint32_t i=0;
    for (;i<7;++i)
        (*progress_handles_50.slot(static_cast<std::int32_t>(i)))->set_position(offset);
    i=0;
    for (;static_cast<std::int32_t>(i)<active_count;++i)
        interrupt_animation_mode2(*progress_handles_50.slot(static_cast<std::int32_t>(i)));
    if (static_cast<std::int32_t>(i)<filled_count) {
        (*progress_handles_50.slot(static_cast<std::int32_t>(i)))->interrupt_offset_7(
            native_progress_script_frames_570780[script_index]);
        ++i;
    }
    for (;static_cast<std::int32_t>(i)<filled_count;++i)
        interrupt_animation_mode3(*progress_handles_50.slot(static_cast<std::int32_t>(i)));
    for (;i<7;++i)
        interrupt_animation_mode5(*progress_handles_50.slot(static_cast<std::int32_t>(i)));
}
void FrontInf::update_progress_handles_6c(std::int32_t active_count,
                                          std::int32_t script_index,
                                          std::int32_t filled_count) {
    if (*progress_handles_6c.slot(0)==nullptr) return;
    Vector3 offset(0.0f,0.0f,0.0f);
    offset.x=static_cast<float>(7-filled_count)*native_progress_marker_spacing_56fd48;
    std::uint32_t i=0;
    for (;i<7;++i)
        (*progress_handles_6c.slot(static_cast<std::int32_t>(i)))->set_position(offset);
    i=0;
    for (;static_cast<std::int32_t>(i)<active_count;++i)
        interrupt_animation_mode2(*progress_handles_6c.slot(static_cast<std::int32_t>(i)));
    if (static_cast<std::int32_t>(i)<filled_count) {
        (*progress_handles_6c.slot(static_cast<std::int32_t>(i)))->interrupt_offset_7(
            native_progress_script_frames_57078c[script_index]);
        ++i;
    }
    for (;static_cast<std::int32_t>(i)<filled_count;++i)
        interrupt_animation_mode3(*progress_handles_6c.slot(static_cast<std::int32_t>(i)));
    for (;i<7;++i)
        interrupt_animation_mode5(*progress_handles_6c.slot(static_cast<std::int32_t>(i)));
}
}
