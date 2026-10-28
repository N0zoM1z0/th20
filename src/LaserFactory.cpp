// Complete native 0x004D47F0 LaserController four-type creator. The separately
// native-verified registration method executes after each successful virtual
// initializer; the four concrete allocator factories remain external native
// boundaries until their actual classes and lifetime sources are recovered.
#include "LaserParameters.hpp"
#include "DiagnosticAllocator.hpp"
namespace th20 {

std::int32_t LaserController::create_laser(std::int32_t kind,const void* parameters) {
    if (static_cast<std::int32_t>(count) >= 512) return 0;
    ++next_handle;
    if (static_cast<std::int32_t>(next_handle) < 0x10000) next_handle=0x10000;
    switch (kind) {
    case 0: {
        auto* beam=process_allocator->allocate_laser_line("D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\laser.cpp:296 LaserLineInf");
        if (!beam) return 0;
        beam->handle=next_handle;
        if (beam->initialize_laser(parameters)<0) return 0;
        register_laser(beam);
        break;
    }
    case 1: {
        auto* beam=process_allocator->allocate_laser_infinite("D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\laser.cpp:306 LaserInfiniteInf");
        if (!beam) return 0;
        beam->handle=next_handle;
        if (beam->initialize_laser(parameters)<0) return 0;
        register_laser(beam);
        break;
    }
    case 3: {
        auto* beam=process_allocator->allocate_laser_curve("D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\laser.cpp:328 LaserCurveInf");
        if (!beam) return 0;
        beam->handle=next_handle;
        if (beam->initialize_laser(parameters)<0) return 0;
        register_laser(beam);
        break;
    }
    case 2: {
        auto* beam=process_allocator->allocate_laser_beam("D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\laser.cpp:317 LaserBeamInf");
        if (!beam) return 0;
        beam->handle=next_handle;
        if (beam->initialize_laser(parameters)<0) return 0;
        register_laser(beam);
        break;
    }
    }
    return static_cast<std::int32_t>(next_handle);
}
}
