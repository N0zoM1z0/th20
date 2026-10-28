// Complete native 143-byte request scheduler; returns void, scans exactly
// 1024 preallocated 72-byte EffectRequest records and copies 56-byte payload.
// Request+8 is the optional live Animation* (not a strategy number).
#include "ItemResourceOwners.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"
#include <cstring>
namespace th20 {
void EffectInfo::queue_effect(std::int32_t delay_frames, std::int32_t kind,
                              const EffectParameters& parameters, Animation* existing_animation) {
    EffectRequest* request=&requests[0];
    for (std::int32_t i=0;i<1024;++i) {
        if (request->type < 0) {
            request->type=kind;
            request->delay=delay_frames;
            request->original_parameters=&parameters;
            request->animation=existing_animation;
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
                spawn_effect(current->type, current->parameters, current->animation);
                current->type = -1;
            } else {
                --current->delay;
            }
        }
        ++current;
    }
    return 1;
}
// Original +0x005AFAB8 table: native 0x20-byte records with observed
// signed file/script indices and an optional cdecl effect setup callback.
// The remaining 24 bytes of each actual record are not yet classified.
using EffectInitCallback = void (*)(Animation*,const EffectParameters&,std::int32_t);
struct EffectScriptSpec {
    std::int16_t file_index;
    std::int16_t script_index;
    EffectInitCallback callback;
    std::uint8_t as_yet_untyped_record_words[24];
};
static_assert(sizeof(EffectScriptSpec)==0x20);
extern const EffectScriptSpec native_effect_scripts[];
void __fastcall clear_animation_handle_value(AnimationHandle& value);


AnimationHandle EffectInfo::spawn_effect(std::int32_t kind, const EffectParameters& parameters,
                                         Animation* existing_animation) {
    const EffectScriptSpec* spec = &native_effect_scripts[kind];
    AnimationHandle result;
    clear_animation_handle_value(result);
    if (spec->script_index >= 0) {
        if (!existing_animation) {
            AnimationFile* file = files[spec->file_index];
            const std::int32_t view = view_index;
            const std::int32_t script = spec->script_index;
            result = file->spawn(nullptr,script,view,nullptr);
            existing_animation = result.resolve();
            existing_animation->set_flag0_recursively();
        } else {
            result = 0;
        }
        if (spec->callback) {
            spec->callback(existing_animation,parameters,view_index);
        }
    }
    return result;
}

} // namespace th20
