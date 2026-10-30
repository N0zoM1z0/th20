// Entire original 230B staged Renderer Animation draw/owner counter loop.
// Original 5993B Animation draw remains separately NONEXACT.
#include "NativeRendererClassificationOwner.hpp"
#include "Animation.hpp"
#include "IntrusiveLink.hpp"
#include <cstdint>
namespace th20 {
void __fastcall apply_renderer_staging_449fa0(NativeRendererClassificationView* renderer) {
    IntrusiveList<Animation>* staged=&renderer->staging;
    IntrusiveIterator<Animation> iterator=staged->begin();
    IntrusiveIterator<Animation>* end=staged->end();
    for(;iterator.differs(end);iterator.advance()) {
        IntrusiveLink<Animation>* link=iterator.get();
        Animation* animation=link->node_access();
        current_animation_pool->draw(animation);
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(current_animation_pool)+0xd8)=
            *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(current_animation_pool)+0xd8)+1u;
    }
}
}
