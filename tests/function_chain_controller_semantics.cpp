#include "FunctionChainController.hpp"
#include "DiagnosticObjectFactories.hpp"
#include <array>
#include <cassert>
#include <cstdio>
#include <thread>
#include <vector>

namespace th20 {
LockRegistry process_locks;
DiagnosticAllocator* process_allocator;
FunctionChainController* process_chain;
// Explicit startup fixture. Controller, node, allocator and list bodies run.
DiagnosticAllocator::DiagnosticAllocator():state_word_(0),resource_() {}
template FunctionChainNode* DiagnosticAllocator::allocate_object<FunctionChainNode>(const char*);
}
namespace {
using namespace th20;
bool available() {
    bool acquired=false;
    std::thread thread([&]{auto& m=process_locks.slot(0);acquired=m.try_lock();if(acquired)m.unlock();});
    thread.join();return acquired;
}
struct State {
    int action=1,calls=0,shutdowns=0;
    FunctionChainController* owner=nullptr;
    FunctionChainNode* victim=nullptr;
};
int callback(void* p) {
    auto& s=*static_cast<State*>(p);++s.calls;
    assert(available());
    if(s.victim){s.owner->remove(s.victim);s.victim=nullptr;}
    if((s.action==2||s.action==6)&&s.calls>1)return 1;
    return s.action;
}
int shutdown(void* p) {
    auto& s=*static_cast<State*>(p);++s.shutdowns;
    assert(!available());return 99;
}
int before_insert(void* p) {
    auto& s=*static_cast<State*>(p);++s.calls;assert(available());return -17;
}
void attach(FunctionChainController& owner,FunctionChainNode& node,State& state,bool drawing=false,int priority=1) {
    node.set_callback(callback);node.set_userdata(&state);node.enable();
    node.set_shutdown_callback(shutdown);state.owner=&owner;
    if(drawing)owner.insert_draw(&node,priority);else owner.insert_update(&node,priority);
}
void remove(FunctionChainController& owner,FunctionChainNode& node) {
    owner.remove(&node);assert(!node.link.owner && !node.link.iterator);
}
void actions(bool drawing) {
    const std::array<int,11> inputs{0,1,2,3,4,5,6,7,8,9,-1};
    const std::array<int,11> update_results{2,2,2,1,0,-1,2,2,0,2,2};
    const std::array<int,11> draw_results{2,2,2,1,0,-1,2,2,2,2,2};
    for(unsigned index=0;index<inputs.size();++index) {
        FunctionChainController owner;
        FunctionChainNode first,second;
        State a,b;a.action=inputs[index];
        attach(owner,first,a,drawing,1);attach(owner,second,b,drawing,2);
        const int result=drawing?owner.draw():owner.update();
        assert(result==(drawing?draw_results:update_results)[index]);
        const bool early=a.action==3||a.action==4||a.action==5||(!drawing&&a.action==8);
        assert(b.calls==(early?0:1));
        assert(a.calls==((a.action==2||(!drawing&&a.action==6))?2:1));
        assert(a.shutdowns==(!drawing&&a.action==7?1:0));
        assert(available());
        assert(!first.link.iterator && !second.link.iterator);
        remove(owner,first);remove(owner,second);
    }
}
void counts_and_shutdown() {
    FunctionChainController owner;
    FunctionChainNode enabled,disabled,empty;
    State a,b;
    attach(owner,enabled,a,false,1);attach(owner,disabled,b,false,2);
    disabled.disable();owner.insert_update(&empty,3);
    owner.shutting_down=1;
    assert(owner.update()==2 && a.calls==0 && b.calls==0 && a.shutdowns==1 && b.shutdowns==0);
    owner.shutting_down=0;
    assert(owner.update()==2 && a.calls==1 && b.calls==0);
    remove(owner,enabled);remove(owner,disabled);remove(owner,empty);
}
void insertion_and_membership() {
    FunctionChainController owner;
    FunctionChainNode a,b,c,d,foreign;
    State state;
    a.set_userdata(&state);a.set_before_insert(before_insert);
    assert(owner.insert_update(&a,2)==-17 && !a.before_insert && state.calls==1);
    assert(owner.insert_update(&b,2)==0);
    assert(owner.insert_update(&c,-1)==0);
    assert(owner.insert_draw(&d,4)==0);
    assert(owner.update_chain.next==&c.link && c.link.next==&b.link && b.link.next==&a.link);
    owner.current=&b.link;owner.remove(&b);assert(owner.current==&a.link);
    foreign.set_callback(callback);owner.remove(&foreign);assert(foreign.callback==callback);
    owner.remove(nullptr);
    remove(owner,a);remove(owner,c);remove(owner,d);
}
void mutations(bool drawing) {
    FunctionChainController owner;
    FunctionChainNode first,next,last;
    State a,b,c;
    attach(owner,first,a,drawing,1);attach(owner,next,b,drawing,2);attach(owner,last,c,drawing,3);
    a.victim=&next;
    assert((drawing?owner.draw():owner.update())==2);
    assert(a.calls==1 && b.calls==0 && c.calls==1);
    assert(!first.link.iterator && !next.link.iterator && !last.link.iterator);
    remove(owner,first);remove(owner,next);remove(owner,last);
}
void registration_and_owned_release() {
    FunctionChainController owner;process_chain=&owner;
    std::array<State,4> states;
    auto* a=register_update(2,callback,&states[0]);
    auto* b=register_update_disabled(1,callback,&states[1]);
    auto* c=register_draw(2,callback,&states[2]);
    auto* d=register_draw_disabled(1,callback,&states[3]);
    assert(a->flags.bits==3 && b->flags.bits==1 && c->flags.bits==3 && d->flags.bits==1);
    assert(owner.update()==2 && owner.draw()==2);
    assert(states[0].calls==1 && states[1].calls==0 && states[2].calls==1 && states[3].calls==0);
    owner.remove(a);owner.remove(b);owner.remove(c);owner.remove(d);
    assert(!owner.update_chain.next && !owner.draw_chain.next);
    assert(owner.update_chain.tail==&owner.update_chain && owner.draw_chain.tail==&owner.draw_chain);
    process_chain=nullptr;
}
}
int main() {
    th20::DiagnosticAllocator allocator;th20::process_allocator=&allocator;
    th20::process_locks.enable();
    actions(false);actions(true);counts_and_shutdown();insertion_and_membership();
    mutations(false);mutations(true);registration_and_owned_release();
    assert(available());th20::process_locks.disable();th20::process_allocator=nullptr;
    std::puts("Complete scheduler protocol passed: action tables, order, counts, shutdown, mutation, locks and owned registration/release.");
}
