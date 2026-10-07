#include "IntegerTriple.hpp"
#include "Color3.hpp"

namespace th20 {

IntegerTriple::IntegerTriple() : first(0), second(0), third(0) {}

IntegerTriple::IntegerTriple(std::int32_t third, std::int32_t second, std::int32_t first)
    : first(first), second(second), third(third) {}
IntegerTriple::IntegerTriple(const Color3& color) : first(0), second(0), third(0) {
    third = color.red;
    second = color.green;
    first = color.blue;
}
IntegerTriple IntegerTriple::operator+(IntegerTriple other) const {
    return IntegerTriple(
        static_cast<std::int32_t>(static_cast<std::uint32_t>(third)+static_cast<std::uint32_t>(other.third)),
        static_cast<std::int32_t>(static_cast<std::uint32_t>(second)+static_cast<std::uint32_t>(other.second)),
        static_cast<std::int32_t>(static_cast<std::uint32_t>(first)+static_cast<std::uint32_t>(other.first)));
}
IntegerTriple IntegerTriple::operator-(IntegerTriple other) const {
    return IntegerTriple(
        static_cast<std::int32_t>(static_cast<std::uint32_t>(third)-static_cast<std::uint32_t>(other.third)),
        static_cast<std::int32_t>(static_cast<std::uint32_t>(second)-static_cast<std::uint32_t>(other.second)),
        static_cast<std::int32_t>(static_cast<std::uint32_t>(first)-static_cast<std::uint32_t>(other.first)));
}
IntegerTriple IntegerTriple::operator*(float factor) const {
    return IntegerTriple(static_cast<std::int32_t>(third*factor),
                         static_cast<std::int32_t>(second*factor),
                         static_cast<std::int32_t>(first*factor));
}

} // namespace th20
