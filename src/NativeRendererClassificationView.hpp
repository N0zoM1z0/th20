#pragma once
// Three genuine consecutive 24B Animation intrusive lists at Renderer
// offsets +0x00/+0x18/+0x30. Classification is a NON-OWNING view: it
// never allocates or invents Renderer lifetime/real owner storage.
#include "NativeSpawnRendererView.hpp"
#include "Animation.hpp"
#include <cstddef>
#include <cstdint>
namespace th20 {
struct NativeRendererClassificationView : NativeSpawnRendererView {
    IntrusiveList<Animation> staging;
    int classify_primary_44a090(int identifier);
    int classify_secondary_44a210(int identifier);
};
static_assert(offsetof(NativeRendererClassificationView,staging)==0x30);
}
