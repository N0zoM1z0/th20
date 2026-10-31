#pragma once
#include <cstddef>
#include <cstdint>
#include <functional>
namespace th20 {
// Borrowed original glyph text render-queue owner. Its +0x04 word is an
// observed nested submission pointer; other allocation state is not owned.
struct NativeGlyphQueueView {
    std::uint32_t state_00;
    void* child_04;
    void append_4131e0(void* child, std::function<void()>&& task);
    // The native 56B wrapper borrows an existing 40B task by reference.
    void submit_4162f0(std::function<void()>& task);
};
#if defined(_M_IX86)
static_assert(offsetof(NativeGlyphQueueView,child_04)==4);
#endif
extern NativeGlyphQueueView* native_glyph_queue_5b66e0;
}
