// CORE/RECON-989: entire original 261B child event+VM update traversal.
// Original VM callee 0x0042B5D0 /39470B remains NONEXACT.
#include "AnimationRuntimeOwner.hpp"
#include "NativeEventDescendantPoolView.hpp"
#include "Animation.hpp"
#include "IntrusiveLink.hpp"
namespace th20 {
void NativeEventDescendantPoolView::update_descendants_44efc0(std::uint32_t handle, std::int32_t event) {
    Animation* animation=resolve_handle(handle);
    if (animation == nullptr) { } else {
        IntrusiveLink<Animation>* children=&animation->child_links[1];
        IntrusiveIterator<Animation> iter=children->begin();
        IntrusiveIterator<Animation>* end=children->end();
        for (;iter.differs(end);iter.advance()) {
            auto* link=iter.get();
            link->node_access()->interrupt(event);
            link->node_access()->update();
        }
    }
}
}
