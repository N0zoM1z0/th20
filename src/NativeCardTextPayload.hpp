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
    ~NativeCardTextPayload();
};
#if defined(_M_IX86)
static_assert(sizeof(NativeCardTextPayload)==0x24);
static_assert(offsetof(NativeCardTextPayload, card)==0);
static_assert(offsetof(NativeCardTextPayload, text)==4);
static_assert(offsetof(NativeCardTextPayload, animation)==0x20);
#endif
}
