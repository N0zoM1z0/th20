#pragma once

#include <cstdint>
#include "DebugMemoryResource.hpp"
#include "LockRegistry.hpp"

namespace th20 {

// Native startup allocates eight bytes: an observed zero word followed by the
// real four-slot PMR resource. The word's meaning and startup body remain open.
struct AnimationCallback;

class DiagnosticAllocator {
public:
    DiagnosticAllocator();
    ~DiagnosticAllocator();

    void* allocate_bytes(std::int32_t size, const char* label);
    void release_bytes(void* memory);

    // Destroy outside the lock, then release scalar storage under slot 1.
    // Null is a no-op; process startup remains an external dependency.
    template<class T>
    void release_object(T* memory) {
        if (!memory) return;
        std::destroy_at(memory);
        std::lock_guard<std::recursive_mutex> guard(process_locks.slot(1));
        ::operator delete(memory);
    }

    // Native 0041F7C0: virtual callback destruction followed by locked delete.
    // The complete callback vtable and this dependency body remain pending.
    void release_animation_callback(AnimationCallback* callback);

    // Runtime uses ordinary nonthrowing default construction. Other scalar
    // instantiations have observed pre-clears whose reproduction remains open.
    template<class T>
    T* allocate_object(const char*);

    template<class T>
    T* allocate_array(const char*, std::int32_t count) {
        std::lock_guard<std::recursive_mutex> guard(process_locks.slot(1));
        T* memory = new T[count];
        return memory;
    }

    template<class T>
    void release_array(T* memory) {
        if (!memory) return;
        std::lock_guard<std::recursive_mutex> guard(process_locks.slot(1));
        delete[] memory;
    }

private:
    std::uint32_t state_word_;
    DebugMemoryResource resource_;
};

// Native pointer at 0x005B8894; production construction/startup remains pending.
extern DiagnosticAllocator* process_allocator;

static_assert(sizeof(void*) != 4 || sizeof(DiagnosticAllocator) == 8);

} // namespace th20

// Native owned-buffer cleanup releases storage and clears its owning lvalue.
// Keep this shared protocol visible to callers with more than one exit path.
#define TH20_RELEASE_ARRAY_AND_RESET(pointer) \
    (th20::process_allocator->release_array(pointer), (pointer) = nullptr)
