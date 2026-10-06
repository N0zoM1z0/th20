#include "DialogueFlags.hpp"
#include "DialogueText.hpp"

#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <new>
#include <type_traits>

// Synthetic storage only. Production storage/lifetime are still unresolved.
char th20::dialogue_text::decoded_text[256];

namespace {
void check_message(const std::array<unsigned char, 256>& plain,
                   const std::array<unsigned char, 256>& expected,
                   unsigned length) {
    struct Input {
        unsigned char before[4];
        char bytes[256];
        unsigned char after[4];
    } input;
    std::memset(&input, 0xd3, sizeof(input));
    for (unsigned i = 0; i <= length; ++i) {
        // Closed-form key sequence, independent of the decoder's recurrence.
        const unsigned key = 0x77 + 7 * i + 8 * i * (i - 1);
        input.bytes[i] = static_cast<char>(plain[i] ^ key);
    }
    const auto original = input;
    std::memset(th20::dialogue_text::decoded_text, 0xa5, 256);
    const char* result = th20::dialogue_text::decode(input.bytes);
    assert(result == th20::dialogue_text::decoded_text);
    assert(std::memcmp(result, expected.data(), length + 1) == 0);
    for (unsigned i = length + 1; i != 256; ++i) {
        assert(static_cast<unsigned char>(result[i]) == 0xa5);
    }
    assert(std::memcmp(&input, &original, sizeof(input)) == 0);
}
}

void check_dialogue_values() {
    using th20::DialogueFlags;
    static_assert(std::is_same_v<decltype(th20::dialogue_text::is_lead(0)), int>);
    alignas(DialogueFlags) std::array<unsigned char, 12> storage;
    for (unsigned low = 0; low != 128; ++low) {
        for (std::uint32_t upper : {0u, 0xffffff80u, 0x5a873d80u, 0xa578c200u}) {
            storage.fill(0xd3);
            const std::uint32_t before = upper | low;
            std::memcpy(storage.data() + 4, &before, 4);
            auto* flags = ::new(storage.data() + 4) DialogueFlags;
            std::uint32_t after;
            std::memcpy(&after, flags, 4);
            assert(after == upper);
            assert(flags->flag_0 == 0 && flags->flag_1 == 0 &&
                   flags->bits_2_5 == 0 && flags->flag_6 == 0);
            for (unsigned i = 0; i != 4; ++i) {
                assert(storage[i] == 0xd3 && storage[i + 8] == 0xd3);
            }
            flags->~DialogueFlags();
        }
    }

    for (unsigned value = 0; value != 256; ++value) {
        const bool lead = (value - 0x81u <= 0x1eu) || (value - 0xe0u <= 0x1cu);
        assert(th20::dialogue_text::is_lead(static_cast<std::uint8_t>(value)) ==
               static_cast<int>(lead));
        if (value && !lead) {
            std::array<unsigned char, 256> plain{}, expected{};
            plain[0] = static_cast<unsigned char>(value);
            expected[0] = value == '_' ? ' ' : static_cast<unsigned char>(value);
            check_message(plain, expected, 1);
        }
        if (lead) {
            // '_' is a valid trail byte and must survive the second pass.
            std::array<unsigned char, 256> plain{}, expected{};
            plain[0] = static_cast<unsigned char>(value);
            plain[1] = '_';
            plain[2] = '_';
            expected = plain;
            expected[2] = ' ';
            check_message(plain, expected, 3);
        }
    }
    constexpr std::array<unsigned char, 4> leads{0x81, 0x9f, 0xe0, 0xfc};
    for (unsigned length = 0; length != 256; ++length) {
        std::array<unsigned char, 256> plain{}, expected{};
        for (unsigned i = 0; i < length; ++i) {
            if (i % 4 == 0 && i + 1 < length) {
                plain[i] = expected[i] = leads[(i / 4) % leads.size()];
            } else if (i % 4 == 1) {
                plain[i] = expected[i] = '_';
            } else {
                plain[i] = '_';
                expected[i] = ' ';
            }
        }
        check_message(plain, expected, length);
    }
    const char* previous = th20::dialogue_text::decoded_text;
    const char encoded_a[]{0x36, 0x7e};
    assert(th20::dialogue_text::decode(encoded_a) == previous);
    assert(previous[0] == 'A' && previous[1] == 0);
    const char encoded_empty[]{0x77};
    assert(th20::dialogue_text::decode(encoded_empty) == previous);
    assert(previous[0] == 0 && previous[1] == 0);
}
