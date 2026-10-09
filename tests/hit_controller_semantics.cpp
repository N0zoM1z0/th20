#include "HitCtrlInf.hpp"
#include "FunctionChainController.hpp"
#include "ClockScalar.hpp"
#include <cassert>
#include <cstdio>
#include <vector>

namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
FunctionChainController* process_chain;
// Only process object placement and allocator startup are fixture-owned.
DiagnosticAllocator::DiagnosticAllocator():state_word_(0),resource_() {}
}
namespace {
using namespace th20;
std::size_t count(const IntrusiveList<DamageRegion>& list) {
    std::size_t result=0;
    const auto* previous=static_cast<const IntrusiveLink<DamageRegion>*>(&list);
    for(auto* link=list.next;link;link=link->next) {
        assert(link->previous==previous && link->owner==&list && !link->iterator);
        assert(link->node && &link->node->link==link);
        previous=link;++result;assert(result<=512);
    }
    assert(list.tail==previous);return result;
}
void release(HitCtrlInf* owner,int index) {
    process_allocator->release_object(owner);
    // Native destruction leaves publication to the surrounding process owner.
    assert(session.context(index).hit_controller()==owner);
    session.context(index).set_hit_controller(nullptr);
}
void lifecycle(int index) {
    auto* owner=create_hit_controller(index);assert(owner);
    assert(hit_controller(index)==owner && owner->context==&session.context(index));
    assert(owner->view_index==index && owner->update_node && !owner->draw_node);
    assert(owner->update_node->priority==28 && owner->update_node->flags.bits==1);
    assert(owner->update_node->userdata==owner && owner->update_node->callback==HitCtrlInf::update_callback);
    assert(owner->flags==2 && owner->visited==0 && owner->age.current==0);
    assert(count(owner->free)==256 && count(owner->active)==0);
    assert(process_chain->update()==1 && owner->age.current==0);
    owner->enable();assert(owner->update_node->flags.bits==3);
    const Vector3 center(3,5,7);
    const auto first=owner->create_rectangle(center,4,6,0,1,11);
    const auto second=owner->create_circle(center,2,0.5f,3,13);
    assert(first.get()==((static_cast<unsigned>(index)<<16)|1u));
    assert(second.get()==2 && owner->next_handle==3);
    auto* rectangle=owner->find(first);auto* circle=owner->find(second);
    assert(rectangle==&owner->pool[0] && circle==&owner->pool[1]);
    assert(!owner->find(Identifier32(0)) && !owner->find(Identifier32(0xffff)));
    assert(rectangle->context==owner->context && circle->context==owner->context);
    assert(rectangle->value_bc==index && circle->value_bc==index);
    assert(rectangle->flags.fields.active && rectangle->flags.fields.kind==0);
    assert(circle->flags.fields.active && circle->flags.fields.kind==1);
    assert(rectangle->damage==11 && circle->damage==13);
    assert(count(owner->active)==2 && count(owner->free)==254);
    assert(process_chain->update()==1);
    assert(owner->visited==2 && owner->age.current==1);
    assert(rectangle->identifier.get()==0 && !rectangle->flags.fields.active);
    assert(!owner->find(first) && owner->find(second)==circle);
    assert(count(owner->active)==1 && count(owner->free)==255);
    const auto reused=owner->create_circle(center,1,0,10,17);
    assert(owner->find(reused)==rectangle && reused.get()==3);
    assert(count(owner->active)==2 && count(owner->free)==254);
    circle->retire();assert(!circle->identifier.get() && !circle->flags.fields.active);
    assert(count(owner->active)==1 && count(owner->free)==255);
    circle->retire();assert(count(owner->active)==1 && count(owner->free)==255);
    owner->disable();assert(process_chain->update()==1 && owner->age.current==1);
    owner->enable();owner->update();assert(owner->visited==1 && owner->age.current==2);
    owner->find(reused)->retire();assert(count(owner->active)==0 && count(owner->free)==256);
    owner->next_handle=0xffff;
    const auto last_generation=owner->create_circle(center,1,0,9,1);
    const auto wrapped_generation=owner->create_circle(center,1,0,9,1);
    assert(last_generation.get()==0xffff && wrapped_generation.get()==1 && owner->next_handle==2);
    assert(owner->find(last_generation) && owner->find(wrapped_generation));
    release(owner,index);
    assert(!process_chain->update_chain.next && process_chain->update_chain.tail==&process_chain->update_chain);
}
void overflow_and_observer_repair(int index) {
    auto* owner=create_hit_controller(index);assert(owner);
    const Vector3 center(0,0,0);
    std::vector<Identifier32> ids;
    for(unsigned i=0;i<261;++i) ids.push_back(owner->create_circle(center,2,0,1,1));
    assert(count(owner->free)==0 && count(owner->active)==261);
    for(unsigned i=0;i<ids.size();++i) {
        auto* region=owner->find(ids[i]);assert(region && region->context==owner->context);
        assert(region->is_heap()==(i>=256));
        if(i<256)assert(region==&owner->pool[i]);
    }
    // Every update retires its current link. Both pool and actual heap releases
    // must repair pending observations without reading freed region storage.
    owner->update();assert(owner->visited==261 && owner->age.current==1);
    assert(count(owner->active)==0 && count(owner->free)==256);
    for(auto id:ids)assert(!owner->find(id));
    // Leave mixed lifetimes live so the actual destructor must drain them.
    for(unsigned i=0;i<259;++i)owner->create_rectangle(center,2,2,0,10,1);
    assert(count(owner->active)==259 && count(owner->free)==0);
    release(owner,index);
    assert(!process_chain->update_chain.next);
}
void direct_heap_default_and_clocks() {
    auto* zero=create_hit_controller(0);auto* one=create_hit_controller(1);
    assert(zero && one && count(zero->free)==256 && count(one->free)==256);
    for(unsigned i=0;i<256;++i)one->allocate();
    auto* heap=one->allocate();assert(heap->is_heap());
    assert(heap->value_bc==0 && heap->context==&session.context(0));
    // Raw pooled allocation leaves context selection to its creation caller.
    for(auto& region:one->pool)region.select_context(1);
    heap->select_context(1);heap->retire();
    assert(count(one->active)==256 && count(one->free)==0);
    for(auto& region:one->pool)region.retire();
    ClockScalar stopped(0);auto* saved=timer_clock_sources[0];timer_clock_sources[0]=&stopped;
    const auto id=one->create_circle(Vector3(1,2,3),1,1,1,1);
    one->update();assert(one->age.current==0 && one->find(id)->timer.current==1);
    assert(one->find(id)->radius_a==2 && one->visited==1);
    timer_clock_sources[0]=saved;
    one->update();assert(!one->find(id) && one->age.current==1);
    release(one,1);release(zero,0);
    assert(!process_chain->update_chain.next);
}
}
int main() {
    th20::DiagnosticAllocator allocator;th20::process_allocator=&allocator;
    th20::FunctionChainController scheduler;th20::process_chain=&scheduler;
    th20::process_locks.enable();
    for(int index:{0,1}) {lifecycle(index);overflow_and_observer_repair(index);}
    direct_heap_default_and_clocks();
    th20::process_locks.disable();th20::process_chain=nullptr;th20::process_allocator=nullptr;
    std::puts("Whole HitCtrlInf protocol passed: real publication, disabled registration, generations, shapes, pool/heap retirement, observer repair, clocks and destruction.");
}
