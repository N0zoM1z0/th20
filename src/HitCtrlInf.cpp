#include "HitCtrlInf.hpp"
#include "FunctionChainController.hpp"
#include "EclDiagnostic.hpp"

namespace th20 {
HitCtrlInf::HitCtrlInf() noexcept : next_handle(0),visited(0),view_index(0),context(nullptr) {
    ecl_diagnostic_hint("initialize HitCtrlInf\n");
}
HitCtrlInf::~HitCtrlInf() {
    ecl_diagnostic_hint("shutdown HitCtrlInf\n");
    process_chain->remove(update_node);
    auto& list=active;
    auto iterator=list.begin();
    auto* finish=list.end();
    for (;iterator.differs(finish);iterator.advance()) {
        auto* link=iterator.get();link->node_access()->retire();
    }
}
std::int32_t HitCtrlInf::initialize(std::int32_t index) {
    select_context(index);
    update_node=register_update_disabled(28,update_callback,this);
    auto& selected=session.context(index);
    selected.set_hit_controller(this);
    auto& active_list=active;active_list.reset(nullptr);
    auto& free_list=free;free_list.reset(nullptr);
    for (auto& region:pool) {
        auto& link=region.link;link.initialize(&region);
        auto& list=free;list.append(&region.link);
    }
    next_handle=(static_cast<std::uint32_t>(index)<<16)|1u;
    age=0;
    return 0;
}
void HitCtrlInf::select_context(std::int32_t index) {
    view_index=index;context=&session.context(view_index);
}
void HitCtrlInf::advance_handle() {
    std::uint32_t next=(next_handle+1)&0xffffu;
    if (!(next&=0xffffu)) next=1;
    next_handle=next;
}
DamageRegion* HitCtrlInf::find(Identifier32 handle) {
    if (!handle.get()) return nullptr;
    {
        auto& list=active;
        auto iterator=list.begin();
        auto* finish=list.end();
        for (;iterator.differs(finish);iterator.advance()) {
            auto* link=iterator.get();
            if (link->node_value()->identifier.equals(handle)) return link->node_value();
        }
    }
    return nullptr;
}
DamageRegion* HitCtrlInf::allocate() {
    auto* link=free.front();
    if (link) {
        link->detach();
        auto& list=active;list.append(link);
        auto* region=link->node_value();
        region->identifier=next_handle;
        advance_handle();return region;
    }
    auto* region=process_allocator->allocate_object<DamageRegion>("D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\hit.cpp:605 HitInf");
    auto& entry=region->link;entry.initialize(region);
    auto& list=active;list.append(&region->link);
    region->identifier=next_handle|0x01000000u;
    region->select_context(0);
    advance_handle();return region;
}
void HitCtrlInf::detach(DamageRegion* region) {
    if (region) {
        region->link.detach();
        if (!region->is_heap()) free.prepend(&region->link);
    }
}
std::int32_t HitCtrlInf::update() {
    std::uint32_t count=0;
    {
        auto& list=active;
        auto iterator=list.begin();
        auto* finish=list.end();
        for (;iterator.differs(finish);iterator.advance()) {
            auto* link=iterator.get();link->node_access()->update();++count;
        }
    }
    visited=count;age++;return 1;
}
std::int32_t HitCtrlInf::update_callback(void* owner) {
    return static_cast<HitCtrlInf*>(owner)->update();
}
Identifier32 HitCtrlInf::create_rectangle(const Vector3& position,float width,float height,float angle,
                                        std::int32_t duration,std::int32_t damage) {
    Identifier32 result(next_handle);
    auto* region=allocate();
    if (region) {
        region->select_context(view_index);
        region->configure_rectangle(position,width,height,angle,duration,damage);
        result=region->identifier;
    } else result=0u;
    return result;
}
Identifier32 HitCtrlInf::create_circle(const Vector3& position,float radius,float growth,
                                     std::int32_t duration,std::int32_t damage) {
    Identifier32 result(next_handle);
    auto* region=allocate();
    if (region) {
        region->select_context(view_index);
        region->configure_circle(position,radius,growth,duration,damage);
        result=region->identifier;
    } else result=0u;
    return result;
}
HitCtrlInf* hit_controller(std::int32_t index) {
    return session.context(index).hit_controller();
}
}
