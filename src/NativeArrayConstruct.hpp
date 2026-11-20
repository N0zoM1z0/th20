#pragma once
#include <cstdint>
namespace th20 {
// Native constructor thunk receives the element address in ECX, matching
// the existing __thiscall ColoredVertex constructor and similar owners.
using NativeArrayElementConstructor = void (__thiscall *)(void*);
void __stdcall native_construct_array_40bc20(void* first,std::uint32_t stride,
    std::uint32_t count,NativeArrayElementConstructor constructor);
}
