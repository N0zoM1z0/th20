#include "Item.hpp"
#include "Session.hpp"
#include "Bullet.hpp"
#include "Weapon.hpp"
#include "WeaponStoneInfo.hpp"
#include "GameRandom.hpp"
#include "MotionMath.hpp"
#include <type_traits>
namespace th20 {
extern GameRandom script_random;
// Native immutable primary/secondary script selections, including -1.
extern const std::int32_t item_scripts[16][2]={
    {-1,-1},{115,137},{116,138},{117,139},{118,140},{119,141},{120,142},{121,143},
    {122,144},{123,-1},{124,-1},{125,-1},{126,-1},{127,-1},{128,-1},{-1,-1}
};
static_assert(std::is_standard_layout_v<Item>);
static_assert(offsetof(Item,link)==0);
Item* ItemInf::spawn(std::int32_t type,const Vector3& position,std::uint32_t color,float angle,float speed,
                    std::int32_t delay,std::uint32_t extra,std::int32_t sound) {
    if(type==1&&player_record(0)->field_a5_value()) {
        bonus_counter=static_cast<std::int32_t>(static_cast<std::uint32_t>(bonus_counter)+1u);
        std::int32_t interval=10;
        if(player_record(0)->field_2f_value())interval=14;
        if(bonus_counter%interval==interval-1) {
            {auto* weapon=weapon_stone_info(0)->passive_weapon();weapon->set_passive(1);}
            auto y=script_random.signed_unit()*16.0f+position.y;
            auto x=script_random.signed_unit()*16.0f+position.x;
            spawn(type,Vector3(x,y,0),color,angle,speed,
                  static_cast<std::int32_t>(static_cast<std::uint32_t>(delay)+16u),extra,sound);
        }
    }
    if(type>=16)return nullptr;
    spawn_counter=static_cast<std::int32_t>(static_cast<std::uint32_t>(spawn_counter)+1u);
    if(type==9||type==10||type==11||type==12||type==13) {
        // Actual special nodes point to the first member of standard-layout Item.
        auto* item=reinterpret_cast<Item*>(special_free.front());
        if(item) {
            item->generation=generation;
            item->link.detach();
            auto& list=active;list.prepend(&item->link);
            if(special_count>=1024)item->delay=spawn_counter%32+16;
            else if(special_count>=512)item->delay=spawn_counter%16+8;
            else if(special_count>=256)item->delay=spawn_counter%8+4;
            else item->delay=spawn_counter%4;
            item->state=5;item->type=type;item->draw_state=0;
            item->position=position;item->position.z=0;
            polar(item->velocity,angle,speed);item->velocity.z=0;
            item->timer=0;item->angle=angle;item->speed=speed;item->extra=extra;item->sound=sound;
            item->select_context(view_index);
        }
        return item;
    } else {
        if(type==15) {
            auto addition=static_cast<std::int32_t>(static_cast<std::uint32_t>(player_table().mode())+1u);
            auto previous=point_counter;
            point_counter=static_cast<std::int32_t>(static_cast<std::uint32_t>(previous)+static_cast<std::uint32_t>(addition));
            if(point_counter<10)return nullptr;
            point_counter=0;type=2;
        }
        // The original requires an available ordinary head, even before testing
        // its stored Item pointer. Do not insert a fabricated empty-list guard.
        auto* item=ordinary_free.front()->node_value();
        if(item) {
            item->link.detach();auto& list=active;list.prepend(&item->link);
            item->state=1;item->position=position;item->position.z=0;
            if(item->position.x<=-192.0f)item->position.x=-192.0f;
            else if(item->position.x>=192.0f)item->position.x=192.0f;
            if(type==14)type=6;
            polar(item->velocity,angle,speed);item->velocity.z=0;item->timer=0;
            item->speed=0;item->attraction_speed=0;item->delay=delay;item->type=type;item->sound=sound;
            item->select_context(view_index);if(delay==0)item->spawn_effect();item->draw_state=0;
            {
                auto* file=context->bullet_controller()->file;
                auto script=item_scripts[type][0];file->bind_animation(&item->animation,script);
                auto* second_file=context->bullet_controller()->file;
                auto second_script=item_scripts[type][1];second_file->bind_animation(&item->secondary_animation,second_script);
                item->attachment=0;
                auto& animation=item->animation;animation.set_packed_color(color);
            }
            item->extra=extra;
        }
        return item;
    }
}
}
