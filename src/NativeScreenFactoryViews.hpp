#pragma once
#include <cstddef>
#include <cstdint>
namespace th20 {
struct NativeScreenInf;
struct NativeScreenFactoryAllocatorView {
    NativeScreenInf* allocate_screen_422d40(const char* source_label);
    void release_screen_41f7c0(NativeScreenInf* screen);
};
struct NativeScreenMemoryView {
    void clear_40c080(std::size_t bytes);
};
struct NativeScreenInfConstructorView {
    NativeScreenInf* construct_4233b0();
};
extern const char native_screen_diagnostic_56d768[];
}
