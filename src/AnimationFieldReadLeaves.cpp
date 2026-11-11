// Two original game-owned Animation read methods: 21B at 0x0044C650 and
// 19B at 0x0044CB00. Both are complete native x86 strict candidates.
// A borrowed derived view names the existing Animation receiver ABI; it
// adds no fields or vtable and is not instantiated as a separate object.
#include "Animation.hpp"
#include <cstdint>

namespace th20 {
struct NativeAnimationReadView : Animation {
    std::uint8_t color_alpha_44c650() const;
    Vector3& vector_484_44cb00();
};
static_assert(sizeof(NativeAnimationReadView)==sizeof(Animation),
              "Borrowed read view must not add any Animation storage");

std::uint8_t NativeAnimationReadView::color_alpha_44c650() const {
    return base.channels_490.alpha;
}

Vector3& NativeAnimationReadView::vector_484_44cb00() {
    return base.vector_484;
}
}
