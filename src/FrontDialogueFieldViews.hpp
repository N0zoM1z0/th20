#pragma once

namespace th20 {

class AnimationFile;

struct NativeSoundInfQueuedTrackView {
    char* queued_track_name_4b8090();
};

struct NativeFrontInfMessageFileView {
    AnimationFile* message_file_4b8270();
};

} // namespace th20
