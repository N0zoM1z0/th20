#include "Item.hpp"
#include "ItemResourceOwners.hpp"
#include "Session.hpp"
#include "GameRandom.hpp"
#include "SoundInf.hpp"
#include "DiagnosticAllocator.hpp"
#include "FunctionChainController.hpp"
#include "WeaponStoneInfo.hpp"
#include <array>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <memory>
#include <vector>

namespace {
struct Event { int kind,argument; th20::AnimationFile* file; };
std::vector<Event> events;
th20::Item* current_item;
bool mutate_effect,mutate_binding;
unsigned releases;
unsigned cases;
}
namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
FunctionChainController* process_chain;
GameRandom script_random(0);
SoundInf process_sound;
StoneMenuInfo* process_stone_menu;
DiagnosticAllocator::DiagnosticAllocator():state_word_(0),resource_() {}
void DiagnosticAllocator::release_animation_callback(AnimationCallback* callback) {
    assert(!callback);++releases;
}
const Matrix4 identity_matrix=[] {
    Matrix4 result;for(int i=0;i<4;++i)result.elements[i][i]=1;return result;
}();
// Explicit synthetic startup/lifetime boundaries for owners whose original
// resource loading/virtual retirement is undefined. Actual member values,
// containers, Worker and TaskInfo construction/destruction still execute.
SoundInf::SoundInf() noexcept=default;
SoundInf::~SoundInf()=default;
// This unresolved Overlay lifetime/enable is uncalled; it supplies UBSan RTTI.
WeaponStoneInfo::~WeaponStoneInfo() {std::abort();}
void WeaponStoneInfo::enable() {std::abort();}
EffectInfo::EffectInfo():files{},ready(0),view_index(0),context(nullptr) {}
EffectInfo::~EffectInfo() {
    for(auto* file:files)assert(!file);
    for(auto& request:requests)assert(!request.animation);
    assert(!update_node && !draw_node);
}
StoneMenuInfo::StoneMenuInfo():file(nullptr),visible(0),saved_selection(0),
    names{},descriptions{},state(0),field_210f8(0),view_index(0),context(nullptr) {}
StoneMenuInfo::~StoneMenuInfo() {assert(!file && !update_node && !draw_node);}
AnimationFile::~AnimationFile() {
    assert(!bytes && !templates && !sprites && !scripts && !textures);
}
AnimationHandle AnimationFile::spawn(const char* stem,int script,const Vector3& position,
                                   float rotation,int layer,Animation** output) {
    assert(std::strcmp(stem,"effect")==0 && script==94);
    assert(&position==&current_item->position && rotation==0 && layer==-1 && !output);
    events.push_back({1,script,this});
    if(mutate_effect)current_item->type=6;
    AnimationHandle result;result=0x12345678u;return result;
}
void AnimationFile::bind_animation(Animation* animation,int script,Animation* parent) {
    assert(!parent && animation==&current_item->animation && current_item->state==2);
    events.push_back({2,script,this});
    if(mutate_binding)current_item->position={31,47,59};
}
void SoundInf::request_effect(int id,int pan) {
    assert(this==&process_sound && !pan);events.push_back({3,id,nullptr});
}
void AnimationHandle::retire() {
    assert(this==&current_item->attachment && current_item->state==0);
    assert(current_item->link.owner);
    events.push_back({4,static_cast<int>(value),nullptr});value=0;
}
}

