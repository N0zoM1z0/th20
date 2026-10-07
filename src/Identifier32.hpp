#pragma once
#include <cstdint>

namespace th20 {

// Native four-byte value protocol. Original tag and enclosing owner names
// remain unknown; identical zero constructors do not establish tag identity.
struct Identifier32 {
    std::uint32_t value;
    Identifier32();
    std::uint32_t get() const;
    void operator=(std::uint32_t input);
    int equals(const Identifier32& other) const;
};
static_assert(sizeof(Identifier32) == 4);

} // namespace th20
