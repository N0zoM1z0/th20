#pragma once
#include "DamageRegion.hpp"
#include "TaskInfo.hpp"
#include "Context.hpp"
#include "Session.hpp"
#include "DiagnosticAllocator.hpp"
#include <array>

namespace th20 {
// Native RTTI, construction and consumers establish the whole owner and pool.
class HitCtrlInf : public TaskInfo {
public:
    std::array<DamageRegion,256> pool;
    std::uint32_t next_handle;
    IntrusiveList<DamageRegion> active,free;
    std::uint32_t visited;
    Timer age;
    std::int32_t view_index;
    Context* context;

    HitCtrlInf() noexcept;
    ~HitCtrlInf() override;
    std::int32_t initialize(std::int32_t index);
    void select_context(std::int32_t index);
    void advance_handle();
    DamageRegion* find(Identifier32 handle);
    DamageRegion* allocate();
    void detach(DamageRegion* region);
    std::int32_t update();
    static std::int32_t update_callback(void* owner);
    Identifier32 create_rectangle(const Vector3&,float,float,float,std::int32_t,std::int32_t);
    Identifier32 create_circle(const Vector3&,float,float,std::int32_t,std::int32_t);
};
HitCtrlInf* hit_controller(std::int32_t index);
HitCtrlInf* create_hit_controller(std::int32_t index);
#if defined(_M_IX86)
static_assert(sizeof(HitCtrlInf)==0xc460);
static_assert(offsetof(HitCtrlInf,pool)==0x10);
static_assert(offsetof(HitCtrlInf,next_handle)==0xc410);
static_assert(offsetof(HitCtrlInf,active)==0xc414);
static_assert(offsetof(HitCtrlInf,free)==0xc42c);
static_assert(offsetof(HitCtrlInf,age)==0xc448);
static_assert(offsetof(HitCtrlInf,context)==0xc45c);
#endif
}
