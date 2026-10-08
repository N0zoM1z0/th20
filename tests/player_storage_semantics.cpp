#include "PlayerStorage.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <memory>
#include <type_traits>

namespace {
using namespace th20;
void zero(const Vector3& v) { assert(v.x==0 && v.y==0 && v.z==0); }
void zero(const IntPoint& v) { assert(v.x==0 && v.y==0); }
void zero(const Timer& t) {
    assert(t.previous==0 && t.current==0 && t.current_fraction==0 && t.flags==0);
}
template<class T> void detached(const IntrusiveLink<T>& link) {
    assert(!link.node && !link.next && !link.previous && !link.owner && !link.iterator);
}
void defaults(const PlayerOption& v) {
    assert(v.state==0); zero(v.position); zero(v.previous_position);
    for (const auto& x:v.vectors_1c) zero(x);
    zero(v.fixed_position); zero(v.previous_fixed_position);
    for (const auto& x:v.offsets) zero(x);
    zero(v.point_b8); zero(v.point_c0); zero(v.vector_c8);
    assert(v.identifier_d4.value==0 && v.field_d8==0);
    assert(v.handle_dc.value==0 && v.handle_e0.value==0); zero(v.timer_e4);
    assert(v.field_f4==0 && v.field_f8==0 && v.field_fc==0);
    assert(v.state_100.flags==0 && v.state_100.focused==0);
    assert(v.field_108==0 && v.field_10c==0 && v.field_110==0);
    assert(v.handle_114.value==0 && v.field_118==0 && v.field_11c==0 && v.field_120==0);
    assert(v.player_index==0 && !v.context);
}
void defaults(const PlayerFeedback& v) {
    zero(v.timer_00); zero(v.timer_10); zero(v.timer_20); zero(v.vector_40);
    assert(v.field_30==0 && v.field_34==0 && v.field_38==0 && v.field_3c==0);
    assert(v.handle_4c.value==0 && v.enabled==0 && v.player_index==0 && !v.context);
}
void defaults(const PlayerCollisionBounds& v) {
    assert(v.normal_radius==0 && v.focus_radius==0);
    zero(v.normal_extent); zero(v.focus_extent);
}
void defaults(const PlayerMotionParameters& v) {
    assert(v.field_00==0 && v.field_04==0 && v.field_08==0 && v.field_0c==0 && v.field_10==0);
}
void defaults(const PlayerShot& v) {
    detached(v.link); assert(v.state_14==0 && v.handle_18.value==0);
    zero(v.timer_1c); zero(v.timer_2c);
    assert(v.flags_3c.bits==0 && v.field_40==0 && v.field_44==0 && v.field_48==0 && v.field_4c==0);
    // Native Motion has no padding and its constructor initializes every lane.
    std::array<unsigned char,sizeof(Motion)> bytes{};
    assert(std::memcmp(bytes.data(),&v.motion,sizeof(Motion))==0);
    assert(v.identifier_98.value==0 && v.field_9c==0 && v.handle_a0.value==0);
    assert(v.field_a4==1 && v.field_a8==0 && v.field_ac==0);
    assert(v.extent.x==0 && v.extent.y==0);
    for (auto x:v.words_b8) assert(x==0);
    for (auto x:v.words_e0) assert(x==0);
    assert(v.record_index==0 && v.damage.value==0); zero(v.vector_100);
    assert(v.field_10c==0 && v.field_110==0 && v.byte_114==0);
    assert(v.player_index==0 && !v.owner && !v.context);
}
void defaults(const PlayerShotPool& v) {
    static_assert(std::extent_v<decltype(PlayerShotPool::slots)> == 256);
    for (const auto& slot:v.slots) defaults(slot);
}
void defaults(const PlayerShotController& v) {
    defaults(v.pool); zero(v.timer_12400); zero(v.timer_12410); zero(v.timer_12420);
    detached<PlayerShot>(v.active); detached<PlayerShot>(v.free);
    assert(v.active.tail==&v.active && v.free.tail==&v.free);
    assert(v.field_12460==0 && v.field_12464==0);
    for (auto x:v.counters_12468) assert(x==0);
    for (auto x:v.counters_124e0) assert(x==0);
    assert(v.field_12558==0 && v.flags_1255c.bits==0 && v.identifier_12560.value==0);
    assert(v.field_12564==0 && v.field_12578==0 && v.byte_1257c==0);
    zero(v.timer_12568); zero(v.timer_12580);
    assert(v.player_index==0 && !v.context);
}
template<class T> void guarded() {
    constexpr std::size_t guard=16;
    alignas(T) std::array<unsigned char,sizeof(T)+2*guard> storage;
    storage.fill(0xa5);
    auto* value=std::construct_at(reinterpret_cast<T*>(storage.data()+guard));
    defaults(*value);
    std::destroy_at(value);
    auto untouched=[](auto begin,auto end) {
        assert(std::all_of(begin,end,[](auto x){return x==0xa5;}));
    };
    untouched(storage.begin(),storage.begin()+guard);
    untouched(storage.end()-guard,storage.end());
}
}

int main() {
    guarded<PlayerOption>(); guarded<PlayerFeedback>();
    guarded<PlayerCollisionBounds>(); guarded<PlayerMotionParameters>();
    guarded<PlayerShot>(); guarded<PlayerShotPool>(); guarded<PlayerShotController>();
    // Exercise the actual pool/list relationship: all 256 detached objects can
    // be linked, transferred and removed without touching neighboring storage.
    PlayerShotController controller;
    for (auto& shot:controller.pool.slots) controller.free.append(&shot.link);
    assert(controller.free.tail==&controller.pool.slots[255].link);
    assert(controller.free.next==&controller.pool.slots[0].link);
    for (auto& shot:controller.pool.slots) {
        assert(shot.link.owner==&controller.free);
        controller.free.remove(&shot.link);
        detached(shot.link);
        controller.active.append(&shot.link);
        assert(shot.link.owner==&controller.active);
    }
    assert(!controller.free.next && controller.free.tail==&controller.free);
    for (auto& shot:controller.pool.slots) {
        controller.active.remove(&shot.link);
        defaults(shot);
    }
    defaults(controller);
    for (auto word:{0u,1u,0x80000000u,0xffffffffu}) {
        DamageHandle handle(word); assert(handle.value==word);
    }
}
