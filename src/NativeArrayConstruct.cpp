#include "NativeArrayConstruct.hpp"
namespace th20 {
void __stdcall native_construct_array_40bc20(void* first,std::uint32_t stride,
        std::uint32_t count,NativeArrayElementConstructor constructor) {
    while (count-- > 0) {
        constructor(first);
        first=static_cast<unsigned char*>(first)+stride;
    }
}
}
