#pragma once
#include "Timer.hpp"
#include "Vector3.hpp"
#include <cstddef>
#include <cstdint>
namespace th20 {
// Native 0x44-byte per-player reward-number record. The eight bytes before
// active and the ten trailing bytes are retained, unassigned storage.
struct ItemRewardPopupEntry {
    std::uint8_t digits[10];
    std::uint8_t field_0a[2];
    Vector3 position;
    float clock_value;
    std::uint32_t color;
    Timer timer;
    std::uint8_t field_30[8];
    std::uint8_t active;
    std::uint8_t digit_count;
    std::uint8_t field_3a[10];
};
static_assert(sizeof(ItemRewardPopupEntry)==0x44);
static_assert(offsetof(ItemRewardPopupEntry,position)==0x0c);
static_assert(offsetof(ItemRewardPopupEntry,clock_value)==0x18);
static_assert(offsetof(ItemRewardPopupEntry,color)==0x1c);
static_assert(offsetof(ItemRewardPopupEntry,timer)==0x20);
static_assert(offsetof(ItemRewardPopupEntry,active)==0x38);
static_assert(offsetof(ItemRewardPopupEntry,digit_count)==0x39);
struct ItemRewardPopupQueue {
    std::uint8_t field_00[0x14];
    std::int32_t current;
    std::uint8_t field_18[0x5e8];
    ItemRewardPopupEntry entries[10];
    void enqueue(const Vector3* position,std::int32_t amount,std::uint32_t color);
};
static_assert(offsetof(ItemRewardPopupQueue,current)==0x14);
static_assert(offsetof(ItemRewardPopupQueue,entries)==0x600);
ItemRewardPopupQueue* item_reward_popup_queue(std::int32_t index);
}
