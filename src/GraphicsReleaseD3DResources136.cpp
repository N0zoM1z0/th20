// Whole original 136B/35-i386 Graphics D3D9 resource recovery at 0x004DD840.
// Original PE absolute resource fields are genuinely process Graphics
// global owner +0x19C/+0x1A0/+0x1A4, each a real IUnknown resource.
// Release through the COM vtable, clear each slot and the primary again.
#include "Graphics.hpp"
namespace th20 {
struct NativeFrameGraphicsView {
    void frame_recover_4dd840();
};
void NativeFrameGraphicsView::frame_recover_4dd840() {
    if (process_graphics.resource_19c != nullptr) {
        process_graphics.resource_19c->Release();
        process_graphics.resource_19c = nullptr;
    }
    if (process_graphics.resource_1a0 != nullptr) {
        process_graphics.resource_1a0->Release();
        process_graphics.resource_1a0 = nullptr;
    }
    if (process_graphics.resource_1a4 != nullptr) {
        process_graphics.resource_1a4->Release();
        process_graphics.resource_1a4 = nullptr;
    }
    process_graphics.resource_19c = nullptr;
}
}
