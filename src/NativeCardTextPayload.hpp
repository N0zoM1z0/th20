#pragma once
#include <cstddef>
#include <memory_resource>
#include <string>
namespace th20 {
struct Card;
class Animation;
// Original 36-byte payload captured by Card::start_spell's deferred text
// pathway. Real standard-library PMR string occupies bytes 4..31; its
// 167-byte copy constructor is an independent compiler-provided native head.
struct NativeCardTextPayload {
    Card* card;
    std::pmr::string text;
    Animation* animation;
    NativeCardTextPayload(Card* card, const std::pmr::string& text,
                          Animation* animation);
    // A std::function target must be copyable for its own copy requests.
    // This is ordinary PMR string copying, separate from the accepted move.
    NativeCardTextPayload(const NativeCardTextPayload& source);
    // Original lambda/callback capture move: the PMR string is transferred,
    // not copied; the underlying STL move implementation is separate.
    NativeCardTextPayload(NativeCardTextPayload&& source);
    ~NativeCardTextPayload();
    // Actual Card text lambda entry at 0x00486E80, 111B. Its UI drawing
    // body is still under separate native reconstruction, not a fake stub.
    void operator()() const;
};
#if defined(_M_IX86)
static_assert(sizeof(NativeCardTextPayload)==0x24);
static_assert(offsetof(NativeCardTextPayload, card)==0);
static_assert(offsetof(NativeCardTextPayload, text)==4);
static_assert(offsetof(NativeCardTextPayload, animation)==0x20);
#endif
}
