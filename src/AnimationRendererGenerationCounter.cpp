#include "NativeRendererPoolRegister.hpp"
namespace th20 {
std::uint32_t NativeGenerationPool::operator++(int unused) {
    std::uint32_t old=value;
    value=value+1;
    return old;
}
void NativeGenerationPool::operator&=(std::uint32_t mask) {
    value &= mask;
}
std::uint32_t NativeGenerationPool::generation_bits_4493e0(int bits) {
    return value << bits;
}
}
