#pragma once
#include <cstdint>
namespace th20 {
// Native shared four-byte integer cursor; original source spelling is unknown.
struct IntegerIterator {
    std::int32_t value;
    explicit IntegerIterator(std::int32_t input) : value(input) {}
    IntegerIterator& operator++() { ++value; return *this; }
    bool operator!=(const IntegerIterator& other) const { return value!=other.value; }
    std::int32_t operator*() const { return value; }
};
// Full-width value tags select the independently observed finite domains.
// Their enum spelling is a hypothesis; only the native one-word ABI is proven.
enum class ProgressCharacters : std::int32_t { all=0, count=2 };
enum class ProgressProfiles : std::int32_t { all=0, count=9 };
inline IntegerIterator begin(ProgressCharacters) { return IntegerIterator(0); }
inline IntegerIterator end(ProgressCharacters) { return IntegerIterator(2); }
inline IntegerIterator begin(ProgressProfiles) { return IntegerIterator(0); }
inline IntegerIterator end(ProgressProfiles) { return IntegerIterator(9); }
static_assert(sizeof(IntegerIterator)==4);
} // namespace th20
