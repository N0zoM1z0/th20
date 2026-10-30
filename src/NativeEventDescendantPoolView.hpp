#pragma once
// Original non-owning pool receiver for the full 261B descendant event pass.
// Its 456B handle resolver is already source-present whole strict exact.
#include "AnimationRuntimeOwner.hpp"
#include <cstdint>
namespace th20 {
struct NativeEventDescendantPoolView : AnimationPoolOwner {
    void update_descendants_44efc0(std::uint32_t handle,std::int32_t event);
};
}
