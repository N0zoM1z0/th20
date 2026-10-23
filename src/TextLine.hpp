#pragma once

#include "Vector3.hpp"
#include "Angle.hpp"
#include "Animation.hpp"
#include "AnimationHandle.hpp"
#include "Rectangle.hpp"
#include "TaskInfo.hpp"
#include "Worker.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <list>
#include <type_traits>

namespace th20 {

// REF-022: native ASCII queue records have a 0x140-byte stride.
struct TextLine {
    char text[256];
    Vector3 position;
    std::uint32_t color;
    std::uint32_t blend;
    float scale_x;
    float scale_y;
    float rotation;
    std::uint32_t field_120;
    std::uint32_t field_124;
    std::int32_t font;
    std::uint32_t shadow;
    std::int32_t layer;
    std::int32_t frames;
    std::uint32_t align_x;
    std::uint32_t align_y;

    TextLine() noexcept;
};

static_assert(sizeof(TextLine) == 0x140);
static_assert(offsetof(TextLine, position) == 0x100);
static_assert(offsetof(TextLine, color) == 0x10C);
static_assert(offsetof(TextLine, blend) == 0x110);
static_assert(offsetof(TextLine, scale_x) == 0x114);
static_assert(offsetof(TextLine, scale_y) == 0x118);
static_assert(offsetof(TextLine, rotation) == 0x11C);
static_assert(offsetof(TextLine, field_120) == 0x120);
static_assert(offsetof(TextLine, field_124) == 0x124);
static_assert(offsetof(TextLine, font) == 0x128);
static_assert(offsetof(TextLine, shadow) == 0x12C);
static_assert(offsetof(TextLine, layer) == 0x130);
static_assert(offsetof(TextLine, frames) == 0x134);
static_assert(offsetof(TextLine, align_x) == 0x138);
static_assert(offsetof(TextLine, align_y) == 0x13C);
static_assert(std::is_trivially_copyable_v<TextLine>);

class AnimationFile;
struct TextJob;

// The text queue and resource receiver at process slot 0x005c0698.
// The three Animations are separate members in the native constructor.
class AsciiInf : public TaskInfo {
public:
    Animation animation_10;
    Animation animation_5f4;
    Animation animation_bd8;
    std::array<TextLine, 320> lines;
    std::int32_t line_count;
    std::uint32_t color;
    std::uint32_t shadow_color;
    std::uint32_t field_1a1c8;
    float scale_x;
    float scale_y;
    std::uint32_t field_1a1d4;
    std::uint32_t field_1a1d8;
    std::uint32_t shadow;
    std::int32_t font;
    std::int32_t field_1a1e4;
    std::uint32_t field_1a1e8;
    std::int32_t layer;
    std::int32_t frames;
    std::uint32_t align_x;
    std::uint32_t align_y;
    std::uint32_t blend;
    IntPoint texture_size;
    Angle rotation;
    IntrusiveList<TextJob> jobs;
    Worker worker;
    std::list<std::function<void()>> pending_tasks;
    std::int32_t font_width;
    std::int32_t field_1a240;
    AnimationFile* animation_file;
    AnimationHandle animation_handle;
    AnimationHandle loading_handle;
    FunctionChainNode* draw_node_1a250;
    FunctionChainNode* draw_node_1a254;
    FunctionChainNode* draw_node_1a258;
    FunctionChainNode* draw_node_1a25c;
    char text_buffer[256];

    AsciiInf() noexcept;
    ~AsciiInf() override;
    void enable() override;
    AnimationFile* text_animation_file();
};

extern AsciiInf* current_ascii;
// This is the shared resource slot, separate from AsciiInf::animation_file.
extern AnimationFile* shared_text_animation_file;

#if defined(_M_IX86)
static_assert(sizeof(AsciiInf) == 0x1A360);
static_assert(offsetof(AsciiInf, animation_10) == 0x10);
static_assert(offsetof(AsciiInf, animation_5f4) == 0x5F4);
static_assert(offsetof(AsciiInf, animation_bd8) == 0xBD8);
static_assert(offsetof(AsciiInf, lines) == 0x11BC);
static_assert(offsetof(AsciiInf, line_count) == 0x1A1BC);
static_assert(offsetof(AsciiInf, scale_x) == 0x1A1CC);
static_assert(offsetof(AsciiInf, texture_size) == 0x1A200);
static_assert(offsetof(AsciiInf, rotation) == 0x1A208);
static_assert(offsetof(AsciiInf, jobs) == 0x1A20C);
static_assert(offsetof(AsciiInf, worker) == 0x1A224);
static_assert(offsetof(AsciiInf, pending_tasks) == 0x1A234);
static_assert(offsetof(AsciiInf, animation_file) == 0x1A244);
static_assert(offsetof(AsciiInf, text_buffer) == 0x1A260);
#endif

} // namespace th20
