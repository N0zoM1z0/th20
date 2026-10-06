#pragma once

#include <cstdint>

namespace th20::dialogue_text {

// Original shared storage starts at 0x005c4a20; its allocation remains external.
extern char decoded_text[];

// Native ABI takes one byte and returns a full int, not a bool.
int is_lead(std::uint8_t value);

// Input includes its encoded NUL. Both passes must stay within result storage;
// a lead byte must have a non-NUL trail byte. Each call overwrites the shared
// result, so callers must consume or copy it before another call.
const char* decode(const char* input);

} // namespace th20::dialogue_text
