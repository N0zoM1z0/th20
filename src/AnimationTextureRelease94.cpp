// Original full 94B IDirect3DTexture9 Release and buffer cleanup.
#include "AnimationFile.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "NativeFileClearPoolView.hpp"
#include "DiagnosticAllocator.hpp"
#include <d3d9.h>
namespace th20 {
void NativeFileClearPoolView::cleanup_texture_44c510(TextureRecord* record) {
    if(record->texture){
        record->texture->Release();
        record->texture=nullptr;
    }
    if(record->external_bytes){
        if(record->external_bytes){
            process_allocator->release_bytes(record->external_bytes);
            record->external_bytes=nullptr;
        }
    }
}
}
