#pragma once
#include "DiagnosticAllocator.hpp"

// One real scalar-allocation body shared by explicitly selected owners.
// Native pre-clear emission for some types remains independently unresolved.
namespace th20 {
template<class T> T* DiagnosticAllocator::allocate_object(const char*) { return new T; }
}
