// Primary Renderer animation update, including deferred subtree retirement.
// The source follows the complete native iterator and two-phase release path.
#include "NativeAnimationRendererUpdate.hpp"
#include "NativeAnimationRetirePoolView.hpp"
#include "Animation.hpp"
#include "IntrusiveLink.hpp"

namespace th20 {
void __fastcall animation_list_update_449870(IntrusiveList<Animation>* list) {
    IntrusiveList<Animation> pending{};
    pending.reset(nullptr);
    {
        IntrusiveList<Animation>* active = list;
        IntrusiveIterator<Animation> iterator = active->begin();
        IntrusiveIterator<Animation>* end = active->end();
        for (; iterator.differs(end); iterator.advance()) {
            IntrusiveLink<Animation>* link = iterator.get();
            link->node_access()->field_554 = 0;
            link->node_access()->field_550 = 0;
            if (link->node_access()->field_570 == 1) {
                reinterpret_cast<NativeAnimationRetirePoolView*>(current_animation_pool)
                    ->queue_retired_animation_44f840(link->node_access(), &pending);
            } else if (link->node_access()->field_570 == 0) {
                if (link->node_access()->update() != 0) {
                    reinterpret_cast<NativeAnimationRetirePoolView*>(current_animation_pool)
                        ->queue_retired_animation_44f840(link->node_access(), &pending);
                }
            }
        }
    }
    {
        IntrusiveList<Animation>* retired = &pending;
        IntrusiveIterator<Animation> iterator = retired->begin();
        IntrusiveIterator<Animation>* end = retired->end();
        for (; iterator.differs(end); iterator.advance()) {
            IntrusiveLink<Animation>* link = iterator.get();
            current_animation_pool->release_animation(link->node_access());
        }
    }
}
}
