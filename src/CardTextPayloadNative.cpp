// Original Card start's complete native typed capture payload.
// An implicit ordinary std::pmr::string copy constructor produces the
// separate 167-byte original STL copy head and original EH/cookie roles.
#include "NativeCardTextPayload.hpp"
#include "Card.hpp"
#include "Animation.hpp"
#include <utility>

// CORE/RECON-1187: the original 108B PMR basic_string move path calls the
// shared 8B std::move<T&> forwarding leaf for its polymorphic allocator.
// Preserve that ABI boundary rather than letting current MSVC inline it.
template __declspec(noinline) std::pmr::polymorphic_allocator<char>&&
std::move<std::pmr::polymorphic_allocator<char>&>(
    std::pmr::polymorphic_allocator<char>&) noexcept;

namespace th20 {
NativeCardTextPayload::NativeCardTextPayload(
    Card* owner, const std::pmr::string& source, Animation* ani)
    : card(owner), text(source), animation(ani) {}
NativeCardTextPayload::NativeCardTextPayload(const NativeCardTextPayload& source)
    : card(source.card), text(source.text), animation(source.animation) {}
NativeCardTextPayload::NativeCardTextPayload(NativeCardTextPayload&& source)
    : card(source.card), text(std::move(source.text)), animation(source.animation) {}
NativeCardTextPayload::~NativeCardTextPayload() {}
}
