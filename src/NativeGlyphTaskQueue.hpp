#pragma once
#include <functional>
#include <list>
#include <memory_resource>
namespace th20 {
// Native global 0x005B66E0 is the actual 12-byte i386 PMR list owner:
// polymorphic allocator resource, sentinel/head node, and live task count.
// The separate exact 56B submission method borrows its +0x04 node slot.
using GlyphTaskQueue = std::pmr::list<std::function<void()>>;
extern GlyphTaskQueue native_glyph_task_queue_5b66e0;
#if defined(_M_IX86)
static_assert(sizeof(GlyphTaskQueue)==12);
#endif
}
