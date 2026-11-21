#include "FrontDialogueFieldViews.hpp"
#include <cstdint>

namespace th20 {

char* NativeSoundInfQueuedTrackView::queued_track_name_4b8090() {
    return reinterpret_cast<char*>(reinterpret_cast<std::uint8_t*>(this) + 0x2444);
}

AnimationFile* NativeFrontInfMessageFileView::message_file_4b8270() {
    return *reinterpret_cast<AnimationFile**>(reinterpret_cast<std::uint8_t*>(this) + 0x170);
}

} // namespace th20
