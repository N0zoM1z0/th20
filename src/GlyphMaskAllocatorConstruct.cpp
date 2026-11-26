// Native glyph PMR construction and tuple-application protocol.
// C++17 preserves the original out-of-line forwarding and empty-sequence ABI.
#include "NativeGlyphMaskOffsets.hpp"
#include <tuple>
#include <utility>

template __declspec(noinline) const th20::GlyphMaskOffset&&
std::move<const th20::GlyphMaskOffset&>(const th20::GlyphMaskOffset&) noexcept;

namespace std {
#if _MSVC_LANG < 202002L
// C++17 library compatibility: the native PMR allocator helper predates the
// C++20 standard declaration, but its ABI is the same one-element argument tuple.
template <class _Ty, class _Alloc, class... _Types>
_NODISCARD constexpr auto uses_allocator_construction_args(const _Alloc&, _Types&&...) noexcept;
#endif

template <>
_NODISCARD constexpr __declspec(noinline) tuple<const th20::GlyphMaskOffset&&>
forward_as_tuple<const th20::GlyphMaskOffset>(
    const th20::GlyphMaskOffset&& source) noexcept {
    return tuple<const th20::GlyphMaskOffset&&>(std::move(source));
}

template <>
_NODISCARD constexpr __declspec(noinline) auto
uses_allocator_construction_args<
    th20::GlyphMaskOffset,
    pmr::polymorphic_allocator<th20::GlyphMaskOffset>,
    const th20::GlyphMaskOffset>(
    const pmr::polymorphic_allocator<th20::GlyphMaskOffset>& allocator,
    const th20::GlyphMaskOffset&& source) noexcept {
    (void)allocator;
    return std::forward_as_tuple(std::move(source));
}
} // namespace std

namespace std::pmr {
template <>
template <>
__declspec(safebuffers) void polymorphic_allocator<th20::GlyphMaskOffset>::construct<
    th20::GlyphMaskOffset, const th20::GlyphMaskOffset>(
    th20::GlyphMaskOffset* const destination,
    const th20::GlyphMaskOffset&& source) {
    std::apply(
        [destination](const th20::GlyphMaskOffset&& value) -> th20::GlyphMaskOffset* {
            return ::new (const_cast<void*>(static_cast<const volatile void*>(destination)))
                th20::GlyphMaskOffset(std::move(value));
        },
        std::uses_allocator_construction_args<th20::GlyphMaskOffset>(
            *this,std::move(source)));
}
} // namespace std::pmr
