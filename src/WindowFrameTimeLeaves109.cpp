// Three real time-conversion helpers reached from original 113B Window
// timestamp pipeline. These are source-exact but their ultimate app-vs-
// C++ runtime authorship is left for an independent original-origin audit.
// The genuine copy constructor/assignment are the original 32B callees.
#include "NativeWindowFrameClockView.hpp"
#include <cstdint>
namespace th20 {

// A borrowed 8B time value with the same physical layout as the two-word
// FrameTimePair. Keeping this copyable view distinct means the original
// 113B game-parent trivial copy remains directly compiled, not a new call.
struct NativeFrameClockPairValue {
    std::uint64_t ticks;
    NativeFrameClockPairValue()=default;
    NativeFrameClockPairValue(const NativeFrameClockPairValue&);
    NativeFrameClockPairValue& operator=(const NativeFrameClockPairValue&);
};
static_assert(sizeof(NativeFrameClockPairValue)==sizeof(NativeFrameTimePair));

std::uint64_t __cdecl native_clock_ticks_541900();
NativeFrameTimePair* __cdecl read_frame_pair_4ac170(NativeFrameTimePair* destination) {
    NativeFrameClockPairValue sample;
    sample.ticks=native_clock_ticks_541900();
    *reinterpret_cast<NativeFrameClockPairValue*>(destination) =
        NativeFrameClockPairValue(sample);
    return destination;
}

struct NativeFrameTimePairBuilder {
    NativeFrameTimePair* native_stamp_input_451620(NativeFrameTimePair* output);
};
struct NativeFrameTimeValue64 {
    std::uint64_t stored_value;
    std::uint64_t native_timestamp_value_44c090();
};
static_assert(sizeof(NativeFrameTimeValue64)==8);
NativeFrameTimeValue64* __cdecl native_stamp_convert_4abb20(
    NativeFrameTimeValue64* output,const NativeFrameTimePair* input);
std::uint64_t __cdecl frame_time_u64_4ac200(NativeFrameTimePair* input) {
    NativeFrameTimePair first;
    NativeFrameTimeValue64 second;
    return native_stamp_convert_4abb20(
        &second,reinterpret_cast<NativeFrameTimePairBuilder*>(input)
            ->native_stamp_input_451620(&first))->native_timestamp_value_44c090();
}

void __cdecl native_time_breakdown_55139c(std::uint8_t* output,
                                          const std::uint64_t* ticks);
void __cdecl frame_time_breakdown_4ac270(std::uint8_t* output,
                                         std::uint64_t* ticks) {
    native_time_breakdown_55139c(output,ticks);
}
}
