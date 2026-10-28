// Complete native 143-byte request scheduler; returns void, scans exactly
// 1024 preallocated 72-byte EffectRequest records and copies 56-byte payload.
// The +8 record member is the later creation policy, NOT Animation* storage.
#include "ItemResourceOwners.hpp"
#include "AnimationRuntimeOwner.hpp"
#include <cstring>
namespace th20 {
void EffectInfo::queue_effect(std::int32_t delay_frames, std::int32_t kind,
                              const EffectParameters& parameters, std::int32_t policy) {
    EffectRequest* request=&requests[0];
    for (std::int32_t i=0;i<1024;++i) {
        if (request->type < 0) {
            request->type=kind;
            request->delay=delay_frames;
            request->original_parameters=&parameters;
            request->policy=policy;
            std::memcpy(&request->parameters,&parameters,sizeof(EffectParameters));
            break;
        }
        ++request;
    }
}
// Whole original 271B native EffectInfo frame: preserve direct indexed
// handle access and the delay <= 0 branch's original /Od evaluation order.
std::int32_t EffectInfo::process_queued_effects() {
    current_animation_pool->select_view(view_index);
    for (std::int32_t i = 0; i < 1024; ++i) {
        if (!handles[i].handle.resolve()) {
            handles[i].handle = 0;
        }
    }
    EffectRequest* current = &requests[0];
    for (std::int32_t i = 0; i < 1024; ++i) {
        if (current->type >= 0) {
            if (current->delay <= 0) {
                spawn_effect(current->type, current->parameters, current->policy);
                current->type = -1;
            } else {
                --current->delay;
            }
        }
        ++current;
    }
    return 1;
}
} // namespace th20
