// Original 111B / 42-i386 Card spell-name lambda callback.
// Correct native owner ABI: the text is an embedded std::pmr::string at +4;
// its real std::pmr::string::c_str() helper is the 22B physical 0x44BAF0.
// The 8B text result is a native return object; the variadic Renderer owner
// uses __cdecl (this on stack), and the 294B submit child is __thiscall.
#include "NativeCardTextPayload.hpp"
#include "NativeAsciiTextDrawView.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Card.hpp"
#include <functional>
#include <cstdint>
namespace th20 {
// A four-byte real callable holding the Card owner. Its 24B value constructor
// folds into original 0x004142A0, an already accepted physical 24B helper.
// The implementation of operator() is still a separate native source owner.
struct NativeCardTickCallback {
    Card* owner;
    explicit NativeCardTickCallback(Card* card) : owner(card) {}
    void operator()() const;
};
#if defined(_M_IX86)
static_assert(sizeof(NativeCardTickCallback) == 4);
#endif
void NativeCardTextPayload::operator()() const {
    // The native layer number is 0x00FFFFFF, NOT -1: both values are distinct
    // and MSVC emits different instructions for their original pushes.
    reinterpret_cast<NativeTextSubmitOwner*>(current_animation_pool)->draw_44b020(
        animation, 0x00FFFFFF, 0xFF000000u, 4, 0, 0,
        std::function<void()>(NativeCardTickCallback(card)), text.c_str());
}
}
