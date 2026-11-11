// Original native WindowState current RepeatCounter getter 0x0041CA50.
// It is a real 31B game-member leaf, called repeatedly by the 884B
// Window frame scheduler. The index is WindowState+0x2100 and the
// 12B array starts at +0x2104. Direct borrowed this expressions avoid
// an artificial local pointer and reproduce all 31 original bytes.
#include "NativeWindowFrameScheduleView.hpp"
#include <cstdint>
namespace th20 {
WindowState::RepeatCounter* NativeWindowFrameScheduleView::active_repeat_41ca50() {
    return reinterpret_cast<WindowState::RepeatCounter*>(reinterpret_cast<std::uint8_t*>(this)+0x2104)+reinterpret_cast<WindowState*>(this)->input_latch;
}
}
