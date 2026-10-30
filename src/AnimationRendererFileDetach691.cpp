// Complete original 691B game Renderer file detachment Boss.
// Iterate both true 24B Animation intrusive lists in the one genuine 72B
// Renderer slot at pool+0x6C8; mark affected Animation records at +0x570.
// The original /Od branches have an intentional empty null-file arm.
// All native 29 E8 and two PE HIGHLOW fields are original-target checked.
#include "NativeFileClearPoolView.hpp"
#include "NativeSpawnRendererView.hpp"
#include "NativeSpawnAnimationPoolView.hpp"
#include "Animation.hpp"
#include "IntrusiveLink.hpp"
#include <cstdint>
namespace th20 {
struct NativeAnimationFlagByte4b0 { std::uint8_t bit0 : 1; std::uint8_t bit1 : 1; std::uint8_t other : 6; };
void NativeFileClearPoolView::detach_file_44fd30(AnimationFile* file,char flag) {
    if(file == nullptr) { } else {
        for(std::int32_t view=0;view<1;++view) {
            auto* renderer = reinterpret_cast<NativeSpawnRendererView*>(
                reinterpret_cast<NativeRendererPoolSelector*>(reinterpret_cast<std::uint8_t*>(this)+0x6C8)->renderer_index_449490(view));
            {
                IntrusiveIterator<Animation> iterator=reinterpret_cast<IntrusiveList<Animation>*>(renderer)->begin();
                IntrusiveIterator<Animation>* end=renderer->main.end();
                for(;iterator.differs(end);iterator.advance()) {
                    IntrusiveLink<Animation>* link=iterator.get();
                    if (link->node_access()->base.field_18==file->id &&
                        (static_cast<std::uint8_t>(flag)==0 || reinterpret_cast<NativeAnimationFlagByte4b0&>(link->node_access()->base.flags.word_18).bit1 == 0)) {
                        link->node_access()->field_570=1;
                    } else if(link->node_access()->base.field_1c==file->id &&
                        (static_cast<std::uint8_t>(flag)==0 || reinterpret_cast<NativeAnimationFlagByte4b0&>(link->node_access()->base.flags.word_18).bit1 == 0)) {
                        link->node_access()->field_570=1;
                    }
                }
            }
            {
                auto* secondary = reinterpret_cast<IntrusiveList<Animation>*>(
                    reinterpret_cast<std::uint8_t*>(reinterpret_cast<NativeRendererPoolSelector*>(
                        reinterpret_cast<std::uint8_t*>(this)+0x6C8)->renderer_index_449490(view))+0x18);
                IntrusiveIterator<Animation> iterator=secondary->begin();
                IntrusiveIterator<Animation>* end=secondary->end();
                for(;iterator.differs(end);iterator.advance()) {
                    IntrusiveLink<Animation>* link=iterator.get();
                    if (link->node_access()->base.field_18==file->id &&
                        (static_cast<std::uint8_t>(flag)==0 || reinterpret_cast<NativeAnimationFlagByte4b0&>(link->node_access()->base.flags.word_18).bit1 == 0)) {
                        link->node_access()->field_570=1;
                    } else if(link->node_access()->base.field_1c==file->id &&
                        (static_cast<std::uint8_t>(flag)==0 || reinterpret_cast<NativeAnimationFlagByte4b0&>(link->node_access()->base.flags.word_18).bit1 == 0)) {
                        link->node_access()->field_570=1;
                    }
                }
            }
        }
    }
}
}
