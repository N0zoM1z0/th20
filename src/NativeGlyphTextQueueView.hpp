#pragma once
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory_resource>
#include "NativeGlyphTaskQueue.hpp"
namespace th20 {
// Borrowed i386 layout of the ORIGINAL 12B global PMR list object.
// This is NOT an external NativeGlyphQueueView* global: the original native
// instructions use 0x005B66E0 as the address of the actual 12B object.
// A separate canonical GlyphTaskQueue declaration owns that same global.
// The 56B exact submission bridge only touches the native +0x04 head.
struct NativeGlyphQueueView {
    std::pmr::memory_resource* resource_00;
    void* child_04;
    std::uint32_t count_08;
    void append_4131e0(void* child, std::function<void()>&& task);
    // The native 56B wrapper borrows an existing 40B task by reference.
    void submit_4162f0(std::function<void()>& task);
};
#if defined(_M_IX86)
static_assert(offsetof(NativeGlyphQueueView,child_04)==4);
static_assert(offsetof(NativeGlyphQueueView,count_08)==8);
static_assert(sizeof(NativeGlyphQueueView)==sizeof(GlyphTaskQueue));
#endif
}
