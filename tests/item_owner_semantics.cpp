#include "Item.hpp"
#include "Session.hpp"
#include "GameRandom.hpp"
#include "OverlayCounter.hpp"
#include "DiagnosticObjectFactories.hpp"
#include "FunctionChainController.hpp"
#include "WeaponStoneInfo.hpp"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <vector>

namespace {
struct SpawnObservation {
    th20::ItemInf* owner;
    const th20::Vector3* position;
    std::int32_t type,delay,sound;
    std::uint32_t color,extra;
    float angle,speed;
};
std::vector<SpawnObservation> spawns;
std::vector<void*> owned_geometry;
unsigned geometry_releases,animation_releases;
}
extern "C" void __real_free(void*);
extern "C" void __wrap_free(void* memory) {
    for(auto& owned:owned_geometry) if(owned && owned==memory) {
        owned=nullptr;++geometry_releases;break;
    }
    __real_free(memory);
}
namespace th20 {
// Explicit process-startup and unresolved gameplay boundaries. All Item,
// Animation, allocator, RNG, Session and scheduler bodies under test are real.
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
FunctionChainController* process_chain;
GameRandom script_random(0);
DiagnosticAllocator::DiagnosticAllocator():state_word_(0),resource_() {}
WeaponStoneInfo::~WeaponStoneInfo() {std::abort();}
void WeaponStoneInfo::enable() {std::abort();}
void DiagnosticAllocator::release_animation_callback(AnimationCallback* callback) {
    assert(!callback);++animation_releases;
}
const Matrix4 identity_matrix=[] {
    Matrix4 result;for(int i=0;i<4;++i)result.elements[i][i]=1;return result;
}();
std::int32_t ItemInf::update_callback(void*) {std::abort();}
std::int32_t ItemInf::draw_callback(void*) {std::abort();}
std::int32_t ItemInf::second_draw_callback(void*) {std::abort();}
Item* ItemInf::spawn(std::int32_t type,const Vector3& position,std::uint32_t color,
                    float angle,float speed,std::int32_t delay,std::uint32_t extra,
                    std::int32_t sound) {
    spawns.push_back({this,&position,type,delay,sound,color,extra,angle,speed});
    // The caller discards the genuine dependency's return, including null.
    return spawns.size()%2?nullptr:&pool[0];
}
}
namespace {
using namespace th20;
void pool_partition(ItemInf& owner) {
    assert(!owner.active.next && owner.active.tail==&owner.active);
    for(int group=0;group<2;++group) {
        auto& list=group?owner.special_free:owner.ordinary_free;
        const int first=group?512:0,count=group?1024:512;
        auto* previous=static_cast<IntrusiveLink<Item>*>(&list);
        auto* link=list.next;
        for(int index=first;index<first+count;++index) {
            auto& item=owner.pool[index];assert(link==&item.link);
            assert(link->node==&item && link->owner==&list && link->previous==previous);
            assert(!link->iterator && item.free_list==&list);
            assert(!item.context && !item.state && !item.type && !item.attachment.value);
            // Native byte initialization clears the complete resource-free slot.
            const auto* bytes=reinterpret_cast<const unsigned char*>(&item.animation);
            for(std::size_t n=0;n<sizeof(Animation);++n)assert(bytes[n]==0);
            bytes=reinterpret_cast<const unsigned char*>(&item.secondary_animation);
            for(std::size_t n=0;n<sizeof(Animation);++n)assert(bytes[n]==0);
            previous=link;link=link->next;
        }
        assert(!link && list.tail==previous);
    }
}
void direct_item() {
    Item item;
    assert(item.link.node==&item && !item.link.owner && !item.free_list);
    assert(item.animation.link_4ec.node==&item.animation);
    assert(item.secondary_animation.link_4ec.node==&item.secondary_animation);
    assert(!item.speed && !item.angle && !item.state && !item.context);
    item.select_context(1);assert(item.context==&session.context(1) && item.view_index==1);
}
void initialize_and_lifetime() {
    auto* owner=new ItemInf;
    assert(owner->flags==2 && !owner->update_node && !owner->draw_node && !owner->second_draw_node);
    for(auto& item:owner->pool) {
        assert(item.link.node==&item && !item.link.next && !item.link.previous);
        assert(item.animation.link_4ec.node==&item.animation);
        assert(item.secondary_animation.link_4ec.node==&item.secondary_animation);
    }
    owner->processed=13;owner->special_count=17;owner->attract=1;
    owner->attraction_center={2,3,4};owner->select_context(1);
    owner->spawn_counter=9;owner->point_counter=8;owner->generation=7;
    owner->bonus_counter=6;owner->speed_scale=5;owner->field_49c880=4;owner->field_49c87c=3;
    owner->pool[500].state=23;owner->pool[1000].position={7,8,9};
    owner->initialize_pool();pool_partition(*owner);
    assert(!owner->spawn_counter && !owner->point_counter && !owner->generation && !owner->bonus_counter);
    assert(owner->speed_scale==1 && !owner->field_49c880 && owner->field_49c87c==100);
    assert(owner->processed==13 && owner->special_count==17 && owner->attract==1);
    assert(owner->attraction_center.z==4 && owner->context==&session.context(1) && owner->view_index==1);
    assert(owner->initialize(1)==0 && item_controller(1)==owner);pool_partition(*owner);
    assert(owner->update_node->priority==39 && owner->draw_node->priority==35 && owner->second_draw_node->priority==19);
    for(auto* node:{owner->update_node,owner->draw_node,owner->second_draw_node})
        assert(node->flags.bits==1 && node->userdata==owner);
    assert(owner->update_node->callback==ItemInf::update_callback);
    assert(owner->draw_node->callback==ItemInf::draw_callback);
    assert(owner->second_draw_node->callback==ItemInf::second_draw_callback);
    assert(process_chain->update()==1 && process_chain->draw()==2);
    owner->enable();
    for(auto* node:{owner->update_node,owner->draw_node,owner->second_draw_node})assert(node->flags.bits==3);
    owner->disable();
    assert(owner->update_node->flags.bits==1 && owner->draw_node->flags.bits==1);
    assert(owner->second_draw_node->flags.bits==3);owner->second_draw_node->disable();
    // Allocate geometry only after byte initialization, then release it through
    // all 3,072 genuine Animation destructors. Never clear a resource owner.
    for(auto& item:owner->pool) for(auto* animation:{&item.animation,&item.secondary_animation}) {
        animation->geometry=process_allocator->allocate_bytes(8,"Item semantic geometry");
        assert(animation->geometry);owned_geometry.push_back(animation->geometry);
        animation->geometry_bytes=8;animation->handle.value=123;
    }
    const auto before=animation_releases;
    process_allocator->release_object(owner);
    assert(animation_releases-before==3072 && geometry_releases==3072);
    for(auto* memory:owned_geometry)assert(!memory);
    // Original destruction does not clear publication. Avoid dereferencing the
    // stale published value and explicitly close the fixture's context slot.
    session.context(1).set_item_controller(nullptr);
    assert(!process_chain->update_chain.next && !process_chain->draw_chain.next);
    assert(process_chain->update_chain.tail==&process_chain->update_chain);
    assert(process_chain->draw_chain.tail==&process_chain->draw_chain);
}
void rewards_and_random() {
    auto* zero=new ItemInf;auto* one=new ItemInf;
    session.context(0).set_item_controller(zero);session.context(1).set_item_controller(one);
    Vector3 position(2,3,4);script_random.seed(991);
    auto expected=script_random;auto initial=script_random.last;
    zero->spawn_many(&position,0,7);zero->spawn_many(&position,-9,7);
    assert(spawns.empty() && script_random.last==initial);
    zero->spawn_many(&position,3,7);assert(spawns.size()==3);
    for(const auto& call:spawns) {
        const float angle=expected.signed_range(3.1415927410125732f/180.f*10.f)-3.1415927410125732f/2.f;
        assert(call.owner==zero && call.position==&position && call.type==7);
        assert(call.angle==angle && call.speed==2 && call.color==0xffffffffu);
        assert(!call.delay && !call.extra && call.sound==-1);
    }
    assert(script_random.next()==expected.next());spawns.clear();
    OverlayCounter counter;assert(counter.threshold==1500 && counter.current==0);
    counter.add_reward(nullptr,1500,3);assert(spawns.empty() && counter.current==1500);
    counter.add_reward(&position,1,3);assert(spawns.size()==1 && counter.current==1);
    assert(spawns.back().owner==zero && spawns.back().position==&position && spawns.back().type==3);
    spawns.clear();counter.current=0;counter.add_reward(&position,4500,4);
    assert(spawns.size()==2 && counter.current==1500);
    for(const auto& call:spawns)assert(call.owner==zero && call.type==4);
    spawns.clear();counter.current=std::numeric_limits<std::int32_t>::max();
    counter.add_reward(nullptr,1,5);assert(counter.current==std::numeric_limits<std::int32_t>::min() && spawns.empty());
    counter.current=10;counter.add_reward(nullptr,-20,5);assert(counter.current==-10 && spawns.empty());
    expected=script_random;assert(script_random.signed_range(-2.f)==expected.signed_unit()*-2.f);
    assert(script_random.next()==expected.next());
    process_allocator->release_object(zero);process_allocator->release_object(one);
    session.context(0).set_item_controller(nullptr);session.context(1).set_item_controller(nullptr);
}
}
int main() {
    using namespace th20;
    DiagnosticAllocator allocator;process_allocator=&allocator;
    FunctionChainController scheduler;process_chain=&scheduler;process_locks.enable();
    direct_item();initialize_and_lifetime();rewards_and_random();
    process_locks.disable();process_chain=nullptr;process_allocator=nullptr;
    std::puts("Actual Item owner passed: complete1536-slot construction,512/1024 pool partition, Context publication, disabled39/35/19 registration, enable3/disable2,3072 owned geometry releases, strict reward threshold/mod32 and scaled RNG/bulk-spawn calls. Original frame callbacks and primary spawn remain explicit fixtures.");
}
