// Original full 82B geometry storage release and 90B pool-record bounds,
// plus native 23B STL index for 0x600-byte PooledAnimation records.
#include "NativeAnimationPoolReleaseViews.hpp"
#include "DiagnosticAllocator.hpp"
namespace th20 {
void NativeAnimationGeometryReleaseView::release_geometry_44c5f0() {
    if (geometry != nullptr) {
        if (geometry != nullptr) {
            process_allocator->release_bytes(geometry);
            geometry=nullptr;
        }
        geometry_bytes=0;
    }
}
int NativeAnimationPoolRecordView::belongs_to_pool_44d970(Animation* animation) {
    return animation >= reinterpret_cast<Animation*>(&(*reinterpret_cast<std::array<PooledAnimation,65536>*>(reinterpret_cast<std::uint8_t*>(this)+0x710))[0]) &&
           animation <= reinterpret_cast<Animation*>(&(*reinterpret_cast<std::array<PooledAnimation,65536>*>(reinterpret_cast<std::uint8_t*>(this)+0x710))[65535]);
}
void instantiate_native_pooled_array_index(std::array<PooledAnimation,65536>& records,std::uint32_t index) {
    (void)&records[index];
}
}
