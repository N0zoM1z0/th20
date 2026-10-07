#include "Identifier32.hpp"
namespace th20 {
Identifier32::Identifier32() : value(0) {}
std::uint32_t Identifier32::get() const { return value; }
void Identifier32::operator=(std::uint32_t input) { value = input; }
int Identifier32::equals(const Identifier32& other) const {
    return value == other.value ? 1 : 0;
}
} // namespace th20
