#include "TrophyText.hpp"

namespace th20::trophy_text {

char decoded_text[256];

void Message::reset() {
    id = -1;
}

const char* decode(const std::uint8_t* input) {
    unsigned index = 0;
    std::uint8_t key = 0x77;
    std::uint8_t step = 7;
    char value;
    do {
        value = static_cast<char>(*input ^ key);
        decoded_text[index] = value;
        ++index;
        ++input;
        key = static_cast<std::uint8_t>(key + step);
        step = static_cast<std::uint8_t>(step + 0x10);
    } while (value);
    return decoded_text;
}

} // namespace th20::trophy_text
