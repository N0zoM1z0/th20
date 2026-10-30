// Full two original Renderer classification/queueing Bosses 382B and 394B.
// The direct nested link_500.initialize(node_access()) expression preserves
// the actual original native receiver/argument evaluation order; no fake NOP.
#include "Animation.hpp"
#include "NativeSpawnRendererView.hpp"
#include "NativeRendererClassificationView.hpp"
#include "IntrusiveLink.hpp"
#include <cstdint>
namespace th20 {
int NativeRendererClassificationView::classify_primary_44a090(int identifier) {
    int found=0;
    staging.reset(nullptr);
    {
        IntrusiveList<Animation>* active=&main;
        IntrusiveIterator<Animation> iterator=active->begin();
        IntrusiveIterator<Animation>* end=active->end();
        for(;iterator.differs(end);iterator.advance()) {
            IntrusiveLink<Animation>* link=iterator.get();
            if(link->node_access()->field_570==0) {
                int index=link->node_access()->base.field_14;
                if(index>=46 && index<=53) index -= 17;
                else if(index==45) index=26;
                if(index==identifier) {
                    link->node_access()->link_500.initialize(link->node_access());
                    staging.append(&link->node_access()->link_500);
                    ++found;
                }
            }
        }
    }
    return found;
}
int NativeRendererClassificationView::classify_secondary_44a210(int identifier) {
    int found=0;
    staging.reset(nullptr);
    {
        IntrusiveList<Animation>* active=&secondary;
        IntrusiveIterator<Animation> iterator=active->begin();
        IntrusiveIterator<Animation>* end=active->end();
        for(;iterator.differs(end);iterator.advance()) {
            IntrusiveLink<Animation>* link=iterator.get();
            if(link->node_access()->field_570==0) {
                int index=link->node_access()->base.field_14;
                if(index>=29 && index<=36) index += 17;
                else if(index==26) index=45;
                else index=47;
                if(index==identifier) {
                    link->node_access()->link_500.initialize(link->node_access());
                    staging.append(&link->node_access()->link_500);
                    ++found;
                }
            }
        }
    }
    return found;
}
}
