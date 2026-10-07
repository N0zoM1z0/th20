#pragma once

#include "LockRegistry.hpp"
#include <cstddef>
#include <new>

// The global template name is observed in the native EtamaArgInf control-block
// RTTI. Raw allocation and release both use process lock slot 1. Conversion is
// potentially throwing in the native control-block exception protocol.
template<class T>
struct DebugAllocator {
    using value_type = T;

    DebugAllocator() = default;
    template<class U> DebugAllocator(const DebugAllocator<U>&) {}

    T* allocate(std::size_t count) {
        std::lock_guard<std::recursive_mutex> guard(th20::process_locks.slot(1));
        T* memory = static_cast<T*>(::operator new(count * sizeof(T)));
        return memory;
    }

    void deallocate(T* memory, std::size_t) {
        std::lock_guard<std::recursive_mutex> guard(th20::process_locks.slot(1));
        ::operator delete(memory);
    }

    // Every specialization uses the same process allocation/release protocol.
    template<class U> bool operator==(const DebugAllocator<U>&) const noexcept {
        return true;
    }
};
