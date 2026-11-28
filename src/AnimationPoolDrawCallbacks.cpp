// Draw-chain callbacks registered by the AnimationPoolOwner constructor at
// 0x00447E00. Each one classifies one renderer group; the groups listed with
// a view reset first clear the owner view selection at +0x6C0.
#include "NativeAnimationRendererUpdate.hpp"
#include "NativeRendererClassificationOwner.hpp"

#include <cstdint>

namespace th20 {

void NativeRendererClassificationOwner::clear_view_selection_44ee70() {
    *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x6C0) = -1;
}

int __cdecl update_secondary_renderers_4508c0(AnimationPoolOwner* pool) {
    return animation_renderer_update_secondary_449a70(pool);
}

int __cdecl draw_renderer_group_0_4508d0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(0);
}

int __cdecl draw_renderer_group_1_4508e0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(1);
}

int __cdecl draw_renderer_group_4_4508f0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(4);
}

int __cdecl draw_renderer_group_15_450900(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(15);
}

int __cdecl draw_renderer_group_2_450910(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(2);
}

int __cdecl draw_renderer_group_18_450920(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(18);
}

int __cdecl draw_renderer_group_7_450930(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(7);
}

int __cdecl draw_renderer_group_8_450940(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(8);
}

int __cdecl draw_renderer_group_9_450950(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(9);
}

int __cdecl draw_renderer_group_10_450960(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(10);
}

int __cdecl draw_renderer_group_16_450970(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(16);
}

int __cdecl draw_renderer_group_17_450980(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(17);
}

int __cdecl draw_renderer_group_32_450990(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(32);
}

int __cdecl draw_renderer_group_33_4509a0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(33);
}

int __cdecl draw_renderer_group_37_4509b0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(37);
}

int __cdecl draw_renderer_group_38_4509c0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(38);
}

int __cdecl draw_renderer_group_34_4509d0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(34);
}

int __cdecl draw_renderer_group_35_4509e0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(35);
}

int __cdecl draw_renderer_group_36_4509f0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(36);
}

int __cdecl draw_renderer_group_29_450a00(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(29);
}

int __cdecl draw_renderer_group_26_450a10(NativeRendererClassificationOwner* owner) {
    static_cast<NativeRendererClassificationOwner*>(current_animation_pool)->clear_view_selection_44ee70();
    return owner->select_renderer_group_449e40(26);
}

int __cdecl draw_renderer_group_30_450a30(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(30);
}

int __cdecl draw_renderer_group_31_450a40(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(31);
}

int __cdecl draw_renderer_group_3_450a50(NativeRendererClassificationOwner* owner) {
    static_cast<NativeRendererClassificationOwner*>(current_animation_pool)->clear_view_selection_44ee70();
    return owner->select_renderer_group_449e40(3);
}

int __cdecl draw_renderer_group_5_450a70(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(5);
}

int __cdecl draw_renderer_group_11_450a80(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(11);
}

int __cdecl draw_renderer_group_6_450a90(NativeRendererClassificationOwner* owner) {
    static_cast<NativeRendererClassificationOwner*>(current_animation_pool)->clear_view_selection_44ee70();
    return owner->select_renderer_group_449e40(6);
}

int __cdecl draw_renderer_group_19_450ab0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(19);
}

int __cdecl draw_renderer_group_12_450ac0(NativeRendererClassificationOwner* owner) {
    static_cast<NativeRendererClassificationOwner*>(current_animation_pool)->clear_view_selection_44ee70();
    return owner->select_renderer_group_449e40(12);
}

int __cdecl draw_renderer_group_25_450ae0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(25);
}

int __cdecl draw_renderer_group_24_450af0(NativeRendererClassificationOwner* owner) {
    static_cast<NativeRendererClassificationOwner*>(current_animation_pool)->clear_view_selection_44ee70();
    return owner->select_renderer_group_449e40(24);
}

int __cdecl draw_renderer_group_22_450b10(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(22);
}

int __cdecl draw_renderer_group_23_450b20(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(23);
}

int __cdecl draw_renderer_group_21_450b30(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(21);
}

int __cdecl draw_renderer_group_20_450b40(NativeRendererClassificationOwner* owner) {
    static_cast<NativeRendererClassificationOwner*>(current_animation_pool)->clear_view_selection_44ee70();
    return owner->select_renderer_group_449e40(20);
}

int __cdecl draw_renderer_group_28_450b60(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(28);
}

int __cdecl draw_renderer_group_27_450b70(NativeRendererClassificationOwner* owner) {
    static_cast<NativeRendererClassificationOwner*>(current_animation_pool)->clear_view_selection_44ee70();
    return owner->select_renderer_group_449e40(27);
}

int __cdecl draw_renderer_group_49_450b90(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(49);
}

int __cdecl draw_renderer_group_50_450ba0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(50);
}

int __cdecl draw_renderer_group_54_450bb0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(54);
}

int __cdecl draw_renderer_group_55_450bc0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(55);
}

int __cdecl draw_renderer_group_51_450bd0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(51);
}

int __cdecl draw_renderer_group_52_450be0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(52);
}

int __cdecl draw_renderer_group_53_450bf0(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(53);
}

int __cdecl draw_renderer_group_46_450c00(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(46);
}

int __cdecl draw_renderer_group_45_450c10(NativeRendererClassificationOwner* owner) {
    static_cast<NativeRendererClassificationOwner*>(current_animation_pool)->clear_view_selection_44ee70();
    return owner->select_renderer_group_449e40(45);
}

int __cdecl draw_renderer_group_47_450c30(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(47);
}

int __cdecl draw_renderer_group_48_450c40(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(48);
}

int __cdecl draw_renderer_group_14_450c50(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(14);
}

int __cdecl draw_renderer_group_13_450c60(NativeRendererClassificationOwner* owner) {
    return owner->select_renderer_group_449e40(13);
}

} // namespace th20
