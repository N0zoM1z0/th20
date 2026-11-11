#pragma once
// Non-owning view of the original process card/ASCII renderer pointer at
// 0x005C0698. Only the native 20B AnimationFile* member getter is modeled;
// the complete 0x1A244+ layout is borrowed from the already maintained
// AsciiInf where its real task queue and shared text-file accessor live.
namespace th20 {
class AnimationFile;
struct NativeCardRendererFileView {
    AnimationFile* current_file_437950();
};
extern NativeCardRendererFileView* native_card_renderer_5c0698;
}
