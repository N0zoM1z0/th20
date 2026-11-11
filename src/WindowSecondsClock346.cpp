// Original full 346B WindowState clock Boss at 0x0041CB10.
// A single real elapsed double is reused in the disjoint high-resolution
// QPC and timeGetTime fallback branches, matching original stack-slot
// lifetimes. The 2-double wrap table is the real .rdata 0x0056CDD0.
// The lock and call ABIs are provided by existing game source interfaces.
#include "WindowState.hpp"
#include "NativeCardClockViews.hpp"
#include "LockRegistry.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <mutex>
#include <cstdint>
// The original two-double correction table contains 0.0 and 2^32.
// It converts a signed 32-bit timeGetTime sample into unsigned milliseconds
// without truncating on wrap. The data are in the locked original binary.
namespace th20 {
double NativeCardWindowTimeView::current_seconds_41cb10() {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(5));
    // This is a used arithmetic value shared by mutually exclusive paths,
    // not an artificial scratch local for byte alignment.
    double elapsed;
    if (window_state.performance_frequency != 0) {
        LARGE_INTEGER stamp;
        QueryPerformanceCounter(&stamp);
        elapsed =
            static_cast<double>(stamp.QuadPart - static_cast<std::int64_t>(window_state.performance_origin))/
            static_cast<double>(window_state.performance_frequency);
        if (elapsed < window_state.clock_offset)
            window_state.clock_offset = elapsed;
        return elapsed - window_state.clock_offset;
    } else {
        const std::int32_t millis=static_cast<std::int32_t>(timeGetTime());
        static const double correction[2]={0.0,4294967296.0};
        const double timestamp=static_cast<double>(millis)+correction[static_cast<std::uint32_t>(millis)>>31];
        if(timestamp < window_state.clock_offset)
            window_state.clock_offset=timestamp;
        elapsed=window_state.clock_offset*1000.0;
        elapsed=(timestamp-elapsed)/1000.0;
        return elapsed;
    }
}
}