namespace {
std::uint32_t next_seed(std::uint32_t& value) {
    value=static_cast<std::uint32_t>((std::uint64_t(value)*48271)%2147483647);
    return value;
}
void activation(th20::AnimationFile& file) {
    using namespace th20;
    session.context(0).current_player=&session.table.players[0];
    session.context(1).current_player=&session.table.players[1];
    const std::array<std::array<int,4>,3> selections{{
        {{0,2,4,6}},{{INT_MIN,-3,INT_MAX,-1}},{{1,3,5,7}}
    }};
    for(auto selection:selections) {
        auto& record=session.table.players[0];
        record.field_0c=selection[0];record.field_14=selection[1];
        record.field_10=selection[2];record.field_18=selection[3];
        for(int index:std::array<int,8>{{INT_MIN,-1,0,1,2,3,4,INT_MAX}}) {
            assert(record.starting_configuration(index)==selection[index>=0 && index<4?index:0]);
        }
        for(unsigned seed=1;seed<=192;++seed) {
            Item item;current_item=&item;item.type=13;item.state=5;
            item.select_context(1);item.position={1,2,3};
            item.animation.vector_5bc={7,8,9};
            item.secondary_animation.base.field_28=17;
            item.secondary_animation.base.flags.bytes_00.field_01=0xa5;
            item.secondary_animation.base.flags.bit_10=1;
            item.secondary_animation.base.flags.other_02=0x55;
            script_random.seed(seed);events.clear();
            auto independent=seed;auto first=next_seed(independent);
            auto second=next_seed(independent);int expected;
            if(first%8<=4)expected=selection[second%4]/2+9;
            else expected=static_cast<int>(second%4)+9;
            assert(item.activate()==0 && item.type==expected && item.state==2);
            assert(script_random.last==independent);
            assert(item.animation.vector_5bc.x==1 && item.animation.vector_5bc.y==2 && item.animation.vector_5bc.z==3);
            assert(item.secondary_animation.base.field_28==-1 && !item.secondary_animation.base.flags.bit_10);
            assert(item.secondary_animation.base.flags.other_02==0x55);
            assert(item.secondary_animation.base.flags.bytes_00.field_01==0xa5);
            if(expected>=9 && expected<=12) {
                assert(events.size()==1 && events[0].kind==2 && events[0].argument==expected+28 && events[0].file==&file);
            } else assert(events.empty());
            ++cases;
        }
    }
    for(int type:std::array<int,12>{{INT_MIN,-1,0,1,8,9,10,11,12,14,15,INT_MAX}}) {
        Item item;current_item=&item;item.type=type;item.position={-5,6,7};
        item.secondary_animation.base.flags.bit_10=1;
        script_random.seed(55);events.clear();
        assert(item.activate()==0 && item.type==type && script_random.last==55);
        assert(events.size()==static_cast<unsigned>(type>=9 && type<=12));
        ++cases;
    }
    Item item;current_item=&item;item.type=9;item.position={1,2,3};
    mutate_binding=true;events.clear();assert(item.activate()==0);mutate_binding=false;
    assert(item.animation.vector_5bc.x==31 && item.animation.vector_5bc.y==47 && item.animation.vector_5bc.z==59);
    ++cases;
}
void effects(th20::EffectInfo& owner,th20::AnimationFile& file) {
    using namespace th20;
    session.context(1).object_20=&owner;owner.files[0]=&file;
    for(int type=-1;type<=16;++type)for(int sound:std::array<int,3>{{-1,0,INT_MAX}}) {
        Item item;current_item=&item;item.select_context(1);item.type=type;item.sound=sound;
        item.attachment=0x55u;events.clear();
        assert(item.spawn_effect()==0 && item.attachment.value==0x55u);
        bool major=type==4 || type==5 || type==6 || type==7 || type==14;
        bool ordinary=type==1 || type==2;
        assert(events.size()==static_cast<unsigned>(major?2:ordinary?(sound>=0?2:1):0));
        if(major || ordinary) {
            assert(events[0].kind==1 && events[0].file==&file);
            if(events.size()==2)assert(events[1].kind==3 && events[1].argument==(major?(type==4 || type==5?74:48):sound));
        }
        ++cases;
    }
    Item item;current_item=&item;item.select_context(1);item.type=4;
    mutate_effect=true;events.clear();assert(item.spawn_effect()==0);mutate_effect=false;
    assert(item.type==6 && events.size()==2 && events[1].argument==48);++cases;
    owner.files[0]=nullptr;session.context(1).object_20=nullptr;
}
void owner_interfaces(th20::StoneMenuInfo& menu,th20::EffectInfo& effect) {
    using namespace th20;
    for(auto& entry:effect.handles)assert(entry.handle.value==0);
    for(unsigned mask=0;mask<4;++mask) {
        FunctionChainNode update,draw;
        update.flags.bits=draw.flags.bits=0xfffffffdu;
        menu.update_node=mask&1?&update:nullptr;
        menu.draw_node=mask&2?&draw:nullptr;
        TaskInfo& task=menu;task.enable();
        assert(update.flags.bits==(mask&1?0xffffffffu:0xfffffffdu));
        assert(draw.flags.bits==(mask&2?0xffffffffu:0xfffffffdu));
        ++cases;
    }
    menu.update_node=menu.draw_node=nullptr;
}
void retirement() {
    using namespace th20;
    Item first,middle,last;IntrusiveList<Item> active,available;
    for(auto* item:{&first,&middle,&last}) {
        item->free_list=&available;item->state=2;item->attachment=0x123u;
        active.append(&item->link);
    }
    {
        auto observer=active.begin();assert(observer.current==&first.link && observer.pending==&middle.link);
        current_item=&middle;events.clear();middle.retire();
        assert(observer.current==&first.link && observer.pending==&last.link);
        assert(active.tail==&last.link && available.front()==&middle.link);
        assert(!middle.attachment.value && middle.state==0 && middle.link.owner==&available);
        assert(events.size()==1 && events[0].kind==4 && events[0].argument==0x123);
        current_item=&first;first.retire();
        assert(!observer.current && observer.pending==&last.link);
        observer.advance();assert(observer.current==&last.link && !observer.pending);
        current_item=&last;last.retire();assert(!observer.current && !observer.pending);
    }
    assert(!active.front() && active.tail==&active);
    assert(available.front()==&last.link && last.link.next==&first.link && first.link.next==&middle.link);
    while(auto* link=available.front())link->detach();
    assert(available.tail==&available);cases+=3;
}
}
int main() {
    using namespace th20;
    DiagnosticAllocator allocator;process_allocator=&allocator;process_locks.enable();
    {
        AnimationFile file;auto effect=std::make_unique<EffectInfo>();
        auto menu=std::make_unique<StoneMenuInfo>();menu->file=&file;process_stone_menu=menu.get();
        owner_interfaces(*menu,*effect);activation(file);effects(*effect,file);retirement();
        menu->file=nullptr;process_stone_menu=nullptr;
    }
    assert(cases==651 && releases>0);
    process_locks.disable();process_allocator=nullptr;
    std::printf("%u whole Item cases passed: actual objects/RNG/record selection, effect ordering, animation state and observer-safe retirement; ANM/Sound/renderer and owner startup/retirement remain fixtures.\n",cases);
}
