// Original 182B Renderer AnimationFile find/preload and completion wait.
// Source-present: genuine game-owned file lookup, 269B preload, and stage
// atomic operations. This borrowed class has no separate Renderer storage.
#include "NativeAnimationFileLoadView.hpp"
#include "EclDiagnostic.hpp"
#include "Win32FileApi.hpp"
#include <atomic>
#include <cstdint>
namespace th20 {
// Exactly the same borrowed view declaration as the existing 269B owner;
// the native Renderer instance and method are not duplicated.
struct NativeRendererAnmPreloadView : NativeRendererAnmGroupView {
    NativeAnimationFileLoadView* preload_anm_44ed40(std::uint32_t index, const char* filename);
};
struct NativeRendererAnmFindOrLoadView : NativeRendererAnmPreloadView {
    AnimationFile* find_or_load_file_44eb30(std::int32_t index,const char* filename);
};
extern std::uint32_t native_renderer_async_mode_5c5888;
AnimationFile* NativeRendererAnmFindOrLoadView::find_or_load_file_44eb30(
        std::int32_t index, const char* filename) {
    if (file_by_index(index) != nullptr) {
        ecl_diagnostic_hint("::preloadAnim already : %s\n", filename);
        return file_by_index(index);
    }
    NativeAnimationFileLoadView* file=preload_anm_44ed40(index,filename);
    if (file==nullptr) return nullptr;
    file->stage=1;
    // The original uses std::atomic<uint32_t>::operator bool for the
    // completion poll. Calling .load() returns a different STL thunk and
    // omits the native boolean conversion/local life-time sequence.
    while (static_cast<bool>(file->stage) && ((native_renderer_async_mode_5c5888>>5)&3)==0) {
        Sleep(1);
    }
    ecl_diagnostic_hint("::preloadAnimEnd : %s\n",filename);
    return file;
}
}
