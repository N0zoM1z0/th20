#pragma once
#include "DiagnosticAllocator.hpp"
#include <utility>

// One real scalar-allocation body shared by explicitly selected owners.
// Native pre-clear emission for some types remains independently unresolved.
namespace th20 {
template<class T> T* DiagnosticAllocator::allocate_object(const char*) { return new T; }
// Native constructor arguments are copied into the factory before forwarding.
template<class T, class... Args>
T* DiagnosticAllocator::allocate_object(const char*, Args... args) {
    return new T(std::forward<Args>(args)...);
}
}
