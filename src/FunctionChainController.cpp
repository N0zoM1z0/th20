#include "FunctionChainController.hpp"

namespace th20 {

FunctionChainController::FunctionChainController():current(nullptr),shutting_down(0) {}

FunctionChainNode* FunctionChainController::create(FunctionChainCallback callback) {
    auto* node=process_allocator->allocate_object<FunctionChainNode>("D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\func.cpp:317 funcChainInf");
    node->set_callback(callback);
    node->set_owned();
    return node;
}

FunctionChainNode* register_update(std::int32_t priority,FunctionChainCallback callback,void* userdata) {
    auto* node=process_chain->create(callback);
    node->set_userdata(userdata);node->enable();
    process_chain->insert_update(node,priority);return node;
}
FunctionChainNode* register_update_disabled(std::int32_t priority,FunctionChainCallback callback,void* userdata) {
    auto* node=process_chain->create(callback);
    node->set_userdata(userdata);node->disable();
    process_chain->insert_update(node,priority);return node;
}
FunctionChainNode* register_draw(std::int32_t priority,FunctionChainCallback callback,void* userdata) {
    auto* node=process_chain->create(callback);
    node->set_userdata(userdata);node->enable();
    process_chain->insert_draw(node,priority);return node;
}
FunctionChainNode* register_draw_disabled(std::int32_t priority,FunctionChainCallback callback,void* userdata) {
    auto* node=process_chain->create(callback);
    node->set_userdata(userdata);node->disable();
    process_chain->insert_draw(node,priority);return node;
}

void FunctionChainController::remove_unlocked(FunctionChainNode* node) {
    if (!node) return;
    auto& updates=update_chain;
    auto* link=updates.find(node);
    if (!link) {
        auto& draws=draw_chain;
        link=draws.find(node);
        if (!link) return;
    }
    if (current==link) current=link->next_value();
    link->detach();
    node->callback=nullptr;
    if (node->flags.bits&1u) process_allocator->release_object(node);
}

void FunctionChainController::remove(FunctionChainNode* node) {
    if (!node) return;
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(0));
    remove_unlocked(node);
}

std::int32_t FunctionChainController::insert_update(FunctionChainNode* node,std::int32_t priority) {
    std::int32_t result=0;
    if (node->before_insert) {result=node->before_insert(node->userdata_value());node->before_insert=nullptr;}
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(0));
    node->priority=priority;
    {
        auto& list=update_chain;
        auto iterator=list.begin();
        auto* end=list.end();
        for (;iterator.differs(end);iterator.advance()) {
            auto* link=iterator.get();
            if (link->node_access()->priority>=priority) {link->insert_before(&node->link);return result;}
        }
    }
    auto& list=update_chain;
    list.append(&node->link);return result;
}

std::int32_t FunctionChainController::insert_draw(FunctionChainNode* node,std::int32_t priority) {
    std::int32_t result=0;
    if (node->before_insert) {result=node->before_insert(node->userdata_value());node->before_insert=nullptr;}
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(0));
    node->priority=priority;
    {
        auto& list=draw_chain;
        auto iterator=list.begin();
        auto* end=list.end();
        for (;iterator.differs(end);iterator.advance()) {
            auto* link=iterator.get();
            if (link->node_access()->priority>=priority) {link->insert_before(&node->link);return result;}
        }
    }
    auto& list=draw_chain;
    list.append(&node->link);return result;
}

std::int32_t FunctionChainController::update() {
    process_locks.enter_tracked(0);
restart:
    std::int32_t count=0;
    {
        auto& list=update_chain;
        auto iterator=list.begin();
        auto* end=list.end();
        for (;iterator.differs(end);iterator.advance()) {
            auto* link=iterator.get();
            if (!link->node_access()->callback) continue;
enabled:
            if ((link->node_access()->flags.bits>>1)&1u) {
                if (shutting_down) goto shutdown;
                process_locks.leave_tracked(0);
                {
                const auto action=link->node_access()->callback(link->node_access()->userdata);
                process_locks.enter_tracked(0);
                switch (action) {
                case 0:remove_unlocked(link->node_access());break;
                case 1:break;
                case 2:goto enabled;
                case 3:count=1;goto finish;
                case 4:count=0;goto finish;
                case 5:count=-1;goto finish;
                case 6:goto restart;
                case 7:goto shutdown;
                case 8:count=0;goto finish;
                }
                }
                goto counted;
shutdown:
                    if (link->node_access()->shutdown_callback_value()) {
                        auto callback=link->node_access()->shutdown_callback_value();
                        callback(link->node_access()->userdata_value());
                    }
            }
counted:
            ++count;
        }
    }
finish:
    process_locks.leave_tracked(0);return count;
}

std::int32_t FunctionChainController::draw() {
    process_locks.enter_tracked(0);
    std::int32_t count=0;
    {
        auto& list=draw_chain;
        auto iterator=list.begin();
        auto* end=list.end();
        for (;iterator.differs(end);iterator.advance()) {
            auto* link=iterator.get();
            if (!link->node_access()->callback) continue;
enabled:
            if ((link->node_access()->flags.bits>>1)&1u) {
                process_locks.leave_tracked(0);
                const auto action=link->node_access()->callback(link->node_access()->userdata_value());
                process_locks.enter_tracked(0);
                switch (action) {
                case 0:remove_unlocked(link->node_access());break;
                case 1:break;
                case 2:goto enabled;
                case 3:count=1;goto clear_observers;
                case 4:count=0;goto clear_observers;
                case 5:count=-1;goto clear_observers;
                }
            }
            ++count;
        }
    }
clear_observers:
    {
        auto& list=draw_chain;
        auto iterator=list.begin();
        auto* end=list.end();
        for (;iterator.differs(end);iterator.advance()) {
            auto* link=iterator.get();link->set_iterator(nullptr);
        }
    }
    process_locks.leave_tracked(0);return count;
}
}
