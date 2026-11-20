#include "LaserParameters.hpp"
#include "DiagnosticAllocator.hpp"
#include <cstring>

namespace th20 {

// The native base constructor initializes its real subobjects and scalar
// lanes first, then clears the complete 0x6F8 prefix.  The final Timer
// assignment is deliberately after the memset, just as in the original.
Laser::~Laser() {
    if (runtime_link_6d8) {
        process_allocator->release_object(runtime_link_6d8);
        runtime_link_6d8=nullptr;
    }
}

Laser::Laser()
    : flags(0), state(0), field_24(0), age(), timer_38(), timer_48(),
      position(), velocity(), angle(0.0f), field_74(0.0f), speed(0.0f),
      field_7c(0.0f), field_80(0.0f), field_84(0), field_88(0), handle(0),
      commands(), command_index(0), field_694(0), active_commands(0),
      field_6a0(0), field_6a4(0), field_6a8(0), timer_6ac(), timer_6bc(),
      field_6cc(0), field_6d0(0), field_6d4(0), runtime_link_6d8(nullptr),
      field_6dc(0), field_6e0(0), field_6e4(0), field_6e8(0xffffffffu),
      view_index(0), context(nullptr) {
    std::memset(this,0,0x6f8);
    age=0;
}

} // namespace th20
