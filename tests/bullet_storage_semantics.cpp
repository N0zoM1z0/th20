#include "Bullet.hpp"
#include "Session.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <limits>
#include <memory>
#include <vector>

namespace th20 {
// Explicit fixtures for the two still-open controller operations. Member
// destruction remains real BulletPool/Bullet/shared_ptr destruction.
BulletController::~BulletController() = default;
void BulletController::enable() {TaskInfo::enable_callbacks();}
}
namespace {
using namespace th20;
void zero(const Vector3& v) {assert(v.x==0 && v.y==0 && v.z==0);}
void zero(const Vector2& v) {assert(v.x==0 && v.y==0);}
void zero(const Timer& v) {
    assert(v.previous==0 && v.current==0 && v.current_fraction==0 && v.flags==0);
}
template<class T> void zero(const Interpolation<T>& v) {
    if constexpr (std::is_same_v<T,float>) {
        assert(v.start==0 && v.end==0 && v.tangent_start==0 && v.tangent_end==0 && v.current==0);
    } else {zero(v.start);zero(v.end);zero(v.tangent_start);zero(v.tangent_end);zero(v.current);}
    zero(v.timer);assert(v.duration==0 && v.mode==0);
}
void untouched(const unsigned char* first,const unsigned char* last) {
    assert(std::all_of(first,last,[](unsigned char c){return c==0xa5;}));
}
void defaults(const Bullet& b) {
    assert(b.link.node==&b && !b.link.next && !b.link.previous && !b.link.owner && !b.link.iterator);
    assert(b.flags.bits==0 && b.field_18==0 && !b.animation && b.speed==0 && b.field_24==0);
    assert(b.index==0 && b.field_2c==0 && b.command_index==0 && b.cancel_script==0);
    assert(b.field_38==0 && b.field_3c==0 && b.field_40==0 && b.draw_group==0 && b.scale==0);
    assert(b.field_4c==0 && b.field_4e==0 && b.state==0 && b.field_54==0 && !b.style);
    assert(b.animation_handle.value==0 && !b.draw_next && b.angle.value==0 && b.color.value==0);
    zero(b.position);zero(b.velocity);zero(b.size);
    assert(b.command_flags.bits==0 && !b.metadata && b.metadata.use_count()==0);
    for(const auto& c:b.commands.slots) {
        zero(c.timer);zero(c.vector_18);zero(c.vector_24);
        assert(c.scalar_10==0 && c.scalar_14==0 && c.word_30==0 && c.word_34==0 && c.word_38==0 && c.word_3c==0);
    }
    zero(b.interpolation_420);zero(b.interpolation_474);
    zero(b.timer_4a0);zero(b.timer_4b0);zero(b.timer_4c0);
    zero(b.timer_4d8);zero(b.timer_4e8);zero(b.timer_4f8);zero(b.timer_508);
    assert(b.field_4d0==0 && b.field_4d4==0 && b.field_518==0 && b.view_index==0 && !b.context);
    untouched(reinterpret_cast<const unsigned char*>(&b.color)+sizeof(b.color),
              reinterpret_cast<const unsigned char*>(&b.command_flags));
    untouched(reinterpret_cast<const unsigned char*>(&b.context)+sizeof(b.context),
              reinterpret_cast<const unsigned char*>(&b)+sizeof(b));
}
std::vector<unsigned char> snapshot(const BulletController& value) {
    const auto* p=reinterpret_cast<const unsigned char*>(&value);
    return {p,p+sizeof(value)};
}
void same_except_metadata(const BulletController& value,const std::vector<unsigned char>& before) {
    const auto* p=reinterpret_cast<const unsigned char*>(&value);
    std::size_t offset=0;
    for(const auto& b:value.pool.slots) {
        const auto* metadata=reinterpret_cast<const unsigned char*>(&b.metadata);
        const auto next=static_cast<std::size_t>(metadata-p);
        assert(std::equal(p+offset,p+next,before.data()+offset));
        offset=next+sizeof(b.metadata);
    }
    assert(std::equal(p+offset,p+sizeof(value),before.data()+offset));
}
}
int main() {
    using namespace th20;
    constexpr std::size_t guard=16;
    struct alignas(BulletController) Guarded {
        std::array<unsigned char,sizeof(BulletController)+2*guard> bytes;
    };
    auto storage=std::make_unique<Guarded>();storage->bytes.fill(0xa5);
    auto* owner=std::construct_at(reinterpret_cast<BulletController*>(storage->bytes.data()+guard));
    assert(owner->flags==2 && !owner->update_node && !owner->draw_node && !owner->next_bullet);
    for(auto* head:owner->draw_heads) assert(!head);
    for(auto* tail:owner->draw_tails) assert(!tail);
    assert(owner->bullet_count==0 && owner->field_48==0);
    zero(owner->vector_4c);zero(owner->vector_54);
    assert(owner->age==0 && owner->item_counter==0 && owner->field_286d84==0 && owner->cancel_counter==0);
    assert(!owner->file && owner->field_286d90==0 && owner->field_286d94==0 && owner->field_286d98==0);
    assert(owner->view_index==0 && !owner->context);
    assert(owner->pool.begin()==&owner->pool.slots[0] && owner->pool.end()==&owner->pool.slots[2001]);
    for(const auto& b:owner->pool) defaults(b);
    for(const auto& h:owner->handles.slots) assert(h.value==0);
    for(const auto* list:{&owner->free,&owner->active}) {
        assert(!list->node && !list->next && !list->previous && !list->owner && !list->iterator && list->tail==list);
    }
    // Two actual Context objects publish the same borrowed owner independently.
    for(int index:{0,1}) {
        auto& context=session.context(index);
        assert(!context.bullet_controller());
        context.set_bullet_controller(owner);
        auto before=snapshot(*owner);
        owner->select_context(index);
        assert(owner->view_index==index && owner->context==&context && bullet_controller(index)==owner);
        const auto* p=reinterpret_cast<const unsigned char*>(owner);
        auto replace=[&](const auto& field) {
            const auto* begin=reinterpret_cast<const unsigned char*>(&field);
            std::memcpy(before.data()+(begin-p),begin,sizeof(field));
        };
        replace(owner->view_index);replace(owner->context);
        assert(snapshot(*owner)==before);
    }
    for(auto count:{std::numeric_limits<std::int32_t>::min(),-1,0,1,2000,2001,
                    std::numeric_limits<std::int32_t>::max()}) {
        owner->bullet_count=count;auto before=snapshot(*owner);
        assert(owner->count()==count && snapshot(*owner)==before);
    }
    // Resource release covers the entire typed pool, including the final slot.
    auto shared=std::make_shared<ShotMetadata>();auto distinct=std::make_shared<ShotMetadata>();
    assert(shared->commands.size()==2 && distinct->commands.size()==2);
    std::weak_ptr<ShotMetadata> shared_weak=shared,distinct_weak=distinct;
    for(auto index:{0,1000,2000}) owner->pool.slots[index].metadata=shared;
    owner->pool.slots[1001].metadata=distinct;
    shared.reset();distinct.reset();
    assert(shared_weak.use_count()==3 && distinct_weak.use_count()==1);
    FunctionChainNode update,draw;
    update.flags.bits=0xa5a5a5a7u;draw.flags.bits=0x5a5a5a5au;
    owner->update_node=&update;owner->draw_node=&draw;
    auto before=snapshot(*owner);owner->disable();
    assert(shared_weak.expired() && distinct_weak.expired());
    for(const auto& b:owner->pool) assert(!b.metadata && b.metadata.use_count()==0);
    same_except_metadata(*owner,before);
    assert(update.flags.bits==0xa5a5a5a5u && draw.flags.bits==0x5a5a5a58u);
    owner->update_node=nullptr;before=snapshot(*owner);owner->disable();
    same_except_metadata(*owner,before);
    owner->draw_node=nullptr;before=snapshot(*owner);owner->disable();
    same_except_metadata(*owner,before);
    // Real pool destruction releases a resource acquired after disable.
    shared=std::make_shared<ShotMetadata>();shared_weak=shared;
    owner->pool.slots[2000].metadata=shared;shared.reset();
    session.context(0).set_bullet_controller(nullptr);
    session.context(1).set_bullet_controller(nullptr);
    std::destroy_at(owner);assert(shared_weak.expired());
    untouched(storage->bytes.data(),storage->bytes.data()+guard);
    untouched(storage->bytes.data()+guard+sizeof(BulletController),storage->bytes.data()+storage->bytes.size());
}
