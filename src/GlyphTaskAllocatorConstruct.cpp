// Task construction retains the native C++17 tuple-application protocol.
#include "NativeGlyphTaskAllocator.hpp"
#include <tuple>
#include <utility>

namespace std {
#if _MSVC_LANG < 202002L
// C++17 compatibility for the one-element C++20 allocator argument protocol.
template <class _Ty, class _Alloc, class... _Types>
_NODISCARD constexpr auto uses_allocator_construction_args(const _Alloc&, _Types&&...) noexcept;
#endif

template <>
_NODISCARD constexpr __declspec(noinline) auto
uses_allocator_construction_args<
    th20::NativeGlyphTask,
    pmr::polymorphic_allocator<th20::NativeGlyphTaskNode>,
    th20::NativeGlyphTask>(
    const pmr::polymorphic_allocator<th20::NativeGlyphTaskNode>& allocator,
    th20::NativeGlyphTask&& source) noexcept {
    (void)allocator;
    return std::forward_as_tuple(std::forward<th20::NativeGlyphTask>(source));
}
}

namespace std::pmr {
template <>
template <>
void polymorphic_allocator<th20::NativeGlyphTaskNode>::construct<
    th20::NativeGlyphTask, th20::NativeGlyphTask>(
    th20::NativeGlyphTask* const destination, th20::NativeGlyphTask&& source) {
    std::apply(
        [destination](auto&&... values) {
            return ::new (const_cast<void*>(static_cast<const volatile void*>(destination)))
                th20::NativeGlyphTask(std::forward<decltype(values)>(values)...);
        },
        std::uses_allocator_construction_args<th20::NativeGlyphTask>(
            *this, std::forward<th20::NativeGlyphTask>(source)));
}
}
