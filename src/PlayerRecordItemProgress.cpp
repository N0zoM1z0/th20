#include "PlayerRecord.hpp"
#include "HudGauge.hpp"
#include "NativeCardFinishViews.hpp"
#include "Session.hpp"
#include "SoundInf.hpp"
#include <cstdint>
namespace th20 {
extern const std::int32_t native_item_progress_thresholds_standard[31];
extern const std::int32_t native_item_progress_thresholds_mode4[10];

void PlayerRecord::advance_progress_cc(std::int32_t amount) {
    field_cc+=amount;
    if (field_cc>=clamped_field_d8())
        field_d0=0;
    if (field_cc>clamped_field_d8())
        field_cc=clamped_field_d8();
    else
        process_sound.request_effect(0x2e,0);
    if (current_front!=nullptr)
        current_front->update_progress_handles_6c(
            clamped_field_cc(),clamped_field_d0(),clamped_field_d8());
}

void PlayerRecord::tick_progress_d0(std::int32_t amount) {
    if (field_cc>=clamped_field_d8()) {
        field_d0=0;
    } else {
        field_d0+=amount;
        if (field_d0>=3) {
            field_d0=0;
            advance_progress_cc(1);
        }
        if (current_front!=nullptr)
            current_front->update_progress_handles_6c(
                clamped_field_cc(),clamped_field_d0(),clamped_field_d8());
    }
}

std::int32_t PlayerRecord::advance_progress_b8(std::int32_t amount) {
    if (field_b8>=clamped_field_bc())
        field_c0=0;
    field_b8+=amount;
    if (field_b8>clamped_field_bc()) {
        field_b8=clamped_field_bc();
        field_c0=0;
    }
    if (current_front!=nullptr)
        current_front->update_progress_handles_50(
            clamped_field_b8(),clamped_field_c0(),clamped_field_bc());
    return 1;
}

void PlayerRecord::tick_progress_c0(std::int32_t amount) {
    if (field_b8>=clamped_field_bc()) {
        field_c0=0;
        return;
    }
    field_c0+=amount;
    std::int32_t threshold;
    if (session.mode()==4)
        threshold=native_item_progress_thresholds_mode4[field_c4];
    else
        threshold=native_item_progress_thresholds_standard[field_c4];
    std::int32_t loop_threshold=threshold;
    while (static_cast<volatile std::int32_t&>(field_c0)>=loop_threshold) {
        field_c0-=loop_threshold;
        advance_progress_c4();
    }
    if (current_front!=nullptr) {
        std::int32_t progress_max=clamped_field_bc();
        std::int32_t progress_accumulator=clamped_field_c0();
        std::int32_t progress_count=clamped_field_b8();
        current_front->update_progress_handles_50(
            progress_count,progress_accumulator,progress_max);
    }
}

void PlayerRecord::advance_progress_c4() {
    if (advance_progress_b8(1)!=0) {
        process_sound.request_effect(0x11,0);
        if (current_front!=nullptr)
            reinterpret_cast<NativeCardHudView*>(current_front)->report_spell_result_4b90e0(4,0);
    }
    ++field_c4;
}

extern const std::int32_t native_item_progress_thresholds_standard[31] = {
    3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
    3,3,3,3,3,3,3,3,3,3,3,3,3,3,99999999
};
extern const std::int32_t native_item_progress_thresholds_mode4[10] = {
    3,3,3,3,3,3,3,3,3,99999999
};
}
