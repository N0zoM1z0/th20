#include "Bomb.hpp"
#include "DiagnosticObjectFactories.hpp"

namespace th20 {
void Context::release_bomb_controller() {
    if (object_18) {process_allocator->release_object(object_18);object_18=nullptr;}
}
template BombController* DiagnosticAllocator::allocate_object<BombController>(const char*);
BombController* create_bomb_controller(std::int32_t index) {
    auto* owner=process_allocator->allocate_object<BombController>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\bomb.cpp:87 BombInf");
    if (!owner) return nullptr;
    // The genuine failure path releases allocation and invalidates its
    // local pointer. Preserve the original explicit cleanup control flow.
    if (owner->initialize(index)) goto cleanup;
    {
        auto& selected = session.context(index);
        selected.set_bomb_controller(owner);
        return owner;
    }
cleanup:
    if (owner) {
        process_allocator->release_object(owner);
        owner = nullptr;
    }
    return nullptr;
}
void destroy_bomb_controller(std::int32_t index) {
    session.context(index).release_bomb_controller();
}
}
