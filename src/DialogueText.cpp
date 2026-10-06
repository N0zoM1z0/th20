#include "DialogueText.hpp"

namespace th20::dialogue_text {

int is_lead(std::uint8_t value) {
    if ((value >= 0x81 && value <= 0x9f) ||
        (value >= 0xe0 && value <= 0xfc)) {
        return 1;
    } else {
        return 0;
    }
}

const char* decode(const char* input) {
    unsigned offset = 0;
    std::uint8_t key = 0x77;
    std::uint8_t step = 7;
    std::uint8_t value;
    do {
        value = static_cast<std::uint8_t>(*input ^ key);
        decoded_text[offset] = static_cast<char>(value);
        ++offset;
        ++input;
        key = static_cast<std::uint8_t>(key + step);
        step = static_cast<std::uint8_t>(step + 0x10);
    } while (value);

    unsigned index = 0;
    while (static_cast<unsigned char>(decoded_text[index])) {
        if (is_lead(static_cast<unsigned char>(decoded_text[index]))) {
            ++index;
        } else if (static_cast<unsigned char>(decoded_text[index]) == '_') {
            decoded_text[index] = ' ';
        }
        ++index;
    }
    return decoded_text;
}

} // namespace th20::dialogue_text
