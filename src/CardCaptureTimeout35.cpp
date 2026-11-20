// Original Card capture timer threshold predicate at 0x004887D0.
// The receiver aliases actual Card storage, with no secondary object.
#include "Card.hpp"
#include "NativeCardCaptureTimeoutView.hpp"
namespace th20 {
std::int32_t NativeCardCaptureTimeoutView::elapsed_4887d0() const {
    const Timer* timer = &reinterpret_cast<const Card*>(this)->age;
    return timer->at_least(60);
}
}
