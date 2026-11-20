// Original 67B ScreenInf allocation/zero/construction helper at 0x00422D40.
#include "NativeScreenFactoryViews.hpp"
#include "NativeScreenEffect.hpp"
#include <new>
namespace th20 {
NativeScreenInf* NativeScreenFactoryAllocatorView::allocate_screen_422d40(
    const char*) {
    void* memory=::operator new(0x44);
    NativeScreenInf* result;
    if (memory!=nullptr) {
        reinterpret_cast<NativeScreenMemoryView*>(memory)->clear_40c080(0x44);
        result=reinterpret_cast<NativeScreenInfConstructorView*>(memory)->construct_4233b0();
    } else {
        result=nullptr;
    }
    return result;
}
}
