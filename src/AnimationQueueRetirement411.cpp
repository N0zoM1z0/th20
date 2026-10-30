// CORE/RECON-977: complete original 411B recursive Animation retirement.
// Actual 57B native IntrusiveList append is the physical 0x411EA0 call;
// do not conflate with the distinct 76B native insert_after 0x411EE0.
#include "Animation.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "NativeAnimationRetirePoolView.hpp"
#include "IntrusiveLink.hpp"
#include <cstdint>
namespace th20 {
void NativeAnimationRetirePoolView::queue_retired_animation_44f840(Animation* animation,IntrusiveList<Animation>* pending) {
    if(animation->child_links[1].next_value()) {
        IntrusiveLink<Animation>* first=animation->child_links[1].next_value();
        IntrusiveIterator<Animation> iterator=first->begin();
        IntrusiveIterator<Animation>* end=first->end();
        for(;iterator.differs(end);iterator.advance()) {
            IntrusiveLink<Animation>* link=iterator.get();
            queue_retired_animation_44f840(link->node_access(),pending);
        }
    }
    if(animation->field_570 != 2) {
        animation->link_53c.initialize(animation);
        pending->append(&animation->link_53c);
    }
    animation->field_570=2;
    animation->parent_558=nullptr;
    animation->parent_55c=nullptr;
    animation->field_554=0;
    animation->field_550=0;
    animation->child_links[0].detach();
}
}
