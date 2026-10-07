#include "Animation.hpp"
#include "DiagnosticAllocator.hpp"
namespace th20 {
AnimationBase::AnimationBase() noexcept : timer(), field_10(0), field_14(0),
    field_18(0), field_1c(0), field_20(0), field_24(0), field_28(0), vector_2c(),
    vector_38(), vector_44(), vector_50(), vector_58(), vector_60(), vector_68(),
    vector_70(), field_78(0.0f), field_7c(0.0f), vector_80(), interpolation_8c(),
    interpolation_e0(), interpolation_134(), interpolation_160(), interpolation_1b4(),
    interpolation_1e0(), interpolation_220(), interpolation_260(), interpolation_2a0(),
    interpolation_2f4(), interpolation_320(), interpolation_34c(), vectors_378(),
    vector_398(), field_3a0(0.0f), field_3a4(0.0f), field_3a8(0), field_3ac(0),
    field_3b0(0), field_3b4(0), matrix_3b8(), matrix_3f8(), field_438(0), field_43c(0),
    field_440(0), variables(), vector_484(), color_490(0), color_494(0), flags{},
    field_4b8(0.0f), field_4bc(0.0f) {}
Animation::Animation() noexcept : base(), handle(), index(0), timer_4c8(), timer_4d8(),
    field_4e8(0), link_4ec(this), link_500(this), link_514(this), link_528(this),
    link_53c(this), field_550(0), field_554(0), parent_558(nullptr), parent_55c(nullptr), field_560(0.0f),
    geometry(nullptr), callback(nullptr), geometry_bytes(0), field_570(0), field_574(0), field_578(0),
    field_579(0), matrix_57c(), vector_5bc(), field_5c8(0), field_5cc(0), vector_5d0(),
    field_5dc(0), field_5e0(0) {}
Animation::~Animation() noexcept { release_resources(); }
PooledAnimation::PooledAnimation() : animation(), free_link(), active(0), index(0) {}
void Animation::reset() {
    base.vector_50.x = 1.0f;
    base.vector_50.y = 1.0f;
    base.vector_58.x = 1.0f;
    base.vector_58.y = 1.0f;
    base.vector_68.x = 1.0f;
    base.vector_68.y = 1.0f;
    base.color_490 = 0xffffffffu;
    base.matrix_3b8 = identity_matrix;
    base.flags = {};
    base.flags.bit_10 = 1;
    base.flags.word_04 |= 1u;
    base.flags.mode = 1;
    timer_4c8.reset();
    timer_4d8.reset();
    base.variables.field_34 = 1.0f;
    base.variables.field_38 = 3.1415927410125732f;
    base.variables.field_3c = 0x10000;
    parent_558 = nullptr;
    parent_55c = nullptr;
    base.vector_2c = {0.0f, 0.0f, 0.0f};
    base.vector_484 = {0.0f, 0.0f, 0.0f};
    base.vector_38 = {0.0f, 0.0f, 0.0f};
    base.vector_44 = {0.0f, 0.0f, 0.0f};
    base.vector_50 = {1.0f, 1.0f};
    base.vector_58 = {1.0f, 1.0f};
    base.vector_60 = {0.0f, 0.0f};
    base.vector_68 = {1.0f, 1.0f};
    base.vector_70 = {0.0f, 0.0f};
    base.field_7c = 0.0f;
    base.field_78 = 0.0f;
    base.vector_80 = {0.0f, 0.0f, 0.0f};
    base.interpolation_8c.stop();
    base.interpolation_e0.stop();
    base.interpolation_134.stop();
    base.interpolation_160.stop();
    base.interpolation_1b4.stop();
    base.interpolation_1e0.stop();
    base.interpolation_220.stop();
    base.interpolation_260.stop();
    base.interpolation_2a0.stop();
    base.interpolation_2f4.stop();
    base.interpolation_320.stop();
    base.interpolation_34c.stop();
    field_570 = 0;
}
Vector3& Animation::position_ref() { return base.vector_2c; }
float Animation::inherited_scale_y() {
    float parent_scale = 1.0f;
    if (parent_558 && !((base.flags.word_04 >> 12) & 1u))
        parent_scale = parent_558->inherited_scale_y();
    return base.vector_50.y * parent_scale;
}
float Animation::inherited_scale_x() {
    float parent_scale = 1.0f;
    if (parent_558 && !((base.flags.word_04 >> 12) & 1u))
        parent_scale = parent_558->inherited_scale_x();
    return base.vector_50.x * parent_scale;
}
float Animation::height() { return base.vector_70.y * inherited_scale_y(); }
float Animation::width() { return base.vector_70.x * inherited_scale_x(); }
}

namespace th20 {
void Animation::release_resources() {
    if (geometry) process_allocator->release_bytes(geometry);
    geometry = nullptr;
    geometry_bytes = 0;
    process_allocator->release_animation_callback(callback);
    callback = nullptr;
    handle = 0;
    base.field_28 = -1;
    // Preserve the observed nonreturning path rather than inventing recovery.
    if (field_550) {
        while (true) { handle = 0; }
    }
}
}
