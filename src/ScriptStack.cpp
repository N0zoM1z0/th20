#include "ScriptStack.hpp"

namespace th20 {

ScriptStack::ScriptStack() noexcept : pointer(0), frame_base(0) {}

void ScriptStack::reset() {
    pointer = 0;
    frame_base = 0;
    words.clear();
    auto& storage = words;
    storage.reserve(256);
}

std::uint32_t& ScriptStack::absolute(std::int32_t byte_offset) {
    if (words.size() < static_cast<std::size_t>(byte_offset / 4 + 1)) {
        words.resize(byte_offset / 4 + 1);
    }
    return words[byte_offset / 4];
}

std::uint32_t& ScriptStack::local(std::int32_t byte_offset) {
    if (words.size() < static_cast<std::size_t>((frame_base + byte_offset) / 4 + 1)) {
        words.resize((frame_base + byte_offset) / 4 + 1);
    }
    return words[(frame_base + byte_offset) / 4];
}

int ScriptStack::leave_frame() {
    const auto previous = frame_base;
    pop(4, &frame_base, 0);
    pointer = previous;
    return 0;
}

} // namespace th20
