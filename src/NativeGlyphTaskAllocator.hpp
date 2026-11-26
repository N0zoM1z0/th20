#pragma once
#include <functional>
#include <list>
#include <memory_resource>

namespace th20 {
using NativeGlyphTask = std::function<void()>;
using NativeGlyphTaskNode = std::_List_node<NativeGlyphTask, void*>;
}

namespace std::pmr {
template <>
template <>
void polymorphic_allocator<th20::NativeGlyphTaskNode>::construct<
    th20::NativeGlyphTask, th20::NativeGlyphTask>(
    th20::NativeGlyphTask* const destination, th20::NativeGlyphTask&& source);
}
