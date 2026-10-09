#include "Item.hpp"
#include "Session.hpp"
#include "FunctionChainController.hpp"
#include "EclDiagnostic.hpp"
#include "GameRandom.hpp"
#include "OverlayCounter.hpp"
#include <cstring>
namespace th20 {
extern GameRandom script_random;
Item::Item():link(this),free_list(nullptr),speed(0),angle(0),state(0),type(0),draw_state(0),attraction_speed(0),delay(0),generation(0),extra(0),sound(0),view_index(0),context(nullptr) {}
Item::~Item() {}
ItemInf::ItemInf() noexcept:field_10(0),second_draw_node(nullptr),speed_scale(0),processed(0),spawn_counter(0),point_counter(0),special_count(0),generation(0),bonus_counter(0),field_49c87c(0),field_49c880(0),attract(0),view_index(0),context(nullptr) {
    ecl_diagnostic_hint("initialize ItemInf\n");
}
ItemInf::~ItemInf() {
    ecl_diagnostic_hint("shutdown ItemInf\n");
    process_chain->remove(update_node);process_chain->remove(draw_node);process_chain->remove(second_draw_node);
}
void Item::select_context(std::int32_t index) {view_index=index;context=&session.context(view_index);}
void ItemInf::select_context(std::int32_t index) {view_index=index;context=&session.context(view_index);}
void ItemInf::enable() {
    if(update_node)update_node->enable();
    if(draw_node)draw_node->enable();
    if(second_draw_node)second_draw_node->enable();
}
void ItemInf::initialize_pool() {
    spawn_counter=0;point_counter=0;generation=0;
    auto bytes=pool.size()*sizeof(Item);
    auto* values=pool.data();
    std::memset(static_cast<void*>(values),0,bytes);
    auto& active_list=active;active_list.reset(nullptr);
    auto& ordinary_list=ordinary_free;ordinary_list.reset(nullptr);
    for(std::int32_t i=0;i<512;++i) {
        pool[i].link.initialize(&pool[i]);
        pool[i].free_list=&ordinary_free;
        auto& list=ordinary_free;list.append(&pool[i].link);
    }
    auto& special_list=special_free;special_list.reset(nullptr);
    for(std::int32_t i=0;i<1024;++i) {
        pool[i+512].link.initialize(&pool[i+512]);
        pool[i+512].free_list=&special_free;
        auto& list=special_free;list.append(&pool[i+512].link);
    }
    speed_scale=1;field_49c880=0;field_49c87c=100;bonus_counter=0;
}
std::int32_t ItemInf::initialize(std::int32_t index) {
    auto& selected=session.context(index);selected.set_item_controller(this);
    select_context(index);
    update_node=register_update_disabled(39,update_callback,this);
    draw_node=register_draw_disabled(35,draw_callback,this);
    second_draw_node=register_draw_disabled(19,second_draw_callback,this);
    initialize_pool();return 0;
}
ItemInf* Context::item_controller() {return object_0c;}
void Context::set_item_controller(ItemInf* owner) {object_0c=owner;}
ItemInf* item_controller(std::int32_t index) {return session.context(index).item_controller();}
float GameRandom::signed_range(float limit) {return signed_unit()*limit;}
void ItemInf::spawn_many(const Vector3* position,std::int32_t count,std::int32_t type) {
    while(count>0) {
        spawn(type,position,0xffffffffu,script_random.signed_range(3.1415927410125732f/180.0f*10.0f)-3.1415927410125732f/2.0f,2.0f,0,0,-1);
        --count;
    }
}
void OverlayCounter::add_reward(const Vector3* position,std::int32_t amount,std::int32_t type) {
    current=static_cast<std::int32_t>(static_cast<std::uint32_t>(current)+static_cast<std::uint32_t>(amount));
    while(current>threshold) {
        auto* owner=item_controller(0);owner->spawn_many(position,1,type);
        current=static_cast<std::int32_t>(static_cast<std::uint32_t>(current)-static_cast<std::uint32_t>(threshold));
    }
}
}
