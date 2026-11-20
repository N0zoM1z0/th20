#include "ItemRewardPopupQueue.hpp"
#include "Session.hpp"
#include "Player.hpp"
namespace th20 {
extern const float native_one_56c8cc;
ItemRewardPopupQueue* __cdecl item_reward_popup_queue(std::int32_t index) {
    return reinterpret_cast<ItemRewardPopupQueue*>(
        reinterpret_cast<Player*>(&session.context(index))->animation_file_ref());
}
void ItemRewardPopupQueue::enqueue(const Vector3* position,std::int32_t amount,std::uint32_t color) {
    if (current>=10) current=0;
    std::int32_t count;
    ItemRewardPopupEntry* entry=&entries[current];
    entry->active=1;
    count=0;
    if (amount>=0) {
        while (amount!=0) {
            entry->digits[count]=static_cast<std::uint8_t>(amount%10);
            ++count;
            amount/=10;
        }
    } else {
        entry->digits[count]=10;
        ++count;
    }
    if (count==0) {
        entry->digits[count]=0;
        ++count;
    }
    entry->digit_count=count;
    entry->color=color;
    entry->timer=0;
    entry->position=*position;
    entry->clock_value=native_one_56c8cc;
    ++current;
}
}
