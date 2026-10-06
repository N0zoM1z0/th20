#pragma once

#include <cstdint>
#include <cstddef>

namespace th20::trophy_text {

struct Message {
    std::int32_t id;
    std::uint8_t title[256];
    std::uint8_t description[2][3][256];

    void reset();
};

static_assert(sizeof(Message) == 0x704);
static_assert(offsetof(Message, title) == 4);
static_assert(offsetof(Message, description) == 0x104);

// Each call overwrites this shared result. The decoder is not reentrant.
extern char decoded_text[256];

// Input must include its encoded NUL and decode to at most 256 bytes.
const char* decode(const std::uint8_t* input);

} // namespace th20::trophy_text
