#include "ScriptStack.hpp"
#include <cstring>

namespace th20 {
int ScriptStack::push(std::int32_t byte_count, const void* input, char supplied_type) {
    if (words.size() < static_cast<std::size_t>((pointer + byte_count + 4) / 4)) {
        words.resize((pointer + byte_count + 4) / 4);
    }
    if (supplied_type) {
        words[pointer / 4] = supplied_type;
        pointer += 4;
    }
    if (byte_count == 4) {
        words[pointer / 4] = *reinterpret_cast<const std::uint32_t*>(input);
    } else {
        std::memcpy(&words[pointer / 4], input, byte_count);
    }
    pointer += byte_count;
    return 0;
}
int ScriptStack::pop(std::int32_t byte_count, void* output, char requested_type) {
    pointer -= byte_count;
    if (byte_count == 4) {
        *reinterpret_cast<std::uint32_t*>(output) = words[pointer / 4];
    } else {
        std::memcpy(output, &words[pointer / 4], byte_count);
    }
    if (requested_type) {
        pointer -= 4;
        switch (words[pointer / 4]) {
        case 'f':
            if (requested_type == 'i') {
                *reinterpret_cast<std::int32_t*>(output) = static_cast<std::int32_t>(*reinterpret_cast<float*>(output));
            }
            break;
        case 'i':
            if (requested_type == 'f') {
                *reinterpret_cast<float*>(output) = static_cast<float>(*reinterpret_cast<std::int32_t*>(output));
            }
            break;
        }
    }
    return 0;
}
int ScriptStack::peek(std::int32_t byte_offset, void* output, char requested_type) {
    if (requested_type) {
        byte_offset += 4;
    }
    std::memcpy(output, &words[(pointer + byte_offset) / 4], 4);
    if (requested_type) {
        switch (words[(pointer + byte_offset - 4) / 4]) {
        case 'f':
            if (requested_type == 'i') {
                *reinterpret_cast<std::int32_t*>(output) = static_cast<std::int32_t>(*reinterpret_cast<float*>(output));
            }
            break;
        case 'i':
            if (requested_type == 'f') {
                *reinterpret_cast<float*>(output) = static_cast<float>(*reinterpret_cast<std::int32_t*>(output));
            }
            break;
        }
    }
    return 0;
}
}
