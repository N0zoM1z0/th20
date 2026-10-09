#include "Bomb.hpp"
#include "DiagnosticObjectFactories.hpp"
#include "FunctionChainController.hpp"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <thread>
#include <vector>

namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
FunctionChainController* process_chain;
DiagnosticAllocator::DiagnosticAllocator():state_word_(0),resource_() {}
// Explicit bindings for unimplemented ANM and gameplay dependencies. The
// tests exercise real owned construction/registration/dispatch/destruction.
// Calling either unresolved gameplay body is a fixture failure, not a stub
// implementation accepted as reconstructed gameplay.
std::int32_t Bomb::start(std::int32_t) {std::abort();}
std::int32_t BombController::update() {std::abort();}
std::vector<std::uint32_t> fixture_retired_handles;
void AnimationHandle::retire() {fixture_retired_handles.push_back(value);value=0;}
}
namespace {
using namespace th20;
int events,draws,finishes,destructions;
int controller_destructions;
const Vector3* observed_position;
const Vector2* observed_dimensions;
bool destroy_without_allocator_lock;
struct ObservedBomb final : Bomb {
    bool delete_on_finish=false;
    ~ObservedBomb() override {
        ++destructions;
        // A different thread must acquire slot1 during virtual destruction:
        // a same-thread try_lock would also pass under a recursive lock.
        bool acquired=false;
        std::thread checker([&] {
            if (process_locks.slot(1).try_lock()) {
                acquired=true;process_locks.slot(1).unlock();
            }
        });
        checker.join();destroy_without_allocator_lock=acquired;
    }
    std::int32_t event(const Vector3* position,const Vector2* dimensions) override {
        ++events;observed_position=position;observed_dimensions=dimensions;return 91;
    }
    std::int32_t draw() override {++draws;return -7;}
    std::int32_t finish() override {
        ++finishes;
        if (delete_on_finish) process_allocator->release_object(this);
        return 37;
    }
};
struct ObservedController final : BombController {
    ~ObservedController() override {++controller_destructions;}
};
void clean_chains() {
    assert(!process_chain->update_chain.next && !process_chain->draw_chain.next);
    assert(process_chain->update_chain.tail==&process_chain->update_chain);
    assert(process_chain->draw_chain.tail==&process_chain->draw_chain);
}
void lifecycle_and_dispatch() {
    auto* owner=create_bomb_controller(0);assert(owner==bomb_controller(0));
    assert(owner->context==&session.context(0) && owner->view_index==0);
    assert(owner->flags==2 && !owner->active_bomb && !owner->active_state);
    assert(owner->update_node->priority==33 && owner->draw_node->priority==44);
    assert(owner->update_node->flags.bits==3 && owner->draw_node->flags.bits==3);
    assert(owner->update_node->userdata==owner && owner->draw_node->userdata==owner);
    assert(owner->update_node->callback==BombController::update_callback);
    assert(owner->draw_node->callback==BombController::draw_callback);
    assert(owner->event(nullptr,nullptr)==0 && owner->finish()==0 && owner->draw()==1);
    owner->disable();assert(owner->update_node->flags.bits==1 && owner->draw_node->flags.bits==1);
    assert(process_chain->update()==1 && process_chain->draw()==1);
    // Only draw is enabled: original Controller::update remains unimplemented.
    owner->draw_node->enable();
    auto* bomb=new ObservedBomb;
    assert(!bomb->field_04 && !bomb->field_78 && !bomb->field_7c);
    assert(bomb->interpolation.start==0 && bomb->interpolation.end==0);
    assert(bomb->interpolation.duration==0 && bomb->interpolation.mode==0);
    assert(!bomb->handle_70.value && !bomb->handle_74.value && !bomb->handle_ac.value);
    bomb->select_context(0);owner->active_bomb=bomb;owner->active_state=1;
    Vector3 position(2,3,4);Vector2 dimensions(5,6);
    assert(owner->event(&position,&dimensions)==0 && events==1);
    assert(observed_position==&position && observed_dimensions==&dimensions);
    assert(owner->event(nullptr,nullptr)==0 && events==2);
    assert(!observed_position && !observed_dimensions);
    assert(process_chain->draw()==1 && draws==1);
    assert(owner->finish()==37 && finishes==1 && owner->active_bomb==bomb);
    bomb->handle_70.value=17;bomb->handle_74.value=19;
    bomb->delete_on_finish=true;
    assert(owner->finish()==37 && finishes==2);
    assert(destructions==1 && destroy_without_allocator_lock);
    assert(!owner->active_bomb && !owner->active_state);
    assert((fixture_retired_handles==std::vector<std::uint32_t>{17,19}));
    destroy_bomb_controller(0);assert(!bomb_controller(0));clean_chains();
    destroy_bomb_controller(0);clean_chains();
}
void cross_context_destruction() {
    auto* zero=create_bomb_controller(0);auto* one=create_bomb_controller(1);
    assert(one==bomb_controller(1) && one->context==&session.context(1));
    assert(one->view_index==1 && one->age.current==0);
    zero->active_state=8;
    auto* bomb=new ObservedBomb;bomb->select_context(1);
    assert(bomb->context==one->context && bomb->view_index==1);
    bomb->handle_70.value=23;bomb->handle_74.value=29;
    one->active_bomb=bomb;one->active_state=1;
    destroy_bomb_controller(1);
    // Original BombBaseInf explicitly resets Context0 even when bound to1.
    assert(!zero->active_bomb && zero->active_state==0);
    assert(!bomb_controller(1) && bomb_controller(0)==zero);
    assert(destructions==2 && destroy_without_allocator_lock);
    assert((fixture_retired_handles==std::vector<std::uint32_t>{17,19,23,29}));
    assert(process_chain->update_chain.next->node==zero->update_node);
    assert(process_chain->draw_chain.next->node==zero->draw_node);
    destroy_bomb_controller(0);clean_chains();
}
void direct_base_protocol() {
    auto* owner=create_bomb_controller(0);
    auto* bomb=new Bomb;owner->active_bomb=bomb;owner->active_state=1;
    assert(bomb->update()==0 && bomb->draw()==0 && bomb->finish()==0);
    assert(bomb->event(nullptr,nullptr)==0);
    destroy_bomb_controller(0);assert(!bomb_controller(0));clean_chains();
    process_allocator->release_object(static_cast<Bomb*>(nullptr));
}
void controller_virtual_release() {
    auto* owner=new ObservedController;assert(owner->initialize(1)==0);
    session.context(1).set_bomb_controller(owner);
    destroy_bomb_controller(1);
    assert(controller_destructions==1 && !bomb_controller(1));clean_chains();
}
}
int main() {
    DiagnosticAllocator allocator;process_allocator=&allocator;
    FunctionChainController scheduler;process_chain=&scheduler;
    process_locks.enable();
    lifecycle_and_dispatch();cross_context_destruction();direct_base_protocol();controller_virtual_release();
    process_locks.disable();process_chain=nullptr;process_allocator=nullptr;
    std::puts("Actual Bomb ownership passed: native enabled registration, typed publication, dispatch return handling, virtual release outside lock, self-retirement, Context0 reset and real scheduler teardown. ANM/gameplay bindings remain fixtures.");
}
