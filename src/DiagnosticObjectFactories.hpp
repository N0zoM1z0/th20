#pragma once
#include "DiagnosticAllocator.hpp"
#include <utility>

// One scalar-construction body, including the empty-argument case.
namespace th20 {
template<class T, class... Args>
T* DiagnosticAllocator::allocate_object(const char*, Args... args) {
    return new T(std::forward<Args>(args)...);
}
}
