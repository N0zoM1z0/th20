#pragma once
#include "Animation.hpp"
#include "Context.hpp"
#include "TaskInfo.hpp"
#include <array>
namespace th20 {
struct Item {
    IntrusiveLink<Item> link;
    IntrusiveList<Item>* free_list;
    Animation animation,secondary_animation;
    AnimationHandle attachment;
    Vector3 position,velocity;
    float speed,angle;
    Timer timer,secondary_timer;
    std::int32_t state,type,draw_state;
    float attraction_speed;
    std::int32_t delay,generation;
    std::uint32_t extra;
    std::int32_t sound,view_index;
    Context* context;
    Item();
    ~Item();
    void select_context(std::int32_t index);
    void spawn_effect();
};
class ItemInf : public TaskInfo {
public:
    std::uint32_t field_10;
    FunctionChainNode* second_draw_node;
    std::array<Item,1536> pool;
    IntrusiveList<Item> active,ordinary_free,special_free;
    float speed_scale;
    std::int32_t processed,spawn_counter,point_counter,special_count,generation,bonus_counter;
    std::int32_t field_49c87c,field_49c880,attract;
    Vector3 attraction_center;
    std::int32_t view_index;
    Context* context;
    ItemInf() noexcept;
    ~ItemInf() override;
    void enable() override;
    void select_context(std::int32_t index);
    // Native whole-pool byte initialization requires fresh, resource-free
    // Item/Animation storage. It is not a general release/reset operation.
    void initialize_pool();
    std::int32_t initialize(std::int32_t index);
    void spawn_many(const Vector3* position,std::int32_t count,std::int32_t type);
    // Primary spawning is maintained; original frame callbacks remain open.
    Item* spawn(std::int32_t type,const Vector3& position,std::uint32_t color,float angle,float speed,
                std::int32_t delay,std::uint32_t extra,std::int32_t sound);
    static std::int32_t update_callback(void* owner);
    static std::int32_t draw_callback(void* owner);
    static std::int32_t second_draw_callback(void* owner);
};
ItemInf* item_controller(std::int32_t index);
ItemInf* create_item_controller(std::int32_t index);
#if defined(_M_IX86)
static_assert(sizeof(Item)==0xc4c);
static_assert(offsetof(Item,animation)==0x18);
static_assert(offsetof(Item,attachment)==0xbe0);
static_assert(offsetof(Item,position)==0xbe4);
static_assert(offsetof(Item,state)==0xc24);
static_assert(offsetof(Item,context)==0xc48);
static_assert(sizeof(ItemInf)==0x49c89c);
static_assert(offsetof(ItemInf,pool)==0x18);
static_assert(offsetof(ItemInf,active)==0x49c818);
static_assert(offsetof(ItemInf,speed_scale)==0x49c860);
static_assert(offsetof(ItemInf,context)==0x49c898);
#endif
}
