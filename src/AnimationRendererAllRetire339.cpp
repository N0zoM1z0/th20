// CORE/RECON-988: original whole 339B/106-i386 two-list Renderer retirement.
// Both loops invoke the same genuine whole-exact 308B AnimationPool retire.
#include "NativeSpawnRendererView.hpp"
#include "Animation.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "IntrusiveLink.hpp"
namespace th20 {
void __fastcall retire_all_renderer_44a3a0(NativeSpawnRendererView* renderer) {
    {
        IntrusiveList<Animation>* active=&renderer->main;
        IntrusiveIterator<Animation> iter=active->begin();
        IntrusiveIterator<Animation>* end=active->end();
        for(;iter.differs(end);iter.advance()) {
            auto* link=iter.get();
            Animation* value=link->node_access();
            current_animation_pool->release_animation(value);
        }
    }
    {
        IntrusiveList<Animation>* secondary=&renderer->secondary;
        IntrusiveIterator<Animation> iter=secondary->begin();
        IntrusiveIterator<Animation>* end=secondary->end();
        for(;iter.differs(end);iter.advance()) {
            auto* link=iter.get();
            Animation* value=link->node_access();
            current_animation_pool->release_animation(value);
        }
    }
}
}
