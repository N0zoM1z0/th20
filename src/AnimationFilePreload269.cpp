// Original native 269B game Renderer ANM file preload and registration.
// One real owner: the live Renderer, with 42 indexed AnimationFile slots.
// The full original C++/EH byte matching is independently verified.
#include "NativeAnimationFileLoadView.hpp"
#include "DiagnosticObjectFactories.hpp"
#include "DiagnosticLog.hpp"
#include "EclDiagnostic.hpp"
#include "LockRegistry.hpp"
#include <array>
#include <cstdint>
#include <mutex>
namespace th20 {
extern const char native_anm_preload_format_56e378[];
extern const char native_anm_slots_error_56e38c[];
struct NativeRendererAnmPreloadView : NativeRendererAnmGroupView {
    NativeAnimationFileLoadView* preload_anm_44ed40(std::uint32_t index,const char* filename);
};
NativeAnimationFileLoadView* NativeRendererAnmPreloadView::preload_anm_44ed40(
        std::uint32_t index,const char* filename) {
    ecl_diagnostic_hint(native_anm_preload_format_56e378,filename);
    if (static_cast<std::int32_t>(index)>=42) {
        report_log_error(&diagnostic_log,native_anm_slots_error_56e38c);
        return nullptr;
    }
    NativeAnimationFileLoadView* result;
    {
        std::lock_guard<std::recursive_mutex> guard(process_locks.slot(0x11));
        AnimationFile* file=process_allocator->allocate_object<AnimationFile>(
            "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\sprtlib.cpp:950 SprtGroupInf");
        auto& files=*reinterpret_cast<std::array<AnimationFile*,42>*>(
            reinterpret_cast<std::uint8_t*>(this)+0x06000730);
        files.at(index)=file;
        result=static_cast<NativeAnimationFileLoadView*>(file);
        result->id=index;
    }
    if (result->load_resource_44a700(filename)!=0) {
        process_allocator->release_object(static_cast<AnimationFile*>(result));
        result=nullptr;
        return nullptr;
    }
    return result;
}
}
